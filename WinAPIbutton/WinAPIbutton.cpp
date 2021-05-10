#include <windows.h>
#include "resource.h"
#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK about(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstanc, LPSTR lpCmdLine, int nShowCmd)

{
	char szTitle[] = "My First Window Program";
	char szClass[] = "Class";

	// 1. Declare window class -----------------------------------------------------

	WNDCLASSEX WndEx;
	WndEx.style = NULL; // window style
	WndEx.lpfnWndProc = WndProc; //window procedure(function) pointer
	WndEx.cbClsExtra = 0; //additional memory size for widow class
	WndEx.cbWndExtra = 0; // additional memory size for window
	WndEx.hInstance = hInstance; // intance handle of the window procdeure
	WndEx.hIcon = LoadIcon(NULL, ""); //big icon
	WndEx.hIconSm = LoadIcon(hInstance, ""); //small icon
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor
	WndEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//background
	WndEx.lpszMenuName = "IDR_MENU";//menui
	WndEx.lpszClassName = szClass;//window class name
	WndEx.cbSize = sizeof(WndEx); //size of window class structure

	// 2. Register window calss -----------------------------------------------------

	RegisterClassEx(&WndEx);

	// 3. Create window -------------------------------------------------------------
	HWND hWnd;
	hWnd = CreateWindowEx(NULL, szClass, szTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		320 * 2, 240 * 2, NULL, NULL, hInstance, NULL);

	// 4. Show and Update window-----------------------------------------------------

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	// 5. Message loop --------------------------------------------------------------

	MSG mSg;
	while (TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButtPrint, hButtExit, hButtDialog;
	static HWND hEdit;

	switch (uMsg)
	{
	case WM_CREATE:
		hButtPrint = CreateWindow("BUTTON", "Output", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			60, 60, 90, 30, hWnd, (HMENU)1, NULL, NULL);

		hButtExit = CreateWindow("BUTTON", "Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			60, 120, 90, 30, hWnd, (HMENU)2, NULL, NULL);

		hButtDialog = CreateWindow("BUTTON", "Open Dialog", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			60, 180, 120, 30, hWnd, (HMENU)3, NULL, NULL);

		hEdit = CreateWindow("EDIT", "Edit", WS_CHILD | WS_VISIBLE | WS_BORDER,
			160, 60, 90, 30, hWnd, (HMENU)5, NULL, NULL);

		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 1:
			MessageBox(hWnd, "Button 1 has been clicked !!!", "Output", NULL);

			break;
		case 2:
			PostQuitMessage(0);

			break;
		case 3:
			DialogBox(hInst, "IDD_DIALOG", hWnd, DLGPROC(about));

			break;
		}

		return FALSE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK about(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTT_EXIT:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}

	return FALSE;
}