#pragma once
// windows
#include <windows.h>
#include <string>

// d3d12
#include <d3d12.h>

// debug
#include <cassert>

// link lib
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	~D3DApp();

	bool Initialize();
	static D3DApp* GetApp();
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	int Run();
private:
	bool InitMainWindow();
	bool InitDirect3D();
	static D3DApp* mApp;
	HINSTANCE mhAppInst = nullptr; // application instance handle
	HWND      mhMainWnd = nullptr; // main window handle


	std::wstring mMainWndCaption = L"d3d App";
	int mClientWidth = 800;
	int mClientHeight = 600;
};


