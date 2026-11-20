#include <Windows.h>

LRESULT CALLBACK Default_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) {
	const wchar_t MAIN_CLASS[] = L"Main_Class";

	WNDCLASS wc = { 0 };		//메인 창 클래스

	wc.lpfnWndProc = Default_Proc;
	wc.hInstance = hInstance;
	wc.lpszClassName = MAIN_CLASS;


}

LRESULT CALLBACK Default_Proc(		//기본 창 프로시저
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hwnd);

		case WM_DESTROY:
			PostQuitMessage(0);
	}
}