//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Application.h"
#include "ThreadMain.h"
#include "Keys.h"
#include "WindowHook.h"
#include "Version.h"
#include "Map.h"
#include "AutoLogin.h"
#include "Variable.h"
#include "Script.h"
#include "ThreadBot.h"

#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall ThreadMain::ThreadMain(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------

void __fastcall ThreadMain::RefreshData()
{

}
//---------------------------------------------------------------------------
void __fastcall ThreadMain::Execute()
{
	Sleep(500);
	TStringList* list = new TStringList();
	list->Delimiter = ' ';
	list->DelimitedText = GetCommandLine();
	LoginServer = StrToInt(list->Strings[6]);
	LoginChannel = StrToInt(list->Strings[7]);
	LoginChar = StrToInt(list->Strings[8]);
	AutoGuagi_Start = StrToInt(list->Strings[10]);
	strcpy(LoginerPath,AnsiString(list->Strings[9]).c_str());
	strcpy(GameAccount,AnsiString(list->Strings[4]).c_str());
	delete list;

	while( (hWndLoginer=FindWindow(NULL,"LoginMgr")) == NULL);

	new ThreadBot(false);
	InitializeKeys();
	InitMapList();


	InstallWindowHook();
    InstallScript();
	LoginProcdure();
	FMXmain(NULL);
	while(true)
	{

		Sleep(200);
    }
	TerminateProcess(GetCurrentProcess(),0);
}
//---------------------------------------------------------------------------
