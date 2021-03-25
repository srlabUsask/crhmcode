// 10/30/09
//---------------------------------------------------------------------------

#ifndef FlowH
#define FlowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------

// Create a derived TPanel which has a Canvas property
class TBackPanel : public TPanel
{
    public:
        __fastcall TBackPanel(TComponent *Owner) : TPanel(Owner) { }
        __property Canvas;
};

//---------------------------------------------------------------------------
class TFlowForm : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *MainMenu1;
  TStringGrid *StringGrid1;
  TMenuItem *File1;
  TMenuItem *Print1;
  TMenuItem *N2;
  TMenuItem *Exit1;
  TPrinterSetupDialog *PrinterSetupDialog1;
  TPrintDialog *PrintDialog1;
  TMenuItem *PrinterSetUp1;
  TFontDialog *FontDialog1;
  TMenuItem *Selection1;
  TMenuItem *Copy1;
  TMenuItem *BitFile1;
  TMenuItem *MetaFile1;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall Exit1Click(TObject *Sender);
  void __fastcall FormResize(TObject *Sender);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall Print1Click(TObject *Sender);
  void __fastcall PrinterSetUp1Click(TObject *Sender);
  void __fastcall Selection1Click(TObject *Sender);
  void __fastcall BitFile1Click(TObject *Sender);
  void __fastcall MetaFile1Click(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
  void __fastcall DeleteCol(TStringGrid *Grid, int Column);
  void __fastcall DeleteBlankRows(TStringGrid *Grid);
  void __fastcall DeleteRow(TStringGrid *Grid, int Row);

  TMetafile *pMetafile;
  TMetafileCanvas *pFlow;
  TMetafileCanvas *zFlow;
  String Title;

public:		// User declarations
  __fastcall TFlowForm(TComponent* Owner);
  void __fastcall DrawGrid(TObject *Sender);
  void __fastcall DrawGridO(TObject *Sender);

  friend class Diagram;
  Diagram *OurDiagram;

//  TStringList *VarList;
  bool DisplyPar;
  int __fastcall GetNumVar(int Mod, int &First, int &Last);
  void SetTitle(String Text);
  TStringList *LocalModulesList;
  bool OurCntrl;
  int __fastcall TFlowForm::MatchDecl_Obs(String module, String Obs);
  bool Variation_Decide(int indx, long variation_set);
};

class Box {
public:
  int Xul;
  int Yul;
  int Xlr;
  int Ylr;
  int InCnt;   // number of variable inputs
  int OutCnt;  // number of used outputs
  int ObsCnt;  // number of input parameters or observations
  int ObsCntX; // number of input parameters or observations used more than once
  int Height;
  int CSpacing; // used to sync components
  int *OutXs;   // updated by GetXY
  int *OutYs;   // updated by GetXY
  int PadjX;    // make space for parameters or observations
  int PadjY;    // future space for Put inputs
  int MaxOutNameLen; // longest output variable name length locked to CSpacing

  Box() : Xul(0), Yul(0), Xlr(0), Ylr(0), InCnt(0), OutCnt(0),  ObsCnt(0), ObsCntX(0),
    OutXs(NULL), OutYs(NULL), PadjX(0), PadjY(0), MaxOutNameLen(0) {};
  ~Box();
  void GetXY(int Out_Var, int InX, int &ToX, int &ToY);  
};

class Diagram {

  TFlowForm *FlowForm;

  Box *Boxes;

  int Width;
  int Height;
  int HSpacing;
  int VSpacing;
  int CSpacing;
  
public:
  int Xmax;
  int Ymax;

public:
  Diagram(TFlowForm *FlowForm);
  ~Diagram();
  void DrawModules();

};

union ModandVar {

  int both;
  short int Module[2];
  int GetMod(void) {return Module[0];};
  void PutMod(int M) {Module[0] = M;};
  int GetVar(void) {return Module[1];};
  void PutVar(int V) {Module[1] = V;};

  int GetX(void) {return Module[0];};
  void PutX(int M) {Module[0] = M;};
  int GetY(void) {return Module[1];};
  void PutY(int V) {Module[1] = V;};
};

//---------------------------------------------------------------------------
extern PACKAGE TFlowForm *FlowForm;
//---------------------------------------------------------------------------
#endif
