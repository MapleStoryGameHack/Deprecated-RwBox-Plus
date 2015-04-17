//---------------------------------------------------------------------------

#pragma hdrstop

#include "Keys.h"
//---------------------------------------------------------------------------

TStrings * Keys;

void InitializeKeys()
{
	Keys  =  new TStringList;
	Keys->Add("`");
	Keys->Add("Delete");
	Keys->Add("LSHIFT");
	Keys->Add("RSHIFT");
	Keys->Add("CTRL");
	Keys->Add("PGDOWN");
	Keys->Add("PGUP");
	Keys->Add("HOME");
	Keys->Add("END");
	Keys->Add("INS");
	Keys->Add("SPACE");

	Keys->Add("NUM1");
	Keys->Add("NUM2");
	Keys->Add("NUM3");
	Keys->Add("NUM4");
	Keys->Add("NUM5");
	Keys->Add("NUM6");
	Keys->Add("NUM7");
	Keys->Add("NUM8");
	Keys->Add("NUM9");
	Keys->Add("NUM0");

	Keys->Add("1");
	Keys->Add("2");
	Keys->Add("3");
	Keys->Add("4");
	Keys->Add("5");
	Keys->Add("6");
	Keys->Add("7");
	Keys->Add("8");
	Keys->Add("9");
	Keys->Add("0");

	Keys->Add("A");
	Keys->Add("B");
	Keys->Add("C");
	Keys->Add("D");
	Keys->Add("E");
	Keys->Add("F");
	Keys->Add("G");
	Keys->Add("H");
	Keys->Add("I");
	Keys->Add("J");
	Keys->Add("K");
	Keys->Add("L");
	Keys->Add("M");
	Keys->Add("N");
	Keys->Add("O");
	Keys->Add("P");
	Keys->Add("Q");
	Keys->Add("R");
	Keys->Add("S");
	Keys->Add("T");
	Keys->Add("U");
	Keys->Add("V");
	Keys->Add("W");
	Keys->Add("X");
	Keys->Add("Y");
	Keys->Add("Z");
}

#pragma package(smart_init)
