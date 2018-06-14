//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "TeCanvas.hpp"
#include "TeePenDlg.hpp"
#include <Buttons.hpp>
#include "sColorSelect.hpp"
#include "sSpeedButton.hpp"
#include "sSkinManager.hpp"
#include "sCheckBox.hpp"
#include "acProgressBar.hpp"
#include "sLabel.hpp"
#include "sEdit.hpp"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *F1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TEdit *Edit1;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TGroupBox *GroupBox4;
	TImage *Image1;
	TButton *Button2;
	TLabel *Label5;
	TEdit *Mo;
	TRichEdit *RichEdit1;
	TsSkinManager *sSkinManager1;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N10;
	TMenuItem *N7;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TsProgressBar *sProgressBar1;
	TMenuItem *N19;
	TMenuItem *N21;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N20;
	TsLabel *sLabel1;
	TsLabel *sLabel2;
	TsLabel *ResultLabel;
	TsLabel *sLabel3;
	TsLabel *sLabel4;
	TsLabel *Label10;
	TGroupBox *GroupBox1;
	TsColorSelect *sColorSelect1;
	TsColorSelect *sColorSelect2;
	TsColorSelect *sColorSelect3;
	TsColorSelect *sColorSelect4;
	TsLabel *sLabel5;
	TsLabel *sLabel6;
	TsLabel *sLabel7;
	TsLabel *sLabel8;
	TsLabel *sLabel9;
	TsLabel *sLabel10;
	TsLabel *sLabel11;
	TsLabel *sLabel12;
	TsLabel *sLabel13;
	TsEdit *LabX2;
	TsEdit *LabY2;
	TsEdit *LabX1;
	TsEdit *LabY1;
	TsEdit *LabX;
	TsEdit *LabY;
	TsEdit *LabR;
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall MoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabXKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabYKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabRKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabX1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabY1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabX2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall LabY2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall MoExit(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall sColorSelect1Change(TObject *Sender);
	void __fastcall sColorSelect2Change(TObject *Sender);
	void __fastcall sColorSelect3Change(TObject *Sender);
	void __fastcall sColorSelect4Change(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N15Click(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall N17Click(TObject *Sender);
	void __fastcall N18Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N20Click(TObject *Sender);

private:	// User declarations
bool findsimvol(String s1,String s2);
int findsubs(String,String,int);
double max(double,double);
double min(double,double);
double round (double,int);
void __fastcall setskin(short);
short index;
bool save;
int allperes,findcout;


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
