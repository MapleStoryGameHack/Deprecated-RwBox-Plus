//---------------------------------------------------------------------------

#ifndef FormTaxiH
#define FormTaxiH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include "Pointer.h"
#include "MapList.h"
#include "MapLink.h"
#include "Function.h"
#include "ThreadTaxi.h"
//---------------------------------------------------------------------------
class TfrmTaxi : public TForm
{
__published:	// IDE-managed Components
	TStyleBook *style;
	TComboBox *plist;
	TLabel *Label1;
	TButton *btn_go;
	void __fastcall btn_goClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmTaxi(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmTaxi *frmTaxi;
//---------------------------------------------------------------------------
#endif
