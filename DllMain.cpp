//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "DllMain.h"
#include "ThreadMain.h"
#include "Variable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ThreadMain *threadMain;
HINSTANCE hinstDll;

//---------------------------------------------------------------------------

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	if (fwdreason == DLL_PROCESS_ATTACH)
	{
		::hinstDll = hinstDll;
		hIcon1 = LoadIcon(hinstDll,"IDI_ICON1");
		threadMain = new ThreadMain(false);
	}
	else if (fwdreason == DLL_PROCESS_DETACH)
	{

	}
	return 1;
}
//---------------------------------------------------------------------------

