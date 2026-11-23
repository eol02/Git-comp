#include <Windows.h>

LRESULT CALLBACK Default_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	RegisterClassW(&wc);

	HWND main_hwnd = CreateWindowExW(		//메인 창 생성
		0,
		MAIN_CLASS,
		NULL,
		WS_OVERLAPPEDWINDOW,
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

	ShowWindow(main_hwnd, SW_SHOW);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0) > 0) {		//메세지 루프
		DispatchMessage(&msg);
	}
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