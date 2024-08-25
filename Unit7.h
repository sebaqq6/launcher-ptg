//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ddraw.h>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TformDDraw : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TMemo *Memo1;
        TTimer *Timer1;
        TButton *Button2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
        void __fastcall DDraw(void);
        void __fastcall DDrawStop(void);
        LPDIRECTDRAW            lpDD;
        LPDIRECTDRAWSURFACE     lpDDSEkran;
        LPDIRECTDRAWSURFACE     lpDDSBuffer;
        HDC                     kontekst;
        HDC hdcmem;
        HBITMAP hbmp;
public:		// User declarations
        __fastcall TformDDraw(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformDDraw *formDDraw;
//---------------------------------------------------------------------------
#endif
 