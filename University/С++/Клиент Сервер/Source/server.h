//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <FileCtrl.hpp>
#include <ScktComp.hpp>
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include "sTooledit.hpp"
#include <Mask.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TServerSocket *ServerSocket1;
	TFileListBox *FileListBox1;
	TsDirectoryEdit *sDirectoryEdit1;
	TMemo *Memo1;
	TButton *BSend;
	TEdit *Edit1;
	TLabeledEdit *LabeledEdit1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall sDirectoryEdit1Change(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall BSendClick(TObject *Sender);
	void __fastcall ServerSocket1ClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ServerSocket1ClientConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);



private:	// User declarations
public:		// User declarations
TDateTime d2;
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
