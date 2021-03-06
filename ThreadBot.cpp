//---------------------------------------------------------------------------


#pragma hdrstop
#include "Variable.h"
#include "ThreadBot.h"
#include "Function.h"
#include "Pointer.h"
#include <queue>
#include <vector>
#include "AutoGuagi.h"
#include "Script.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ThreadBot::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ThreadBot::ThreadBot(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ThreadBot::RunAutoSkill()
{
	for(int i = 0; i < 4; i++)
	{
		if( AutoKey_Skill_Ticket[i] < GetTickCount() +100 && AutoKey_Skill_OnOff[i] == 1 && Taxi_OnOff == false)
		{
			WritePointer(PeopleBase, PeopleSkillAct, -1);
			Sleep(500);
			SendKey(hWndMS,AutoKey_Skill_Key[i]);
			AutoKey_Skill_Ticket[i] = GetTickCount() + AutoKey_Skill_Time[i]*1000;
			Sleep(100);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall ThreadBot::RunAttack()
{
	if ( AutoKey_Att_Ticket < GetTickCount() + 10 && AutoKey_Att_OnOff == 1 && Taxi_OnOff == false && !( AutoGuagi_OnOff && ( AutoLR_Step == 0 || AutoLR_Step <= 2)   ) )
	{
		SendKey(hWndMS,AutoKey_Att_Key);
		AutoKey_Att_Ticket = GetTickCount() + AutoKey_Att_Time;
		Sleep(200);
	}
}
//---------------------------------------------------------------------------
void __fastcall ThreadBot::RunPick()
{
	if ( AutoKey_Pick_Ticket < GetTickCount() + 10 && AutoKey_Pick_OnOff == 1 && Taxi_OnOff == false && !(AutoKey_Pick_OnOff ==1 && AutoLR_Step > 3 ))
	{
		WritePointer(SystemBase, SuperPickOffset, 0);
		WritePointer(SystemBase, SuperPickOffset2, 0);
		SendKey(hWndMS,AutoKey_Pick_Key);
		AutoKey_Pick_Ticket = GetTickCount() + AutoKey_Pick_Time;
		Sleep(200);
	}
}
//---------------------------------------------------------------------------
void __fastcall ThreadBot::Execute()
{
	while( !CloseGame )
	{

		if( *(DWORD*)PeopleBase > 0)
		{

			if( AutoKey_HP_OnOff == 1 && HP_Max > 0 )
			{
			   if( HP_Now < AutoKey_HP_Value )
			   {
				   WritePointer(SystemBase, SuperPickOffset, 0);
				   WritePointer(SystemBase, SuperPickOffset2, 0);
				   PressKey(hWndMS,VK_HOME);
				   Sleep(10);
			   }

			}
			if( AutoKey_MP_OnOff == 1 && MP_Max > 0 )
			{
			   if( MP_Now < AutoKey_MP_Value )
			   {
				   WritePointer(SystemBase, SuperPickOffset, 0);
					WritePointer(SystemBase, SuperPickOffset2, 0);
				   PressKey(hWndMS,VK_END);
				   Sleep(10);
			   }
			}
			RunAutoSkill();
			RunAttack();
			RunPick();
			AutoGuagiProcdure();
        }
    }
}
//---------------------------------------------------------------------------
