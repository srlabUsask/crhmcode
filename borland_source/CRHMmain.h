// 08/02/17
//---------------------------------------------------------------------------
#ifndef CRHMmainH
#define CRHMmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "Chart.hpp"
#include "TeeComma.hpp"
#include "TeeEdiGene.hpp"
#include "TeeEdit.hpp"
#include "TeeNavigator.hpp"
#include "TeEngine.hpp"
#include "TeePageNumTool.hpp"
#include "TeeProcs.hpp"
#include "TeeTools.hpp"
#include <AppEvnts.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include "TeeComma.hpp"
#include "TeeEdiGene.hpp"
#include "TeeEdit.hpp"
#include "TeeNavigator.hpp"
#include "TeePageNumTool.hpp"
#include "TeeProcs.hpp"
#include "TeeTools.hpp"
#include <AppEvnts.hpp>
#include <TeeProcs.hpp>
#include "TeeEdiGene.hpp"
#include "TeeNavigator.hpp"
#include <AppEvnts.hpp>
#include "TeeComma.hpp"
#include "TeeEdit.hpp"
#include "TeePageNumTool.hpp"
#include "TeeTools.hpp"
#include "TeeComma.hpp"
#include "TeeNavigator.hpp"
#include "TeeEdiGene.hpp"
#include <AppEvnts.hpp>
#include "TeeEdit.hpp"
#include "TeeTools.hpp"
#include "TeePageNumTool.hpp"
#include <ToolWin.hpp>
#include <string>
#include <map>
#include <iostream>
#include <fstream.h>
#include <AppEvnts.hpp>
#include "ClassCRHM.h"
#include "boost/shared_ptr.hpp"

using namespace std;

//---------------------------------------------------------------------------
class TMain : public TForm
{
__published:	// IDE-managed Components
  TOpenDialog *OpenDialogObs;
  TMainMenu *MainMenu1;
  TMenuItem *FileMenu;
  TMenuItem *Open;
  TMenuItem *N1;
  TMenuItem *N2;
  TMenuItem *ObsClose;
  TMenuItem *Build;
  TMenuItem *Parameters;
  TMenuItem *Run;
  TMenuItem *Export;
  TMenuItem *Help;
  TMenuItem *About;
  TMenuItem *Construct;
  TSaveDialog *SaveDialogPar;
  TOpenDialog *OpenDialogPar;
  TMenuItem *Prjt;
  TStatusBar *StatusBar1;
  TMenuItem *PrjExit;
  TMenuItem *PrjOpen;
  TMenuItem *N5;
  TMenuItem *PrjSave;
  TMenuItem *PrjSaveAs;
  TMenuItem *N6;
  TPanel *Panel1;
  TMenuItem *PrjClose;
  TMenuItem *N7;
  TSaveDialog *SaveDialogPrj;
  TMenuItem *N8;
  TMenuItem *ClearModules1;
  TMenuItem *Stat;
  TMenuItem *StatOpenInit;
  TMenuItem *N9;
  TMenuItem *StatSave;
  TMenuItem *StatSaveStateAs;
  TSaveDialog *SaveDialogState;
  TOpenDialog *OpenDialogState;
  TPanel *Panel2;
  TMenuItem *Log;
  TMenuItem *N3;
  TMenuItem *HTMLhelp1;
  TMenuItem *N4;
  TMenuItem *PrjAutoRun;
  TMenuItem *N11;
  TMenuItem *PrjReport;
  TOpenDialog *OpenDialogDLL;
  TMenuItem *DLL1;
  TMenuItem *DLL1Open;
  TMenuItem *DLL1CloseALL;
  TMenuItem *N12;
  TMenuItem *N13;
  TPopupMenu *PopupListBox3;
  TMenuItem *DeleteListBox3;
  TMenuItem *NegateListBox3;
  TPopupMenu *PopupListBox4;
  TMenuItem *DeleteListBox4;
  TMenuItem *NegateListBox4;
  TPopupMenu *PopupListBox1;
  TMenuItem *AddListBox1;
  TPopupMenu *PopupListBox2;
  TMenuItem *AddListBox2;
  TMenuItem *FunctionListBox2;
  TMenuItem *HRUsAddListBox1;
  TMenuItem *N14;
  TMenuItem *LaysAdd1;
  TMenuItem *HRUsLAYsAdd1;
  TApplicationEvents *ApplicationEvents1;
  TMenuItem *Analysis1;
  TMenuItem *Variables;
  TMenuItem *FlowDiagram;
  TPanel *Panel3;
  TPanel *Panel4;
  TLabel *LabelObs;
  TPanel *Panel5;
  TLabel *LabelVar;
  TLabel *HruName;
  TPanel *Panel7;
  TLabel *FlipTic;
  TPanel *Panel6;
  TMenuItem *N15;
  TMenuItem *Log1;
  TMenuItem *Last1;
  TMenuItem *All1;
  TMenuItem *AddArray1;
  TMenuItem *N16;
  TMenuItem *N17;
  TMenuItem *PrjAutoExit;
  TMenuItem *N18;
  TMenuItem *Macro1;
  TMenuItem *N10;
  TPanel *Panel8;
  TPanel *Panel9;
  TLabel *Label5;
  TLabel *Label10;
  TListBox *ListBox2;
  TListBox *ListBox4;
  TPanel *Panel10;
  TLabel *LabelHRUIndx;
  TLabel *Label2;
  TUpDown *UpDownHRUIndx;
  TDateTimePicker *DateTimePicker1;
  TLabel *LabelOBSIndx;
  TLabel *Label3;
  TUpDown *UpDownOBSIndx;
  TDateTimePicker *DateTimePicker2;
  TLabel *LabelFunct;
  TPanel *Panel11;
  TLabel *Label1;
  TLabel *Label4;
  TPanel *Panel12;
  TListBox *ListBox1;
  TListBox *ListBox3;
  TPanel *Panel13;
  TPanel *Panel14;
  TChartPreviewer *ChartPreviewer1;
  TChartEditor *ChartEditor1;
  TPanel *Panel15;
  TTeeCommander *TeeCommander1;
  TChartPageNavigator *ChartPageNavigator1;
  TChart *Chart;
//  TRadioGroup *RadioGroup1;
  TRadioGroup *RadioGroupFunct;
  TRadioGroup *RadioGroupDisplay;
  TOpenDialog *OpenDialogPrj;
  TPageNumTool *ChartTool1;
  TMenuItem *N19;
  TMenuItem *SaveChartTemplate;
  TMenuItem *AddObsFunct1;
  TMenuItem *N20;
  TMenuItem *N21;
  TMenuItem *FreqDefault1;
  TMenuItem *N22;
  TMenuItem *N23;
  TMenuItem *PlotRefresh1;
  TMenuItem *daily1;
  TMenuItem *biweekly1;
  TMenuItem *weekly1;
  TMenuItem *monthly1;
  TMenuItem *atend1;
  TMenuItem *yearly1;
  TMenuItem *DebugScreen1;
  TLabel *LabelBase;
  TMenuItem *SummaryScreen1;
  TMenuItem *Abs1;
  TCoolBar *CoolBar1;
        TMenuItem *N24;
  
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall UpDownHRUIndxClick(TObject *Sender, TUDBtnType Button);
  void __fastcall ExitClick(TObject *Sender);
  void __fastcall OpenClick(TObject *Sender);
  void __fastcall ObsCloseClick(TObject *Sender);
  bool __fastcall OpenObsFile(TObject *Sender, String FileName);
  void __fastcall BldModelClick(TObject *Sender);
  void __fastcall RunClick(TObject *Sender);
  void __fastcall ExportClick(TObject *Sender);
  void __fastcall AboutClick(TObject *Sender);
  void __fastcall ListBox3Click(TObject *Sender);
  void __fastcall ConstructClick(TObject *Sender);
  void __fastcall InitModules(TObject *Sender);
  void __fastcall ListBox4Click(TObject *Sender);
  void __fastcall PrjExitClick(TObject *Sender);
  void __fastcall ObsFileClose(TObject *Sender);
  void __fastcall StateFileClose(TObject *Sender);
  void __fastcall StateFileCloseAll(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
  void __fastcall DateTimePicker1Change(TObject *Sender);
  void __fastcall DateTimePicker2Change(TObject *Sender);
  void __fastcall PrjOpenClick(TObject *Sender);
  void __fastcall PrjCloseClick(TObject *Sender);
  void __fastcall PrjSaveAsClick(TObject *Sender);
  void __fastcall PrjSaveClick(TObject *Sender);
  void __fastcall ClearModulesClick(TObject *Sender);
  void __fastcall ClearModules(TObject *Sender, bool All);
  void __fastcall StatSaveStateAsClick(TObject *Sender);
  void __fastcall StatSaveClick(TObject *Sender);
  void __fastcall StatOpenInitClick(TObject *Sender);
  void __fastcall LogClick(TObject *Sender);
  void __fastcall ParametersClick(TObject *Sender);
  void __fastcall UpDownOBSIndxClick(TObject *Sender, TUDBtnType Button);
  void __fastcall HTMLhelp1Click(TObject *Sender);
  void __fastcall PrjAutoRunClick(TObject *Sender);
  void __fastcall SqueezeParams(TObject *Sender);
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall PrjReportClick(TObject *Sender);
  void __fastcall DLL1OpenClick(TObject *Sender);
  void __fastcall DLL1CloseALLClick(TObject *Sender);
  void __fastcall DeleteListBox3Click(TObject *Sender);
  void __fastcall NegateListBox3Click(TObject *Sender);
  void __fastcall AbsListBox3Click(TObject *Sender);
  void __fastcall DeleteListBox4Click(TObject *Sender);
  void __fastcall ListBox4RemoveFuncts(TObject *Sender, String Svar);
  void __fastcall NegateListBox4Click(TObject *Sender);
  void __fastcall AddListBox1Click(TObject *Sender);
  void __fastcall ListBox1Click(TObject *Sender);
  void __fastcall AddListBox2Click(TObject *Sender);
  void __fastcall ListBox2Click(TObject *Sender);
  void __fastcall FunctionListBox2Click(TObject *Sender);
  void __fastcall LabelFunctClick(TObject *Sender);
  void __fastcall HRUsAddListBox1Click(TObject *Sender);
  void __fastcall FormClick(TObject *Sender);
  void __fastcall LAYsAddListBox1Click(TObject *Sender);
  void __fastcall HRUsLAYsAddListBox1Click(TObject *Sender);
  void __fastcall FlipTicMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall Analysis1Click(TObject *Sender);
  void __fastcall FlowDiagramClick(TObject *Sender);
  void __fastcall HruNameClick(TObject *Sender);
  void __fastcall Last1Click(TObject *Sender);
  void __fastcall All1Click(TObject *Sender);
  void __fastcall DebugScreen1Click(TObject *Sender);
  void __fastcall AddArray1Click(TObject *Sender);
  void __fastcall PrjAutoExitClick(TObject *Sender);
  void __fastcall Macro1Click(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall AKA1Click(TObject *Sender);
  void __fastcall SaveChartTemplateClick(TObject *Sender);
  void __fastcall AddObsFunct1Click(TObject *Sender);
  void __fastcall Label4Click(TObject *Sender);
  void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall ListBox1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
  void __fastcall FreqDefault1Click(TObject *Sender);
  void __fastcall daily1Click(TObject *Sender);
  void __fastcall biweekly1Click(TObject *Sender);
  void __fastcall weekly1Click(TObject *Sender);
  void __fastcall monthly1Click(TObject *Sender);
  void __fastcall atend1Click(TObject *Sender);
  void __fastcall yearly1Click(TObject *Sender);
  void __fastcall SummaryScreen1Click(TObject *Sender);
  void __fastcall LabelBaseMouseDown(TObject *Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall RadioGroupFunctClick(TObject *Sender);
  void __fastcall RadioGroupDisplayClick(TObject *Sender);
  void __fastcall CancelScreenClick(TObject *Sender);
private:	// User declarations
  void __fastcall AddObsPlot(TObject *Sender, ClassVar *thisVar, TLineSeries *cdSeries, String S, CRHM::TFun Funct);
  void __fastcall FreeChart1(TObject *Sender);
  void __fastcall FreeChart2(TObject *Sender);
  void __fastcall SaveProject(TObject *Sender);
  void __fastcall ClearListBox4(TObject *Sender);
  void __fastcall SaveState(TObject *Sender);
  void __fastcall ControlSaveState(TObject *Sender, bool MainLoop, ClassPar * VarPar, BitSet &Bit);
  void __fastcall ReadStateFile(TObject *Sender, bool & GoodRun);
  void __fastcall ControlReadState(TObject *Sender, bool MainLoop, ClassPar * VarPar = NULL);
  void __fastcall VariableBackUp(TObject *Sender);
  void __fastcall VariableRestore(TObject *Sender);
  void __fastcall ResetLoopList(TObject *Sender);
  void __fastcall OnHint(TObject *Sender);
  void __fastcall UpdateDim(CRHM::TDim Dim, long dim);
  bool __fastcall DllinUse(String FileName);
  void __fastcall DllFileClose(TObject *Sender);
  void __fastcall DllFileCloseAux(String FileName);
  void __fastcall DllDelete(String FileName);
  void __fastcall UpDateModelMenu(void);
  void __fastcall UpDateHelpMenu(void);
  void __fastcall DoPrjOpen(TObject *Sender);
  void __fastcall OpenHelp(TObject *Sender);
  void __fastcall DoObsStatus(TObject *Sender, bool &First);
  void __fastcall ResetPickers(void);
  void __fastcall VarObsFunct_Update(TObject *Sender);
  bool __fastcall AppHelp(WORD Command, int Data, bool &CallHelp);
  String __fastcall ExtractHruLay(String S, long &Hru, long &Lay);
  String __fastcall ExtractHruLayFunct(String S, long &Hru, long &Lay, String &Funct, String &FullName);
  String __fastcall BuildHru(String S, long Hru, CRHM::TDim dimen);
  String __fastcall BuildLay(String S, long Lay);
  bool HruNames;
  void __fastcall Last1Rprt(TObject *Sender);
  void __fastcall All1Rprt(TObject *Sender);
  void __fastcall SummaryScreen1Rprt(TObject *Sender);
  void __fastcall DebugScreen1Rprt(TObject *Sender);
  void __fastcall LastRprtObs(TObject *Sender);
  void __fastcall AllRprtObs(TObject *Sender);
  void __fastcall ParameterBackUp(TObject *Sender);
  void __fastcall ParameterRestore(TObject *Sender);
  void __fastcall MacroLoad(TObject *Sender);
  bool __fastcall FindFileName(String &FileName);
  bool __fastcall FileExistsSp(String FileName);
protected:
  void __fastcall WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg);  // prototype for msg handler
  void __fastcall WMMainUpdateDim(TMessage &Message);      // prototype for msg handler
  void __fastcall WMMainUpdateStatus(TMessage &Message);   // prototype for msg handler
  void __fastcall WMMainUpdateDirty(TMessage &Message);    // prototype for msg handler

  BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(WM_GETMINMAXINFO,TWMGetMinMaxInfo, WMGetMinMaxInfo)
    MESSAGE_HANDLER(WM_CRHM_Main_DIM,    TMessage, WMMainUpdateDim)
    MESSAGE_HANDLER(WM_CRHM_Main_STATUS, TMessage, WMMainUpdateStatus)
    MESSAGE_HANDLER(WM_CRHM_Main_DIRTY,  TMessage, WMMainUpdateDirty)
  END_MESSAGE_MAP(TForm)

public:		// User declarations
  __fastcall TMain(TComponent* Owner);
  void __fastcall RemoveSharedParams(void); // Replaces basin parameter with module parameters
  void __fastcall SetSharedParams(ClassPar *basinPar); // When loading projects converts shared parameters to module parameters
  void __fastcall CompactDlls(void);
  void __fastcall UpdateOurModules(void);
  bool __fastcall OpenDLLFile(String FileName);
  void __fastcall FileDefaults(TObject *Sender);
  String __fastcall HRUStdString(String S);
  void __fastcall ListBoxMacroClear(TObject *Sender);
  String __fastcall DeclObsName(ClassVar *thisVar);
  bool __fastcall TMain::isSimple(string module);
  bool Variation_Decide(int Variation_set, long Variation);

  TLineSeries **cdSeries;
  long SeriesCnt;
  long CurChartPage;
  bool dirty; // changes made to project
  bool cancel; // handles cancel from open new project with current dirty project

  TStringList *ObsFilesList;
  TStringList *ProjectList;
  TStringList *OpenDLLs;
  TStringList *PrjObsHelp;
  TStringList *ListHruNames;
  TStringList *LoopList;  // used by ControlReadState
  MapstrSS    *MapGrpNames;

  bool SaveStateFlag;
  bool ProjectOpen;
  bool ShiftDown; // Linked to ListBox1 and ListBox2

  typedef __declspec(dllimport) void LoadModuleType(String DllName);

  LoadModuleType *LoadUserModules;

  TDateTime ProjectFileDate;

  long __fastcall IndexOf(TListBox *Box, const AnsiString S);
  long __fastcall CheckforModule(String S, long Pos);
  long RefreshTime;

  long Max_Name_Width1; // used ListBox1/3 scrollbar
  long Max_Name_Width2; // used ListBox2/4 scrollbar
  
//  void __fastcall MacroLoad_X(TObject *Sender);
  void __fastcall CheckBlankModule(TObject *Sender);
  long __fastcall FindWildVarFloat(string name, ClassVar* &newVar, bool OnceFlag = false);
};

  class Classinfo; // used to process shared parameters
  
  typedef boost::shared_ptr<Classinfo> Pinfo;
  typedef pair<string, Pinfo>  Pairinfo;
  typedef multimap<string, Pinfo>  paras;

  typedef pair<string, ClassPar*>  PairPar;
  typedef multimap<string, ClassPar*>  GrpParas;

  class Classinfo {
    public:
    Classinfo() : thisPar(NULL), rootinfo(NULL), matched(false), cnt(0) {};
    Classinfo(ClassPar *thisPar) : thisPar(thisPar), rootinfo(NULL), matched(false), cnt(0) {};
    ClassPar *thisPar;
    Classinfo *rootinfo;
    long cnt;
    bool matched;
  };

  typedef pair<string, String>  PairDllModule;
  typedef multimap<string, String>  TDllModule;

  ClassVar *VarFind(string name);
  ClassPar *ParFind(string name);

  CRHM::TFun  FindObservationType(String Kind);

//---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
//---------------------------------------------------------------------------
#endif
