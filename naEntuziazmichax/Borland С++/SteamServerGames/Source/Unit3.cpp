//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma link "sLabel"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
ShellExecute(0,0,"http://bzhack.ucoz.ru/SteamServerGames.exe",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button3Click(TObject *Sender)
{
ShellExecute(0,0,"http://bzhack.ucoz.ru/SteamServerGames.zip",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
if(clos == 1)
{
Form3->Top = Form3->Top + 130;
Form3->Width = 233;
Form3->Left = Form3->Left + 230;
Form3->Height = 194;
clos = 0;
}

Form3->Perform(WM_CLOSE,0,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button4Click(TObject *Sender)
{
clos = 1;
Form3->Left = Form3->Left - 230;
Form3->Top = Form3->Top - 130;
Form3->Width = 703;
Form3->Height = 455;
CppWebBrowser1->Left = 0;
CppWebBrowser1->Top = 0;
Button3->Left = 152;
Button3->Top = 392;
Button2->Left = 296;
Button2->Top = 392;
Button1->Left = 560;
Button1->Top = 392;
upd->Visible = false;
Button4->Visible = false;
CppWebBrowser1->Visible = true;
CppWebBrowser1->Navigate(WideString("http://bzhack.ucoz.ru/histori.html"));
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
CppWebBrowser1->Left = 555;
CppWebBrowser1->Top = 555;
CppWebBrowser1->Visible = false;
Button3->Left = 48;
Button3->Top = 64;
Button2->Left = 48;
Button2->Top = 96;
Button1->Left = 48;
Button1->Top = 128;
Button4->Visible = true;
upd->Visible = true;
Label2->Caption = "";
}
//---------------------------------------------------------------------------




void __fastcall TForm3::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
AnsiString Header = "HEAD /v11.txt HTTP/1.1\r\n"
                    "Accept: */*\r\n"
                    "Host: bzhack.ucoz.ru\r\n\r\n";
Socket->SendText(Header);        
}
//---------------------------------------------------------------------------


void __fastcall TForm3::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
TStringList * List = new TStringList();
List->Delimiter = ' ';
List->DelimitedText = Socket->ReceiveText();

TIniFile *ini2;
ini2 = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F3Caption1;
F3Caption1 = ini2->ReadString("Form","F3Caption1","");

const unsigned int INTERVAL = 300;
Sleep (INTERVAL);

if (StrToInt(List->Strings[1]) == 200)
   {
  if(Button4->Caption == F3Caption1)
   Label2->Caption = "New update found!";
  else
   Label2->Caption = "Обнаружено обновление программы!";
   }
else
   {
  if(Button4->Caption == F3Caption1)
   Label2->Caption = "Updates not found";
  else
   Label2->Caption = "Обновления не найденно";
   }
delete List;
ClientSocket1->Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm3::FormCreate(TObject *Sender)
{
Label2->Visible = true;
 if(Form1->lang2 == 1)
Label2->Caption = "Wait...";
 if(Form1->lang2 == 0)
Label2->Caption = "Подождите...";

ClientSocket1->Host = "bzhack.ucoz.ru";
ClientSocket1->Port = 80;
ClientSocket1->Open();

TIniFile *ini;
ini = new TIniFile(ChangeFileExt("./settings.ini", ".INI" ));

String UPdatePROG;
UPdatePROG = ini->ReadString("Menu","UPdatePROG","");
if(UPdatePROG == 1)
upd->Checked = true;
if(UPdatePROG == 0)
upd->Checked = false;

if(Form1->lang2 == 1)
{
TIniFile *ini2;
ini2 = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F3Caption1;
F3Caption1 = ini2->ReadString("Form","F3Caption1","");
Button4->Caption = F3Caption1;

String F3Caption2;
F3Caption2 = ini2->ReadString("Form","F3Caption2","");
Button3->Caption = F3Caption2;

String F3Caption3;
F3Caption3 = ini2->ReadString("Form","F3Caption3","");
Button2->Caption = F3Caption3;

String F3Caption4;
F3Caption4 = ini2->ReadString("Form","F3Caption4","");
upd->Caption = F3Caption4;

String F3Caption5;
F3Caption5 = ini2->ReadString("Form","F3Caption5","");
Button1->Caption = F3Caption5;

String F3Caption6;
F3Caption6 = ini2->ReadString("Form","F3Caption6","");
Form3->Caption = F3Caption6;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm3::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  if(Form1->lang2 == 1)
    Label2->Caption = "Connection error";
  if(Form1->lang2 == 0)
    Label2->Caption = "Ошибка подключения";
}
//---------------------------------------------------------------------------



void __fastcall TForm3::Button5Click(TObject *Sender)
{
Label2->Visible = true;
 if(Form1->lang2 == 1)
Label2->Caption = "Wait...";
 if(Form1->lang2 == 0)
Label2->Caption = "Подождите...";

ClientSocket1->Host = "bzhack.ucoz.ru";
ClientSocket1->Port = 80;
ClientSocket1->Open();
}
//---------------------------------------------------------------------------

