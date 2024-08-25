//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "PERFGRAP.h"
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Graphics.hpp>
#include <IdIcmpClient.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
#include <filectrl.hpp>
#include <CustomizeDlg.hpp>
#include <MPlayer.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <NMUDP.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *downbar;
	TImage *skinimg;
	TTimer *RefreshChat;
	TImage *uruchomgre;
	TImage *enterforum;
	TImage *connectts;
	TEdit *chattext;
	TImage *sendChat;
	TImage *bcloseapp;
	TImage *bminimizeapp;
	TCheckBox *checkRefChat;
	TImage *tlo;
	TTimer *antySpamTimer;
	TImage *logout;
	TImage *chPassword;
	TLabel *InfoLabel;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *Label2;
	TBevel *Bevel4;
	TLabel *Label3;
	TCheckBox *checkEnterChat;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel5;
	TBevel *Bevel6;
	TBevel *Bevel7;
	TBevel *Bevel8;
	TBevel *Bevel9;
	TBevel *Bevel10;
	TButton *bShowMap;
	TProgressBar *hpBAR;
	TProgressBar *lvlBAR;
	TBevel *Bevel11;
	TProgressBar *glodBAR;
	TProgressBar *senBAR;
	TLabel *llNick;
	TLabel *llOrg;
	TLabel *llRasa;
	TLabel *llPlec;
	TBevel *Bevel12;
	TLabel *llHP;
	TBevel *Bevel13;
	TBevel *Bevel14;
	TBevel *Bevel15;
	TLabel *llPoziom;
	TLabel *llScore;
	TLabel *llKasa;
	TLabel *llTimeOnline;
	TLabel *llLastOnline;
	TLabel *llGlod;
	TLabel *llSen;
	TBevel *Bevel16;
	TLabel *llOnline;
	TTimer *RefAppTimer;
	TTimer *runSamp;
	TBevel *Bevel18;
	TBevel *Bevel17;
	TLabel *llPlayersCount;
	TLabel *llAdminsCount;
	TImage *bSettings;
        TCppWebBrowser *changelogBrowser;
        TCppWebBrowser *chatBrowser;
        TIdHTTP *IdHTTP1;
        TButton *Button1;
        TLabel *Label18;
	void __fastcall FormActivate(TObject *Sender);
    void __fastcall OnLogIn(TObject *Sender);
	void __fastcall uruchomgreClick(TObject *Sender);
	void __fastcall enterforumClick(TObject *Sender);
	void __fastcall connecttsClick(TObject *Sender);
	void __fastcall bcloseappClick(TObject *Sender);
	void __fastcall bminimizeappClick(TObject *Sender);
	void __fastcall tloMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall RefreshChatTimer(TObject *Sender);
	void __fastcall chattextEnter(TObject *Sender);
	void __fastcall sendChatClick(TObject *Sender);
	void __fastcall antySpamTimerTimer(TObject *Sender);
	void __fastcall logoutClick(TObject *Sender);
	void __fastcall chPasswordClick(TObject *Sender);
	void __fastcall InfoLabelClick(TObject *Sender);
	void __fastcall bShowMapClick(TObject *Sender);
    void __fastcall ShowStats();
	void __fastcall RefAppTimerTimer(TObject *Sender);
	void __fastcall Label2DblClick(TObject *Sender);
	void __fastcall runSampTimer(TObject *Sender);
	void __fastcall chattextKeyPress(TObject *Sender, char &Key);
	void __fastcall chatBrowserNavigateComplete2(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL);
    void __fastcall OnAppMinimize(TObject *Sender);
    void __fastcall OnAppRestore(TObject *Sender);
	void __fastcall bSettingsClick(TObject *Sender);
	void __fastcall checkRefChatClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	void __fastcall Przesun(TMouseButton Button);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    void __fastcall FindDir(String Dir);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
