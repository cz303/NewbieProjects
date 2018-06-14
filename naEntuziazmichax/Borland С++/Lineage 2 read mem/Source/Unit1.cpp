//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
#include <process.h>
#include <stddef.h>
#include <math.h>
#include <string.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "JvAppHotKey"
#pragma link "JvComponentBase"
#pragma link "JvExComCtrls"
#pragma link "JvHotKey"
#pragma resource "*.dfm"
TForm1 *Form1;
static DWORD __stdcall FindAdrMem(LPVOID);
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

BOOL DoRtlAdjustPrivilege()
{
/*
Важная функция. Получаем привилегии дебаггера.
Именно это позволит нам получить нужную информацию
о доступности памяти.
*/
#define SE_DEBUG_PRIVILEGE 20L
#define AdjustCurrentProcess 0
BOOL bPrev = FALSE;
LONG (WINAPI *RtlAdjustPrivilege)(DWORD, BOOL, INT, PBOOL);
*(FARPROC *)&RtlAdjustPrivilege = GetProcAddress(GetModuleHandle("ntdll.dll"), "RtlAdjustPrivilege");
if(!RtlAdjustPrivilege) return FALSE;
RtlAdjustPrivilege(SE_DEBUG_PRIVILEGE, TRUE, AdjustCurrentProcess, &bPrev);
return TRUE;
}
//---------------------------------------------------------------------------

int mem_sub(void * src, size_t src_sz, void * dst, size_t dst_sz)
{
   int ret = -1;
   for (size_t i = 0; i < src_sz - dst_sz + 1; i++)
   {
           if (!memcmp((char *)src + i, dst, dst_sz))
		   {
               ret = i;
               break;
           }
   }
   return ret;
}
//---------------------------------------------------------------------------



DWORD __stdcall OldFindAdrMem(LPVOID pParams)
{
int *finghp = (int*)pParams;

MEMORY_BASIC_INFORMATION mbi;
SYSTEM_INFO msi;
ZeroMemory(&mbi, sizeof(mbi));
GetSystemInfo(&msi);
Form1->Memo1->Lines->Add("Получили информацию о памяти");

BYTE Code[65000];
BYTE Code2[8];
BYTE Code3[8];
BYTE Code4[8];
// LPBYTE lpAddress = (LPBYTE)0x00000000;
LPBYTE lpAddress = (LPBYTE)0x09690830;
__int64 sub = *finghp;
int pos;

if(Form1->hProc)
{
if(DoRtlAdjustPrivilege())
{
Form1->Memo1->Lines->Add("Привилегии дебагера ок");

// LPBYTE lpAddress = (LPBYTE)0x0001000;
// Memo1->Lines->Add("Размер региона - "+AnsiString().sprintf("%p",(LPBYTE)mbi.RegionSize));
Form1->Memo1->Lines->Add("Проверка памяти...ищем "+IntToStr(sub));
// Form1->Memo1->Lines->Add("");
// for(LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress;
// lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress;
// lpAddress += mbi.RegionSize)


for(lpAddress;
lpAddress <= (LPBYTE)0x30000000;
lpAddress = lpAddress + mbi.RegionSize)
// lpAddress = lpAddress + 0x00090000)
{

if(VirtualQueryEx(Form1->hProc, (LPCVOID)lpAddress, &mbi, sizeof(mbi))){
//  Form1->Memo1->Lines->Add("Проверка доступности - ");
// if((mbi.Protect & PAGE_READWRITE)  || (mbi.Protect & PAGE_WRITECOPY)){
/* if((mbi.Protect == PAGE_READONLY)
 || (mbi.Protect == PAGE_WRITECOPY)
 || (mbi.State==MEM_COMMIT)
 || (mbi.Protect == PAGE_READWRITE) )
 {
*/
// Form1->Memo1->Lines->Add("Читаемо");


for(lpAddress;(lpAddress<lpAddress+mbi.RegionSize)  && (lpAddress <= (LPBYTE)0x3000000);lpAddress=lpAddress+0x00010000)

{
// Memo1->Lines->Add(AnsiString().sprintf("%p",lpAddress));

   Form1->Memo1->Lines->Strings[Form1->Memo1->Lines->Count-1]=AnsiString().sprintf("%p",lpAddress);
// Memo1->Refresh();
//	Application->Initialize();
// Label1->Caption = AnsiString().sprintf("%p",lpAddress);

/* ReadProcessMemory(hProc,(LPCVOID)lpAddress,Code,8,NULL);
/*
    if(*(__int64*)Code == 1894)
    {
      Form1->Memo1->Lines->Add("Есть совпадение");
      ReadProcessMemory(hProc,(LPCVOID)(lpAddress-0x00000008),Code2,8,NULL);
       if(*(__int64*)Code2 == 1894)
    	{
    	 Form1->Label2->Caption = AnsiString().sprintf("%p",lpAddress);
    	 Form1->Memo1->Lines->Add("Есть двойное совпадение");
    	 // lpAddress = (LPBYTE)0x20000010;
    	// break;
    	return 1;
    	}
    	Form1->Memo1->Lines->Add("");
	}
*/
Form1->dwRead = 0;

ReadProcessMemory(Form1->hProc,(LPCVOID)lpAddress,Code,65000,&Form1->dwRead);

pos = mem_sub(Code, 65000, &sub, sizeof(sub));
   if (pos != -1)
   {
   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress+0x00000008)+pos),Code2,8,NULL);
   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress-0x00000008)+pos),Code3,8,NULL);
   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress)+pos),Code4,8,NULL);

   if(*(__int64*)Code3 == Form1->Edit5->Text.ToInt() || *(__int64*)Code2 == Form1->Edit5->Text.ToInt() || *(__int64*)Code4 == Form1->Edit5->Text.ToInt())
   Form1->Memo2->Lines->Add(AnsiString().sprintf("%p",((lpAddress)+pos))+":  "+IntToStr(*(__int64*)Code3)+"/"+IntToStr(*(__int64*)Code4)+"/"+IntToStr(*(__int64*)Code2) );

   if(*(__int64*)Code2 == sub || *(__int64*)Code3 == sub ){
	 // ShowMessage(AnsiString().sprintf("%p",lpAddress)+" cовпадение "+IntToStr(pos)+" а это "+AnsiString().sprintf("%p",lpAddress+pos));
	 // pos -= sizeof(sub)-1;
	 // ShowMessage(" а это "+AnsiString().sprintf("%p",lpAddress+pos));
	 // break;
	 // Form1->Label2->Caption = AnsiString().sprintf("%p",((lpAddress+0x00000008)+pos));
	 Form1->Label1->Caption = IntToStr((*(__int64*)Code2))+"/"+IntToStr((*(__int64*)Code2));
	 Form1->Memo1->Lines->Add("Есть совпадение, адрес найден - "+AnsiString().sprintf("%p",((lpAddress)+pos)));
	 Form1->HPAddress = (lpAddress+0x00000008)+pos;
	 Form1->find = true;
     Form1->CheckBox1->Enabled = true;

	 // lpAddress = (LPBYTE)0x20DFD130;
	 break;
   }
	   else
	   {
	   //	Form1->Memo1->Lines->Add("Есть совпадение, но "+AnsiString().sprintf("%p",((lpAddress+0x00000008)+pos))+" не то");
	   }
   }

}

// }
// else{
// Form1->Memo1->Lines->Add(AnsiString().sprintf("%p",lpAddress)+" память не доступна для чтения");
// }


 }
 else{
 Form1->Memo1->Lines->Add("Не получилось получить информацию доступности");
 break;
}

}
}

else
ShowMessage("Привилегии дебагера - ошибка");
}
else
ShowMessage("Процесс не найден");


Form1->Memo1->Lines->Add("Поиск окончен.");
return 1;
}
//---------------------------------------------------------------------------


DWORD __stdcall FindAdrMem(LPVOID pParams)
{
int *finghp = (int*)pParams;

MEMORY_BASIC_INFORMATION mbi;
SYSTEM_INFO msi;
ZeroMemory(&mbi, sizeof(mbi));
GetSystemInfo(&msi);
Form1->Memo1->Lines->Add("Получили информацию о памяти");

BYTE Code[80000];
BYTE Code2[8];
BYTE Code3[8];
BYTE Code4[8];
// LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress;
LPBYTE lpAddress = (LPBYTE)0x0A690830;
__int64 sub = *finghp;
int pos;
Form1->Memo1->Lines->Add("Начало: "+   AnsiString().sprintf("%p",(LPBYTE)msi.lpMinimumApplicationAddress)	);
Form1->Memo1->Lines->Add("Конец: "+   AnsiString().sprintf("%p",(LPBYTE)msi.lpMaximumApplicationAddress)			);

if(Form1->hProc)
{
if(DoRtlAdjustPrivilege())
{
Form1->Memo1->Lines->Add("Привилегии дебагера ок");
Form1->Memo1->Lines->Add("Проверка памяти...ищем "+IntToStr(sub));

for(lpAddress;
lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress;
lpAddress = lpAddress + mbi.RegionSize)
{

if(VirtualQueryEx(Form1->hProc,(LPCVOID)lpAddress,&mbi,sizeof(mbi)) != sizeof(MEMORY_BASIC_INFORMATION))
{
 Form1->Memo1->Lines->Add("Не получилось получить информацию доступности");
 break;
}

if((mbi.Protect == PAGE_READONLY)
 || (mbi.Protect == PAGE_WRITECOPY)
 || (mbi.State==MEM_COMMIT)
 || (mbi.Protect == PAGE_READWRITE) )
 {

for(lpAddress;(lpAddress<lpAddress+mbi.RegionSize)
  && (lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress);
  lpAddress=lpAddress+0x00010000)
{
Form1->Memo1->Lines->Strings[Form1->Memo1->Lines->Count-1]=AnsiString().sprintf("%p",lpAddress);
Form1->dwRead = 0;
ReadProcessMemory(Form1->hProc,(LPCVOID)lpAddress,Code,80000,NULL);
pos = mem_sub(Code, 80000, &sub, sizeof(sub));

   if (pos != -1)
   {
	   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress+0x00000008)+pos),Code2,8,NULL);
	   if(*(__int64*)Code2 == sub )
	   {
	   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress)+pos),Code4,8,NULL);
	   Form1->Memo2->Lines->Add(AnsiString().sprintf("%p",((lpAddress)+pos))+":  "+IntToStr(*(__int64*)Code3)+"/"+IntToStr(*(__int64*)Code4)+"/"+IntToStr(*(__int64*)Code2) );

		 Form1->Label1->Caption = IntToStr((*(__int64*)Code2))+"/"+IntToStr((*(__int64*)Code4));
		 Form1->Memo1->Lines->Add("Есть совпадение, адрес найден - "+AnsiString().sprintf("%p",((lpAddress)+pos)));
		 Form1->HPAddress = (lpAddress+0x00000008)+pos;
		 Form1->find = true;
		 Form1->CheckBox1->Enabled = true;
         return 1;

	   }
	   else
	   {
	   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress-0x00000008)+pos),Code3,8,NULL);
	   ReadProcessMemory(Form1->hProc,(LPCVOID)((lpAddress)+pos),Code4,8,NULL);
	   Form1->Memo2->Lines->Add(AnsiString().sprintf("%p",((lpAddress)+pos))+":  "+IntToStr(*(__int64*)Code3)+"/"+IntToStr(*(__int64*)Code4)+"/"+IntToStr(*(__int64*)Code2) );
	   }
   }

}
}
 else{
Form1->Memo1->Lines->Add(AnsiString().sprintf("%p",lpAddress)+" память не доступна для чтения");
}

}
}
else
ShowMessage("Привилегии дебагера - ошибка");
}
else
ShowMessage("Процесс не найден");


Form1->Memo1->Lines->Add("Поиск окончен.");
return 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
 if(Edit5->Text == "")
 ShowMessage("Укажите количество хп, которое будет использовано для поиска адреса в памяти процесса, оно длжно быть равным максимуму хп на данный момент.");
 else{
 static int finghp = Edit5->Text.ToInt();
 HANDLE hthread;
 // unsigned long threadID=0;
 DWORD threadID=0;
 Form1->hProc = OpenProcess (PROCESS_ALL_ACCESS,
	FALSE,
	Form1->Edit1->Text.ToInt());
 hthread= CreateThread(
                                0,
                                0,
							FindAdrMem,
							&finghp,
								0,
							&threadID);
 SetThreadPriority(hthread ,THREAD_PRIORITY_HIGHEST);
 CloseHandle( hthread );
 }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button2Click(TObject *Sender)
{
/* LPBYTE lpAddress = (LPBYTE)0x096A0830;
MEMORY_BASIC_INFORMATION mbi;
SYSTEM_INFO msi;
ZeroMemory(&mbi, sizeof(mbi));
GetSystemInfo(&msi);
*/
hProc2 = OpenProcess (PROCESS_ALL_ACCESS,
	FALSE,
	Edit2->Text.ToInt());
ReadProcessMemory(hProc2,(LPCVOID)0x096A0830,HP,8,0);
ReadProcessMemory(hProc2,(LPCVOID)(0x096A0830-0x00000008),HPmax,8,0);

Label1->Caption = IntToStr(*(__int64*)HP)+"/"+IntToStr(*(__int64*)HPmax);

 // Label2->Caption = AnsiString().sprintf("%p",lpAddress-0x00000008);
 // Label2->Caption = AnsiString().sprintf("%p",lpAddress+mbi.RegionSize);
}
//---------------------------------------------------------------------------

String decTOhex(String y)
{
  if(y=="10") return "A"; if(y=="13") return "D";
  if(y=="11") return "B"; if(y=="14") return "E";
  if(y=="12") return "C"; if(y=="15") return "F";
  return y;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
__int64 sub = 1894;
int pos;
char buff[] = {0, 0, 0x66, 0x07, 0, 0, 0, 0, 0, 0, 0xd2, 0x04, 0, 0, 4, 9, 0};

pos = mem_sub(buff, sizeof(buff), &sub, sizeof(sub));
   if (pos != -1)
   {
	  ShowMessage("cовпадение "+IntToStr(pos));
   }

/*
int i,i2;
i = 1894;
String hex,byte,ost,temps;
char tempc;
int xtemp;
double temp,x;

	for (temp = i; temp > 16; ) {
		ost = (int)fmod(temp, 16);
		temps += decTOhex(ost);
		temp = temp/16;
		modf(temp, &x);
		xtemp = x;
	}
	temps+=decTOhex(xtemp);

	for (i2 = temps.Length(); i2>0; i2--) {
	 hex = hex + temps[i2];
	}

x=hex.Length();

for(i2=1; i2<=x/2; i2++)
{
 tempc = hex[i2];
 hex[i2] = hex[x-i2+1];
 hex[x-i2+1] = tempc;
}

for(i2 = 1; i2<16; i2++)
{
	if(i2<hex.Length())
	{
	  byte+=hex[i2];
	}

	if(i2==hex.Length())
	{
	  byte+="0";
	  byte+=hex[i2];
	}

	if(i2>hex.Length())
	{
	  byte+="00";
	  i2++;
	}
}
Memo1->Lines->Add(byte);

char Code2[8];

x=hex.Length();

int i3=1;

for(i2=0; i2<8; i2++)
{
 ost = "0x";
 ost += byte[i3];
 ost += byte[i3+1];
 strcpy(&Code2[i2],AnsiString(ost).c_str());
 i3+=2;
 Memo1->Lines->Add(Code2[i2]);
}

Memo1->Lines->Add(Code2);

 */




}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
bool RHKret = RegisterHotKey(Form1->Handle,101,MOD_ALT+MOD_CONTROL,VK_NUMPAD8);
 if (RHKret) Memo1->Lines->Add("Хоткей ctrl+alt+num_8 зарегистрирован для выбора основного окна.");
 bool RHKret2 = RegisterHotKey(Form1->Handle,102,MOD_ALT+MOD_CONTROL,VK_NUMPAD9);
 if (RHKret2)Memo1->Lines->Add("Хоткей ctrl+alt+num_9 зарегистрирован для выбора окна бафера.");
 bool RHKret3 = RegisterHotKey(Form1->Handle,103,MOD_ALT+MOD_CONTROL,VK_NUMPAD1);
 if (RHKret3)Memo1->Lines->Add("Хоткей ctrl+alt+num_1 зарегистрирован (для галки вкл/выкл).");
 bool RHKret4 = RegisterHotKey(Form1->Handle,107,MOD_ALT+MOD_CONTROL,VK_NUMPAD2);
 if (RHKret4)Memo1->Lines->Add("Хоткей ctrl+alt+num_2 зарегистрирован (для галки лечения).");
 Memo1->Lines->Add("by leporel");
 find = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
UnregisterHotKey(Form1->Handle, 101);
UnregisterHotKey(Form1->Handle, 102);
UnregisterHotKey(Form1->Handle, 103);
UnregisterHotKey(Form1->Handle, 107);
if(InGameKey1) UnregisterHotKey(Form1->Handle, 1);
if(InGameKey2) UnregisterHotKey(Form1->Handle, 2);
if(InGameKey3) UnregisterHotKey(Form1->Handle, 3);
if(InGameKey4) UnregisterHotKey(Form1->Handle, 4);

// // // // //
// Cleanup
if (hProc)
CloseHandle(hProc);
///////////////
// // // // //
// Cleanup
if (hProc2)
CloseHandle(hProc);
///////////////
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ApplicationEvents1Message(tagMSG &Msg, bool &Handled)
{
if (Msg.message == WM_HOTKEY)
		{
		if (Msg.wParam == 101)
				{
				HWND h = NULL;
				DWORD pid;
				POINT p;
				GetCursorPos(&p);
				h = WindowFromPoint(p);
				// char * c = (char*)malloc(32 * sizeof(char));
				// GetWindowText(h, c, 32);
				// ShowMessage(c);
				GetWindowThreadProcessId(h,&pid);
				// ShowMessage(pid);
				Edit1->Text = pid;
				CloseHandle(h);
				Sleep(500);
				Button1->Click();
				}
		if (Msg.wParam == 102)
				{
				HWND h = NULL;
				DWORD pid;
				POINT p;
				GetCursorPos(&p);
				h = WindowFromPoint(p);
				// char * c = (char*)malloc(32 * sizeof(char));
				// GetWindowText(h, c, 32);
				// ShowMessage(c);
				GetWindowThreadProcessId(h,&pid);
				// ShowMessage(pid);
				Edit2->Text = pid;
				hProc2 = h;
				CloseHandle(h);
				}
		if (Msg.wParam == 103)
				{
					if(CheckBox1->Checked==true){
					CheckBox1->Checked = false;
					Timer1->Enabled = false;
					}
					else{
					CheckBox1->Checked = true;
						if(find){
						Timer1->Interval = Edit4->Text.ToInt();
						Timer1->Enabled = true;
						}
					}
				}
		if (Msg.wParam == 107)
				{
					if(CheckBox5->Checked==true)
						CheckBox5->Checked = false;
					else
						CheckBox5->Checked = true;
				}
		if (Msg.wParam == 1)
				{
					if(hotid[0] == 1)
					{hotid[0]=0; goto breakp; }
					Memo1->Lines->Add("["+TimeToStr(Time())+"] Нажат хоткей 1");
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
					for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey4->HotKey) & 128 ) {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0); Sleep(500);}
					if( HIBYTE(HotKey4->HotKey) & 64 )  {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);  Sleep(500);}
					if( HIBYTE(HotKey4->HotKey) & 32 ) {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);  Sleep(500);}
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey4->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey4->HotKey),0);
					if( HIBYTE(HotKey4->HotKey) & 128 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0); }
					if( HIBYTE(HotKey4->HotKey) & 64 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);   }
					if( HIBYTE(HotKey4->HotKey) & 32 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0); }
					}
					if(CheckBox6->Checked == true){
						hotid[0] = 1;
						Timer2->Interval = Edit7->Text.ToInt();
						Timer2->Enabled = true;
						}
					breakp:

				}
		if (Msg.wParam == 2)
				{
					if(hotid[1] == 1)
					{hotid[1]=0; goto breakp1; }
				Memo1->Lines->Add("["+TimeToStr(Time())+"] Нажат хоткей 2");
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				 for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey6->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey6->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey6->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey6->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey6->HotKey),0);
					if( HIBYTE(HotKey6->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey6->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey6->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
					if(CheckBox6->Checked == true){
						hotid[1] = 1;
						Timer2->Interval = Edit7->Text.ToInt();
						Timer2->Enabled = true;
						}
					breakp1:
				}
		if (Msg.wParam == 3)
				{
				   if(hotid[2] == 1)
					{hotid[2]=0; goto breakp2; }
				  Memo1->Lines->Add("["+TimeToStr(Time())+"] Нажат хоткей 3");
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey8->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey8->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey8->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey8->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey8->HotKey),0);
					if( HIBYTE(HotKey8->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey8->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey8->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
					if(CheckBox6->Checked == true){
						hotid[2] = 1;
						Timer2->Interval = Edit7->Text.ToInt();
						Timer2->Enabled = true;
						}
					breakp2:
				}
		if (Msg.wParam == 4)
				{
				   if(hotid[3] == 1)
					{hotid[3]=0; goto breakp3; }
				  Memo1->Lines->Add("["+TimeToStr(Time())+"] Нажат хоткей 4");
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey9->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey9->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey9->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey9->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey9->HotKey),0);
					if( HIBYTE(HotKey9->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey9->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey9->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
					if(CheckBox6->Checked == true){
						hotid[3] = 1;
						Timer2->Interval = Edit7->Text.ToInt();
						Timer2->Enabled = true;
						}
					breakp3:
				}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if(find && CheckBox1->Checked)
{
ReadProcessMemory(hProc,(LPCVOID)HPAddress,HP,8,0);
ReadProcessMemory(hProc,(LPCVOID)(HPAddress-0x00000008),HPmax,8,0);

if(*(__int64*)HP==*(__int64*)HPmax)
{
 HPmin = Edit3->Text.ToInt();
}

if(*(__int64*)HP<Edit3->Text.ToInt()){
if(CheckBox5->Checked)
HPmin = *(__int64*)HPmax;
else
HPmin = Edit3->Text.ToInt();
}

Label1->Caption = IntToStr(*(__int64*)HP)+"/"+IntToStr(*(__int64*)HPmax);

	if(*(__int64*)HP==0)
	{
	 Memo1->Lines->Add("Мы умерли :(");
	 CheckBox1->Checked = false;
	 Timer1->Enabled = false;
	}

	if(*(__int64*)HP<HPmin)
	{
	 Memo1->Lines->Add("["+TimeToStr(Time())+"] Лечимся ("+Label1->Caption+" хп)");

	 if( HIBYTE(HotKey1->HotKey) & 64 )
		PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
	 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey1->HotKey),0);
	 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey1->HotKey),0);
	 if( HIBYTE(HotKey1->HotKey) & 64 )
		PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
	}
}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
if(CheckBox1->Checked==false){
Timer1->Enabled = false;
}
else{
	if(find==true){
	Timer1->Interval = Edit4->Text.ToInt();
	Timer1->Enabled = true;
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
if(CheckBox2->Checked == true && InGameKey1 == false) {
if( HIBYTE(HotKey3->HotKey) & 128 ) Flags1 |= MOD_CONTROL;
if( HIBYTE(HotKey3->HotKey) & 64 )  Flags1 |= MOD_ALT;
if( HIBYTE(HotKey3->HotKey) & 32 )  Flags1 |= MOD_SHIFT;
}

if(CheckBox3->Checked == true && InGameKey2 == false){
if( HIBYTE(HotKey5->HotKey) & 128 ) Flags2 |= MOD_CONTROL;
if( HIBYTE(HotKey5->HotKey) & 64 )  Flags2 |= MOD_ALT;
if( HIBYTE(HotKey5->HotKey) & 32 )  Flags2 |= MOD_SHIFT;
}

if(CheckBox4->Checked == true && InGameKey3 == false){
if( HIBYTE(HotKey7->HotKey) & 128 ) Flags3 |= MOD_CONTROL;
if( HIBYTE(HotKey7->HotKey) & 64 )  Flags3 |= MOD_ALT;
if( HIBYTE(HotKey7->HotKey) & 32 )  Flags3 |= MOD_SHIFT;
}

if(CheckBox7->Checked == true && InGameKey4 == false){
if( HIBYTE(HotKey2->HotKey) & 128 ) Flags4 |= MOD_CONTROL;
if( HIBYTE(HotKey2->HotKey) & 64 )  Flags4 |= MOD_ALT;
if( HIBYTE(HotKey2->HotKey) & 32 )  Flags4 |= MOD_SHIFT;
}

 if(CheckBox2->Checked == true && InGameKey1 == false)
 { InGameKey1 = RegisterHotKey(Handle,1,Flags1,LOBYTE(HotKey3->HotKey));
  if(InGameKey1)
  {ShowMessage("Хоткей 1 зарегистрирован");}
  else
  {
  MessageDlg("Не удалось зарегистрировать 1 хоткей.", mtError, TMsgDlgButtons()<<mbOK, 0);
  CheckBox2->Checked = false;
  }
 }

 if(CheckBox3->Checked == true && InGameKey2 == false)
 { InGameKey2 = RegisterHotKey(Handle,2,Flags2,LOBYTE(HotKey5->HotKey));
  if(InGameKey2)
  {ShowMessage("Хоткей 2 зарегистрирован");}
  else
  {
  MessageDlg("Не удалось зарегистрировать 2 хоткей.", mtError, TMsgDlgButtons()<<mbOK, 0);
  CheckBox3->Checked = false;
  }
 }

 if(CheckBox4->Checked == true && InGameKey3 == false)
 { InGameKey3 = RegisterHotKey(Handle,3,Flags3,LOBYTE(HotKey7->HotKey));
  if(InGameKey3)
   {ShowMessage("Хоткей 3 зарегистрирован");}
  else {
   MessageDlg("Не удалось зарегистрировать 3 хоткей.", mtError, TMsgDlgButtons()<<mbOK, 0);
   CheckBox4->Checked = false;
  }
 }

 if(CheckBox7->Checked == true && InGameKey4 == false)
 { InGameKey4 = RegisterHotKey(Handle,4,Flags4,LOBYTE(HotKey2->HotKey));
  if(InGameKey4)
   {ShowMessage("Хоткей 4 зарегистрирован");}
  else {
   MessageDlg("Не удалось зарегистрировать 4 хоткей.", mtError, TMsgDlgButtons()<<mbOK, 0);
   CheckBox7->Checked = false;
  }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
if(InGameKey1) {UnregisterHotKey(Form1->Handle, 1); InGameKey1 = false; ShowMessage("Хоткей 1 удален"); CheckBox2->Checked = false;}
if(InGameKey2) {UnregisterHotKey(Form1->Handle, 2); InGameKey2 = false; ShowMessage("Хоткей 2 удален"); CheckBox3->Checked = false;}
if(InGameKey3) {UnregisterHotKey(Form1->Handle, 3); InGameKey3 = false; ShowMessage("Хоткей 3 удален"); CheckBox4->Checked = false;}
if(InGameKey4) {UnregisterHotKey(Form1->Handle, 4); InGameKey4 = false; ShowMessage("Хоткей 4 удален"); CheckBox7->Checked = false;}

Timer2->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
if(Edit2->Text == "")
{
 GroupBox1->Enabled = false;
}
else
 GroupBox1->Enabled = true;


if((Edit2->Text == "") || (Edit1->Text == "") || ((Edit3->Text == "") || (Edit4->Text == "")))
{
	CheckBox1->Checked = false;
	CheckBox1->Enabled = false;
}
else
{
  CheckBox1->Enabled = true;
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
		if (hotid[0] == 1)
				{
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
					for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey4->HotKey) & 128 ) {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0); Sleep(500);}
					if( HIBYTE(HotKey4->HotKey) & 64 )  {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);  Sleep(500);}
					if( HIBYTE(HotKey4->HotKey) & 32 ) {PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);  Sleep(500);}
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey4->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey4->HotKey),0);
					if( HIBYTE(HotKey4->HotKey) & 128 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0); }
					if( HIBYTE(HotKey4->HotKey) & 64 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);   }
					if( HIBYTE(HotKey4->HotKey) & 32 ) {Sleep(500); PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0); }
					}

				}
		if (hotid[1] == 1)
				{
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				 for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey6->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey6->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey6->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey6->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey6->HotKey),0);
					if( HIBYTE(HotKey6->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey6->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey6->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
				}
		if (hotid[2] == 1)
				{
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey8->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey8->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey8->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey8->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey8->HotKey),0);
					if( HIBYTE(HotKey8->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey8->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey8->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
				}
		if (hotid[3] == 1)
				{
					if(Edit6->Text.ToInt() == 0)
					  mega_i=2;
					else
					  mega_i=0;
				for(mega_i;mega_i<3;mega_i++){
					if( HIBYTE(HotKey9->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_CONTROL,0);
					if( HIBYTE(HotKey9->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYDOWN,VK_MENU,0);
					if( HIBYTE(HotKey9->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYDOWN,VK_SHIFT,0);
						 PostMessage((HWND)hProc2,WM_KEYDOWN,LOBYTE(HotKey9->HotKey),0);
					Sleep(Edit6->Text.ToInt());
						 PostMessage((HWND)hProc2,WM_KEYUP,LOBYTE(HotKey9->HotKey),0);
					if( HIBYTE(HotKey9->HotKey) & 128 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_CONTROL,0);
					if( HIBYTE(HotKey9->HotKey) & 64 )  PostMessage((HWND)hProc2,WM_KEYUP,VK_MENU,0);
					if( HIBYTE(HotKey9->HotKey) & 32 ) PostMessage((HWND)hProc2,WM_KEYUP,VK_SHIFT,0);
					}
				}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
UnregisterHotKey(Form1->Handle, 101);
UnregisterHotKey(Form1->Handle, 102);
UnregisterHotKey(Form1->Handle, 103);
UnregisterHotKey(Form1->Handle, 107);
UnregisterHotKey(Form1->Handle, 1);
UnregisterHotKey(Form1->Handle, 2);
UnregisterHotKey(Form1->Handle, 3);
UnregisterHotKey(Form1->Handle, 4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
UnregisterHotKey(Form1->Handle, 101);
UnregisterHotKey(Form1->Handle, 102);
UnregisterHotKey(Form1->Handle, 103);
UnregisterHotKey(Form1->Handle, 107);
}
//---------------------------------------------------------------------------

