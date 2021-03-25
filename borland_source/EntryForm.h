// 01/14/08
//---------------------------------------------------------------------------

#ifndef EntryFormH
#define EntryFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class Module {
public:
  Module() : head(0), tail(0), avail(false), isGroup(false), isStruct(false){};
  int head;
  int tail;
  bool avail;
  bool isGroup;
  bool isStruct;
  static long GrpCnt;
  static long StructCnt;
};

class TFormEntry : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *MainMenu;
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *Panel3;
  TPanel *Panel4;
  TMemo *Memo;
  TMenuItem *File;
  TMenuItem *N1;
  TMenuItem *Save;
  TMenuItem *SaveAs;
  TMenuItem *N2;
  TMenuItem *Exit;
  TSaveDialog *SaveDialogMcr;
  TOpenDialog *OpenDialogMcr;
  TMenuItem *Open;
  TButton *SaveChanges;
  TButton *CancelChanges;
  TMemo *MemoFile;
  TMenuItem *N3;
  TMenuItem *Clear1;
  TMenuItem *N4;
  TMenuItem *CreateGroup1;
        TSaveDialog *SaveDialogPar;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall ExitClick(TObject *Sender);
  void __fastcall SaveClick(TObject *Sender);
  void __fastcall SaveAsClick(TObject *Sender);
  void __fastcall OpenClick(TObject *Sender);
  void __fastcall SaveChangesClick(TObject *Sender);
  void __fastcall CancelChangesClick(TObject *Sender);
  void __fastcall ClearClick(TObject *Sender);
        void __fastcall CreateGroup1Click(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
  void __fastcall DoSave(TObject *Sender);
  void __fastcall DoLoad(TObject *Sender);
public:		// User declarations
  __fastcall TFormEntry(TComponent* Owner);
  void __fastcall AddGroup(int ii);
  void __fastcall AddSupport(Module* ThisModule);
  TStringList *ProjectFile; // hold project file
  TStringList *ModuleList;  // list of modules in group
  TStringList *MacroList;   // macros in project file
  TStringList *DefinedList; // macros already defined
  TStringList *ParaList;    // defined parameters
  TStringList *AKAList;     // AKA defines
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEntry *FormEntry;
//---------------------------------------------------------------------------
#endif
