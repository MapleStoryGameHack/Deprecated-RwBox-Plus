//---------------------------------------------------------------------------
#include <fmx.h>

#include <windows.h>
#include <tchar.h>
#pragma hdrstop
#include <gdiplus.h>
#include "Application.h"
#include "FormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

ULONG_PTR gdiplusToken;
extern "C" DWORD WINAPI FMXmain(LPVOID lpParameter)
{
	Sleep(1000);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	gdiplusStartupInput.GdiplusVersion = 1;
	gdiplusStartupInput.DebugEventCallback = NULL;
	gdiplusStartupInput.SuppressBackgroundThread = false;
	gdiplusStartupInput.SuppressExternalCodecs = false;
	Gdiplus::GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);
	try
	{
		Fmx::Forms::Application->Initialize();

		Fmx::Forms::Application->CreateForm(__classid(TfrmMain), &frmMain);
		Fmx::Forms::Application->Run();
		//TerminateProcess(GetCurrentProcess(),0);
	}
	catch (Exception &exception)
	{
		Fmx::Forms::Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Fmx::Forms::Application->ShowException(&exception);
		}
	}
	return 0;
}

