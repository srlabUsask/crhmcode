// 09/12/16
//---------------------------------------------------------------------------

#ifndef reportH
#define reportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "MacroUnit.h"
//---------------------------------------------------------------------------
class TRprt : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Save1;
        TMenuItem *SaveAs1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TSaveDialog *SaveDialog1;
        TMenuItem *N2;
        TMenuItem *Print1;
        TMenuItem *PrintSetup1;
        TMenuItem *Font1;
        TMenuItem *N3;
        TMenuItem *Execution1;
        TMenuItem *Mapvars;
        TMenuItem *Mappars;
        TMenuItem *Lists1;
        TMenuItem *Bld1;
        TMenuItem *declvar1;
        TMenuItem *getvar1;
        TMenuItem *putvar1;
        TMenuItem *readvar1;
        TMenuItem *declobs1;
        TMenuItem *declpar1;
        TMenuItem *AllModulesList1;
        TMenuItem *OurModulesList1;
        TMenuItem *declstat1;
        TMenuItem *Global1;
        TMenuItem *AKA1;
        TMenuItem *MacroModulesList1;
        TMenuItem *Chart1;
        TMenuItem *Hierarchy1;
        TMenuItem *AKA2;
        TMenuItem *DeclRootList1;
        TMenuItem *Mapvarsget1;
        TMenuItem *Mapobsget1;
        TMenuItem *Mapvarsput1;
        TMenuItem *MapSharedpars1;
        TPanel *Panel3;
        TPanel *Panel1;
        TMemo *Memo1;
        TPanel *Panel2;
        TLabel *Label1;
        TListBox *ListBox1;
  TMenuItem *ExtractGroup;
        TMenuItem *RenameGroup;
        TEdit *Edit;
  TMenuItem *Extras1;
        TMenuItem *CheckNan1;
  TMenuItem *LOGVARLOAD1;
  TMenuItem *LogTimeFormat1;
  TMenuItem *MSTime1;
  TMenuItem *MMDDYYYY1;
  TMenuItem *YYYYMMDD1;
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall SaveAs1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Font1Click(TObject *Sender);
        void __fastcall Print1Click(TObject *Sender);
        void __fastcall PrintSetup1Click(TObject *Sender);
        void __fastcall MapvarsClick(TObject *Sender);
        void __fastcall MapparsClick(TObject *Sender);
        void __fastcall declvar1Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall getvar1Click(TObject *Sender);
        void __fastcall putvar1Click(TObject *Sender);
        void __fastcall readvar1Click(TObject *Sender);
        void __fastcall declobs1Click(TObject *Sender);
        void __fastcall declpar1Click(TObject *Sender);
        void __fastcall AllModulesList1Click(TObject *Sender);
        void __fastcall OurModulesList1Click(TObject *Sender);
        void __fastcall Label1Click(TObject *Sender);
        void __fastcall declstat1Click(TObject *Sender);
        void __fastcall Global1Click(TObject *Sender);
        void __fastcall AKA1Click(TObject *Sender);
        void __fastcall MacroModulesList1Click(TObject *Sender);
        void __fastcall Chart1Click(TObject *Sender);
        void __fastcall Hierarchy1Click(TObject *Sender);
        void __fastcall AKA2Click(TObject *Sender);
        void __fastcall DeclRootList1Click(TObject *Sender);
        void __fastcall Mapvarsget1Click(TObject *Sender);
        void __fastcall Mapobsget1Click(TObject *Sender);
        void __fastcall Mapvarsput1Click(TObject *Sender);
        void __fastcall MapSharedpars1Click(TObject *Sender);
        void __fastcall ExtractGroupClick(TObject *Sender);
        void __fastcall RenameGroupClick(TObject *Sender);
        void __fastcall EditKeyPress(TObject *Sender, char &Key);
        void __fastcall CheckNan1Click(TObject *Sender);
        void __fastcall LOGVARLOAD1Click(TObject *Sender);
  void __fastcall MSTime1Click(TObject *Sender);
  void __fastcall MMDDYYYY1Click(TObject *Sender);
  void __fastcall YYYYMMDD1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TRprt(TComponent* Owner);
        void __fastcall Expand_Grp_to_OurModuleList(TObject *Sender, long ii);
        void __fastcall HierarchyList(TObject *Sender);
        void __fastcall AddMacroCode(String S, TStringList *MacroModulesList, TStrings* Memo1, long &MacroPos);
        long __fastcall Add_NHRU(String S, TStringList *MacroModulesList);
        void __fastcall ExtractGroupFile(TObject *Sender, ClassModule *thisMod);
        long __fastcall findvar(TObject *Sender, String who, String what, bool &Self);
        long __fastcall findstatvar(TObject *Sender, String who, String what, bool &Self);
        bool __fastcall Not_Obs(String Mod, String Var);
        void __fastcall CheckNan1Init(TObject *Sender);
        void __fastcall LOGVARLOAD1Init(TObject *Sender);
        String  __fastcall Pnt(int P);
        TStringList * SummaryList;
        bool Rename_Changes;
        bool In_Rename;
};
//---------------------------------------------------------------------------
extern PACKAGE TRprt *Rprt;
//---------------------------------------------------------------------------
#endif
