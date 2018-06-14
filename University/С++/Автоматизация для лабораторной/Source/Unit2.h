//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "sButton.hpp"
#include "sEdit.hpp"
#include "sLabel.hpp"
#include "sMemo.hpp"
#include "sSkinManager.hpp"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo3;
	TMemo *Memo2;
	TLabel *Дата;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TButton *Button1;
	TMemo *Memo1;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TMemo *Memo4;
	TLabel *Label9;
	TLabel *Label10;
	TsSkinManager *sSkinManager1;
	TMemo *Memo5;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:
String  to2(int);
String  to3(int);
String  to5(int);
String  to8(int);
String  to16(int);
int  hexTOdec(String);
String  plustoplus5(String,String);
String  decTOhex(String);
int max(int,int);

	// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
