//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <fstream.h>
#include "Unit5.h"
#include "Unit1.h"
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sLabel"
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1Click(TObject *Sender)
{
Form5->Perform(WM_CLOSE,0,0);
}
//---------------------------------------------------------------------------


void __fastcall TForm5::Button2Click(TObject *Sender)
{
  if(Form1->lang2 == 1)
ShowMessage("Save in \ cstrike \ cfg \ mani_admin_plugin, administrator  was created with full rights and immunity, for creating and editing admins use the menu in the game.");
  if(Form1->lang2 == 0)
ShowMessage("—охран€ть в \cstrike\cfg\mani_admin_plugin, Ётот админ был создан с полными правами и имунитетом, дл€ создани€ и редактировани€ админов воспользуйтесь меню в игре (команда admin в консоле).");

if (SaveDialog1->Execute())
{
// Generate(SaveDialog1->FileName);

TStringList *List = new TStringList;
List->Add("\"clients.txt\"");
List->Add("{");
List->Add("\"version\" \"1\"");
List->Add("");
List->Add("// This key group lists all your client players");
List->Add("\"players\"");
List->Add("{");
List->Add("// This must be a unique client name");
List->Add((AnsiString ("\""+Name->Text+"\"")).c_str());
List->Add("{");
List->Add("// Client real name");
List->Add((AnsiString ("\"name\" \""+Name->Text+"\"")).c_str());
if(Steamid->Text != "")
{
List->Add("// Steam ID for client");
List->Add((AnsiString ("\"steam\" \""+Steamid->Text+"\"")).c_str());
}
if(idip->Text != "")
{
List->Add("// IP adress for client");
List->Add((AnsiString ("\"ip\" \""+idip->Text+"\"")).c_str());
}
if(Nik->Text != "")
{
List->Add("// Nik name for client");
List->Add((AnsiString ("\"nick\" \""+Nik->Text+"\"")).c_str());
}
if(Pass->Text != "")
{
List->Add("// Pass for client");
List->Add((AnsiString ("\"password\" \""+Pass->Text+"\"")).c_str());
}
List->Add("// These are personal access flags for a player");
List->Add("\"flags\"");
List->Add("{");
List->Add("\"Immunity\"	\"Immunity grav ping afk a b c d e f g h i j k l m n o p q r s\"");
List->Add("\"Immunity\"	\"t u v x y autojoin\"");
List->Add("\"Admin\"	\"q2 q3 grav pban A B C D E F G H I J K L M N O P Q R S T U V\"");
List->Add("\"Admin\"	\"W X Y Z a b c d e f g i j k l m o p q r s t v w x y z client\"");
List->Add("\"Admin\"	\"admin spray\"");
List->Add("}");
List->Add("}");
List->Add("}");
List->Add("");
List->Add("// These are global groups of flags that can be assigned to clients");
List->Add("\"groups\"");
List->Add("{");
List->Add("\"Admin\"");
List->Add("{");
List->Add("\"Admin\"	\"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d\"");
List->Add("\"Admin\"	\"e f g i j k l m o p q r s t v w x y z admin spray grav pban\"");
List->Add("\"Admin\"	\"client\"");
List->Add("}");
List->Add("}");
List->Add(" ");
List->Add("}");
List->SaveToFile(SaveDialog1->FileName+".txt");
List->Clear();
List->LoadFromFile(SaveDialog1->FileName+".txt");
List[44];//-это строка
List->Count;//-это кол-во строк
}
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Generate()
{
//ofstream fo;
// fo.open("./clients.txt");
// fo<<"\"clients.txt\""<<endl;
// fo<<"{"<<endl;
// fo<<"\"version\" \"1\""<<endl;
// fo<<""<<endl;
// fo<<"// This key group lists all your client players"<<endl;...
//fo<<"\"players\""<<endl;
// fo<<"{"<<endl;
// fo<<"// This must be a unique client name"<<endl;
// fo<<"\""<<(Name->Text).c_str()<<"\""<<endl;
// fo<<"{"<<endl;
// fo<<"// Client real name"<<endl;
// fo<<"\"name\" \""<<(Name->Text).c_str()<<"\""<<endl;
// if(Steamid->Text != "")
// {
// fo<<"// Steam ID for client"<<endl;
// fo<<"\"steam\" \""<<(Steamid->Text).c_str()<<"\""<<endl;
// }
// if(idip->Text != "")
// {
// fo<<"// IP adress for client"<<endl;
// fo<<"\"ip\" \""<<(idip->Text).c_str()<<"\""<<endl;
// }
// if(Nik->Text != "")
// {
// fo<<"// Nik name for client"<<endl;
// fo<<"\"nick\" \""<<(Nik->Text).c_str()<<"\""<<endl;
// }
// if(Pass->Text != "")
// {
// fo<<"// Pass for client"<<endl;
// fo<<"\"password\" \""<<(Pass->Text).c_str()<<"\""<<endl;
// }
// fo<<"// These are personal access flags for a player"<<endl;
// fo<<"\"flags\""<<endl;
// fo<<"{"<<endl;
// fo<<"\"Immunity\"	\"Immunity grav ping afk a b c d e f g h i j k l m n o p q r s\""<<endl;
// fo<<"\"Immunity\"	\"t u v x y autojoin\""<<endl;
// fo<<"\"Admin\"	\"q2 q3 grav pban A B C D E F G H I J K L M N O P Q R S T U V\""<<endl;
// fo<<"\"Admin\"	\"W X Y Z a b c d e f g i j k l m o p q r s t v w x y z client\""<<endl;
// fo<<"\"Admin\"	\"admin spray\""<<endl;
// fo<<"}"<<endl;
// fo<<"}"<<endl;
// fo<<"}"<<endl;
// fo<<""<<endl;
// fo<<"// These are global groups of flags that can be assigned to clients"<<endl;
// fo<<"\"groups\""<<endl;
// fo<<"{"<<endl;
// fo<<"\"Admin\""<<endl;
// fo<<"{"<<endl;
// fo<<"\"Admin\"	\"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d\""<<endl;
// fo<<"\"Admin\"	\"e f g i j k l m o p q r s t v w x y z admin spray grav pban\""<<endl;
// fo<<"\"Admin\"	\"client\""<<endl;
// fo<<"}"<<endl;
// fo<<"}"<<endl;
// fo<<" "<<endl;
// fo<<"}"<<endl;
// fo.close();

TStringList *List = new TStringList;
List->Add("\"clients.txt\"");
List->Add("{");
List->Add("\"version\" \"1\"");
List->Add("");
List->Add("// This key group lists all your client players");
List->Add("\"players\"");
List->Add("{");
List->Add("// This must be a unique client name");
List->Add((AnsiString ("\""+Name->Text+"\"")).c_str());
List->Add("{");
List->Add("// Client real name");
List->Add((AnsiString ("\"name\" \""+Name->Text+"\"")).c_str());
if(Steamid->Text != "")
{
List->Add("// Steam ID for client");
List->Add((AnsiString ("\"steam\" \""+Steamid->Text+"\"")).c_str());
}
if(idip->Text != "")
{
List->Add("// IP adress for client");
List->Add((AnsiString ("\"ip\" \""+idip->Text+"\"")).c_str());
}
if(Nik->Text != "")
{
List->Add("// Nik name for client");
List->Add((AnsiString ("\"nick\" \""+Nik->Text+"\"")).c_str());
}
if(Pass->Text != "")
{
List->Add("// Pass for client");
List->Add((AnsiString ("\"password\" \""+Pass->Text+"\"")).c_str());
}
List->Add("// These are personal access flags for a player");
List->Add("\"flags\"");
List->Add("{");
List->Add("\"Immunity\"	\"Immunity grav ping afk a b c d e f g h i j k l m n o p q r s\"");
List->Add("\"Immunity\"	\"t u v x y autojoin\"");
List->Add("\"Admin\"	\"q2 q3 grav pban A B C D E F G H I J K L M N O P Q R S T U V\"");
List->Add("\"Admin\"	\"W X Y Z a b c d e f g i j k l m o p q r s t v w x y z client\"");
List->Add("\"Admin\"	\"admin spray\"");
List->Add("}");
List->Add("}");
List->Add("}");
List->Add("");
List->Add("// These are global groups of flags that can be assigned to clients");
List->Add("\"groups\"");
List->Add("{");
List->Add("\"Admin\"");
List->Add("{");
List->Add("\"Admin\"	\"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d\"");
List->Add("\"Admin\"	\"e f g i j k l m o p q r s t v w x y z admin spray grav pban\"");
List->Add("\"Admin\"	\"client\"");
List->Add("}");
List->Add("}");
List->Add(" ");
List->Add("}");
List->SaveToFile("");
List->Clear();
List->LoadFromFile("");
List[44];//-это строка
List->Count;//-это кол-во строк

}
//---------------------------------------------------------------------------


void __fastcall TForm5::Label4Click(TObject *Sender)
{
ShellExecute(NULL, "open", "./FAQ/Documentation(ru).html", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------


void __fastcall TForm5::FormCreate(TObject *Sender)
{
if(Form1->lang2 == 1)
{
TIniFile *ini;
ini = new TIniFile(ChangeFileExt("language/English.ini", ".INI" ));
String F5Caption1;
F5Caption1 = ini->ReadString("Form","F5Caption1","");
GroupBox1->Caption = F5Caption1;

String F5Caption2;
F5Caption2 = ini->ReadString("Form","F5Caption2","");
Label1->Caption = F5Caption2;

String F5Caption3;
F5Caption3 = ini->ReadString("Form","F5Caption3","");
GroupBox2->Caption = F5Caption3;

String F5Caption4;
F5Caption4 = ini->ReadString("Form","F5Caption4","");
Label6->Caption = F5Caption4;

String F5Caption5;
F5Caption5 = ini->ReadString("Form","F5Caption5","");
Label5->Caption = F5Caption5;

String F5Caption6;
F5Caption6 = ini->ReadString("Form","F5Caption6","");
Label3->Caption = F5Caption6;

String F5Caption7;
F5Caption7 = ini->ReadString("Form","F5Caption7","");
Button2->Caption = F5Caption7;

String F5Caption8;
F5Caption8 = ini->ReadString("Form","F5Caption8","");
Button1->Caption = F5Caption8;

Label4->Visible = false;
}

}
//---------------------------------------------------------------------------

