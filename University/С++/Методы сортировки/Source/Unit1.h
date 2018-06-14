//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *EMn;
	TEdit *EMm;
	TLabel *Label1;
	TLabel *Label2;
	TCheckBox *CNegative;
	TMemo *Memo1;
	TButton *CreateMas;
	TButton *Start;
	TCheckBox *CRealTime;
	TCheckBox *CParalel;
	TMemo *Memo2;
	TMemo *Memo3;
	TMemo *Memo4;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EMaxNumber;
	TLabel *Label6;
	TLabel *Label7;
	TGroupBox *MasSetup;
	TGroupBox *Result;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *LOpX;
	TLabel *LTimeX;
	TLabel *LOpP;
	TLabel *LTimeP;
	TLabel *LOpI;
	TLabel *LTimeI;
	TCheckBox *CPusyr;
	TCheckBox *CInsert;
	TCheckBox *CXoar;
	TCheckBox *CShell;
	TLabel *Label8;
	TLabel *Label11;
	TLabel *LOpS;
	TLabel *LTimeS;
	TLabel *Label14;
	TMemo *Memo5;
	TButton *TerminatedThear;
	void __fastcall CreateMasClick(TObject *Sender);
	void __fastcall StartClick(TObject *Sender);
	void __fastcall EMnChange(TObject *Sender);
	void __fastcall CNegativeClick(TObject *Sender);
	void __fastcall TerminatedThearClick(TObject *Sender);
private:	// User declarations
int * array;  // Указатель для динамического массива

/*- Функции сортировки -*/
void  TForm1::SortXoar();
void  TForm1::SortMarge();
void  TForm1::mergeSort(int *a, int len, TTime time);
int*  TForm1::merge(int *m1, int* m2, int l1, int l2);
void  TForm1::SortQuick1(int *, int, int);
void  TForm1::SortQuick2(int *, int, int,  TTime);
void  TForm1::SortInsert();
void  TForm1::SortShell();
/*- .Функции сортировки -*/

// Функция возвращает массив в виде текста
String  TForm1::Print(int *);

/*- Для потоков -*/
static DWORD __stdcall TForm1::SortP(LPVOID);
static DWORD __stdcall TForm1::SortX(LPVOID);
static DWORD __stdcall TForm1::SortI(LPVOID);
static DWORD __stdcall TForm1::SortS(LPVOID);
static DWORD __stdcall TForm1::StartChek(LPVOID);
HANDLE hthread1,hthread2,hthread3,hthread4,hthread5;
bool ok[4];
/*- .Для потоков -*/

/*- Счетчики -*/
int CountOpX;
int CountOpP;
int CountOpI;
int CountOpS;
String  TForm1::FormatInt(double);
/*- .Счетчики -*/

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
