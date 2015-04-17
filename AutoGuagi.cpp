//---------------------------------------------------------------------------

#pragma hdrstop

#include "AutoGuagi.h"
#include "FormMain.h"
#include "Pointer.h"
#include "MapList.h"
#include "MapLink.h"
#include "Function.h"
#include "Variable.h"
#include "ThreadTaxi.h"
#include "Script.h"
#include <windows.h>


void TeleXY( bool s , int x, int y)
{
	WritePointer(PeopleBase,PeopleTeleX,x);
	WritePointer(PeopleBase,PeopleTeleY,y);
	WritePointer(PeopleBase,PeopleTeleSW,s);
}
int taxi_flag = 0;
//---------------------------------------------------------------------------
long TaxiEnumProc(int s, long current , long target)
{
	if( s == -2)
	{
     	taxi_flag = 1;
    }
	return 1;
}
//---------------------------------------------------------------------------
void AutoGuagiProcdure()
{
	long map = ReadPointer(MapBase,MapIDOffset);
	if( *(DWORD*)PeopleBase )
	{
		if( AutoGuagi_Start == 1)
		{

			AutoGuagi_OnOff = 1;
			AutoGuagi_Status = 0;
			AutoGuagi_Start= 0;
		}
		if ( AutoGuagi_OnOff != 0)
		{

			switch(AutoGuagi_Status)
			{
				case 0:	//檢查地圖
					taxi_flag = 0;
					Sleep(2000);
					frmMain->ck_att->IsChecked = false;
					frmMain->ck_func_godmode->IsChecked = true;
					GodMode_OnOff = true;
					if( map !=  AutoGuagi_MapId)
						AutoGuagi_Status = 1;
					else
						AutoGuagi_Status = 2;
					break;
				case 1: //地圖不同 -> 計程車
					ThreadTaxi = new TThreadTaxi(false, map ,AutoGuagi_MapId  ,TaxiEnumProc );
					ThreadTaxi->WaitFor();
					if( taxi_flag == -1 )
					{
						AutoGuagi_Status = -1;
						break;
                    }
					map = ReadPointer(MapBase,MapIDOffset);
					if( map  !=  AutoGuagi_MapId )
					   AutoGuagi_Status = -1;
					else
						AutoGuagi_Status = 2;
					break;
				case 2: //瞬間移動到指定位置
					Sleep(200);
					TeleXY( true , AutoGuagi_X , AutoGuagi_Y - 5 );
					Sleep(2000);
					AutoGuagi_Status = 3;
					break;
				case 3: //啟動左右走
					frmMain->ck_func_csx->IsChecked = true;
					frmMain->ck_func_autolr->IsChecked = true;
					AutoGuagi_Status = 4;
					Sleep(200);
					break;
				case 4: //啟動全圖打
					CSMobVac_OnOff = 1;
					FullMap_OnOff = 1;
					GodMode_OnOff = true;
					frmMain->ck_att->IsChecked = true;
					break;
				case -1:
					AutoGuagi_OnOff = 0;
					FullMap_OnOff = 0;
					CSMobVac_OnOff = 0;
					AutoGuagi_Status = -1;
					taxi_flag = 0;
					break;
				case -2:
					AutoGuagi_OnOff = 0;
					FullMap_OnOff = 0;
					CSMobVac_OnOff = 0;
					frmMain->ck_att->IsChecked = false;
					AutoGuagi_Status = -1;
					break;
			}

		}
		else
		{

			AutoGuagi_Status = 0;
		}
	}
}
//---------------------------------------------------------------------------



#pragma package(smart_init)
