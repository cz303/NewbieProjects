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
ShowMessage("Введите порт прослушивания");
return ;
}
Button1->Enabled = false;
Button2->Enabled = true;
ServerSocket1->Port = LabeledEdit1->Text.ToInt();
ServerSocket1->Active = true;
Memo1->Lines->Add(" Сервер ожидает подключения.");
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
Memo1->Lines->Add(" Сервер выключен.");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::BSendClick(TObject *Sender)
{
ServerSocket1->Socket->Connections[0]->SendText("#M"+Edit1->Text);
Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] Я: "+Edit1->Text);
Edit1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket)

{
String RevText = Socket->ReceiveText();
TMemoryStream *MS = new TMemoryStream ; // поток для передачи файла
if(RevText[1]=='#')
{  RevText.Delete(1,1);
if(RevText[1]=='A')
{
   Memo1->Lines->Add(" Подключаеться клиент "+ServerSocket1->Socket->Connections[0]->RemoteAddress);
   RevText.Delete(1,1);
   if(RevText!="admin;admin" && RevText!="user;user")
   {
	ServerSocket1->Socket->Connections[0]->SendText("#AApnh");
	  Memo1->Lines->Add(" Клиент "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" отключен, неверный пароль.");
	Socket->Close();
   }
   else
   {
	if(RevText=="admin;admin")
		ServerSocket1->Socket->Connections[0]->SendText("#AAok");
	if(RevText=="user;user")
		ServerSocket1->Socket->Connections[0]->SendText("#AUok");

	Memo1->Lines->Add(" Клиент "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" присоеденился.");
	BSend->Enabled = true;
   }
   return;
}

if(RevText[1]=='M'){
Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] Клиент: "+RevText.Delete(1,1)); return;
}

if(RevText[1]=='C')
{
RevText.Delete(1,1);
	if(RevText=="GetList")
	{
		if (MessageBox(Form2->Handle,String("Клиент "+ServerSocket1->Socket->Connections[0]->RemoteAddress+" хочет получить список файлов, разрешить?").c_str(),L"Запрос",MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
		  ServerSocket1->Socket->Connections[0]->SendText("#CF"+FileListBox1->Items->Text);
		}
		else {
		 ServerSocket1->Socket->Connections[0]->SendText("#CBВ запросе отказано"); }
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
	   Memo1->Lines->Add(" Клиент отключился.");
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
	  void *P;   // указатель на файл
	  int Size; // размер

	 //	if( OpenDialog1->Execute() )
	 //	{
			MS->LoadFromFile( sDirectoryEdit1->Text+"\\"+RevText ); // выбираем  файл
	 //		Memo1->Lines->Add( "Загрузили требуемый файл в поток..." ); // заполняем лог
	 //	}
		ServerSocket1->Socket->Connections[0]->SendText( "#FD" + RevText + "#" + IntToStr( MS->Size ) + "#" );
		// отправляем заголовок

	 //	Memo1->Lines->Add ( "Послали заголовок" );
		Memo1->Lines->Add ( " Отправка файла "+RevText);
		MS->Position = 0 ;      // Устанавливаем поток в начальную позицию ;
		P    = MS->Memory ;     // присваиваем указателю поток файла
		Size = ServerSocket1->Socket->Connections[0]->SendBuf( P , MS->Size );               // отправляем буфер клиенту; Size
																					  // равно размеру отправленной  информации
	 //	Memo1->Lines->Add( "Отправлено: " + IntToStr( Size ) + " из " + IntToStr( MS->Size ) ); // заполняем лог
	}

	if(RevText=='E') // если клиент прислал команду "end"
	{
	Memo1->Lines->Add(" Клиент принял файл"); // записываем в лог
	MS->Clear() ;                            // Очищаем поток
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

