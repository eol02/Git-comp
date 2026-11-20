#include <Windows.h>

LRESULT CALLBACK Default_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) {

}

LRESULT CALLBACK Default_Proc(
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