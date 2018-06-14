//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H


//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "sSkinManager.hpp"
#include "sSplitter.hpp"
#include "sCurrEdit.hpp"
#include "sCurrencyEdit.hpp"
#include "sCustomComboEdit.hpp"
#include "sMaskEdit.hpp"
#include <Mask.hpp>
#include "sEdit.hpp"
#include <Graphics.hpp>
#include <AppEvnts.hpp>
#include "sStatusBar.hpp"
#include <ComCtrls.hpp>
#include "sHintManager.hpp"
#include <IdBaseComponent.hpp>
#include <IdNetworkCalculator.hpp>
#include <IdComponent.hpp>
#include <IdIPWatch.hpp>
#include <IdIntercept.hpp>
#include <IdSSLIntercept.hpp>
#include <IdSSLOpenSSL.hpp>
#include <ScktComp.hpp>
#include "acProgressBar.hpp"
#include "acHeaderControl.hpp"
#include <NMHttp.hpp>
#include <Psock.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "sLabel.hpp"
#include <Dialogs.hpp>
#include "trayicon.h"

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"


#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include "sComboBoxes.hpp"
#include <ImgList.hpp>

#include "sRichEdit.hpp"
#include "sDialogs.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *RUN;
        TGroupBox *serverstats;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TCheckBox *CheckBox3;
        TEdit *Edit1;
        TEdit *Edit6;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TRadioGroup *RadioGroup7;
        TRadioGroup *RadioGroup8;
        TRadioGroup *RadioGroup9;
        TRadioGroup *RadioGroup10;
        TRadioGroup *RadioGroup11;
        TRadioGroup *RadioGroup12;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N3;
        TMenuItem *N15;
        TMenuItem *N5;
        TMenuItem *N2;
        TMenuItem *sev;
        TMenuItem *auturan;
        TMenuItem *autoservr;
        TMenuItem *N4;
        TMenuItem *N8;
        TLabel *Label2;
        TsHintManager *sHintManager1;
        TButton *Button4;
        TsProgressBar *Dum1;
        TClientSocket *ClientSocket1;
        TEdit *Ater;
        TButton *Button5;
        TEdit *Edit2;
        TOpenDialog *OpenDialog1;
        TEdit *test;
        TOpenDialog *OpenDialog2;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *Ru;
        TMenuItem *En;
        TMenuItem *N6;
        TEdit *test2;
        TButton *Button6;
        TOpenDialog *OpenDialog3;
        TPopupMenu *PopupMenu1;
        TMenuItem *N7;
        TMenuItem *N11;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N16;
        TMenuItem *N17;
        TMenuItem *N18;
        TTrayIcon *TrayIcon1;
        TMenuItem *N22;
        TMenuItem *N25;
        TMenuItem *N26;
        TMenuItem *N27;
        TMenuItem *N28;
        TButton *Button7;
        TCppWebBrowser *CppWebBrowser1;
        TButton *Button8;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TEdit *Edit3;
        TButton *Button12;
        TButton *Button13;
        TButton *Button14;
        TCheckBox *CheckBox2;
        TTimer *Timer1;
        TMenuItem *N20;
        TMenuItem *N24;
        TsLabel *Label5;
        TsLabel *Label6;
        TButton *Button15;
        TTimer *Timer2;
        TsWebLabel *Label4;
        TLabel *Label3;
        TsSkinManager *sSkinManager1;
        TsRichEdit *RichEdit1;
        TsLabel *sLabel2;
        TMenuItem *N12;
        TMenuItem *Clienttxt1;
        TMenuItem *N19;
        TMenuItem *maplisttxt1;
        TMenuItem *SRCDSCFGCreator1;
        TMenuItem *pad;
        TCheckBox *CheckBox4;
        TMenuItem *N21;
        TMenuItem *Skin1;
        TMenuItem *Steam1;
        TMenuItem *Vista1;
        TMenuItem *WMP111;
        TMenuItem *Cold1;
        TMenuItem *Beijing1;
        TMenuItem *Neutral1;
        TMenuItem *NextAlpha1;
        TMenuItem *Officeblack1;
        TMenuItem *Retro1;
        TMenuItem *WLM1;
        TsComboBoxEx *game;
        TMenuItem *Winter1;
        TMenuItem *N23;
        TMenuItem *N29;
        TMenuItem *N30;
        TsOpenDialog *sOpenDialog1;
        TsSaveDialog *sSaveDialog1;
        TMenuItem *Chatonlineru1;
        TMenuItem *N31;
        TMenuItem *N32;
        TMenuItem *Chatonline1;
        void __fastcall sevClick(TObject *Sender);
        void __fastcall auturanClick(TObject *Sender);
        void __fastcall autoservrClick(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall sockConnecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall RUNClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall sLabel1Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall RuClick(TObject *Sender);
        void __fastcall EnClick(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall Label4Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
        void __fastcall N17Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall N19Click(TObject *Sender);
        void __fastcall clients1Click(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall N25Click(TObject *Sender);
        void __fastcall N28Click(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall TrayIcon1Minimize(TObject *Sender);
        void __fastcall N27Click(TObject *Sender);
        void __fastcall N26Click(TObject *Sender);
        void __fastcall TrayIcon1Restore(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall CppWebBrowser1DocumentComplete(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Button12Click(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall Edit8Change(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall N20Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Clienttxt1Click(TObject *Sender);
        void __fastcall HLSW1Click(TObject *Sender);
        void __fastcall maplisttxt1Click(TObject *Sender);
        void __fastcall SRCDSCFGCreator1Click(TObject *Sender);
        void __fastcall padClick(TObject *Sender);
        void __fastcall Steam1Click(TObject *Sender);
        void __fastcall Vista1Click(TObject *Sender);
        void __fastcall WMP111Click(TObject *Sender);
        void __fastcall Cold1Click(TObject *Sender);
        void __fastcall Beijing1Click(TObject *Sender);
        void __fastcall Neutral1Click(TObject *Sender);
        void __fastcall NextAlpha1Click(TObject *Sender);
        void __fastcall Officeblack1Click(TObject *Sender);
        void __fastcall Retro1Click(TObject *Sender);
        void __fastcall WLM1Click(TObject *Sender);
        void __fastcall Winter1Click(TObject *Sender);
        void __fastcall N29Click(TObject *Sender);
        void __fastcall N30Click(TObject *Sender);
        void __fastcall Chatonlineru1Click(TObject *Sender);
        void __fastcall Chatonline1Click(TObject *Sender);

private:
char tr;
char tr2;
char cl;
char tt;
char start1;
char start2;
char close;
char sizeform;
char statusop;
char tyi;
String currentcfg;
void __fastcall MyFunction();
void __fastcall MyFunction2();
void __fastcall sevdir();
void __fastcall OneSt();
void __fastcall sevop();
void __fastcall language();
int main(int argc, char* argv[]);
// User declarations
public:
char index;
char lang2;	// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
