//---------------------------------------------------------------------------

#include <vcl.h>
#include <bass.h>
#pragma hdrstop

String app_wersja = "PTG Launcher v1.0[PRO]";
unsigned app_wersja_code = 7;
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit2.cpp", fLogin);
USEFORM("Unit3.cpp", fChangePass);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit5.cpp", fMapa);
USEFORM("Unit6.cpp", fSettings);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
    	HANDLE ptgmtx;
    	ptgmtx = OpenMutex (MUTEX_ALL_ACCESS, false, "PTGLauncher");
        if (ptgmtx == NULL)
        {
            ptgmtx = CreateMutex (NULL, true, "PTGLauncher");
        }
        else
        {
            Application->MessageBox("Możesz mieć tylko jeden uruchomiony Launcher :)", "Wystąpił błąd!", MB_OK | MB_ICONWARNING);
            return 0;
        }
		Application->Initialize();
		Application->Title = app_wersja;
		Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TfLogin), &fLogin);
                 Application->CreateForm(__classid(TfChangePass), &fChangePass);
                 Application->CreateForm(__classid(TForm4), &Form4);
                 Application->CreateForm(__classid(TfMapa), &fMapa);
                 Application->CreateForm(__classid(TfSettings), &fSettings);
                 Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
    BASS_Free();
	return 0;
}
//---------------------------------------------------------------------------
