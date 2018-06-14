//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "sDialogs.hpp"
#include "sComboBox.hpp"
#include "sComboBoxes.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TButton *Button1;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TButton *Button2;
        TEdit *Edit2;
        TButton *Button5;
        TsPathDialog *sPathDialog1;
        TLabel *Label8;
        TImageList *ImageList1;
        TsComboBoxEx *game;
        void __fastcall Label2Click(TObject *Sender);
        void __fastcall Label3Click(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall Label5Click(TObject *Sender);
        void __fastcall Label6Click(TObject *Sender);
        void __fastcall Label7Click(TObject *Sender);
        void __fastcall Label9Click(TObject *Sender);
        void __fastcall Label10Click(TObject *Sender);
        void __fastcall Label11Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Label8Click(TObject *Sender);
private:
void __fastcall create();	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
