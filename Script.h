//---------------------------------------------------------------------------

#ifndef ScriptH
#define ScriptH
#include <windows.h>

#define ONOFF int

#define FPHook(adr, func) (*(void**)adr = (void*)func) ;
#define R(adr) (*(long*)(adr)) // Watch out the size of long
#define P(adr, off) ( R( (R(adr) + off) ) )

#define SCRIPT_INCLUDE(SCRIPT) void __declspec(naked) SCRIPT () ;
#define SCRIPT_START(SCRIPT)   void __declspec(naked) SCRIPT () { __asm {
#define SCRIPT_END             }}
#define ACALL(ADDRESS)         mov  [esp-0x08], ADDRESS; call [esp-0x08]
#define AJUMP(ADDRESS)         push ADDRESS; ret
#define AMOVESP(ESP,ADDRESS)   mov [esp-0x8],eax;mov eax,ADDRESS;mov [esp+ESP],eax;mov eax,[esp-0x8]

//---------------------------------------------------------------------------

extern GodMode_OnOff;
extern SCRIPT_INCLUDE(GodMode_Entry)
extern SCRIPT_INCLUDE(GodMode_Main)

extern CSX_OnOff;
extern SCRIPT_INCLUDE(CSX_Entry)

extern SuperDiagua_OnOff;
extern SCRIPT_INCLUDE(SuperDiagua_Entry)

extern SuperMobStupid_OnOff;
extern SCRIPT_INCLUDE(SuperMobStupide_Entry)
extern SCRIPT_INCLUDE(SuperMobStupid_Main)

extern FullMap_OnOff;
extern SCRIPT_INCLUDE(FullMap_Entry)
extern SCRIPT_INCLUDE(FullMap_Main)
extern SCRIPT_INCLUDE(FullMap_Bypass)

extern ItemVac_OnOff;
extern SCRIPT_INCLUDE(ItemVac_Entry)
extern SCRIPT_INCLUDE(ItemVac_Main)

extern FaceLR_OnOff;
extern FaceLR_Value;
extern SCRIPT_INCLUDE(FaceLR_Entry)
extern SCRIPT_INCLUDE(FaceLR_Main)


extern UltimateJmp_OnOff;
extern SCRIPT_INCLUDE(UltimateJmp_Entry)


extern NoSkillAni_OnOff;
extern SCRIPT_INCLUDE(NoSkillAni_Entry)

extern WalkSpeedUp_OnOff;
extern SCRIPT_INCLUDE(WalkSpeedUp_Entry)

extern SCRIPT_INCLUDE(ItemFilter_Main)
extern SCRIPT_INCLUDE(ItemFilter_Entry)

extern AutoLR_Value;
extern AutoLR_Range;
extern AutoLR_Step;
extern AutoLR_Position;
extern AutoLR_OnOff;
extern SCRIPT_INCLUDE(AutoLR_Main)
extern SCRIPT_INCLUDE(AutoLR_Entry)

extern CSMobVac_OnOff;

extern NoBkImg_OnOff;

extern SCRIPT_INCLUDE(GetInfo_Entry)

extern void __stdcall InstallScript();

#endif
