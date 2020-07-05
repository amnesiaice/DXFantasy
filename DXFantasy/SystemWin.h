#pragma once

// windows
#include <windows.h>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <wrl.h>

// debug

#include "DXFantasyUtil.h"

class SystemWin
{
public:
	SystemWin(HINSTANCE inAppInstHandle);
	DXFResult				InitMainSystemWindow();
	int						HandleMessage();
	
private:
	HINSTANCE				mhAppInst;

	// Window
	HWND					mhMainWnd = nullptr;		// main window handle
	std::wstring			mMainWndCaption = L"d3d App";
	int						mClientWidth = 800;
	int						mClientHeight = 600;
};

