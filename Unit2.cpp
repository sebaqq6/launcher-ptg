//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include "qq/qqutils.h"
#include <inifiles.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfLogin *fLogin;
extern String klucz;
extern void OnLogIn();
extern bool zalogowany;
extern unsigned app_wersja_code;
unsigned long __stdcall watek_login(void *args);
void UruchomWatekLogin()
{
   CreateThread(NULL,0,&watek_login,NULL,0,NULL);
}
bool wykonaj_watek_connect_check = false;
bool wykonaj_watek_weryfikacja = false;
//---------------------------------------------------------------------------
__fastcall TfLogin::TfLogin(TComponent* Owner)
: TForm(Owner)
{
    if(wykonaj_watek_connect_check) return;
    wykonaj_watek_connect_check = true;
    UruchomWatekLogin();
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::bZalogujClick(TObject *Sender)
{
    if(wykonaj_watek_weryfikacja) return;
    wykonaj_watek_weryfikacja = true;
    UruchomWatekLogin();  
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::eHasloKeyPress(TObject *Sender, char &Key)
{
	if(Key == VK_RETURN)
    {
    	bZalogujClick(Sender);
        Key = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfLogin::eLoginKeyPress(TObject *Sender, char &Key)
{
	if(Key == VK_RETURN)
    {
    	bZalogujClick(Sender);
        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(!zalogowany)
    {
    	Application->Terminate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::eLoginClick(TObject *Sender)
{
	if(!(eLogin->Tag))
    {
    	eLogin->Tag = 1;
    	eLogin->Clear();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::eHasloClick(TObject *Sender)
{
	if(!(eHaslo->Tag))
    {
    	eHaslo->Tag = 1;
    	eHaslo->Clear();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::eHasloEnter(TObject *Sender)
{
  if(!(eHaslo->Tag))
  {
   eHaslo->Tag = 1;
   eHaslo->Clear();
}
}
//---------------------------------------------------------------------------

void __fastcall TfLogin::Image1Click(TObject *Sender)
{
	ShellExecute(Handle, NULL , "http://forum.ptgrp.pl/member.php?action=register", "http://forum.ptgrp.pl/member.php?action=register", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
unsigned long __stdcall watek_login(void *args)
{
    try
    {
        if(wykonaj_watek_connect_check)
        {
            wykonaj_watek_connect_check = false;
            fLogin->eLogin->Enabled = false;
            fLogin->eHaslo->Enabled = false;
            fLogin->sStatus->SimpleText = "Trwa testowanie polaczenia...";
            String status;
            if(!DirectoryExists("ptg"))
            {
                CreateDirectory("ptg", NULL);
            }
            try
            {
                status = HttpPost(fLogin->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", "");
                if(status == "ERR_1")
                {
                    fLogin->sStatus->SimpleText = "Polaczenie z serwerem jest OK! Możesz się zalogować.";
                    TIniFile *config = new TIniFile("ptg\\config.ini");
                    klucz = config->ReadString("HEAD", "Klucz", "brak");
                    klucz = decode_b64(klucz);
                    delete config;
                    char freq[512];
                    fLogin->sStatus->SimpleText = "Trwa sprawdzanie danych do autologowania...";
                    sprintf(freq, "app=test&ssid=%s", klucz.c_str());
                    status = HttpPost(fLogin->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", freq);
                    if(status != "ERR_10" && status != "ERR_11" && status != "ERR_12")
                    {
                        fLogin->sStatus->SimpleText = "Trwa autologowanie...";
                        Form1->OnLogIn(NULL);
                        fLogin->Close();
                    }
                    fLogin->sStatus->SimpleText = "Zaloguj się.";
                    fLogin->eLogin->Enabled = true;
                    fLogin->eHaslo->Enabled = true;
                }
                else
                {
                    fLogin->sStatus->SimpleText = "Polaczenie z serwerem nie powiodlo sie!";
                    fLogin->eLogin->Enabled = true;
                    fLogin->eHaslo->Enabled = true;
                }
            }
            catch(...)
            {
                fLogin->sStatus->SimpleText = "Polaczenie z serwerem nie powiodlo sie!";
            	fLogin->eLogin->Enabled = true;
                fLogin->eHaslo->Enabled = true;
            }
        }
        if(wykonaj_watek_weryfikacja)
        {
            wykonaj_watek_weryfikacja = false;
            fLogin->eLogin->Enabled = false;
            fLogin->eHaslo->Enabled = false;
            String haslo, login, status;
            login = fLogin->eLogin->Text;
            haslo = "ptg2016"+fLogin->eHaslo->Text;
            if(login.Length() == 0)
            {
                fLogin->sStatus->SimpleText = "Wprowadź login!";
            }
            else
            {
                haslo = encode_b64(haslo);
                char freq[512];
                sprintf(freq, "app=login&user=%s&pass=%s&app_ver=%d", login.c_str(), haslo.c_str(), app_wersja_code);
                //sprintf(freq, "app=login&user=%s&pass=%s", login.c_str(), haslo.c_str());
                try
                {
                    fLogin->sStatus->SimpleText = "Trwa weryfikacja...";
                    status = HttpPost(fLogin->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", freq);
                }
                catch(...)
                {
                    fLogin->sStatus->SimpleText = "Polaczenie z serwerem nie powiodlo sie!";
                    return 20;
                }
                if(status == "ERR_27")
                {
                	fLogin->sStatus->SimpleText = "Zaktualizuj launcher - forum.ptgrp.pl";
                }
                else if(status == "ERR_8" || status == "ERR_9")
                {
                    fLogin->sStatus->SimpleText = "Login lub hasło jest niepoprawne!";
                    fLogin->eHaslo->Clear();
                    fLogin->eLogin->Clear();
                    fLogin->eLogin->Enabled = true;
                    fLogin->eHaslo->Enabled = true;
                }
                else
                {
                    klucz = status;
                    Form1->OnLogIn(NULL);
                    fLogin->Close();
                }
            }
        }
    }
    catch(...){}

    return 1;
}