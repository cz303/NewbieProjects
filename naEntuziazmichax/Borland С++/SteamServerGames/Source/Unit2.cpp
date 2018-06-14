//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
Form2->Close();
Form1->index = -1;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
if(RadioGroup1->ItemIndex == -1)
Form1->index = -1;
if(RadioGroup1->ItemIndex == 0)
Form1->index = 0;
if(RadioGroup1->ItemIndex == 1)
Form1->index = 1;
Form2->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
if(Form1->lang2 == 1)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F2Caption1;
F2Caption1 = ini->ReadString("Form","F2Caption1","");
Form2->Button2->Caption = F2Caption1;

String F2Caption2;
F2Caption2 = ini->ReadString("Form","F2Caption2","");
Form2->RadioGroup1->Caption = F2Caption2;

String F2Caption3;
F2Caption3 = ini->ReadString("Form","F2Caption3","");
Form2->RadioGroup1->Items->Strings[0]= F2Caption3;

String F2Caption4;
F2Caption4 = ini->ReadString("Form","F2Caption4","");
Form2->RadioGroup1->Items->Strings[1]= F2Caption4;

String F2Caption5;
F2Caption5 = ini->ReadString("Form","F2Caption5","");
Form2->Caption = F2Caption5;
}
}
//---------------------------------------------------------------------------

