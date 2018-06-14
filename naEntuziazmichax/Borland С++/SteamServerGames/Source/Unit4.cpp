//---------------------------------------------------------------------------
#include <FileCtrl.hpp>
#include <vcl.h>
#pragma hdrstop
#include <fstream.h>
#include <IniFiles.hpp>
#include <Sysutils.hpp>
#include "Unit1.h"
#include "Unit4.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sDialogs"
#pragma link "sComboBox"
#pragma link "sComboBoxes"
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label3Click(TObject *Sender)
{
ShellExecute(0,0,"http://mani-admin-plugin.com/mani_admin_plugin/v1_2_beta_s/mani_admin_plugin_v1_2_beta_s.zip",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label4Click(TObject *Sender)
{
ShellExecute(0,0,"http://mani-admin-plugin.com/mani_admin_plugin/v1_2_beta_s/mani_admin_plugin_v1_2_beta_s_orange.zip",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label5Click(TObject *Sender)
{
ShellExecute(0,0,"http://mani-admin-plugin.com/mani_admin_plugin/vdftool/CreateVDF.zip",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label6Click(TObject *Sender)
{
ShellExecute(0,0,"http://www.sourcemm.net/?go=downloads",0,0, SW_SHOWDEFAULT);        
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label7Click(TObject *Sender)
{
ShellExecute(0,0,"http://www.sourcemod.net/newstats.php",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label9Click(TObject *Sender)
{
ShellExecute(0,0,"http://mattie.info/cs/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label10Click(TObject *Sender)
{
ShellExecute(0,0,"http://www.bailopan.net/cssdm/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label11Click(TObject *Sender)
{
ShellExecute(0,0,"http://www.zombiemod.com/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Label2Click(TObject *Sender)
{
ShellExecute(0,0,"http://mani-admin-plugin.com/",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button3Click(TObject *Sender)
{
Form5->ShowModal();        
}
//---------------------------------------------------------------------------

bool __fastcall MyCopy(AnsiString From, AnsiString To)
{
     SHFILEOPSTRUCT s;
     s.hwnd = 0;
     s.pFrom = From.c_str();
     s.pTo = To.c_str();
     s.wFunc = FO_COPY;
     s.fFlags = FOF_ALLOWUNDO + FOF_NOCONFIRMATION;
     if(!SHFileOperation(&s))
          return true;
     else
          return false;

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
if(Edit2->Text == ""){
  if(Form1->lang2 == 1)
ShowMessage("Choose the path of a new server!");
  if(Form1->lang2 == 0)
ShowMessage("Выбирите путь нового сервера!");
}
else
{
if(game->Text == "")
{
  if(Form1->lang2 == 1)
ShowMessage("Choose game!");
  if(Form1->lang2 == 0)
ShowMessage("Выбирите игру!");
}
else
{
const unsigned int INTERVAL2 = 500;
String dirr;
dirr = Edit2->Text;

MyCopy("./server",dirr);

Sleep(INTERVAL2);

String sgame;
String games;
if(game->ItemIndex == 0)
{
sgame = "tfupdate.bat";
games = "tf";
}
if(game->ItemIndex == 1)
{
sgame = "cssupdate.bat";
games = "\"Counter-Strike Source\"";
}
if(game->ItemIndex == 2)
{
games = "hl2mp";
sgame = "hl2mpupdate.bat";
}
if(game->ItemIndex == 3)
{
sgame = "dodupdate.bat";
games = "dods";
}
if(game->ItemIndex == 4)
{
sgame = "csupdate.bat";
games = "cstrike";
}
if(game->ItemIndex == 5)
{
sgame = "l4dupdate.bat";
games = "left4dead";
}
if(game->ItemIndex == 6)
{
sgame = "GModupdate.bat";
games = "garrysmod";
}
if(game->ItemIndex == 7)
{
sgame = "InsurgencyUpdate.bat";
games = "insurgency";
}
if(game->ItemIndex == 8)
{
sgame = "ZpsUpdate.bat";
games = "zps";
}


STARTUPINFO startupInfo = {0};
startupInfo.cb = sizeof(startupInfo);
PROCESS_INFORMATION processInformation;
create();
if(game->ItemIndex == 4)
CreateProcess(NULL,(AnsiString (dirr+"\\server\\SHL1\\"+sgame)).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
else
CreateProcess(NULL,(AnsiString (dirr+"\\server\\SHL2\\"+sgame)).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
ShowMessage("Началась закачка сервера, дождитесь закрытия чёрного окна, это займёт много времени.");

if(FileExists(dirr+"/server/SHL2/srcds.exe") == false && FileExists(dirr+"/server/SHL2/orangebox/srcds.exe") == false){
if(game->ItemIndex == 4){
DeleteFile(dirr+"/server/SHL2/ClientRegistry.blob");
DeleteFile(dirr+"/server/SHL2/InstallRecord.blob");
DeleteFile(dirr+"/server/SHL2/HldsUpdateTool.exe");
DeleteFile(dirr+"/server/SHL2/HldsUpdateTool_25.mst");
DeleteFile(dirr+"/server/SHL2/HldsUpdateTool_32.mst");
DeleteFile(dirr+"/server/SHL2/HldsUpdateTool_35.mst");
DeleteFile(dirr+"/server/SHL2/HldsUpdateTool_25.pkg");
DeleteFile(dirr+"/server/SHL2/hlds_steamgames.vdf");
 RemoveDir(dirr+"/server/SHL2");
 }
}

if(FileExists(dirr+"/server/SHL1/hlds.exe") == false)
{
if(game->ItemIndex != 4)
 {
DeleteFile(dirr+"/server/SHL1/ClientRegistry.blob");
DeleteFile(dirr+"/server/SHL1/InstallRecord.blob");
DeleteFile(dirr+"/server/SHL1/HldsUpdateTool.exe");
DeleteFile(dirr+"/server/SHL1/HldsUpdateTool_32.mst");
DeleteFile(dirr+"/server/SHL1/HldsUpdateTool_35.mst");
DeleteFile(dirr+"/server/SHL1/HldsUpdateTool_32.pkg");
  RemoveDir(dirr+"/server/SHL1");
 }
}

}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button5Click(TObject *Sender)
{
AnsiString dir;
// SelectDirectory("Выберите паку в которой хотите создать сервер",WideString("Desktop"),dir);
if(sPathDialog1->Execute())
{
dir = sPathDialog1->Path;
Edit2->Text = dir;
if(Edit2->Text != "")
 {
  if(Form1->lang2 == 1)
ShowMessage("Server will be created at "+dir+"\\server\\. CAUTION: In the way the new server should not be gaps, otherwise the program will give an error!");
  if(Form1->lang2 == 0)
ShowMessage("Сервер будет создан по адресу "+dir+"\\server\\. ВНИМАНИЕ! в адресе не должно быть пробелов, в противном случае при создании сервера будет ошибка!");


//__int64 FreeSpace = DiskFree(disk2);
//ShowMessage(FreeSpace);
 }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{
ShellExecute(0,0, "./FAQ/Documentation(ru).html",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::create()
{
String dirr;
dirr = Edit2->Text;

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
sgame = "ZpsUpdate";
games = "zps";
}
// ofstream fo;
// fo.open((AnsiString (dirr+"/server/")+sgame+".bat").c_str());
// fo<<"start /wait "<<(AnsiString (dirr+"/server/")).c_str()<<"hldsupdatetool.exe"<<endl;
// fo<<"start /wait "<<(AnsiString (dirr+"/server/")).c_str()<<"hldsupdatetool.exe "<<"-command update -game "<<(AnsiString (games)).c_str()<<" -dir ."<<endl<<"exit";
// fo.close();

TStringList *List = new TStringList;
if(game->ItemIndex == 4)
{
List->Add((AnsiString ("start /wait "+dirr+"\\server\\SHL1\\hldsupdatetool.exe")).c_str());
List->Add((AnsiString ("start "+dirr+"\\server\\SHL1\\hldsupdatetool.exe -command update -game "+games+" -dir "+dirr+"\\server\\SHL1")).c_str());
}
else
{
List->Add((AnsiString ("start /wait "+dirr+"\\server\\SHL2\\hldsupdatetool.exe")).c_str());
List->Add((AnsiString ("start "+dirr+"\\server\\SHL2\\hldsupdatetool.exe -command update -game "+games+" -dir "+dirr+"\\server\\SHL2")).c_str());
}
List->Add("exit");
if(game->ItemIndex == 4)
{
List->SaveToFile((AnsiString (dirr+"\\server\\SHL1\\")+sgame+".bat").c_str());
List->Clear();
List->LoadFromFile((AnsiString (dirr+"\\server\\SHL1\\")+sgame+".bat").c_str());
}
else
{
List->SaveToFile((AnsiString (dirr+"\\server\\SHL2\\")+sgame+".bat").c_str());
List->Clear();
List->LoadFromFile((AnsiString (dirr+"\\server\\SHL2\\")+sgame+".bat").c_str());
}
List[3];//-это строка
List->Count;//-это кол-во строк
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{
if(Form1->lang2 == 1)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F4Caption1;
F4Caption1 = ini->ReadString("Form","F4Caption1","");
Label1->Caption = F4Caption1;

String F4Caption2;
F4Caption2 = ini->ReadString("Form","F4Caption2","");
Label3->Caption = F4Caption2;

String F4Caption3;
F4Caption3 = ini->ReadString("Form","F4Caption3","");
Label4->Caption = F4Caption3;

String F4Caption4;
F4Caption4 = ini->ReadString("Form","F4Caption4","");
Label5->Caption = F4Caption4;

String F4Caption5;
F4Caption5 = ini->ReadString("Form","F4Caption5","");
Label7->Caption = F4Caption5;

String F4Caption6;
F4Caption6 = ini->ReadString("Form","F4Caption6","");
Label9->Caption = F4Caption6;

String F4Caption8;
F4Caption8 = ini->ReadString("Form","F4Caption8","");
Button1->Caption = F4Caption8;

String F4Caption9;
F4Caption9 = ini->ReadString("Form","F4Caption9","");
Button5->Caption = F4Caption9;

String F4Caption10;
F4Caption10 = ini->ReadString("Form","F4Caption10","");
GroupBox1->Caption = F4Caption10;

String F4Caption11;
F4Caption11 = ini->ReadString("Form","F4Caption11","");
Form4->Caption = F4Caption11;

String F4Caption12;
F4Caption12 = ini->ReadString("Form","F4Caption12","");
Label8->Caption = F4Caption12;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Label8Click(TObject *Sender)
{
ShellExecute(0,0,"http://hlsw.net/?page=download&category=hlsw",0,0, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------



