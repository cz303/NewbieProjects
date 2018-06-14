//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sCustomComboEdit"
#pragma link "sMaskEdit"
#pragma link "sTooledit"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{


}
//---------------------------------------------------------------------------


void __fastcall TForm2::sDirectoryEdit1Change(TObject *Sender)
{
if(sDirectoryEdit1->Text!="")
FileListBox1->Directory = sDirectoryEdit1->Text ;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
if(LabeledEdit1->Text == "")
{
ShowMessage("������� ���� �������������");
return ;
}
Button1->Enabled = false;
Button2->Enabled = true;
ServerSocket1->Port = LabeledEdit1->Text.ToInt();
ServerSocket1->Active = true;
Memo1->Lines->Add(" ������ ������� �����������.");
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button2Click(TObject *Sender)
{
for (int i=0;i<=(ServerSocket1->Socket->ActiveConnections-1);i++)
ServerSocket1->Socket->Connections[i]->SendText("#CD");
Sleep(250);
ServerSocket1->Socket->Close();
ServerSocket1->Active = false;
Button1->Enabled = true;
Button2->Enabled = false;
Memo1->Lines->Add(" ������ ��������.");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BSendClick(TObject *Sender)
{
ServerSocket1->Socket->Connections[0]->SendText("#M"+Edit1->Text);
Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] �: "+Edit1->Text);
Edit1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket)

{
String RevText = Socket->ReceiveText();
TMemoryStream *MS = new TMemoryStream ; // ����� ��� �������� �����
if(RevText[1]=='#')
{  RevText.Delete(1,1);
if(RevText[1]=='A')
{
   Memo1->Lines->Add(" ������������� ������ "+ServerSocket1->Socket->Connections[0]->RemoteAddress);
   RevText.Delete(1,1);
   if(RevText!="admin;admin" && RevText!="user;user")
   {
	ServerSocket1->Socket->Connections[0]->SendText("#AApnh");
	  Memo1->Lines->Add(" ������ "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" ��������, �������� ������.");
	Socket->Close();
   }
   else
   {
	if(RevText=="admin;admin")
		ServerSocket1->Socket->Connections[0]->SendText("#AAok");
	if(RevText=="user;user")
		ServerSocket1->Socket->Connections[0]->SendText("#AUok");

	Memo1->Lines->Add(" ������ "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" �������������.");
	BSend->Enabled = true;
   }
   return;
}

if(RevText[1]=='M'){
Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] ������: "+RevText.Delete(1,1)); return;
}

if(RevText[1]=='C')
{
RevText.Delete(1,1);
	if(RevText=="GetList")
	{
		if (MessageBox(Form2->Handle,String("������ "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" ����� �������� ������ ������, ���������?").c_str(),L"������",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
		  ServerSocket1->Socket->Connections[0]->SendText("#CF"+FileListBox1->Items->Text);
		}
		else {
		 ServerSocket1->Socket->Connections[0]->SendText("#CB� ������� ��������"); }
	return;
	}
	if(RevText[1]=='M')
	{
	 RevText.Delete(1,1);
	 FileListBox1->Mask =  RevText;
	 ServerSocket1->Socket->Connections[0]->SendText("#CF"+FileListBox1->Items->Text);
     FileListBox1->Mask =  "*.*";
	 return;
    }
	if(RevText=='D')
	{
	   Memo1->Lines->Add(" ������ ����������.");
	   Socket->Close(); return;
	}
}


if(RevText[1]=='F')
{
RevText.Delete(1,1);
	if(RevText[1]=='D')
	{
	  RevText.Delete(1,1);
	  DeleteFile(sDirectoryEdit1->Text+"\\"+RevText);
	  FileListBox1->Update();
	  ServerSocket1->Socket->Connections[0]->SendText("#CF"+FileListBox1->Items->Text);
	return;
	}

	if(RevText[1]=='G')
	{
	  RevText.Delete(1,1);
	  void *P;   // ��������� �� ����
	  int Size; // ������

	 //	if( OpenDialog1->Execute() )
	 //	{
			MS->LoadFromFile( sDirectoryEdit1->Text+"\\"+RevText ); // ��������  ����
	 //		Memo1->Lines->Add( "��������� ��������� ���� � �����..." ); // ��������� ���
	 //	}
		ServerSocket1->Socket->Connections[0]->SendText( "#FD" + RevText + "#" + IntToStr( MS->Size ) + "#" );
		// ���������� ���������

	 //	Memo1->Lines->Add ( "������� ���������" );
		Memo1->Lines->Add ( " �������� ����� "+RevText);
		MS->Position = 0 ;      // ������������� ����� � ��������� ������� ;
		P    = MS->Memory ;     // ����������� ��������� ����� �����
		Size = ServerSocket1->Socket->Connections[0]->SendBuf( P , MS->Size );               // ���������� ����� �������; Size
																					  // ����� ������� ������������  ����������
	 //	Memo1->Lines->Add( "����������: " + IntToStr( Size ) + " �� " + IntToStr( MS->Size ) ); // ��������� ���
	}

	if(RevText=='E') // ���� ������ ������� ������� "end"
	{
	Memo1->Lines->Add(" ������ ������ ����"); // ���������� � ���
	MS->Clear() ;                            // ������� �����
	}

return;
}

}
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
if(Button2->Enabled==true)
Button2->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ServerSocket1ClientConnect(TObject *Sender, TCustomWinSocket *Socket)

{
ServerSocket1->Socket->Connections[0]->SendText("#Awhois");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
FileListBox1->Update();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
sDirectoryEdit1->Text = GetCurrentDir();
}
//---------------------------------------------------------------------------

