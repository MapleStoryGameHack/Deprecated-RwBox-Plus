//---------------------------------------------------------------------------

#ifndef ThreadBotH
#define ThreadBotH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ThreadBot : public TThread
{
private:
	void __fastcall AutoGuagi();
	void __fastcall RunAutoSkill();
	void __fastcall RunAttack();
	void __fastcall RunPick();
    long TimeTicket;
protected:
	void __fastcall Execute();

public:
	__fastcall ThreadBot(bool CreateSuspended);

};
//---------------------------------------------------------------------------
#endif
