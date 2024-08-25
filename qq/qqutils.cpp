#include <IdHTTP.hpp>
#include <ctime>
#include "qqutils.h"
#include "base64.h"
String HttpPost(TIdHTTP *idhttp, AnsiString url, AnsiString postdata)
{
    TStringStream *pst = new TStringStream(postdata);
    TStringStream *rece = new TStringStream(NULL);
    idhttp->Request->ContentType="application/x-www-form-urlencoded";
    idhttp->Request->UserAgent="Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)";
    idhttp->Post(url, pst, rece);
    String wynik = rece->DataString;
    delete pst;
    delete rece;
    return wynik;
}

String encode_b64(AnsiString txt)
{
	std::string wynik = txt.c_str();
    wynik = base64_encode(reinterpret_cast<const unsigned char*>(wynik.c_str()), wynik.length());
	return wynik.c_str();
}

String decode_b64(AnsiString txt)
{
	std::string wynik = txt.c_str();
    wynik = base64_decode(wynik);
    return wynik.c_str();
}
bool Inject(DWORD pId, LPSTR dllName)
{
  HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
  if(h)
  {
    LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    LPVOID dereercomp = VirtualAllocEx(h, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READ);
    WriteProcessMemory(h, dereercomp, dllName, strlen(dllName), NULL);
    HANDLE asdc = CreateRemoteThread(h, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, dereercomp, 0, NULL);
    WaitForSingleObject(asdc, INFINITE);
    VirtualFreeEx(h, dereercomp, strlen(dllName), MEM_RELEASE);
    CloseHandle(asdc);
    CloseHandle(h);
    return TRUE;
  }
  return FALSE;
}


bool randomgen_init = false;
long long randomgen(long long min, long long max)
{
    if(!randomgen_init)
    {
    	srand(time(NULL));
    	randomgen_init = true;
    }
    long long random = rand() % max + min;
    return random;
}
