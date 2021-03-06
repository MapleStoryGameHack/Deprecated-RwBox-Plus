//---------------------------------------------------------------------------
#include <stdio.h>
#pragma hdrstop
#include "Function.h"
//---------------------------------------------------------------------------
#define jmp(from, to) (int)(((int)to - (int)from) - 5);
//---------------------------------------------------------------------------
void HookICS(unsigned int Pointer, void *Function) // Written by Toby
 //這個和Write4Byte其實是一樣的，只是加了轉型更方便寫HOOK函數
{
	__try
	{
		DWORD OldProtection;
		VirtualProtect((LPVOID)Pointer, 0x4, PAGE_EXECUTE_READWRITE, &OldProtection);
		*(unsigned int*)(Pointer) = (unsigned int)Function;  //轉型在這裡
		VirtualProtect((LPVOID)Pointer, 0x4, OldProtection, &OldProtection);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}
//---------------------------------------------------------------------------

DWORD GetFunctionAddress(_TCHAR *moduleName, char *functionName) // Written by Toby
{
	return (DWORD)GetProcAddress(GetModuleHandle(moduleName), functionName);
}
//---------------------------------------------------------------------------

bool SendKey(HWND hWnd, WORD Key)
{
	PostMessage(hWnd, WM_KEYDOWN, Key, (MapVirtualKey(Key, 0) << 16) + 0xC0000001);
	return PostMessage(hWnd, WM_KEYUP, Key, (MapVirtualKey(Key, 0) << 16) + 0xC0000001);
}
//---------------------------------------------------------------------------

bool PressKey(HWND hWnd, WORD Key)
{
	return PostMessage(hWnd, WM_KEYDOWN, Key, (MapVirtualKey(Key, 0) << 16) + 1);
}
//---------------------------------------------------------------------------

void MEMwrite(PVOID address, void* val, int bytes)  	//寫入AOB 用法 MEMwrite(0x00400000,(BYTE*)"\x90\x90",2);
{														//MEMwrite(位置,AOB,長度);
	__try
	{
		DWORD d, ds;
		VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
		memcpy(address, val, bytes);
		VirtualProtect(address,bytes,d,&ds);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}
void AsmJump(const DWORD ulAddress, LPCVOID Function, unsigned Nops)	//Jmp  AsmJump(位置,主程序,幾個nop);
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)ulAddress,10,PAGE_EXECUTE_READWRITE, &OldProtection);
	__try {
	*(LPBYTE)ulAddress = 0xE9;
	*(LPDWORD)(ulAddress + 1) = jmp(ulAddress, Function);
	memset(((LPBYTE)ulAddress + 5), 0x90, Nops); }
    __except (EXCEPTION_EXECUTE_HANDLER) {}
	VirtualProtect((LPVOID)ulAddress,10,OldProtection, &OldProtection);
}
void AsmCall(const DWORD ulAddress, LPCVOID Function, unsigned Nops)   //Call  AsmCall(位置,主程序,幾個nop);
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)ulAddress,10,PAGE_EXECUTE_READWRITE, &OldProtection);
	__try {
	*(LPBYTE)ulAddress = 0xE8;
	*(LPDWORD)(ulAddress + 1) = jmp(ulAddress, Function);
	memset(((LPBYTE)ulAddress + 5), 0x90, Nops); }
	__except (EXCEPTION_EXECUTE_HANDLER) {}
	VirtualProtect((LPVOID)ulAddress,10,OldProtection, &OldProtection);
}
void Write4Byte(long adr,int value)                                    //ICS的寫入Value(DD)
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)adr,0x4,PAGE_EXECUTE_READWRITE, &OldProtection);
	__try { *(int*)(adr)=value; }
	__except (EXCEPTION_EXECUTE_HANDLER) {}
	VirtualProtect((LPVOID)adr,0x4,OldProtection, &OldProtection);
}
void WriteByte(long adr,unsigned char value)                           //這個妳因該用不到
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)adr,0x4,PAGE_EXECUTE_READWRITE, &OldProtection);
	__try {*(unsigned char*)(adr)=value; }
	__except (EXCEPTION_EXECUTE_HANDLER) {}
	VirtualProtect((LPVOID)adr,0x4,OldProtection, &OldProtection);
}
unsigned long ReadPointer( unsigned long ulBase, int iOffset )          //ReadProcessMemory簡單板
{                                                                           //好比說我要讀取某基指
   __try { return *(unsigned long*)(*(unsigned long*)ulBase + iOffset); }   //ex.00FABCDEF , offset:5A0
   __except (EXCEPTION_EXECUTE_HANDLER) { return 0; }                       //long getpo = ReadPointer(0x00FABCDEF,0x5A0);
}

bool WritePointer(unsigned long ulBase, int iOffset, int iValue)         //寫入某Pointer的位置   WritePointer(0x00FABCDEF,0x5A0,50);    寫入50
{
	__try { *(int*)(*(unsigned long*)ulBase + iOffset) = iValue; return true; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

unsigned long GetPointedAddress(unsigned long ulBase, int iOffset) 			//GetPointedAddress(0x00FABCDEF,0x5A0);  //取得這個基指的位置
{
	__try { return *(unsigned long*)ulBase + iOffset; }
	__except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
}

/**********************************************/
unsigned char GetVirtualKeyCodeByName(char * KeyName) {
	if (!KeyName || KeyName[0] == 0)
		return 0;
	else if (KeyName[0] == '`' || KeyName[0] == '~')
		return VK_OEM_3;
	else if (stricmp(KeyName, "SPACE") == 0 || KeyName[0] == ' ')
		return VK_SPACE;
	else if (stricmp(KeyName, "INS") == 0 || stricmp(KeyName, "INSERT") == 0)
		return VK_INSERT;
	else if (stricmp(KeyName, "DEL") == 0 || stricmp(KeyName, "DELETE") == 0)
		return VK_DELETE;
	else if (stricmp(KeyName, "HOME") == 0)
		return VK_HOME;
	else if (stricmp(KeyName, "END") == 0)
		return VK_END;
	else if (stricmp(KeyName, "PGUP") == 0 || stricmp(KeyName, "PAGEUP") == 0)
		return VK_PRIOR;
	else if (stricmp(KeyName, "PGDOWN") == 0 || stricmp(KeyName, "PAGEDOWN") == 0)
		return VK_NEXT;
	else if (stricmp(KeyName, "CTRL") == 0 || stricmp(KeyName, "CONTROL") == 0)
		return VK_CONTROL;
	else if (stricmp(KeyName, "ALT") == 0 || stricmp(KeyName, "ALTERNATE") == 0)
		return VK_MENU;
	else if (stricmp(KeyName, "SHIFT") == 0 || stricmp(KeyName, "LSHIFT") == 0)
		return VK_LSHIFT;
	else if (stricmp(KeyName, "RSHIFT") == 0)
		return VK_RSHIFT;
	else if (stricmp(KeyName, "NUM0") == 0)
		return VK_NUMPAD0;
	else if (stricmp(KeyName, "NUM1") == 0)
		return VK_NUMPAD1;
	else if (stricmp(KeyName, "NUM2") == 0)
		return VK_NUMPAD2;
	else if (stricmp(KeyName, "NUM3") == 0)
		return VK_NUMPAD3;
	else if (stricmp(KeyName, "NUM4") == 0)
		return VK_NUMPAD4;
	else if (stricmp(KeyName, "NUM5") == 0)
		return VK_NUMPAD5;
	else if (stricmp(KeyName, "NUM6") == 0)
		return VK_NUMPAD6;
	else if (stricmp(KeyName, "NUM7") == 0)
		return VK_NUMPAD7;
	else if (stricmp(KeyName, "NUM8") == 0)
		return VK_NUMPAD8;
	else if (stricmp(KeyName, "NUM9") == 0)
		return VK_NUMPAD9;
	else if ('0' <= KeyName[0] && KeyName[0] <= '9' || 'A' <= KeyName[0] && KeyName[0] <= 'Z')
		return KeyName[0];
	else if ('a' <= KeyName[0] && KeyName[0] <= 'z')
		return KeyName[0] - 'a' + 'A';

	return 0;
}

const char * GetKeyNameByKeyCode(unsigned char KeyCode) {
	switch (KeyCode) {
		case VK_OEM_3:   return "~";
		case VK_SPACE:   return "Space";
		case VK_INSERT:  return "Insert";
		case VK_DELETE:  return "Delete";
		case VK_HOME:    return "Home";
		case VK_END:     return "End";
		case VK_PRIOR:   return "PgUp";
		case VK_NEXT:    return "PgDown";
		case VK_CONTROL: return "Ctrl";
		case VK_MENU:    return "Alt";
		case VK_LSHIFT:  return "Shift";
		case VK_NUMPAD9:  return "Num9";
		case VK_NUMPAD8:  return "Num8";
		case VK_NUMPAD7:  return "Num7";
		case VK_NUMPAD6:  return "Num6";
		case VK_NUMPAD5:  return "Num5";
		case VK_NUMPAD4:  return "Num4";
		case VK_NUMPAD3:  return "Num3";
		case VK_NUMPAD2:  return "Num2";
		case VK_NUMPAD1:  return "Num1";
		case VK_NUMPAD0:  return "Num0";
	}
	if ('0' <= KeyCode && KeyCode <= '9') return &("0\01\02\03\04\05\06\07\08\09\0"[(KeyCode - '0') * 2]);
	if ('A' <= KeyCode && KeyCode <= 'Z') return &("A\0B\0C\0D\0E\0F\0G\0H\0I\0J\0K\0L\0M\0N\0O\0P\0Q\0R\0S\0T\0U\0V\0W\0X\0Y\0Z\0"[(KeyCode - 'A') * 2]);
	return "Unknow";
}
