//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TfLogin : public TForm
{
__published:	// IDE-managed Components
	TEdit *eLogin;
	TEdit *eHaslo;
	TStatusBar *sStatus;
	TIdHTTP *IdHTTP1;
	TImage *bZaloguj;
	TImage *tlo;
	TImage *Image1;
	void __fastcall bZalogujClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall eLoginClick(TObject *Sender);
	void __fastcall eHasloClick(TObject *Sender);
	void __fastcall eHasloEnter(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall eHasloKeyPress(TObject *Sender, char &Key);
	void __fastcall eLoginKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfLogin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfLogin *fLogin;
//---------------------------------------------------------------------------
#endif
