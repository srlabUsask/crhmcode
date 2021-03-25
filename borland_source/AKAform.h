// 03/14/10
//---------------------------------------------------------------------------

#ifndef AKAformH
#define AKAformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "Common.h"
#include "ClassModule.h"
//---------------------------------------------------------------------------
class TFormAKA : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel3;
  TMainMenu *MainMenu1;
  TOpenDialog *OpenDialogAKA;
  TSaveDialog *SaveDialogAKA;
  TMenuItem *File;
  TMenuItem *Open1;
  TMenuItem *N1;
  TMenuItem *Save;
  TMenuItem *SaveAs;
  TMenuItem *N2;
  TMenuItem *Exit;
  TPanel *Panel4;
  TButton *Save1;
  TButton *RemoveUnused;
  TButton *Void;
  TButton *Escape;
  TRadioGroup *RadioGroup;
  TMemo *Memo;
  TListBox *ListBox1;
  TStringGrid *StringGrid1;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
  int ARow, bool &CanSelect);
  void __fastcall StringGrid1KeyPress(TObject *Sender, char &Key);
  void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol,
  int ARow, const AnsiString Value);
  void __fastcall StringGrid1GetEditText(TObject *Sender, int ACol,
  int ARow, AnsiString &Value);
  void __fastcall Open1Click(TObject *Sender);
  void __fastcall SaveClick(TObject *Sender);
  void __fastcall SaveAsClick(TObject *Sender);
  void __fastcall ExitClick(TObject *Sender);
  void __fastcall RadioGroupClick(TObject *Sender);
  void __fastcall FormDeactivate(TObject *Sender);
  void __fastcall Save1Click(TObject *Sender);
  void __fastcall VoidClick(TObject *Sender);
  void __fastcall RemoveUnusedClick(TObject *Sender);
  void __fastcall EscapeClick(TObject *Sender);
  void __fastcall StringGrid1MouseDown(TObject *Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall MemoDblClick(TObject *Sender);
private:	// User declarations
  void __fastcall DrawGridVar(TObject *Sender);
  void __fastcall DrawGridObs(TObject *Sender);
  void __fastcall Gets1Click(TObject *Sender);
  void __fastcall SaveScreenCode(TObject *Sender);
  void __fastcall AKAseparate(TObject *Sender);
  bool __fastcall AKACheck(void);
  void __fastcall AKAcombine(TObject *Sender);
  void __fastcall ClearGrid(TObject *Sender);
  void __fastcall ReadMemo(TObject *Sender);
  bool __fastcall OriginalVar(String module, String name);
  bool __fastcall OriginalObs(String module, String name);
  void __fastcall DeleteRow(int Row);
  int __fastcall MatchMod_Name(String module, String name, int Col);
  int __fastcall MatchSimple_Name(String name, int Col);
  String  __fastcall GetUnits(String S, String SS);
  ClassVar* __fastcall GetVar(String S, String SS);
  void __fastcall AKAModuleDelete(Mapstr2 &MapAKAany);

  String LastValue, LocalValue;
  int selectCol, selectRow;
  int LastScreenIndex; // same as RadioGroup ItemIndex
  string module, name, Newname, source;

  Mapstr2 MapAKACopy;
  Mapstr2 MapAKAVar;
  Mapstr2 MapAKAPar;
  Mapstr2 MapAKAObs;
  Convert convert;

public:		// User declarations
  __fastcall TFormAKA(TComponent* Owner);
  TAKA Digest(Mapstr2::iterator it, string & module, string & name, string & Newname, string & source);
  bool __fastcall isGroup(string name);
  bool __fastcall isSame_decl(string name, string Newname);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormAKA *FormAKA;
//---------------------------------------------------------------------------
#endif
