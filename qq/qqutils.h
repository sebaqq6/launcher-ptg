#include <IdHTTP.hpp>

String HttpPost(TIdHTTP *idhttp, AnsiString url, AnsiString postdata);
String encode_b64(AnsiString txt);
String decode_b64(AnsiString txt);
bool Inject(DWORD pId, LPSTR dllName);
bool InjectEX(DWORD pId, LPSTR dllName);
long long randomgen(long long min, long long max);