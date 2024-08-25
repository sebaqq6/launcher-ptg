//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfMapa : public TForm
{
__published:	// IDE-managed Components
	TIdHTTP *IdHTTP1;
	TTimer *Timer1;
	TImage *imgMap;
	TStatusBar *statusbar;
	TRadioGroup *RadioGroup1;
	TRadioButton *onlyPlayer;
	TRadioButton *showAllPlayers;
	TBevel *Bevel1;
	TCheckBox *autoRefMap;
	TButton *bRefresh;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall bRefreshClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfMapa(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMapa *fMapa;
//---------------------------------------------------------------------------
#endif
