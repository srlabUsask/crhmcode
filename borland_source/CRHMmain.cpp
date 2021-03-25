// 03/15/21 add conditional statement to restrict divided by zero error
// in Volumetric module 02/01/21
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#define CurrentVersion "03/15/21"

#include <stdexcept>
#include "CRHMmain.h"
#include "Common.h"
#include "Para.h"
#include "About.h"
#include "Bld.h"
#include "Log.h"
#include "Export.h"
#include "report.h"
#include "ClassModule.h"
#include <sstream>
#include <iostream>
#include <fstream.h>
#include "SysUtils.hpp"
#include "htmlhelp.h"
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include "Analy.h"
#include "Flow.h"
#include "EntryForm.h"
#include "MacroUnit.h"
#include "UpdateForm.h"
#include <Forms.hpp>
#include "TeeThemes.hpp"
#include "TeeStore.hpp"
#include "AKAform.h"
#include <FileCtrl.hpp>
#include <StrUtils.hpp>
#include <vector>
#include <math.hpp>

#if !defined NO_MODULES
  #if defined QUINTON
    #include "quinton2.h"
    #include "quinton2.cpp"
  #elif defined CRHM_DLL
    #include "NewModules.h"
    #include "NewModules.cpp"
  #else
    #include "NewModules.h"
    #include "NewModules.cpp"
  #endif
#endif

Administer AdminMacro("03/24/06", "Macro");

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeComma"
#pragma link "TeeNavigator"
#pragma link "TeeEdiGene"
#pragma link "TeeEdit"
#pragma link "TeeTools"
#pragma link "TeeThemeEditor"
#pragma link "TeePageNumTool"
#pragma link "TeeEdiGene"
#pragma link "TeeNavigator"
#pragma link "TeeComma"
#pragma link "TeeEdit"
#pragma link "TeePageNumTool"
#pragma link "TeeTools"
#pragma link "TeeComma"
#pragma link "TeeEdiGene"
#pragma link "TeeEdit"
#pragma link "TeeNavigator"
#pragma link "TeePageNumTool"
#pragma link "TeeProcs"
#pragma link "TeeTools"
#pragma link "Chart"
#pragma link "TeeComma"
#pragma link "TeeEdiGene"
#pragma link "TeeEdit"
#pragma link "TeeNavigator"
#pragma link "TeEngine"
#pragma link "TeePageNumTool"
#pragma link "TeeProcs"
#pragma link "TeeTools"
#pragma resource "*.dfm"

int _matherr (struct _exception *a){
  char Error[][10] = {"NONE", "DOMAIN","SING","OVERFLOW","UNDERFLOW","TLOSS"};
  CRHMException Except((String(Error[a->type]) + " error in function '" + a->name + "' ").c_str(), TERMINATE);
  throw Except;
}

using namespace std;

TMain *Main;

Global global;

extern double xLimit;
extern long lLimit;

bool CommandLine = false;

String ApplicationDir = ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
String ProjectDir = ApplicationDir;

String FStrings[] = {"Observation", "VP_saturated", "W_to_MJ/Int", "MJ/Int_to_W", "Average", "Minimum", "Maximum", "Total", "Positive",
                     "First", "Last", "Count", "Count0", "Delta", "Intvl"};
String Sstrings[] = {"", "_VPsat", "_WtoMJ", "_MJtoW", "_Avg", "_Min", "_Max", "_Tot", "_Pos", "_First", "_Last", "_Cnt", "_Cnt0", "_Dlta"};

String TBases[] = {"Daily", "Water_year", "Calendar_year", "Monthly_summary", "Summarize_all"};
String Tmonths[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
String TLogFormats[] = {"MS_time", "MM/DD/YYYY", "YYYY-MM-DD"};
long water_year_month = 10;

extern string AKAstrings[];

CRHM::TFun Funct = CRHM::FOBS;

long ObsFunct_Toggle = 0; // no display/Final/Trend values


int InitModCnt = 0;
int InitMacroCnt = 0;
long TBase;

long Box1Disply = CRHM::USUAL; // always starts with this display

bool KeyShift = false;

string DescripPrj("Description - to be added");

ClassPar *StatePar = NULL; // used to handle basin StateVars_to_Handle

// clWebTomato - 0x4763FF, clWebSalmon - 0x7280FA, clWebFuchsia - 0xFF00FF, clWebDarkOrange - 0x008CFF, clWebChartreuse - 0x00FF7F, clWebGoldenRod - 0x20A5DA
const long colours[] = {clBlack, clDkGray, clBlue, clTeal, clFuchsia, clGreen, clNavy, clMaroon, clNavy, clOlive, clPurple, clRed, clTeal, clMaroon, 0x4763FF, 0x7280FA, 0xFF00FF, 0x008CFF, 0x00FF7F, 0x20A5DA};

long ncolours = (sizeof colours)/4; // long is 4 bytes

TColor CurrentColor;

long TempTime;

//---------------------------------------------------------------------------

__fastcall TMain::TMain(TComponent* Owner)
  : TForm(Owner)
{
  ListHruNames = NULL;
  MapGrpNames = NULL;
  HruNames = False;
  dirty = false;
  RefreshTime = 0;
}

//---------------------------------------------------------------------------

void __fastcall TMain::FileDefaults(TObject *Sender){

  OpenDialogPrj->InitialDir = GetCurrentDir();
  SaveDialogPrj->InitialDir = GetCurrentDir();
  OpenDialogObs->InitialDir = GetCurrentDir();
  OpenDialogState->InitialDir = GetCurrentDir();
  SaveDialogState->InitialDir = GetCurrentDir();
  OpenDialogDLL->InitialDir = ApplicationDir;
}

//---------------------------------------------------------------------------

void __fastcall TMain::FormCreate(TObject *Sender){

  OpenDialogPrj->InitialDir = GetCurrentDir();
  SaveDialogPrj->InitialDir = GetCurrentDir();
  OpenDialogObs->InitialDir = GetCurrentDir();
  OpenDialogState->InitialDir = GetCurrentDir();
  SaveDialogState->InitialDir = GetCurrentDir();
  OpenDialogDLL->InitialDir = ApplicationDir;

  ProjectOpen = false;

  float W = Screen->Width;
  float H = Screen->Height;

  Width = W/H * Height;

  Application->OnHint = OnHint;
  Application->ShowHint = true;
  Application->OnHelp = AppHelp;

  ApplicationEvents1->Activate();
  HelpContext = 1000;

  Global::BuildFlag = CRHM::BUILD;

  Global::maxhru = 1;
  Global::maxlay = 1;
  Global::maxobs = 1;

  Global::Freq = 48;
  Global::Interval = 1.0/Global::Freq;
  TBase = 0;

  cdSeries = NULL;

  TDateTime Dt = TDateTime::CurrentDate();

  DateTimePicker1->Date = Dt;
  DateTimePicker2->Date = Dt;

  DateTimePicker1->Format = "MMM dd', ' yyyy";
  DateTimePicker2->Format = "MMM dd', ' yyyy";

  DateTimePicker2->Font->Name = Screen->Fonts->Strings[0];

  SaveStateFlag = false;

  Global::crhmMain = Main->Handle; // used by Windows messaging in next calls

  Global::nhru = Global::maxhru;
  Global::nobs = Global::maxobs;
  Global::nlay = Global::maxlay;

  Global::OBS_AS_IS = false;

  ObsFilesList = new TStringList;

  ProjectList = new TStringList;

  PrjObsHelp = new TStringList;
  PrjObsHelp->AddObject("", (TObject*) 1);

  Global::AllModulesList = new TStringList;
  Global::AllModulesList->CaseSensitive = true;

  Global::OurModulesList = new TStringList;
  Global::OurModulesList->Sorted = false;

  Global::MacroModulesList = new TStringList;
  Global::MacroModulesList->Sorted = false; // Global::ModelModulesList is not sorted
  Global::MacroModulesList->QuoteChar = '\'';

  Global::AllModelsList = new TStringList;
  Global::AllModelsList->Sorted = true;

  Global::ModelModulesList = new TStringList;
  Global::ModelModulesList->Sorted = false;

  Global::OurHelpList = new TStringList;   // DLL help files
  Global::PendingDLLModuleList = new TStringList; // current DLL modules

  Global::ReportList = NULL; //
  LoopList = NULL; //

  Global::DeclRootList = new TStringList;
  Global::DeclRootList->Sorted = true;

#ifdef CRHM_DLL
  DLL1->Enabled = true;
  OpenDLLs = new TStringList;
#else
  DLL1->Enabled = false;
#endif

#if !defined NO_MODULES
  MoveModulesToGlobal();
  ((ClassModule*) Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept(mrYesToAll);
  ++InitModCnt;
  UpDateModelMenu();
#endif

  CurChartPage = 1;
  Chart->Legend->LegendStyle = lsSeries;
  Chart->Legend->CheckBoxes = true;
  Chart->View3D = false;
  Chart->Axes->Right->Grid->Visible = false;

  StatusBar1->Panels->Items[0]->Text = "Idle";

  LabelFunct->Caption = FStrings[Funct];

  TCommanderControls Tcntrls[4] = {tcbEdit,tcbSeparator,tcbPrintPreview,tcbSeparator};
  TeeCommander1->CreateControls(Tcntrls, 3);

  Global::OldModuleName = new TStringList;
  Global::NewModuleName = new TStringList;
  Global::OldModuleName->CommaText = "long, CanopyClearingGap2";
  Global::NewModuleName->CommaText = "longVt, CanopyClearingGap";

// Global::OldModuleName->CommaText = "AnnandaleX, calcsunX, calcsun_QsiD, Slope_QsiX, ebsmX, long,   longVtX, route,    smbal, Trees";
// Global::NewModuleName->CommaText = "Annandale,  calcsun,  calcsun,      Slope_Qsi,  ebsm,  longVt, longVt,  Netroute, Soil,  Canopy";

#if !defined NO_MODULES
  for(long ii = 0; ii < Global::NewModuleName->Count; ++ii){
    long jj = Global::AllModulesList->IndexOf(Global::NewModuleName->Strings[ii]);
    assert(jj != -1);
    Global::OldModuleName->Objects[ii] = (TObject*) jj;
  }
#endif

  Global::CRHMStatus = 0;  // Status
  Global::CurrentModuleRun = -1;  // currently executing module
  Global::CRHMControlSaveCnt = 0; // NewModules input

  Global::HRU_OBS_DIRECT = new long*[5];
  for(long jj = 0; jj < 5; ++jj){
    Global::HRU_OBS_DIRECT[jj] = new long[500];

    for(long ii=0; ii < 500; ++ii)
      Global::HRU_OBS_DIRECT[jj][ii] = ii + 1;
  }

  Global::HRU_OBS = Global::HRU_OBS_DIRECT;

  Global::NaNcheck = false;
  Global::LOGVARLOAD = false;
  Global::TimeFormat = MS;

} // end of FormCreate
//---------------------------------------------------------------------------

void __fastcall TMain::UpDownHRUIndxClick(TObject *Sender, TUDBtnType Button)
{
  UpDownHRUIndx->Max = Global::maxhru;
  LabelHRUIndx->Caption = "HRU " + String(UpDownHRUIndx->Position);
  LabelHRUIndx->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMain::ExitClick(TObject *Sender)
{

  Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMain::OpenClick(TObject *Sender){

  OpenDialogObs->Filter = "Observation Files (*.obs)|*.obs";
  OpenDialogObs->Title = "Open Observation File";
  OpenDialogObs->DefaultExt = "obs";

  if(OpenDialogObs->Execute()) {
    OpenDialogObs->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogObs->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
    if(OpenDialogObs->InitialDir.IsEmpty())
      OpenDialogObs->InitialDir = GetCurrentDir();

    Box1Disply = CRHM::PRIVATE;
    Label4Click(Sender);

    OpenObsFile(Sender, OpenDialogObs->FileName);
  }

  Box1Disply = CRHM::OUTPUT;
  Label4Click(Sender);
}
//---------------------------------------------------------------------------

bool __fastcall TMain::OpenObsFile(TObject *Sender, String FileName){

  ClassData  * FileData;

    if(ObsFilesList->IndexOf(FileName.c_str()) != -1)
         return false;  // already open

    if(ObsFilesList->Count == 0) {
      Global::DTstart = 0; // used to flag first data file
      Global::DTend = 0; // used to flag first data file
    }

    StatusBar1->Panels->Items[0]->Text = "Reading Data File";
    StatusBar1->Repaint();

    SetCaptureControl(Main);

    FileData = new ClassData(FileName.c_str());

    StatusBar1->Panels->Items[0]->Text = "Idle";

    if(FileData->Success) {

      if(ObsFilesList->Count == 0) {
        if(FileData->Times != NULL) { // handle sparse data
          Application->MessageBox("Could be a Sequential file with an error at indicated position.", "Sparse file cannot be the first file.", MB_OK);
          delete FileData;
          FileData = NULL;
          return false;
        }

        Global::Interval = FileData->Interval;
        Global::Freq = FileData->Freq;

        Global::IndxMin = FileData->IndxMin;
        Global::IndxMax = FileData->IndxMax;

        DateTimePicker1->MinDate = 0;
        DateTimePicker1->MaxDate = 80000;

        DateTimePicker2->MinDate = 0;
        DateTimePicker2->MaxDate = 80000;

        DateTimePicker1->Date = FileData->Dt1;
        DateTimePicker2->Date = FileData->Dt2;

        DateTimePicker1->MinDate = floor(FileData->Dt1);
        DateTimePicker1->MaxDate = floor(FileData->Dt2);

        DateTimePicker2->MinDate = floor(FileData->Dt1);
        DateTimePicker2->MaxDate = floor(FileData->Dt2);

        DateTimePicker1->Enabled = true;
        DateTimePicker2->Enabled = true;
      }
      else if(FileData->Freq > Global::Freq) { // handle higher interval after first
        Application->MessageBox("later observation file has finer time step than first", "File time step Error", MB_OK);
        delete FileData;
        FileData = NULL;
        return false;
      }

      FileData->ModN = Global::Freq / FileData->Freq;

      MapVar::iterator itVar;
      ClassVar * thisVar;

// always starts with this display// remove entries that are in observation ListBox1
      for(int ii = 0; ii < ListBox1->Items->Count; ii++) {
        thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];
        if(thisVar && thisVar->varType >= CRHM::Read) {
          ListBox1->Items->Delete(ii);
          ii = 0;
        }
      }

// remove entries that are in observation ListBox3
      for(int ii = 0; ii < ListBox3->Items->Count; ii++) {
        thisVar =  (ClassVar *) ListBox3->Items->Objects[ii];
        if(thisVar && thisVar->varType >= CRHM::Read) {
          ListBox3->Items->Delete(ii);
          ii = 0;
        }
      }

      ListBox2->Clear();

      for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
        thisVar = (*itVar).second;
        if(thisVar && thisVar->varType >= CRHM::Read)
          if(IndexOf(ListBox2, thisVar->name.c_str()) == -1)
            ListBox2->Items->AddObject(thisVar->name.c_str(), (TObject*) thisVar);
      }

      TMenuItem *ObsItem, *NewItem;
      ObsItem = MainMenu1->Items->Items[1];

      NewItem = new TMenuItem(ObsItem);
      String S = "&" + IntToStr(ObsFilesList->Count + 1) +
                           " " + OpenDialogObs->FileName;
      NewItem->Caption = S;
      ObsFilesList->AddObject(OpenDialogObs->FileName.c_str() , (TObject *) FileData);

      String as = ExtractFileName(OpenDialogObs->FileName);
             as = ChangeFileExt(as,".CHM");

      if(FileExistsSp(as)) {
        PrjObsHelp->AddObject(as.SubString(1, as.Length()-4) + ".obs", (TObject*) ObsItem->Count);
        UpDateHelpMenu();
      }

      NewItem->OnClick = ObsFileClose;
      ObsItem->Insert(ObsItem->Count, NewItem);
      ReleaseCapture();
      return true;
    }
    else {
      if(ObsFilesList->Count == 0) {
        Global::DTstart = 0; // used to flag first data file
        Global::DTend = 0; // used to flag first data file
      }

      delete FileData;
      FileData = NULL;
      ReleaseCapture();
      return false;
    }
} // end of OpenObsFile
//---------------------------------------------------------------------------

void __fastcall TMain::ObsCloseClick(TObject *Sender){

  TMenuItem *ObsItem;
  ObsItem = MainMenu1->Items->Items[1];

  if(ObsItem->Count <= 4) return; // no files open

  if(ProjectOpen)

    if(Application->MessageBox("First observation File affects Obs timebase",
                  "Close All Observation Files", IDOK) != IDOK) return;

  ListBox2->Clear();

  ClearListBox4(Sender);

  while(ObsItem->Count > 4)
      ObsItem->Delete(ObsItem->Count-1);

  for(int ii = 0; ii < ObsFilesList->Count; ii++) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
    delete FileData;   // delete ClassData instance
    FileData = NULL;
  }
  ObsFilesList->Clear();  // clear list

  ResetPickers();

  Global::nobs = 1;  // reset to 1
  Global::maxobs = 1;  // reset to 1

  while (PrjObsHelp->Count > 1)
    PrjObsHelp->Delete(PrjObsHelp->Count-1);

  UpDateModelMenu();

}
//---------------------------------------------------------------------------

void __fastcall TMain::BldModelClick(TObject *Sender)
{
  TMenuItem *ObsItem;

  TMenuItem * thisMenu = (TMenuItem *) Sender;

  FreeChart1(Sender);          // remove series and clear ListBox4

  ClearModules(Sender, false);

  int Index = (int) Global::AllModelsList->Objects[thisMenu->MenuIndex - 6]; // Global::AllModelsList is sorted

  Global::OurModulesList->CommaText = Global::ModelModulesList->Strings[Index]; // Global::ModelModulesList is not sorted
  DescripPrj = Global::AllModelsList->Strings[thisMenu->MenuIndex - 6].c_str();

  Chart->SubTitle->Text->Clear(); // put in plot for information
  Chart->SubTitle->Text->Add(DescripPrj.c_str());

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
    long Variation = 0;
    int P;
    if(P = Global::OurModulesList->Strings[ii].Pos("#"), P > 0){ // remove any suffix
      Variation = pow(2, Global::OurModulesList->Strings[ii][P+1] - char('1'));
      Global::OurModulesList->Strings[ii] = Global::OurModulesList->Strings[ii].Delete(Global::OurModulesList->Strings[ii].Length()-1, 2);
    }
    int jj = Global::AllModulesList->IndexOf(Global::OurModulesList->Strings[ii]);
    if(jj < 0) {
      CRHMException Except((Global::OurModulesList->Strings[ii] + " Module not defined in CRHM model").c_str(), ERR);
      Global::OurModulesList->Clear();
      Application->MessageBox(Except.Message.c_str(), "Missing module", MB_OK);
      LogError(Except);
      return;
    }

    ((ClassModule*) Global::AllModulesList->Objects[jj])->variation = Variation;

    Global::OurModulesList->Objects[ii] = Global::AllModulesList->Objects[jj];
  }

  ProjectOpen = true;

  InitModules(Sender);

  SqueezeParams(Sender);  // converts all parameters to shared parameters

  dirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::RunClick(TObject *Sender){

  ClassVar *thisVar;
  float **mmsData;
  long **mmsDataL;
  bool GoodRun = true;
  MapVar::iterator itVar;
  PlotControl->IntervalControl = 0;
  PlotControl->IntervalLength = 3; // make default
  Global::ModuleBitSet.reset();

  Global::HRU_OBS = Global::HRU_OBS_DIRECT; // always correct? Not set by macro project?
  Global::OBS_AS_IS = false;
  Global::WQ_prj = false;

  UpDownHRUIndxClick(Sender, btNext); // updates if macro group nhru > Global::nhru

  if(LogForm->DeclErrors > 0)
    if(Application->MessageBox("Module errors", "Model Declaration Error", MB_OK)) return;
  LogForm->ClearRunLogs();

  if(ObsFilesList->Count == 0 && ((ClassModule*) Global::OurModulesList->Objects[0])->UsingObservations()){
    if(Application->MessageBox("CRHM requires an observation file(s) with at least; t, rh, ea, u, p (or ppt).", "No observation file(s) specified", MB_OK)) return;
    return;  // do not run
  }

  if(Global::IndxMin != 0){
    if(Application->MessageBox("", "First observation day - not an entire day", MB_OK)) return;
    return;  // do not run
  }

  if(cdSeries) {
    for (int ii = 0; ii < SeriesCnt; ii ++) {

      thisVar =  (ClassVar *) cdSeries[ii]->Tag;
      thisVar->TchrtOpt = cdSeries[ii]->VertAxis == aRightAxis;
      cdSeries[ii]->ParentChart = NULL;
      cdSeries[ii]->Clear();
    }
    delete [] cdSeries;
    cdSeries = NULL;
    SeriesCnt = 0;
  }

  if(ListBox3->Items->Count == 0){
    if(Application->MessageBox("", "No model output selected", MB_OK)) return;
    return;  // nothing selected
  }

  String Message = "Project file: " + OpenDialogPrj->FileName;
  LogMessage(Message.c_str());
  LogMessage(" ");

  for(int ii = 0; ii < ObsFilesList->Count; ii++){
    Message = "Observation file: " + ObsFilesList->Strings[ii];
    LogMessage(Message.c_str());
  }
  LogMessage(" ");

  TDateTime Dt = TDateTime::CurrentDateTime();
  Message = "Time of model run: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt)
    + ". Program  " + AboutBox->Label2->Caption;
  LogMessage(Message.c_str());
  LogMessage(" ");

  String S = String("Module List \"") ;
  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    S += Global::OurModulesList->Strings[ii];
    if(thisModule->variation != 0){
      String AA("#0");
      AA[2] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }
    if(ii == Global::OurModulesList->Count-1)
      S += ".\"";
    else
      S += ", ";
  }

  LogDebug(S.c_str());
  LogMessage(" ");

  if(!Global::MapAKA.empty()) {
    Mapstr2::iterator it;
    LogMessage("Linkage modifications (AKAs)");
    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {

      Message = String((*it).first.c_str()) + " " + String((*it).second.c_str());
      LogMessage(Message.c_str());
    }
    LogMessage(" ");
  }

  Global::DeclRootList->Clear(); // used by AKA to stop looping

// clears storage for observation read and function lists
  ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

  double DTstartR = INT(DateTimePicker1->Date);
  double DTendR   = INT(DateTimePicker2->Date);

  ClassPar *thisPar;

  if(CommandLine){                          // ********
    double P = 0;
    thisPar = ParFind("basin RUN_START");
    if(thisPar){
      if(thisPar->ivalues[0] > 0)
        P = thisPar->ivalues[0];
    }
    else{
      MapPar::iterator itPar;

      for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
        thisPar = (*itPar).second;
        if(thisPar->param == "RUN_START" && thisPar->ivalues[0] > 0) {
          P = thisPar->ivalues[0];
          break;
        }
      }
    }
    if(P > 0){
      if(P < Global::DTstart || P > Global::DTend)
        P = Global::DTstart;

      DTstartR = P;
      DateTimePicker1->Date = P;
    }

    P = 0;
    thisPar = ParFind("basin RUN_END");
    if(thisPar){
      if(thisPar->ivalues[0] > 0)
        P = thisPar->ivalues[0];
    }
    else{
      MapPar::iterator itPar;

      for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
        thisPar = (*itPar).second;
        if(thisPar->param == "RUN_END" && thisPar->ivalues[0] > 0) {
          P = thisPar->ivalues[0];
          break;
        }
      }
    }

    if(P > 0){
      if(P < Global::DTstart || P > Global::DTend)
        P = Global::DTend;

      DTendR = P;
      DateTimePicker2->Date = P;
    }
  }

  Global::DTmin  = INT((DTstartR-Global::DTstart)* Global::Freq);
  Global::DTmax  = INT((DTendR-Global::DTstart)* Global::Freq);
  Global::DTindx = Global::DTmin;
  Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);

  Global::MapVarsGet.clear();
  Global::MapVarsPut.clear();
  Global::MapObsGet.clear();

  try{
    for(Global::CurrentModuleRun = 0; Global::CurrentModuleRun < Global::OurModulesList->Count; Global::CurrentModuleRun++)
      ((ClassModule*) (Global::OurModulesList->Objects[Global::CurrentModuleRun]))->initbase();
  }
  catch (CRHMException Except){ // serious error - program had to stop immediately

    Application->MessageBox(Except.Message.c_str(),
      (String("Initialisation of module - ") + ((ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun])->Name.c_str()).c_str(),
      MB_OK);
    GoodRun = false;
  }

  catch (Sysutils::Exception &E){
    ShowMessage(E.Message + " in Initialisation of " + ((ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun])->Name.c_str());
    GoodRun = false;
  }

  if(LogForm->Errors > 0 && !GoodRun){ // initialisation
    GoodRun = false;
  }
  else if(DTstartR >= DTendR) {
    Application->MessageBox("Start Time >= EndTime", "Time Error", MB_OK);
    GoodRun = false;
  }

  if(CommandLine){
    thisPar = ParFind("Shared INIT_STATE");
    if(thisPar && thisPar->Strings->Count && !thisPar->Strings->Strings[0].IsEmpty()){
      OpenDialogState->FileName = thisPar->Strings->Strings[0].c_str();
      ReadStateFile(Sender, GoodRun);
    }
    else{
      MapPar::iterator itPar;

      for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
        thisPar = (*itPar).second;
        if(thisPar->param == "INIT_STATE" && thisPar->Strings->Count && !thisPar->Strings->Strings[0].IsEmpty()) {
          OpenDialogState->FileName = thisPar->Strings->Strings[0].c_str();
          ReadStateFile(Sender, GoodRun);
          break;
        }
      }
    }
  }

  TMenuItem *StateItem = MainMenu1->Items->Items[5];

  if(StateItem->Count > 5){ // State files open
    for(int ii = 5; ii < StateItem->Count; ++ii){
      LogMessage(" ");
      OpenDialogState->FileName = StateItem->Items[ii]->Caption;
      ReadStateFile(Sender, GoodRun);
    }
  }

  if(!GoodRun) { //cleanup memory before returning

// deletes storage for observation read list
    ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

// deletes module allocated storage
    for(int ii = 0; ii < Global::CurrentModuleRun; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->finish(false);

    Global::BuildFlag = CRHM::DECL;
    StatusBar1->Panels->Items[0]->Text = "Faulty Run";
    Chart->Repaint();
    return;
  }

  SeriesCnt = ListBox3->Items->Count;

  cdSeries = new TLineSeries*[SeriesCnt];

  mmsData = new float*[SeriesCnt];
  mmsDataL = new long*[SeriesCnt];

  for (int ii = 0; ii < ListBox3->Items->Count; ii ++) {

    thisVar = (ClassVar *) (ListBox3->Items->Objects[ii]);

    if(thisVar->PointPlot)
      cdSeries[ii] = (TLineSeries *) new TPointSeries(this);
    else
      cdSeries[ii] = new TLineSeries(this);

    CurrentColor = colours[ii % ncolours];
    cdSeries[ii]->Color = CurrentColor;

    cdSeries[ii]->Tag = (int) thisVar;
    cdSeries[ii]->VertAxis = (TVertAxis) thisVar->TchrtOpt;

    if(ii == 0) Chart->Axes->Items[2]->Title->Caption = thisVar->units.c_str();

    cdSeries[ii]->XValues->DateTime = TRUE;
    cdSeries[ii]->ParentChart = Chart;

    String S = ListBox3->Items->Strings[ii];
    cdSeries[ii]->Title = S;
    if(thisVar->TchrtOpt)
      cdSeries[ii]->VertAxis = aRightAxis;

    long lay, dim;

    ExtractHruLay(S, dim, lay);

    if(thisVar->varType == CRHM::Float) {
      mmsDataL[ii] = NULL;
      if(thisVar->lay == 0){
        mmsData[ii]  = thisVar->values+(dim-1);
      }
      else {
        mmsData[ii]  = (thisVar->layvalues[lay-1])+(dim-1);
      }
    }
    else if(thisVar->varType == CRHM::Int) {
      mmsData[ii]  = NULL;
      if(thisVar->lay == 0){
        mmsDataL[ii] = thisVar->ivalues+(dim-1);
      }
      else {
        mmsDataL[ii] = (thisVar->ilayvalues[lay-1])+(dim-1);
      }
    }
  }

  Global::BuildFlag = CRHM::RUN;

  Chart->AutoRepaint = false;
  StatusBar1->Panels->Items[0]->Text = "Spacing";
  StatusBar1->Repaint();

  bool First = true;
  TCursor OriginalCursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;
  SetCaptureControl(Main);

  ParameterBackUp(Sender); // after modules initialized
  RefreshTime = 0;

  LogMessage(" ");
  S = String("timestep ") + Global::Interval*24 + " hr.";
  LogDebug(S.c_str());

  LogDebugT("\"start of run\".");
  LogMessage(" ");

  Global::CRHMControlSaveCnt = 0; // set by module
  Global::CRHMStatus = 0; // module status; module control = 1 , main control = 2 and Finished = 4. Both inhibit output.
  Global::LoopCntDown = -1;
  StatePar = NULL;
  Global::ModuleBitSet.reset();

  ClassModule* Obs_preset; // used to call preset for simple projects

  int jj = Global::OurModulesList->IndexOf("obs");

  if(jj == -1)
    Obs_preset = NULL;
  else
    Obs_preset = (ClassModule*) Global::OurModulesList->Objects[jj];

  if(Global::LoopCnt && ((double) Global::RapidAdvanceTo == 0.0 || (double) Global::RapidAdvanceTo <= DTstartR))
    Global::RapidAdvanceTo = DTstartR + 1;

  try{
    for (Global::DTindx = Global::DTmin; Global::DTindx < Global::DTmax; Global::DTindx++) {

      if(Global::Freq == 1)
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx);
      else
          Global::DTnow = Global::DTstart + Global::Interval*(Global::DTindx+1);

      if((double) Global::RapidAdvanceTo > 0.0){
        if(Global::DTnow < Global::RapidAdvanceTo)
          Global::CRHMStatus |= 2; // set module control and inhibit display

        else if(Global::DTnow == Global::RapidAdvanceTo){ // reached RapidAdvanceTo
            Global::CRHMStatus &=125; // clear status == 2 (main control) and resume display
            Global::RapidAdvanceTo = 0;
            LogMessage("Terminate fast loop aheadMain", DD);
        }
      }

      if(Global::LoopCnt && (double) Global::RapidAdvanceTo == 0.0){
        if(Global::LoopCntDown == -1){ // first time
          Global::LoopCntDown = Global::LoopCnt;
          StatePar = ParFind("basin StateVars_to_Update");
          ControlSaveState(Sender, true, StatePar, Global::RunUpBitSet); // save this position
          Global::CRHMStatus |= 2; // set module control and inhibit display
          LogMessage("Initialise LoopTo Main", DD);
        }
        else if(Global::DTnow == Global::LoopTo){ // reached LoopTo position
          ControlReadState(Sender, true, StatePar); // return to earlier position
          --Global::LoopCntDown; // after above ReadState
          LogMessage("Reached loop Main", DD);
          if(Global::LoopCntDown <= 0){
            ResetLoopList(Sender);
            Global::CRHMStatus &=125; // remove status == 2 (inhibit display)
            Global::CRHMStatus |= 4; // flag done
            Global::LoopCnt = 0;
            LogMessage("Terminate LoopTo Main", DD);
          }
        }
      }

      if(RefreshTime <= 0){

        String S = String("Calculating  ") +
                   Global::DTnow.FormatString("yyyy'/'m'/'d");

        if(PrjAutoExit->Checked && (All1->Checked || Last1->Checked || SummaryScreen1->Checked)){
          RefreshTime = Global::DTmax - Global::DTmin - 1;
          S += " with No graphical refresh!";
        }
        else{
          switch(PlotControl->IntervalLength) {
            case 2: // daily
              RefreshTime = Global::Freq;
              daily1->Checked = true;
              break;
            case 3: // bi-weekly
              RefreshTime = (float) Global::Freq*3.5;
              biweekly1->Checked = true;
              break;
            case 4: // weekly
              RefreshTime = Global::Freq*7;
              weekly1->Checked = true;
              S += " with weekly refresh!";
              break;
            case 5:  // monthly
              RefreshTime = Global::Freq*30;
              monthly1->Checked = true;
              S += " with monthly refresh!";
              break;
            case 6:  // yearly
              RefreshTime = Global::Freq*366;
              yearly1->Checked = true;
              S += " with yearly refresh!";
              break;
            case 7: // end of run
              RefreshTime = Global::DTmax - Global::DTindx;
              atend1->Checked = true;
              S += " with No graphical refresh!";
              biweekly1Click(Sender); // make default
              break;
          } // switch
        }
        StatusBar1->Panels->Items[0]->Text = S.c_str();
        StatusBar1->Repaint();
        Chart->AutoRepaint = true;
        Chart->Repaint();
        Application->ProcessMessages();
      }

      if(PlotControl->IntervalControl)
        break;
// determine which obervation files have good data
      DoObsStatus(Sender, First);

// reads observations for current interval

      long Nan_error = 0;
      bool Reset = true;

      if(Obs_preset) // for simple prj, set up elev etc.
          Obs_preset->pre_run();

      for(Global::CurrentModuleRun = 0; Global::CurrentModuleRun < Global::OurModulesList->Count; Global::CurrentModuleRun++){
        long Last = Global::CRHMControlSaveCnt;

        ClassModule *p = (ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun];

        if(p->GroupCnt && ((ClassMacro*) p)->ObsModule) // only execute if group has an obs module
          ((ClassMacro*) p)->ObsModule->pre_run();

        p->ReadObs(Reset);
        Reset = false;

// Simple project for module obs. For group always when !CRHMStatus otherwise only selected groups

        CheckBlankModule(Sender);

        if(!p->isGroup || !Global::CRHMStatus || (Global::CRHMStatus & 1 && Global::ModuleBitSet[Global::CurrentModuleRun])){

          p->run();
        }

        CheckBlankModule(Sender);

// module flag loop

        if(Last != Global::CRHMControlSaveCnt) // means last module/group
          Global::ModuleBitSet.set(Global::CurrentModuleRun);
      } // end for

      if(Global::NaNcheck){
        for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
          thisVar = (*itVar).second;

          if(thisVar->varType == CRHM::Float){
            for(long cc = 0; cc < thisVar->dim; ++cc){
              if(IsNan(thisVar->values[cc])){
                thisVar->values[cc] = -999;
                if(Nan_error <= 0){
                  Nan_error = 1;
                  String D = "***** NAN (not a number error) found at yy mm dd hh mm: " + Global::DTnow.FormatString("yy mm dd hh nn ") + " ,DTindx = " + String(Global::DTindx);
                  LogMessage(D.c_str());
                }

                String SS = String(String(thisVar->module.c_str()) + " " + String(thisVar->name.c_str()) + "(" + String(cc+1) + ")");
                LogMessage(SS.c_str());
              }
            } // for
          } // match this module
        } // loop through variables
      } // NaN checking ON

      if(Nan_error > 0){
        LogMessage("***** NAN (not a number error) end");
        LogMessage("");
        Nan_error = -1;
      }

// module loop control
      bool OneOutput = false;
      bool DoOutput = true;
      if(Global::CRHMControlSaveCnt && !(Global::CRHMStatus & 1)){ // Set module mode. Save current position at end of day.
        VariableBackUp(Sender); // after modules initialized
        Global::CRHMStatus |= 1; // set module control bit and inhibit display.
        LogMessage("Start save Main", DD);
        OneOutput = true;
      }

// module loop control reset
      if((Global::CRHMStatus & 1) && (!Global::CRHMControlSaveCnt || Global::DTindx >= Global::DTmax-1)){ // handles daily + last day of run
        Global::CRHMStatus &= 126; // reset module mode.
        VariableRestore(Sender);
        Global::CRHMControlSaveCnt = 0; // required for Global::DTindx >= Global::DTmax-1 condition
        LogMessage("End save Main", DD);
        LogDebug(" ");
        DoOutput = false;
      }

      if(!(Global::CRHMStatus & 7) && !(Global::CRHMControlSaveCnt) && DoOutput || OneOutput){ // display if not module or main controlled. why?  && DoOutput

        double xx;
        for (int ii = 0; ii < SeriesCnt; ii++) {
          if(mmsData[ii] != NULL) {
            xx = *mmsData[ii];
            if(xx < xLimit)
              cdSeries[ii]->AddXY(Global::DTnow, xx, "", CurrentColor);
          }
          else {
            xx = (*mmsDataL[ii]);
            if(xx < lLimit)
              cdSeries[ii]->AddXY(Global::DTnow, xx, "", CurrentColor);
          }
        }
      }
      else
        Global::CRHMStatus &=123; // remove status == 2 (inhibit display)


      RefreshTime--;

      if(Nan_error != 0){
        String D = "yy mm dd hh mm: " + Global::DTnow.FormatString("yy mm dd hh nn ") + ", DTindx = " + String(Global::DTindx);
        Application->MessageBox(D.c_str(), "NaN error", MB_OK);
        GoodRun = false;

        break;
      }
    } // end for

    Global::BuildFlag = CRHM::DECL;
  }

  catch (Sysutils::Exception &E){
    String S = E.Message + " at " +
      Global::DTnow.FormatString("yyyy'/'m'/'d hh':'nn") + " (" + getstep() + ") in '" + Global::OurModulesList->Strings[Global::CurrentModuleRun] + "'" + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 6) + ")";
    ShowMessage(S.c_str());
    LogError(S , ERR);
    GoodRun = false;
  }

  catch (CRHMException Except){
    String S = Except.Message.c_str() + String("at ") +
      Global::DTnow.FormatString("yyyy'/'m'/'d hh':'nn") + " in '" + Global::OurModulesList->Strings[Global::CurrentModuleRun] + "'";
    ShowMessage(S.c_str());
    LogError(S + " (" + FloatToStrF(Global::DTnow, ffGeneral	, 10, 0) + ")", ERR);
    GoodRun = false;
  }

  LogMessage(" ");
  Dt = TDateTime::CurrentDateTime();
  Message = "End of model run: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt)
    + ". Program  " + AboutBox->Label2->Caption;
  LogMessage(Message.c_str());
  LogDebug(" ");

  Screen->Cursor = OriginalCursor;
  ReleaseCapture();

  Global::CRHMStatus = 0;  // Status

  delete[] mmsData;
  delete[] mmsDataL;

  ParameterRestore(Sender);

// deletes storage for observation read list
  ((ClassModule*) Global::OurModulesList->Objects[0])->InitReadObs();

// deletes module allocated storage
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->finish(true);

  if(GoodRun) {
    if(!PlotControl->IntervalControl){
      StatusBar1->Panels->Items[0]->Text = "Updating VarObsFunct";
      StatusBar1->Repaint();
      VarObsFunct_Update(Sender);
      if(SaveStateFlag) SaveState(Sender);
      if(Last1->Checked) Last1Rprt(Sender);
      if(All1->Checked) All1Rprt(Sender);
      if(DebugScreen1->Checked) DebugScreen1Rprt(Sender);
      if(SummaryScreen1->Checked) SummaryScreen1Rprt(Sender);
    }
    else if(LoopList){ // clean up if looping
      delete LoopList;
      LoopList = NULL;
    }

    StatusBar1->Panels->Items[0]->Text = "Idle";
    LogDebugT("\"end of run\".");
  }
  else
    StatusBar1->Panels->Items[0]->Text = "Faulty Run";

  Chart->AutoRepaint = true;
  Chart->Repaint();

} // end of RunClick
//---------------------------------------------------------------------------

void __fastcall TMain::ExportClick(TObject *Sender){

  FileOutput->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain::AboutClick(TObject *Sender){

  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox3Click(TObject *Sender)
{
  int ii = ListBox3->ItemIndex;
  if(SeriesCnt <= 0)
    ListBox3->Items->Delete(ii);
  else
    for(int jj = 0; jj < SeriesCnt; jj++)
      if(cdSeries[jj]->Title == ListBox3->Items->Strings[ii]) {

        ((ClassVar*) cdSeries[jj]->Tag)->TchrtOpt = cdSeries[jj]->VertAxis == aRightAxis;

        cdSeries[jj]->ParentChart = NULL;
        cdSeries[jj]->Clear();

        for(int kk = jj+1; kk < SeriesCnt; kk++)
          cdSeries[kk-1] = cdSeries[kk];

        ListBox3->Items->Delete(ii);
        SeriesCnt--;
        break;
      }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ConstructClick(TObject *Sender)
{
  LogForm->ClearRunLogs();

  FreeChart1(Sender);          // remove series and clear ListBox4

//  ObsCloseClick(Sender);

  BldForm->ShowModal();

  if(BldForm->Execute) {
    InitModules(Sender);
    BldForm->ReadBuildParameters(Sender); // restore original parameters

    dirty = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::InitModules(TObject *Sender) {

  ClassVar *thisVar;

  Global::BuildFlag = CRHM::DECL;

  Box1Disply = CRHM::OUTPUT; // Synchronise ListBox1 disply

// executes the DECL portion of the declvar/declparam etc. routines
  for(Global::CurrentModuleRun = 0; Global::CurrentModuleRun < Global::OurModulesList->Count; Global::CurrentModuleRun++){
    ((ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun])->nhru = Global::nhru;
    ((ClassModule*) Global::OurModulesList->Objects[Global::CurrentModuleRun])->decl();
  }

  if(LogForm->DeclErrors > 0)
    Application->MessageBox("Module errors", "Model Declaration Error", MB_OK);
  Label4Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox4Click(TObject *Sender)
{
  long Showing = ListBox4->ItemIndex;
  if(Showing == -1) return; //nothing selected

  TLineSeries *cdSeries = (TLineSeries *) ListBox4->Items->Objects[ListBox4->ItemIndex];

  ClassVar* thisVar =  (ClassVar *) cdSeries->Tag;
  thisVar->TchrtOpt = cdSeries->VertAxis == aRightAxis;

  if(thisVar->FunKind > CRHM::FOBS)
    delete thisVar;

  cdSeries->ParentChart = NULL;
  cdSeries->Clear();

  ListBox4->Items->Delete(ListBox4->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddObsPlot(TObject *Sender, ClassVar *thisVar,
                             TLineSeries *cdSeries, String S, CRHM::TFun Funct){

  ClassVar *newVar;
  Global::HRU_OBS = Global::HRU_OBS_DIRECT; // always correct?

  Chart->Axes->Items[2]->Title->Caption = thisVar->units.c_str();

  float **Data = thisVar->FileData->Data;
  double xx;
  double DTstartR = INT(DateTimePicker1->Date);
  double DTendR   = INT(DateTimePicker2->Date);

  if(DTstartR >= DTendR) return;

  TDateTime Save_DTnow = Global::DTnow; // Save

  double MyInterval = thisVar->FileData->Interval;
  long DTmin  = INT((DTstartR-Global::DTstart)* thisVar->FileData->Freq)*Global::Freq/thisVar->FileData->Freq;
  long DTmax  = INT((DTendR-Global::DTstart)* thisVar->FileData->Freq)*Global::Freq/thisVar->FileData->Freq;

  long jj1 = S.LastDelimiter("(");
  long jj2 = S.LastDelimiter(")");

  long Indx;
  string::size_type pp;
  pp = thisVar->name.rfind('(');
  bool AlreadyIndex = (pp != string::npos); // handles exported variables in Obs files

  if(ListHruNames && thisVar->varType < CRHM::Read) // using names
    Indx = ListHruNames->IndexOf(S.SubString(jj1+1, jj2-jj1-1)) - 1;
  else{ if(thisVar->root != "" || AlreadyIndex)
      Indx = 0; // (non observations always 0
    else
      Indx = (S.SubString(jj1+1, jj2-jj1-1)).ToInt()-1;
  }

  long IndxMin = thisVar->FileData->IndxMin;
  long IndxMax = thisVar->FileData->IndxMax;

  if(thisVar->FileData->Times != NULL) { // display sparse data
    if(Global::Freq == 1)
      --DTendR;

    float Sum = 0.0;

    for(long ii = 0; ii < thisVar->FileData->Lines; ++ii) {
      if(thisVar->FileData->Times[ii] < DTstartR) continue;
      if(thisVar->FileData->Times[ii] > DTendR) continue;

      xx = Data[thisVar->offset+Indx][ii];

      if(Funct == CRHM::TOT){
        Sum += xx;
        xx = Sum;
      }

      cdSeries->AddXY(thisVar->FileData->Times[ii], xx, "", CurrentColor);
    }
  }

  else if(Funct <= CRHM::MJ_W){ // display simple observations

    if(MyInterval == 1) cdSeries->Stairs = true;

    for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx++) {
      Global::DTnow = Global::DTstart + Global::Interval*Global::DTindx + Global::Interval;

      if(MyInterval >= 1) --Global::DTnow;

      if(Global::DTindx*thisVar->FileData->Freq/Global::Freq >= IndxMin
           && Global::DTindx*thisVar->FileData->Freq/Global::Freq <= IndxMax){

        xx = Data[thisVar->offset+Indx][(Global::DTindx*thisVar->FileData->Freq/Global::Freq - IndxMin)];
        if(Funct == CRHM::FOBS)
          ; // do nothing
        else if(Funct == CRHM::VP_SAT){
          if (xx > 0.0)
             xx = 0.611 * exp(17.27*xx / (xx + 237.3));
          else
             xx = 0.611 * exp(21.88*xx / (xx + 265.5));
        }
        else if(Funct == CRHM::W_MJ)
          xx *= thisVar->FileData->Interval*86400/1.0E6;
        else if(Funct == CRHM::MJ_W)
          xx *= 1.0E6/86400/thisVar->FileData->Interval;

        cdSeries->AddXY(Global::DTnow, xx, "", CurrentColor);
      }
    }
  }
  else { // display observations functions
    cdSeries->Stairs = true;
// N.B. object FileData copied. If Obs function - Obs deletes else if VarObsFunct ListBox4 deletes.
    newVar = new ClassVar(*thisVar);

    newVar->name = S.c_str();

    newVar->FileData->DataFileName = "Copy";


    string::size_type pp = thisVar->units.find_last_of(")");

    if(thisVar->FileData->Freq > 1 && (thisVar->units[pp-1] == 'd'))   //  || TBase == 0
      thisVar->Daily = TRUE;
    else
      thisVar->Daily = FALSE;

    if(newVar->root == ""){ // Observation
      if(thisVar->FileData->Freq == 1)
         newVar->LoopFunct = &ClassVar::LoopFirst;
      else if(thisVar->Daily)
         newVar->LoopFunct = &ClassVar::LoopFirst;
      else
         newVar->LoopFunct = &ClassVar::LoopRange;
    }
    else { // Variable
      if(thisVar->Daily)
         newVar->LoopFunct = &ClassVar::LoopLast;
      else
         newVar->LoopFunct = &ClassVar::LoopRange;
    }

    newVar->FunctVar = thisVar;

    switch (Funct) {
      case CRHM::AVG:
          newVar->UserFunct_ = &ClassVar::Tot_;
          newVar->FunKind = CRHM::AVG;
          break;
      case CRHM::MIN:
          newVar->UserFunct_ = &ClassVar::Min_;
          newVar->FunKind = CRHM::MIN;
          break;
      case CRHM::MAX:
          newVar->UserFunct_ = &ClassVar::Max_;
          newVar->FunKind = CRHM::MAX;
          break;
      case CRHM::TOT:
          newVar->UserFunct_ = &ClassVar::Tot_;
          newVar->FunKind = CRHM::TOT;
          break;
      case CRHM::POS:
          newVar->UserFunct_ = &ClassVar::Pos_;
          newVar->FunKind = CRHM::POS;
          break;
      case CRHM::FIRST:
          newVar->UserFunct_ = &ClassVar::First_;
          newVar->FunKind = CRHM::FIRST;
          newVar->LoopFunct = &ClassVar::LoopFirst;
          break;
      case CRHM::LAST:
          newVar->UserFunct_ = &ClassVar::Last_;
          newVar->FunKind = CRHM::LAST;
          newVar->LoopFunct = &ClassVar::LoopLast;
          break;
      case CRHM::CNT:
          newVar->UserFunct_ = &ClassVar::Count_;
          newVar->FunKind = CRHM::CNT;
          break;
      case CRHM::CNT0:
          newVar->UserFunct_ = &ClassVar::Count0_;
          newVar->FunKind = CRHM::CNT0;
          break;
      case CRHM::DLTA:
          newVar->UserFunct_ = &ClassVar::First_;
          newVar->LoopFunct = &ClassVar::LoopFirst;
          newVar->FunKind = CRHM::DLTA;
          break;
    } // switch

    bool First = false;
    long Next = -1;
    long Days = 0;
    long LastDays = 0;
    long Lastkk = 0;
    long CurrentIndx = -1;
    long LastIndex = -1;
    long itime[6];
    long Greatest;
    long DTminX = DTmin;
    if(IndxMin > 0)
      DTminX = IndxMin;
    float Delta0 = 0.0;
    float First0;
    float Temp;
    dattim("now", itime);

    for (Global::DTindx = DTmin; Global::DTindx < DTmax; Global::DTindx+=Global::Freq) {
      Global::DTnow = Global::DTstart + Global::Interval*Global::DTindx + Global::Interval;

      if(Global::DTindx*Global::Freq/thisVar->FileData->Freq >= IndxMin)
        if(Global::DTindx*thisVar->FileData->Freq/Global::Freq > IndxMax)
          break;
        else {
        if(Global::Interval >= 1) --Global::DTnow;

        dattim("now", itime);

        switch(TBase){

          case 0: // daily
            if(Next == -1 || Next != itime[2]){
              Next = itime[2];
              First = TRUE;
            }
            break;
          case 1: // water annual
            if(Next == -1 || itime[0] == Next && itime[1] == water_year_month){
              if(Next == -1 && itime[1] < water_year_month)
                Next = itime[0];
              else
                Next = itime[0] + 1;
              First = TRUE;
            }
            break;
          case 2: // annual
            if(Next == -1 || itime[0] == Next && itime[1] == 1){
              Next = itime[0] + 1;
              First = TRUE;
            }
            break;
          case 3: // monthly
            if(Next == -1 || Next == itime[1]){
              Next = (itime[1])%12 + 1;
              First = TRUE;
            }
            break;
          case 4: // All - do nothing
            if(Next == -1){
              Next = 0;
              First = TRUE; // do nothing
            }
        } // switch

        CurrentIndx = (Global::DTindx - DTminX)/thisVar->FileData->Freq-1;

        if(First){
          if(Global::DTindx > DTmin && Global::DTindx > IndxMin){ // Handle RUN starting after beginning of primary obs file and secondary obs file later
            switch(Funct){
                case CRHM::DLTA:
                  Temp = cdSeries->YValue[(Global::DTindx - DTmin)/thisVar->FileData->Freq-1];
                  cdSeries->YValue[CurrentIndx] -= Delta0;
                  Delta0 = Temp; // fall through
                case CRHM::AVG:
                case CRHM::MIN: // duplicate last
                case CRHM::MAX: // duplicate last
                case CRHM::TOT: // duplicate last
                case CRHM::POS: // duplicate last
                case CRHM::LAST: // duplicate last
                case CRHM::CNT:  // duplicate last
                case CRHM::CNT0: // duplicate last
                  if(ObsFunct_Toggle == 1) // show final value
                    for(long jj = LastIndex+1; jj <= CurrentIndx; ++jj)
                      cdSeries->YValue[jj] = cdSeries->YValue[CurrentIndx];
                 break;
                case CRHM::FIRST: // duplicate first
                    for(long jj = LastIndex+1; jj <= CurrentIndx; ++jj)
                      cdSeries->YValue[jj] = First0;
                 break;
            } // switch
          }
          else if(Funct == CRHM::DLTA && TBase){ // only very first time
            (newVar->*(newVar->LoopFunct))(Indx);
            Delta0 = newVar->values[Indx];

            newVar->UserFunct_ = &ClassVar::Last_; // change from First interval to Last interval
            newVar->FunKind = CRHM::LAST;
            newVar->LoopFunct = &ClassVar::LoopLast;
          }

          Lastkk = Global::DTindx;
          if(CurrentIndx > -1) // skip first time
            LastIndex = CurrentIndx;

          switch (Funct) { // beginning of period reset
            case CRHM::MAX:
              newVar->values[Indx] = -1000000.0;
              break;
            case CRHM::MIN:
              newVar->values[Indx] = 1000000.0;
              break;
            case CRHM::AVG:
            case CRHM::TOT:
            case CRHM::CNT:
            case CRHM::CNT0:
            case CRHM::DLTA:
            case CRHM::POS:
              newVar->values[Indx] = 0.0;
          } // switch

          LastDays = Days;
          Days = 0.0;
        } // if First

        (newVar->*(newVar->LoopFunct))(Indx);

        xx = newVar->values[Indx];
        cdSeries->AddXY(Global::DTnow, xx, "", CurrentColor);

        if(First)
          First0 = xx;

        if(Global::DTindx > DTmin && Global::DTindx > IndxMin){
          switch(Funct){
              case CRHM::AVG:
                Greatest = Days;
                if(LastDays > Days)
                  Greatest = LastDays;
                cdSeries->YValue[CurrentIndx] /= (Global::Freq*Greatest);
                LastDays = 0;
                break;
              case CRHM::DLTA:
                if(!First)
                  cdSeries->YValue[CurrentIndx] -= Delta0;
                break;
          } // switch
        }

        ++Days;

        First = FALSE;
      } // if
    } // for

    if(Global::DTindx > DTmin && Global::DTindx > IndxMin){ // Handle RUN starting after beginning of primary obs file and secondary obs file later
      CurrentIndx = (Global::DTindx - DTminX)/thisVar->FileData->Freq-1;
      switch(Funct){
          case CRHM::AVG:
            Greatest = Days;
            if(LastDays > Days)
              Greatest = LastDays;
            cdSeries->YValue[CurrentIndx] /= (Global::Freq*Greatest);
            if(ObsFunct_Toggle == 1) // show final value
              for(long jj = LastIndex+1; jj <= CurrentIndx; ++jj)
                cdSeries->YValue[jj] = cdSeries->YValue[CurrentIndx];
            break;
          case CRHM::DLTA:
            cdSeries->YValue[CurrentIndx] -= Delta0;
          case CRHM::MIN: // duplicate last
          case CRHM::MAX: // duplicate last
          case CRHM::TOT: // duplicate last
          case CRHM::POS: // duplicate last
          case CRHM::LAST: // duplicate last
          case CRHM::CNT:  // duplicate last
          case CRHM::CNT0: // duplicate last
            if(ObsFunct_Toggle == 1) // show final value
              for(long jj = LastIndex+1; jj <= CurrentIndx; ++jj)
                cdSeries->YValue[jj] = cdSeries->YValue[CurrentIndx];
           break;
          case CRHM::FIRST: // duplicate first
              for(long jj = LastIndex+1; jj <= CurrentIndx; ++jj)
                cdSeries->YValue[jj] = First0;
           break;
      } // switch
    }

    delete newVar->FileData; // created in this routine
    delete newVar; // created in this routine

    cdSeries->Tag = NULL;
  } // else

  Global::DTnow = Save_DTnow; // restore

  if(!CommandLine)  // do not repaint
    Chart->Repaint();
} // end of AddObsPlot
//---------------------------------------------------------------------------

void __fastcall TMain::PrjExitClick(TObject *Sender)
{ // Handles Menu Exit
  this->Close(); // calls TMain::FormClose
}
//---------------------------------------------------------------------------

void __fastcall TMain::ObsFileClose(TObject *Sender){

  TMenuItem *ObsItem;
  MapVar::iterator itVar;
  ClassVar * thisVar;

  TMenuItem * thisMenu = (TMenuItem *) Sender;


  String S = thisMenu->Caption;

  S = S.Delete(1, S.Pos(" ")); // remove "&1 "

  int Pos  = ObsFilesList->IndexOf(S);

  if(Pos == 0 && ObsFilesList->Count > 1) {
    ObsCloseClick(Sender);
    return;
  }

  int Reply = Application->MessageBox(S.c_str(), "Close Observation File", IDOK);

  if(Reply == IDOK) {

    if(Pos == 0) {
      ResetPickers();

      Global::nobs = 1;  // reset to 1
      Global::maxobs = 1;  // reset to 1
    }

    ObsItem = MainMenu1->Items->Items[1];
    ObsItem->Delete(Pos+4);  // delete submenu

    FreeChart2(Sender); // ?? do not remove VarObsFunct

    ListBox2->Clear();

    ClassData * FileData = (ClassData *) ObsFilesList->Objects[Pos];
    delete FileData;   // delete ClassData instance
    FileData = NULL;
    ObsFilesList->Delete(Pos);  // delete entry in list

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType >= CRHM::Read)
	if(IndexOf(ListBox2, (*itVar).second->name.c_str()) == -1)
          ListBox2->Items->AddObject((*itVar).second->name.c_str(),
            (TObject*) (*itVar).second);
    }

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::VARIABLE)
	if(IndexOf(ListBox1, (*itVar).second->name.c_str()) == -1)
	  ListBox1->Items->AddObject((*itVar).second->name.c_str(),
	    (TObject*) (*itVar).second);
    }

    S = ExtractFileName(S);

    for(long jj = 0; jj < SeriesCnt; jj++) {
      if(cdSeries[jj]->Title == S) {

//        ClassVar* thisVar =  (ClassVar *) cdSeries[jj]->Tag;

        cdSeries[jj]->ParentChart = NULL;
        cdSeries[jj]->Clear();
      }
    }

    Pos  = PrjObsHelp->IndexOf(S.SubString(1, S.Length()-4) + ".obs");  // remove help file - if it exists
    if(Pos > -1) {
      PrjObsHelp->Delete(Pos);
      UpDateModelMenu();
    }
//    dirty = true;
  }
} // end of ObsFileClose
//---------------------------------------------------------------------------

void __fastcall TMain::FormDestroy(TObject *Sender){

  HtmlHelp(0, NULL, HH_CLOSE_ALL, 0);

  for(int ii = 0; ii < ObsFilesList->Count; ++ii) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
    delete FileData;   // delete ClassData instance
  }

  delete ObsFilesList;

  ModVarRemove(Global::MapVars);
  Global::SharedMapPars.clear();

  delete ProjectList;

#ifdef CRHM_DLL

    Global::OurModulesList->Clear();  // clear list;

    DLL1CloseALLClick(Sender);    // remove any DLLs

    delete OpenDLLs;

#endif

  delete Global::OurModulesList;

  delete Global::ModelModulesList;

  delete Global::OurHelpList;

  delete Global::PendingDLLModuleList;

  delete PrjObsHelp;

  delete Global::DeclRootList;

  ClearListBox4(Sender);

  if(cdSeries) {
    for (int ii = 0; ii < SeriesCnt; ii ++) {
      cdSeries[ii]->ParentChart = NULL;
      cdSeries[ii]->Clear();
    }

    delete [] cdSeries;
  }

  for(long ii=0; ii < 5; ++ii)
    delete[] Global::HRU_OBS_DIRECT[ii];

  delete[] Global::HRU_OBS_DIRECT;
} // end of FormDestroy
//---------------------------------------------------------------------------

void __fastcall TMain::DateTimePicker1Change(TObject *Sender)
{
  FreeChart2(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMain::DateTimePicker2Change(TObject *Sender)
{
  FreeChart2(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMain::FreeChart1(TObject *Sender){

  if(SeriesCnt > 0) {
    for (int ii = 0; ii < SeriesCnt; ii ++) {

      ClassVar* thisVar =  (ClassVar *) cdSeries[ii]->Tag;
      if(thisVar->FunKind > CRHM::FOBS && !thisVar->values && !thisVar->ivalues)
        delete thisVar;

      cdSeries[ii]->ParentChart = NULL;
      cdSeries[ii]->Clear();
    }
    SeriesCnt = 0;
  }

  ClearListBox4(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMain::FreeChart2(TObject *Sender){

      long end = ListBox4->Items->Count-1;

      for (long ii = end; ii >= 0; --ii) { // reverse order because of the delete
        TLineSeries * cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];


        ClassVar* thisVar =  (ClassVar *) cdSeries->Tag;

        if(thisVar){ // derived from observation
          if(thisVar->root == "") // observation or observation VarObsFunct
            ListBox4->Items->Delete(ii);
          else // VarObsFunct
            continue;

          if(thisVar->FunKind > CRHM::FOBS)
            delete thisVar;
        }
        else{ // VarObsFunct
          String Name = ListBox4->Items->Strings[ii];
          Name = Name.SubString(1, Name.LastDelimiter('(')-1);
          thisVar = VarFind(string(string("obs ") + Name.c_str()));

          if(thisVar && thisVar->root == "") // observation or observation VarObsFunct
            ListBox4->Items->Delete(ii);
          else // VarObsFunct
            continue;
        }

        cdSeries->ParentChart = NULL;
        cdSeries->Clear();
      }
}
//---------------------------------------------------------------------------

void __fastcall TMain::WMGetMinMaxInfo(TWMGetMinMaxInfo &Msg)
{

  int X = Msg.MinMaxInfo->ptMaxSize.x; //ptMaxSize is the size of the window
  int Y = Msg.MinMaxInfo->ptMaxSize.y; //when the window is fully maximized

// ptMaxSize is the coordinate of the frame’s lower right corner when it’s maximized.
  Msg.MinMaxInfo->ptMaxSize.x = X;
  Msg.MinMaxInfo->ptMaxSize.y = Y;

// ptMaxPosition is the coordinate of the frame’s upper left corner when it’s maximized.
  Msg.MinMaxInfo->ptMaxPosition.x = 0;
  Msg.MinMaxInfo->ptMaxPosition.y = 0;

//the minimum tracking width (point.x) and the minimum tracking height (point.y) of the window.
  Msg.MinMaxInfo->ptMinTrackSize.x = X*0.75; //ptMinTrackSize = min size allowed
  Msg.MinMaxInfo->ptMinTrackSize.y = Y*0.75; //by dragging with the mouse.

// the maximum tracking width (point.x) and the maximum tracking height (point.y) of the window.
  Msg.MinMaxInfo->ptMaxTrackSize.x = X; //ptMaxTrackSize = max size allowed
  Msg.MinMaxInfo->ptMaxTrackSize.y = Y; //by dragging with the mouse
}
//---------------------------------------------------------------------------

void __fastcall TMain::PrjSaveAsClick(TObject *Sender)
{
  SaveDialogPrj->Filter = "Project Files (*.prj)|*.prj";
  SaveDialogPrj->DefaultExt = "prj";
  SaveDialogPrj->Title = "Save Project As";
  if(SaveDialogPrj->Execute()) {
    SaveDialogPrj->InitialDir = ExtractFilePath(AnsiReplaceStr(SaveDialogPrj->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
    if(SaveDialogPrj->InitialDir.IsEmpty())
      SaveDialogPrj->InitialDir = GetCurrentDir();
    OpenDialogPrj->FileName = SaveDialogPrj->FileName;
    SaveProject(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::PrjSaveClick(TObject *Sender)
{
  if(!SaveDialogPrj->FileName.IsEmpty())
    SaveProject(Sender);
  else
    PrjSaveAsClick(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TMain::SaveProject(TObject *Sender){

    MapPar::iterator itPar;
    MapDim::iterator itDim;
    ClassPar *thisPar;
    ClassVar *lastVar = NULL;
    String Output;

    ProjectList->Add(DescripPrj.c_str());
    TDateTime Dt = TDateTime::CurrentDateTime();
    String S("  Creation: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt));

    ProjectList->Add("###### " + AboutBox->Label2->Caption + S);

    bool Prj = (SaveDialogPrj->FileName.LowerCase()).Pos(".prj");
    if(Prj) {

      Main->Text = Main->Text.SubString(1, 49) + " - " + SaveDialogPrj->FileName;

      ProjectList->Add("Dimensions:");
      ProjectList->Add("######");
      ProjectList->Add(String("nhru " + String(Global::maxhru)));
      ProjectList->Add(String("nlay " + String(Global::nlay)));
      ProjectList->Add(String("nobs " + String(Global::nobs)));
      ProjectList->Add("######");

      ProjectList->Add("Macros:");
      ProjectList->Add("######");

      for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii)
        ProjectList->Add("'" + Global::MacroModulesList->Strings[ii] + "'");

      ProjectList->Add("######");

      if(!Global::MapAKA.empty()) {
        Mapstr2::iterator it;

        ProjectList->Add("AKAs:");
        ProjectList->Add("######");

        for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {
          string Var = (*it).first + ' ' + (*it).second;
          ProjectList->Add(Var.c_str());
        }
        ProjectList->Add("######");
      }

      ProjectList->Add("Observations:");
      ProjectList->Add("######");
        for(int ii = 0; ii < ObsFilesList->Count; ii++) {
          String S = ObsFilesList->Strings[ii];
          ProjectList->Add(S);
        }
      ProjectList->Add("######");

      ProjectList->Add("Dates:");
      ProjectList->Add("######");
      String S;
      S = DateTimePicker1->Date.FormatString("yyyy m d");
      if(ObsFilesList->Count == 0)
        S = S + " " + FloatToStrF(Global::Freq, ffGeneral, 0, 0);
      ProjectList->Add(S);
      S = DateTimePicker2->Date.FormatString("yyyy m d");
      ProjectList->Add(S);
      ProjectList->Add("######");

 #ifdef CRHM_DLL
     if(OpenDLLs->Count > 0) {
       ProjectList->Add("DLLs:");
       ProjectList->Add("######");
       CompactDlls();
       for(int ii = 0; ii < OpenDLLs->Count; ii++) {
         String S = OpenDLLs->Strings[ii];
         ProjectList->Add(S);
       }
       ProjectList->Add("######");
     }
 #endif

      ProjectList->Add("Modules:");
      ProjectList->Add("######");
      for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
        ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
        String S = Global::OurModulesList->Strings[ii];
        if(thisModule->variation > 0){
          string AA("#0 ");
          AA[1] += log(thisModule->variation)/log(2) + 1;
          S = S + AA.c_str();
        }
        else
          S = S + " ";

        S = S + thisModule->DLLName + " ";
        S = S + thisModule->Version;
        ProjectList->Add(S);

        if(thisModule->isGroup || thisModule->isStruct){
          list<ModulePtr> ::iterator iterM;
          iterM = ((ClassMacro *) thisModule)->Modules.begin();
          while(iterM != ((ClassMacro *) thisModule)->Modules.end()) {
            boost::weak_ptr<ClassModule> MP((*iterM));
            String S = String(" +") + (*iterM)->NameRoot.c_str();
            if((*iterM)->variation > 0){
              string AA("#0 ");
              AA[1] += log((*iterM)->variation)/log(2) + 1;
              S = S + AA.c_str();
            }
            else
              S = S + " ";

            S = S + (*iterM)->DLLName + " ";
            S = S + (*iterM)->Version;
            ProjectList->Add(S);
            ++iterM;
          }
        }
      }
      ProjectList->Add("######");

      ProjectList->Add("Parameters:");
      ProjectList->Add("###### 'basin' parameters always first");

      for(int bb = 0; bb < 2; ++bb){ // shared parameters first - initially over-write all others
        for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
          thisPar = (*itPar).second;

          if(thisPar->param == "HRU_group")
            continue;
          if(bb == 0 && thisPar->module != "shared")
            continue;
          if(bb == 1 && thisPar->module == "shared")
            continue;

          String S = String(thisPar->module.c_str()) + " " + String(thisPar->param.c_str());

          if(thisPar->varType != CRHM::Txt)
            S += " <" + FloatToStrF(thisPar->minVal, ffGeneral, 4, 0)+ " to " + FloatToStrF(thisPar->maxVal, ffGeneral, 4, 0) + ">";

          ProjectList->Add(S);

          for(int jj = 0; jj<thisPar->lay; jj++) {
            S = "";
            for(int ii = 0; ii < thisPar->dim; ii++) {
              if(thisPar->varType == CRHM::Float)
                S = S + FloatToStrF(thisPar->layvalues[jj][ii], ffGeneral, 4, 0) + " ";
              else if(thisPar->varType == CRHM::Int)
                S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], ffFixed, 8, 0) + " ";
              else if(thisPar->varType == CRHM::Txt)
                if(thisPar->Strings->Count > ii)
                  S = S + "'" + thisPar->Strings->Strings[ii] + "' ";
                else
                  S = "''"; // handle null string

              if(ii%16 == 15) {
                ProjectList->Add(S);
                S = "";
              }
            }
            if(!S.IsEmpty()) {ProjectList->Add(S); S = "";}
          }
          if(!S.IsEmpty()) ProjectList->Add(S);
        } // output loop
      }  // basin module/other loop

      ProjectList->Add("######");

      ProjectList->Add("Initial_State");
      ProjectList->Add("######");

      TMenuItem *StateItem;
      StateItem = MainMenu1->Items->Items[5];

      if(StateItem->Count > 5){ // State files open
        for(int ii = 5; ii < StateItem->Count; ++ii)
          ProjectList->Add(StateItem->Items[ii]->Caption);
      }

      ProjectList->Add("######");

      ProjectList->Add("Final_State");
      ProjectList->Add("######");
        if(SaveStateFlag) {
          ProjectList->Add(SaveDialogState->FileName);
        }
      ProjectList->Add("######");
    }

    ProjectList->Add("Summary_period");
    ProjectList->Add("######");
    String T = TBases[TBase];
    if(TBase == 1)
    T = T + " " + String(water_year_month);
    ProjectList->Add(T);
    ProjectList->Add("######");

    ProjectList->Add("Log_Time_Format");
    ProjectList->Add("######");
    T = TLogFormats[Global::TimeFormat];
    ProjectList->Add(T);
    ProjectList->Add("######");

    if(Global::LOGVARLOAD) {
      ProjectList->Add("LOGVARLOAD");
      ProjectList->Add("######");
    }

    ProjectList->Add("Display_Variable:");
    ProjectList->Add("######");

    for (int ii = 0; ii < SeriesCnt; ii ++) { // transfer TeeChart data

      ClassVar *thisVar =  (ClassVar *) cdSeries[ii]->Tag;
      thisVar->TchrtOpt = cdSeries[ii]->VertAxis == aRightAxis;
    }

    lastVar = NULL;
    Output = "";

    if(HruNames)
      HruNameClick(Sender);

    for (int ii = 0; ii < ListBox3->Items->Count; ++ii) {

      long lay, dim;

      ExtractHruLay(ListBox3->Items->Strings[ii], dim, lay);

      ClassVar *thisVar = (ClassVar *) (ListBox3->Items->Objects[ii]);

      if(thisVar->TchrtOpt)
        dim = -dim;
      String SS = String(dim);
      if(thisVar->lay > 0) SS += "," + String(lay);

      string Mod = thisVar->module;

      if(lastVar == NULL)
        Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
      else if(lastVar != thisVar) {
        ProjectList->Add(Output);
        Output = (Mod + " " + thisVar->name + " ").c_str() + SS;
      }
      else
        Output += " " + SS;

      lastVar = thisVar;
    }

    if(!Output.IsEmpty()) ProjectList->Add(Output);

    ProjectList->Add("######");

    ProjectList->Add("Display_Observation:");
    ProjectList->Add("######");

    lastVar = NULL;
    String kind, lastkind;
    Output = "";

    for (int ii = 0; ii < ListBox4->Items->Count; ii ++) {

      String S = ListBox4->Items->Strings[ii];
      String FullName;
      long dim, lay;
      kind = "_obs";

      String Name = ExtractHruLayFunct(ListBox4->Items->Strings[ii], dim, lay, kind, FullName);

      TLineSeries *cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];

      ClassVar *thisVar;
      thisVar =  (ClassVar *) cdSeries->Tag; // always OK for observation

      if(!thisVar || !thisVar-> FileData){  // VarObsFunct
        if(!thisVar){
          long Indx = ListBox3->Items->IndexOf(FullName);
          if(Indx > -1)
            thisVar = (ClassVar *) ListBox3->Items->Objects[Indx];
          else
            thisVar = VarFind(string(string("obs ") + Name.c_str()));
        }
      }

      if(cdSeries->VertAxis == aRightAxis)
        dim = -dim;

      String SS = String(dim);

      if(lay > 0)
        SS += "," + String(lay);

      if(Output != "" && (thisVar != lastVar || kind != lastkind)){
        ProjectList->Add(Output + " " + lastkind);
        if(thisVar)
          Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();
        else // fudge for obs _Avg thru _Tot being null for observations
          Output = (String("obs ") + Name.c_str() + " " + SS.c_str()).c_str();
      }
      else if(lastVar) // add to earlier output
        Output += " " + SS;
      else // first output
        Output = (thisVar->module + " " + Name.c_str() + " " + SS.c_str()).c_str();

      lastVar = thisVar;
      lastkind = kind;
    }


    if(!Output.IsEmpty()) ProjectList->Add(Output + " " + kind); // handle last output

    ProjectList->Add("######");

    if(PrjAutoRun->Checked) {
      ProjectList->Add("Auto_Run");
      ProjectList->Add("######");
    }

    if(SaveChartTemplate->Checked) {
      ProjectList->Add("SaveChartTemplate");
      ProjectList->Add("######");
      String FileName = ChangeFileExt(SaveDialogPrj->FileName, ".Tee");
      Chart->RemoveAllSeries();
      SaveChartToFile(Chart, FileName, false, true);
    }

    if(PrjAutoExit->Checked) {
      ProjectList->Add("Auto_Exit");
      ProjectList->Add("######");
    }

    if(Last1->Checked) {
      ProjectList->Add("Log_Last");
      ProjectList->Add("######");
    }

    if(All1->Checked) {
      ProjectList->Add("Log_All");
      ProjectList->Add("######");
    }

    if(DebugScreen1->Checked) {
      ProjectList->Add("Log_Screen");
      ProjectList->Add("######");
    }

    if(SummaryScreen1->Checked) {
      ProjectList->Add("Summary_Screen");
      ProjectList->Add("######");
    }

    ProjectList->Add("TChart:");
    ProjectList->Add("######");

    for(int ii = 0; ii < Chart->Title->Text->Count; ++ii)
      ProjectList->Add(Chart->Title->Text->Strings[ii]);
    ProjectList->Add(" ");

    for(int ii = 0; ii < Chart->SubTitle->Text->Count; ++ii)
      ProjectList->Add(Chart->SubTitle->Text->Strings[ii]);
    ProjectList->Add(" ");

    ProjectList->Add(Chart->Axes->Items[2]->Title->Caption);
    ProjectList->Add(" ");

    for(int ii = 0; ii < Chart->Foot->Text->Count; ++ii)
      ProjectList->Add(Chart->Foot->Text->Strings[ii]);
    ProjectList->Add(" ");

    for(int ii = 0; ii < Chart->SubFoot->Text->Count; ++ii)
      ProjectList->Add(Chart->SubFoot->Text->Strings[ii]);
    ProjectList->Add(" ");

    if(Chart->MaxPointsPerPage != 0) {
      String S = String(Chart->MaxPointsPerPage) + " " + String(Chart->Page);
      ProjectList->Add(S);
    }
    ProjectList->Add("######");

    ProjectList->SaveToFile(SaveDialogPrj->FileName);

    ProjectList->Clear();

    dirty = false;
} // end of SaveProject
//---------------------------------------------------------------------------

void __fastcall TMain::PrjOpenClick(TObject *Sender) {

  OpenDialogPrj->Filter = "Project Files (*.prj)|*.prj";
  OpenDialogPrj->Title = "Open Project";
  if(OpenDialogPrj->Execute()) DoPrjOpen(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMain::DoPrjOpen(TObject *Sender) {

  MapPar::iterator itPar;
  ClassPar *thisPar;
  ClassVar *thisVar;
  ifstream DataFile;
  long Variation;

  char module[80], param[80], name[80];
  string S, s, Line;
  String SS;

  Global::WQ_prj = false;

  Global::NaNcheck = false;
  Global::LOGVARLOAD = false;

  String Default = GetCurrentDir();

  SaveDialogPrj->InitialDir = Default;

  ProjectDir  = Default + "\\";

  int iFileHandle = FileOpen(OpenDialogPrj->FileName, fmOpenRead);
  if(iFileHandle > -1){ // not file error
    int T = FileGetDate(iFileHandle);
    ProjectFileDate = FileDateToDateTime(T);
    FileClose(iFileHandle);
  }

  DataFile.open(OpenDialogPrj->FileName.c_str());
  if(!DataFile) {
    Application->MessageBox("cannot open file", "File Error", MB_OK);
    return;
  }

  bool Prj = (OpenDialogPrj->FileName.LowerCase()).Pos(".prj");
  if(Prj) {

    if(ProjectOpen) {
      if(Application->MessageBox("Current Project will be overwritten! Proceed?",
                             "Warning", MB_OKCANCEL) == IDCANCEL) return;

      String OpenSave(OpenDialogPrj->FileName);

      PrjCloseClick(Sender);// close current model
      if(cancel) // close current model
        return; // cancel

      OpenDialogPrj->FileName = OpenSave;
    }
    else
      ObsCloseClick(Sender); // close any Observation files opened
  }

  OpenDialogPrj->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogPrj->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
  if(OpenDialogPrj->InitialDir.IsEmpty())
    OpenDialogPrj->InitialDir = GetCurrentDir();

  SaveDialogPrj->InitialDir = OpenDialogPrj->InitialDir;
  SetCurrentDir(OpenDialogPrj->InitialDir);

  ProjectOpen = true;
  Last1->Checked = false;
  All1->Checked = false;
  DebugScreen1->Checked = false;

  Main->Text = Main->Text.SubString(1, 49) + " - " + OpenDialogPrj->FileName;
  Chart->Title->Text->Clear();
  Chart->Title->Text->Add(Main->Text.SubString(1, 49));

  Chart->SubTitle->Text->Clear();
  Chart->SubTitle->Text->Add(OpenDialogPrj->FileName);

  Chart->Foot->Text->Clear();
  Chart->SubFoot->Text->Clear();

  SaveDialogPrj->FileName = OpenDialogPrj->FileName;

  SaveDialogPrj->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogPrj->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
  if(SaveDialogPrj->InitialDir.IsEmpty())
    SaveDialogPrj->InitialDir = GetCurrentDir();

  getline(DataFile, DescripPrj);
  DataFile.ignore(180, '#');
  getline(DataFile, Line);

  String as = ExtractFileName(OpenDialogPrj->FileName);
         as = ChangeFileExt(as,".CHM");

  if(FileExistsSp(as)){
    PrjObsHelp->Strings[0] = as.SubString(1, as.Length()-4) + ".chm";
    UpDateHelpMenu();
  }

  Global::MacroModulesList->Clear();

  TBase = 0; // Change to daily

  LabelBase->Caption = TBases[TBase];

  CRHM::TFun Funct = CRHM::FOBS; // Change to observation
  LabelFunct->Caption = FStrings[Funct];

  try{

    do {
      DataFile >> S;
      if(DataFile.eof()) break;

      DataFile.ignore(180, '#');
      getline(DataFile, Line);

      if(S == "AKAs:") {
        string module, type, name, alias, source;

        while(!DataFile.eof()) {
          DataFile >> type ;
          if(type[1] == '#') break;
          DataFile >> module >> name >> alias;

          string::size_type pp = module.find('#');  // AKAs do not have variation. Should never happen except using editor
          if(pp != string::npos)
            module.erase(pp);

          TAKA Type = AKAtype(type);

          if(Type == VARG || Type == OBSR || Type == OBSF) {
            DataFile >> source;
            pp = source.find('#');
            if(pp != string::npos)
              source.erase(pp);

            alias += ' ' + source;
          }

          if(Type != AKAERROR) {
            Pairstr2 Item = Pairstr2(type + " " + module + " " + name, alias);
            Global::MapAKA.insert(Item);
          }

          if(DataFile.eof()) return; // final exit

        }
      }
      else if(S == "DLLs:") {
        getline(DataFile, S);
#ifdef CRHM_DLL
        while(S[1] != '#'){

          SS = S.c_str();
          if(!FindFileName(SS)){
              Application->MessageBox(String("file: " + SS).c_str(), "DLL not found!", MB_OK);
              return;
          }

          getline(DataFile, S);
        }
#else
        CRHMException Except("Using DLLs in Non-DLL CRHM model", ERR);
        Application->MessageBox(Except.Message.c_str(),
                                 "Use DLL CHRM model", MB_OK);
        LogError(Except);

        while(S[1] != '#'){
          DataFile >> S;
        }
#endif
      }
      else if(S == "Macros:") {
        getline(DataFile, S);

        while (S[1] != '#') {
          Global::MacroModulesList->Add((S.substr(1, S.length()-2)).c_str());
          getline(DataFile, S);
        }
        MacroLoad(Sender);
      }
      else if(S == "Observations:") {
        getline(DataFile, S);
        while(S[1] != '#'){
          SS = S.c_str();
          if(FindFileName(SS)){
            OpenDialogObs->FileName = SS.c_str();

            OpenDialogObs->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogObs->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
            if(!OpenObsFile(Sender, SS)) ;   // was return
          }
          else{
            Application->MessageBox(SS.c_str(), "Cannot find observation file", MB_OK);
          }
          getline(DataFile, S);
        }
      }
      else if(S == "Dates:") {
        int D[3];
        TDateTime DT;

        if(Global::DTstart == 0.0){ // handles no observation file

          ResetPickers();

          DateTimePicker1->Enabled = true;
          DateTimePicker2->Enabled = true;
        }

        for (int ii = 0; ii < 3; ii++)
          DataFile >> D[ii];

        DT = EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]);

        if(ObsFilesList->Count){ // leave at max for simulation
          DateTimePicker1->MinDate = Global::DTstart;
          DateTimePicker1->MaxDate = Global::DTend;
        }

        if(DT >= DateTimePicker1->MinDate && DT <= DateTimePicker1->MaxDate || !ObsFilesList->Count) // was for -ve dates
          DateTimePicker1->Date = floor(DT);
        else
          DateTimePicker1->Date = DateTimePicker1->MinDate;

        int c;
        while((c = DataFile.peek(), c==32)) {
          DataFile.get();
          c = DataFile.peek();
        }

        if(isdigit(c) && ObsFilesList->Count == 0) {
            DataFile >> Global::Freq;
            Global::Interval = 1.0/Global::Freq;
          }
        else
            DataFile.ignore(256, '\n');

        for (int ii = 0; ii < 3; ii++)
          DataFile >> D[ii];

        DT = EncodeDate((Word)D[0], (Word)D[1], (Word)D[2]);

        if(ObsFilesList->Count){ // leave at max for simulation
          DateTimePicker2->MinDate = Global::DTstart;
          DateTimePicker2->MaxDate = Global::DTend;
        }

        if(DT >= DateTimePicker2->MinDate && DT <= DateTimePicker2->MaxDate || !ObsFilesList->Count) // was for -ve dates
          DateTimePicker2->Date = floor(DT);
        else
          DateTimePicker2->Date = DateTimePicker2->MaxDate;

       DataFile >> S;
      }
      else if(S == "Modules:") {
        Global::OurModulesList->Clear();

#ifdef CRHM_DLL
        TDllModule DllModule;
#endif
        for(;;) {
          getline(DataFile, S);
          if(S[1] == '#') break;

          bool InGrp = false;
          string::size_type idx = S.find('+');
          if(idx != string::npos){
            S = S.substr(idx+1);
            InGrp = true;
          }
          idx = S.find(' ');
          s = S.substr(0, idx);

          idx = S.find('#');
          if(idx != string::npos){
            Variation = pow(2, S[idx+1] - char('1'));
            s = S.substr(0, idx);
          }
          else
            Variation = 0;

          if(!InGrp)
            Global::OurModulesList->AddObject(s.c_str(), (TObject*) Variation);

          S = S.substr(idx+1);
          idx = S.rfind(' ');
          S = S.substr(0, idx);

          transform(S.begin(), S.end(), S.begin(), ::toupper);
          idx = S.rfind(".DLL");
#ifdef CRHM_DLL
          if(idx != string::npos){ // not DLL file
            bool exists = false;

            TDllModule::iterator it;
            pair<TDllModule::iterator, TDllModule::iterator> range = DllModule.equal_range(S.c_str());

            for(it = range.first; it != range.second; ++it){
              if(it->second == s.c_str())
                exists = true;
                break;
              }

            if(!exists){
              String SS = S.c_str();
              FindFileName(SS);
              PairDllModule Item = PairDllModule(SS.c_str(), s.c_str());
              DllModule.insert(Item);
            }
          }
#endif
        }

#ifdef CRHM_DLL
        TDllModule::iterator itPar, itPar2;
        pair<TDllModule::iterator, TDllModule::iterator> range;

        itPar = DllModule.begin();

// process multimap by DLL file name
        while (itPar !=  DllModule.end()) {
          string S = (*itPar).first;

// transfer module names
          Global::PendingDLLModuleList->Clear(); // clear
          range = DllModule.equal_range(S);
          for(itPar2 = range.first; itPar2 != range.second; ++itPar2) {
            String S2 = (*itPar2).second;
            Global::PendingDLLModuleList->Add(S2); // add
          }

          if(!OpenDLLFile(S.c_str())) ;

          itPar = DllModule.upper_bound(S);
        } // while

        DllModule.clear(); // finished
#endif

        for(int ii = Global::OurModulesList->Count-1; ii >= 0; --ii) {
          String Name = Global::OurModulesList->Strings[ii];
          int jj = CheckforModule(Name, ii);
          if(jj < 0) {
            CRHMException Except("Unknown Module: \"" + string(Name.c_str()) + "\"", ERR);
            Application->MessageBox(Except.Message.c_str(),
                               "Unknown Module: incorrect CRHM version or DLL not loaded", MB_OK);
            LogError(Except);
            Global::OurModulesList->Delete(ii);

            DataFile.seekg(0, ios_base::end);  // cause break out
          }
          else{
            Variation = ((long) Global::OurModulesList->Objects[ii]);
            ((ClassModule*) Global::AllModulesList->Objects[jj])->variation = Variation;
            Global::OurModulesList->Objects[ii] = Global::AllModulesList->Objects[jj];
          }
        }

        InitModules(Sender);
      }
      else if(S == "Dimensions:") {
        DataFile >> S;
        long dim;
        while(S[1] != '#'){
          DataFile >> dim;
          setdim(S, dim);
          DataFile >> S;
        }
      }
      else if(S == "Parameters:") {

        int c;
        long Cols, Rows;
        bool TooFewHRUs = false;
        string ss;
        long ErrorCnt = 5;

        while(!DataFile.eof()) {
          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> param;

          if(DataFile.eof()) return; // final exit

          DataFile.ignore(80, '\n'); // need for character input, why?
          S = "";

          do { // determine # columns
            getline(DataFile, ss);
            S += ss + ' ';
            while(c = DataFile.peek(), iscntrl(c) || isspace(c))
              DataFile.get();

          } while(c = DataFile.peek(), !isalpha(c) && c != '#');

          string Sc = S; // use copy
          string::iterator pos; // first handle single quotes
           bool inField = false;

          for(pos = Sc.begin(); pos != Sc.end(); ++pos){ // change spaces to '_' to keep form
            if(*pos == '\'')
              inField = !inField;
            if(inField && *pos == ' ')
              *pos = '_';
          }

          istringstream instr; // count columns
          instr.clear();
          instr.str(Sc);
          Cols = 0;
          for (;;) {
            instr >> s;
            if(instr.fail()) break;
              ++Cols; // # of HRU's in Basin
          }

          if(string(module, strlen(module)) == "Shared") {
// write Shared parameters to module parameters
// all parameter values are set to basin values.  If re-defined in a module will be changed.
            MapPar::iterator itPar;
            for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
              thisPar = (*itPar).second;
              if(thisPar->param == string(param, strlen(param))){
                if(thisPar->dim == Cols/thisPar->lay) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                  break;
//                else if(Cols > 0 && Cols%thisPar->lay == 0) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
//                  break;
                else if(thisPar->varType == CRHM::Txt && thisPar->dimen < CRHM::NHRU) // text can have variable length
                  break;
                else if(Cols%thisPar->dim == 0 && thisPar->dim != Cols/thisPar->dim){ // (thisPar->param == "obs_elev" || thisPar->param == "soil_withdrawal") &&
                  CRHMException TExcept("Upgrading layer dimension of parameter added to shared: '" + string(thisPar->module) + " -> '" + string(thisPar->param) + "'", WARNING);
                  LogError(TExcept);
                  break;
                }
                else { // Added to handle 2D parameters
                  if(thisPar->param == string(param, strlen(param)) && (thisPar->dim == Cols/thisPar->dim))
                    break;
                  else
                    thisPar = NULL;
                }
              }
              else
                thisPar = NULL; // required for last loop when parameter not found
            }
          }
          else{
            thisPar = ClassParFind(module, param); // find module parameter for template
            if(thisPar)
              strcpy(module, thisPar->module.c_str()); // set it to found name
          }

          if(thisPar) {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = module; // set module name
            if(thisPar->varType == CRHM::Txt) {
              newPar->Strings->DelimitedText = S.c_str();
            }
            else {
              Rows = 0;
              istringstream instr; // count columns
              instr.clear();
              instr.str(S);
              for(int jj = 0; jj <thisPar->lay; ++jj) {
                Cols = 0;
                for(int ii = 0; ii < newPar->dim; ++ii) {
                  if(newPar->varType == CRHM::Float){
                    float x;
                    instr >> x;
                    if(instr.fail())
                      break;
                    newPar->layvalues[jj][ii] = x;
                  }
                  else if(newPar->varType == CRHM::Int) {
                    float x;
                    instr >> x;
                    if(instr.fail())
                      break;
                    newPar->ilayvalues[jj][ii] = x;
                  }
                  ++Cols;
                } // for ii (Cols)

                if(instr.fail()) { // parameter data shortage

                  if(!TooFewHRUs && newPar->module != "Shared") {
                    Application->MessageBox(string("parameter \"" + thisPar->param + "\" in module \"" + newPar->module + "\" only some parameter values or layers are available.").c_str(),
                                   "Too few parameter values or layers. Duplicating last HRU values.", MB_OK);
                    if(newPar->lay > Global::nlay)
                      Global::nlay = newPar->lay;

                    TooFewHRUs = true;
                  }

                  if(!(Cols == 0 && newPar->lay > Rows)){ // always handle rows before filling columns

                    for(int ii = Cols; ii < newPar->dim; ++ii){ // fills columns
                      if(newPar->varType == CRHM::Float)
                        newPar->layvalues[Rows][ii] = newPar->layvalues[Rows][ii-1];
                      else
                        newPar->ilayvalues[Rows][ii] = newPar->ilayvalues[Rows][ii-1];
                    }
                  } // if
                  else{
                    for(int jjj = Rows; jjj <thisPar->lay; ++jjj){
                      for(int ii = 0; ii < newPar->dim; ++ii){
                        if(newPar->varType == CRHM::Float)
                          newPar->layvalues[jjj][ii] = newPar->layvalues[jjj-1][ii];
                        else
                          newPar->ilayvalues[jjj][ii] = newPar->ilayvalues[jjj-1][ii];
                      } // for
                    } // for
                  } // else
                }
                ++Rows;
              } // for jj (Rows)
            } // else

            if(String(module) == "Shared") {// Shared parameters first - initially over-write all others
              SetSharedParams(newPar); // copy template parameter to basin module
              delete newPar;
            }
            else
              ClassParSet(newPar);  // can delete newPar!
          }
          else {
            if(String(param) != "Use_Observations_As_Supplied"){
              if(ErrorCnt){
                --ErrorCnt;
                CRHMException Except("Unknown Module Parameter: " + string(module) + " -> "+ string(param) +
                  " in " + string(OpenDialogPrj->FileName.c_str()), ERR);
                Application->MessageBox(Except.Message.c_str(),
                                   "Unknown Parameter in project file", MB_OK);
                LogError(Except);
              }
            }

            while(c = DataFile.peek(), !isalpha(c) && c != '#')
              DataFile.ignore(256, '\n');
          }
          long cnt = Global::MapPars.size();
          DataFile.clear();
        } // while
        SqueezeParams(Sender);  // converts identical parameters to shared parameters
      }
      else if(S == "Summary_period"){

        while(!DataFile.eof()) {
          getline(DataFile, S);
          if(S[1] == '#') break;
            String MM;
            SS = S.c_str();
            long jj = SS.LastDelimiter(" ");
            if(jj){
              water_year_month = (SS.SubString(jj+1, SS.Length()-1)).ToInt();
              SS = SS.SubString(1, jj-1);
              MM = " - " + Tmonths[water_year_month-1];
            }
            for(long Base = 0; Base < 5; ++Base)
              if(SS == TBases[Base]){
                  LabelBase->Caption = TBases[Base] + MM;
                  TBase = Base;
                break;
              }
        } // while
      }
      else if(S == "Log_Time_Format"){

        while(!DataFile.eof()) {
          getline(DataFile, S);
          if(S[1] == '#') break;
            SS = S.c_str();

            for(long Base = 0; Base < 3; ++Base)
              if(SS == TLogFormats[Base]){
                Global::TimeFormat = (CRHM::TIMEFORMAT) Base;
                break;
              }
        } // while
      }
      else if(S == "LOGVARLOAD"){
        Global::LOGVARLOAD = true;
      }
      else if(S == "Display_Variable:"){
        istringstream instr;
        string::size_type pp;
        if(Global::LOGVARLOAD){
          ifstream DataFile;
          string List("SWE, soil_moist, snowmeltD");
          DataFile.open(String(OpenDialogPrj->InitialDir + "\\LogVarLoad.lvl").c_str());
          if(DataFile) {
            CRHMException TExcept("Loading ouput variables from file: 'LogVarLoad.lvl'.", WARNING);
            LogError(TExcept);
            getline(DataFile, List);
            DataFile.close();

            pp = List.rfind(',');  // remove commas
            if(pp != string::npos){
              while(pp != string::npos){
                List[pp] = ' ';
                pp = List.rfind(',');
              }
            }
          }

          instr.str(List);

          for( ; ; ) {
            instr >> S;
            if(instr.fail()) break;

            for(long gg = 0; gg <= Global::GroupCntTrk; gg++){
              string AA, S2;
              S2 = S;
              if(Global::GroupCntTrk > 0){
                if(gg > 0){
                  GroupEnding(AA, gg);
                  S2 += AA;
                }
                else
                  continue;
              }

              long GetUnit = FindWildVarFloat(S2, thisVar); // name

              if(thisVar) {
                for(long hh = 1; hh <= thisVar->dim; hh++){
                  SS = String(S2.c_str()) + "(" + String(hh) + ")";
                    if(IndexOf(ListBox3, SS) == -1)
                      ListBox3->Items->AddObject(SS, (TObject*) thisVar);
                } // for
              } // if
            } // for
          } // variable List
        }
        else{
          while(!DataFile.eof()) {

            long Index, lay;
            bool comma;

            getline(DataFile, S);
            if(S[1] == '#') break;

            pp = S.rfind(',');
            if(pp != string::npos){
              comma = true;
              while(pp != string::npos){
                S[pp] = ' ';
                pp = S.rfind(',');
              }
            }
            else
              comma = false;

            instr.clear();
            instr.str(S);
            instr  >> module;
            instr  >> name;

            S = string(module) + ' ' +  string(name);

            thisVar = ClassVarFind(S);

            if(thisVar) {

              for( ; ; ) {
//                DataFile >> Index;
                if(comma){
                  instr >> Index;
                  if(Index < 0) { // right axis 11/30/17
                    Index = labs(Index);
                    thisVar->TchrtOpt = 1;
                  }
                  if(instr.fail()) break;
                  instr >> lay;
                  SS = String(thisVar->name.c_str()) + "(" + String(Index) + ',' + String(lay) + ")";
                }
                else{
                  lay = 0;
                  instr >> Index;
                  if(instr.fail()) break;

                  if(Index < 0) { // right axis
                    Index = labs(Index);
                    thisVar->TchrtOpt = 1;
                  }
                  SS = String(thisVar->name.c_str()) + "(" + String(Index) + ")";
                }

                if(IndexOf(ListBox3, SS) == -1 && Index <= thisVar->dim)
                  ListBox3->Items->AddObject(SS, (TObject*) thisVar);
              } // infinite for
            }
            else {
                CRHMException Except("Unknown Variable \"" + S +
                       "\" in " + string(OpenDialogPrj->FileName.c_str()), ERR);
                Application->MessageBox(Except.Message.c_str(),
                                   "Unknown Variable in project file", MB_OK);
                LogError(Except);

                DataFile.ignore(256, '\n');
            }
            instr.clear();
            DataFile.clear();
          } // while
        }
      }
      else if(S == "Display_Observation:") {
        istringstream instr;
        string::size_type pp, pp1;
        string Kind;
        String SS_Index;
        long Index, lay;
        bool comma, isVar;

        while(!DataFile.eof()) {
          getline(DataFile, S);
          if(S[1] == '#') break;

          pp = S.rfind('_');
          if(pp != string::npos){
            Kind = S.substr(pp);
            S.erase(pp-1);
            if(Kind == "_obs")
              Kind = "";
          }

          pp = S.rfind(',');
          if(pp != string::npos){
            comma = true;
            while(pp != string::npos){
              S[pp] = ' ';
              pp = S.rfind(',');
            }
          }
          else
            comma = false;

          instr.clear();
          instr.str(S);
          instr  >> module;
          instr  >> name;

          string S1 = string(module) + ' ' +  string(name);

          thisVar = ClassVarFind(S1);

          if(thisVar)
            isVar = true;
          else
            isVar = false;

          for( ; ; ) {
            if(comma){
              instr >> Index;
              if(instr.fail()) break;
              instr >> lay;
              SS = String(name) + '(' + String(labs(Index)) + ',' + String(lay) + ')';
              SS_Index = SS;
              S1 = string(module) + ' ' + SS.c_str();
              if(!isVar){
                thisVar = ClassVarFind(S1);
                SS += "(" + String(Index) + ")" + Kind.c_str();
              }
              else
                SS += Kind.c_str();
            }
            else{
              lay = 0;
              instr >> Index;
              if(instr.fail()) break;

              if(Index < 0) { // right axis
                Index = labs(Index);
              }
              SS = String(name) + '(' + String(labs(Index)) + ')';
              SS_Index = SS;
              S1 = string(module) + ' ' + SS.c_str();
              if(!isVar){
                thisVar = ClassVarFind(S1);
                SS +=  String("(1)") + Kind.c_str(); //
              }
              else
                SS += Kind.c_str();
            }

            if(thisVar && IndexOf(ListBox4, SS) == -1 && (!isVar || lay <= thisVar->lay && Index <= thisVar->dim)){

              if(thisVar->FileData){ // observation

                TLineSeries *cdSeries;
                if(!thisVar || !thisVar->FileData->Times)
                  cdSeries = new TLineSeries(this);
                else
                  cdSeries = (TLineSeries *) new TPointSeries(this);

                cdSeries->Tag = (int) thisVar;
                cdSeries->VertAxis =  (Index < 0);

                cdSeries->XValues->DateTime = TRUE;
                CurrentColor = colours[ListBox4->Count-1 % ncolours];
                cdSeries->Color = CurrentColor;
                cdSeries->Title = SS;

                if(Index < 0)
                   cdSeries->VertAxis = aRightAxis;

                ListBox4->Items->AddObject(SS, (TObject *) cdSeries);

                if(thisVar && thisVar->FileData){ // observation
                  AddObsPlot(Sender, (ClassVar *) thisVar, cdSeries, SS, FindObservationType(Kind.c_str()));
                  cdSeries->ParentChart = Chart;
                }
                else  // VarObsFunct
                  cdSeries->Tag = NULL;
              }
              else{ // VarObsFunct

                if(FindObservationType(Kind.c_str()) > CRHM::MJ_W){
                   long Indx = ListBox3->Items->IndexOf(SS_Index);
                   if(Indx == -1)
                      ListBox3->Items->AddObject(SS_Index, (TObject*) thisVar);
                }

                TLineSeries *cdSeries;
                cdSeries = new TLineSeries(this);

                cdSeries->Tag = (int) thisVar;
                cdSeries->VertAxis =  (Index < 0);

                cdSeries->XValues->DateTime = TRUE;
                CurrentColor = colours[ListBox4->Count % ncolours];
                cdSeries->Color = CurrentColor;
                cdSeries->ParentChart = Chart;
                cdSeries->Title = SS;

                if(Index < 0)
                   cdSeries->VertAxis = aRightAxis;

                ListBox4->Items->AddObject(SS, (TObject *) cdSeries);
                cdSeries->Tag = NULL;
              } // if
            } // if
            else {
                CRHMException Except("Unknown Variable " + S +
                       " in " + string(OpenDialogPrj->FileName.c_str()), ERR);
                Application->MessageBox(Except.Message.c_str(),
                                   "Unknown Variable in project file", MB_OK);
                LogError(Except);

                DataFile.ignore(256, '\n');
            }
          } // infinite for
          instr.clear();
          DataFile.clear();
        } // while
      }
      else if(S == "Initial_State") {
        while(!DataFile.eof()) {
          getline(DataFile, S);
          if(S[1] == '#') break;
	  SS = S.c_str();
	  if(FindFileName(SS)){

	    TMenuItem *ObsItem, *NewItem;
	    ObsItem = MainMenu1->Items->Items[5];

	    NewItem = new TMenuItem(ObsItem);
	    NewItem->Caption = SS;

	    NewItem->OnClick = StateFileClose;
	    ObsItem->Insert(ObsItem->Count, NewItem);
	  }
        }
      }
      else if(S == "Final_State") {
        getline(DataFile, S);
	if(S[1] != '#') {
	  SS = S.c_str();
          SaveDialogState->FileName = SS;
          SaveStateFlag = true;
          DataFile >> S;
        }
        else
          SaveDialogState->FileName = "";
      }
      else if(S == "Auto_Run") {
        PrjAutoRun->Checked = true;
      }
      else if(S == "Auto_Exit") {
        PrjAutoExit->Checked = true;
      }
      else if(S == "Log_Last") {
        Last1->Checked = true;
      }
      else if(S == "Log_All") {
        All1->Checked = true;
      }
      else if(S == "Log_Screen") {
        DebugScreen1->Checked = true;
      }
      else if(S == "Summary_Screen") {
        SummaryScreen1->Checked = true;
      }
      else if(S == "SaveChartTemplate") {
        String FileName = ChangeFileExt(SaveDialogPrj->FileName, ".Tee");
        if(FileExistsSp(FileName)) {
          LoadChartFromFile(dynamic_cast<TCustomChart*>(Chart),FileName);
          SaveChartTemplate->Checked = true;
          Chart->RemoveAllSeries();
        }
        else{
          Application->MessageBox(String("file: '" + FileName).c_str(), "TeeChart Template file not found", MB_OK);
        }
      }
      else if(S == "TChart:" && !SaveChartTemplate->Checked) {
        Chart->Title->Text->Clear();
        Chart->SubTitle->Text->Clear();
        Chart->Foot->Text->Clear();
         Chart->SubFoot->Text->Clear();
        int nn = 0;

        while(!DataFile.eof()){
          getline(DataFile, S);
          if(DataFile.eof()) break;
          if(S[1] == '#') break;
          SS = S.c_str();
          SS = SS.TrimRight();
          if(SS.IsEmpty())
            ++nn;
          else {
            switch (nn) {
              case 0:
                Chart->Title->Text->Add(SS);
              break;
              case 1:
                Chart->SubTitle->Text->Add(SS);
              break;
              case 2:
                Chart->Axes->Items[2]->Title->Caption = SS;
              break;
              case 3:
                Chart->Foot->Text->Add(SS);
              break;
              case 4:
                Chart->SubFoot->Text->Add(SS);
              break;
              case 5:
                int pos = SS.Pos(" ");
                Chart->MaxPointsPerPage = SS.SubString(1, pos-1).ToInt();
                Chart->Page = SS.SubString(pos+1, 10).ToInt();
              break;
            }
          }
        }
      }
    }while(!DataFile.eof());
  }

  catch (CRHMException Except) {
    Application->MessageBox(Except.Message.c_str(), "Loading project Error", MB_OK);
    LogForm->ShowModal();
    DataFile.close();
    return;
  }

  DataFile.close();

  if(PrjAutoRun->Checked && !CommandLine && ObsFilesList->Count != 0) {
    Main->Refresh();
    RunClick(Sender);
  }
} // end of DoPrjOpen
//---------------------------------------------------------------------------

void __fastcall TMain::PrjCloseClick(TObject *Sender)
{
  cancel = false;
  if(dirty){
    int Reply = Application->MessageBox(String("Save changes to " + SaveDialogPrj->FileName + " ?").c_str(), "", MB_YESNOCANCEL);
    if(Reply == IDCANCEL){
      cancel = true;
      return;
    }
    else if(Reply == IDYES)
      PrjSaveClick(Sender);

    dirty = false;
  }

  ProjectOpen = false;
  Chart->MaxPointsPerPage = 0; // reset paging

  while (PrjObsHelp->Count > 1)
    PrjObsHelp->Delete(PrjObsHelp->Count-1);

  PrjObsHelp->Strings[0] = "";
  UpDateHelpMenu();

  Main->Text = Main->Text.SubString(1, 49);
  ObsCloseClick(Sender);       // remove any observations

  FreeChart1(Sender);          // remove series and clear ListBox4

  StateFileCloseAll(Sender); // clear State file menu

  ClearModules(Sender, true);   // remove any modules

  if(cdSeries) {
    delete [] cdSeries;        // remove TLineSeries
    cdSeries = NULL;
  }

  if(InitMacroCnt && InitModCnt){
    --InitModCnt;
    InitMacroCnt = 0;
  }
  AdminMacro.MacroClear();

  UpDateModelMenu();

  DLL1CloseALLClick(Sender);    // remove any DLLs
  Chart->Refresh();

  Global::OurModulesList->Clear();

  Global::MacroModulesList->Clear();

  Global::DeclRootList->Clear();

  Global::MapVars.clear();
  Global::MapVarsGet.clear();
  Global::MapVarsPut.clear();
  Global::MapObsGet.clear();
  Global::MapPars.clear();
  Global::SharedMapPars.clear();

  Global::MapAKA.clear();

  DescripPrj = "Description";

  Global::RapidAdvanceTo = 0;
  Global::LoopTo = 0;
  Global::LoopCnt = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMain::ClearListBox4(TObject *Sender){

      for (int ii = 0; ii < ListBox4->Items->Count; ii++) {
        TLineSeries * cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];

        ClassVar* thisVar =  (ClassVar *) cdSeries->Tag;

        if(thisVar && thisVar->FunKind > CRHM::FOBS){
          if(thisVar->visibility == CRHM::PRIVATE)
            delete thisVar->FileData;
          delete thisVar;
        }

        cdSeries->ParentChart = NULL;
        cdSeries->Clear();
      }

      ListBox4->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMain::ClearModulesClick(TObject *Sender){

  ClearModules(Sender, true);
}
//---------------------------------------------------------------------------


void __fastcall TMain::ClearModules(TObject *Sender, bool All){

  ModVarRemove(Global::MapVars);

  Global::SharedMapPars.clear();

  if(All)
    for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
      ((ClassModule*) (Global::OurModulesList->Objects[ii]))->reset();

  Global::OurModulesList->Clear();

  if(All){
    AdminMacro.MacroClear();

    Global::MacroModulesList->Clear();

    OpenDialogPrj->FileName = "";
    SaveDialogPrj->FileName = "";
  }

  ListBox1->Clear();
  ListBox3->Clear();

  if(cdSeries) {
    for (int ii = 0; ii < SeriesCnt; ii ++)
      cdSeries[ii]->ParentChart = NULL;

    delete [] cdSeries;           // remove TLineSeries
    cdSeries = NULL;
    SeriesCnt = 0; // ??? ListBox3->Items->Count;
  }
  Chart->Refresh();

  Global::BuildFlag = CRHM::BUILD;

  Global::MapAKA.clear(); // remove all AKA
}
//---------------------------------------------------------------------------

void __fastcall TMain::StatSaveStateAsClick(TObject *Sender)
{
  SaveDialogState->Filter = "Initial State Files (*.int)|*.int";
  SaveDialogState->DefaultExt = "int";
  SaveDialogState->Title = "Save Final State As";

  if(SaveDialogState->Execute()) {
    SaveDialogState->InitialDir = ExtractFilePath(AnsiReplaceStr(SaveDialogState->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
    if(SaveDialogState->InitialDir.IsEmpty())
      SaveDialogState->InitialDir = GetCurrentDir();

    SaveStateFlag = true;
  }
  else  SaveStateFlag = false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::SaveState(TObject *Sender)
{
  TStringList *StateList;
  MapVar::iterator itVar;
  ClassVar * thisVar;
  StateList = new TStringList;
  String S;

  StateList->Add("Description of State File - to be added");
  StateList->Add("######");

  StateList->Add("Time:");
  S = (Global::DTnow).FormatString("yyyy m d");
  StateList->Add(S);
  StateList->Add("######");

  StateList->Add("Dimension:");
  StateList->Add(String(Global::nhru) + " " + String(Global::nlay ));
  StateList->Add("######");

  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    thisVar = (*itVar).second;
    if(thisVar->varType < CRHM::Read && thisVar->StatVar) {
      S = String(thisVar->module.c_str()) + " " +
                   String(thisVar->name.c_str());
      StateList->Add(S);
      S = "";
      if(thisVar->lay == 0)
        for(int ii = 0; ii < thisVar->dim; ii++) {
          if(thisVar->values != NULL)
            S = S + FloatToStrF(thisVar->values[ii], ffGeneral, 4, 0) + " ";
          else if(thisVar->ivalues != NULL)
            S = S + FloatToStrF(thisVar->ivalues[ii], ffGeneral, 4, 0) + " ";
          else
            S = S + "-0 ";

          if(ii%10 == 9) {
            StateList->Add(S);
            S = "";
          }
        }
      else
        for(int ll = 0; ll < thisVar->lay; ll++) {
          for(int ii = 0; ii < thisVar->dim; ii++) {
            if(thisVar->layvalues != NULL)
              S = S + FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else if(thisVar->ivalues != NULL)
              S = S + FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else
              S = S + "-0 ";

            if(ii%10 == 9) {
              StateList->Add(S);
              S = "";
            }
          }
          if(!S.IsEmpty()) StateList->Add(S);
          S = "";
        }
      if(!S.IsEmpty()) StateList->Add(S);
      StateList->Add("######");
    }
  }
  StateList->SaveToFile(SaveDialogState->FileName);
  delete StateList;

  SaveDialogState->FileName = "";
  SaveStateFlag = false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
// On main runup, determines state variables to be saved from parameter "basin StateVars_to_Updatefills"VarPar" and
//  flags modules required to be run in Global::RunUpBitSet.
//
// On module, uses Global::ModuleBitSet to determine state variables to be saved from modules being executed.

void __fastcall TMain::ControlSaveState(TObject *Sender, bool MainLoop, ClassPar * VarPar, BitSet &Bit)
{
  TStringList *StateList;
  MapVar::iterator itVar;
  ClassVar * thisVar;
  StateList = new TStringList;
  String S;
  bool Needed;

  Global::RunUpBitSet.reset();

  bool Wild = false;
  if(VarPar && !VarPar->Strings->Strings[0].IsEmpty()) // first parameter determines the type
    Wild = VarPar->Strings->Strings[0].Pos("@") == 0;

  if( MainLoop)
    StateList->Add("Starting main run-up loop");
  else
    StateList->Add("starting module run-ahead to determine future variables");

  StateList->Add("######");

  StateList->Add("Time:");
  S = (Global::DTnow).FormatString("yyyy m d");
  StateList->Add(S);
  StateList->Add("######");

  StateList->Add("DTindx:");
  StateList->Add(String(Global::DTindx));
  StateList->Add("######");

  StateList->Add("CurrentModuleRun:");
  StateList->Add(String(Global::CurrentModuleRun));
  StateList->Add("######");

  StateList->Add("Dimension:");
  StateList->Add(String(Global::nhru) + " " + String(Global::nlay));
  StateList->Add("######");

  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    thisVar = (*itVar).second;
    Needed = false;

    if(thisVar->varType < CRHM::Read && (thisVar->visibility != CRHM::PRIVATE || thisVar->StatVar)){ // Is state variable!  && thisVar->StatVar

      if(!thisVar->InGroup || Global::ModuleBitSet[thisVar->InGroup-1])  // All variables in simple projects and module requested group projects
         Needed = true;
      else if(MainLoop){
        String namebasic = thisVar->name.c_str();
        if(VarPar->Strings->IndexOf(namebasic) > -1)
          Needed = true;
        else if(Wild){ // if Wild reduce parameter to root
          int Idx = namebasic.Pos("@");
          if(Idx){
            namebasic = namebasic.SubString(1, Idx-1);
            if(VarPar->Strings->IndexOf(namebasic) > -1)
              Needed = true;
          }
        } // wild!
        Global::RunUpBitSet[thisVar->InGroup-1] = true;
      } // MainLoop!
    } // state variable!

    if(Needed){
      S = String(thisVar->module.c_str()) + " " + String(thisVar->name.c_str());
      StateList->Add(S);
      S = "";
      if(thisVar->lay == 0)
        for(int ii = 0; ii < thisVar->dim; ii++) {
          if(thisVar->values != NULL)
            S = S + FloatToStrF(thisVar->values[ii], ffGeneral, 7, 0) + " ";
          else if(thisVar->ivalues != NULL)
            S = S + FloatToStrF(thisVar->ivalues[ii], ffGeneral, 7, 0) + " ";
          else
            S = S + "-0 ";

          if(ii%10 == 9) {
            StateList->Add(S);
            S = "";
          }
        }
      else
        for(int ll = 0; ll < thisVar->lay; ll++) {
          for(int ii = 0; ii < thisVar->dim; ii++) {
            if(thisVar->layvalues != NULL)
              S = S + FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else if(thisVar->ivalues != NULL)
              S = S + FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 4, 0) + " ";
            else
              S = S + "-0 ";

            if(ii%10 == 9) {
              StateList->Add(S);
              S = "";
            }
          }
          if(!S.IsEmpty()) StateList->Add(S);
          S = "";
        }
      if(!S.IsEmpty()) StateList->Add(S);
      StateList->Add("######");
    }
  }
  if(MainLoop)
    StateList->SaveToFile(SaveDialogPrj->InitialDir + "\\" + "ControlStateFile.tmp1");
  else
    StateList->SaveToFile(SaveDialogPrj->InitialDir + "\\" + "ControlStateFile.tmp2");

  delete StateList;
}
//---------------------------------------------------------------------------

void __fastcall TMain::StatSaveClick(TObject *Sender)
{
  if(SaveDialogState->FileName.IsEmpty())
    StatSaveStateAsClick(Sender);
  else
     SaveStateFlag = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::StatOpenInitClick(TObject *Sender)
{

  OpenDialogState->Filter = "Initial State Files (*.int)|*.int";
  OpenDialogState->DefaultExt = "int";
  OpenDialogState->Title = "Open Initial State File";

  if(OpenDialogState->Execute()) {
    OpenDialogState->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogState->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
    if(OpenDialogState->InitialDir.IsEmpty())
      OpenDialogState->InitialDir = GetCurrentDir();

    TMenuItem *ObsItem, *NewItem;
    ObsItem = MainMenu1->Items->Items[5];

    NewItem = new TMenuItem(ObsItem);
    NewItem->Caption = OpenDialogState->FileName;

    NewItem->OnClick = StateFileClose;
    ObsItem->Insert(ObsItem->Count, NewItem);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ReadStateFile(TObject *Sender, bool & GoodRun){

  MapPar::iterator itVar;
  ClassVar *thisVar;

  ifstream DataFile;
  char module[80], name[80];
  string S, Descrip, Line;
    DataFile.open(OpenDialogState->FileName.c_str());
    if(!DataFile) {
      Application->MessageBox(String("cannot open StateFile '" + OpenDialogState->FileName + "'").c_str(), "File Error", MB_OK);
      GoodRun = false;
      return;
    }

    String Message = "State file: " + OpenDialogState->FileName;
    LogMessage(Message.c_str());

    getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "TIME:"
    Word D[3];
    DataFile >> D[0] >> D[1] >> D[2];
    double DT = EncodeDate(D[0], D[1], D[2]);
    if(DT != floor(DateTimePicker1->Date)) {
      Application->MessageBox("State File and Run start times are not equal",
                              "File Error", MB_OK);
      GoodRun = false;
      return;
    }

    getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "Dimension:"
    long filehru, filelay;
    DataFile >> filehru >> filelay;
    if(filehru != Global::nhru || filelay != Global::nlay ){
      Application->MessageBox("State File and Model #HRU's or #LAY's are not equal",
                              "File Error", MB_OK);
      GoodRun = false;
      return;
    }

    DataFile.ignore(80, '#');
    getline(DataFile, Line);

    while(!DataFile.eof()) {
      DataFile >> module >> name;
      if(DataFile.fail()) break;

      DataFile.ignore();

      long exist = Global::OurModulesList->IndexOf(module);
      ClassModule*  mod;
      if(exist > -1)
        mod = (ClassModule*) Global::OurModulesList->Objects[exist];
      else {
        Application->MessageBox((String("State File module ") + module).c_str(),
                                "Unknown module", MB_OK);
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
        continue;
      }

      S = string(module) + ' ' + string(name);
      thisVar = ClassVarFind(S);

      if(!thisVar)
        thisVar = ClassVarFind("#" + S);  // could be local variable

      if(!thisVar && mod->isGroup){
        string::size_type idx = S.find('@');
        if(idx == -1){
      string A;
      GroupEnding(A, mod->GroupCnt);
          S += A;
          thisVar = ClassVarFind(S);
        }
      }
       if(thisVar) {
        if(thisVar->lay == 0){
          for(int ii = 0; ii < thisVar->dim; ii++)
            if(thisVar->values != NULL)
              DataFile >> thisVar->values[ii];
            else if(thisVar->ivalues != NULL)
              DataFile >> thisVar->ivalues[ii];
        }
        else {
          for(int ll = 0; ll < thisVar->lay; ll++)
            for(int ii = 0; ii < thisVar->dim; ii++)
              if(thisVar->layvalues != NULL)
                DataFile >> thisVar->layvalues[ll][ii];
              else  if(thisVar->ivalues != NULL)
                DataFile >> thisVar->ilayvalues[ll][ii];
        }
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }
      else {
        Application->MessageBox((String("State File variable ") + S.c_str()).c_str(),
                                "Unknown variable", MB_OK);
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }
    }
} // end of ReadStateFile
//---------------------------------------------------------------------------

void __fastcall TMain::ResetLoopList(TObject *Sender){ // writes to "CRHM_loop_output" and cleans up

  if(LoopList == NULL)
    return;

  ClassPar *thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  String FileName = "CRHM_loop_output";
  if(ID > 0)
    FileName += String("_") + ID;

  LoopList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".txt");

  delete LoopList;
  LoopList = NULL;
}
void __fastcall TMain::ControlReadState(TObject *Sender, bool MainLoop, ClassPar * VarPar){

  MapPar::iterator itVar;
  ClassVar *thisVar;

  String Sy;
  String Sx;
  bool first = true;
  bool Wild = false;

  if(VarPar && !VarPar->Strings->Strings[0].IsEmpty()) // first parameter determines the type
    Wild = VarPar->Strings->Strings[0].Pos("@") == 0;

  ifstream DataFile;

  char module[80], name[80];
  string S, Descrip, Line;
    if(MainLoop)
      DataFile.open(String(OpenDialogPrj->InitialDir + "\\" + "ControlStateFile.tmp1").c_str());
    else
      DataFile.open(String(OpenDialogPrj->InitialDir + "\\" + "ControlStateFile.tmp2").c_str());

    getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "TIME:"
    Word D[3];
    DataFile >> D[0] >> D[1] >> D[2];

    DataFile.ignore(180, '#'); // not working?
    getline(DataFile, Line); // reads "#####"
    getline(DataFile, Line); // read "DTindx:"
    DataFile >> Global::DTindx;

    DataFile.ignore(180, '#'); // not working?
    getline(DataFile, Line); // reads "#####"
    getline(DataFile, Line); // read "CurrentModuleRun:"
    DataFile >> Global::CurrentModuleRun;

    getline(DataFile, Descrip);
    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    getline(DataFile, Line); // read "Dimension:"
    long filehru, filelay;
    DataFile >> filehru >> filelay;

    DataFile.ignore(180, '#');
    getline(DataFile, Line);

    while(!DataFile.eof()) {
      DataFile >> module >> name;
      if(DataFile.fail()) break;

      DataFile.ignore();

      long exist = Global::OurModulesList->IndexOf(module);
      ClassModule*  mod;
      if(exist > -1)
        mod = (ClassModule*) Global::OurModulesList->Objects[exist];
      else{
        if(MainLoop){ // assume otherwise OK
          Application->MessageBox((String("State File module ") + module).c_str(),
                                  "Unknown module", MB_OK);
          DataFile.ignore(180, '#');
          getline(DataFile, Line);
        }
        continue;
      }

      S = string(module) + ' ' + string(name);
      thisVar = ClassVarFind(S);

      if(!thisVar)
        thisVar = ClassVarFind("#" + S);  // could be local variable

      if(!thisVar && mod->isGroup){
        string::size_type idx = S.find('@');
        if(idx == -1){
      string A;
      GroupEnding(A, mod->GroupCnt);
          S += A;
          thisVar = ClassVarFind(S);
        }
      }

      String namebasic = name;
      if(Wild){ // if Wild reduce parameter to root
        int Idx = namebasic.Pos("@");
        if(Idx)
          namebasic = namebasic.SubString(1, Idx-1);
      }

      if(thisVar) {

        if(VarPar && VarPar->Strings->IndexOf(namebasic) > -1){
          if(LoopList == NULL){
            LoopList = new TStringList;
            Sx = Global::DTnow.DateString();
            LoopList->Add(Sx);
          }
          if(first){
            Sx = "loop " + IntToStr(Global::LoopCnt - Global::LoopCntDown + 1) + "\t" + name;
            first = false;
          }
          else
            Sx += ("\t" + String(name));

// write data

          Sy ="";
          if(thisVar->lay == 0){
            for(int ii = 0; ii < thisVar->dim; ii++)
              if(thisVar->values != NULL){
                Sy += FloatToStrF(thisVar->values[ii], ffGeneral, 4, 0) + " ";
              }
              else if(thisVar->ivalues != NULL){
                Sy += FloatToStrF(thisVar->ivalues[ii], ffFixed, 0, 0) + " ";
              }
          }
          else {
            for(int ll = 0; ll < thisVar->lay; ll++)
              for(int ii = 0; ii < thisVar->dim; ii++)
                if(thisVar->layvalues != NULL){
                  Sy += FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
                }
                else  if(thisVar->ivalues != NULL){
                  Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 0, 0) + " ";
                }
          }

          Sx = Sx + "\t" + Sy;
        }
        else {
          if(thisVar->lay == 0){
            for(int ii = 0; ii < thisVar->dim; ii++)
              if(thisVar->values != NULL)
                DataFile >> thisVar->values[ii];
              else if(thisVar->ivalues != NULL)
                DataFile >> thisVar->ivalues[ii];
          }
          else {
            for(int ll = 0; ll < thisVar->lay; ll++)
              for(int ii = 0; ii < thisVar->dim; ii++)
                if(thisVar->layvalues != NULL)
                  DataFile >> thisVar->layvalues[ll][ii];
                else  if(thisVar->ivalues != NULL)
                  DataFile >> thisVar->ilayvalues[ll][ii];
          }
        }

        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }
      else {
        Application->MessageBox((String("State File variable ") + S.c_str()).c_str(),
                                "Unknown variable", MB_OK);
        DataFile.ignore(180, '#');
        getline(DataFile, Line);
      }

    } // while

    if(MainLoop){
      bool Wild2 = false;
      ClassPar * TraceVarPar = ParFind("basin TraceVars");

      if(TraceVarPar && !TraceVarPar->Strings->Strings[0].IsEmpty()) // first parameter determines the type
        Wild2 = TraceVarPar->Strings->Strings[0].Pos("@") == 0;

      for(int ii = 0; ii < TraceVarPar->Strings->Count; ++ii){
        String Trimmed = TraceVarPar->Strings->Strings[ii].Trim();
        if(!Trimmed.IsEmpty()){
          int jj = ListBox1->Items->IndexOf(Trimmed);
          if(jj > -1){
            for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
                ClassVar * thisVar = VarFind(string(Global::OurModulesList->Strings[ii].c_str()) + ' ' + TraceVarPar->Strings->Strings[0].c_str());
                if(thisVar)
                  break;
            } // for

            thisVar = (ClassVar*) ListBox1->Items->Objects[jj];
            if(thisVar){
              Sx += ("\t" + String(Trimmed));
              Sy ="";
              if(thisVar->lay == 0){
                for(int ii = 0; ii < thisVar->dim; ii++)
                  if(thisVar->values != NULL){
                    Sy += FloatToStrF(thisVar->values[ii], ffGeneral, 4, 0) + " ";
                  }
                  else if(thisVar->ivalues != NULL){
                    Sy += FloatToStrF(thisVar->ivalues[ii], ffFixed, 0, 0) + " ";
                  }
              }
              else {
                for(int ll = 0; ll < thisVar->lay; ll++)
                  for(int ii = 0; ii < thisVar->dim; ii++)
                    if(thisVar->layvalues != NULL){
                      Sy += FloatToStrF(thisVar->layvalues[ll][ii], ffGeneral, 4, 0) + " ";
                    }
                    else  if(thisVar->ivalues != NULL){
                      Sy += FloatToStrF(thisVar->ilayvalues[ll][ii], ffGeneral, 0, 0) + " ";
                    }
              }

              Sx = Sx + "\t" + Sy;
            }
          } // if
        }
      }
    }

    if(!Sx.IsEmpty())
      LoopList->Add(Sx);
} // end of ControlReadState
//---------------------------------------------------------------------------

void __fastcall TMain::OnHint(TObject *Sender)
{
  StatusBar1->Panels->Items[0]->Text = Application->Hint;
  StatusBar1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMain::LogClick(TObject *Sender)
{
  LogForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain::ParametersClick(TObject *Sender)
{
  Parameter->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain::UpDownOBSIndxClick(TObject *Sender, TUDBtnType Button)
{
  LabelOBSIndx->Caption = LabelOBSIndx->Caption.SubString(1,4) + String(UpDownOBSIndx->Position);
  LabelOBSIndx->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMain::UpdateDim(CRHM::TDim Dim, long dim){

  switch(Dim) {
    case CRHM::NHRU :
      Global::nhru = dim;
      Global::maxhru = dim;
      UpDownHRUIndx->Max = Global::maxhru;
      UpDownHRUIndx->Position = 1;
      LabelHRUIndx->Caption = "HRU 1";
      LabelHRUIndx->Refresh();
      break;
    case CRHM::NOBS :
      Global::nobs = dim;
      Global::maxobs = dim;
      UpDownOBSIndx->Max = Global::maxobs;
      UpDownOBSIndx->Position = 1;
      LabelOBSIndx->Caption = "OBS 1";
      LabelOBSIndx->Refresh();
      break;
    case CRHM::NLAY :
      Global::nlay = dim;
      Global::maxlay = dim;
      break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::HTMLhelp1Click(TObject *Sender) {
  String Name = ApplicationDir + "crhm.chm";
  FindFileName(Name);
 HtmlHelp(0, Name.c_str(), HH_HELP_CONTEXT, 1000);
}
//---------------------------------------------------------------------------

void __fastcall TMain::PrjAutoRunClick(TObject *Sender) {
  if(PrjAutoRun->Checked)
    PrjAutoRun->Checked = false;
  else
    PrjAutoRun->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::RemoveSharedParams(void){ // pseudo shared parameters

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::DeclRootList->Clear(); // used by AKA to stop looping

  Global::BuildFlag = CRHM::BUILD; // default value

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii)
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();


  Global::BuildFlag = CRHM::DECL; // model loaded

  ClassPar *thisPar;
  MapPar::iterator itPar;
  long count;
// restore original module parameters from pseudo Shared parameters if they do not already exist

  itPar = Global::SharedMapPars.begin();
  while (itPar !=  Global::SharedMapPars.end()) {
    thisPar = (*itPar).second;
    count = ClassParFindParBld(thisPar);
    Global::MapPars.erase("Shared " + thisPar->param);
    delete thisPar; // parameter no longer needed
    ++itPar;
  }
  Global::SharedMapPars.clear();
}
//---------------------------------------------------------------------------

void __fastcall TMain::SetSharedParams(ClassPar *basinPar){

// copy basin parameter to all module parameters

  ClassPar *thisPar;
  MapPar::iterator itPar;

  for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
    thisPar = (*itPar).second;
    if(basinPar == thisPar) // skip itself
      continue;
    if(thisPar->param == basinPar->param && thisPar->dim == basinPar->dim)
      thisPar->Change(*basinPar);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::SqueezeParams(TObject *Sender){

  paras MapInfo; // holds all parameters - used for processing
  ClassPar *thisPar, *thisPar2;

// make multimap: keyed by parameter name holding pointer to parameter

  MapPar::iterator itPar; // iterator for Global::MapPars
  itPar = Global::MapPars.begin();
  while (itPar !=  Global::MapPars.end()) {
    thisPar = (*itPar).second;
    string S = ((*itPar).second)->param;
    Pairinfo Item = Pairinfo(S, Pinfo(new Classinfo(thisPar)));
    MapInfo.insert(Item);
    ++itPar;
  } // while

  paras::iterator itPar2, itPar3, itPar4;
  itPar2 = MapInfo.begin();
  pair<paras::iterator, paras::iterator> range;
  GrpParas Matched; // working matched parametrs multimap
  string Key; // key for eventual shared parameters
  MapPar MapParsNew; // holds final processed parameters

// process multimap by parameter name

  while (itPar2 !=  MapInfo.end()) {
    string S = (*itPar2).first;
    long thiscnt = MapInfo.count(S.c_str()); // # of occurrences of string S

// if duplicate parameter name from other module

    if(thiscnt > 1) {
      range = MapInfo.equal_range(S.c_str());
      long greatestCnt = 0;
      bool first = true;

      ClassPar *SharedPar = NULL; // set if Simple actual Basin parameter

// proceed through duplicate list

      for(itPar3 = range.first; itPar3 != range.second; itPar3++) {
        Classinfo *info3 = ((*itPar3).second).get();

        if(info3->rootinfo == NULL)
          info3->rootinfo = info3;

        thisPar = info3->thisPar;

        range.first++;

        if(info3->matched) // handled by earlier pass
          continue;

        PairPar Item = PairPar(thisPar->module, thisPar);
        Matched.insert(Item);

// compare with following duplicate entries

        for(itPar4 = range.first; itPar4 != range.second; itPar4++) {
          Classinfo *info4 = ((*itPar4).second).get();

          if(info4->matched) // skip if already matched
            continue;

          thisPar2 = info4->thisPar;

// check for duplicate values
          bool match = thisPar->Same(*thisPar2) && !thisPar->Inhibit_share;

// if same values indicate could be merged

          if(match) {
            PairPar Item = PairPar(thisPar->module, thisPar2);
            Matched.insert(Item);
            info4->matched = true;
            thisPar2->Identical = thisPar; // used when reading observations lapse rate and elev
            if(++info3->rootinfo->cnt > greatestCnt){
              greatestCnt = info3->rootinfo->cnt;
              Key = info3->rootinfo->thisPar->module;
            } // update Key
          } // if(match)

        } // for(compare successively with first in range
      } // for(range of S)

      GrpParas::iterator itPar5;
      if(Matched.count(Key) > 1){
        pair<GrpParas::iterator, GrpParas::iterator> range2;
        range2 = Matched.equal_range(Key);
          bool first = true;
          for(itPar5 = range2.first; itPar5 != range2.second; itPar5++) {
            thisPar = (*itPar5).second;

// save module as shared parameters in MapPars and SharedMapPars

            if(first){
              thisPar->module = "Shared";
              PairPar Item = PairPar("Shared " + thisPar->param, thisPar);
              MapParsNew.insert(Item);
              Global::SharedMapPars.insert(Item);
              first = false;
            } // first
            else  // remove module parameters so as Shared parameters visible
              delete thisPar;
            (*itPar5).second = NULL; // Indicate has been handled
        } // for(range of S)
      } // if(greatestCnt > 0)

      for(itPar5 = Matched.begin(); itPar5 != Matched.end(); itPar5++) {
        thisPar = (*itPar5).second;
        if(!thisPar) // already handled
          continue;
        PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
        MapParsNew.insert(Item);
      }
      Matched.clear();
    } // if(thiscnt > 1)
    else{
      Classinfo *info = ((*itPar2).second).get();
      thisPar = info->thisPar;
      PairPar Item = PairPar(thisPar->module + ' ' + thisPar->param, thisPar);
      MapParsNew.insert(Item);
    }
    MapInfo.erase(S.c_str());
    itPar2 = MapInfo.begin();
  } // while

  Global::MapPars.clear();
  Global::MapPars = MapParsNew;
} // end of SqueezeParams
//---------------------------------------------------------------------------

void __fastcall TMain::FormActivate(TObject *Sender){

#ifdef CRHM_DLL
  #ifdef NO_MODULES
    AboutBox->Label2->Caption = String("Version: CRHM_DLL_NONE ") + CurrentVersion;
  #else CRHM_2
    AboutBox->Label2->Caption = String("Version: CRHM_DLL ") + CurrentVersion;
  #endif
#elif defined CRHM_2
  AboutBox->Label2->Caption = String("Version: CRHM ") + CurrentVersion;
#elif defined QUINTON
  AboutBox->Label2->Caption = String("Version: CRHM_QUINTON ") + CurrentVersion;
#else
  AboutBox->Label2->Caption = String("Version: CRHM ") + CurrentVersion;
#endif

  Global::crhmLog = LogForm->Handle;

  for(int pp = 0; pp < ParamCount(); ++pp) {
    String FileS = ParamStr(pp+1);
    if(FileExistsSp(FileS)) {
      if(LowerCase(ExtractFileExt(FileS)) == ".prj") {

        CommandLine = true;  // handle autorun differently

        OpenDialogPrj->FileName = FileS;
        OpenDialogPrj->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogPrj->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        if(OpenDialogPrj->InitialDir.IsEmpty())
          OpenDialogPrj->InitialDir = GetCurrentDir();

        SetCurrentDir(OpenDialogPrj->InitialDir);
        OpenDialogObs->InitialDir = OpenDialogPrj->InitialDir;

        FileDefaults(Sender);
        DoPrjOpen(Sender);
      }
      else if(LowerCase(ExtractFileExt(FileS)) == ".obs") {
        TDateTime Dt = TDateTime::CurrentDateTime();
        Chart->Title->Text->Clear();
        Chart->Title->Text->Add("Current Date: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt));

        OpenDialogObs->FileName = FileS;
        String path = ExtractFilePath(AnsiReplaceStr(OpenDialogObs->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        if(path.IsEmpty()){
          path = GetCurrentDir();
          FileS = path + "\\" + FileS;
        }
        OpenDialogObs->InitialDir = path;
        OpenObsFile(Sender, FileS);

        int iFileHandle  = FileOpen(FileS, fmOpenRead);
        int T = FileGetDate(iFileHandle);
        ProjectFileDate = FileDateToDateTime(T);
        char Buf[121];
        FileRead(iFileHandle, Buf, 120);
        String C(Buf);
        int n = C.Pos("\r");
        C.SetLength(n-1);
        FileClose(iFileHandle);
        String SS = ProjectFileDate.DateString() + FormatDateTime(" hh:mm", ProjectFileDate);

        Chart->SubTitle->Text->Clear();
        Chart->SubTitle->Text->Add(FileS + " Last modified: " + SS);
        Chart->SubTitle->Text->Add("Description: " + C);
      }
      else if(LowerCase(ExtractFileExt(FileS)) == ".par") {
        if(!CommandLine) // cannot change parameters unless project loaded
          continue;

        ifstream DataFile;
        int c, Cols;
        string ss;

        bool TooFewHRUs = false;
        string module, param, Descrip, Line, S, s;
        ClassPar *thisPar;

        OpenDialogPar->FileName = FileS;
        String path = ExtractFilePath(AnsiReplaceStr(OpenDialogPar->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        if(path.IsEmpty()){
          path = GetCurrentDir();
          FileS = path + "\\" + FileS;
        }
        OpenDialogPar->InitialDir = path;

        DataFile.open(OpenDialogPar->FileName.c_str());
        if(!DataFile) {
          Application->MessageBox("cannot open file", "File Error", MB_OK);
          return;
        }

        getline(DataFile, Descrip);
        DataFile.ignore(80, '#');
        getline(DataFile, Line);

        RemoveSharedParams(); // change shared parameters to module parameters

        while(!DataFile.eof()) {
          DataFile.clear();

          DataFile >> module;
          if(module[1] == '#') break;
          DataFile  >> param;
          if(DataFile.eof()) return; // final exit

          DataFile.ignore(80, '\n'); // need for character input, why?
          S = "";

          do {
            getline(DataFile, ss);
            S += ss + ' ';
            while(c = DataFile.peek(), iscntrl(c) || isspace(c))
              DataFile.get();

          } while(c = DataFile.peek(), !isalpha(c) && c != '#' && !DataFile.eof());

          string Sc = S; // use copy
          string::iterator pos; // first handle single quotes
          bool inField = false;

          for(pos = Sc.begin(); pos != Sc.end(); ++pos){
            if(*pos == '\'')
              inField = !inField;
            if(inField && *pos == ' ')
              *pos = '_';
          }

          istringstream instr; // count columns
          instr.clear();
          instr.str(Sc);
          Cols = 0;
          for (;;) {
            instr >> s;
          if(instr.fail()) break;
            ++Cols; // # of HRU's in Basin
          }

          if(module == "Shared") {
// write shared parameters to module parameters
// all parameter values are set to shared values.  If re-defined in a module will be changed.
            MapPar::iterator itPar;
            for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
              thisPar = (*itPar).second;
              if(thisPar->param == string(param)){
                if(thisPar->dim == Cols/thisPar->lay) // find module parameter for template thisPar->varType == CRHM::Int || thisPar->varType == CRHM::Float ||
                  break;
                else if(thisPar->varType == CRHM::Txt && thisPar->dimen < CRHM::NHRU) // text can have variable length
                  break;
                else { // Added to handle 2D parameters
                  if(thisPar->param == string(param) && (thisPar->dim == Cols/thisPar->dim))
                    break;
                  else
                    thisPar = NULL;
                }
              }
            }
          }
          else
            thisPar = ClassParFind(module, param); // find module parameter for template

          if(thisPar) {
            ClassPar *newPar = new ClassPar(*thisPar);
            newPar->module = module; // set module name
            if(thisPar->varType == CRHM::Txt) {
              newPar->Strings->DelimitedText = S.c_str();
            }
            else {
              istringstream instr; // count columns
              instr.clear();
              instr.str(S);
              for(int jj = 0; jj<thisPar->lay; jj++) {
                for(int ii = 0; ii < newPar->dim; ii++) {

                  if(newPar->varType == CRHM::Float)
                    instr >> newPar->layvalues[jj][ii];
                  else if(newPar->varType == CRHM::Int) {
                    float x;
                    instr >> x;
                    newPar->ilayvalues[jj][ii] = x;
                  }
                }

                if(newPar->dim > Cols) {
                  if(!TooFewHRUs) {
                    Application->MessageBox("Too few HRUs defined in the Project file",
                                   "parameters not complete", MB_OK);
                    TooFewHRUs = true;
                  }

                  for(int ii = Cols; ii < newPar->dim; ii++)
                    if(newPar->varType == CRHM::Float)
                      newPar->layvalues[jj][ii] = newPar->layvalues[jj][ii-1];
                    else
                      newPar->ilayvalues[jj][ii] = newPar->ilayvalues[jj][ii-1];
                }
              }
            }

            if(module == "Shared") {
              SetSharedParams(newPar); // copy template parameter to basin module
              delete newPar;
            }
            else
              ClassParSet(newPar);  // can delete newPar!
          }
          else {
            CRHMException Except("Unknown Module Parameter: " + string(module) + " -> "+ string(param) +
              " in " + string(OpenDialogPrj->FileName.c_str()), ERR);
            Application->MessageBox(Except.Message.c_str(), "Unknown Parameter in project file", MB_OK);
            LogError(Except);

            while(c = DataFile.peek(), !isalpha(c) && c != '#')
              DataFile.ignore(256, '\n');
          }
        } // while

        DataFile.close();

        SqueezeParams(Sender);  // converts identical parameters to shared parameters
      }
      else
          Application->MessageBox(String(FileS + " - file extension not 'prj', 'obs' or 'par'").c_str(), "Problem with File extension", MB_OK);
    }
    else
        Application->MessageBox(String(FileS + " - file does not exist").c_str(), "Problem with File", MB_OK);
  }  // for param

  if(PrjAutoRun->Checked) {
    if(!Global::OurModulesList->Count && ListBox4->Items->Count){
      if(Last1->Checked) LastRprtObs(Sender);
      if(All1->Checked) AllRprtObs(Sender);
      if(DebugScreen1->Checked) DebugScreen1Rprt(Sender);
      if(SummaryScreen1->Checked) SummaryScreen1Rprt(Sender);
    }
    else
      RunClick(Sender);

    Main->Refresh();
  }

  CommandLine = false;

  if(PrjAutoExit->Checked && !PlotControl->IntervalControl && (All1->Checked || Last1->Checked || DebugScreen1->Checked || SummaryScreen1->Checked)){
    Close();
  }

  biweekly1->Checked = true; // keep in step with UpdateForm
} // end of FormActivate
//---------------------------------------------------------------------------

void __fastcall TMain::WMMainUpdateDim(TMessage &Message){

  UpdateDim((CRHM::TDim) Message.WParam, (long) Message.LParam);
}
//---------------------------------------------------------------------------

void __fastcall TMain::WMMainUpdateStatus(TMessage &Message){

  String S = (*((String*) Message.WParam)).c_str();
  StatusBar1->Panels->Items[0]->Text = S;
  StatusBar1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TMain::WMMainUpdateDirty(TMessage &Message){

  dirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::PrjReportClick(TObject *Sender){

  MapPar::iterator itPar;
  MapDim::iterator itDim;
  ClassPar *thisPar;

  TStringList *SumList = new TStringList;

  SumList->Add(DescripPrj.c_str());
  SumList->Add("");

  TDateTime Dt = TDateTime::CurrentDateTime();
  SumList->Add("CURRENT TIME: " + Dt.DateString() +  FormatDateTime(" hh:mm", Dt));
  SumList->Add("");

  SumList->Add("CRHM " + AboutBox->Label2->Caption);
  SumList->Add("");

  SumList->Add("PROJECT FILE NAME:");
  SumList->Add("");

  if((OpenDialogPrj->FileName.LowerCase()).Pos(".prj") && ProjectOpen && !dirty) {

    String S = ProjectFileDate.DateString() + FormatDateTime(" hh:mm", ProjectFileDate);
    SumList->Add(SaveDialogPrj->FileName + "  dated " + S);
  }
  else if (dirty)
    SumList->Add("WARNING: Project not saved");

  SumList->Add("");

  SumList->Add("DIMENSIONS:");
  SumList->Add(" ");
  SumList->Add(String("nhru " + String(Global::nhru)));
  SumList->Add(String("nlay " + String(Global::nlay)));
  SumList->Add(String("nobs " + String(Global::nobs)));
  SumList->Add(" ");

  if(!Global::MapAKA.empty()) {
    Mapstr2::iterator it;

    SumList->Add("AKAs:");
    SumList->Add(" ");

    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {
      string Var = (*it).first + ' ' + (*it).second;
      SumList->Add(Var.c_str());
    }
    SumList->Add(" ");
  }

  SumList->Add("OBSERVATIONS:");
  SumList->Add(" ");

    for(int ii = 0; ii < ObsFilesList->Count; ii++) {
      String S = ObsFilesList->Strings[ii];
      ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];

      TDateTime Dt1 = FileData->Dt1;
      if(FileData->Interval < 1.0)
        Dt1 += FileData->Interval; // *(1 + FileData->IndxMin);

      TDateTime Dt2 = FileData->Dt2;

      S +=  "         ( " + Dt1.DateString() +  FormatDateTime(" hh:mm", Dt1) + " - "
                + Dt2.DateString() +  FormatDateTime(" hh:mm", Dt2) + ", Interval = ";

      if(FileData->Times != NULL)
        S +=  "sparse data file )";
      else if(FileData->Interval < 1.0)
        S +=  FormatDateTime("hh:mm", (TDateTime) FileData->Interval) + " )";
      else
        S +=  "daily )";

      SumList->Add(S);
    }
  SumList->Add(" ");

  SumList->Add("DATES:");
  SumList->Add(" ");

  String S;
  S = DateTimePicker1->Date.FormatString("yyyy m d");
  if(ObsFilesList->Count == 0)
    S = S + " " + FloatToStrF(Global::Freq, ffGeneral, 0, 0);
  SumList->Add(S);
  S = DateTimePicker2->Date.FormatString("yyyy m d");
  SumList->Add(S);
  SumList->Add(" ");

#ifdef CRHM_DLL
  SumList->Add("DLLs:");
  SumList->Add(" ");
//  CompactDlls();
  for(int ii = 0; ii < OpenDLLs->Count; ii++) {
    String S = OpenDLLs->Strings[ii];
    SumList->Add(S);
  }
  SumList->Add(" ");
#endif

  SumList->Add("MODULES:");
  SumList->Add(" ");

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
    String S = Global::OurModulesList->Strings[ii];
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    if(thisModule->variation > 0){
      string AA("#0 ");
      AA[1] += log(thisModule->variation)/log(2) + 1;
      S = S + AA.c_str();
    }
    else
      S = S + " ";

    S = S + thisModule->DLLName;

    S = S + thisModule->Version;
    SumList->Add(S);
  }
  SumList->Add(" ");

  SumList->Add("PARAMETERS:");
  SumList->Add(" ");

  for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
    thisPar = (*itPar).second;

    String S = String(thisPar->module.c_str()) + " - " +
               String(thisPar->param.c_str());

    if(thisPar->varType != CRHM::Txt)
      S += " <" + FloatToStrF(thisPar->minVal, ffGeneral, 4, 0)+ " to " + FloatToStrF(thisPar->maxVal, ffGeneral, 4, 0) + ">";

    SumList->Add(S);

    for(int jj = 0; jj<thisPar->lay; jj++) {
      S = "";
      for(int ii = 0; ii < thisPar->dim; ii++) {
        if(thisPar->varType == CRHM::Float)
          S = S + FloatToStrF(thisPar->layvalues[jj][ii], ffGeneral, 4, 0) + " ";
        else if(thisPar->varType == CRHM::Int)
          S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], ffGeneral, 8, 0) + " ";
        else if(thisPar->varType == CRHM::Txt)
          if(thisPar->Strings->Count > ii)
            S = S + "'" + thisPar->Strings->Strings[ii] + "' ";

        if(ii%10 == 9) {
          SumList->Add(S);
          S = "";
        }
      }
      if(!S.IsEmpty()) {SumList->Add(S); S = "";}
    }
  if(!S.IsEmpty()) SumList->Add(S);
  SumList->Add(" ");
  }

  SumList->Add(" ");

  SumList->Add("INITIAL STATE:");
  SumList->Add(" ");

  TMenuItem *StateItem;
  StateItem = MainMenu1->Items->Items[5];

  if(StateItem->Count > 5){ // State files open
    for(int ii = 5; ii < StateItem->Count; ++ii)
      SumList->Add(StateItem->Items[ii]->Caption);
  }

  SumList->Add(" ");

  SumList->Add("FINAL STATE:");
  SumList->Add(" ");

  if(SaveStateFlag) {
    SumList->Add(SaveDialogState->FileName);
  }

  SumList->Add(" ");

  Rprt->SummaryList = SumList;

  Rprt->ShowModal();

  Rprt->SummaryList = NULL;
  delete SumList;

  LogForm->ClearRunLogs();
} // end of PrjReportClick
//---------------------------------------------------------------------------

void __fastcall TMain::DLL1OpenClick(TObject *Sender)
{
  OpenDialogDLL->Filter = "DLL Files (*.dll)|*.dll";
  OpenDialogDLL->Title = "Open DLL File";
  OpenDialogDLL->DefaultExt = "dll";

  if(OpenDialogDLL->Execute()) {
    OpenDialogDLL->InitialDir = ExtractFilePath(AnsiReplaceStr(OpenDialogDLL->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
    if(OpenDialogDLL->InitialDir.IsEmpty())
      OpenDialogDLL->InitialDir = GetCurrentDir();

    Global::PendingDLLModuleList->Clear(); // clear
    OpenDLLFile(OpenDialogDLL->FileName);

    dirty = true;
    UpdateOurModules();
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::DllFileCloseAux(String FileName)
{
  TMenuItem *DllItem, *DllItem2;
  DllItem = MainMenu1->Items->Items[3];
  for(int ii = DllItem->Count-1; ii > 3; --ii) // find entry
    if(FileName == DllItem->Items[ii]->Caption)
      break;

  int Pos  = OpenDLLs->IndexOf(FileName);

  DllItem = MainMenu1->Items->Items[3];
  DllItem->Delete(Pos+4);  // delete submenu

  HINSTANCE Dll = (HINSTANCE) OpenDLLs->Objects[Pos];

  DllDelete(FileName);           // remove modules
  OpenDLLs->Delete(Pos);  // delete entry in list

  FreeLibrary(Dll); // must come last

  if((int) Global::OurHelpList->Objects[Pos+InitModCnt]){ // displayed
    DllItem = MainMenu1->Items->Items[MainMenu1->Items->Count-1];
    DllItem->Delete(Pos+2+InitModCnt);  // delete submenu
  }

  Global::OurHelpList->Delete(Pos+InitModCnt);  // delete help file from list
}
//---------------------------------------------------------------------------

void __fastcall TMain::DllFileClose(TObject *Sender)
{
  TMenuItem *DllItem;

  TMenuItem * thisMenu = (TMenuItem *) Sender;

  String S = thisMenu->Caption;

  if(!DllinUse(S)) {

    int Pos  = OpenDLLs->IndexOf(S);

    DllItem = MainMenu1->Items->Items[3];
    DllItem->Delete(Pos+4);  // delete submenu

    HINSTANCE Dll = (HINSTANCE) OpenDLLs->Objects[Pos];

    DllDelete(S);           // remove modules
    OpenDLLs->Delete(Pos);  // delete entry in list

    FreeLibrary(Dll); // must come last

    if((int) Global::OurHelpList->Objects[Pos+InitModCnt]){ // displayed
      DllItem = MainMenu1->Items->Items[MainMenu1->Items->Count-1];
      DllItem->Delete(Pos+2+InitModCnt);  // delete submenu
    }

    Global::OurHelpList->Delete(Pos+InitModCnt);  // delete help file from list
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::DLL1CloseALLClick(TObject *Sender)
{
  TMenuItem *DllItem, *DllItem2;
  DllItem = MainMenu1->Items->Items[3];
  for(int ii = DllItem->Count-1; ii > 3; --ii) {
    String S = DllItem->Items[ii]->Caption;
    if(!DllinUse(S)) {
      int Pos  = OpenDLLs->IndexOf(S);

      HINSTANCE Dll = (HINSTANCE) OpenDLLs->Objects[Pos];

      DllItem->Delete(ii);
      DllDelete(S);           // remove modules
      OpenDLLs->Delete(Pos);  // delete entry in list

      FreeLibrary(Dll);  // must come last

      if((int) Global::OurHelpList->Objects[Pos+InitModCnt]){ // displayed
        DllItem2 = MainMenu1->Items->Items[MainMenu1->Items->Count-1];
        DllItem2->Delete(Pos+2+InitModCnt);  // delete submenu
      }

      Global::OurHelpList->Delete(Pos+InitModCnt);  // delete help file from list
    }
  }
}
//---------------------------------------------------------------------------

bool __fastcall TMain::DllinUse(String FileName)
{
  for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    if(thisModule->DLLName == FileName) {
      Application->MessageBox(("DLL in use " + FileName).c_str(), "Cannot close DLL File", MB_OK    );
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::CompactDlls(void)
{
  TMenuItem *DllItem;
  bool* UsedList = new bool [OpenDLLs->Count];
  for(int ii = 0; ii < OpenDLLs->Count; ii++) UsedList[ii] = false;

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    if(thisModule->DLLName.IsEmpty()) continue;
    if(thisModule->isGroup || thisModule->isStruct){
      list<ModulePtr> ::iterator iterM;
      iterM = ((ClassMacro *) thisModule)->Modules.begin();
      while(iterM != ((ClassMacro *) thisModule)->Modules.end()) {
	boost::weak_ptr<ClassModule> MP((*iterM));
	int jj = OpenDLLs->IndexOf((*iterM)->DLLName);
	if(jj >= 0) UsedList[jj] = true;
	++iterM;
      }
    }
    else{ // simple module
      int jj = OpenDLLs->IndexOf(thisModule->DLLName);
      if(jj >= 0) UsedList[jj] = true;
    }
  }

  for(int ii = OpenDLLs->Count-1; ii >= 0; --ii)
    if(!UsedList[ii]) {
      DllItem = MainMenu1->Items->Items[3];
      DllItem->Delete(ii+4);  // delete submenu

      HINSTANCE Dll = (HINSTANCE) OpenDLLs->Objects[ii];

      DllDelete(OpenDLLs->Strings[ii]);
      OpenDLLs->Delete(ii); // delete entry in list

      FreeLibrary(Dll); // must come last

      if((int) Global::OurHelpList->Objects[ii+1]){ // displayed
        DllItem = MainMenu1->Items->Items[MainMenu1->Items->Count-1];
        DllItem->Delete(ii+3);  // delete submenu
      }

      Global::OurHelpList->Delete(ii+1);  // delete help file from list
    }
  delete [] UsedList;
}
//---------------------------------------------------------------------------

bool __fastcall TMain::OpenDLLFile(String FileName)
{
  TStringList *DesiredModuleList;

  if(OpenDLLs->IndexOf(FileName) != -1){  // already open
    if(Application->MessageBox(String("Reload DLL \"" + FileName + "\" to change module selection?").c_str(),
                   "DLL already loaded!", MB_OKCANCEL) == IDOK)
      DllFileCloseAux(FileName);
    else
      return true;
  }

  if(Global::PendingDLLModuleList->Count > 0){ // Modules required by DLL project
    DesiredModuleList = new TStringList; // Have to save as it is loaded with all DLL modules
    DesiredModuleList->AddStrings(Global::PendingDLLModuleList);
  }
  else
    DesiredModuleList = NULL;

  HINSTANCE DLL = LoadLibrary(FileName.c_str());

  if (DLL) {

// Get the address of the function.
    LoadUserModules = (LoadModuleType *) GetProcAddress(DLL, "_MoveModulesToGlobal");
// Make sure we have the address then call the function.
    if (LoadUserModules) {

      LoadUserModules(FileName);
      if(DesiredModuleList != NULL){
        for(int ii = Global::PendingDLLModuleList->Count-1; ii >= 0; --ii){
          if(DesiredModuleList->IndexOf(Global::PendingDLLModuleList->Strings[ii]) == -1)
            Global::PendingDLLModuleList->Delete(ii);
        }
        delete DesiredModuleList;
        DesiredModuleList = NULL;
        ((ClassModule*) Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept(mrYesToAll);
      }
      else
        ((ClassModule*) Global::PendingDLLModuleList->Objects[0])->OurAdmin->Accept();

      OpenDLLs->AddObject(FileName, (TObject*) DLL);
      UpDateModelMenu();

      TMenuItem *DllItem, *NewItem;
      DllItem = MainMenu1->Items->Items[3];

      NewItem = new TMenuItem(DllItem);
      NewItem->Caption = FileName;

      NewItem->OnClick = DllFileClose;
      DllItem->Insert(DllItem->Count, NewItem);

      return true;
    }
    else {
      ShowMessage(SysErrorMessage(GetLastError()));
      FreeLibrary(DLL);  // must come last
    }
  }
  else {
      ShowMessage(SysErrorMessage(GetLastError()));
      ShowMessage("Unable to load the DLL");
  }
  return false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::DllDelete(String FileName)
{
  for(int ii = Global::AllModulesList->Count-1; ii >= 0; --ii) { // remove modules
    String ZZ = Global::AllModulesList->Strings[ii];
    ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[ii];
    if(thisModule->DLLName == FileName)
      Global::AllModulesList->Delete(ii);
  }

  for(int ii = Global::AllModelsList->Count-1; ii >= 0 ; --ii) { // remove models
    String Z = Global::AllModelsList->Strings[ii]; // used for testing

    int Index = (int) Global::AllModelsList->Objects[ii]; // Global::AllModelsList is sorted

    Administer *p = (Administer*) Global::ModelModulesList->Objects[Index];
    if(p->DLLName == FileName)
      Global::AllModelsList->Delete(ii);  // delete Model
  }

  UpDateModelMenu();
  dirty = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::UpDateModelMenu(void) {

  TMenuItem *ObsItem, *NewItem;

// Handle build menu

  ObsItem = MainMenu1->Items->Items[2];

  while(ObsItem->Count > 6)
        ObsItem->Delete(ObsItem->Count-1);

  for(int ii = 0; ii < Global::AllModelsList->Count; ii++) {

      NewItem = new TMenuItem(ObsItem);
      NewItem->Caption = Global::AllModelsList->Strings[ii];
      NewItem->OnClick = BldModelClick;
      NewItem->Tag = ii;

      ObsItem->Insert(ObsItem->Count, NewItem);
  }

// Handle help menu

  ObsItem = MainMenu1->Items->Items[MainMenu1->Items->Count-1];

  while(ObsItem->Count > 4)
        ObsItem->Delete(ObsItem->Count-3);

  for(int ii = 0; ii < Global::OurHelpList->Count; ii++) {
      if((int) Global::OurHelpList->Objects[ii]){

        NewItem = new TMenuItem(ObsItem);
        NewItem->Caption = Global::OurHelpList->Strings[ii];
        NewItem->OnClick = OpenHelp;

        NewItem->Tag = 0;  // if file does not exist - disable menu item

        if((InitModCnt >> ii) || OpenDLLs == NULL) { // DLL_NONE
          NewItem->Tag = 1;
        }
        else {
          String Fix = Global::OurHelpList->Strings[ii] + ".chm"; // clears warning
          if(FindFileName(Fix)) {
            NewItem->Tag = -(ii+1);
            NewItem->Hint = Global::OurHelpList->Strings[ii] + ".chm";
          }
        }

        NewItem->Enabled = NewItem->Tag;

        ObsItem->Insert(ObsItem->Count-2, NewItem);
      }
  }
  UpDateHelpMenu();
}
//---------------------------------------------------------------------------

void __fastcall TMain::UpDateHelpMenu(void) {

  TMenuItem *HelpItem, *NewItem;

// Handle help menu

  HelpItem = MainMenu1->Items->Items[MainMenu1->Items->Count-1];

  int NumDlls = 0;

#ifdef CRHM_DLL
  NumDlls = OpenDLLs->Count;
#endif

  while(HelpItem->Count > 4 + InitModCnt + NumDlls)
        HelpItem->Delete(HelpItem->Count-3);

  for(int ii = 0; ii < PrjObsHelp->Count; ii++) {

      if(PrjObsHelp->Strings[ii].IsEmpty()) continue;  // no project help file

      NewItem = new TMenuItem(HelpItem);
      NewItem->Caption = PrjObsHelp->Strings[ii];
      NewItem->OnClick = OpenHelp;
      NewItem->Tag = (int) PrjObsHelp->Objects[ii];

      HelpItem->Insert(HelpItem->Count-1, NewItem);

      if(ii == PrjObsHelp->Count-1 || ii == 0)
        HelpItem->InsertNewLineAfter(HelpItem->Items[HelpItem->Count-2]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::DeleteListBox3Click(TObject *Sender)
{
  TComponent *pComponent = PopupListBox3->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox3") {

      int StartCnt = ListBox3->Items->Count;
      for(int ii = StartCnt-1; ii >= 0; --ii) {

        if(ListBox3->Selected[ii]) {
          ListBox4RemoveFuncts(Sender, ListBox3->Items->Strings[ii]);

          if(SeriesCnt <= 0){
            ListBox3->Items->Delete(ii);
          }
          else {
            bool Found = false;
            for(int jj = 0; jj < SeriesCnt; jj++) {
              if(cdSeries[jj]->Title == ListBox3->Items->Strings[ii]) {

                Found = true;
                ClassVar* thisVar =  (ClassVar *) cdSeries[jj]->Tag;
                thisVar->TchrtOpt = cdSeries[jj]->VertAxis == aRightAxis;

                cdSeries[jj]->ParentChart = NULL;
                cdSeries[jj]->Clear();

                for(int kk = jj+1; kk < SeriesCnt; kk++)
                  cdSeries[kk-1] = cdSeries[kk];
                ListBox3->Items->Delete(ii);
                SeriesCnt--;
                break;
              }
            } // for

            if(!Found) ListBox3->Items->Delete(ii);
          }
        }
      } // for
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

void __fastcall TMain::NegateListBox3Click(TObject *Sender)
{
  TComponent *pComponent = PopupListBox3->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox3") {

      int StartCnt = ListBox3->Items->Count;
      for(int ii = StartCnt-1; ii >= 0; --ii) {

        if(ListBox3->Selected[ii]) {

          if(SeriesCnt <= 0) {
            Application->MessageBox("please run the model first", "Warning", MB_OK);
            return;
          }
          else {
            for(int Indx = 0; Indx < SeriesCnt; Indx++)
              if(cdSeries[Indx]->Title == ListBox3->Items->Strings[ii]) {
                long stop = cdSeries[Indx]->Count();
                for (int iii = 0; iii < stop; iii++)
                  cdSeries[Indx]->YValue[iii] = -1*cdSeries[Indx]->YValue[iii];
                break;
              }
          }
        }
      }
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

void __fastcall TMain::AbsListBox3Click(TObject *Sender)
{
  TComponent *pComponent = PopupListBox3->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox3") {

      int StartCnt = ListBox3->Items->Count;
      for(int ii = StartCnt-1; ii >= 0; --ii) {

        if(ListBox3->Selected[ii]) {

          if(SeriesCnt <= 0) {
            Application->MessageBox("please run the model first", "Warning", MB_OK);
            return;
          }
          else {
            for(int Indx = 0; Indx < SeriesCnt; Indx++)
              if(cdSeries[Indx]->Title == ListBox3->Items->Strings[ii]) {
                long stop = cdSeries[Indx]->Count();
                for (int iii = 0; iii < stop; iii++)
                  cdSeries[Indx]->YValue[iii] = fabs(cdSeries[Indx]->YValue[iii]);
                break;
              }
          }
        }
      }
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

  void __fastcall TMain::ListBox4RemoveFuncts(TObject *Sender, String Svar){

    for(long ii = 0; ii < ListBox4->Items->Count; ++ii){
      long Indx = ListBox4->Items->Strings[ii].Pos(Svar); // find functions of variable
      if(Indx > 0){
        TLineSeries *cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];
        if(cdSeries){
          cdSeries->ParentChart = NULL;
          cdSeries->Clear();
        }

        ListBox4->Items->Delete(ii);  // delete series
      }
    } // for
  }

//---------------------------------------------------------------------------

void __fastcall TMain::DeleteListBox4Click(TObject *Sender){

  TComponent *pComponent = PopupListBox4->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox4") {

      int StartCnt = ListBox4->Items->Count;
      for(long ii = StartCnt-1; ii >= 0; --ii) {

        if(ListBox4->Selected[ii]) {

          TLineSeries *cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];

          ClassVar* thisVar =  (ClassVar *) cdSeries->Tag;
          if(thisVar){ // if NULL means that cdSeries is Obs/Var function
            thisVar->TchrtOpt = cdSeries->VertAxis == aRightAxis;

            if(thisVar->FunKind > CRHM::FOBS){ // Original Observation - do not delete
              if(thisVar->FileData)
                delete thisVar->FileData;
              thisVar->FileData = NULL;
              delete thisVar;
            }
          }

          cdSeries->ParentChart = NULL;
          cdSeries->Clear();

          ListBox4->Items->Delete(ii);  // delete series
        }
      }
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

void __fastcall TMain::NegateListBox4Click(TObject *Sender)
{
  TComponent *pComponent = PopupListBox4->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox4") {

      int StartCnt = ListBox4->Items->Count;
      for(int ii = StartCnt-1; ii >= 0; --ii) {

        if(ListBox4->Selected[ii]) {

          TLineSeries *Series = (TLineSeries *) ListBox4->Items->Objects[ii];

          long stop = Series->Count();
          for (int iii = 0; iii < stop; iii++)
            Series->YValue[iii] = -1*Series->YValue[iii];
        }
      }
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddListBox1Click(TObject *Sender) {

  TComponent *pComponent = PopupListBox1->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1") {

      int StartCnt = ListBox1->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox1->Selected[ii]) {
          if(ListBox1->Items->Strings[ii][1] == ' ')
            continue;

          ClassVar *thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];

          if(thisVar->dimen == CRHM::BASIN && UpDownHRUIndx->Position > 1 ||
            UpDownHRUIndx->Position > thisVar->dim || !thisVar->values && !thisVar->ivalues)
            return;

          String S = BuildHru(ListBox1->Items->Strings[ii], UpDownHRUIndx->Position, thisVar->dimen);

          if(UpDownOBSIndx->Position > 0) {
            if(!thisVar->values && !thisVar->ivalues) return;
            if(thisVar->lay == 0) {
              UpDownOBSIndx->Position = 1;
              LabelOBSIndx->Caption = "LAY 1";
              UpDownOBSIndx->Refresh();
            }
            else
              S = BuildLay(S, UpDownOBSIndx->Position);
          }

          int indx = IndexOf(ListBox3, S);
          if(indx == -1) ListBox3->Items->AddObject(S, ListBox1->Items->Objects[ii]);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox1Click(TObject *Sender)
{
  if(LabelOBSIndx->Caption[1] != 'L') {
    UpDownOBSIndx->Max = Global::maxlay;
    UpDownOBSIndx->Position = 1;
    LabelOBSIndx->Caption = "LAY 1";
    LabelOBSIndx->Refresh();
  }

  long Showing = ListBox1->ItemIndex;

  if(Showing > -1) {
    if(ListBox1->Items->Strings[Showing][1] == ' '){
      LabelVar->Caption = "Module description";
      ClassModule* thisModule = (ClassModule*) ListBox1->Items->Objects[Showing];
      if(thisModule)
        StatusBar1->Panels->Items[2]->Text = thisModule->Description;
      else
        StatusBar1->Panels->Items[2]->Text = "";
      return;
    }

    LabelVar->Caption = "Variable help";
    ClassVar *thisVar =  (ClassVar *) ListBox1->Items->Objects[Showing];
    StatusBar1->Panels->Items[2]->Text = string(thisVar->help +"    units: " + thisVar->units).c_str();
    Chart->Axes->Items[2]->Title->Caption = thisVar->units.c_str();
    if(thisVar->lay <= 1) {
      UpDownOBSIndx->Position = 1;
      LabelOBSIndx->Caption = "LAY 1";
      UpDownOBSIndx->Position = 0;
      UpDownOBSIndx->Refresh();
    }
    else{
      if(thisVar->lay > UpDownOBSIndx->Max){
        UpDownOBSIndx->Max = thisVar->lay;
        if(UpDownOBSIndx->Position > thisVar->lay)
          UpDownOBSIndx->Position = 1;
        LabelOBSIndx->Caption = LabelOBSIndx->Caption.SubString(1,4) + String(UpDownOBSIndx->Position);
        LabelOBSIndx->Refresh();
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddListBox2Click(TObject *Sender) {

  TComponent *pComponent = PopupListBox2->PopupComponent;
  if(pComponent) {
    if((pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2")
      || (pComponent->ClassNameIs("TLabel") && pComponent->Name == "LabelFunct")) {

      int StartCnt = ListBox2->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox2->Selected[ii]) {

          int Indx = UpDownOBSIndx->Position;
          int IndxMax = ((ClassVar *) ListBox2->Items->Objects[ii])->cnt;
          if(Indx > IndxMax) Indx = IndxMax;

          String S = ListBox2->Items->Strings[ii] +
                   "(" + String(Indx) + ")" + Sstrings[Funct];

          int iii = IndexOf(ListBox4, S);

          if(iii == -1) {
            TLineSeries *cdSeries;

            if(((ClassVar *) ListBox2->Items->Objects[ii])->FileData->Times == NULL)
              cdSeries = new TLineSeries(this);
            else
              cdSeries = (TLineSeries *) new TPointSeries(this);

            ClassVar* thisVar = (ClassVar*) ListBox2->Items->Objects[ii];
            cdSeries->Tag = (int) thisVar; // ClassVar*
            cdSeries->VertAxis = (TVertAxis) thisVar->TchrtOpt;

            cdSeries->XValues->DateTime = TRUE;
            CurrentColor = colours[ii % ncolours];
            cdSeries->Color = CurrentColor;
            cdSeries->ParentChart = Chart;
            cdSeries->Title = S;

            ListBox4->Items->AddObject(S, (TObject *) cdSeries);
            AddObsPlot(Sender, (ClassVar *) ListBox2->Items->Objects[ii], cdSeries, S, Funct);
          } // if
        }  // if
      } //for
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox2Click(TObject *Sender) {

  if(LabelOBSIndx->Caption[1] != 'O') {
    UpDownOBSIndx->Max = Global::maxobs;
    UpDownOBSIndx->Position = 1;
    LabelOBSIndx->Caption = "OBS 1";
    LabelOBSIndx->Refresh();
  }

  long Showing = ListBox2->ItemIndex;

  if(Showing > -1) {
    ClassVar *thisVar =  (ClassVar *) ListBox2->Items->Objects[Showing];
    StatusBar1->Panels->Items[1]->Text = string(thisVar->help +
         "  units: " +  thisVar->units +
         "  File: " + thisVar->FileData->DataFileName).c_str();

    Chart->Axes->Items[2]->Title->Caption = thisVar->units.c_str();
    LabelFunct->Caption = FStrings[Funct];
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::FunctionListBox2Click(TObject *Sender){

  CoolBar1->Show(); // display CoolBar
}
//---------------------------------------------------------------------------

void __fastcall TMain::LabelFunctClick(TObject *Sender){

  if(Funct >= CRHM::DLTA)
    Funct = CRHM::FOBS;
  else
    Funct = (TFun) (Funct + 1);

  LabelFunct->Caption = FStrings[Funct];

}
//---------------------------------------------------------------------------

void __fastcall TMain::FormClick(TObject *Sender)
{
  if(Global::BuildFlag != CRHM::RUN)
    return;

  PlotControl->ShowModal();

  if(!PlotControl->IntervalControl){ // terminate run
    RefreshTime = 0;
    SetCaptureControl(Main);
  }
}
//---------------------------------------------------------------------------

  void __fastcall TMain::OpenHelp(TObject *Sender){

  TMenuItem *thisMenu = (TMenuItem *) Sender;

  String Name;

  String as = thisMenu->Caption;
  if(as.Pos(".") > 0) as = as.SubString(1, as.Length()-4);
  as += ".chm";

  switch (thisMenu->Tag) {
    case 1: // CRHM help in project directory or application directory
    case 2: // redundant
      Name = ProjectDir + as;
      if(!FileExistsSp(Name))  // problem ProjectDir may have changed since Help menu set up
        Name = ApplicationDir + as;
      break;
    default: // observation or Dll file index.
      if(thisMenu->Tag > 3) {
      // Handle observation menu

        TMenuItem *ObsItem = MainMenu1->Items->Items[1];
        int ii = thisMenu->Tag;
        String path = ObsItem->Items[ii]->Caption;
        path = path.Delete(1, path.Pos(" "));
        path = ExtractFilePath(AnsiReplaceStr(path, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        Name =  path + as;
      }
      else {
      // Handle DLL file
        int ii = labs(thisMenu->Tag)-1;
        String path = OpenDLLs->Strings[ii-InitModCnt];
        path = ExtractFilePath(AnsiReplaceStr(path, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
        Name = path + as;
      }
      break;
  }

  FindFileName(Name);
  HtmlHelp(0, Name.c_str(), HH_DISPLAY_TOPIC, NULL); // HH_DISPLAY_TOPIC HH_HELP_CONTEXT
} // end of OpenHelp

//---------------------------------------------------------------------------
  void __fastcall TMain::DoObsStatus(TObject *Sender, bool &First){

  if(First) {
    for(int ii = 0; ii < ObsFilesList->Count; ii++) {
      ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];
      FileData->TimeIndx = 0;
    }
    First = false;
  }

  for(int ii = 0; ii < ObsFilesList->Count; ii++) {
    ClassData * FileData = (ClassData *) ObsFilesList->Objects[ii];

    FileData->GoodInterval = true;

    if(ii == 0) {  // first observation file always good
      FileData->GoodDay = true;
      continue;
    }

    FileData->GoodInterval = true;

    if(FileData->Times != NULL) { // sparse data
        FileData->GoodDay = false;

      while (FileData->Times[FileData->TimeIndx] < Global::DTnow
        && FileData->TimeIndx < FileData->Lines-1)
        ++FileData->TimeIndx;

      if(FileData->Times[FileData->TimeIndx] != Global::DTnow)
        FileData->GoodInterval = false;
    }
    else { // normal observation file

      long Index = Global::DTindx*FileData->Freq/Global::Freq;

      if(Index < FileData->IndxMin || Index > FileData->IndxMax){
        FileData->GoodInterval = false;
        FileData->GoodDay = false;
        continue;
      }

      if(Index%FileData->Freq == 0){ // beginning of day
        FileData->GoodDay = true;
        if(FileData->Freq <= 1) continue; // handle daily data (only one observation)
        Index+= Global::Freq -1; // check if full day available
        if(Index < FileData->IndxMin || Index > FileData->IndxMax){
          FileData->GoodDay = false;
          continue;
        }
        continue;
      }
      else { // remainder of day
        if(FileData->GoodDay)
          FileData->GoodInterval = true;
        else if(Index < FileData->IndxMin || Index > FileData->IndxMax)
// day at end of file missing data
          FileData->GoodInterval = false;
      }
    }
  } // for
}
//---------------------------------------------------------------------------

void __fastcall TMain::HRUsAddListBox1Click(TObject *Sender) {

  TComponent *pComponent = PopupListBox1->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1") {

      int StartCnt = ListBox1->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox1->Selected[ii]) {
          if(ListBox1->Items->Strings[ii][1] == ' ')
            continue;

          for(int hh = UpDownHRUIndx->Position; /*hh < UpDownHRUIndx->Max+1*/; ++hh) {
            ClassVar *thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];
            if(thisVar->dimen == CRHM::BASIN && hh > 1 || hh > thisVar->dim || !thisVar->values && !thisVar->ivalues)
              break;

            String S = BuildHru(ListBox1->Items->Strings[ii], hh, thisVar->dimen);

            if(UpDownOBSIndx->Position > 0) {
              if(thisVar->lay == 0) {
                UpDownOBSIndx->Position = 1;
                LabelOBSIndx->Caption = "LAY 1";
                UpDownOBSIndx->Refresh();
              }
              else
               S = BuildLay(S, UpDownOBSIndx->Position);
            }

            int indx = IndexOf(ListBox3, S);
            if(indx == -1) ListBox3->Items->AddObject(S, ListBox1->Items->Objects[ii]);
          } // for
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::LAYsAddListBox1Click(TObject *Sender) {

  TComponent *pComponent = PopupListBox1->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1") {

      int StartCnt = ListBox1->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox1->Selected[ii]) {
          if(ListBox1->Items->Strings[ii][1] == ' ')
            continue;

          ClassVar *thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];
          if(thisVar->dimen == CRHM::BASIN && UpDownHRUIndx->Position > 1 ||
            UpDownHRUIndx->Position > thisVar->dim || !thisVar->values && !thisVar->ivalues)
            return;

          String S = BuildHru(ListBox1->Items->Strings[ii], UpDownHRUIndx->Position, thisVar->dimen);

          if(UpDownOBSIndx->Position > 0) {
            if(thisVar->lay == 0) {
              UpDownOBSIndx->Position = 1;
              LabelOBSIndx->Caption = "LAY 1";
              UpDownOBSIndx->Refresh();
              int indx = IndexOf(ListBox3, S);
              if(indx == -1) ListBox3->Items->AddObject(S, ListBox1->Items->Objects[ii]);
            }
            else {
              long lls = UpDownOBSIndx->Position;
              long lle = thisVar->lay+1;
              if(ShiftDown){
                lls = 1;
                lle = UpDownOBSIndx->Position+1;
              }
              for(long ll = lls; ll < lle; ++ll){
                String S2 = BuildLay(S, ll);
                int indx = IndexOf(ListBox3, S2);
                if(indx == -1) ListBox3->Items->AddObject(S2, ListBox1->Items->Objects[ii]);
              }
            }
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::HRUsLAYsAddListBox1Click(TObject *Sender){

  TComponent *pComponent = PopupListBox1->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox1") {

      int StartCnt = ListBox1->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox1->Selected[ii]) {
          if(ListBox1->Items->Strings[ii][1] == ' ')
            continue;

          for(int hh = UpDownHRUIndx->Position; hh < UpDownHRUIndx->Max+1; ++hh) {

          ClassVar *thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];
          if(thisVar->dimen == CRHM::BASIN && hh > 1 || hh > thisVar->dim || !thisVar->values && !thisVar->ivalues)
            break;

            String S = BuildHru(ListBox1->Items->Strings[ii], hh, thisVar->dimen);

            if(UpDownOBSIndx->Position > 0) {
              if(thisVar->lay == 0) {
                UpDownOBSIndx->Position = 1;
                LabelOBSIndx->Caption = "LAY 1";
                UpDownOBSIndx->Refresh();
                int indx = IndexOf(ListBox3, S);
                if(indx == -1) ListBox3->Items->AddObject(S, ListBox1->Items->Objects[ii]);
              }
              else {
                long lls = UpDownOBSIndx->Position;
                long lle = thisVar->lay+1;
                if(ShiftDown){
                  lls = 1;
                  lle = UpDownOBSIndx->Position+1;
                }
                for(long ll = lls; ll < lle; ++ll){
                  String S2 = BuildLay(S, ll);
                  int indx = IndexOf(ListBox3, S2);
                  if(indx == -1) ListBox3->Items->AddObject(S2, ListBox1->Items->Objects[ii]);
                } // for
              } // else
            } // if
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ResetPickers(void){

  DateTimePicker1->MinDate = -80000;
  DateTimePicker1->MaxDate =  80000;

  DateTimePicker2->MinDate = -80000;
  DateTimePicker2->MaxDate =  80000;

  Global::DTstart = 0; // used to flag first data file
  Global::DTend = 0; // used to flag first data file

}
//---------------------------------------------------------------------------

bool __fastcall TMain::AppHelp(WORD Command, int Data, bool &CallHelp){

  if(Command == HELP_CONTEXT || Command == HELP_CONTEXTPOPUP) {
    String Name = ApplicationDir + "crhm.chm";
    FindFileName(Name);
    HtmlHelp(NULL, Name.c_str(), HH_HELP_CONTEXT, Data);  // data = helpcontext id
    CallHelp = false; // do not call WinHelp
    return true;
  }
  else {
    CallHelp = true; // call WinHelp
    return false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::FlipTicMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y){
  bool flip;

  if(Shift.Contains(ssLeft)){
    if(!SeriesCnt)
      return;
    if(Shift.Contains(ssCtrl)){
      flip = !cdSeries[0]->Visible;
      for (int ii = 0; ii < SeriesCnt; ii ++)
        cdSeries[ii]->Visible = flip;
    }
    else
      for (int ii = 0; ii < SeriesCnt; ii ++)
        cdSeries[ii]->Visible = !cdSeries[ii]->Visible;
  }
  else {
    TLineSeries *cdSeries;
    if(!ListBox4->Items->Count)
      return;
    if(Shift.Contains(ssCtrl)){

      cdSeries = (TLineSeries *) ListBox4->Items->Objects[0];
      flip = !cdSeries->Visible;
      for (int ii = 0; ii < ListBox4->Items->Count; ii ++){
        cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];
        cdSeries->Visible = flip;
      }
    }
    else
      for (int ii = 0; ii < ListBox4->Items->Count; ii ++) {
        cdSeries = (TLineSeries *) ListBox4->Items->Objects[ii];
        cdSeries->Visible = !cdSeries->Visible;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::Analysis1Click(TObject *Sender)
{
  Analysis->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain::FlowDiagramClick(TObject *Sender)
{
  FlowForm->SetTitle(Main->Text.SubString(53, Main->Text.Length()));
  FlowForm->ShowModal();
}
//---------------------------------------------------------------------------

String __fastcall TMain::ExtractHruLay(String S, long &Hru, long &Lay){

  long jj = S.LastDelimiter("(");
  long jj1 = S.LastDelimiter(",");
  long jj2 = S.LastDelimiter(")");

  Lay = 0;
  if(jj1 != 0)
    Lay = (S.SubString(jj1+1, jj2-jj1-1)).ToInt();
  else
    jj1 = jj2;

  if(!HruNames) {
    Hru = (S.SubString(jj+1, jj1-jj-1)).ToInt();
  }
  else{
    Hru = ListHruNames->IndexOf(S.SubString(jj+1, jj1-jj-1));
    if(Hru == -1) // detects observations - still numeric index value
      Hru = (S.SubString(jj+1, jj1-jj-1)).ToInt();
    else
      if(Hru == 0) ++Hru;
  }

  return S.SubString(1, jj-1);
}//---------------------------------------------------------------------------

String __fastcall TMain::ExtractHruLayFunct(String S, long &Hru, long &Lay, String &Funct, String &FullName){

  long jj = S.LastDelimiter("(");
  long jj1 = S.Pos(",");
  long jj2 = S.LastDelimiter(")");
  long jj3 = S.LastDelimiter("_");
  long jj4 = S.LastDelimiter(")");

  Lay = 0;
  if(jj1 != 0)
    Lay = (S.SubString(jj1+1, jj2-jj1-1)).ToInt();
  else
    jj1 = jj2;

  if(!HruNames) {
    Hru = (S.SubString(jj+1, jj1-jj-1)).ToInt();
    if(jj3 > jj2) // if not '_' in variable name
     Funct = S.SubString(jj4+1, S.Length());
  }
  else{
    Hru = ListHruNames->IndexOf(S.SubString(jj+1, jj1-jj-1));
    if(Hru == -1) // detects observations - still numeric index value
      Hru = (S.SubString(jj+1, jj1-jj-1)).ToInt();
    else
      if(Hru == 0) ++Hru;
  }
  FullName = S.SubString(1, jj2); // return name and bracket
  return S.SubString(1, jj-1); // return name
}
//---------------------------------------------------------------------------

String __fastcall TMain::BuildHru(String S, long Hru, CRHM::TDim dimen){

  if(!HruNames)
    return S  + "(" + String(Hru) + ")";
  else{
    String SS;
    if(dimen == CRHM::BASIN)
      SS = "(" + ListHruNames->Strings[0] + ")";
    else
      SS = "(" + ListHruNames->Strings[Hru] + ")";
    return S + SS;
  }
}
//---------------------------------------------------------------------------

String __fastcall TMain::BuildLay(String S, long Lay){

  return S.SubString(1, S.Length()-1) + "," + String(Lay) + ")";
}
//---------------------------------------------------------------------------

void __fastcall TMain::HruNameClick(TObject *Sender){

  MapPar::iterator itPar;
  ClassPar *newPar;
  long Hru, Lay;

  ListBox3->Sorted = false;

  if(!ListHruNames){

    ListHruNames = new TStringList;
    MapGrpNames = new MapstrSS;

    if((itPar = Global::MapPars.find("basin basin_name")) != Global::MapPars.end()) {
      newPar = (*itPar).second;
      ListHruNames->Add(newPar->Strings->Strings[0]);
    }
    else
      ListHruNames->Add("Basin");

    if((itPar = Global::MapPars.find("basin hru_names")) != Global::MapPars.end()) {
      newPar = (*itPar).second;

      for(int ii = 0; ii < newPar->Strings->Count; ++ii)
        ListHruNames->Add(newPar->Strings->Strings[ii]);
    }
    else{
      for(int ii = 0; ii < Global::nhru; ++ii)
        ListHruNames->Add("hru" + String(ii));
    }

    for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
      ClassModule* Mod = (ClassModule*) Global::OurModulesList->Objects[ii];
      String S = Global::OurModulesList->Strings[ii];

      if(Mod->GroupCnt > 0 || Mod->StructCnt > 0){

        if(Mod->GroupCnt > 0){
          string AA;
          GroupEnding(AA, Mod->GroupCnt);
          Pairstr Item = Pairstr(AA.c_str(), ('@' + Mod->Name).c_str());
          MapGrpNames->insert(Item);
        }
        else if(Mod->StructCnt > 0){
          string AA;
          GroupEnding(AA, Mod->GroupCnt);
          Pairstr Item = Pairstr(AA.c_str(), ('@' + Mod->Name).c_str());
          MapGrpNames->insert(Item);
        }
      }
    }

    for(int ii = 0; ListBox3->Items->Count > ii; ++ii){
      String S = ListBox3->Items->Strings[ii];

      ClassVar *thisVar =  (ClassVar *) ListBox3->Items->Objects[ii];

      HruNames = false;
      S = ExtractHruLay(S, Hru, Lay);

      HruNames = true;
      S = BuildHru(S, Hru, thisVar->dimen);

      if(Lay)
        S = BuildLay(S, Lay);

      int Indx = S.Pos("@"); // Insert Group & Struct names
      if(Indx){
        MapstrSS::iterator it;
        if((it = MapGrpNames->find(S.SubString(Indx, 2))) != MapGrpNames->end()) {
          String NewName = (*it).second;
          S.Delete(Indx, 2);
          S.Insert(NewName, Indx);
        }
      }
      ListBox3->Items->Strings[ii] = S;
    }
  }
  else{ // currently using HRU names
    for(int ii = 0; ListBox3->Items->Count > ii; ++ii){
      String S = ListBox3->Items->Strings[ii];

      HruNames = true;
      S = ExtractHruLay(S, Hru, Lay);

      HruNames = false;
      S = BuildHru(S, Hru, CRHM::NHRU);  // fill parameter

      if(Lay)
        S = BuildLay(S, Lay);

      int Indx = S.Pos("@");
      if(Indx){ // group or structure name
        MapstrSS::iterator it;
        for (it = MapGrpNames->begin(); it !=  MapGrpNames->end(); ++it) {
          int pos = S.Pos((*it).second);
          if(pos){ // found name
            String NewName = (*it).first;
            String Name = (*it).second;
            int Len = Name.Length();
            int End = S.Pos("(");
            if(End-pos == Len){ // correct length
              S.Delete(pos, Len);
              S.Insert(NewName, pos);
              break;
            }
          }
        }
      }
      ListBox3->Items->Strings[ii] = S;
    }

    delete ListHruNames;
    ListHruNames = NULL;
    delete MapGrpNames;
    MapGrpNames = NULL;
  }

  ListBox3->Sorted = false;
}
//---------------------------------------------------------------------------

  String __fastcall TMain::HRUStdString(String S){ // handles observations too!

    long Hru, Lay;

    if(ListHruNames) {

      String SS = ExtractHruLay(S, Hru, Lay);

      HruNames = false; // temporarily change state

      S = BuildHru(SS, Hru, CRHM::NHRU);  // fill parameter

      if(Lay)
        S = BuildLay(S, Lay);

      HruNames = true; // restore
    }

    return S;

  }
//---------------------------------------------------------------------------

void __fastcall TMain::Last1Click(TObject *Sender)
{
  if(Last1->Checked)
    Last1->Checked = false;
  else {
    Last1->Checked = true;
    All1->Checked = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::All1Click(TObject *Sender)
{
  if(All1->Checked)
    All1->Checked = false;
  else {
    All1->Checked = true;
    Last1->Checked = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::DebugScreen1Click(TObject *Sender)
{
  if(DebugScreen1->Checked)
    DebugScreen1->Checked = false;
  else
    DebugScreen1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::Last1Rprt(TObject *Sender)
{
  TStringList *LogList = new TStringList;

  String S, Sx, Sy;
  ClassVar *thisVar;

  Sx = "time";
  Sy = "units";

  for(int vv = 0; vv < SeriesCnt; ++vv) {
    S = cdSeries[vv]->Title;
    Sx += "\t" + S;

    thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    S = thisVar->units.c_str();
    Sy += "\t" + S;
  }

  LogList->Add(Sx);
  LogList->Add(Sy);

  int nn = cdSeries[0]->Count();

  Sx = FloatToStrF(cdSeries[0]->XValue[nn-1], ffGeneral, 10, 0);

  for (int vv = 0; vv < SeriesCnt; ++vv) {
    thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    int prec = 6;
    if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
      prec = 4;

    Sy = FloatToStrF(cdSeries[vv]->YValue[nn-1], ffGeneral, prec, 0);

    Sx = Sx + "\t" + Sy;
  }

  LogList->Add(Sx);

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  String FileName = "CRHM_output";
  if(ID > 0)
    FileName += String("_") + ID;

  LogList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".txt");
  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMain::All1Rprt(TObject *Sender){

  TStringList *LogList = new TStringList;

  String S, Sx, Sy;
  ClassVar *thisVar;
  TDateTime Dt;

  Sx = "time";
  Sy = "units";

  for(int vv = 0; vv < SeriesCnt; ++vv) {
    S = cdSeries[vv]->Title;
    Sx += "\t" + S;

    thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    S = thisVar->units.c_str();
    Sy += "\t" + S;
  }

  LogList->Add(Sx);
  LogList->Add(Sy);

  for(int nn = 0; nn < cdSeries[0]->Count(); ++nn){

    switch (Global::TimeFormat){
      case CRHM::MS:
        Sx = FloatToStrF(cdSeries[0]->XValue[nn], ffGeneral, 10, 0);
        break;
      case CRHM::MMDDYYYY:
        Dt = TDateTime (cdSeries[0]->XValue[nn]);
        Sx = FormatDateTime("mm/dd/yyyy hh:mm ", Dt);
        break;
      case CRHM::YYYYMMDD:
        Dt = TDateTime (cdSeries[0]->XValue[nn]);
        Sx = FormatDateTime("yyyy-mm-dd hh:mm ", Dt);
        break;
    }

    for (int vv = 0; vv < SeriesCnt; ++vv) {
      if(cdSeries[0]->Count() == cdSeries[vv]->Count()){ // has to equal first series length
        ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
        int prec = 6;

        if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
          prec = 4;

        Sy = FloatToStrF(cdSeries[vv]->YValue[nn], ffGeneral, prec, 0);

        Sx = Sx + "\t" + Sy;
      }
    }

    LogList->Add(Sx);
  }

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  String FileName = "CRHM_output";
  if(ID > 0)
    FileName += String("_") + ID;

  LogList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".txt");
  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMain::DebugScreen1Rprt(TObject *Sender)
{
  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  String FileName = "CRHM_output";
  if(ID > 0)
    FileName += String("_") + ID;

  LogForm->MemoDebug->Lines->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".log");
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddArray1Click(TObject *Sender) {

  TComponent *pComponent = PopupListBox2->PopupComponent;
  if(pComponent) {
    if((pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox2")
      || (pComponent->ClassNameIs("TLabel") && pComponent->Name == "LabelFunct")) {

      int StartCnt = ListBox2->Items->Count;
      for(int ii = 0; ii < StartCnt; ++ii) {

        if(ListBox2->Selected[ii]) {

          int IndxMax = ((ClassVar *) ListBox2->Items->Objects[ii])->cnt;

          for(int nn = UpDownOBSIndx->Position; nn < IndxMax+1; ++nn) {

            String S = ListBox2->Items->Strings[ii] +
                     "(" + String(nn) + ")" + Sstrings[Funct];

            int iii = IndexOf(ListBox4, S);

            if(iii == -1) {
              TLineSeries *cdSeries;

              if(((ClassVar *) ListBox2->Items->Objects[ii])->FileData->Times == NULL)
                cdSeries = new TLineSeries(this);
              else
                cdSeries = (TLineSeries *) new TPointSeries(this);

              ClassVar* thisVar = (ClassVar*) ListBox2->Items->Objects[ii];
              cdSeries->Tag = (int) thisVar; // ClassVar*
              cdSeries->VertAxis = (TVertAxis) thisVar->TchrtOpt;

              cdSeries->XValues->DateTime = TRUE;
              CurrentColor = colours[nn % ncolours];
              cdSeries->Color = CurrentColor;
              cdSeries->ParentChart = Chart;
              cdSeries->Title = S;

              ListBox4->Items->AddObject(S, (TObject *) cdSeries);
              AddObsPlot(Sender, (ClassVar *) ListBox2->Items->Objects[ii], cdSeries, S, Funct);
            } // if
          } // for
        }  // if
      } //for
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::PrjAutoExitClick(TObject *Sender)
{
  if(PrjAutoExit->Checked)
    PrjAutoExit->Checked = false;
  else
    PrjAutoExit->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::ParameterBackUp(TObject *Sender) {

  MapPar::iterator itPar;
  ClassPar *thisPar;

  for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
    thisPar = (*itPar).second;
    thisPar->BackUp(); // copy parameter values
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::ParameterRestore(TObject *Sender) {

  MapPar::iterator itPar;
  ClassPar *thisPar;

  for(itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); ++itPar){
    thisPar = (*itPar).second;
    thisPar->Restore(); // restore parameter values
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::VariableBackUp(TObject *Sender) {

  MapVar::iterator itVar;
  ClassVar *thisVar;

  TempTime = Global::DTindx;

  for(itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); ++itVar){
    thisVar = (*itVar).second;
    thisVar->BackUp(); // copy variable                                        values
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::VariableRestore(TObject *Sender) {

  MapVar::iterator itVar;
  ClassVar *thisVar;

  Global::DTindx = TempTime;

  for(itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); ++itVar){
    thisVar = (*itVar).second;
    if(thisVar->name == "Julian_window")
      continue;

    if(thisVar->name == "Julian_lockout")
      continue;

    if(thisVar->name == "t0_Var")
      continue;

    if(thisVar->name == "t0_Acc")
      continue;

    if(thisVar->name == "t0_inhibit#")
      continue;

    thisVar->Restore(); // restore variable values
  }
}
//---------------------------------------------------------------------------

ClassVar *VarFind(string name){
  MapVar::iterator itVar;

  if((itVar = Global::MapVars.find(name)) == Global::MapVars.end())
    return NULL;
  else
    return ((*itVar).second);
}
//---------------------------------------------------------------------------

ClassPar *ParFind(string name){ // where name is concatenation of MODULE and NAME
  MapPar::iterator itPar;

  if((itPar = Global::MapPars.find(name)) != Global::MapPars.end())
    return ((*itPar).second);
  else
    return NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMain::Macro1Click(TObject *Sender)
{
  if(FormEntry->ShowModal() == mrOk){

    if(InitMacroCnt && InitModCnt){
      --InitModCnt;
      InitMacroCnt = 0;
    }

    ListBoxMacroClear(Sender); // clears ListBox1 & ListBox2

    AdminMacro.MacroClear();

    MacroLoad(Sender);

    AdminMacro.MacroUpdate();

    InitModules(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::MacroLoad(TObject *Sender)
{
  Global::GroupCntTrk = 0;
  Global::StructCntTrk = 0;

  ClearModules(Sender, false);

  if(Global::MacroModulesList->Count > 0) {
    int Macro = 0;

    while (Macro < Global::MacroModulesList->Count) {

      string s(Global::MacroModulesList->Strings[Macro].c_str());
      string::size_type ppp = s.find_last_not_of(' ');
      if(s.empty() || ppp == string::npos || s[0] == '/'){
        ++Macro;
        continue;
      }
      string Desc;
      string::size_type pp = s.find_first_of(" /");
      if(pp != string::npos){
        Desc = s.substr(pp); // macro dis
        s = s.substr(0, pp); // macro name
        pp = Desc.find_first_not_of(" /");
        Desc = Desc.substr(pp);
        Desc = '\'' + Desc + '\''; // Bld handles as block
      }
      else
        Desc = "'no description given'"; // Bld handles as block

      ClassMacro *Custom = new ClassMacro(s, Macro, "04/20/06", Desc);
      AdminMacro.AddModule(Custom);

      String S;

      while(S = Global::MacroModulesList->Strings[Macro].TrimLeft(), !(S.SubString(1,3) == "end" &&
            (S.Length() == 3 || S.IsDelimiter(" /", 4))) && Macro < Global::MacroModulesList->Count)

        ++Macro;

      ++Macro;
    } // while

    AdminMacro.LoadCRHM("Macro");
    AdminMacro.Accept(mrYesToAll);

    if(InitMacroCnt == 0){
      InitMacroCnt = 1;
      ++InitModCnt;
    }

    UpDateModelMenu();

    if(SeriesCnt > 0) {
      for (int ii = 0; ii < SeriesCnt; ii ++) {
        cdSeries[ii]->ParentChart = NULL;
        cdSeries[ii]->Clear();
      }
      SeriesCnt = 0;
    }
  } // if
}
//---------------------------------------------------------------------------


void __fastcall TMain::FormClose(TObject *Sender, TCloseAction &Action)
{ // handles Main close button

  PrjCloseClick(Sender);
  if(cancel)
    Action = caNone; // cancel
  else{
    HtmlHelp(0, NULL, HH_CLOSE_ALL, 0);
    if(ListHruNames){
      delete ListHruNames;
      delete MapGrpNames;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::AKA1Click(TObject *Sender)
{
  FormAKA->ShowModal();
}
//---------------------------------------------------------------------------

bool __fastcall TMain::FindFileName(String &FileName) {

String FilePart;

String ApplicationDir = ExtractFilePath(AnsiReplaceStr(Application->ExeName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples
String ProjectDir = ExtractFilePath(AnsiReplaceStr(OpenDialogPrj->FileName, "/", "\\")); // Fix for "C:/Program files/CRHM/Examples

  if(FileExistsSp(FileName)) // file path directory
    return true;

  int Pos = FileName.LastDelimiter("\\/" );
  if(Pos){
    FilePart = FileName.SubString(Pos+1, FileName.Length());

    if(FileExistsSp(FilePart)){ // current directory
      FileName = FilePart;
      return true;
    }
  }
  else
    FilePart = FileName;

// original file may now be in project directory
  String NewFileName = ProjectDir + FilePart;
  if(FileExistsSp(NewFileName)){
    FileName = NewFileName;
    return true;
  }

// original file may now be in Application directory
  NewFileName = ApplicationDir + FilePart;
  if(FileExistsSp(NewFileName)){
    FileName = NewFileName;
    return true;
  }

  return false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::SaveChartTemplateClick(TObject *Sender){
  if(SaveChartTemplate->Checked)
    SaveChartTemplate->Checked = false;
  else
    SaveChartTemplate->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::UpdateOurModules(void){

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
    int jj = Global::AllModulesList->IndexOf(Global::OurModulesList->Strings[ii]);
    if(jj < 0) {
      CRHMException Except((Global::OurModulesList->Strings[ii] + " Module not defined in CRHM model").c_str(), ERR);
      Global::OurModulesList->Clear();
      Application->MessageBox(Except.Message.c_str(), "Missing module", MB_OK);
      LogError(Except);
    }
    else
      Global::OurModulesList->Objects[ii] = Global::AllModulesList->Objects[jj];
  }
}
//---------------------------------------------------------------------------
long __fastcall TMain::IndexOf(TListBox *Box, const AnsiString S){
  for(int ii = 0; ii < Box->Count; ++ii){
    if(Box->Items->Strings[ii] == S)
    return ii;
  }
  return -1;
}
//---------------------------------------------------------------------------

void __fastcall TMain::AddObsFunct1Click(TObject *Sender)
{
  TComponent *pComponent = PopupListBox3->PopupComponent;
  if(pComponent) {
    if(pComponent->ClassNameIs("TListBox") && pComponent->Name == "ListBox3") {

      for(int ii = 0; ii < ListBox3->Items->Count; ++ii) {

        if(ListBox3->Selected[ii]) {

            if(Funct == CRHM::FOBS) {
              Application->MessageBox("cannot be a simple observation function", "Warning", MB_OK);
              return;
            }

            int Index;
            for(Index = 0; Index < Main->Chart->SeriesCount(); ++Index)
              if(ListBox3->Items->Strings[ii] == Main->Chart->Series[Index]->Title)
                break;

            String S = ListBox3->Items->Strings[ii] + Sstrings[Funct];

            int iii = IndexOf(ListBox4, S);

            if(iii == -1 && Funct != CRHM::FOBS) {
              long jj = S.LastDelimiter("(");
              long jj2 = S.LastDelimiter(")");

              TLineSeries *cdSeries;

              ClassVar* orgVar = (ClassVar*) ListBox3->Items->Objects[ii];
              ClassVar* thisVar = new ClassVar(*orgVar);

              cdSeries = new TLineSeries(this);

              cdSeries->Tag = NULL;
              cdSeries->Tag = (int) thisVar; // ClassVar*
              cdSeries->VertAxis = (TVertAxis) thisVar->TchrtOpt;

              cdSeries->XValues->DateTime = TRUE;
              CurrentColor = colours[Index % ncolours];
              cdSeries->Color = CurrentColor;
              cdSeries->ParentChart = Chart;
              cdSeries->Title = S;

            if(SeriesCnt <= 0 || Index >= Main->Chart->SeriesCount() || Main->Chart->Series[Index]->Count() <= 0) {
              ListBox4->Items->AddObject(S, (TObject *) cdSeries);
              cdSeries->Tag = NULL;
              delete thisVar;
              continue;
            }

              thisVar->name = S.c_str();
              thisVar->FileData = new ClassData();

              thisVar->FunKind = Funct; // permits deletion of FileData
              thisVar->VarFunct = 1;
              thisVar->FileData->Data = new float*[thisVar->dim];   // Data [Cnt] [Lines]
              thisVar->cnt = thisVar->dim; // added 11/23/11
              thisVar->FileData->Lines = Main->Chart->Series[Index]->Count();
              thisVar->FileData->Freq = Global::Freq;
              thisVar->FileData->IndxMin = Global::DTmin;
// interrupt is not synced to end of day. 05/14/12
              thisVar->FileData->IndxMax = (thisVar->FileData->Lines/Global::Freq)*Global::Freq + thisVar->FileData->IndxMin - 1;
              thisVar->FileData->ModN = 1;
              thisVar->FileData->Interval = Global::Interval;
              thisVar->FileData->DataCnt = thisVar->dim;
              thisVar->FileData->FirstFile = false;
              thisVar->visibility = CRHM::PRIVATE;

              for (int jj = 0; jj < thisVar->dim; jj++)
                thisVar->FileData->Data[jj] = new float[thisVar->FileData->Lines];

              long Indx;
              if(ListHruNames) // using names
                Indx = ListHruNames->IndexOf(S.SubString(jj+1, jj2-jj-1)) - 1;
              else{ if(thisVar->root != "")
                  Indx = 0; // not an observation
                else
                  Indx = (S.SubString(jj+1, jj2-jj-1)).ToInt()-1;
              }

              for (long jj = 0; jj < thisVar->FileData->Lines; jj++)
                thisVar->FileData->Data[Indx][jj] = Main->Chart->Series[Index]->YValue[jj];

              ListBox4->Items->AddObject(S, (TObject *) cdSeries);
              AddObsPlot(Sender, thisVar, cdSeries, S, Funct);

              delete thisVar->FileData;
              thisVar->FileData = NULL;
            } // if
        }
      }
    }
  }
  else
    MessageBeep(0);
}
//---------------------------------------------------------------------------

CRHM::TFun  FindObservationType(String Kind){

  if(Kind == "_obs") Kind = "";
  for(int ii = CRHM::FOBS; ii <= CRHM::DLTA; ii++)
    if(Kind == Sstrings[ii]) return (CRHM::TFun)ii;
  return (CRHM::TFun) 0;
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBoxMacroClear(TObject *Sender){ // used by Macro

  ClassVar * thisVar;

  if(SeriesCnt <= 0)
    ListBox3->Clear();
  else{
    int indx;
    for(int jj = 0; jj < SeriesCnt;)
      if(indx = ListBox3->Items->IndexOf(cdSeries[jj]->Title), indx > -1) {
        thisVar =  (ClassVar *) ListBox3->Items->Objects[indx];
        if(thisVar->DLLName == "Macro"){ // delete only macros
          cdSeries[jj]->ParentChart = NULL;
          cdSeries[jj]->Clear();

          for(int kk = jj+1; kk < SeriesCnt; ++kk)
            cdSeries[kk-1] = cdSeries[kk];

          ListBox3->Items->Delete(indx);
          SeriesCnt--; // no need to increment
        }
        else
          ++jj; // increment
      }
  }

  for(int ii = 0; ii < ListBox1->Items->Count; ii++) {
    thisVar =  (ClassVar *) ListBox1->Items->Objects[ii];
    if(thisVar != NULL && thisVar->DLLName == "Macro") {
      ListBox1->Items->Delete(ii);
      ii = 0;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::StateFileClose(TObject *Sender){

  TMenuItem *ObsItem;

  TMenuItem * thisMenu = (TMenuItem *) Sender;

  ObsItem = MainMenu1->Items->Items[5];

  if(ObsItem->Count > 5){

    String S = thisMenu->Caption;
    S = S.Delete(1, 1); // remove "&"

    int Reply = IDOK;
    if(ProjectOpen)
      Reply = Application->MessageBox(S.c_str(), "Close State File", IDOK);

    if(Reply == IDOK)
      ObsItem->Delete(5);  // delete submenu
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::StateFileCloseAll(TObject *Sender){

// clear State file menu

  TMenuItem *StateItem;

  StateItem = MainMenu1->Items->Items[5];

  if(StateItem->Count > 5){ // State files open
    for(int ii = 5; ii < StateItem->Count;){ // count updates after the delete!
//      String S = StateItem->Caption;
      StateItem->Delete(ii);  // delete submenu
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TMain::LastRprtObs(TObject *Sender)
{
  bool Daily;

  int SeriesCnt = ListBox4->Items->Count;
  if(SeriesCnt <= 0) return;

  TLineSeries *cdS = (TLineSeries *) ListBox4->Items->Objects[0];
  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

  cdSeries = new TLineSeries*[SeriesCnt];

// can only do interval or daily at one time
  int Acnt = 0;
  for (int ii = 0; ii < SeriesCnt ; ++ii){
    cdSeries[Acnt] = (TLineSeries *) ListBox4->Items->Objects[ii];
    ClassVar *thisVar =  (ClassVar *) cdSeries[Acnt]->Tag;
    if(ii == 0){
      if(thisVar->FunKind > MJ_W)
        Daily = true;
      ++Acnt;
    }
    else
      if(thisVar->FunKind > MJ_W && Daily || thisVar->FunKind <= MJ_W && !Daily)
        ++Acnt;
  }
  SeriesCnt = Acnt;
  TStringList *LogList = new TStringList;

  String Sx, Sy;

  Sx = "time";
  for(int vv = 0; vv < SeriesCnt; ++vv) {
    String S = cdSeries[vv]->Title;
    Sx += "\t" + S;
  }
  LogList->Add(Sx);

  int nn = cdSeries[0]->Count();

  Sx = FloatToStrF(cdSeries[0]->XValue[nn-1], ffGeneral, 10, 0);

  for (int vv = 0; vv < SeriesCnt; ++vv) {
    ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
    int prec = 6;
    if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
      prec = 4;

    Sy = FloatToStrF(cdSeries[vv]->YValue[nn-1], ffGeneral, prec, 0);

    Sx = Sx + "\t" + Sy;
  }

  LogList->Add(Sx);

  delete [] cdSeries;
  cdSeries = NULL;

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  String FileName = "CRHM_output";
  if(thisPar)
    if(thisPar->ivalues[0] > 0)
      FileName += String("_") + thisPar->ivalues[0];

  LogList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".txt");
  LogList->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMain::AllRprtObs(TObject *Sender)
{
  bool Daily;

  int SeriesCnt = ListBox4->Items->Count;
  if(SeriesCnt <= 0) return;

  TLineSeries *cdS = (TLineSeries *) ListBox4->Items->Objects[0];
  ClassVar *thisVar =  (ClassVar *) cdS->Tag;

  cdSeries = new TLineSeries*[SeriesCnt];

// can only do interval or daily at one time
  int Acnt = 0;
  for (int ii = 0; ii < SeriesCnt ; ++ii){
    cdSeries[Acnt] = (TLineSeries *) ListBox4->Items->Objects[ii];
    ClassVar *thisVar =  (ClassVar *) cdSeries[Acnt]->Tag;
    if(ii == 0){
      if(thisVar->FunKind > MJ_W)
        Daily = true;
      ++Acnt;
    }
    else
      if(thisVar->FunKind > MJ_W && Daily || thisVar->FunKind <= MJ_W && !Daily)
        ++Acnt;
  }
  SeriesCnt = Acnt;

  TStringList *LogList = new TStringList;

  String Sx, Sy;

  Sx = "time";
  for(int vv = 0; vv < SeriesCnt; ++vv) {
    String S = cdSeries[vv]->Title;
    Sx += "\t" + S;
  }
  LogList->Add(Sx);

  for(int nn = 0; nn < cdSeries[0]->Count(); ++nn){

    Sx = FloatToStrF(cdSeries[0]->XValue[nn], ffGeneral, 10, 0);

    for (int vv = 0; vv < SeriesCnt; ++vv) {
      ClassVar *thisVar =  (ClassVar *) cdSeries[vv]->Tag;
      int prec = 6;
      if(thisVar->varType == CRHM::Int || thisVar->varType == CRHM::ReadI)
        prec = 4;

      Sy = FloatToStrF(cdSeries[vv]->YValue[nn], ffGeneral, prec, 0);
      Sx = Sx + "\t" + Sy;
    }

    LogList->Add(Sx);
  }

  delete [] cdSeries;
  cdSeries = NULL;

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  String FileName = "CRHM_output";
  if(thisPar)
    if(thisPar->ivalues[0] > 0)
      FileName += String("_") + thisPar->ivalues[0];

  LogList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".txt");
  LogList->Clear();
}
//---------------------------------------------------------------------------

bool __fastcall TMain::FileExistsSp(String FileName) {

  ifstream DataFile;

  DataFile.open(FileName.c_str());
  if(DataFile) {
    DataFile.close();
    return true;
  }
  else
    return false;
}
//---------------------------------------------------------------------------

String __fastcall TMain::DeclObsName(ClassVar *thisVar){

  String Newname = thisVar->name.c_str();
  int jj = Global::OurModulesList->IndexOf(thisVar->module.c_str()); // find module
  if(jj > -1 && Newname.Pos("#") > 0){ // -1 for "obs" and "#" for declared "obs"
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[jj];
    if(thisModule->isGroup){ // if group add suffix
      String AA;
      GroupEnding(AA, thisModule->GroupCnt);
      Newname += AA;
    }
  }
  return Newname;
}
//---------------------------------------------------------------------------

void __fastcall TMain::Label4Click(TObject *Sender){

  ClassVar *thisVar;
  MapVar::iterator itVar;

  String Labels[] = {"Variables", "Variables by Module", "Diagnostic Variables", "Private Variables"};
  String Newname;

  ++Box1Disply;
  if(Box1Disply > CRHM::PRIVATE)
    Box1Disply = CRHM::OUTPUT;

  Label4->Caption = Labels[Box1Disply];
  ListBox1->Items->Clear();

  Max_Name_Width1 = 0;
  Max_Name_Width2 = 0;

  SendMessage(ListBox1->Handle,
    LB_SETHORIZONTALEXTENT, 150, 0);

  if(Box1Disply == CRHM::OUTPUT){
    ListBox1->Sorted = true;

    for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
      thisVar = (*itVar).second;
      if(thisVar->varType < CRHM::Read && thisVar->visibility == CRHM::USUAL &&
         thisVar->dimen != CRHM::NREB &&
         (thisVar->values || thisVar->ivalues) && !thisVar->FileData){
        Newname = DeclObsName(thisVar);
        if(IndexOf(ListBox1, Newname) == -1){
          ListBox1->Items->AddObject(Newname, (TObject*) thisVar);
          if(Newname.Length() > Max_Name_Width2)
             Max_Name_Width2 = Newname.Length();
        }
      }
    }
  }
  else{
    ListBox1->Sorted = false;
    String S0;

    for(int ii = 0; ii < Global::OurModulesList->Count; ii++) {
      String S = Global::OurModulesList->Strings[ii];
      ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
      if(S0 != S){
        if(!S0.IsEmpty())
          ListBox1->Items->Add(" ");
        S0 = S;
        if(thisModule->variation != 0){
          String AA("#0");
          AA[2] += log(thisModule->variation)/log(2) + 1;
          S0 += AA;
        }

        S0 = "   --- " + S0;
        ListBox1->Items->AddObject(S0 + " ---", Global::OurModulesList->Objects[ii]);
        if(S0.Length() > Max_Name_Width1)
           Max_Name_Width1 = S0.Length();
      }

      switch (Box1Disply){ // display in module/group
        case CRHM::USUAL :
          for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
            thisVar = (*itVar).second;
            if(S == thisVar->module.c_str() && thisVar->visibility == CRHM::USUAL &&
               Variation_Decide(thisVar->variation_set, thisModule->variation) &&
               thisVar->dimen != CRHM::NREB &&
               (thisVar->values || thisVar->ivalues) && !thisVar->FileData){

              if(UpDownOBSIndx->Max < thisVar->lay && thisVar->dimen == CRHM::NDEF)
                  UpDownOBSIndx->Max = thisVar->lay;
              Newname = DeclObsName(thisVar);
              if(IndexOf(ListBox1, Newname) == -1){
                ListBox1->Items->AddObject(Newname, (TObject*) thisVar);
                if(Newname.Length() > Max_Name_Width2)
                   Max_Name_Width2 = Newname.Length();
              }
            }
          }
          break;

        case CRHM::DIAGNOSTIC : // display diagnostic variables
          for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
            thisVar = (*itVar).second;
            if(S == thisVar->module.c_str() && thisVar->visibility == CRHM::DIAGNOSTIC &&
               thisVar->dimen != CRHM::NREB &&
               (thisVar->values || thisVar->ivalues) && !thisVar->FileData){
              Newname = DeclObsName(thisVar);
              if(IndexOf(ListBox1, Newname) == -1){
                ListBox1->Items->AddObject(Newname, (TObject*) thisVar);
                if(Newname.Length() > Max_Name_Width2)
                   Max_Name_Width2 = Newname.Length();
              }
            }
          }
          break;

        case CRHM::PRIVATE : // display Local variables
          for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
            thisVar = (*itVar).second;
            if(S == thisVar->module.c_str() && thisVar->visibility == CRHM::PRIVATE &&
               thisVar->dimen != CRHM::NREB &&
               (thisVar->values || thisVar->ivalues) && !thisVar->FileData){
              Newname = DeclObsName(thisVar);
              if(IndexOf(ListBox1, Newname) == -1){
                ListBox1->Items->AddObject(Newname, (TObject*) thisVar);
                if(Newname.Length() > Max_Name_Width2)
                   Max_Name_Width2 = Newname.Length();
              }
            }
          }
          break;
      }
    } // for
  } // else

  if(Max_Name_Width2 > Max_Name_Width1) // Max_Name_Width1 only title, Max_Name_Width2 handles other names
    Max_Name_Width1 = Max_Name_Width2;

  if(Max_Name_Width1*6 > ListBox1->Width)
    ListBox1->ScrollWidth = Max_Name_Width1*6;

  Max_Name_Width1 += 5; // handles array element

  if(Max_Name_Width2*6 > ListBox3->Width)
    ListBox3->ScrollWidth = Max_Name_Width1*6;

  if(Max_Name_Width2*6 > ListBox2->Width)
    ListBox2->ScrollWidth = Max_Name_Width2*6;

  Max_Name_Width2 += 5; // handles array element

  if(Max_Name_Width2*6 > ListBox4->Width)
    ListBox4->ScrollWidth = Max_Name_Width2*6;

}
//---------------------------------------------------------------------------

bool __fastcall TMain::isSimple(string module){ // determines if Simple or Group/Struct module

  int jj = Global::AllModulesList->IndexOf(module.c_str());
  ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[jj];
  if(!(thisModule->isGroup || thisModule->isStruct))
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------

bool TMain::Variation_Decide(int Variation_set, long Variation){

  VandP V; V.Set(Variation);

  long variations = V.GetV(); // & 2047;

  if((Variation_set & 2048) != 0 && variations == 0 || // handles VARIATION_0
    (Variation_set & 4096) != 0 ||                        // handles VARIATION_0
    (Variation_set == 0) ||                               // handles VARIATION_ORG
    (variations & Variation_set) != 0)                 // handles #1, #2, #4 etc.
    return true;
  else
    return false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if(Shift.Contains(ssShift))
    ShiftDown = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::ListBox1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  ShiftDown = false;
}
//---------------------------------------------------------------------------

void __fastcall TMain::FreqDefault1Click(TObject *Sender)
{
  const long OK_Values[14] = {1, 2, 3, 4, 6, 8, 12, 24, 48, 72, 96, 144, 192, 288};
  if(ObsFilesList->Count == 0) {
    loop:
    long Warn = Application->MessageBox(" Yes - increase, \n No - decrease or\n Cancel - exit.\n\n This is only effective when NO observation files are open.",
                                        String("Do you want to change the default interval? Currently: " + String(Global::Freq)).c_str(), MB_YESNOCANCEL);
    if(Warn == IDYES || Warn == IDNO){
      for(int ii = 0; ii < 14; ++ii) {
        if(Global::Freq == OK_Values[ii]){
          if(Warn == IDYES){
            if(ii == 13)
              Global::Freq = OK_Values[0];
            else
              Global::Freq = OK_Values[ii+1];
          }
          else{
            if(ii == 0)
              Global::Freq = OK_Values[13];
            else
              Global::Freq = OK_Values[ii-1];
          }
          Global::Interval = 1.0/Global::Freq;
          goto loop;
        }
      }
    }
    return;
  }
  else
    Application->MessageBox("Only operates when NO observation files are open.", String("changes the default interval? Currently: " + String(Global::Freq)).c_str(), MB_OK);
}
//---------------------------------------------------------------------------

  long __fastcall TMain::CheckforModule(String S, long Pos){
    long jj = Global::AllModulesList->IndexOf(S);
    if(jj > -1)
      return jj;
    else{ // renamed module
      jj = Global::OldModuleName->IndexOf(S); // find old name
      if(jj == -1)
        return jj; // unknown module
      Global::OurModulesList->Strings[Pos] = Global::NewModuleName->Strings[jj]; // replace with new name
      String Message = "Converting module " + Global::OldModuleName->Strings[jj] + " to " + Global::NewModuleName->Strings[jj];
      LogMessage(Message.c_str());
      Application->MessageBox(Message.c_str(), "Save File (Use a new project file name until satisfied with changes!)", MB_OK);
      return (long) Global::OldModuleName->Objects[jj]; // position in Global::AllModulesList
    }
}

void __fastcall TMain::daily1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 2;
  daily1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::biweekly1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 3;
  biweekly1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::weekly1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 4;
  weekly1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::monthly1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 5;
  monthly1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::yearly1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 6;
  yearly1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::atend1Click(TObject *Sender)
{
  PlotControl->PlotUpdate->ItemIndex = 7;
  atend1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::VarObsFunct_Update(TObject *Sender){

  ClassVar* thisVar;
  ClassVar* orgVar;
  CRHM::TFun Funct;

  long Index;
  long nn;
  bool isObs = false;

  for(long ii = 0; ii < ListBox4->Items->Count; ++ii) {

      Funct = CRHM::FOBS; // handles names containing underscores

      String S = ListBox4->Items->Strings[ii];
      String S1, S2;

      long jj1 = S.LastDelimiter("_");

      S1 = S.SubString(1, jj1-1);
      if(jj1 != 0)
        S2 = S.SubString(jj1, S.Length());

      for(Index = 0; Index < Main->Chart->SeriesCount(); ++Index){ // must not add/delete series while in use
        if(Main->Chart->Series[Index]->Title == S1)
          break;
      }

      for(nn = 0; nn < 16; ++nn){ // search table for function type
        if(Sstrings[nn] == S2){ // found
          Funct = nn;
          break;
        }
      }

      if(Funct == CRHM::FOBS)
        continue;  // an observation

      long Indx = ListBox3->Items->IndexOf(S1);
      if(Indx == -1){ // an observation
        isObs = true;
        jj1 = S.LastDelimiter("(");
        string S3 = string("obs ") +  S.SubString(1, jj1-1).c_str();
        thisVar = ClassVarFind(S3); // find original observation
      }

      TLineSeries * cdSeries2 = (TLineSeries *) ListBox4->Items->Objects[ii]; // last obs/var function plot

      if(!isObs){ // variable
        if(cdSeries2->Tag){
          thisVar = (ClassVar*) cdSeries2->Tag;
          delete thisVar; // delete from previous run
        }
        orgVar = (ClassVar*) ListBox3->Items->Objects[Indx];
        thisVar = new ClassVar(*orgVar); // copy of original variable to create "FileData" run data values in.
      }


      TLineSeries * cdSeries = new TLineSeries(this);

      ListBox4->Items->Objects[ii] = (TObject*) cdSeries;

      cdSeries->XValues->DateTime = TRUE;
      CurrentColor = colours[ii % ncolours];
      cdSeries->Color = CurrentColor;
      cdSeries->Title = S;

      if(ObsFunct_Toggle)
        cdSeries->Visible = true;
      else
        cdSeries->Visible = false;

      if(isObs){
        AddObsPlot(Sender, thisVar, cdSeries, S, Funct);
      }
      else{

        thisVar->name = S.c_str();
        thisVar->FileData = new ClassData();

        cdSeries->VertAxis = (TVertAxis) thisVar->TchrtOpt;

        thisVar->FunKind = Funct; // permits deletion of FileData

        thisVar->FileData->Data = new float*[1];   // Data [Cnt] [Lines]
        thisVar->cnt = 1;
        thisVar->FileData->Lines = Main->Chart->Series[Index]->Count();
        thisVar->FileData->Freq = Global::Freq;
        thisVar->FileData->IndxMin = Global::DTmin;
// interrupt is not synced to end of day. 05/14/12
        thisVar->FileData->IndxMax = (thisVar->FileData->Lines/Global::Freq)*Global::Freq + thisVar->FileData->IndxMin - 1;
        thisVar->FileData->ModN = 1;
        thisVar->FileData->Interval = Global::Interval;
        thisVar->FileData->DataCnt = 1;
        thisVar->FileData->FirstFile = false;
        thisVar->visibility = CRHM::PRIVATE;

        thisVar->FileData->Data[0] = new float[thisVar->FileData->Lines];

        for (long jj = 0; jj < thisVar->FileData->Lines; jj++)
          thisVar->FileData->Data[0][jj] = Main->Chart->Series[Index]->YValue[jj];

        AddObsPlot(Sender, thisVar, cdSeries, S, Funct);

        delete thisVar->FileData;
        thisVar->FileData = NULL;

        cdSeries->Tag = (int) thisVar;
      }

      cdSeries2->Clear(); // delete old series data
      cdSeries2->ParentChart = NULL; // remove old series from chart

      cdSeries->ParentChart = Chart; // plot new series to chart
  }  // for
}
//---------------------------------------------------------------------------

void __fastcall TMain::SummaryScreen1Click(TObject *Sender)
{
  if(SummaryScreen1->Checked)
    SummaryScreen1->Checked = false;
  else
    SummaryScreen1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMain::SummaryScreen1Rprt(TObject *Sender){

  TStringList *LogList = new TStringList;
  String S, Sx, Sy;
  TLineSeries * cdSeries2;

  long itime[6];
  long Next = -1;
  long Index;
  long First = -1;

  long *Wanted = new long[Main->Chart->SeriesCount()]; // -1 = false, 1 = currently being handled, -2 = handled

  for(long ii = 0; ii < Main->Chart->SeriesCount(); ++ii)
    Wanted[ii] = -1;

  for( ; ;){ // handles different series lengths
    First = -1;
    for(long ii = 0; ii < ListBox4->Items->Count; ++ii) {
      S = ListBox4->Items->Strings[ii];

      for(Index = 0; Index < Main->Chart->SeriesCount(); ++Index) // find series
        if(Main->Chart->Series[Index]->Title == S){
          long tt = S.Pos(")_");
          if(!S.Pos(")_")) // ignore root observations
            break;
          cdSeries2 = (TLineSeries *) ListBox4->Items->Objects[ii];
          if(Wanted[Index] == -1){
            if(First == -1)
              First = Index; // flag first trace found
            else if(Main->Chart->Series[Index]->Count() != Main->Chart->Series[First]->Count() || Main->Chart->Series[Index]->XValue[0] != Main->Chart->Series[First]->XValue[0])
              break;

            Wanted[Index] = 1;
          }
        }

      if(Index == Main->Chart->SeriesCount()) // not found
        continue;
    }

    if(First < 0){ // nothing to do
      break;
    }

    Sx = "Dates";
    Sy = "units";
    for(long ii = 0; ii < Main->Chart->SeriesCount(); ++ii) {
      if(Wanted[ii] > 0){
        S = Main->Chart->Series[ii]->Title;
        Sx += "\t" + S;

        ClassVar *thisVar =  (ClassVar *) Main->Chart->Series[ii]->Tag;
        S = thisVar->units.c_str();
        Sy += "\t" + S;
      }
    }
    LogList->Add(Sx);
    LogList->Add(Sy);

    long prec = 6;
    bool Print = FALSE;

    for(long nn = 0; nn < Main->Chart->Series[First]->Count(); ++nn){

      double Date = Main->Chart->Series[First]->XValue[nn];
      dattim(Date, itime);

      switch(TBase){

        case 0: // daily
          if(Next == -1 || Next == itime[2]){ // first interval of next day
            ++Date; // increment day
            dattim(Date, itime);
            if(Next != -1)
              Print = TRUE;
            Next = itime[2];
          }
          break;
        case 1: // water annual
          if(Next == -1 || itime[0] == Next && itime[1] == water_year_month){
            if(Next == -1 && itime[1] < water_year_month)
              Next = itime[0]; // set year
            else{
              if(Next != -1)
                Print = TRUE;
              Next = itime[0] + 1; // increment year
            }
          }
          break;
        case 2: // annual
          if(Next == -1 || itime[0] == Next && itime[1] == 1){
            if(Next == -1 && itime[1] != 1)
              Next = itime[0] + 1; // increment year
            else{
              if(Next != -1)
                Print = TRUE;
              Next = itime[0] + 1; // increment year
            }
          }
          break;
        case 3: // monthly
          if(Next == -1 || Next == itime[1]){
            if(Next != -1)
              Print = TRUE;
            Next = (itime[1])%12 + 1; // increment month
          }
          break;
        case 4: // All
          break;
      } // switch

  // only handles last interval
      if(nn == Main->Chart->Series[First]->Count()-1){ // last time! Short of date by one.
        Print = TRUE;
        ++nn; // cancelled by following --nn
      } // if

      if(Print){
          --nn; // go to previous day

        Sx = FloatToStrF(floor(Main->Chart->Series[First]->XValue[nn]), ffGeneral, 10, 0);

        TDateTime Dt2 = Main->Chart->Series[First]->XValue[nn];
        Sx = Sx + " " + Dt2.DateString();

        for (long vv = 0; vv < Main->Chart->SeriesCount(); ++vv) {
          if(Wanted[vv] > 0){
            Sy = FloatToStrF(Main->Chart->Series[vv]->YValue[nn], ffGeneral, prec, 0);
            Sx = Sx + "\t" + Sy;
          }
        } // for

        ++nn; // restore

        LogList->Add(Sx);
        Print = FALSE;
      } // if print
    }  // for

    for(long ii = 0; ii < Main->Chart->SeriesCount(); ++ii){
      if(Wanted[ii] > 0)
        Wanted[ii] = -2; // indicate handled
    }
  } // infinite for

  ClassPar *thisPar;
  thisPar = ParFind("basin RUN_ID");

  long ID = 0;

  if(!thisPar){
    MapPar::iterator itPar;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->param == "RUN_ID" && thisPar->ivalues[0] > 0) {
        ID = thisPar->ivalues[0];
        break;
      }
    }
  }
  else
    ID = thisPar->ivalues[0];

  String FileName = "CRHM_output";
  if(ID > 0)
    FileName += String("_") + ID;

  LogList->SaveToFile(OpenDialogPrj->InitialDir + "\\" + FileName + ".sum");
  LogList->Clear();

  delete[] Wanted;
}
//---------------------------------------------------------------------------

void __fastcall TMain::LabelBaseMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y){

  if (Button == mbRight){
    ++water_year_month;
    if(water_year_month > 12)
      water_year_month = 1;
  }
  else{
    ++TBase;
    if(TBase > 4)
      TBase = 0;
  }

  if(TBase ==  1)
    LabelBase->Caption = TBases[TBase] + " - " + Tmonths[water_year_month-1];
  else
    LabelBase->Caption = TBases[TBase];
}
//---------------------------------------------------------------------------
//  void __fastcall TMain::MacroLoad_X(TObject *Sender){
//
//    MacroLoad(Sender);
//  }
//---------------------------------------------------------------------------

  void __fastcall TMain::RadioGroupFunctClick(TObject *Sender){

      Funct = (TFun) RadioGroupFunct->ItemIndex;

      LabelFunct->Caption = FStrings[Funct];
  }
//---------------------------------------------------------------------------

  void __fastcall TMain::RadioGroupDisplayClick(TObject *Sender){

    switch (RadioGroupDisplay->ItemIndex) {
      case 0:
        ObsFunct_Toggle = 0;
        break;
      case 1:
        ObsFunct_Toggle = 1;
        break;
      case 2:
        ObsFunct_Toggle = 2;
        break;
    }
  }
//---------------------------------------------------------------------------

  void __fastcall TMain::CancelScreenClick(TObject *Sender){

    CoolBar1->Hide();
  }
//---------------------------------------------------------------------------

void __fastcall TMain::CheckBlankModule(TObject *Sender){

  MapVar::iterator itVar;
  ClassVar * thisVar;

  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    thisVar = (*itVar).second;
    string s = thisVar->name;
  }
}
//---------------------------------------------------------------------------

long __fastcall TMain::FindWildVarFloat(string name, ClassVar* &newVar, bool OnceFlag){

  string spacename = " " + name;;
  string Var;

  MapVar::iterator itVar;
  for (itVar = Global::MapVars.begin(); itVar !=  Global::MapVars.end(); itVar++) {
    Var = (*itVar).first;

    if(Var[0] == '#') // local variable
      continue;

    string::size_type indx = Var.rfind(spacename); // can find name inside longer name
    if(indx == string::npos){
      continue; // nothing found
    }

    newVar = (*itVar).second;
    if(newVar->cnt > 0)  // only observations set "cnt"
      continue;

    if(spacename.substr(1) != newVar->name) // exact match - previous match contained name
      continue;

    return newVar->GetUnit();
  } // for

  newVar = NULL;
  return -1;
}
//---------------------------------------------------------------------------

