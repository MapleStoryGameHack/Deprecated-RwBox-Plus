//---------------------------------------------------------------------------

#ifndef FunctionH
#define FunctionH
//---------------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h>
//---------------------------------------------------------------------------
void HookICS(unsigned int Pointer, void *Function);
DWORD GetFunctionAddress(_TCHAR *moduleName, char *functionName);
bool SendKey(HWND hWnd, WORD Key);
bool PressKey(HWND hWnd, WORD Key);
void MEMwrite(PVOID address, void* val, int bytes);
void AsmJump(const DWORD ulAddress, LPCVOID Function, unsigned Nops);
void AsmCall(const DWORD ulAddress, LPCVOID Function, unsigned Nops);
void Write4Byte(long adr,int value);
void WriteByte(long adr,unsigned char value);
unsigned long ReadPointer( unsigned long ulBase, int iOffset );
unsigned long GetPointedAddress(unsigned long ulBase, int iOffset);
bool WritePointer(unsigned long ulBase, int iOffset, int iValue);
const char * GetKeyNameByKeyCode(unsigned char KeyCode);
unsigned char GetVirtualKeyCodeByName(char * KeyName);
//---------------------------------------------------------------------------
#endif
