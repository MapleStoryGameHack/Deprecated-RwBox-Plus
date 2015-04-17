//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FormTaxi.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TfrmTaxi *frmTaxi;
//---------------------------------------------------------------------------
__fastcall TfrmTaxi::TfrmTaxi(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
long EnumProc(char *Name , char* Street, long MapId, void *Param)
{
	frmTaxi->plist->Items->Add( String(Street) + "-" + String(Name)) ;
	return 1;
}
//---------------------------------------------------------------------------
long TaxiEnumProc(int s, long current , long target)
{
	POINT p;
	switch (s) {
	case -1:
		frmTaxi->btn_go->Enabled = true;
		frmTaxi->Close();
		break;
	case 0:
		frmTaxi->btn_go->Enabled = false;
		break;
	case 1:
		GetTeleportPoint( current , target, p);
		frmTaxi->btn_go->Enabled = false;
		Sleep(200);
    default:
        ;
	}
	return 1;
}

//---------------------------------------------------------------------------
void __fastcall TfrmTaxi::btn_goClick(TObject *Sender)
{
	if (plist->ItemIndex != -1)
	{
		AnsiString l = plist->Selected->Text;
		AnsiString st = l.SubString(0,l.Pos('-')-1);
		AnsiString n = l.SubString(l.Pos('-')+1,l.Length()- l.Pos('-'));
		long eid = GetMapId(n.c_str(),st.c_str());
		if ( eid != -1 ) {
			ThreadTaxi = new TThreadTaxi(false, ReadPointer(MapBase,MapIDOffset) ,eid  ,TaxiEnumProc);
		}
		else
		{
			MessageBoxA(0,"找不到地圖 ","計程車",MB_ICONERROR);
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TfrmTaxi::FormCreate(TObject *Sender)
{
	plist->Clear();
	try
	{
		EnumPossibleMap( ReadPointer(MapBase,MapIDOffset), EnumProc, NULL);
	}
	catch(...)
	{
		MessageBox(0, "列出可能地圖出錯！", "錯誤", MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------

