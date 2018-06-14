//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "JvExComCtrls.hpp"
#include "JvHotKey.hpp"
#include <AppEvnts.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TButton *Button2;
	TButton *Button3;
	TMemo *Memo1;
	TApplicationEvents *ApplicationEvents1;
	TLabel *Label3;
	TEdit *Edit2;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit3;
	THotKey *HotKey1;
	TLabel *Label6;
	TCheckBox *CheckBox1;
	TTimer *Timer1;
	TEdit *Edit4;
	TLabel *Label7;
	TEdit *Edit5;
	TLabel *Label8;
	TGroupBox *GroupBox1;
	TLabel *Label9;
	THotKey *HotKey3;
	THotKey *HotKey4;
	TLabel *Label10;
	THotKey *HotKey5;
	THotKey *HotKey6;
	THotKey *HotKey7;
	THotKey *HotKey8;
	TButton *Button4;
	TButton *Button5;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TEdit *Edit6;
	TLabel *Label15;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TEdit *Edit7;
	TTimer *Timer2;
	TMemo *Memo2;
	TCheckBox *CheckBox7;
	THotKey *HotKey2;
	THotKey *HotKey9;
	TButton *Button6;
	TButton *Button7;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ApplicationEvents1Message(tagMSG &Msg, bool &Handled);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);




private:	// User declarations
public:
bool find;
short HPmin;
HANDLE hProc;
HANDLE hProc2;
LPBYTE HPAddress;
BYTE HP[8];
BYTE HPmax[8];
DWORD dwRead;
UINT Flags1;
UINT Flags2;
UINT Flags3;
UINT Flags4;
bool InGameKey1;
bool InGameKey2;
bool InGameKey3;
bool InGameKey4;
int mega_i;
short hotid[3];

	// User declarations

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
