// 12/20/13
//---------------------------------------------------------------------------

#ifndef LogH
#define LogH
//---------------------------------------------------------------------------
using namespace std;

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <string>
#include "GlobalCommon.h"
#include "Common.h"

//---------------------------------------------------------------------------

class TLogForm : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *MainMenu1;
  TSaveDialog *SaveDialog1;
  TMenuItem *File;
  TMenuItem *FileSave;
  TMenuItem *FileSaveAs;
  TMenuItem *N1;
  TMenuItem *Exit1;
  TMenuItem *Clear;
  TMenuItem *ClearErrors;
  TMenuItem *ClearDebug;
  TMenuItem *Print1;
  TMenuItem *N2;
  TMenuItem *PrinterSetup1;
  TMenuItem *N3;
  TMenuItem *Font1;
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel4;
  TPanel *Panel5;
  TPanel *Panel6;
  TLabel *LabelLog;
  TLabel *LabelDebug;
  TMemo *MemoLog;
  TPanel *Panel7;
  TMemo *MemoDebug;
  TMenuItem *Flags1;
  TMenuItem *Coefficients1;
  TMenuItem *Parameters1;
  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall FileSaveClick(TObject *Sender);
  void __fastcall FileSaveAsClick(TObject *Sender);
  void __fastcall MemoLogEnter(TObject *Sender);
  void __fastcall MemoDebugEnter(TObject *Sender);
  void __fastcall ClearErrorsClick(TObject *Sender);
  void __fastcall ClearDebugClick(TObject *Sender);
  void __fastcall Print1Click(TObject *Sender);
  void __fastcall PrinterSetup1Click(TObject *Sender);
  void __fastcall Font1Click(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall Flags1Click(TObject *Sender);
  void __fastcall Coefficients1Click(TObject *Sender);
  void __fastcall Parameters1Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

protected:
  void __fastcall WMLogException(TMessage &Message);
  void __fastcall WMLogException1(TMessage &Message);
  void __fastcall WMLogDebug(TMessage &Message);

  BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_CRHM_LOG_EXCEPTION, TMessage, WMLogException)
    MESSAGE_HANDLER(WM_CRHM_LOG_EXCEPTION1, TMessage, WMLogException1)
    MESSAGE_HANDLER(WM_CRHM_LOG_DEBUG, TMessage, WMLogDebug)
  END_MESSAGE_MAP(TForm)

private:	// User declarations
  void __fastcall LogError(CRHMException Except);
  void __fastcall LogError(String S, TExcept Kind);
  TStringList *MemoDebugBkup;
  TStringList *MemoLogBkup;
  void __fastcall SaveMemoLog(TObject *Sender);
  void __fastcall SaveDebugLog(TObject *Sender);

public:		// User declarations
  __fastcall TLogForm(TComponent* Owner);
  void __fastcall ClearAllLogs(void);
  void __fastcall ClearRunLogs(void);

  TMemoSel MemoSel;
  long Warnings;
  long Errors;
  long DeclErrors;
};

//---------------------------------------------------------------------------
extern PACKAGE TLogForm *LogForm;
//---------------------------------------------------------------------------
#endif
