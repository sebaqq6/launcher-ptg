//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <jpeg.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfMapa *fMapa;
extern signed uID;
//---------------------------------------------------------------------------
__fastcall TfMapa::TfMapa(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfMapa::FormActivate(TObject *Sender)
{
	char req[128];
    statusbar->SimpleText = "Trwa odświeżanie mapy... Proszę czekać...";
    bRefresh->Enabled = false;
    Timer1->Enabled = false;
    bRefresh->Caption = "Odświeżanie...";
    if(onlyPlayer->Checked)
    {
    	sprintf(req, "http://panel.ptgrp.pl/panel/map_app.php?id=%d", uID);
    }
    else
    {
    	sprintf(req, "http://panel.ptgrp.pl/panel/map_app.php");
    }
    try
    {
    	TFileStream *mapfile = new TFileStream("ptg\\map.jpg", fmCreate);
    	TJPEGImage *jpeg = new TJPEGImage;
    	IdHTTP1->Get(req, mapfile);
    	delete mapfile;
    	jpeg->LoadFromFile("ptg\\map.jpg");
    	imgMap->Picture->Assign(jpeg);
        delete jpeg;
    	statusbar->SimpleText = "Mapa została załadowana!";
    }
    catch(...)
    {
    	statusbar->SimpleText = "Wystąpił błąd podczas ładowania mapy :(";
    }
    bRefresh->Enabled = true;
    bRefresh->Caption = "Odśwież!";
    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfMapa::Timer1Timer(TObject *Sender)
{
	if(autoRefMap->Checked) FormActivate(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfMapa::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfMapa::bRefreshClick(TObject *Sender)
{
	if(Timer1->Enabled)
    {
    	Timer1->Enabled = false;
        Timer1->Enabled = true;
    }
    FormActivate(Sender);
}
//---------------------------------------------------------------------------
