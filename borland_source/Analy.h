// 01/30/14
//---------------------------------------------------------------------------
#ifndef AnalyH
#define AnalyH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "Numerical.h"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include "Common.h"
#include "TeeComma.hpp"
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "TeeEdiGene.hpp"
#include "TeeNavigator.hpp"
#include "TeeEdit.hpp"
//---------------------------------------------------------------------------
using namespace std;
using namespace Numerical;

class TAnalysis : public TForm
{
__published:	// IDE-managed Components
  TMainMenu *MainMenu1;
  TSaveDialog *SaveDialog1;
  TMenuItem *File;
  TMenuItem *Save;
  TMenuItem *SaveAs;
  TMenuItem *N1;
  TMenuItem *Exit;
  TPopupMenu *PopupMenu1;
  TChart *Chart;
  TTeeCommander *TeeCommander1;
  TPanel *Panel1;
  TPanel *Panel6;
  TMemo *Memo1;
  TPanel *Panel4;
  TListBox *ListBox1;
  TListBox *ListBox2;
  TPanel *Panel8;
  TPanel *Panel5;
  TRadioGroup *RadioGroup2;
  TRadioGroup *RadioGroup1;
  TPanel *Panel7;
  TPanel *Panel3;
  TLabel *Label1;
  TUpDown *UpDown1;
  TPanel *Panel2;
  TButton *Button1;
  TButton *Button2;
  TChartPageNavigator *ChartPageNavigator1;
  TChartEditor *ChartEditor1;
  TChartPreviewer *ChartPreviewer1;
  TDateTimePicker *DateTimePicker1;
  TDateTimePicker *DateTimePicker2;
        TLabel *Label2;
        TLabel *Label3;
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall ListBox2Click(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
  void __fastcall RadioGroup1Click(TObject *Sender);
  void __fastcall RadioGroup2Click(TObject *Sender);
  void __fastcall SaveClick(TObject *Sender);
  void __fastcall SaveAsClick(TObject *Sender);
  void __fastcall ExitClick(TObject *Sender);
  void __fastcall DoSave(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall Button2Click(TObject *Sender);
  private:	// User declarations
  long ShowLines;
  CRHM::TDsply Dsply;

  public:		// User declarations

  __fastcall TAnalysis(TComponent* Owner);
  void __fastcall CleanUp(TObject *Sender);
  long __fastcall IndexOf(TListBox *Box, const AnsiString S);
};

class Plot {
  public:
  TLineSeries *MySeries;
  TLineSeries *FitSeries;
  LeastSquares *MyFit;
  long NumTerms;
  int Error;
  
  static TLineSeries *FirstSeries;
  static CRHM::TFitType FitType;
  static CRHM::TAgainst Against;
  Plot(long Index);
  ~Plot();

  void  OutFit(TLineSeries *OutSeries);
};

//---------------------------------------------------------------------------
extern PACKAGE TAnalysis *Analysis;
//---------------------------------------------------------------------------
#endif
