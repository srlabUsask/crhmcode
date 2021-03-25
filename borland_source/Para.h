// 05/21/09
//---------------------------------------------------------------------------
#ifndef ParaH
#define ParaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TParameter : public TForm
{
__published:	// IDE-managed Components
  TOpenDialog *OpenDialogPar;
  TSaveDialog *SaveDialogPar;
  TMainMenu *MainMenu1;
  TMenuItem *File;
  TMenuItem *FileSave;
  TMenuItem *FileSaveAs;
  TMenuItem *N1;
  TMenuItem *FileExit;
  TMenuItem *FileOpen;
  TMenuItem *N2;
  TPanel *Panel1;
  TLabel *Label1;
  TPanel *Panel2;
  TListBox *ListBox1;
  TPanel *Panel3;
  TStringGrid *StringGrid1;
  TPanel *Panel4;
  TLabel *Label3;
  TLabel *LabelHelp;
  TPanel *Panel5;
  TLabel *Label4;
  TLabel *LabelUnits;
  TLabel *Label2;
  TPanel *Panel7;
  TLabel *Label5;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall StringGrid1GetEditText(TObject *Sender, int ACol,
  int ARow, AnsiString &Value);
  void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
  int ARow, bool &CanSelect);
  void __fastcall FileExitClick(TObject *Sender);
  void __fastcall FileSaveClick(TObject *Sender);
  void __fastcall FileSaveAsClick(TObject *Sender);
  void __fastcall SaveParameters(TObject *Sender);
  void __fastcall FileOpenClick(TObject *Sender);
  void __fastcall FindParaCount(TObject *Sender, int Indx);
  void __fastcall DisplayBasin(TObject *Sender, int Indx, int Rows);
  void __fastcall StringGrid1KeyPress(TObject *Sender, char &Key);
  void __fastcall StringGrid1SetEditText(TObject *Sender, int ACol,
  int ARow, const AnsiString Value);
  bool __fastcall FileExistsSp(String FileName);
        void __fastcall Label5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TParameter(TComponent* Owner);
  bool Variation_Decide(long variation, long variation_set);
  TStringList *ParaList;
  long ParaCount;
  long LocalParaCount;
  long endLocal;
  long endBasin;
  bool dirty;
  long ExtraCols;
};
//---------------------------------------------------------------------------
extern PACKAGE TParameter *Parameter;
//---------------------------------------------------------------------------
#endif
