//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm9::FormCreate(TObject *Sender)
{
CppWebBrowser1->Navigate(WideString("http://protected.ucoz.ru/index/0-2"));
}
//---------------------------------------------------------------------------
void __fastcall TForm9::FormClose(TObject *Sender, TCloseAction &Action)
{
CppWebBrowser1->Navigate(WideString("http://protected.ucoz.ru/index/0-2"));
}
//---------------------------------------------------------------------------
