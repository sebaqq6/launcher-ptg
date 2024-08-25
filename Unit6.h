//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TfSettings : public TForm
{
__published:	// IDE-managed Components
	TRadioGroup *RadioGroup1;
	TRadioButton *rAutoNone;
	TRadioButton *rAutoGta;
	TRadioButton *rAutoWWW;
	TRadioButton *rAutoTS;
	TGroupBox *GroupBox1;
	TCheckBox *checkAutoRef;
	TCSpinEdit *cRefEdit;
	TLabel *Label1;
	TRadioButton *rAutoWWWTS;
	TGroupBox *GroupBox2;
	TCheckBox *cRefChangelog;
	TGroupBox *GroupBox3;
	TCheckBox *rPTGStatus;
	TTrackBar *rVolume;
	TLabel *Label2;
        TTimer *Timer1;
        TMemo *Memo1;
	void __fastcall rAutoNoneClick(TObject *Sender);
	void __fastcall rAutoGtaClick(TObject *Sender);
	void __fastcall rAutoWWWClick(TObject *Sender);
	void __fastcall rAutoTSClick(TObject *Sender);
	void __fastcall checkAutoRefClick(TObject *Sender);
	void __fastcall cRefEditChange(TObject *Sender);
	void __fastcall cRefChangelogClick(TObject *Sender);
	void __fastcall rPTGStatusClick(TObject *Sender);
	void __fastcall rVolumeChange(TObject *Sender);
	void __fastcall rAutoWWWTSClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfSettings *fSettings;
//---------------------------------------------------------------------------
#endif
