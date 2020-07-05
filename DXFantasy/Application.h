#pragma once
#include <windows.h>
#include "DXFantasyUtil.h"
#include "RendererLib\Renderer.h"

class SystemWin;
class Application
{
public:
	Application(HINSTANCE hInstance);

	DXFResult				Initialize();
	DXFResult				Run();

	static Application*		GetApp();
	static SystemWin*		GetSystem();

	void					SignalQuit();
	void					SignalPause();

private:
	static Application*		mApp;
	static SystemWin*		mSystem;
	Renderer				mRenderer;

	int						mAppFrameCount = 0;
	bool					mAppPaused = false;
	bool					mAppQuit = false;
};

