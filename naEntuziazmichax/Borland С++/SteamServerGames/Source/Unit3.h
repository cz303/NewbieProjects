//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <ScktComp.hpp>
#include "sLabel.hpp"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TCppWebBrowser *CppWebBrowser1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TClientSocket *ClientSocket1;
        TCheckBox *upd;
        TButton *Button5;
        TsLabel *Label1;
        TsLabel *Label2;
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall Button5Click(TObject *Sender);
private:
char clos;	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
 