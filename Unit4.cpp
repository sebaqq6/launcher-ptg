//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
                            
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
extern String app_wersja;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image2Click(TObject *Sender)
{
	ShellExecute(Form4->Handle, NULL , "http://sebaqq6.pl", "http://sebaqq6.pl", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image3Click(TObject *Sender)
{
	ShellExecute(Form4->Handle, NULL , "http://forum.ptgrp.pl/member.php?action=profile&uid=261", "http://forum.ptgrp.pl/member.php?action=profile&uid=261", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image4Click(TObject *Sender)
{
	ShellExecute(Form4->Handle, NULL , "http://forum.ptgrp.pl/member.php?action=profile&uid=47", "http://forum.ptgrp.pl/member.php?action=profile&uid=47", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image5Click(TObject *Sender)
{
	ShellExecute(Form4->Handle, NULL , "http://redtm.pl", "http://redtm.pl", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormActivate(TObject *Sender)
{
	Caption = app_wersja; 
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Label1Click(TObject *Sender)
{
        ShellExecute(Form4->Handle, NULL , "http://github.com/Hual/SA-MP-Plus", "http://github.com/Hual/SA-MP-Plus", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

