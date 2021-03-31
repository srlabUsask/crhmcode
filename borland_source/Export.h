// 11/18/15
//---------------------------------------------------------------------------
#ifndef ExportH
#define ExportH
//---------------------------------------------------------------------------
using namespace std;

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "Common.h"
#include <ExtCtrls.hpp>
#include "ClassCRHM.h"
//---------------------------------------------------------------------------

class TFileOutput : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *MainMenu1;
  TMenuItem *FileMenu;
  TMenuItem *SaveAs;
  TMenuItem *Save;
  TMenuItem *N1;
  TMenuItem *Exit;
  TSaveDialog *SaveDialog1;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TLabel *Label2;
        TLabel *Label1;
        TListBox *ListBox2;
        TListBox *ListBox1;
        TButton *Button1;
        TButton *Button2;
        TPanel *Panel5;
        TMemo *Memo1;
//  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall ListBox2Click(TObject *Sender);
  void __fastcall ExitClick(TObject *Sender);
  void __fastcall SaveClick(TObject *Sender);
  void __fastcall SaveAsClick(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall DoSave(TObject *Sender);
private:	// User declarations
  long ShowLines;
  long MaxCount;
  long FirstFreq;
  long Indx1;
  TStringList *ExportList;
  CRHM::TDsply Dsply;

public:		// User declarations
  __fastcall TFileOutput(TComponent* Owner);
  int __fastcall IndexOf(TListBox *Box, const AnsiString S);
  long __fastcall GetFreq(TObject *Sender, long indx);

};

//---------------------------------------------------------------------------
extern PACKAGE TFileOutput *FileOutput;
//---------------------------------------------------------------------------
#endif
