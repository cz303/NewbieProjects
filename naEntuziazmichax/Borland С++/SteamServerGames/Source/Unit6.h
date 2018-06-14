//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "sLabel.hpp"
#include "JvAnimatedImage.hpp"
#include "JvExControls.hpp"
#include "JvGIFCtrl.hpp"
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TImage *Image1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label2;
        TsWebLabel *Label1;
        TJvGIFAnimator *JvGIFAnimator1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Label1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
