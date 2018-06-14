//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include "sLabel.hpp"
//---------------------------------------------------------------------------
class TForm5 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *Name;
        TLabel *Label2;
        TEdit *Steamid;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TEdit *Nik;
        TLabel *Label5;
        TEdit *Pass;
        TLabel *Label3;
        TEdit *idip;
        TSaveDialog *SaveDialog1;
        TsWebLabel *Label4;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:
void __fastcall Generate();
// User declarations
public:		// User declarations
        __fastcall TForm5(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
