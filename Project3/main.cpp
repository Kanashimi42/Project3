#include "Windows.h"
#include "tchar.h"
#include <string>
using std::wstring;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);
void KeyUpHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);
void WmCharHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);
void Cyclez(bool& bMove, HWND hwnd);
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WCHAR className[] = L"FirstWindow";

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;

	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass)) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"My first window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, //x,y
		CW_USEDEFAULT, CW_USEDEFAULT, //width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
bool bMove = true;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		KeyDownHandler(hwnd, wParam, lParam);
		break;

	case WM_KEYUP:
		KeyUpHandler(hwnd, wParam, lParam);
		break;

	case WM_CHAR:
		WmCharHandler(hwnd, wParam, lParam);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
bool bStarted = false;

int counter = 0;
void Cyclez(bool& bMove, HWND hwnd)
{
	if (bStarted)
	{
		SetWindowPos(hwnd, NULL, 0, 0, 300, 300, SWP_NOZORDER);
		bStarted = false;
	}
	Sleep(100);
	do {
		SetWindowPos(hwnd, NULL, counter, 0, 300, 300, SWP_NOZORDER);
		counter++;
		if (GetAsyncKeyState(VK_ESCAPE)) {
			bMove = false;
		}
	} while (bMove);
}
void KeyUpHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int vkey = wParam;
	if (vkey == VK_RETURN)
	{
		bMove = true;
		bStarted = true;
		Cyclez(bMove,hwnd);
	}

}

void KeyDownHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int vkey = wParam;

	short repeat = LOWORD(lParam);
}
void WmCharHandler(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	WCHAR symbol = wParam;

	static wstring str;
	str += symbol;

	SetWindowText(hwnd, str.c_str());
}