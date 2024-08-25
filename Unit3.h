//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TfChangePass : public TForm
{
__published:	// IDE-managed Components
	TImage *tlochangepass;
	TStatusBar *statusbar;
	TEdit *pass1;
	TEdit *pass2;
	TImage *backbut;
	TImage *changebut;
	TIdHTTP *IdHTTP1;
	void __fastcall backbutClick(TObject *Sender);
	void __fastcall pass1Enter(TObject *Sender);
	void __fastcall pass2Enter(TObject *Sender);
	void __fastcall changebutClick(TObject *Sender);
	void __fastcall pass2KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TfChangePass(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfChangePass *fChangePass;
//---------------------------------------------------------------------------
#endif
