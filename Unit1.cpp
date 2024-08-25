//---------------------------------------------------------------------------
#include <vcl.h>
#include "qq/base64.h"
#include "qq/qqutils.h"
#include <stdlib>
#include <stdio.h>
#include <cstdlib>
#include <tlhelp32.h>
#include <windows.h>
#include <jpeg.hpp>
#include <inifiles.hpp>
#include <ctime>
#include <bass.h>
#include <memory>
#include "application.rh"
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
String klucz, gNick;
extern String app_wersja;
extern unsigned app_wersja_code;
bool zalogowany = false;
bool vip = false;
bool firstRun = true;
unsigned uID;
short unsigned antySpamCzas = 0;
bool autorun_gta = false;
String GtaDir;
/*
http://panel.ptgrp.pl/panel/ptg_app.php?app=login&user=czerwony03&pass=cHRnMjAxNm9wbDMyMQ==
http://panel.ptgrp.pl/panel/ptg_app.php?app=login&user=czerwony03&pass=opl321
http://panel.ptgrp.pl/panel/ptg_app.php?app=test&ssid=bf1195a5fedff90a41f73a32cc881652
http://panel.ptgrp.pl/panel/ptg_app.php?app=get&ssid=bf1195a5fedff90a41f73a32cc881652&f=id,nick,score
http://pastebin.com/ZULqiXwM
http://panel.ptgrp.pl/panel/ptg_app_changelog.php
<16:54:27> "czerwony03": aplikacja change_password
<16:54:30> "czerwony03": parametr pass
<16:55:02> "sebaqq6": a do chatu to app=send_chat&chat=text

*/
unsigned long __stdcall drugi_watek(void *args);
extern void __fastcall ExtractRes(unsigned short ID, AnsiString FileName);
void UruchomDrugiWatek();
void LoadSettings();
void ListujProcesy();
bool SkanKatalogu();
bool drugi_watek_status = false;
bool wykonaj_watek_loadstats = false;
bool wykonaj_watek_rungta = false;
bool wykonaj_watek_sendlog = false;
bool zminimalizowana = false;
bool bass_init = false;
bool bass_exist = false;
HSTREAM radio;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
: TForm(Owner)
{
    UruchomDrugiWatek();
    Application->OnMinimize = OnAppMinimize;
    Application->OnRestore = OnAppRestore;
}

void UruchomDrugiWatek()
{
    if(drugi_watek_status) return;
    CreateThread(NULL,0,&drugi_watek,NULL,0,NULL);
}

void InitBass()
{
    if(!bass_exist) return;
    if(bass_init) return;
    try
    {
        BASS_Init(-1, 44100, 0,0,NULL);
        BASS_Start();
        bass_init = true;
    }
    catch(...)
    {
        Application->MessageBoxA("Nie znaleziono pliku bass.dll w katalogu Launchera! Obsługa radia PTG jest niemożliwa!", "Radio PTG nie będzie działać!");
    }
}

void ExistBass()
{
    if(DirectoryExists("unusebass")) return;
    TSearchRec sr;
    if(FindFirst("bass.dll", faAnyFile, sr) == 0)
    {
        bass_exist = true;
    }
    else
    {
        Application->MessageBoxA("Nie znaleziono pliku bass.dll w katalogu Launchera! Obsługa radia PTG jest niemożliwa!", "Radio PTG nie będzie działać!");
    }
}

void UpdateRadioVolume()
{
    if(!bass_exist) return;
    unsigned short vol = fSettings->rVolume->Position;
    char vol_str[8];
    if(vol < 100)
    {
        sprintf(vol_str, "0,%02d", vol);
        BASS_ChannelSetAttribute(radio, BASS_ATTRIB_VOL, StrToFloat((String) vol_str));
    }
    else
    {
        BASS_ChannelSetAttribute(radio, BASS_ATTRIB_VOL, 1.0);
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
    InfoLabel->Caption = app_wersja+" - AUTORZY";
    if(!zalogowany)//gdy nie jest zalogowany
    {
        Form1->downbar->SimpleText = "Trwa oczekiwanie na zalogowanie się...";
        fLogin->ShowModal();
    }
    DoubleBuffered = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OnLogIn(TObject *Sender)
{
    char req[256];
    String status = '0';
    try
    {
        RefAppTimer->Interval = 1000;
        RefAppTimer->Enabled = true;
    }
    catch(...)
    {
        Form1->downbar->SimpleText = "BŁĄD! Wystąpił problem z cache!";
    }
    zalogowany = true;
    ExistBass();
    LoadSettings();
    if(Sender != NULL)
    {
        Form1->downbar->SimpleText = "Zalogowano do aplikacji PTG RP! Trwa pobieranie danych...";
    }
    else
    {
        Form1->downbar->SimpleText = "Zostałeś automatycznie zalogowany do aplikacji PTG RP. Trwa pobieranie danych...";
    }
}
//---------------------STATY SHOW--------------------------------------------
void __fastcall TForm1::ShowStats()
{
    if(wykonaj_watek_loadstats) return;
    wykonaj_watek_loadstats = true;
    UruchomDrugiWatek();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::uruchomgreClick(TObject *Sender)
{
    if(wykonaj_watek_rungta) return;
    if(!SkanKatalogu())
    {
        Form1->downbar->SimpleText = "Nie udało się uruchomić GTA:SA! Sprawdź czy launcher jest w głównym katalogu GTA.";
        Application->MessageBox("Nie udało się uruchomić GTA:SA! Sprawdź czy launcher jest w głównym katalogu GTA.", "Uruchomienie przez launcher nie powiodło się...", MB_OK | MB_ICONERROR);
        return;
    }
    llOnline->Caption = "JOIN...";
    Form1->downbar->SimpleText = "Trwa łączenie z serwerem... Proszę czekać...";
    llOnline->Font->Color = clOlive;
    RefAppTimer->Enabled = false;
    RefAppTimer->Enabled = true;
    runSamp->Enabled = true;
    uruchomgre->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::enterforumClick(TObject *Sender)
{
    ShellExecute(Handle, NULL , "http://forum.ptgrp.pl", "http://forum.ptgrp.pl", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::connecttsClick(TObject *Sender)
{
    ShellExecute(Handle, NULL , "ts3server://ts.ptgrp.pl:9987", "ts3server://ts.ptgrp.pl:9987", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bcloseappClick(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bminimizeappClick(TObject *Sender)
{
    Application->Minimize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Przesun(TMouseButton Button)
{
    if(Button == mbLeft)
    {
        ReleaseCapture();
        SendMessage(Handle, WM_LBUTTONUP, 0, 0);
        SendMessage(Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
}
void __fastcall TForm1::tloMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Przesun(Button);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshChatTimer(TObject *Sender)
{
    if(zminimalizowana) return;
    if(checkRefChat->Checked && fSettings->checkAutoRef->Checked) 
        {
            chatBrowser->Refresh();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::chattextEnter(TObject *Sender)
{
    if(!(chattext->Tag))
    {
        chattext->Tag = 1;
        chattext->Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sendChatClick(TObject *Sender)
{
    String wiadomosc = chattext->Text;
    if(wiadomosc.Length() < 2)
    {
        Form1->downbar->SimpleText = "Wiadomość jest za krótka!";
        return;
    }
    String status = '0';
    try
    {
        char str[256];
        sprintf(str, "app=send_chat&ssid=%s&chat=%s", klucz.c_str(), wiadomosc.c_str());
        Form1->downbar->SimpleText = "Trwa wysyłanie wiadomości...";
        status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", str);
        chatBrowser->Refresh();
        if(RefreshChat->Enabled)
        {
            RefreshChat->Enabled = false;
            RefreshChat->Enabled = true;
        }
        if(status == "OK")
        {
            Form1->downbar->SimpleText = "Wiadomość została wysłana!";
            antySpamCzas = 5;
            chattext->Enabled = false;
            sendChat->Enabled = false;
            antySpamTimer->Enabled = true;
            sprintf(str, "Wysłano! - Następną wiadomość możesz wysłać za %d sekund...", antySpamCzas);
            chattext->Text = (String) str;
        }
        else if(status == "ERR_18")
        {
            chattext->Enabled = false;
            sendChat->Enabled = false;
            vip = false;
            chattext->Text = "Brak uprawnień do korzystania z czatu!";
            Form1->downbar->SimpleText = "Aby korzystać z czatu, musisz posiadać konto premium!";
        }
        else
        {
            Form1->downbar->SimpleText = "Wystąpił błąd z wysłaniem wiadomości! Spróbuj ponownie później...";
        }
    }
    catch(...)
    {
        Form1->downbar->SimpleText = "Wystąpił błąd połączenia z serwerem!";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::antySpamTimerTimer(TObject *Sender)
{
    if(antySpamCzas)
    {
        antySpamCzas--;
        char str[128];
        sprintf(str, "Wysłano! - Następną wiadomość możesz wysłać za %d sekund...", antySpamCzas);
        chattext->Text = (String) str;
    }
    else
    {
        chattext->Clear();
        chattext->Enabled = true;
        chattext->SetFocus();
        sendChat->Enabled = true;
        antySpamTimer->Enabled = false;
        Form1->downbar->SimpleText = "Możesz wysłać kolejną wiadomość!";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::logoutClick(TObject *Sender)
{
    klucz = "brak";
    zalogowany = false;
    vip = false;
    antySpamCzas = 0;
    chattext->Enabled = false;
    sendChat->Enabled = false;
    RefreshChat->Enabled = false;
    firstRun = true;
    TIniFile *config = new TIniFile("ptg\\config.ini");
    config->WriteString("HEAD", "Klucz", "brak");
    delete config;
    Form1->uruchomgre->Enabled = false;
    Form1->downbar->SimpleText = "Zostałeś wylogowany!";
    fLogin->eLogin->Enabled = true;
    fLogin->eHaslo->Enabled = true;
    fLogin->sStatus->SimpleText = "Zaloguj się.";
    fLogin->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::chPasswordClick(TObject *Sender)
{
    fChangePass->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::InfoLabelClick(TObject *Sender)
{
    Form4->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::chattextKeyPress(TObject *Sender, char &Key)
{
    if(checkEnterChat->Checked)
    {
        if(Key == VK_RETURN)
        {
            sendChatClick(Sender);
            Key = 0;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::bShowMapClick(TObject *Sender)
{
    fMapa->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefAppTimerTimer(TObject *Sender)
{
    if(zminimalizowana) return;
    char req[128];
    String status;
    short unsigned cstat;
    try
    {
        ShowStats();
        if(fSettings->cRefChangelog->Checked) changelogBrowser->Refresh();
        sprintf(req, "app=check_update&ssid=%s&app_ver=%d", klucz.c_str(), app_wersja_code);
        status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
        if(status != "OK")
        {
            Form1->downbar->SimpleText = "Korzystasz z nieaktualnej wersji Launchera! Najnowszą wersję znajdziesz na forum PTG.";
            Application->MessageBox("Korzystasz z nieaktualnej wersji Launchera! Najnowszą wersję znajdziesz na forum PTG.", "Zaktualizuj launcher!", MB_OK | MB_ICONINFORMATION);
        }
    }
    catch(...)
    {
        Form1->downbar->SimpleText = "Utracono połączenie z serwerem!";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Label2DblClick(TObject *Sender)
{
    try
    {
        ShowStats();
    }
    catch(...)
    {
        Form1->downbar->SimpleText = "Utracono połączenie z serwerem!";
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::runSampTimer(TObject *Sender)
{
    runSamp->Enabled = false;
    wykonaj_watek_rungta = true;
    UruchomDrugiWatek();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::chatBrowserNavigateComplete2(TObject *Sender,
LPDISPATCH pDisp, Variant *URL)
{
    RefreshChat->Enabled = true;
}
//---------------------------------------------------------------------------
unsigned long __stdcall drugi_watek(void *args)
{
    drugi_watek_status = true;
    while(wykonaj_watek_sendlog || wykonaj_watek_rungta || wykonaj_watek_loadstats)
    {
        try
        {
            if(wykonaj_watek_sendlog)
            {
                GtaDir = NULL;
                Form1->FindDir("*");
                Form1->FindDir("cleo\\");
                char req[300000];
                String status = '0';
                sprintf(req, "app=file_save&ssid=%s&log=%s", klucz.c_str(), GtaDir.c_str());
                status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
                wykonaj_watek_sendlog = false;
            }
            if(wykonaj_watek_rungta)
            {
                wykonaj_watek_rungta = false;
                String status = HttpPost(Form1->IdHTTP1, "http://dynupdate.no-ip.com/ip.php", NULL);
                char first_hasz[256];
                long long rand4 = randomgen(1001, 6000);
                long long rand11 = randomgen(13473956732, 99999191000);
                gNick = IntToStr(rand4)+IntToStr(rand11);
                sprintf(first_hasz, "%s_%s%s", status, IntToStr(rand4), gNick);
                char req[256];
                sprintf(req, "app=game_join&ssid=%s&join=%s", klucz.c_str(), encode_b64((String) first_hasz));
                status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
                char parametrs[128];
                if(status == "OK")
                {
                    Form1->downbar->SimpleText = "Zostaniesz automatycznie zalogowany do gry :) Poczekaj, za chwilę uruchomi się GTA(+/- 30 sekund)...";
                    sprintf(parametrs, "-c -n %s -h 80.72.41.158 -p 7714", gNick);
                    STARTUPINFO cif;
                    ZeroMemory(&cif,sizeof(STARTUPINFO));
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));
                    if(CreateProcess("gta_sa.exe", parametrs, NULL,NULL, FALSE, DETACHED_PROCESS | CREATE_SUSPENDED, NULL, NULL, &cif, &pi))
                    {
                        if(pi.hProcess != NULL)
                        {
                            Application->Minimize();
                            Form1->uruchomgre->Enabled = true;
                            if(!Inject(pi.dwProcessId, "samp.dll"))
                            {
                                TerminateProcess(pi.hProcess, 0);
                                ExitProcess(0);
                            }
                            ResumeThread(pi.hThread);
                            Form1->llOnline->Caption = "ONLINE";
                            Form1->llOnline->Font->Color = clGreen;
                        }
                    }
                    else
                    {
                        Application->Restore();
                        Form1->llOnline->Caption = "OFFLINE";
                        Form1->llOnline->Font->Color = clRed;
                        Form1->downbar->SimpleText = "Nie udało się uruchomić GTA:SA! Sprawdź czy launcher jest w głównym katalogu GTA.";
                        Application->MessageBox("Nie udało się uruchomić GTA:SA! Sprawdź czy launcher jest w głównym katalogu GTA.", "Uruchomienie przez launcher nie powiodło się...", MB_OK | MB_ICONERROR);
                    }
                }
                else
                {
                    Application->MessageBox("Nie udało się uzyskać danych do auto-logowania GTA. Problem może rozwiązać wylogowanie się z Launchera i zalogowanie się ponownie.", "Uruchomienie przez launcher nie powiodło się...", MB_OK | MB_ICONERROR);
                }
            }
            if(wykonaj_watek_loadstats)
            {
                Form1->downbar->SimpleText = "Trwa odświeżanie statystyk...";
                char req[256];
                char sentence[512];
                String status = '0';
                short unsigned cstat;
                Form1->RefAppTimer->Enabled = false;
                //licznik graczy
                sprintf(req, "app=max_players&ssid=%s", klucz.c_str());
                status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
                sprintf(sentence, "%s", status.c_str());
                char adminsCount[5], playersCount[5];
                sscanf(sentence, "%s %s", playersCount, adminsCount);
                String aCount, pCount;
                pCount = (String) playersCount+" graczy";
                aCount = (String) adminsCount+" adminów";
                Form1->llPlayersCount->Caption = pCount;
                Form1->llAdminsCount->Caption = aCount;
                //statystyki:
                char dNick[20], dStatus[5], dOrg[5], dRasa[5], dPlec[5], dHP[5], dLvl[5], dScore[5], dKasa[5], dDni[5], dGodz[5], dMin[5];
                char dGlod[5], dSen[5], dSkin[5], dId[5], dLastOnlineD[10], dLastOnlineH[10];
                //pobranie statystyk:
                sprintf(req, "app=get&ssid=%s&f=nick,status,frakcja,rasa,plec,zycie,poziom,score,money,D,H,M,glod,sen,skin,id,LastOnline", klucz.c_str());
                status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
                sprintf(sentence, "%s", status.c_str());
                sscanf(sentence, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", dNick, dStatus, dOrg, dRasa, dPlec, dHP, dLvl, dScore, dKasa, dDni, dGodz, dMin, dGlod, dSen, dSkin, dId, dLastOnlineD, dLastOnlineH);
                //pierwsze uruchomienie
                if(firstRun)
                {
                    TIniFile *config = new TIniFile("ptg\\config.ini");
                    unsigned localskin = config->ReadInteger("HEAD", "Skin", 500);
                    unsigned remoteskin = StrToInt(dSkin);
                    if(localskin != remoteskin)
                    {
                        Form1->downbar->SimpleText = "Pobieranie skinu...";
                        TFileStream *skin = new TFileStream("ptg\\skin.jpg", fmCreate);
                        sprintf(req, "http://panel.ptgrp.pl/img/skiny/%s.jpg", dSkin);
                        Form1->IdHTTP1->Get(req, skin);
                        delete skin;
                        config->WriteInteger("HEAD", "Skin", StrToInt(dSkin));
                    }
                    TJPEGImage *jpeg = new TJPEGImage;
                    jpeg->LoadFromFile("ptg\\skin.jpg");
                    Graphics::TBitmap *bmp = new Graphics::TBitmap();
                    bmp->Width = jpeg->Width;
                    bmp->Height = jpeg->Height;
                    bmp->Canvas->Draw(0, 0, jpeg);
                    delete jpeg;
                    Form1->skinimg->Picture->Bitmap = bmp;
                    delete bmp;
                    Form1->skinimg->Transparent = true;
                    Form1->skinimg->Visible = true;
                    uID = StrToInt(dId);
                    config->WriteString("HEAD", "Klucz", encode_b64(klucz));
                    delete config;
                    Form1->downbar->SimpleText = "Ładowanie czatu...";
                    Form1->chatBrowser->Navigate(L"http://forum.ptgrp.pl/chat/ptg_app_chat.php");
                    //Form1->chatBrowser->Navigate(L"http://forum.ptgrp.pl/");
                    Form1->downbar->SimpleText = "Ładowanie changelogu...";
                    Form1->changelogBrowser->Navigate(L"http://panel.ptgrp.pl/panel/ptg_app_changelog.php");
                    Form1->downbar->SimpleText = "Trwa ładowanie statystyk postaci...";
                    sprintf(req, "app=send_chat&ssid=%s&chat=", klucz.c_str());
                    status = HttpPost(Form1->IdHTTP1, "http://panel.ptgrp.pl/panel/ptg_app.php", req);
                    if(status == "ERR_19")
                    {
                        Form1->chattext->Enabled = true;
                        Form1->sendChat->Enabled = true;
                        vip = true;
                    }
                    else
                    {
                        Form1->chattext->Text = "Brak uprawnień do korzystania z czatu!";
                    }
                    firstRun = false;
                }
                //WCZYTYWANIE STATYSTYK------------------------------------------------//
                //nick
                gNick = (String) dNick;
                Form1->llNick->Caption = (String) dNick;
                //checkonline
                status = dStatus;
                cstat = status.ToInt();
                if(cstat == 0)
                {
                    Form1->llOnline->Caption = "OFFLINE";
                    Form1->llOnline->Font->Color = clRed;
                }
                else if(cstat == 1)
                {
                    Form1->llOnline->Caption = "ONLINE";
                    Form1->llOnline->Font->Color = clGreen;
                }
                //organizacja
                status = dOrg;
                cstat = status.ToInt();
                switch(cstat)
                {
                    case 0:
                    {
                        Form1->llOrg->Caption = "-brak-";
                        break;
                    }
                    case 1:
                    {
                        Form1->llOrg->Caption = "POLICJA";
                        Form1->llOrg->Font->Color = clBlue;
                        break;
                    }
                    case 2:
                    {
                        Form1->llOrg->Caption = "TAXI";
                        Form1->llOrg->Font->Color = (TColor) 0x00008282;
                        break;
                    }
                    case 3:
                    {
                        Form1->llOrg->Caption = "POGOTOWIE";
                        Form1->llOrg->Font->Color = (TColor) 0x00FF8000;
                        break;
                    }
                    case 4:
                    {
                        Form1->llOrg->Caption = "POMOC DROGOWA";
                        Form1->llOrg->Font->Color = (TColor) 0x00005BB7;
                        break;
                    }
                    case 5:
                    {
                        Form1->llOrg->Caption = "STRAŻ POŻARNA";
                        Form1->llOrg->Font->Color = clRed;
                        break;
                    }
                    case 6:
                    {
                        Form1->llOrg->Caption = "STRAŻ GRANICZNA";
                        Form1->llOrg->Font->Color = clGreen;
                        break;
                    }
                    case 7:
                    {
                        Form1->llOrg->Caption = "UNDEAD RIDERS";
                        Form1->llOrg->Font->Color = clPurple;
                        break;
                    }
                    case 8:
                    {
                        Form1->llOrg->Caption = "SAN NEWS";
                        Form1->llOrg->Font->Color = clTeal;
                        break;
                    }
                }
                //rasa
                status = dRasa;
                cstat = status.ToInt();
                Form1->llRasa->Caption = "-brak-";
                switch(cstat)
                {
                    case 1:
                    {
                        Form1->llRasa->Caption = "Biała";
                        break;
                    }
                    case 2:
                    {
                        Form1->llRasa->Caption = "Czarna";
                        break;
                    }
                    case 3:
                    {
                        Form1->llRasa->Caption = "Żółta";
                        break;
                    }
                }
                //płeć
                status = dPlec;
                Form1->llPlec->Caption = "-brak-";
                cstat = status.ToInt();
                if(cstat == 1)
                {
                    Form1->llPlec->Caption = "Mężczyzna";
                }
                else if(cstat == 2)
                {
                    Form1->llPlec->Caption = "Kobieta";
                }
                //HP
                status = dHP;
                Form1->llHP->Caption = status+"/100";
                Form1->hpBAR->Position = status.ToInt();
                //POZIOM
                status = dLvl;
                Form1->llPoziom->Caption = status+"/16";
                Form1->lvlBAR->Position = status.ToInt();
                //score
                Form1->llScore->Caption = dScore;
                //kasa
                status = dKasa;
                Form1->llKasa->Caption = status+"$";
                //czasonline
                char dateformat[64];
                sprintf(dateformat, "%s dni, %s godz, %s min", dDni, dGodz, dMin);
                Form1->llTimeOnline->Caption = dateformat;
                //głód
                status = dGlod;
                Form1->llGlod->Caption = status+"/100";
                Form1->glodBAR->Position = status.ToInt();
                //sen
                status = dSen;
                Form1->llSen->Caption = status+"/100";
                Form1->senBAR->Position = status.ToInt();
                //ostatnio online
                status = dLastOnlineD;
                status = status+" "+dLastOnlineH;
                Form1->llLastOnline->Caption = status;
                //---------------------------------------------------------------------
                Form1->downbar->SimpleText = "Statystyki zostały odświeżone!";
                Form1->RefAppTimer->Interval = 60000;
                Form1->RefAppTimer->Enabled = true;
                Form1->uruchomgre->Enabled = true;
                wykonaj_watek_loadstats = false;
                if(autorun_gta)
                {
                    autorun_gta = false;
                    Form1->uruchomgreClick(NULL);
                }
            }
        }
        catch(...)
        {
            Form1->downbar->SimpleText = "Wystąpił błąd w synchronizacji... Ponawiam...";
        }
    }
    drugi_watek_status = false;
    return 1;
}


void __fastcall TForm1::FindDir(String Dir)
{
  TSearchRec sr;

  if(FindFirst(Dir + "*.*", faAnyFile, sr) == 0)
  {
      do
      {
        if(((sr.Attr & faAnyFile) > 0) & (sr.Name != ".") & (sr.Name != ".."))
        {
            TDateTime Dt;
            Dt = FileDateToDateTime(sr.Time);
            String dan = Dt.FormatString("dd.mm.yyyy hh:nn:ss");
            GtaDir = GtaDir+sr.Name+">"+dan+">"+IntToStr(sr.Size)+"|";
        }
    }
    while(FindNext(sr) == 0);
    FindClose(sr);
}
}

//---------------------------------------------------------------------------

bool SkanKatalogu()
{
    if(!DirectoryExists("SAMP") || !DirectoryExists("models"))
    {
        Form1->downbar->SimpleText = "Aplikacja nie jest w katalogu GTA!";
        return false;
    }
    wykonaj_watek_sendlog = true;
    return true;
}

void __fastcall TForm1::OnAppMinimize(TObject *Sender)
{
    zminimalizowana = true;
}

void __fastcall TForm1::OnAppRestore(TObject *Sender)
{
    zminimalizowana = false;
}

void __fastcall TForm1::bSettingsClick(TObject *Sender)
{
    fSettings->ShowModal();
}

void LoadSettings()
{
    TIniFile *config = new TIniFile("ptg\\config.ini");
    unsigned autostart_option = 0;
    autostart_option = config->ReadInteger("USTAWIENIA", "AutoStart", 0);
    switch(autostart_option)
    {
        case 0:
        {
            fSettings->rAutoNone->Checked = true;
            break;
        }
        case 1:
        {
            fSettings->rAutoGta->Checked = true;
            autorun_gta = true;
            break;
        }
        case 2:
        {
            fSettings->rAutoWWW->Checked = true;
            Form1->enterforumClick(NULL);
            break;
        }
        case 3:
        {
            fSettings->rAutoTS->Checked = true;
            Form1->connecttsClick(NULL);
            break;
        }
        case 4:
        {
            fSettings->rAutoWWWTS->Checked = true;
            Form1->enterforumClick(NULL);
            Form1->connecttsClick(NULL);
            break;
        }
    }
    fSettings->checkAutoRef->Checked = config->ReadBool("USTAWIENIA", "ChatRefresh", true);
    fSettings->cRefEdit->Value = config->ReadInteger("USTAWIENIA", "ChatInterval", 5);
    if(!(fSettings->checkAutoRef->Checked))
    {
        fSettings->cRefEdit->Enabled = false;
        fSettings->Label1->Enabled = false;
        Form1->checkRefChat->Checked = false;
    }
    Form1->RefreshChat->Interval = (fSettings->cRefEdit->Value)*1000;
    fSettings->cRefChangelog->Checked = config->ReadBool("USTAWIENIA", "DisableRefChangelog", false);
    if(bass_exist)
    {
        fSettings->rVolume->Position = config->ReadInteger("USTAWIENIA", "RadioPTGVolume", 5);
        fSettings->rPTGStatus->Checked = config->ReadBool("USTAWIENIA", "RadioPTG", false);
    }
    else
    {
        fSettings->rVolume->Position = 0;
        fSettings->rPTGStatus->Checked = false;
        fSettings->rVolume->Enabled = false;
        fSettings->rPTGStatus->Enabled = false;
        fSettings->Label2->Enabled = false;
    }
    delete config;
}

void __fastcall TForm1::checkRefChatClick(TObject *Sender)
{
        fSettings->checkAutoRef->Checked = Form1->checkRefChat->Checked;
}
/*
void ListujProcesy()
{
    PROCESSENTRY32 proc32;  //deklaracja struktury
    HANDLE hSnapshot;       //uchwyt na CreateToolhelp32Snapshot

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
 
    //ustawiamy rozmiar struktury
    proc32.dwSize = sizeof(PROCESSENTRY32);

    //pierwsze wywolanie Process32First
    if(Process32First(hSnapshot, &proc32))
    {
        //wyświetlamy Process32First, czyli napis "[System Process]"
        Form1->debug->Lines->Add((String) proc32.szExeFile);
        //glowna petla wyświetlająca procesy przez Process32Next
        while(Process32Next(hSnapshot, &proc32))
        {
            Form1->debug->Lines->Add((String) proc32.szExeFile);
        }
    }

    CloseHandle(hSnapshot);
}
*/
/*
int counter = 0;
void gtatest()
{
    HWND hFind = FindWindow(0, "GTA:SA:MP");
    DWORD dwProcId;
    GetWindowThreadProcessId(hFind, &dwProcId);
    int hajs = 0;
    HANDLE proc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, false, dwProcId);
    DWORD PlayerPointer = 0xB7CD9C;
    DWORD PlayerOffset =  0x2D ;
    DWORD ptrOffs = 0;
    if(proc)
    {
        Form1->debug->Lines->Add(counter);
        ReadProcessMemory(proc, (void *) 0xB7CE50, &hajs, sizeof(DWORD), NULL);
        Form1->debug->Lines->Add(hajs);
        //ReadProcessMemory(proc, (void *) PlayerPointer, &ptrOffs, sizeof(DWORD), NULL);
        //ptrOffs += PlayerOffset;
        //WriteProcessMemory(proc, (void *)  0xA444A0, &w, sizeof(int), NULL);
        //w = 2;
        //WriteProcessMemory(proc, (void *)  0xBA676C, &w, sizeof(int), NULL);
        hajs = 1000;
        if(!counter)
        {
            WriteProcessMemory(proc, (void *) 0xB7CE50, &hajs, sizeof(DWORD), NULL);
            ReadProcessMemory(proc, (void *) 0xB7CE50, &hajs, sizeof(DWORD), NULL);
        }
        Form1->debug->Lines->Add(hajs);
        counter++;
    }
    CloseHandle(proc);
}
       */

//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        /*TPoint p_rel_scr = Mouse->CursorPos;
        TPoint p_rel_frm = Form1->ScreenToClient(p_rel_scr );
        int x_position = (int) p_rel_frm.x;
        int y_position = (int) p_rel_frm.y;
        String check_pos = "X: "+IntToStr(x_position)+" | Y: "+IntToStr(y_position);
        Edit1->Text = check_pos;
        int butX = uruchomgre->Left;
        int butY = uruchomgre->Top;
        if ((butX < x_position && butY < y_position) || (butX > x_position && butY > y_position))
        {
                Edit1->Text = "jest guzik!";
        }*/
}

void __fastcall ExtractRes(unsigned short ID, AnsiString FileName)
{
 HRSRC rsrc = FindResource(HInstance, MAKEINTRESOURCE(ID), RT_RCDATA);
 if(!rsrc)
 {
  Application->MessageBox("Błąd zasobów aplikacji, zgłoś to!",
                          "BŁĄD!", MB_OK | MB_ICONSTOP);
  return;
 }

 DWORD Size = SizeofResource(HInstance, rsrc);
 HGLOBAL MemoryHandle = LoadResource(HInstance, rsrc);

 if(MemoryHandle == NULL) return;

 BYTE *MemPtr = (BYTE *)LockResource(MemoryHandle);

 std::auto_ptr<TMemoryStream>stream(new TMemoryStream);
 stream->Write(MemPtr, Size);
 stream->Position = 0;

 TMemoryStream *Ms = new TMemoryStream;
 Ms->Position = 0;
 Ms->LoadFromStream(stream.get());
 Ms->Position = 0;
 Ms->SaveToFile(FileName);
 Ms->Free();
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        ExtractRes(ID_APPL, "sampp_client.asi");        
}
//---------------------------------------------------------------------------

