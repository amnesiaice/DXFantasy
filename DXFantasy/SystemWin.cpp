#include "SystemWin.h"
#include "Application.h"

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// WM_ACTIVATE is sent when the window is activated or deactivated.  
		// We pause the game when the window is deactivated and unpause it 
		// when it becomes active.  
	case WM_ACTIVATE:
		return 0;

		// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		return 0;

		// The WM_MENUCHAR message is sent when a menu is active and the user presses 
		// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

		// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		Application::GetApp()->SignalQuit();
		PostQuitMessage(0);
		return 0;

	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			Application::GetApp()->SignalPause();
			PostQuitMessage(0);
		}

		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

SystemWin::SystemWin(HINSTANCE inAppInstHandle)
{
	mhAppInst = inAppInstHandle;
}


DXFResult SystemWin::InitMainSystemWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"MainWnd";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return DXFResult::FAILED_WINDOW;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0);
	if (!mhMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return DXFResult::FAILED_WINDOW;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	// Finish without error, return succeed
	return DXFResult::DXF_SUCCEED;
}

int SystemWin::HandleMessage()
{
	MSG msg = { 0 };

	if (msg.message != WM_QUIT)
	{ 
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		Application::GetApp()->SignalQuit();
	}

	return (int)msg.wParam;
}

