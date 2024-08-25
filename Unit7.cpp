//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformDDraw *formDDraw;
bool ddraw_status = 0;
//---------------------------------------------------------------------------
__fastcall TformDDraw::TformDDraw(TComponent* Owner)
        : TForm(Owner)
{
        lpDD = NULL;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TformDDraw::DDraw(void)
{
 DirectDrawCreate(NULL, &lpDD, NULL);

 lpDD->SetCooperativeLevel(Handle, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
 lpDD->SetDisplayMode(1024, 768, 16);

 DDSURFACEDESC ddsd;
 ZeroMemory(&ddsd, sizeof(ddsd));
 ddsd.dwSize = sizeof(ddsd);
 ddsd.dwFlags = DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
 ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE|DDSCAPS_FLIP|DDSCAPS_COMPLEX;
 ddsd.dwBackBufferCount = 1;

 lpDD->CreateSurface(&ddsd, &lpDDSEkran, NULL);

 ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
 lpDDSEkran->GetAttachedSurface(&ddsd.ddsCaps, &lpDDSBuffer);

 hdcmem = CreateCompatibleDC(NULL);
 hbmp = (HBITMAP)LoadImage(Handle, "logo.bmp", IMAGE_BITMAP, 1024, 768, LR_LOADFROMFILE);
 SelectObject(hdcmem, hbmp);

 lpDDSBuffer->GetDC(&kontekst);
 BitBlt(kontekst, 0, 0, 1024, 768, hdcmem, 0, 0, SRCCOPY);

 lpDDSBuffer->ReleaseDC(kontekst);
 lpDDSEkran->Flip(NULL, 0);

 DeleteObject(hbmp);
 DeleteDC(hdcmem);
 lpDDSBuffer->Release();
 ddraw_status = true;
}


void __fastcall TformDDraw::DDrawStop(void)
{
        if(ddraw_status)
        {
                ddraw_status = false;
                lpDDSEkran->Release();
                lpDD->RestoreDisplayMode();
                lpDD->Release();
        }
}

void __fastcall TformDDraw::Button1Click(TObject *Sender)
{
        DDraw();
}
//---------------------------------------------------------------------------
void __fastcall TformDDraw::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        DDrawStop();
}
//---------------------------------------------------------------------------
void __fastcall TformDDraw::FormDeactivate(TObject *Sender)
{
        DDrawStop();
        Close();        
}
//---------------------------------------------------------------------------
int counter_up = 0;
void Log(const char* szFormat, ...);
void __fastcall TformDDraw::Timer1Timer(TObject *Sender)
{
    counter_up++;
    HWND gra = FindWindow(0, "GTA:SA:MP");
    HWND ladowanie = FindWindow(0, "GTA: San Andreas");
    HWND seesamp = GetModuleHandleA("samp.dll");
    String log;
    if(seesamp != NULL)
    {
        log = IntToStr(counter_up)+" | samp.dll czuje, mmm...";
        Memo1->Lines->Add(log);
    }
    if(gra != NULL)
    {
        log = IntToStr(counter_up)+" | W grze...";
        Memo1->Lines->Add(log);
    }
    else if(ladowanie != NULL)
    {
        log = IntToStr(counter_up)+" | W trakcie ladowania...";
        Memo1->Lines->Add(log);
    }
    else
    {
        Memo1->Lines->Add("cisza");
    }
}
//---------------------------------------------------------------------------
