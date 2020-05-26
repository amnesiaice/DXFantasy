#include "D3DApp.h"



D3DApp* D3DApp::mApp = nullptr;

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return D3DApp::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstancem,
	PSTR cmdLine, int showCmd)
{
	D3DApp theApp(hInstance);
	if (!theApp.Initialize())
		return 0;
	return theApp.Run();

	return 0;
}

D3DApp::D3DApp(HINSTANCE hInstance)
{
	mhAppInst = hInstance;
	assert(mApp == nullptr);
	mApp = this;
}

D3DApp::~D3DApp()
{

}

bool D3DApp::Initialize()
{
	if (!InitMainWindow())
		return false;
	if (!InitDirect3D())
		return false;
	return true;
}

D3DApp* D3DApp::GetApp()
{
	return mApp;
}

LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int D3DApp::Run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			//mTimer.Tick();

			//if (!mAppPaused)
			//{
			//	CalculateFrameStats();
			//	Update(mTimer);
			//	Draw(mTimer);
			//}
			//else
			//{
			//	Sleep(100);
			//}
		}
	}

	return (int)msg.wParam;
}

bool D3DApp::InitMainWindow()
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
		return false;
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
		return false;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	return true;
}

bool D3DApp::InitDirect3D()
{
	return true;
}


