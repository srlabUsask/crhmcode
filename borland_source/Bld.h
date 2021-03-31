// 12/23/11
//---------------------------------------------------------------------------
#ifndef BldH
#define BldH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <Menus.hpp>
#include <map>
#include "GlobalCommon.h"
#include "ClassModule.h"
#include "Common.h"

using namespace std;

//---------------------------------------------------------------------------

class TBldForm : public TForm
{
__published:	// IDE-managed Components
  TStatusBar *StatusBar1;
  TPanel *Panel1;
  TMemo *Memo1;
  TStringGrid *StringGrid1;
  TPanel *Panel0;
  TPanel *Panel7;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel5;
  TLabel *LabelMAXLAY;
  TUpDown *UpDownMAXLAY;
  TPanel *Panel6;
  TLabel *LabelMAXHRU;
  TUpDown *UpDownMAXHRU;
  TPanel *Panel4;
  TButton *Check;
  TBitBtn *BitBtn1;
  TBitBtn *BitBtn2;
  TPanel *Panel8;
  TListBox *ListBox2;
  TListBox *ListBox1;
  TPanel *Panel9;
  TLabel *Label1;
  TLabel *Label2;
  TGroupBox *GroupBox1;
  TCheckListBox *CheckListBox1;
  TLabel *Label3;
  TPopupMenu *PopupMenuListBox1;
  TMenuItem *Add1;
  TPopupMenu *PopupMenuListBox2;
  TMenuItem *Delete1;
        TMenuItem *Variation1;
        TMenuItem *Last1;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall BitBtn2Click(TObject *Sender);
  void __fastcall CheckClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormDeactivate(TObject *Sender);
  void __fastcall UpDownMAXLAYClick(TObject *Sender, TUDBtnType Button);
  void __fastcall UpDownMAXHRUClick(TObject *Sender, TUDBtnType Button);
  void __fastcall BitBtn1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall AKAselectiveDelete(TObject *Sender);
  void __fastcall Label1Click(TObject *Sender);
  void __fastcall CheckListBox1ClickCheck(TObject *Sender);
  void __fastcall Add1Click(TObject *Sender);
  void __fastcall Delete1Click(TObject *Sender);
  void __fastcall ListBox2Click(TObject *Sender);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall Variation1Click(TObject *Sender);
  void __fastcall Last1Click(TObject *Sender);
private:	// User declarations

  TStringList *List; // source module + varName, original ListBox2 index
  TStringList *ListAll; // source module + varName, all module outputs. Detects double defines
  TStringList *ListUsed; // source module + varName, useage count
  TStringList *ListPuts; // source module + varName, useage count
  TStringList *ListStats; // source module + varName
  TStringList *ParaList;

  void __fastcall TBldForm::RemoveParameter(TObject *Sender);
  void __fastcall SaveBuildParameters(TObject *Sender);

public:		// User declarations
  __fastcall TBldForm(TComponent* Owner);
  void __fastcall DisplayModule(String S, ClassModule* thisModule, bool LBox1);
  long __fastcall Best_Match(String Var, TStringList *List);
  bool __fastcall Not_Obs(String Mod, String Var);
  long __fastcall CheckModel();
  void __fastcall ReadBuildParameters(TObject *Sender);
  void __fastcall SetSuffix(long Row);
  bool Execute;
  long __fastcall FormatMax(long M);
  TObject *ForceObject;
  Mapstr2 MapAKACopy;
  Mapstr2 MapAKAVar;
  
  int __fastcall IndexOf(TListBox *Box, const AnsiString S);
  bool Variation_Decide(int Variation_set, long Variation);
  bool Visible_Decide(long Variation);
  long Max_Name_Width1; // used ListBox1 scrollbar
  long Max_Name_Width2; // used ListBox2 scrollbar
};

//---------------------------------------------------------------------------
extern PACKAGE TBldForm *BldForm;
//---------------------------------------------------------------------------
#endif
