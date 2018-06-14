//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

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
void __fastcall TForm2::Button1Click(TObject *Sender)
{
if(LabeledEdit3->Text=="" || LabeledEdit4->Text=="")
ShowMessage("Поля логин иили пароль не заполнены!");
else
{
TimeOut=-3;
ClientSocket1->Host = LabeledEdit1->Text; // Присваиваем Клиенту Ай-Пи из Эдита
ClientSocket1->Address = LabeledEdit1->Text;
ClientSocket1->Port = LabeledEdit2->Text.ToInt();
ClientSocket1->Active = true ;
Timer1->Enabled = true;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)
{
Memo1->Lines->Add(" Подключение...");
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BSendClick(TObject *Sender)
{
if(Edit1->Text == "")
{
ShowMessage("Введите текст который надо отправить");
return ;
}

ClientSocket1->Socket->SendText("#M"+Edit1->Text);
Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] Я: "+ Edit1->Text);
Edit1->Text = "" ;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
ClientSocket1->Socket->SendText("#CD");
ClientSocket1->Active = false;
Button1->Enabled = true;
BSend->Enabled = false;
GroupBox1->Enabled = false;
Memo1->Lines->Add(" Вы отключились.");
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TMemoryStream *MS = new TMemoryStream ; // создаем поток под принимаемый файл
int Size ;                              // размер передаваемого файла
bool Receive ;                          // передаем ли мы на данный момент файл
String FileName;                   //  имя файла
//---------------------------------------------------------------------------


DWORD __stdcall ProgressBar(LPVOID pParams)
{
 while(Receive == true ){
  Form2->ProgressBar1->Position = MS->Size;

  if(Size==0)
  {
	Form2->ProgressBar1->Max = 100;  Form2->ProgressBar1->Min = 0;
	Form2->ProgressBar1->Position = -1;
	return 1;
  }
 }
 return 1;
}
//---------------------------------------------------------------------------

void TForm2::Write( AnsiString Text )
{
	if(MS->Size < Size)  // если мы еще принимаем файл и размер потока меньше размера файла
	{
		MS->Write( Text.c_str() , Text.Length() );   // записываем в поток
		// Form2->Memo2->Lines->Strings[Form2->Memo2->Lines->Count] = "Принимаем данные... "+(String)(MS->Size/1024)+" из "+(Size/1024)+" кб"; // пишем лог
	}
	if(MS->Size == Size) // если файл принят и размер потока соответствует размеру файла
	{
		// CloseHandle( hthread );
		Form2->ProgressBar1->Position = MS->Size;
		Receive = false ;                         // останавливаем режим передачи
		MS->Position = 0 ;                        // переводим каретку потока в начало
		Form2->Memo2->Lines->Add("Файл принят !"); // пишем в лог что файл принят
		Form2->ClientSocket1->Socket->SendText("#FE" ); // пишем серверу, что мы приняли файл
		CreateDir( "Downloads" );                 // создаем папку для сохраненных файлов
		Form2->Memo2->Lines->Add("Запись на диск..."); // пишем в лог что файл принят
		MS->SaveToFile( "Downloads\\"+FileName ); // сохраняем туда наш файл
		Form2->Memo2->Lines->Strings[Form2->Memo2->Lines->Count-1] = "Запись на диск...ок";
		MS->Clear() ;                             // освобождаем поток
		Size = 0 ;
		GroupBox1->Enabled = true;
		ProgressBar1->Max = 100;  ProgressBar1->Min = 0;
		ProgressBar1->Position = -1;
		Application->Initialize();
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm2::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)
{
String RevText = Socket->ReceiveText();
String temp;
if( Receive == true ) // если мы в режиме передачи файла, то
{
	Write( RevText ); // записываем его в поток
	return;
}

if(RevText[1]=='#')
{  RevText.Delete(1,1);
if(RevText[1]=='M')
{
	RevText.Delete(1,1);
	Memo1->Lines->Add("["+d2.CurrentTime().TimeString()+"] Админ: "+RevText);
	return;
}

if(RevText[1]=='C')
{
	RevText.Delete(1,1);
	if(RevText[1]=='B')
	{
		RevText.Delete(1,1);
		ShowMessage(RevText);  return;
	}

	if(RevText[1]=='F')
	{
		RevText.Delete(1,1);    GroupBox1->Enabled = true;
		FileListBox1->Items->Text = RevText;
		return;
	}

	if(RevText[1]=='D')
	{
		Memo1->Lines->Add(" Поступила команда отключения от сервера!");
		Socket->Close();
		ClientSocket1->Active = false;
		Button1->Enabled = true;
		BSend->Enabled = false;
		GroupBox1->Enabled = false;
		Form2->Width = 254;   return;
	}
}

if(RevText[1]=='F')
{
  RevText.Delete(1,1);

	if(RevText[1]=='D')
	{
	 RevText.Delete(1,1);
		if( Receive != true ) // если мы не в режиме передачи файла, то
		{
		 //	Memo2->Lines->Add( "Приняли текст :" + RevText );     // пишем в лог все что принимаем от сервера
		 //	if(Rtext.SubString( 0,Rtext.Pos("#")-1) == "file" ) // Если это строка типа
			// file#filename#filesize#, то начинаем парсерить полученную информацию :
		 //	{
			//	Rtext.Delete( 1 , Rtext.Pos( "#" ) ) ;            // удаляем слово file
				FileName = RevText.SubString( 0 , RevText.Pos( "#" ) -1 );// Определяем имя файла
			   //	FileName = Name.SubString( Name.LastDelimiter( "\\" ) + 1 , Name.Length() );
				// Выделяем чистое имя файла , например с c:\\test.txt , берем test.txt
				RevText.Delete( 1 , RevText.Pos( "#" ) );                               // Удаляем последний разделитель
				Size = StrToInt( RevText.SubString( 0 , RevText.Pos( "#" ) - 1) ) ;     // Определяем размер файла
				RevText.Delete( 1 , RevText.Pos( "#" ) );                               // Удаляем последний разделитель
				Memo2->Lines->Add( "Размер файла: " + IntToStr( Size ) + " байт" ); // Выводим размер файла в лог
				ProgressBar1->Max =  Size ;
		   //		Memo2->Lines->Add( "Имя файла: " + Name );                          // Выводим имя файла в лог
				Receive = true;
				hthread = CreateThread(0,0,ProgressBar,0,0,0);
			Form2->Memo2->Lines->Add("Принимаем данные..."); // пишем лог
			// Переводим сервер в режим приёма файла

		 //	}
		}
	}

  return;
}

if(RevText[1]=='A')
{
	RevText.Delete(1,1);
	if(RevText=="whois")
	  {
		Memo1->Lines->Add(" Авторизация...");
		ClientSocket1->Socket->SendText("#A"+LabeledEdit3->Text+";"+LabeledEdit4->Text); // Отправка логина пароля
		return;
	  }

	if(RevText[1]=='A')
	{
	  temp = "Полные";
	  Button6->Enabled = true;
	  Button7->Enabled = true;
	}
	if(RevText[1]=='U')
	{
	  temp = "Частичные";
	  Button6->Enabled = false;
	  Button7->Enabled = false;
	}

	RevText.Delete(1,1);

	if(RevText=="ok")
	  {
		  Memo1->Lines->Add(" Вы удачно подключились!");
		  BSend->Enabled = true;
		  GroupBox1->Enabled = true;            // Делаем доступную панель управления
		  Button1->Enabled = false;            // Делаем недоступно "Подключиться"
		  Label2->Caption = temp;
		  Form2->Width = 516;
		  return;
	  }
	if(RevText=="pnh")
	 {
		Memo1->Lines->Add(" Неправильный логин или пароль!");
		Socket->Close();
		Timer1->Enabled = false;
		ClientSocket1->Active = false;
		Button1->Enabled = true;
		BSend->Enabled = false;
		GroupBox1->Enabled = false;
		Form2->Width = 254;
		return;
	 }
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
 GroupBox1->Enabled = false;
 Application->Initialize();
 ClientSocket1->Socket->SendText("#CGetList");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
if(GroupBox1->Enabled==true)
Button3->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
if(TimeOut==0)
{
	if(ClientSocket1->Socket->Connected == false)
	{
	ClientSocket1->Active = false;
	Memo1->Lines->Add(" Время ожидания истекло!");
	Button1->Enabled = true;
	}
}
TimeOut++;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
FileListBox1->Items->Text = "";
Form2->Width = 254;

TStringList *Files= new   TStringList;
Files->LoadFromFile("ServerIP.txt");
	for(int i=0; i<Files->Count; i++)
	{
	  ComboBox1->Items->Add(Files->Strings[i]);
	}
delete Files;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
String addres = ComboBox1->Items->Strings[ComboBox1->ItemIndex];
LabeledEdit1->Text =  addres.SubString(1,addres.Pos(":")-1);
LabeledEdit2->Text =  addres.SubString(addres.Pos(":")+1,addres.Length()-addres.Pos(":"));
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
if(LabeledEdit1->Text=="" || LabeledEdit2->Text=="")
ShowMessage("Одно из полей адреса сервера не заполнено.");
else
	{
	TStringList *Files= new   TStringList;
	for(int i=0; i<ComboBox1->Items->Count; i++)
	{
	 Files->Add(ComboBox1->Items->Strings[i]);
	}
	Files->Add(LabeledEdit1->Text+":"+LabeledEdit2->Text);
	Files->SaveToFile("ServerIP.txt");
	delete Files;
	ShowMessage(" "+LabeledEdit1->Text+":"+LabeledEdit2->Text+" успешно добвлен в избранное.");
	ComboBox1->Items->Add(LabeledEdit1->Text+":"+LabeledEdit2->Text);
	ComboBox1->ItemIndex = ComboBox1->Items->Count-1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClientSocket1Connecting(TObject *Sender, TCustomWinSocket *Socket)

{
Button1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode)
{
GroupBox1->Enabled = false;
ErrorCode=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
 Button5->Enabled = false;
 TStringList *Files= new   TStringList;
 Files->LoadFromFile("ServerIP.txt");
 Files->Delete(ComboBox1->ItemIndex);
 Files->SaveToFile("ServerIP.txt");
 delete Files;
 ShowMessage(ComboBox1->Items->Strings[ComboBox1->ItemIndex]+" Удален");
 ComboBox1->DeleteSelected();
 ComboBox1->ItemIndex=-1;
 Button5->Enabled = true;
 }
//---------------------------------------------------------------------------


void __fastcall TForm2::ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket)

{
Form2->Width = 254;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button9Click(TObject *Sender)
{
ClientSocket1->Socket->SendText("#CM"+Edit2->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button7Click(TObject *Sender)
{
if (MessageBox(Form2->Handle,String("Вы действительно хотите удалить файл "+ExtractFileName(FileListBox1->FileName)+"?").c_str(),L"Подтверждение",MB_YESNO | MB_ICONQUESTION)==IDYES)
 {
    Memo2->Lines->Add("Удаление файла "+ExtractFileName(FileListBox1->FileName));
	ClientSocket1->Socket->SendText("#FD"+ExtractFileName(FileListBox1->FileName));
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button6Click(TObject *Sender)
{
GroupBox1->Enabled = false;
  ClientSocket1->Socket->SendText("#FG"+ExtractFileName(FileListBox1->FileName));
}
//---------------------------------------------------------------------------


