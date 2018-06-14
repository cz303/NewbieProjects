//---------------------------------------------------------------------------
#if !defined(AFX_STDAFX_H__76B82743_0A0D_4DAF_8A24_6A853435BF48__INCLUDED_)
#define AFX_STDAFX_H__76B82743_0A0D_4DAF_8A24_6A853435BF48__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#pragma argsused
#endif
#define WIN32_LEAN_AND_MEAN
#endif
#include <FileCtrl.hpp>
#include <vcl.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <sstream.h>
#include <winsock2.h>
#include <fstream.h>
#include "registry.hpp"
#include "iostream.h"
#pragma hdrstop

#include <StrUtils.hpp>
#define ADDRESS "213.180.204.8"
//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdlib.h>
#include "iostream.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#pragma argsused
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit6.h"
#include "Unit5.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sSkinManager"
#pragma link "sSplitter"
#pragma link "sCurrEdit"
#pragma link "sCurrencyEdit"
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sEdit"
#pragma link "sStatusBar"
#pragma link "sHintManager"
#pragma link "acProgressBar"
#pragma link "acHeaderControl"
#pragma link "sLabel"
#pragma link "trayicon"
#pragma link "SHDocVw_OCX"
#pragma link "sComboBoxes"
#pragma link "sRichEdit"
#pragma link "sDialogs"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

BOOL WeAreAlone(LPSTR szName)
{
HANDLE hMutex=CreateMutex(NULL,TRUE,szName);
if (GetLastError()==ERROR_ALREADY_EXISTS)
  {
  CloseHandle(hMutex);
  return false;
  }
return true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EnClick(TObject *Sender)
{
if (En->Checked == false)
{
 En->Checked = true;
 Ru->Checked = false;
ShowMessage("Need restart program");
Button3->Enabled = false;
RUN->Enabled = false;
Button8->Enabled = false;
Button9->Enabled = false;
Button10->Enabled = false;
Button1->Enabled = false;
Button2->Enabled = false;
N2->Enabled = false;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::RuClick(TObject *Sender)
{
if (Ru->Checked == false)
 {
 Ru->Checked = true;
 En->Checked = false;
ShowMessage("Перезапустите программу!");
Button3->Enabled = false;
RUN->Enabled = false;
Button8->Enabled = false;
Button9->Enabled = false;
Button10->Enabled = false;
Button1->Enabled = false;
Button2->Enabled = false;
N2->Enabled = false;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::sevClick(TObject *Sender)
{
if (sev->Checked == true)
{
 sev->Checked = false;
 autoservr->Enabled = false;
 autoservr->Checked = false;
 N25->Checked = false;
}
else
{
 N25->Checked = true;
 sev->Checked = true;
 autoservr->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::auturanClick(TObject *Sender)
{
if (auturan->Checked == true)
{
 auturan->Checked = false;
 N27->Checked = false;
TRegistry *Reg = new TRegistry;
Reg->RootKey = HKEY_CURRENT_USER;
Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
String str;
str=Reg->ReadString("Services");
if (str!=Application->ExeName)
Reg->DeleteValue("ServerSteamGames");
Reg->CloseKey();
delete Reg;
}
else
{
 auturan->Checked = true;
 N27->Checked = true;
 TRegistry *Reg = new TRegistry;
Reg->RootKey = HKEY_CURRENT_USER;
Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
String str;
str=Reg->ReadString("Services");
if (str!=Application->ExeName)
Reg->WriteString("ServerSteamGames",Application->ExeName);
Reg->CloseKey();
delete Reg;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::autoservrClick(TObject *Sender)
{
if (autoservr->Checked == true)
{
 N26->Checked = false;
 autoservr->Checked = false;
}
else
{
 N26->Checked = true;
 autoservr->Checked = true;
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N5Click(TObject *Sender)
{
cl = 1;
Form1->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
Form4->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::sockConnecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
//        off->Visible = false;
//        on->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Form2->ShowModal();
if(index == 1){
 const unsigned int INTERVAL = 100;
 Dum1->Visible = true;
 serverstats->Repaint();
 Sleep (INTERVAL);
 Dum1->Position = 7;
 Form1->MyFunction2();
 }
if(index == 0){
 const unsigned int INTERVAL = 100;
 Dum1->Visible = true;
 serverstats->Repaint();
 Sleep (INTERVAL);
 Dum1->Position = 7;
 Form1->MyFunction();
 }
if(index == -1){
 index = 0;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MyFunction2()
{
// unsigned short port = IntToStr(reinterpret_cast<unsigned short>(Edit1->Text));
 if(Edit1->Text == "")
 {
 if(Form1->lang2 == 1)
 ShowMessage("Enter into a field <port> port from 5 symbols (for example 27015)");
 if(Form1->lang2 == 0)
 ShowMessage("Введите в строку <порт> желаемый вами порт (например 27015)");

 Dum1->Visible = false;
 Dum1->Position = 0;
 }
 else
 {
const unsigned int INTERVAL = 200;
 WSADATA WSAData;
  Dum1->Position = 8;
  Sleep (INTERVAL);
 SOCKET Client = INVALID_SOCKET;

 SOCKADDR_IN rmTCP;
char *c; if (!WSAStartup(MAKEWORD(1,1), &WSAData))

    {
    Dum1->Position = 15;
  Sleep (INTERVAL);

    printf("WSA started successfully!\r\n");

    Client = socket (AF_INET,SOCK_STREAM,0);

    rmTCP.sin_family = AF_INET;
       Dum1->Position = 20;
  Sleep (INTERVAL);
    rmTCP.sin_addr.s_addr = inet_addr("213.180.204.8");
       Dum1->Position = 35;
  Sleep (INTERVAL);
    rmTCP.sin_port = htons (Edit1->Text.ToInt());
       Dum1->Position = 55;
  Sleep (INTERVAL);
      Dum1->Position = 80;
  Sleep (INTERVAL);
    if (connect (Client, (struct sockaddr *)&rmTCP,sizeof(rmTCP)) !=0)

        {

        Client = INVALID_SOCKET;

        Dum1->Position = 100;
        Sleep (INTERVAL);
       Label6->Visible = false;
       Label5->Visible = true;
        Label4->Visible = true;

        }

    else {
        Dum1->Position = 100;

        Sleep (INTERVAL);
        Label4->Visible = false;
       Label6->Visible = true;
       Label5->Visible = false;
         }
    shutdown(Client,4);
    WSACleanup();

    }
else
    {
   ShowMessage("WSA startup error!");
    }
gets(c);

Dum1->Position = 0;
Dum1->Visible = false;

}
}
//----------------------------------------------------------------------------



void __fastcall TForm1::MyFunction()
{

 char PORT;
 if(Edit1->Text == "")
 {
  if(Form1->lang2 == 1)
 ShowMessage("Enter into a field <port> port from 5 symbols (for example 27015)");
 if(Form1->lang2 == 0)
 ShowMessage("Введите в строку <порт> желаемый вами порт (например 27015)");
 Dum1->Visible = false;
 Dum1->Position = 0;
 }
 else
 {
 Label4->Visible = false;
// on->Visible = false;
// off->Visible = false;
 PORT = StrToFloat(Edit1->Text);
 const unsigned int INTERVAL = 400;
 char step;
 SOCKET sock;
  Dum1->Position = 14;
  WSADATA wsadata;
  int con, err;
  struct sockaddr_in loc;
  Dum1->Position = 20;
  err = WSAStartup(0x0101, &wsadata);
  Dum1->Position = 21;
  Sleep (INTERVAL);
  Dum1->Position = 22;
  Sleep (INTERVAL);
  if(err != 0)
  {
        //
        Dum1->Position = 40;
        exit(1);
  }
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock <= 0)
  {
        //
        Dum1->Position = 40;
        exit(1);
  }
  Sleep (INTERVAL);
  loc.sin_family = AF_INET;
  Dum1->Position = 45;
  loc.sin_port = htons(PORT);
  Sleep (INTERVAL);
  Dum1->Position = 68;
    Sleep (INTERVAL);
  Dum1->Position = 69;
    Sleep (INTERVAL);
  Dum1->Position = 72;
  loc.sin_addr.s_addr = inet_addr(ADDRESS);

  con = connect(sock, (struct sockaddr *)&loc, sizeof(loc));
  Dum1->Position = 78;
  if(con < 0)
    {
        Dum1->Position = 100;
        Sleep (INTERVAL);
        Label6->Visible = false;
        Label5->Visible = true;
        Label4->Visible = true;
    }
  else
     {
        Dum1->Position = 100;
        Sleep (INTERVAL);
        Label4->Visible = false;
        Label6->Visible = true;
        Label5->Visible = false;
     }
 closesocket(sock);
 Dum1->Position = 0;
 Dum1->Visible = false;

 }

}
//----------------------------------------------------------------------------





void __fastcall TForm1::RUNClick(TObject *Sender)
{
// std::string cmd = "./srcds.exe -game tf -console -port 27018 -console +maxplayers 24 -tickrate 100 +sv_lan 0 +fps_max 300 +exec server.cfg +map ctf_2fort";
// WinExec("./srcds.exe -- +exec server.cfg", SW_HIDE);
// CreateProcess("./srcds.exe -game tf -console -port 27018",NULL,NULL, NULL, NULL,HIGH_PRIORITY_CLASS,NULL, NULL, NULL, NULL);
// CreateProcess("./srcds.exe -- -game tf -console -port 27018",NULL,NULL,NULL,IDLE_PRIORITY_CLASS,NULL,NULL,NULL,NULL,NULL);

String tickrate;
if(RadioGroup12->ItemIndex == 0)
tickrate = "-tickrate 33";
if(RadioGroup12->ItemIndex == 1)
tickrate = "-tickrate 66";
if(RadioGroup12->ItemIndex == 2)
tickrate = "-tickrate 100";

String console;
if(RadioGroup11->ItemIndex == 0)
console = "-console";
if(RadioGroup11->ItemIndex == 1)
console = "";

String LAN;
if(RadioGroup10->ItemIndex == 0)
LAN = "+sv_lan 1";
if(RadioGroup10->ItemIndex == 1)
LAN = "+sv_lan 0";

String bot;
if(RadioGroup9->ItemIndex == 0)
bot = "";
if(RadioGroup9->ItemIndex == 1)
bot = "-nobots";

String VAC2;
if(RadioGroup8->ItemIndex == 0)
VAC2 = "";
if(RadioGroup8->ItemIndex == 1)
VAC2 = "-insecure";

String update;
if(CheckBox3->Checked == true)
update = "-autoupdate";
if(CheckBox3->Checked == false)
update = "";

String dir;
dir = Edit2->Text;

String filee;
if(game->ItemIndex == 0)
filee = dir;
if(game->ItemIndex == 1)
filee = dir;
if(game->ItemIndex == 2)
filee = dir;
if(game->ItemIndex == 3)
filee = dir;
if(game->ItemIndex == 4)
filee = dir;
if(game->ItemIndex == 5)
filee = dir;
if(game->ItemIndex == 6)
filee = dir;
if(game->ItemIndex == 7)
filee = dir;
if(game->ItemIndex == 8)
filee = dir;

String sgame;
if(game->ItemIndex == 0)
sgame = "tf";
if(game->ItemIndex == 1)
sgame = "cstrike";
if(game->ItemIndex == 2)
sgame = "hl2mp";
if(game->ItemIndex == 3)
sgame = "dod";
if(game->ItemIndex == 4)
sgame = "cstrike";
if(game->ItemIndex == 5)
sgame = "left4dead";
if(game->ItemIndex == 6)
sgame = "garrysmod";
if(game->ItemIndex == 7)
sgame = "insurgency";
if(game->ItemIndex == 8)
sgame = "zps";


String prioritet;
if(RadioGroup7->ItemIndex == 0)
prioritet = "HIGH_PRIORITY_CLASS";
if(RadioGroup7->ItemIndex == 1)
prioritet = "NORMAL_PRIORITY_CLASS";
if(RadioGroup7->ItemIndex == 2)
prioritet = "IDLE_PRIORITY_CLASS";

String PORT;
PORT = Edit1->Text;

String NAME;
NAME = Edit6->Text;

String MaxPlaer;
MaxPlaer = Edit7->Text;

String IPADRESS;
IPADRESS = Edit8->Text;

String MAP;
MAP = Edit9->Text;

String AHTER;
AHTER = Ater->Text;

String s;
s = Edit2->Text;
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
s.Delete(s.Length(),1);
if(game->ItemIndex != 4)
s.Delete(s.Length(),1);

String b;
// b = ExtractFilePath(OpenDialog2->FileName);
b = s;
 if(Edit2->Text == "")
   {
   if(Form1->lang2 == 1)
   ShowMessage("Do not chosen right path to srcds.exe!");
   if(Form1->lang2 == 0)
   ShowMessage("Не выбран путь к файлу srcds.exe!");
   }
  else
   {
   if(FileExists(b+"\\"+sgame+"\\maps\\"+MAP+".bsp") != true && CheckBox4->Checked == false)
{

   if(Form1->lang2 == 1)
ShowMessage((AnsiString ("The map \""+MAP+ "\" could not be found at path " +b+sgame+"\\maps\\")).c_str());
   if(Form1->lang2 == 0)
ShowMessage((AnsiString ("Карта \"" +MAP+ "\" не найдена по адресу " +b+sgame+"\\maps\\")).c_str());

}
else
{
 if(game->Text == ""){
   if(Form1->lang2 == 1)
   ShowMessage("Select game");
   if(Form1->lang2 == 0)
ShowMessage("Выбирите игру!");
}
else
 {
 if(Edit2->Text == ""){
   if(Form1->lang2 == 1)
  ShowMessage("Do not chosen right path to srcds.exe!");
   if(Form1->lang2 == 0)
  ShowMessage("Не выбран путь к файлу srcds.exe!");

  }
  else
   {
       if(DirectoryExists(b+"/"+sgame) == true)
         {
           if(CheckBox2->Checked == true)
              {

TStringList *List = new TStringList;
List->Add("Code");
List->Add("@echo off");
List->Add("cls");
List->Add(":loop");
List->Add("echo (%date% %time%) Starting SRCDS");
List->Add("start /wait "+dir+" -game "+sgame+" "+bot+" "+tickrate+" "+update+" "+console+" -ip "+IPADRESS+" -port "+PORT+" "+AHTER+" +hostname \""+NAME+"\" +maxplayers "+MaxPlaer+" +map "+MAP+" "+LAN+" "+VAC2+"(%date% %time%) Restarting SRCDS");
List->Add("goto loop");
List->SaveToFile(b+"/StatusControl.bat");
List->Clear();
List->LoadFromFile(b+"/StatusControl.bat");
List[7];//-это строка
List->Count;//-это кол-во строк
      const unsigned int INTERVAL = 500;
       Sleep (INTERVAL);
STARTUPINFO startupInfo = {0};
startupInfo.cb = sizeof(startupInfo);
PROCESS_INFORMATION processInformation;
CreateProcess(NULL,(AnsiString (b+"/StatusControl.bat")).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);

              }

             else
             {
            STARTUPINFO startupInfo = {0};
            startupInfo.cb = sizeof(startupInfo);
            PROCESS_INFORMATION processInformation;
            if(prioritet == "HIGH_PRIORITY_CLASS")
            CreateProcess(NULL,(AnsiString (dir+" -game "+sgame+" "+bot+" "+tickrate+" "+update+" "+console+" -ip "+IPADRESS+" -port "+PORT+" "+AHTER+" +hostname \""+NAME+"\" +maxplayers "+MaxPlaer+" +map "+MAP+" "+LAN+" "+VAC2+" ")).c_str(), NULL, NULL, FALSE, HIGH_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
            if(prioritet == "NORMAL_PRIORITY_CLASS")
            CreateProcess(NULL,(AnsiString (dir+" -game "+sgame+" "+bot+" "+tickrate+" "+update+" "+console+" -ip "+IPADRESS+" -port "+PORT+" "+AHTER+" +hostname \""+NAME+"\" +maxplayers "+MaxPlaer+" +map "+MAP+" "+LAN+" "+VAC2+" ")).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
            if(prioritet == "IDLE_PRIORITY_CLASS")
            CreateProcess(NULL,(AnsiString (dir+" -game "+sgame+" "+bot+" "+tickrate+" "+update+" "+console+" -ip "+IPADRESS+" -port "+PORT+" "+AHTER+" +hostname \""+NAME+"\" +maxplayers "+MaxPlaer+" +map "+MAP+" "+LAN+" "+VAC2)).c_str(), NULL, NULL, FALSE, IDLE_PRIORITY_CLASS, NULL, NULL, &startupInfo, &processInformation);
             }
          }
            else
            {
              if(Form1->lang2 == 1)
              ShowMessage("Game folder not found");
              if(Form1->lang2 == 0)
            ShowMessage((AnsiString ("Не найдена папка игры ") +sgame).c_str());
            }
          if(start2 == 1)
           Timer1->Enabled = true; 
        }
    }
  }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
sevdir();
// const unsigned int INTERVAL = 600;
// Sleep(INTERVAL);
// MyPath = "";
// Edit2->Text = "";
// dirf2 = "";
// Sleep(INTERVAL);
sevop();
// TIniFile *Ini = new TIniFile("./settings.ini");
// Ini->WriteString("Options", "file",dirf);

// ofstream fo;
// fo.open("./srcds.ini");
// fo<<"[Options]"<<endl;
// fo<<"file="<<(dirf).c_str();
// fo.close();

// String dirf;
// dirf = Edit2->Text;
// TStringList *List = new TStringList;
// List->Add("[Options]");
// List->Add((AnsiString ("file="+dirf)).c_str());
// List->SaveToFile("./srcds.ini");
// List->Clear();
// List->LoadFromFile("./srcds.ini");
// List[2];//-это строка
// List->Count;//-это кол-во строк
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sevop()
{
TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"settings.ini");

// String MyPath;
// MyPath = ExtractFilePath(Application->ExeName);
// WritePrivateProfileSection("Options","",(AnsiString (MyPath+"settings.ini")).c_str());
// WritePrivateProfileSection("Menu","",(AnsiString (MyPath+"settings.ini")).c_str());

String tickrate;
if(RadioGroup12->ItemIndex == -1)
tickrate = -1;
if(RadioGroup12->ItemIndex == 0)
tickrate = 0;
if(RadioGroup12->ItemIndex == 1)
tickrate = 1;
if(RadioGroup12->ItemIndex == 2)
tickrate = 2;
Ini->WriteString("Options","tickrate", tickrate);
// WritePrivateProfileString("Options","tickrate",(AnsiString () +tickrate).c_str(),"./settings.ini");


String console;
if(RadioGroup11->ItemIndex == -1)
console = -1;
if(RadioGroup11->ItemIndex == 0)
console = 0;
if(RadioGroup11->ItemIndex == 1)
console = 1;
Ini->WriteString("Options","console", console);
// WritePrivateProfileString("Options","console",(AnsiString () +console).c_str(),"./settings.ini");

String LAN;
if(RadioGroup10->ItemIndex == -1)
LAN = -1;
if(RadioGroup10->ItemIndex == 0)
LAN = 0;
if(RadioGroup10->ItemIndex == 1)
LAN = 1;
Ini->WriteString("Options","LAN", LAN);
// WritePrivateProfileString("Options","LAN",(AnsiString () +LAN).c_str(),"./settings.ini");

String bot;
if(RadioGroup9->ItemIndex == -1)
bot = -1;
if(RadioGroup9->ItemIndex == 0)
bot = 0;
if(RadioGroup9->ItemIndex == 1)
bot = 1;
Ini->WriteString("Options","bot", bot);
// WritePrivateProfileString("Options","bot",(AnsiString () +bot).c_str(),"./settings.ini");

String VAC2;
if(RadioGroup8->ItemIndex == -1)
VAC2 = -1;
if(RadioGroup8->ItemIndex == 0)
VAC2 = 0;
if(RadioGroup8->ItemIndex == 1)
VAC2 = 1;
Ini->WriteString("Options","VAC2", VAC2);
// WritePrivateProfileString("Options","VAC2",(AnsiString () +VAC2).c_str(),"./settings.ini");

String ProcesClass;
if(RadioGroup7->ItemIndex == -1)
ProcesClass = -1;
if(RadioGroup7->ItemIndex == 0)
ProcesClass = 0;
if(RadioGroup7->ItemIndex == 1)
ProcesClass = 1;
if(RadioGroup7->ItemIndex == 2)
ProcesClass = 2;
Ini->WriteString("Options","ProcesClass", ProcesClass);
// WritePrivateProfileString("Options","ProcesClass",(AnsiString () +ProcesClass).c_str(),"./settings.ini");

String games;
if(game->ItemIndex == -1)
games = -1;
if(game->ItemIndex == 0)
games = 0;
if(game->ItemIndex == 1)
games = 1;
if(game->ItemIndex == 2)
games = 2;
if(game->ItemIndex == 3)
games = 3;
if(game->ItemIndex == 4)
games = 4;
if(game->ItemIndex == 5)
games = 5;
if(game->ItemIndex == 6)
games = 6;
if(game->ItemIndex == 7)
games = 7;
Ini->WriteString("Options","games", games);
// WritePrivateProfileString("Options","games",(AnsiString () +games).c_str(),"./settings.ini");

String PORT;
PORT = Edit1->Text;
Ini->WriteString("Options","PORT", PORT);
// WritePrivateProfileString("Options","PORT",(AnsiString () +PORT).c_str(),"./settings.ini");

String update;
if(CheckBox3->Checked == true)
update = 1;
if(CheckBox3->Checked == false)
update = 0;
Ini->WriteString("Options","update", update);
// WritePrivateProfileString("Options","update",(AnsiString () +update).c_str(),"./settings.ini");


String chmap;
if(CheckBox4->Checked == true)
chmap = 1;
if(CheckBox4->Checked == false)
chmap = 0;
Ini->WriteString("Options","chmap", chmap);


String NAME;
NAME = Edit6->Text;
Ini->WriteString("Options","NAME", NAME);
// WritePrivateProfileString("Options","NAME",(AnsiString () +NAME).c_str(),"./settings.ini");

String MaxPlaer;
MaxPlaer = Edit7->Text;
Ini->WriteString("Options","MaxPlaer", MaxPlaer);
// WritePrivateProfileString("Options","MaxPlaer",(AnsiString () +MaxPlaer).c_str(),"./settings.ini");

String IPADRESS;
IPADRESS = Edit8->Text;
Ini->WriteString("Options","IPADRESS", IPADRESS);
// WritePrivateProfileString("Options","IPADRESS",(AnsiString () +IPADRESS).c_str(),"./settings.ini");

String MAP;
MAP = Edit9->Text;
Ini->WriteString("Options","MAP", MAP);
// WritePrivateProfileString("Options","MAP",(AnsiString () +MAP).c_str(),"./settings.ini");

String AHTER;
AHTER = Ater->Text;
Ini->WriteString("Options","AHTER", AHTER);
// WritePrivateProfileString("Options","AHTER",(AnsiString () +AHTER).c_str(),"./settings.ini");

String sevop;
if(sev->Checked == true)
sevop = 1;
if(sev->Checked == false)
sevop = 0;
// WritePrivateProfileString("Menu","SevOp",(AnsiString () +sevop).c_str(),"./settings.ini");
Ini->WriteString("Menu","SevOp", sevop);

String notepad;
if(pad->Checked == true)
notepad = 1;
if(pad->Checked == false)
notepad = 0;
Ini->WriteString("Menu","Notepad", notepad);

String AutoRanProg;
if(auturan->Checked == true)
AutoRanProg = 1;
if(auturan->Checked == false)
AutoRanProg = 0;
Ini->WriteString("Menu","AutoRanProg", AutoRanProg);
// WritePrivateProfileString("Menu","AutoRanProg",(AnsiString () +AutoRanProg).c_str(),"./settings.ini");

String AutoRanServ;
if(autoservr->Checked == true)
AutoRanServ = 1;
if(autoservr->Checked == false)
AutoRanServ = 0;
Ini->WriteString("Menu","AutoRanServ", AutoRanServ);
// WritePrivateProfileString("Menu","AutoRanServ",(AnsiString () +AutoRanServ).c_str(),"./settings.ini");

String UPdatePROG;
if(Form3->upd->Checked == true)
UPdatePROG = 1;
if(Form3->upd->Checked == false)
UPdatePROG = 0;
Ini->WriteString("Menu","UPdatePROG", UPdatePROG);
// WritePrivateProfileString("Menu","UPdatePROG",(AnsiString () +UPdatePROG).c_str(),"./settings.ini");

String statusserver;
if(Form1->CheckBox2->Checked == true)
statusserver = 1;
if(Form1->CheckBox2->Checked == false)
statusserver = 0;
Ini->WriteString("Options","statusserver", statusserver);

String lang;
if(Ru->Checked  == true)
lang = 0;
if(En->Checked == true)
lang = 1;
Ini->WriteString("SSG","lang", lang);

String Skin;
Skin = sSkinManager1->SkinName;
Ini->WriteString("SSG","Skin", Skin);

delete Ini;
}
//------------------------------------------------------------------------

void __fastcall TForm1::sevdir()
{
// String dirf;
// dirf = Edit2->Text;

// dirf = StringReplace(dirf,"\\", "/", TReplaceFlags() << rfReplaceAll);
// dirf = AnsiReplaceText(dirf, "\\", "/");
// ShowMessage(dirf);

// String MyPath;
// MyPath = ExtractFilePath(Application->ExeName);

// TStringList *List = new TStringList;
// List->Add((AnsiString (dirf)).c_str());
// List->SaveToFile(MyPath+"srcds.txt");
// List->Clear();
// List->LoadFromFile(MyPath+"srcds.txt");
// List[1];//-это строка
// List->Count;//-это кол-во строк

TIniFile *Ini = new TIniFile(ExtractFilePath(Application->ExeName)+"settings.ini");
Ini->WriteString("srcds", "filedir", Edit2->Text);

delete Ini;
// WritePrivateProfileSection("srcds","",(AnsiString (MyPath+"settings.ini")).c_str());
// TIniFile *Ini = new TIniFile(MyPath+"srcds.ini");
// Ini->WriteString("srcds", "filedir",dirf);
// WritePrivateProfileString("srcds", "filedir",(AnsiString () +dirf).c_str(),(AnsiString (MyPath+"settings.ini")).c_str());

// ShowMessage(WritePrivateProfileString(0,0,0,0));
}
//------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("./settings.ini", ".INI" ));
String Rest;
Rest = ini->ReadString("SSG","Rest","");

String lang;
lang = ini->ReadString("SSG","lang","");
if(lang == 1){
En->Checked = true;
Ru->Checked = false;
lang2=1;
}
if(lang == 0){
Ru->Checked = true;
En->Checked = false;
lang2=0;
}

if(Rest == 1)
{
// продолжить
}
else
{
   if (WeAreAlone("Some_Unique_Name_Or_Other"));
     else
       {
        if(Form1->lang2 == 1)
         ShowMessage("Such a program is already running! Look in the tray.");
       if(Form1->lang2 == 0)
         ShowMessage("Такая программа уже запущена! Посмотрите в трее.");
        exit(0);
       }
}


String sevop;
sevop = ini->ReadString("Menu","SevOp","");
if(sevop == 1)
sev->Checked  = true;
if(sevop == 0)
sev->Checked  = false;

if(sev->Checked == false)
{
autoservr->Enabled = false;
autoservr->Checked = false;
}
else
autoservr->Enabled = true;


if(sev->Checked == true)
{
String AutoRanServ;
AutoRanServ = ini->ReadString("Menu","AutoRanServ","");
if(AutoRanServ == 1)
{
autoservr->Checked = true;
N26->Checked = true;
}
if(AutoRanServ == 0)
{
autoservr->Checked = false;
N26->Checked = false;
}

String notepad;
notepad = ini->ReadString("Menu","Notepad","");
if(notepad == 1)
pad->Checked  = true;
if(notepad == 0)
pad->Checked  = false;

N25->Checked = true;

String tickrate;
tickrate = ini->ReadString("Options","tickrate","");
if(tickrate == -1)
RadioGroup12->ItemIndex = -1;
if(tickrate == 0)
RadioGroup12->ItemIndex = 0;
if(tickrate == 1)
RadioGroup12->ItemIndex = 1;
if(tickrate == 2)
RadioGroup12->ItemIndex = 2;


String console;
console = ini->ReadString("Options","console","");
if(console == -1)
RadioGroup11->ItemIndex = -1;
if(console == 0)
RadioGroup11->ItemIndex = 0;
if(console == 1)
RadioGroup11->ItemIndex = 1;

String LAN;
LAN = ini->ReadString("Options","LAN","");
if(LAN == -1)
RadioGroup10->ItemIndex = -1;
if(LAN == 0)
RadioGroup10->ItemIndex = 0;
if(LAN == 1)
RadioGroup10->ItemIndex = 1;

String bot;
bot = ini->ReadString("Options","bot","");
if(bot == -1)
RadioGroup9->ItemIndex = -1;
if(bot == 0)
RadioGroup9->ItemIndex = 0;
if(bot == 1)
RadioGroup9->ItemIndex = 1;

String VAC2;
VAC2 = ini->ReadString("Options","VAC2","");
if(VAC2 == -1)
RadioGroup8->ItemIndex = -1;
if(VAC2 == 0)
RadioGroup8->ItemIndex = 0;
if(VAC2 == 1)
RadioGroup8->ItemIndex = 1;

String ProcesClass;
ProcesClass = ini->ReadString("Options","ProcesClass","");
if(ProcesClass == -1)
RadioGroup7->ItemIndex = -1;
if(ProcesClass == 0)
RadioGroup7->ItemIndex = 0;
if(ProcesClass == 1)
RadioGroup7->ItemIndex = 1;
if(ProcesClass == 2)
RadioGroup7->ItemIndex = 2;

String games;
games = ini->ReadString("Options","games","");
if(games == -1)
game->ItemIndex = -1;
if(games == 0)
game->ItemIndex = 0;
if(games == 1)
game->ItemIndex = 1;
if(games == 2)
game->ItemIndex = 2;
if(games == 3)
game->ItemIndex = 3;
if(games == 4)
game->ItemIndex = 4;
if(games == 5)
game->ItemIndex = 5;
if(games == 6)
game->ItemIndex = 6;
if(games == 7)
game->ItemIndex = 7;

String PORT;
PORT = ini->ReadString("Options","PORT","");
Edit1->Text = PORT;

String AHTER;
AHTER = ini->ReadString("Options","AHTER","");
Ater->Text = AHTER;

String update;
update = ini->ReadString("Options","update","");
if(update == 1)
CheckBox3->Checked = true;
if(update == 0)
CheckBox3->Checked = false;

String chmap;
chmap = ini->ReadString("Options","chmap","");
if(chmap == 1)
CheckBox4->Checked = true;
if(chmap == 0)
CheckBox4->Checked = false;

String statusserver;
statusserver = ini->ReadString("Options","statusserver","");
if(statusserver == 1)
CheckBox2->Checked = true;
if(statusserver == 0)
CheckBox2->Checked = false;

if(CheckBox2->Checked == true)
 {
 RadioGroup7->Enabled = false;
 RadioGroup7->ItemIndex = 1;
 }


String NAME;
NAME = ini->ReadString("Options","NAME","");
Edit6->Text = NAME;

String MaxPlaer;
MaxPlaer = ini->ReadString("Options","MaxPlaer","");
Edit7->Text = MaxPlaer;

String IPADRESS;
IPADRESS = ini->ReadString("Options","IPADRESS","");
if(IPADRESS != "")
tyi = 1;
Edit8->Text = IPADRESS;

String MAP;
MAP = ini->ReadString("Options","MAP","");
Edit9->Text = MAP;

AnsiString file3;
file3 = ini->ReadString("srcds", "filedir","");
Edit2->Text = file3;

AnsiString skin;
skin = ini->ReadString("SSG", "Skin","");
sSkinManager1->SkinName = skin;

// if(autoservr->Checked == true)
// {
//     if(CheckBox1->Checked == true)
//     {
//     Button4Click(Form1);
//     start1 = 1;
//     start2 = 1;
//     }
//      if(CheckBox1->Checked != true)
//      {
//      start2 = 1;
//      RUNClick(Form1);
//      }
//}

}


String UPdatePROG;
UPdatePROG = ini->ReadString("Menu","UPdatePROG","");

String AutoRanProg;
AutoRanProg = ini->ReadString("Menu","AutoRanProg","");
if(AutoRanProg == 1)
{
N27->Checked = true;
auturan->Checked = true;
}
if(AutoRanProg == 0)
{
N27->Checked = false;
auturan->Checked = false;
}

delete ini;


if(En->Checked == true)
{
language();
}

if(UPdatePROG == 0)
{
ClientSocket1->Host = "bzhack.ucoz.ru";
ClientSocket1->Port = 80;
ClientSocket1->Open();
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::N3Click(TObject *Sender)
{
Form3->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
TStringList * List = new TStringList();
List->Delimiter = ' ';
List->DelimitedText = Socket->ReceiveText();

if (StrToInt(List->Strings[1]) == 200)
{
   Form3->Show();
}
delete List;
ClientSocket1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
AnsiString Header = "HEAD /v11.txt HTTP/1.1\r\n"
                    "Accept: */*\r\n"
                    "Host: bzhack.ucoz.ru\r\n\r\n";
Socket->SendText(Header);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N8Click(TObject *Sender)
{
Form6->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::sLabel1Click(TObject *Sender)
{
// ShellExecute(0,0,"http://2ip.ru/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
if(OpenDialog2->Execute())
Edit2->Text = OpenDialog2->FileName;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{

if(game->Text != "")
 {
if(OpenDialog1->Execute())
 {
   AnsiString bat;
   bat = OpenDialog1->FileName;
   test->Text = bat;

if(test->Text != ""){
// CreateProcess(NULL,(AnsiString (bat)).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
TStringList *List = new TStringList;

String sgame;
String games;
if(game->ItemIndex == 0)
{
sgame = "tfupdate";
games = "tf";
}
if(game->ItemIndex == 1)
{
sgame = "cssupdate";
games = "\"Counter-Strike Source\"";
}
if(game->ItemIndex == 2)
{
games = "hl2mp";
sgame = "hl2mpupdate";
}
if(game->ItemIndex == 3)
{
sgame = "dodupdate";
games = "dods";
}
if(game->ItemIndex == 4)
{
sgame = "csupdate";
games = "cstrike";
}
if(game->ItemIndex == 5)
{
sgame = "l4dupdate";
games = "left4dead";
}
if(game->ItemIndex == 6)
{
sgame = "GModupdate";
games = "garrysmod";
}
if(game->ItemIndex == 7)
{
sgame = "InsurgencyUpdate";
games = "insurgency";
}
if(game->ItemIndex == 8)
{
sgame = "ZPSUpdate";
games = "zps";
}

String s2;
s2 = bat;
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);

List->Add((AnsiString ("start /wait "+bat)).c_str());
List->Add((AnsiString ("start "+bat+" -command update -game "+games+" -dir "+s2)).c_str());
List->Add("exit");
List->SaveToFile((AnsiString (s2+"/"+sgame)+".bat").c_str());
List->Clear();
List->LoadFromFile((AnsiString (s2+"/"+sgame)+".bat").c_str());
List[3];//-это строка
List->Count;//-это кол-во строк

STARTUPINFO startupInfo = {0};
startupInfo.cb = sizeof(startupInfo);
PROCESS_INFORMATION processInformation;
CreateProcess(NULL,(AnsiString (s2)+"/"+sgame+".bat").c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);

  }
 }
}

   else{
   if(Form1->lang2 == 1)
     if(game->Text == "")
    ShowMessage("Game not select");
   if(Form1->lang2 == 0)
     if(game->Text == "")
    ShowMessage("Игра не выбрана");
   }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::N6Click(TObject *Sender)
{
ShellExecute(NULL, "open", "./FAQ/Documentation(ru).html", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label4Click(TObject *Sender)
{
 if(lang2 == 1)
 ShellExecute(0,0, (AnsiString ("www.utorrent.com/testport.php?port="+Edit1->Text)).c_str(),0,0, SW_SHOWDEFAULT);
 else
 ShellExecute(0,0, "./FAQ/Documentation(ru).html/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
OpenDialog3->Execute();
AnsiString maps;
maps = OpenDialog3->FileName;
String File_Name = LeftStr(ExtractFileName(OpenDialog3->FileName), ExtractFileName(OpenDialog3->FileName).Length()-ExtractFileExt(ExtractFileName(OpenDialog3->FileName)).Length());
Edit9->Text = File_Name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  if(Form1->lang2 == 1)
    ShowMessage("Connection error, check up updating it is impossible.");
  if(Form1->lang2 == 0)
    ShowMessage("Ошибка подключения, проверить обновление не удалось.");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N11Click(TObject *Sender)
{
if(tr == 1)
{
// Application->Restore();
TrayIcon1->Restore();
   if(Form1->lang2 == 1)
    N11->Caption = "Hide";
   if(Form1->lang2 == 0)
    N11->Caption = "Скрыть окно";
tr = 0;
tr2 = 0;
}
else
{
// Form1->Hide();
TrayIcon1->Minimize();
   if(Form1->lang2 == 1)
    N11->Caption = "Show";
   if(Form1->lang2 == 0)
     N11->Caption = "Показать окно";
tr = 1;
tr2 = 2;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N16Click(TObject *Sender)
{
cl = 1;
Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N17Click(TObject *Sender)
{
Form3->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
RUNClick(Form1);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
ShellExecute(Handle,"open","./FAQ/help.chm",NULL,NULL,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N19Click(TObject *Sender)
{
Form4->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::clients1Click(TObject *Sender)
{
Form5->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
tr2 ++;
if(tr2 > 3)
{
// Application->Restore();
TrayIcon1->Restore();
   if(Form1->lang2 == 1)
    N11->Caption = "Hide";
   if(Form1->lang2 == 0)
    N11->Caption = "Скрыть окно";
tr2 = 0;
tr = 0;
}
if(tr2 == 2)
{
// Form1->Hide();
TrayIcon1->Minimize();
   if(Form1->lang2 == 1)
    N11->Caption = "Show";
   if(Form1->lang2 == 0)
     N11->Caption = "Показать окно";
tr = 1;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N25Click(TObject *Sender)
{
if (N25->Checked == true)
{
 sev->Checked = false;
 autoservr->Enabled = false;
 autoservr->Checked = false;
 N25->Checked = false;
 N26->Enabled = false;
}
else
{
 sev->Checked = true;
 N25->Checked = true;
 autoservr->Enabled = true;
 N26->Enabled = true;
}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N28Click(TObject *Sender)
{
Form6->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{

if(cl == 2)
{
CanClose = false;
TrayIcon1->Minimize();
   if(Form1->lang2 == 1)
    N11->Caption = "Show";
   if(Form1->lang2 == 0)
     N11->Caption = "Показать окно";
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrayIcon1Minimize(TObject *Sender)
{
tr2 = 2;
tr = 1;
   if(Form1->lang2 == 1)
    N11->Caption = "Show";
   if(Form1->lang2 == 0)
     N11->Caption = "Показать окно";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N27Click(TObject *Sender)
{
if (N27->Checked == true)
{
 auturan->Checked = false;
 N27->Checked = false;
TRegistry *Reg = new TRegistry;
Reg->RootKey = HKEY_CURRENT_USER;
Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
String str;
str=Reg->ReadString("Services");
if (str!=Application->ExeName)
Reg->DeleteValue("ServerSteamGames");
Reg->CloseKey();
delete Reg;
}
else
{
 auturan->Checked = true;
 N27->Checked = true;
 TRegistry *Reg = new TRegistry;
Reg->RootKey = HKEY_CURRENT_USER;
Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",true);
String str;
str=Reg->ReadString("Services");
if (str!=Application->ExeName)
Reg->WriteString("ServerSteamGames",Application->ExeName);
Reg->CloseKey();
delete Reg;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N26Click(TObject *Sender)
{
if (N26->Checked == true)
{
 N26->Checked = false;
 autoservr->Checked = false;
}
else
{
 N26->Checked = true;
 autoservr->Checked = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Restore(TObject *Sender)
{
   if(Form1->lang2 == 1)
    N11->Caption = "Hide";
   if(Form1->lang2 == 0)
    N11->Caption = "Скрыть окно";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
   if(Form1->lang2 == 1)
Edit8->Text = "Wait...";
   if(Form1->lang2 == 0)
Edit8->Text = "Ждите...";
Form1->Repaint();
CppWebBrowser1->Navigate(WideString("http://bzhack.ucoz.ru/index/0-8"));
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button7Click(TObject *Sender)
{
if(Edit2->Text == ""){
   if(Form1->lang2 == 1)
      {
       if(game->ItemIndex != 4)
     ShowMessage("Do not chosen right path to srcds.exe!");
       else
     ShowMessage("Do not chosen right path to hlds.exe!");
     }
   if(Form1->lang2 == 0)
     {
       if(game->ItemIndex != 4)
        ShowMessage("Не выбран путь к файлу srcds.exe!");
       else
        ShowMessage("Не выбран путь к файлу hlds.exe!");
     }

  }
  else
   {
   String s2;
s2 = Edit2->Text;
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
s2.Delete(s2.Length(),1);
if(game->ItemIndex != 4)
s2.Delete(s2.Length(),1);
ShellExecute(NULL, "open", (AnsiString (s2)).c_str(), NULL, NULL, SW_SHOW);
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::CppWebBrowser1DocumentComplete(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL)
{
if(start1 != 1){
String IPName = CppWebBrowser1->LocationName;
Edit8->Text = IPName;
Form1->Repaint();
}
 if(start1 == 1)
  {
  String IPName = CppWebBrowser1->LocationName;
  Edit8->Text = IPName;
  Form1->Repaint();
  Edit8->Text = IPName;
     Form1->Hide();
   if(Form1->lang2 == 1)
    N11->Caption = "Show";
   if(Form1->lang2 == 0)
    N11->Caption = "Скрыть окно";
     RUNClick(Form1);
  start1 = 0;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button8Click(TObject *Sender)
{
if(Edit2->Text == ""){
   if(Form1->lang2 == 1)
      {
       if(game->ItemIndex != 4)
     ShowMessage("Do not chosen right path to srcds.exe!");
       else
     ShowMessage("Do not chosen right path to hlds.exe!");
     }
   if(Form1->lang2 == 0)
     {
       if(game->ItemIndex != 4)
        ShowMessage("Не выбран путь к файлу srcds.exe!");
       else
        ShowMessage("Не выбран путь к файлу hlds.exe!");
     }

  }
  else
   {
     if(game->Text == "")
     {
     if(Form1->lang2 == 1)
       ShowMessage("Select game!");
     if(Form1->lang2 == 0)
       ShowMessage("Выбирите игру!");
     }
      else
      {
        String s3;
        s3 = Edit2->Text;
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       s3.Delete(s3.Length(),1);
       if(game->ItemIndex != 4)
       s3.Delete(s3.Length(),1);
       String sgame;
        if(game->ItemIndex == 0)
        sgame = "\\tf\\cfg\\";
        if(game->ItemIndex == 1)
        sgame = "\\cstrike\\cfg\\";
        if(game->ItemIndex == 2)
        sgame = "\\hl2mp\\cfg\\";
        if(game->ItemIndex == 3)
        sgame = "\\dod\\cfg\\";
        if(game->ItemIndex == 4)
        sgame = "\\cstrike\\";
        if(game->ItemIndex == 5)
        sgame = "\\left4dead\\cfg\\";
        if(game->ItemIndex == 6)
        sgame = "\\garrysmod\\cfg\\";
        if(game->ItemIndex == 7)
        sgame = "\\insurgency\\cfg\\";
        if(game->ItemIndex == 8)
        sgame = "\\zps\\cfg\\";
if(pad->Checked == true)
{
  if(FileExists(s3+sgame+"server.cfg") != true)
  {
  if(Form1->lang2 == 1)
  ShowMessage((AnsiString ("File server.cfg could not be found at path "+s3+sgame+"server.cfg")).c_str());
  if(Form1->lang2 == 0)
  ShowMessage((AnsiString ("Не найден искомый файл "+s3+sgame+"server.cfg")).c_str());
  }
  else
  {
  ShellExecute(Handle,NULL,"notepad",(AnsiString (s3+sgame+"server.cfg")).c_str(),NULL, SW_RESTORE);

   if(sizeform == 1)
    {
Form1->Height = Form1->Height-360;
Form1->Top = Form1->Top+200;
RichEdit1->Clear();
sizeform = 0;
Button10->Enabled = true;
Button9->Enabled = true;
Button8->Enabled = true;
Form7->Close();
Form7->RichEdit2->Visible = false;
Form7->RichEdit1->Visible = false;
Form7->Button4->Visible = false;
Form7->Button3->Visible = false;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;
statusop = 0;
    }
  Form7->Show();
  Form7->Left = 0;
  Form7->Top = 0;
  Form7->RichEdit1->Visible = true;
  Form7->Button1->Visible = true;
  Form7->Button2->Visible = true;
  Form7->Button3->Visible = false;
  Form7->Button4->Visible = false;
  }
}
else
 {
if(sizeform == 0)
{
Form1->Height = Form1->Height+360;
Form1->Top = Form1->Top-200;
}
sizeform=1;
Button8->Enabled = false;
Button9->Enabled = true;
Button10->Enabled = true;
RichEdit1->Clear();

Form7->Show();
Form7->Left = 0;
Form7->Top = 0;
Form7->RichEdit1->Visible = true;
Form7->Button1->Visible = true;
Form7->Button2->Visible = true;
Form7->Button3->Visible = false;
Form7->Button4->Visible = false;

      if(FileExists(s3+sgame+"server.cfg") != true)
        {
     if(Form1->lang2 == 1)
        RichEdit1->Lines->Add("File server.cfg could not be found at path "+s3+sgame+"server.cfg");
     if(Form1->lang2 == 0)
        RichEdit1->Lines->Add("Не найден искомый файл "+s3+sgame+"server.cfg");
        }
       else
        {
        RichEdit1->Lines->LoadFromFile(s3+sgame+"server.cfg");
        statusop = 1;
        currentcfg = s3+sgame+"server.cfg";
        }
      }
   }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
Form1->Height = Form1->Height-360;
Form1->Top = Form1->Top+200;
RichEdit1->Clear();
sizeform = 0;
Button10->Enabled = true;
Button9->Enabled = true;
Button8->Enabled = true;
Form7->Close();
Form7->RichEdit2->Visible = false;
Form7->RichEdit1->Visible = false;
Form7->Button4->Visible = false;
Form7->Button3->Visible = false;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;
statusop = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button14Click(TObject *Sender)
{
  int StartPos, ToEnd, FoundAt;
  String sFind = Edit3->Text;
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

void __fastcall TForm1::Button12Click(TObject *Sender)
{
 if(Edit3->Text == ""){
  if(Form1->lang2 == 1)
   ShowMessage("Specify a word for search");
  if(Form1->lang2 == 0)
   ShowMessage("Укажите слово для поиска");
  }
  else
  {
 String sFind = Edit3->Text;
 RichEdit1->SelStart=RichEdit1->Text.Pos(Edit3->Text)-1;
  RichEdit1->SelLength=sFind.Length();
  RichEdit1->SetFocus();
//  RichEdit1->CaretPos = Point(0, 500 );// 500-Нужная позиция

   if(RichEdit1->SelLength != sFind.Length())
   {
      if(Form1->lang2 == 1)
   ShowMessage("Search string not found");
  if(Form1->lang2 == 0)
    ShowMessage("Совпадений нету");
   }
    else
     SendMessage( RichEdit1->Handle,EM_SCROLLCARET, 0,0);
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button10Click(TObject *Sender)
{
if(Edit2->Text == ""){
   if(Form1->lang2 == 1)
      {
       if(game->ItemIndex != 4)
     ShowMessage("Do not chosen right path to srcds.exe!");
       else
     ShowMessage("Do not chosen right path to hlds.exe!");
     }
   if(Form1->lang2 == 0)
     {
       if(game->ItemIndex != 4)
        ShowMessage("Не выбран путь к файлу srcds.exe!");
       else
        ShowMessage("Не выбран путь к файлу hlds.exe!");
     }

  }
  else
   {
     if(game->Text == "")
     {
     if(Form1->lang2 == 1)
       ShowMessage("Select game!");
     if(Form1->lang2 == 0)
       ShowMessage("Выбирите игру!");
     }
      else
      {
      String s3;
      s3 = Edit2->Text;
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     if(game->ItemIndex != 4)
     s3.Delete(s3.Length(),1);
       String sgame;
        if(game->ItemIndex == 0)
        sgame = "\\tf\\cfg\\";
        if(game->ItemIndex == 1)
        sgame = "\\cstrike\\cfg\\";
        if(game->ItemIndex == 2)
        sgame = "\\hl2mp\\cfg\\";
        if(game->ItemIndex == 3)
        sgame = "\\dod\\cfg\\";
        if(game->ItemIndex == 4)
        sgame = "\\cstrike\\";
        if(game->ItemIndex == 5)
        sgame = "\\left4dead\\cfg\\";
        if(game->ItemIndex == 6)
        sgame = "\\garrysmod\\cfg\\";
        if(game->ItemIndex == 7)
        sgame = "\\insurgency\\cfg\\";
        if(game->ItemIndex == 8)
        sgame = "\\zps\\cfg\\";
if(pad->Checked == true)
{
  if(FileExists(s3+sgame+"server.cfg") != true)
  {
  if(Form1->lang2 == 1)
  ShowMessage((AnsiString ("File server.cfg could not be found at path "+s3+sgame+"autoexec.cfg")).c_str());
  if(Form1->lang2 == 0)
  ShowMessage((AnsiString ("Не найден искомый файл "+s3+sgame+"autoexec.cfg")).c_str());
  }
  else
  {
  ShellExecute(Handle,NULL,"notepad",(AnsiString (s3+sgame+"autoexec.cfg")).c_str(),NULL, SW_RESTORE);

     if(sizeform == 1)
    {
Form1->Height = Form1->Height-360;
Form1->Top = Form1->Top+200;
RichEdit1->Clear();
sizeform = 0;
Button10->Enabled = true;
Button9->Enabled = true;
Button8->Enabled = true;
Form7->Close();
Form7->RichEdit2->Visible = false;
Form7->RichEdit1->Visible = false;
Form7->Button4->Visible = false;
Form7->Button3->Visible = false;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;
statusop = 0;
    }
  }
}
else
 {
if(sizeform == 0)
{
Form1->Height = Form1->Height+360;
Form1->Top = Form1->Top-200;
}
sizeform=1;
Button10->Enabled = false;
Button9->Enabled = true;
Button8->Enabled = true;
RichEdit1->Clear();

Form7->Close();
Form7->RichEdit1->Visible == false;
Form7->RichEdit2->Visible == false;
Form7->Button4->Visible = false;
Form7->Button3->Visible = false;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;

    if(FileExists(s3+sgame+"autoexec.cfg") != true)
      {
     if(Form1->lang2 == 1)
       RichEdit1->Lines->Add("File autoexec.cfg could not be found at path "+s3+sgame+"autoexec.cfg");
     if(Form1->lang2 == 0)
      RichEdit1->Lines->Add("Не найден искомый файл "+s3+sgame+"autoexec.cfg");
      }
     else
      {
      RichEdit1->Lines->LoadFromFile(s3+sgame+"autoexec.cfg");
      statusop = 1;
      currentcfg = s3+sgame+"autoexec.cfg";
      }
      }
   }
 }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{

if(Edit2->Text == ""){
   if(Form1->lang2 == 1)
  ShowMessage("Do not chosen right path to srcds.exe!");
   if(Form1->lang2 == 0)
  ShowMessage("Не выбран путь к файлу srcds.exe!");
  }
  else
   {
     if(game->Text == "")
     {
     if(Form1->lang2 == 1)
       ShowMessage("Select game!");
     if(Form1->lang2 == 0)
       ShowMessage("Выбирите игру!");
     }
      else
      {
      String s3;
      s3 = Edit2->Text;
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     s3.Delete(s3.Length(),1);
     if(game->ItemIndex != 4)
     s3.Delete(s3.Length(),1);
       String sgame;
        if(game->ItemIndex == 0)
        sgame = "\\tf\\cfg\\";
        if(game->ItemIndex == 1)
        sgame = "\\cstrike\\cfg\\";
        if(game->ItemIndex == 2)
        sgame = "\\hl2mp\\cfg\\";
        if(game->ItemIndex == 3)
        sgame = "\\dod\\cfg\\";
        if(game->ItemIndex == 4)
        sgame = "\\cstrike\\";
        if(game->ItemIndex == 5)
        sgame = "\\left4dead\\cfg\\";
        if(game->ItemIndex == 6)
        sgame = "\\garrysmod\\cfg\\";
        if(game->ItemIndex == 7)
        sgame = "\\insurgency\\cfg\\";
        if(game->ItemIndex == 8)
        sgame = "\\zps\\cfg\\";
if(pad->Checked == true)
{
  if(FileExists(s3+sgame+"server.cfg") != true)
  {
  if(Form1->lang2 == 1)
  ShowMessage((AnsiString ("File server.cfg could not be found at path "+s3+sgame+"\\cfg\\mani_server.cfg")).c_str());
  if(Form1->lang2 == 0)
  ShowMessage((AnsiString ("Не найден искомый файл "+s3+sgame+"\\cfg\\mani_server.cfg")).c_str());
  }
  else
  {
  ShellExecute(Handle,NULL,"notepad",(AnsiString (s3+sgame+"\\cfg\\mani_server.cfg")).c_str(),NULL, SW_RESTORE);

     if(sizeform == 1)
    {
Form1->Height = Form1->Height-360;
Form1->Top = Form1->Top+200;
RichEdit1->Clear();
sizeform = 0;
Button10->Enabled = true;
Button9->Enabled = true;
Button8->Enabled = true;
Form7->Close();
Form7->RichEdit2->Visible = false;
Form7->RichEdit1->Visible = false;
Form7->Button4->Visible = false;
Form7->Button3->Visible = false;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;
statusop = 0;
    }
  }
}
else
 {
if(sizeform == 0)
{
Form1->Height = Form1->Height+360;
Form1->Top = Form1->Top-200;
}
sizeform=1;
Button9->Enabled = false;
Button8->Enabled = true;
Button10->Enabled = true;
RichEdit1->Clear();

if(Form1->lang2 == 0){
Form7->Show();
Form7->Left = 0;
Form7->Top = 0;
Form7->RichEdit2->Visible = true;
Form7->Button4->Visible = true;
Form7->Button3->Visible = true;
Form7->Button2->Visible = false;
Form7->Button1->Visible = false;
}

    if(FileExists(s3+sgame+"mani_server.cfg") != true)
      {
     if(Form1->lang2 == 1)
       RichEdit1->Lines->Add("File mani_server.cfg could not be found at path "+s3+sgame+"mani_server.cfg");
     if(Form1->lang2 == 0)
      RichEdit1->Lines->Add("Не найден искомый файл "+s3+sgame+"mani_server.cfg");
      }
     else
      {
      RichEdit1->Lines->LoadFromFile(s3+sgame+"mani_server.cfg");
      currentcfg = s3+sgame+"mani_server.cfg";
      statusop = 1;
      }
      }
   }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
if(statusop == 1)
{
 RichEdit1->Lines->SaveToFile(currentcfg);

  if(Form1->lang2 == 1)
   ShowMessage("Changes saved");
  if(Form1->lang2 == 0)
   ShowMessage("Изменения сохранены");
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
if(CheckBox2->Checked == true)
 {
 RadioGroup7->Enabled = false;
 RadioGroup7->ItemIndex = 1;
 }
else
 {
 RadioGroup7->Enabled = true;
 }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Edit8Change(TObject *Sender)
{
  if(tyi == 0){
  if(Form1->lang2 == 1)
   ShowMessage("Enter ip adress not necessarily if  you have 1 network.");
  if(Form1->lang2 == 0)
   ShowMessage("Если у вас одна сеть, указывать ip необязательно.");
   }
 tyi++;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
close++;
if(close == 3)
 {
 cl = 2;
 Form1->Close();
 cl = 0;
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::language()
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));

//**********************************
// Menu for Form1
//**********************************

String MenuH1;
MenuH1 = ini->ReadString("Form","MenuH1","");
N1->Caption = MenuH1;

String MenuH2;
MenuH2 = ini->ReadString("Form","MenuH2","");
N2->Caption = MenuH2;

String MenuH3;
MenuH3 = ini->ReadString("Form","MenuH3","");
N4->Caption = MenuH3;

String MenuB1;
MenuB1 = ini->ReadString("Form","MenuB1","");
N3->Caption = MenuB1;

String MenuB2;
MenuB2 = ini->ReadString("Form","MenuB2","");
N5->Caption = MenuB2;

String MenuB3;
MenuB3 = ini->ReadString("Form","MenuB3","");
sev->Caption = MenuB3;

String MenuB4;
MenuB4 = ini->ReadString("Form","MenuB4","");
autoservr->Caption = MenuB4;

String MenuB5;
MenuB5 = ini->ReadString("Form","MenuB5","");
auturan->Caption = MenuB5;

String MenuB6;
MenuB6 = ini->ReadString("Form","MenuB6","");
N6->Caption = MenuB6;

String MenuB7;
MenuB7 = ini->ReadString("Form","MenuB7","");
N8->Caption = MenuB7;

String MenuB8;
MenuB8 = ini->ReadString("Form","MenuB8","");
N20->Caption = MenuB8;

String MenuB9;
MenuB9 = ini->ReadString("Form","MenuB9","");
N12->Caption = MenuB9;

String MenuB10;
MenuB10 = ini->ReadString("Form","MenuB10","");
Clienttxt1->Caption = MenuB10;

String MenuB11;
MenuB11 = ini->ReadString("Form","MenuB11","");
maplisttxt1->Caption = MenuB11;

String MenuB12;
MenuB12 = ini->ReadString("Form","MenuB12","");
SRCDSCFGCreator1->Caption = MenuB12;

String MenuB13;
MenuB13 = ini->ReadString("Form","MenuB13","");
pad->Caption = MenuB13;

//*********************************
// TrayIcon1
//*********************************
String MenuT1;
MenuT1 = ini->ReadString("Form","MenuT1","");
N11->Caption = MenuT1;

String MenuT2;
MenuT2 = ini->ReadString("Form","MenuT2","");
N7->Caption = MenuT2;

String MenuT3;
MenuT3 = ini->ReadString("Form","MenuT3","");
N17->Caption = MenuT3;

String MenuT4;
MenuT4 = ini->ReadString("Form","MenuT4","");
N22->Caption = MenuT4;

String MenuT5;
MenuT5 = ini->ReadString("Form","MenuT5","");
N28->Caption = MenuT5;

String MenuT6;
MenuT6 = ini->ReadString("Form","MenuT6","");
N16->Caption = MenuT6;

String MenuT7;
MenuT7 = ini->ReadString("Form","MenuT7","");
N26->Caption = MenuT7;

String MenuT8;
MenuT8 = ini->ReadString("Form","MenuT8","");
N27->Caption = MenuT8;

String MenuT9;
MenuT9 = ini->ReadString("Form","MenuT9","");
N25->Caption = MenuT9;

//*********************************
// Form1
//*********************************
String F1Caption1;
F1Caption1 = ini->ReadString("Form","F1Caption1","");
Button5->Caption = F1Caption1;

String F1Caption2;
F1Caption2 = ini->ReadString("Form","F1Caption2","");
Button7->Caption = F1Caption2;

String F1Caption3;
F1Caption3 = ini->ReadString("Form","F1Caption3","");
RUN->Caption = F1Caption3;

String F1Caption4;
F1Caption4 = ini->ReadString("Form","F1Caption4","");
Button2->Caption = F1Caption4;

String F1Caption5;
F1Caption5 = ini->ReadString("Form","F1Caption5","");
Button3->Caption = F1Caption5;

String F1Caption6;
F1Caption6 = ini->ReadString("Form","F1Caption6","");
serverstats->Caption = F1Caption6;

String F1Caption7;
F1Caption7 = ini->ReadString("Form","F1Caption7","");
CheckBox3->Caption = F1Caption7;

String F1Caption8;
F1Caption8 = ini->ReadString("Form","F1Caption8","");
Label8->Caption = F1Caption8;

String F1Caption9;
F1Caption9 = ini->ReadString("Form","F1Caption9","");
Button1->Caption = F1Caption9;

String F1Caption10;
F1Caption10 = ini->ReadString("Form","F1Caption10","");
Label9->Caption = F1Caption10;

String F1Caption11;
F1Caption11 = ini->ReadString("Form","F1Caption11","");
Label10->Caption = F1Caption11;
Label10->Top = 138;
Label2->Visible = false;

String F1Caption12;
F1Caption12 = ini->ReadString("Form","F1Caption12","");
Button4->Caption = F1Caption12;

String F1Caption13;
F1Caption13 = ini->ReadString("Form","F1Caption13","");
N29->Caption = F1Caption13;

String F1Caption13A;
F1Caption13A = ini->ReadString("Form","F1Caption13A","");
N30->Caption = F1Caption13A;

String F1Caption14;
F1Caption14 = ini->ReadString("Form","F1Caption14","");
Label12->Caption = F1Caption14;

String F1Caption15;
F1Caption15 = ini->ReadString("Form","F1Caption15","");
RadioGroup7->Caption = F1Caption15;

String F1Caption16;
F1Caption16 = ini->ReadString("Form","F1Caption16","");
RadioGroup7->Items->Strings[0]  =  F1Caption16;

String F1Caption17;
F1Caption17 = ini->ReadString("Form","F1Caption17","");
RadioGroup7->Items->Strings[1] =  F1Caption17;

String F1Caption18;
F1Caption18 = ini->ReadString("Form","F1Caption18","");
RadioGroup7->Items->Strings[2] =  F1Caption18;

String F1Caption19;
F1Caption19 = ini->ReadString("Form","F1Caption19","");
RadioGroup10->Caption =  F1Caption19;

String F1Caption20;
F1Caption20 = ini->ReadString("Form","F1Caption20","");
RadioGroup9->Caption =  F1Caption20;

String F1Caption21;
F1Caption21 = ini->ReadString("Form","F1Caption21","");
RadioGroup11->Caption =  F1Caption21;

String F1Caption22;
F1Caption22 = ini->ReadString("Form","F1Caption22","");
Label3->Caption =  F1Caption22;
Label3->Left = 150;

String F1Caption23;
F1Caption23 = ini->ReadString("Form","F1Caption23","");
Button8->Caption =  F1Caption23;

String F1Caption24;
F1Caption24 = ini->ReadString("Form","F1Caption24","");
Button10->Caption =  F1Caption24;

String F1Caption25;
F1Caption25 = ini->ReadString("Form","F1Caption25","");
Button9->Caption =  F1Caption25;

String F1Caption26;
F1Caption26 = ini->ReadString("Form","F1Caption26","");
Button11->Caption =  F1Caption26;

String F1Caption27;
F1Caption27 = ini->ReadString("Form","F1Caption27","");
Button13->Caption =  F1Caption27;

String F1Caption28;
F1Caption28 = ini->ReadString("Form","F1Caption28","");
Button12->Caption =  F1Caption28;

String F1Caption29;
F1Caption29 = ini->ReadString("Form","F1Caption29","");
Button14->Caption =  F1Caption29;
Edit3->Text = "";

String F1Caption30;
F1Caption30 = ini->ReadString("Form","F1Caption30","");
Label4->Caption =  F1Caption30;

String F1Caption31;
F1Caption31 = ini->ReadString("Form","F1Caption31","");
Label5->Caption =  F1Caption31;

String F1Caption32;
F1Caption32 = ini->ReadString("Form","F1Caption32","");
Label6->Caption =  F1Caption32;

String F1Caption33;
F1Caption33 = ini->ReadString("Form","F1Caption33","");
CheckBox2->Caption =  F1Caption33;

String F1Caption34;
F1Caption34 = ini->ReadString("Form","F1Caption34","");
sLabel2->Caption =  F1Caption34;

String F1Caption35;
F1Caption35 = ini->ReadString("Form","F1Caption35","");
OpenDialog1->Title =  F1Caption35;

String F1Caption36;
F1Caption36 = ini->ReadString("Form","F1Caption36","");
OpenDialog2->Title =  F1Caption36;

String F1Caption37;
F1Caption37 = ini->ReadString("Form","F1Caption37","");
OpenDialog3->Title =  F1Caption37;

String F1Caption38;
F1Caption38 = ini->ReadString("Form","F1Caption38","");
CheckBox4->Caption = F1Caption38;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button15Click(TObject *Sender)
{
Form1->TrayIcon1->Minimize();
Timer2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
 if(tyi < 1){
 TIniFile *ini;
ini = new TIniFile(ChangeFileExt("./settings.ini", ".INI" ));
String lang;

lang = ini->ReadString("SSG","lang","");
if(lang == 1){
En->Checked = true;
Ru->Checked = false;
lang2=1;
}
if(lang == 0){
Ru->Checked = true;
En->Checked = false;
lang2=0;
}
delete ini;

if(En->Checked == true)
{
En->Checked = true;
Ru->Checked = false;
language();
}
else{
Ru->Checked = true;
En->Checked = false;
}

 TrayIcon1->Restore();
 Form1->Repaint();
 tyi++;
 }
else
{
tyi = 0;
Timer2->Enabled = false;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N20Click(TObject *Sender)
{
if(Form1->lang2 == 1)
ShellExecute(0,0,"./FAQ/helpEn.html",0,0, SW_SHOWDEFAULT);
if(Form1->lang2 == 0)
ShellExecute(0,0,"./FAQ/helpRu.html",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormActivate(TObject *Sender)
{
OneSt();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::OneSt()
{
TIniFile *ini3;
ini3 = new TIniFile(ChangeFileExt("./settings.ini", ".INI" ));
String OneSt;
OneSt = ini3->ReadString("SSG","OneSt","");
if(OneSt == 0)
Form8->Show();
delete ini3;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Clienttxt1Click(TObject *Sender)
{
Form5->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HLSW1Click(TObject *Sender)
{
// STARTUPINFO startupInfo = {0};
// startupInfo.cb = sizeof(startupInfo);
// PROCESS_INFORMATION processInformation;
// CreateProcess(NULL,(AnsiString (ExtractFilePath(Application->ExeName)+"tools/HLSW/hlsw.exe")).c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInformation);

// WinExec("./tools/HLSW/hlsw.exe", 0);
// ShellExecute(Handle, "open",(AnsiString (ExtractFilePath(Application->ExeName)+"tools/HLSW/hlsw.exe")).c_str(), NULL, NULL, SW_SHOW);
// WinExec("tools\\HLSW\\hlsw.exe",SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::maplisttxt1Click(TObject *Sender)
{
ShellExecute(NULL, "open", "./tools/maplist_creator/Maplist creator.exe", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SRCDSCFGCreator1Click(TObject *Sender)
{
ShellExecute(NULL, "open", "./tools/SRCDS CFG Creator.exe", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::padClick(TObject *Sender)
{
if (pad->Checked == false)
 pad->Checked = true;
else
 pad->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Steam1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Steam (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Vista1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Vista (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WMP111Click(TObject *Sender)
{
sSkinManager1->SkinName = "WMP 2008 (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Cold1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Cold (internal)";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Beijing1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Beijing (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Neutral1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Neutral4 (internal)";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NextAlpha1Click(TObject *Sender)
{
sSkinManager1->SkinName = "NextAlpha (internal)";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Officeblack1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Office2007 Black (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Retro1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Retro (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WLM1Click(TObject *Sender)
{
sSkinManager1->SkinName = "WLM (internal)";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Winter1Click(TObject *Sender)
{
sSkinManager1->SkinName = "Winter2003 (internal)";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N29Click(TObject *Sender)
{
if(sSaveDialog1->Execute() == true)
{
AnsiString saveopt;
saveopt = sSaveDialog1->FileName;

struct info{
char *field1;
};


if(saveopt != "")
{
//    saveopt.Delete(saveopt.Length(),1);

struct info Field;
Field.field1=strtok((AnsiString(saveopt)).c_str(),".");

saveopt = Field.field1;


if(Application->MessageBox(
(AnsiString(saveopt+".ini")).c_str(),
"Save?",
MB_YESNO + MB_ICONQUESTION) == ID_YES)

 {
TIniFile *Ini = new TIniFile(saveopt+".ini");

// String MyPath;
// MyPath = ExtractFilePath(Application->ExeName);
// WritePrivateProfileSection("Options","",(AnsiString (MyPath+"settings.ini")).c_str());
// WritePrivateProfileSection("Menu","",(AnsiString (MyPath+"settings.ini")).c_str());

String file3;
file3 = Edit2->Text;
Ini->WriteString("srcds", "filedir", file3);

String tickrate;
if(RadioGroup12->ItemIndex == -1)
tickrate = -1;
if(RadioGroup12->ItemIndex == 0)
tickrate = 0;
if(RadioGroup12->ItemIndex == 1)
tickrate = 1;
if(RadioGroup12->ItemIndex == 2)
tickrate = 2;
Ini->WriteString("Options","tickrate", tickrate);
// WritePrivateProfileString("Options","tickrate",(AnsiString () +tickrate).c_str(),"./settings.ini");


String console;
if(RadioGroup11->ItemIndex == -1)
console = -1;
if(RadioGroup11->ItemIndex == 0)
console = 0;
if(RadioGroup11->ItemIndex == 1)
console = 1;
Ini->WriteString("Options","console", console);
// WritePrivateProfileString("Options","console",(AnsiString () +console).c_str(),"./settings.ini");

String LAN;
if(RadioGroup10->ItemIndex == -1)
LAN = -1;
if(RadioGroup10->ItemIndex == 0)
LAN = 0;
if(RadioGroup10->ItemIndex == 1)
LAN = 1;
Ini->WriteString("Options","LAN", LAN);
// WritePrivateProfileString("Options","LAN",(AnsiString () +LAN).c_str(),"./settings.ini");

String bot;
if(RadioGroup9->ItemIndex == -1)
bot = -1;
if(RadioGroup9->ItemIndex == 0)
bot = 0;
if(RadioGroup9->ItemIndex == 1)
bot = 1;
Ini->WriteString("Options","bot", bot);
// WritePrivateProfileString("Options","bot",(AnsiString () +bot).c_str(),"./settings.ini");

String VAC2;
if(RadioGroup8->ItemIndex == -1)
VAC2 = -1;
if(RadioGroup8->ItemIndex == 0)
VAC2 = 0;
if(RadioGroup8->ItemIndex == 1)
VAC2 = 1;
Ini->WriteString("Options","VAC2", VAC2);
// WritePrivateProfileString("Options","VAC2",(AnsiString () +VAC2).c_str(),"./settings.ini");

String ProcesClass;
if(RadioGroup7->ItemIndex == -1)
ProcesClass = -1;
if(RadioGroup7->ItemIndex == 0)
ProcesClass = 0;
if(RadioGroup7->ItemIndex == 1)
ProcesClass = 1;
if(RadioGroup7->ItemIndex == 2)
ProcesClass = 2;
Ini->WriteString("Options","ProcesClass", ProcesClass);
// WritePrivateProfileString("Options","ProcesClass",(AnsiString () +ProcesClass).c_str(),"./settings.ini");

String games;
if(game->ItemIndex == -1)
games = -1;
if(game->ItemIndex == 0)
games = 0;
if(game->ItemIndex == 1)
games = 1;
if(game->ItemIndex == 2)
games = 2;
if(game->ItemIndex == 3)
games = 3;
if(game->ItemIndex == 4)
games = 4;
if(game->ItemIndex == 5)
games = 5;
if(game->ItemIndex == 6)
games = 6;
if(game->ItemIndex == 7)
games = 7;
Ini->WriteString("Options","games", games);
// WritePrivateProfileString("Options","games",(AnsiString () +games).c_str(),"./settings.ini");

String PORT;
PORT = Edit1->Text;
Ini->WriteString("Options","PORT", PORT);
// WritePrivateProfileString("Options","PORT",(AnsiString () +PORT).c_str(),"./settings.ini");

String update;
if(CheckBox3->Checked == true)
update = 1;
if(CheckBox3->Checked == false)
update = 0;
Ini->WriteString("Options","update", update);
// WritePrivateProfileString("Options","update",(AnsiString () +update).c_str(),"./settings.ini");


String chmap;
if(CheckBox4->Checked == true)
chmap = 1;
if(CheckBox4->Checked == false)
chmap = 0;
Ini->WriteString("Options","chmap", chmap);


String NAME;
NAME = Edit6->Text;
Ini->WriteString("Options","NAME", NAME);
// WritePrivateProfileString("Options","NAME",(AnsiString () +NAME).c_str(),"./settings.ini");

String MaxPlaer;
MaxPlaer = Edit7->Text;
Ini->WriteString("Options","MaxPlaer", MaxPlaer);
// WritePrivateProfileString("Options","MaxPlaer",(AnsiString () +MaxPlaer).c_str(),"./settings.ini");

String IPADRESS;
IPADRESS = Edit8->Text;
Ini->WriteString("Options","IPADRESS", IPADRESS);
// WritePrivateProfileString("Options","IPADRESS",(AnsiString () +IPADRESS).c_str(),"./settings.ini");

String MAP;
MAP = Edit9->Text;
Ini->WriteString("Options","MAP", MAP);
// WritePrivateProfileString("Options","MAP",(AnsiString () +MAP).c_str(),"./settings.ini");

String AHTER;
AHTER = Ater->Text;
Ini->WriteString("Options","AHTER", AHTER);
// WritePrivateProfileString("Options","AHTER",(AnsiString () +AHTER).c_str(),"./settings.ini");

delete Ini;
}
}
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N30Click(TObject *Sender)
{

sOpenDialog1->Execute();
AnsiString loadop;
loadop = sOpenDialog1->FileName;

if(loadop != "")
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt((AnsiString (loadop)).c_str(), ".INI" ));

N25->Checked = true;

String tickrate;
tickrate = ini->ReadString("Options","tickrate","");
if(tickrate == -1)
RadioGroup12->ItemIndex = -1;
if(tickrate == 0)
RadioGroup12->ItemIndex = 0;
if(tickrate == 1)
RadioGroup12->ItemIndex = 1;
if(tickrate == 2)
RadioGroup12->ItemIndex = 2;


String console;
console = ini->ReadString("Options","console","");
if(console == -1)
RadioGroup11->ItemIndex = -1;
if(console == 0)
RadioGroup11->ItemIndex = 0;
if(console == 1)
RadioGroup11->ItemIndex = 1;

String LAN;
LAN = ini->ReadString("Options","LAN","");
if(LAN == -1)
RadioGroup10->ItemIndex = -1;
if(LAN == 0)
RadioGroup10->ItemIndex = 0;
if(LAN == 1)
RadioGroup10->ItemIndex = 1;

String bot;
bot = ini->ReadString("Options","bot","");
if(bot == -1)
RadioGroup9->ItemIndex = -1;
if(bot == 0)
RadioGroup9->ItemIndex = 0;
if(bot == 1)
RadioGroup9->ItemIndex = 1;

String VAC2;
VAC2 = ini->ReadString("Options","VAC2","");
if(VAC2 == -1)
RadioGroup8->ItemIndex = -1;
if(VAC2 == 0)
RadioGroup8->ItemIndex = 0;
if(VAC2 == 1)
RadioGroup8->ItemIndex = 1;

String ProcesClass;
ProcesClass = ini->ReadString("Options","ProcesClass","");
if(ProcesClass == -1)
RadioGroup7->ItemIndex = -1;
if(ProcesClass == 0)
RadioGroup7->ItemIndex = 0;
if(ProcesClass == 1)
RadioGroup7->ItemIndex = 1;
if(ProcesClass == 2)
RadioGroup7->ItemIndex = 2;

String games;
games = ini->ReadString("Options","games","");
if(games == -1)
game->ItemIndex = -1;
if(games == 0)
game->ItemIndex = 0;
if(games == 1)
game->ItemIndex = 1;
if(games == 2)
game->ItemIndex = 2;
if(games == 3)
game->ItemIndex = 3;
if(games == 4)
game->ItemIndex = 4;
if(games == 5)
game->ItemIndex = 5;
if(games == 6)
game->ItemIndex = 6;
if(games == 7)
game->ItemIndex = 7;

String PORT;
PORT = ini->ReadString("Options","PORT","");
Edit1->Text = PORT;

String AHTER;
AHTER = ini->ReadString("Options","AHTER","");
Ater->Text = AHTER;

String update;
update = ini->ReadString("Options","update","");
if(update == 1)
CheckBox3->Checked = true;
if(update == 0)
CheckBox3->Checked = false;

String chmap;
chmap = ini->ReadString("Options","chmap","");
if(chmap == 1)
CheckBox4->Checked = true;
if(chmap == 0)
CheckBox4->Checked = false;

String statusserver;
statusserver = ini->ReadString("Options","statusserver","");
if(statusserver == 1)
CheckBox2->Checked = true;
if(statusserver == 0)
CheckBox2->Checked = false;

if(CheckBox2->Checked == true)
 {
 RadioGroup7->Enabled = false;
 RadioGroup7->ItemIndex = 1;
 }


String NAME;
NAME = ini->ReadString("Options","NAME","");
Edit6->Text = NAME;

String MaxPlaer;
MaxPlaer = ini->ReadString("Options","MaxPlaer","");
Edit7->Text = MaxPlaer;

String IPADRESS;
IPADRESS = ini->ReadString("Options","IPADRESS","");
if(IPADRESS != "")
tyi = 1;
Edit8->Text = IPADRESS;

String MAP;
MAP = ini->ReadString("Options","MAP","");
Edit9->Text = MAP;

AnsiString file4;
file4 = ini->ReadString("srcds", "filedir","");
Edit2->Text = file4;

delete ini;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Chatonlineru1Click(TObject *Sender)
{
Form9->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Chatonline1Click(TObject *Sender)
{
Form9->Show();
}
//---------------------------------------------------------------------------


