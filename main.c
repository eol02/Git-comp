#include <Windows.h>
#include "common.h"

HWND Member[MAX_MEMBERS] = { 0 };
int Member_index = 0;
int MemberList_count = 0;


HWND main_hwnd = NULL;
HWND MainPage_hwnd = NULL;
HWND CreateGroupPage_hwnd = NULL;
HWND EventRegisterPage_hwnd = NULL;
HWND MemberPanel_hwnd = NULL;
HWND MemberContent_hwnd = NULL;

LRESULT CALLBACK Default_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Page_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ScrollPanel_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void RegisterPageClass(HINSTANCE hInstance);
HWND CreatePageWindow(HINSTANCE hInstance, HWND parent);
HWND AddMemberList(HINSTANCE hInstance, HWND parent);
void DeleteMemberList(HWND Member[]);
void SignupMember(HWND Member[], char Signup[][NAME_LEN]);
HWND MainPage(HINSTANCE hInstance, HWND parent);
HWND CreateGroupPage(HINSTANCE hInstance, HWND parent);
HWND EventRegisterPage(HINSTANCE hInstance, HWND parent);

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) {
	const wchar_t MAIN_CLASS[] = L"Main_Class";

	WNDCLASSW wc = { 0 };		//메인 창 클래스

	wc.lpfnWndProc = Default_Proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = MAIN_CLASS;

	RegisterClassW(&wc);		//창 클래스 등록
	RegisterPageClass(hInstance);

	main_hwnd = CreateWindowExW(		//메인 창 생성
		0,
		MAIN_CLASS,
		NULL,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		700,
		800,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (main_hwnd == NULL)
	{
		return 0;
	}

	MainPage_hwnd = MainPage(hInstance, main_hwnd);
	CreateGroupPage_hwnd = CreateGroupPage(hInstance, main_hwnd);
	EventRegisterPage_hwnd = EventRegisterPage(hInstance, main_hwnd);

	ShowWindow(main_hwnd, SW_SHOW);
	ShowWindow(MainPage_hwnd, SW_SHOW);
	//ShowWindow(EventRegisterPage_hwnd, SW_SHOW);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0) > 0) {		//메세지 루프
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK Default_Proc(		//기본 창 프로시저
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			return 0;
		}

		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Page_Proc(			//페이지 창 프로시저
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED) {
				switch (LOWORD(wParam)) {
					case 1001:
						ShowWindow(MainPage_hwnd, SW_HIDE);
						ShowWindow(CreateGroupPage_hwnd, SW_SHOW);
						break;

					case 2001:
						Member[Member_index] = AddMemberList(GetModuleHandleW(NULL), MemberContent_hwnd);
						MemberList_count++;
						ShowWindow(Member[Member_index], SW_SHOW);
						Member_index++;
						break;

					case 2002:
						DeleteMemberList(Member);
						MemberList_count--;
						break;

					case 2005:
						SignupMember(Member, members);
						break;
				}
			}

		case WM_CTLCOLORSTATIC:
			SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
			return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
	}

	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK ScrollPanel_Proc(			//스크롤 패널 프로시저
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	SCROLLINFO si = { 0 };

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	GetScrollInfo(hwnd, SB_VERT, &si);

	switch(uMsg){
		case WM_CREATE:
			si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
			si.nMin = 0;
			si.nMax = 6020;
			si.nPage = 350;
			si.nPos = 0;

			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
			
			return 0;

		case WM_VSCROLL:
			switch (LOWORD(wParam)) {
				case SB_LINEUP:
					si.nPos -= 10;
					break;

				case SB_LINEDOWN:
					si.nPos += 10;
					break;

				case SB_PAGEUP:
					si.nPos -= (int)si.nPage;
					break;

				case SB_PAGEDOWN:
					si.nPos += (int)si.nPage;
					break;

				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;
			}
			
			si.nPos = SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
			SetWindowPos(MemberContent_hwnd, NULL,
				0, -si.nPos, 0, 0,
				SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			return 0;

		case WM_MOUSEWHEEL:
			si.nPos -= GET_WHEEL_DELTA_WPARAM(wParam);
			si.nPos = SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
			SetWindowPos(MemberContent_hwnd, NULL,
				0, -si.nPos, 0, 0,
				SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			return 0;
	}


	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

void RegisterPageClass(HINSTANCE hInstance) {
	WNDCLASSW wc = { 0 };

	wc.lpfnWndProc = Page_Proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Page_Class";
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClassW(&wc);
}

HWND CreatePageWindow(HINSTANCE hInstance, HWND parent) {		//페이지 창 생성 함수
	RECT rect;
	GetClientRect(parent, &rect);

	 return CreateWindowExW(
		0,
		L"Page_Class",
		NULL,
		WS_CHILD,
		0,
		0,
		rect.right,
		rect.bottom,
		parent,
		NULL,
		hInstance,
		NULL
	);
}

HWND AddMemberList(HINSTANCE hInstance, HWND parent) {		//멤버 목록 추가 함수
	if (MemberList_count >= MAX_MEMBERS) {
		MessageBoxW(main_hwnd, L"입력 범위를 초과하였습니다.", L"입력 오류",
			MB_OK | MB_ICONWARNING);
	}

	else {
		HWND Member = CreateWindowExW(
			0,
			L"STATIC",
			NULL,
			WS_CHILD | WS_BORDER,
			15,
			10 + Member_index * (55 + 5),
			550,
			55,
			parent,
			NULL,
			hInstance,
			NULL
		);

		CreateWindowExW(
			WS_EX_CLIENTEDGE,
			L"EDIT",
			NULL,
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
			40,
			15,
			450,
			20,
			Member,
			(HMENU)2004,
			hInstance,
			NULL
		);

		CreateWindowExW(
			0,
			L"BUTTON",
			NULL,
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			10,
			20,
			15,
			15,
			Member,
			(HMENU)2003,
			hInstance,
			NULL
		);

		return Member;
	}
}

void DeleteMemberList(HWND Member[]) {						//멤버 목록 삭제 함수
	for (int i = Member_index - 1; i >= 0; i--) {
		if (SendMessageW(GetDlgItem(Member[i], 2003), BM_GETCHECK, 0, 0) == BST_CHECKED) {
			DestroyWindow(Member[i]);
			
			for (int j = i; j < Member_index; j++) {
				Member[j] = Member[j + 1];

				SetWindowPos(Member[j], NULL,
					15, 10 + j * (55 + 5), 0, 0,
					SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
			}

			Member_index--;
		}
	}
}

void SignupMember(HWND Member[], char Signup[][NAME_LEN]) {					//멤버 등록 함수
	wchar_t tmp[NAME_LEN];

	if (Member_index == 0) {
		MessageBoxW(main_hwnd, L"멤버가 없습니다.", L"생성 오류",
			MB_OK | MB_ICONWARNING);

		return;
	}

	else for (int i = 0; i < Member_index; i++) {
		if (GetWindowTextLengthW(GetDlgItem(Member[i], 2004)) == 0) {
			MessageBoxW(main_hwnd, L"이름을 입력해주세요.", L"입력 오류",
				MB_OK | MB_ICONWARNING);

			return;
		}

		else if (GetWindowTextLengthW(GetDlgItem(Member[i], 2004)) >= NAME_LEN) {
			MessageBoxW(main_hwnd, L"입력 범위를 초과하였습니다.", L"입력 오류",
				MB_OK | MB_ICONWARNING);

			return;
		}
	}

	for (int i = 0; i < Member_index; i++) {
		GetWindowTextW(GetDlgItem(Member[i], 2004), tmp, NAME_LEN);

		WideCharToMultiByte(
			CP_UTF8,
			0,
			tmp,
			-1,
			Signup[i],
			NAME_LEN,
			NULL,
			NULL
		);
	}
}

HWND MainPage(HINSTANCE hInstance, HWND parent) {			//메인 페이지 함수
	HWND MainPage_hwnd = CreatePageWindow(hInstance, parent);

	CreateWindowExW(
		0,
		L"BUTTON",
		L"새 모임 생성",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		50,
		170,
		200,
		40,
		MainPage_hwnd,
		(HMENU)1001,
		hInstance,
		NULL
	);

	return MainPage_hwnd;
}

HWND CreateGroupPage(HINSTANCE hInstance, HWND parent) {			//그룹 생성 페이지 함수
	HWND CreateGroupPage_hwnd = CreatePageWindow(hInstance, parent);

	WNDCLASSW wc = { 0 };

	wc.lpfnWndProc = ScrollPanel_Proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"ScrollPanel_Class";
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClassW(&wc);

	MemberPanel_hwnd = CreateWindowExW(
		0,
		L"ScrollPanel_Class",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL,
		40,
		250,
		600,
		350,
		CreateGroupPage_hwnd,
		NULL,
		hInstance,
		NULL
	);

	MemberContent_hwnd = CreateWindowExW(
		0,
		L"STATIC",
		NULL,
		WS_CHILD | WS_VISIBLE,
		0,
		0,
		600,
		6020,
		MemberPanel_hwnd,
		NULL,
		hInstance,
		NULL
	);

	CreateWindowExW(
		0,
		L"BUTTON",
		L"+",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		100,
		220,
		17,
		17,
		CreateGroupPage_hwnd,
		(HMENU)2001,
		hInstance,
		NULL
	);

	CreateWindowExW(
		0,
		L"BUTTON",
		L"-",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		123,
		220,
		17,
		17,
		CreateGroupPage_hwnd,
		(HMENU)2002,
		hInstance,
		NULL
	);

	CreateWindowExW(
		0,
		L"BUTTON",
		L"생성",
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		530,
		650,
		100,
		35,
		CreateGroupPage_hwnd,
		(HMENU)2005,
		hInstance,
		NULL
	);

	CreateWindowExW(
		0,
		L"STATIC",
		L"참여자",
		WS_CHILD | WS_VISIBLE | SS_CENTER,
		30,
		220,
		70,
		20,
		CreateGroupPage_hwnd,
		NULL,
		hInstance,
		NULL
	);

	return CreateGroupPage_hwnd;
}

HWND EventRegisterPage(HINSTANCE hInstance, HWND parent) {				//이벤트 등록 페이지 함수
	HWND EventRegisterPage_hwnd = CreatePageWindow(hInstance, parent);

	CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		50,
		200,
		350,
		30,
		EventRegisterPage_hwnd,
		(HMENU)3001,
		hInstance,
		NULL
	);

	CreateWindowExW(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		NULL,
		WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
		50,
		280,
		350,
		30,
		EventRegisterPage_hwnd,
		(HMENU)3002,
		hInstance,
		NULL
	);

	return EventRegisterPage_hwnd;
}