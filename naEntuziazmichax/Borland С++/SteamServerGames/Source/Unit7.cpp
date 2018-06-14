//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit1.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1Click(TObject *Sender)
{

 if(Edit1->Text == "")
  ShowMessage("Укажите слово для поиска");
  else
  {
 String sFind = Edit1->Text;
 RichEdit1->SelStart=RichEdit1->Text.Pos(Edit1->Text)-1;
  RichEdit1->SelLength=sFind.Length();
  RichEdit1->SetFocus();

   if(RichEdit1->SelLength != sFind.Length())
    ShowMessage("Совпадений нету");
    else
     SendMessage( RichEdit1->Handle,EM_SCROLLCARET, 0,0);
   }

}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button2Click(TObject *Sender)
{
    int StartPos, ToEnd, FoundAt;
  String sFind = Edit1->Text;
  StartPos = RichEdit1->SelStart + 1;
  ToEnd = RichEdit1->Text.Length() - StartPos;

  int nMatch=0, n;

  while (1) {
    n = RichEdit1->FindText(sFind, StartPos, ToEnd, TSearchTypes()<< stMatchCase);
    if (n == -1)
      break;
    StartPos = n + sFind.Length();
    ToEnd = sFind.Length() - StartPos;
    ++nMatch;
    FoundAt = n;
  }

  if (nMatch) {
    RichEdit1->SetFocus();
    RichEdit1->SelStart = FoundAt;
    RichEdit1->SelLength = sFind.Length();
    SendMessage( RichEdit1->Handle,EM_SCROLLCARET, 0,0);
  }


}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button3Click(TObject *Sender)
{
 if(Edit1->Text == "")
  ShowMessage("Укажите слово для поиска");
  else
  {
 String sFind = Edit1->Text;
 RichEdit2->SelStart=RichEdit2->Text.Pos(Edit1->Text)-1;
  RichEdit2->SelLength=sFind.Length();
  RichEdit2->SetFocus();

   if(RichEdit2->SelLength != sFind.Length())
    ShowMessage("Совпадений нету");
    else
     SendMessage( RichEdit2->Handle,EM_SCROLLCARET, 0,0);
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Button4Click(TObject *Sender)
{
int StartPos, ToEnd, FoundAt;
  String sFind = Edit1->Text;
  StartPos = RichEdit2->SelStart + 1;
  ToEnd = RichEdit2->Text.Length() - StartPos;

  int nMatch=0, n;

  while (1) {
    n = RichEdit2->FindText(sFind, StartPos, ToEnd, TSearchTypes()<< stMatchCase);
    if (n == -1)
      break;
    StartPos = n + sFind.Length();
    ToEnd = sFind.Length() - StartPos;
    ++nMatch;
    FoundAt = n;
  }

  if (nMatch) {
    RichEdit2->SetFocus();
    RichEdit2->SelStart = FoundAt;
    RichEdit2->SelLength = sFind.Length();
    SendMessage( RichEdit2->Handle,EM_SCROLLCARET, 0,0);
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm7::FormCreate(TObject *Sender)
{
if(Form1->lang2 == 1)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));

Edit1->Text = "";

String F7Caption1;
F7Caption1 = ini->ReadString("Form","F7Caption1","");
Button3->Caption = F7Caption1;
Button1->Caption = F7Caption1;

String F7Caption2;
F7Caption2 = ini->ReadString("Form","F7Caption2","");
Button2->Caption = F7Caption2;
Button4->Caption = F7Caption2;

RichEdit1->Lines->LoadFromFile("./FAQ/ServeCfgEn.txt"); 
}
}
//---------------------------------------------------------------------------

