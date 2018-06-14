//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit1.h"
#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sComboBox"
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ComboBox1Change(TObject *Sender)
{
if(ComboBox1->ItemIndex == 0)
 {
 Form8->Caption = "Первый запуск";
 Button2->Caption = "Читать \"Как использовать программу\"";
 }
if(ComboBox1->ItemIndex == 1)
 {
 Form8->Caption = "First start";
 Button2->Caption = "How to use program";
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm8::Button2Click(TObject *Sender)
{
if(ComboBox1->ItemIndex == 0)
ShellExecute(0,0,"./FAQ/helpRu.html",0,0, SW_SHOWDEFAULT);
if(ComboBox1->ItemIndex == 1)
ShellExecute(0,0,"./FAQ/helpEn.html",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm8::Button1Click(TObject *Sender)
{
TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"settings.ini");
String OneSt;
OneSt = 1;
Ini->WriteString("SSG","OneSt", OneSt);

String lang;
if(ComboBox1->ItemIndex == 0)
lang = 0;
if(ComboBox1->ItemIndex == 1)
lang = 1;
Ini->WriteString("SSG","lang", lang);

if(ComboBox1->ItemIndex == 1)
{
Form1->En->Checked = true;
Form1->Ru->Checked = false;
Form1->lang2 = 1;
String Rest;
Rest=1;
Ini->WriteString("SSG","Rest", Rest);
WinExec(AnsiString(Application->ExeName).c_str(),SW_SHOW);
TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"settings.ini");
String RestP;
RestP=0;
Ini->WriteString("SSG","Rest", RestP);
delete Ini;
Form1->Close();
// Form1->TrayIcon1->Minimize();
// Form1->Button15Click(Form1);
}
if(ComboBox1->ItemIndex == 0)
{
Form1->En->Checked = false;
Form1->Ru->Checked = true;
Form1->lang2 = 0;
Form8->Close();
}

}
//---------------------------------------------------------------------------
