#include "Application.h"
#include "SystemWin.h"

// static 
Application* Application::mApp = nullptr;
SystemWin* Application::mSystem = nullptr;

Application::Application(HINSTANCE hInstance)
{
	ASSERT(mApp == nullptr);
	mApp = this;

	ASSERT(mSystem == nullptr);
	SystemWin* theSystem = new SystemWin(hInstance);
	mSystem = theSystem;

	ASSERT(mApp != nullptr);
	ASSERT(mSystem != nullptr);
}

DXFResult Application::Initialize()
{
	if (SUCCEED(mSystem->InitMainSystemWindow()))
		return DXFResult::FAILED_WINDOW;

	// Finish without error, return succeed
	return DXFResult::DXF_SUCCEED;
}

DXFResult Application::Run()
{
	while (!mAppQuit)
	{
		mSystem->HandleMessage();
		// Otherwise, do animation/game stuff.
		if (!mAppPaused)
		{
			// Add frame count
			mAppFrameCount++;
			mRenderer.RendererFrameCountIncrease();

		}
		else
		{
			Sleep(100);
		}
	}
	
	// Finish without error, return succeed
	return DXFResult::DXF_SUCCEED;
}


Application* Application::GetApp()
{
	ASSERT(mApp != nullptr);
	return mApp;
}

SystemWin* Application::GetSystem()
{
	ASSERT(mSystem != nullptr);
	return mSystem;
}

void Application::SignalQuit()
{
	mAppQuit = true;
}

void Application::SignalPause()
{
	mAppPaused = !mAppPaused;
}
