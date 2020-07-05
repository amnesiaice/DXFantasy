#include <WindowsX.h>
#include "Application.h"
#include "DXFantasyUtil.h"
#include "SystemWin.h"

using Microsoft::WRL::ComPtr;
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstancem,
	PSTR cmdLine, int showCmd)
{
	Application theApp(hInstance);

	if (SUCCEED(Application::GetApp()->Initialize()))
		return 0;
	if (SUCCEED(Application::GetApp()->Run()))
		return 0;

	return 0;
}