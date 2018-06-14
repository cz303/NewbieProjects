//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#define MAX_READ 128


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int fMatchCheck (char *mainstr, int mainstrLen, char *checkstr, int checkstrLen)
{
/*
Проверка наличия подстроки в строке.
При этом под "строкой" подразумевается
просто последовательность байт.
*/
BOOL fmcret=TRUE;
int x,y;

for (x=0; x<mainstrLen; x++) {
fmcret=TRUE;

for (y=0; y<checkstrLen; y++) {
if (checkstr[y]!=mainstr[x+y]) {
fmcret=FALSE;
break;
}
}

if (fmcret)
return x+checkstrLen;
}
return -1;
}


char *getMem(char *buff, size_t buffLen, int from, int to)
{
/*
Выделяем у себя память, в которой будем хранить
копию данных из памяти чужой программы.
*/
size_t ourSize = buffLen*2;
char *ret = (char*)malloc(ourSize);

memset(ret, 0, ourSize);

memcpy(ret, &buff[from], buffLen-from);
memset(&ret[to-from], 0, to-from);

return ret;
}

char *delMem(char *buff, size_t buffLen, int from, int to)
{
/*
Освобождаем память.
*/
size_t ourSize = buffLen*2;
char *ret = (char*)malloc(ourSize);
int i,x=0;

memset(ret, 0, ourSize);

for (i=0; (unsigned)i<buffLen; i++) {
if (!(i>=from&&i<to)) {
ret[x]=buff[i];
x++;
}
}

return ret;
}

char *addMem(char *buff, size_t buffLen, char *buffToAdd, size_t addLen, int addFrom)
{
/*
Запись в память.
*/
size_t ourSize = (buffLen+addLen)*2;
char *ret = (char*)malloc(ourSize);
int i,x=0;

memset(ret, 0, ourSize);

memcpy(ret, getMem(buff, buffLen, 0, addFrom), addFrom);

x=0;
for (i=addFrom; (unsigned)i<addLen+addFrom; i++) {
ret[i]=buffToAdd[x];
x++;
}

x=0;
for (i; (unsigned)i<addFrom+buffLen; i++) {
ret[i]=buff[addFrom+x];
x++;
}

return ret;
}

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


void __fastcall TForm1::Button1Click(TObject *Sender)
{
/*** VARIABLES ***/
HANDLE hProc;

MEMORY_BASIC_INFORMATION mbi;
SYSTEM_INFO msi;
ZeroMemory(&mbi, sizeof(mbi));
GetSystemInfo(&msi);
/*
Получаем информацию о памяти в текущей системе.
*/

DWORD dwRead=0;

int x,at;
BYTE lpData[8];
BYTE Code[8];
/*****************/


ZeroMemory(lpData, MAX_READ);

// открываем процесс

hProc = OpenProcess (PROCESS_ALL_ACCESS,
FALSE,
Edit1->Text.ToInt());



for(LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress;
lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress;
lpAddress += mbi.RegionSize){
/*
Этот цикл отвечает как раз за то, что наша программа не совершит
лишних действий. Память в Windows в процессе делится на "регионы".
У каждого региона свой уровень доступа: к какому-то доступ запрещен,
какой-то можно только прочитать. Нам нужны регионы доступные для записи.
Это позволит в разы ускорить работу поиска по памяти и избежать ошибок
записи в память. Именно так работает ArtMoney.
*/

if(VirtualQueryEx(hProc, lpAddress, &mbi, sizeof(mbi))){
/*
Узнаем о текущем регионе памяти.
*/

if((mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_WRITECOPY)){
/*
Если он доступен для записи, работаем с ним.
*/

for (lpAddress;
lpAddress<(lpAddress + mbi.RegionSize);
lpAddress+=0x00000100) {
/*
Проходим по адресам указателей в памяти чужого процесса от начала, до конца региона
и проверяем, не в них ли строка поиска.
*/

dwRead=0;
if (ReadProcessMemory (hProc,
(LPCVOID)lpAddress,
lpData,
MAX_READ,
&dwRead) == TRUE) {
/*
Читаем по 128 байт из памяти чужого процесса от начала
и проверяем, не в них ли строка поиска.
*/

char lpOrig [] = {0x04,0x00,0x00,0x00,0x0D,0x00,0x00,0x00,0x1B,0x02,0x00,0x00,0x00,0x00,0x00,0x00};

if (fMatchCheck(lpData, dwRead, lpOrig, sizeof(lpOrig)-1)!=-1) {


Label1->Caption = *lpAddress;
ReadProcessMemory(hProc,(LPCVOID)(lpAddress+0x00000100),Code,8,NULL);
Label2->Caption = *(__int64*)Code;
}

}
}

}

}
}

// // // // //
// Cleanup
if (hProc)
CloseHandle(hProc);
if (lpData)
GlobalFree(lpData);
///////////////
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
BYTE lp [] = {0x04,0x00,0x00,0x00,0x0D,0x00,0x00,0x00,0xD7,0x02,0x00,0x00,0x00,0x00,0x00,0x00};
Label2->Caption = *(__int64*)lp;
}
//---------------------------------------------------------------------------

