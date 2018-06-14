//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include <FileCtrl.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TClientSocket *ClientSocket1;
	TMemo *Memo1;
	TButton *BSend;
	TEdit *Edit1;
	TLabeledEdit *LabeledEdit1;
	TLabeledEdit *LabeledEdit2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TTimer *Timer1;
	TComboBox *ComboBox1;
	TButton *Button4;
	TButton *Button5;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TLabeledEdit *LabeledEdit3;
	TLabeledEdit *LabeledEdit4;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button6;
	TButton *Button7;
	TLabel *Label3;
	TEdit *Edit2;
	TFileListBox *FileListBox1;
	TButton *Button9;
	TMemo *Memo2;
	TProgressBar *ProgressBar1;
	TGroupBox *GroupBox3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall BSendClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ClientSocket1Connecting(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);



private: 	// User declarations
public:		// User declarations
int TimeOut;
TDateTime d2;
void TForm2::Write( AnsiString Text);
HANDLE hthread;
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
