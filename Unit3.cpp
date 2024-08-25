//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include "qq/qqutils.h"
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfChangePass *fChangePass;
extern String klucz;
//---------------------------------------------------------------------------
__fastcall TfChangePass::TfChangePass(TComponent* Owner)
	: TForm(Owner)
{
	statusbar->SimpleText = "Wprowadź nowe hasło.";
}
//---------------------------------------------------------------------------
void __fastcall TfChangePass::backbutClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------


void __fastcall TfChangePass::pass1Enter(TObject *Sender)
{
	if(!(pass1->Tag))
    {
    	pass1->Tag = 1;
    	pass1->Clear();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfChangePass::pass2Enter(TObject *Sender)
{
	if(!(pass2->Tag))
    {
    	pass2->Tag = 1;
    	pass2->Clear();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfChangePass::changebutClick(TObject *Sender)
{
	String h1 = pass1->Text;
    String h2 = pass2->Text;
    if(h1.Length() < 4)
    {
    	statusbar->SimpleText = "Hasło jest za krótkie!";
        pass1->Clear();
        pass2->Clear();
        pass1->SetFocus();
    	return;
    }
    if(h1 != h2)
    {
    	statusbar->SimpleText = "Hasła nie są takie same!";
        pass1->Clear();
        pass2->Clear();
        pass1->SetFocus();
        return;
    }
    String status = '0';
    char req[512];
    sprintf(req, "app=change_password&ssid=%s&pass=%s", klucz.c_str(), h1.c_str());
    try
    {
    	statusbar->SimpleText = "Trwa wysyłanie rządania o zmianę hasła...";
    	status = HttpPost(IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
        if(status == "OK")
        {
        	statusbar->SimpleText = "Hasło zostało zmienione!";
            pass1->Clear();
        	pass2->Clear();
            pass1->SetFocus();
        }
        else if(status == "ERR_24")
        {
        	statusbar->SimpleText = "Podane hasło nie jest inne od aktualnego.";
            pass1->Clear();
        	pass2->Clear();
            pass1->SetFocus();
        }
        else
        {
			sprintf(req, "Wystąpił błąd serwera. Błąd: %s", status.c_str());
        	statusbar->SimpleText = (String) req;
            pass1->SetFocus();
        }
    }
    catch(...)
    {
    	statusbar->SimpleText = "Wystąpił błąd serwera! Spróbuj później.";
        pass1->SetFocus();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfChangePass::pass2KeyPress(TObject *Sender, char &Key)
{
	if(Key == VK_RETURN)
    {
    	changebutClick(Sender);
        Key = 0;
    }
}
//---------------------------------------------------------------------------

