//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit1.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sLabel"
#pragma link "JvAnimatedImage"
#pragma link "JvExControls"
#pragma link "JvGIFCtrl"
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button1Click(TObject *Sender)
{
Form6->Perform(WM_CLOSE,0,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Label1Click(TObject *Sender)
{
ShellExecute(0,0,"http://BZhack.ucoz.ru",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormCreate(TObject *Sender)
{
if(Form1->lang2 == 1)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F6Caption1;
F6Caption1 = ini->ReadString("Form","F6Caption1","");
Label1->Caption = F6Caption1;
}
}
//---------------------------------------------------------------------------

