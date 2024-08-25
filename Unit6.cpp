//---------------------------------------------------------------------------

#include <vcl.h>
#include <inifiles.hpp>
#include <bass.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TfSettings *fSettings;
extern void InitBass();
extern void UpdateRadioVolume();
extern HSTREAM radio;
extern bool bass_exist;
//---------------------------------------------------------------------------
__fastcall TfSettings::TfSettings(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::rAutoNoneClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    if(rAutoNone->Checked)
    {
    	config->WriteInteger("USTAWIENIA", "AutoStart", 0);
    }
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::rAutoGtaClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    if(rAutoGta->Checked)
    {
    	config->WriteInteger("USTAWIENIA", "AutoStart", 1);
    }
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::rAutoWWWClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    if(rAutoWWW->Checked)
    {
    	config->WriteInteger("USTAWIENIA", "AutoStart", 2);
    }
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::rAutoTSClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    if(rAutoTS->Checked)
    {
    	config->WriteInteger("USTAWIENIA", "AutoStart", 3);
    }
    delete config;
}

void __fastcall TfSettings::rAutoWWWTSClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    if(rAutoWWWTS->Checked)
    {
    	config->WriteInteger("USTAWIENIA", "AutoStart", 4);
    }
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::checkAutoRefClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
	if(checkAutoRef->Checked)
    {
    	cRefEdit->Enabled = true;
        Label1->Enabled = true;
        Form1->checkRefChat->Checked = true;
        config->WriteBool("USTAWIENIA", "ChatRefresh", true);
    }
    else
    {
    	cRefEdit->Enabled = false;
        Label1->Enabled = false;
        Form1->checkRefChat->Checked = false;
        config->WriteBool("USTAWIENIA", "ChatRefresh", false);
    }
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::cRefEditChange(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    config->WriteInteger("USTAWIENIA", "ChatInterval", cRefEdit->Value);
    Form1->RefreshChat->Interval = (fSettings->cRefEdit->Value)*1000;
    delete config;
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::cRefChangelogClick(TObject *Sender)
{
	TIniFile *config = new TIniFile("ptg\\config.ini");
    config->WriteBool("USTAWIENIA", "DisableRefChangelog", cRefChangelog->Checked);
    delete config;
}
//---------------------------------------------------------------------------
void __fastcall TfSettings::rPTGStatusClick(TObject *Sender)
{
		if(!bass_exist) return;
		InitBass();
        TIniFile *config = new TIniFile("ptg\\config.ini");
        config->WriteBool("USTAWIENIA", "RadioPTG", rPTGStatus->Checked);
    	delete config;
        if(rPTGStatus->Checked)
        {
            BASS_ChannelStop(radio);
            radio = BASS_StreamCreateURL("http://radio.ptgrp.pl:8000/", 0, 0, NULL, 0);
            UpdateRadioVolume();
            BASS_ChannelPlay(radio, false);
        }
        else
        {
                BASS_ChannelStop(radio);
        }
}
//---------------------------------------------------------------------------

void __fastcall TfSettings::rVolumeChange(TObject *Sender)
{
	if(!bass_exist) return;
	InitBass();
	UpdateRadioVolume();
    TIniFile *config = new TIniFile("ptg\\config.ini");
    config->WriteInteger("USTAWIENIA", "RadioPTGVolume", fSettings->rVolume->Position);
   	delete config;
}
//---------------------------------------------------------------------------


void __fastcall TfSettings::Timer1Timer(TObject *Sender)
{
    String nuta = BASS_ChannelGetTags(radio, BASS_TAG_META);
    nuta.Delete(1, 13);
    String temp = "';StreamUrl='";
    int x = nuta.AnsiPos(temp);
    nuta.Delete(x, nuta.Length());
    Memo1->Lines->Add(nuta);
}
//---------------------------------------------------------------------------



