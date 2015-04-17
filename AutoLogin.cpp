//---------------------------------------------------------------------------

#pragma hdrstop

#include "AutoLogin.h"
#include "Pointer.h"
#include "WindowHook.h"
#include "Variable.h"
#include "Function.h"
#include <vcl.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)


void LoginProcdure()
{
	PostMessage(hWndLoginer,WM_PING,GetCurrentProcessId(),0);
	//登入中
    Sleep(2000);

	DWORD TempTime = 0;
    TempTime = GetTickCount();
	while ( ReadPointer(pLogin,oLoginPage) != 1 || *(DWORD*)pLogin == 0 )
	{
		if( GetTickCount() - TempTime > 90*1000)
			TerminateProcess(GetCurrentProcess(), 0);
		Sleep(100);
	}
	PostMessage(hWndLoginer,WM_PING,GetCurrentProcessId(),1);
    //進伺服器中
	Sleep(500);
	TempTime = GetTickCount();
	while( ReadPointer(pLogin,oLoginPage) == 1)
	{
		if( GetTickCount() - TempTime > 90*1000)
			TerminateProcess(GetCurrentProcess(), 0);
		WritePointer(plServer,olServer,LoginServer);
		WritePointer(plChannel,olChannel,LoginChannel);
		PressKey(hWndMS,VK_RETURN);
		Sleep(500);
	}
	Sleep(500);
	TempTime = GetTickCount();
	PostMessage(hWndLoginer,WM_PING,GetCurrentProcessId(),2);
	//選角中
	do {

		if( GetTickCount() - TempTime > 90*1000)
			TerminateProcess(GetCurrentProcess(), 0);
		Sleep(1000);
	}while ( ReadPointer(pLogin,oLoginPage) != 2 );
	Sleep(500);
    TempTime = GetTickCount();
	while( ReadPointer(pLogin,oLoginPage) == 2 && !(*(DWORD*)PeopleBase))
	{
		if( GetTickCount() - TempTime > 90*1000)
			TerminateProcess(GetCurrentProcess(), 0);
		WritePointer(pLogin,oLoginChar,LoginChar);
		PressKey(hWndMS,VK_RETURN);
		Sleep(1000);
	}
	PostMessage(hWndLoginer,WM_PING,GetCurrentProcessId(),3);
	//登入成功
}


