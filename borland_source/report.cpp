// 09/29/16
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "report.h"
#include "GlobalCommon.h"
#include "DefCRHMGlobal.h"
#include "ClassModule.h"
#include "CRHMmain.h"
#include "Examples.h"
#include <vcl\printers.hpp>
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRprt *Rprt;

using namespace std;

char varTypes[][6] = {"none", "Int", "Float", "Txt", "Read", "ReadI", "ReadF"};
char dimens[][6] = {"BASIN", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "NHRU", "NOBS", "NLAY", "NDEF", "NFREQ", "NREB", "NDEFN", "NDEFNZ"};
char T_F[][6] = {"No", "Yes"};
char Linked[][13] = {"Shared", "declparam", "declputparam"};
char V_D_H[][11] = {"OUTPUT", "NORMAL", "DIAGNOSTIC", "PRIVATE"};
char Mem[][9] = {"NULL", "Assigned"};
char Fun[][8] = {"FOBS", "VP_SAT", "W_MJ", "MJ_W", "AVG", "MIN", "MAX", "TOT", "POS", "FIRST", "LAST", "CNT", "CNT0", "DLTA", "INTVL", "DAY"};
char Call[][9] = {"NO", "as Basic", "as Funct"};
String LVLStrings[] = {"BASIC", "MACRO", "ADVANCED", "PROTOTYPE", "OBSOLETE", "CUSTOM", "SUPPORT"};

//---------------------------------------------------------------------------
__fastcall TRprt::TRprt(TComponent* Owner)
        : TForm(Owner)                                                                 
{
  if(!Printer()->Printers->Count){
    TMenuItem *FileItem3 = File1->Items[3]; // Print1Click
    FileItem3->Enabled = false;
    TMenuItem *FileItem4 = File1->Items[4]; // PrinterSetup1Click
    FileItem4->Enabled = false;
    TMenuItem *FileItem6 = File1->Items[6]; // Font1Click
    FileItem6->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TRprt::Save1Click(TObject *Sender)
{
  if(!SaveDialog1->FileName.IsEmpty())
    Memo1->Lines->SaveToFile(SaveDialog1->FileName);
  else SaveAs1Click(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TRprt::SaveAs1Click(TObject *Sender)
{
  SaveDialog1->Title = "Save As";
  SaveDialog1->DefaultExt = "rpt";
  SaveDialog1->Filter = "Report Files (*.rpt)|*.rpt";

  if(SaveDialog1->Execute()) {
    SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
    if(SaveDialog1->InitialDir.IsEmpty())
      SaveDialog1->InitialDir = GetCurrentDir();

    Memo1->Lines->SaveToFile(SaveDialog1->FileName);
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TRprt::FormActivate(TObject *Sender)
{
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

  if(SaveDialog1->InitialDir.IsEmpty())
    SaveDialog1->InitialDir = GetCurrentDir();

  Memo1->Lines->Clear();
  Memo1->Lines->Assign(SummaryList);

  if(Printer()->Printers->Count){
    TPrinter *OurPrinter = Printer();
    OurPrinter->Orientation = poPortrait;
  }
  ListBox1->Clear();
  Label1->Caption = "";
  In_Rename = false;
  Rename_Changes = false;

  if(Global::NaNcheck)
    CheckNan1->Caption = "NaN_check ON";
  else
    CheckNan1->Caption = "NaN_check OFF";

}
//---------------------------------------------------------------------------

void __fastcall TRprt::FormClose(TObject *Sender, TCloseAction &Action)
{
  Memo1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Font1Click(TObject *Sender){

  TPrinter *OurPrinter = Printer();
  TFontDialog *FontDialog1 = new TFontDialog(Rprt);

  //If the user pressed OK on the font dialog
  if (FontDialog1->Execute()){ //Change the font of the memo box
    Memo1->Font = FontDialog1->Font;
    OurPrinter->Canvas->Font = FontDialog1->Font; //Change the font of the printer
  }

  delete FontDialog1;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Print1Click(TObject *Sender){

  int LineOnPage, LinesPerPage;
  int StartLine, EndLine, PagesInDoc, FromPage, ToPage;
  int x, y, z, PageNumber;
  bool NewPageRequired;

  TPrinter *OurPrinter = Printer();

  TPrintDialog *PrintDialog1 = new TPrintDialog(Rprt);
  TFontDialog *FontDialog1 = new TFontDialog(Rprt);

  OurPrinter->Refresh();
  //Printer will start at the top of a new page. So we don't have to issue a new page before printing the first page
  NewPageRequired = FALSE;
  //Calculate number of lines that can fit on a page
  LinesPerPage = (OurPrinter->PageHeight /
    OurPrinter->Canvas->TextHeight("W"));
  //Calculate number of whole pages in the document
  PagesInDoc = Memo1->Lines->Count / LinesPerPage;
  //If there are any lines left over, add one more page
  //(that will be a partial page)
  if ((Memo1->Lines->Count % LinesPerPage) > 0)
    PagesInDoc++;

  //Tell the printer dialog the maximum page number
  PrintDialog1->Options.Clear();
  PrintDialog1->Options << poPageNums;
  PrintDialog1->MinPage = 1;
  PrintDialog1->MaxPage = PagesInDoc;
  PrintDialog1->FromPage = 1;
  PrintDialog1->ToPage = PagesInDoc;

  //If the user did not press OK on the printer dialog, return
  if (!PrintDialog1->Execute()) return;

  //Change the font of the printer just in case user changed
  OurPrinter->Canvas->Font = FontDialog1->Font;

  if(PrintDialog1->PrintRange == prPageNums) {    //Set up to print a page range
    FromPage = PrintDialog1->FromPage;
    ToPage = PrintDialog1->ToPage;
  }
  else {           //Print from page 1 to end
    FromPage = 1;
    //To the last page
    ToPage = PagesInDoc;
  }

  //Set the title used in the print manager to identify this job
  OurPrinter->Title = Memo1->Lines->Strings[6];
  //Start the printing job
  OurPrinter->BeginDoc();

  //Start with the first line
  LineOnPage = 0;

  //Always start at the first page
  PageNumber = FromPage;
  //Loop runs until we run out of pages to print
  do
  {
    //Loop to print multiple copies of a page (if required)
    for (y = 0; y < PrintDialog1->Copies; y++) {
      //If a new page is required
      if (NewPageRequired)
      {
        //Print a new page
        OurPrinter->NewPage();
        //Reset the line count
        LineOnPage = 0;
      }
      //Must always print a new page
      //for pages after the first
      NewPageRequired = TRUE;

      //Calculate the memo line that prints at the top of this page
      StartLine = ((PageNumber - 1) * (LinesPerPage-2));
      //Calculate the memo line that prints at the bottom of this page
      EndLine = (LinesPerPage-2) + ((PageNumber - 1) * (LinesPerPage-2));

      //Asjust the ending line count for the last page (which may not be full)
      if (EndLine >= Memo1->Lines->Count) EndLine = Memo1->Lines->Count;

      //For each memo line that will appear on this page
      for (z = StartLine; z < EndLine; z++)
      {
        //Print out a line
        OurPrinter->Canvas->TextOut(20,
          OurPrinter->Canvas->TextHeight(Memo1->Lines->Strings[z]) * LineOnPage,
            ("          " + Memo1->Lines->Strings[z]));
        //Increment the line count
        LineOnPage++;
      }

      OurPrinter->Canvas->TextOut(20,
        OurPrinter->Canvas->TextHeight("W") * (LinesPerPage-1),
          ("           Page " + IntToStr(PageNumber) + " of " + IntToStr(ToPage)));
    } //Required copies of page are printed

    //Increment the page number
    PageNumber++;
  //Keep going until we're out of pages to print
  } while (PageNumber <= ToPage);

  //Close the document
  OurPrinter->EndDoc();

  delete PrintDialog1;
  delete FontDialog1;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::PrintSetup1Click(TObject *Sender) {

  TPrinter *OurPrinter = Printer();

  TPrinterSetupDialog *PrinterSetupDialog1 = new TPrinterSetupDialog(Rprt);
  TFontDialog *FontDialog1 = new TFontDialog(Rprt);

  //Bring up the print setup dialog box
  if(PrinterSetupDialog1->Execute()) //Change the font of the printer just in case user changed
    OurPrinter->Canvas->Font = FontDialog1->Font;

  delete PrinterSetupDialog1;
  delete FontDialog1;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MapvarsClick(TObject *Sender)
{
  ClassVar *thisVar;
  MapVar::iterator itVar;
  string S;

  Label1->Caption = "Mapvars";
  Label1->Tag = 1;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++){
    thisVar = (*itVar).second;
    if(thisVar != NULL){
      S = (*itVar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisVar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MapparsClick(TObject *Sender)
{
  ClassPar *thisPar;
  MapPar::iterator itPar;
  string S;

  Label1->Caption = "Mappars";
  Label1->Tag = 3;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++){
    thisPar = (*itPar).second;
    if(thisPar != NULL){
      S = (*itPar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisPar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::declvar1Click(TObject *Sender){
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "declvar (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapdeclvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      if(!Not_Obs(S, itMap->second.first))
        SS += " *** Observation ****";

      SS = String(String(S.c_str()) + " " + SS);
      if(Memo1->Lines->IndexOf(SS) == -1)
        Memo1->Lines->Add(SS);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::ListBox1Click(TObject *Sender)
{

  if(Label1->Tag == 1){
    ClassVar *thisVar  = (ClassVar *) ListBox1->Items->Objects[ListBox1->ItemIndex];
    if(thisVar != NULL){
      Memo1->Lines->Add("module:    " + String(thisVar->module.c_str()));
      Memo1->Lines->Add("DLLName:   " + String(thisVar->DLLName.c_str()));
      Memo1->Lines->Add("root:        " + String(thisVar->root.c_str()));
      Memo1->Lines->Add("name:      " + String(thisVar->name.c_str()));
      Memo1->Lines->Add("help:      " + String(thisVar->help.c_str()));
      Memo1->Lines->Add("units:     " + String(thisVar->units.c_str()));
      Memo1->Lines->Add("this:      " + Pnt((int) thisVar));
      Memo1->Lines->Add("  ");
      Memo1->Lines->Add("dimen:     " + String(dimens[thisVar->dimen]));
      Memo1->Lines->Add("dim:       " + String(thisVar->dim));
      Memo1->Lines->Add("dimMax:       " + String(thisVar->dimMax));
      Memo1->Lines->Add("lay:       " + String(thisVar->lay));
      Memo1->Lines->Add("StatVar:   " + String(T_F[thisVar->StatVar]));
      Memo1->Lines->Add("InGroup:       " + String(thisVar->InGroup));
      Memo1->Lines->Add("Visibility:     " + String(V_D_H[thisVar->visibility]));
      Memo1->Lines->Add("optional:  " + String(T_F[thisVar->optional]));
      Memo1->Lines->Add("PointPlot: " + String(T_F[thisVar->PointPlot]));
      Memo1->Lines->Add("  ");
      Memo1->Lines->Add("values:     " + Pnt((int) thisVar->values));
      Memo1->Lines->Add("ivalues:    " + Pnt((int) thisVar->ivalues));
      Memo1->Lines->Add("layvalues:  " + Pnt((int) thisVar->layvalues));
      Memo1->Lines->Add("ilayvalues: " + Pnt((int) thisVar->ilayvalues));
      Memo1->Lines->Add("  ");
      Memo1->Lines->Add("varType:   " + String(varTypes[thisVar->varType]));
      Memo1->Lines->Add("HRU_OBS_indexed:   " + String(thisVar->HRU_OBS_indexed));
      Memo1->Lines->Add("FunctVar: " + Pnt((int) thisVar->FunctVar));
      Memo1->Lines->Add("No_ReadVar: " + String(thisVar->No_ReadVar));
      Memo1->Lines->Add("FunctKind: " + String(Fun[thisVar->FunKind]));
      Memo1->Lines->Add("CustomFunctName: " + thisVar->CustomFunctName);
      Memo1->Lines->Add("nfreq:     " + String(T_F[thisVar->nfreq]));
      Memo1->Lines->Add("variation_set:  " + String(thisVar->variation_set));

      if(thisVar->FileData){
        Memo1->Lines->Add("");
        Memo1->Lines->Add("File name:             " + String(thisVar->FileData->DataFileName.c_str()));
        Memo1->Lines->Add("File Description:      " + String(thisVar->FileData->Description.c_str()));
        Memo1->Lines->Add("offset:                " + String(thisVar->offset));
        Memo1->Lines->Add("observation dimension: " + String(thisVar->cnt));
        Memo1->Lines->Add("DataCnt:               " + String(thisVar->FileData->DataCnt));
        Memo1->Lines->Add("FilterCnt:             " + String(thisVar->FileData->FilterCnt));
        Memo1->Lines->Add("Frequency:             " + String(thisVar->FileData->Freq));
        Memo1->Lines->Add("FirstFile:             " + String(T_F[thisVar->FileData->FirstFile]));
      }

      Memo1->Lines->Add(AnsiString::StringOfChar('*', 25));
      Memo1->Lines->Add("");
    }
  }
  else if(Label1->Tag == 2){
    ClassModule *thisMod  = (ClassModule *) ListBox1->Items->Objects[ListBox1->ItemIndex];
    ClassMacro *thisMacro;
    if(thisMod != NULL){
      if(thisMod->DLLName == "Macro")
        thisMacro  = dynamic_cast<ClassMacro *> (thisMod);

      Memo1->Lines->Add("module:     " + String(thisMod->Name.c_str()));
      Memo1->Lines->Add("Root:       " + String(thisMod->NameRoot.c_str()));
      Memo1->Lines->Add("DLLName:    " + String(thisMod->DLLName.c_str()));
      Memo1->Lines->Add("Version:    " + String(thisMod->Version.c_str()));
      Memo1->Lines->Add("Description:    " + String(thisMod->Description.c_str()));
      Memo1->Lines->Add("nhru:       " + String(thisMod->nhru));
      Memo1->Lines->Add("Level:      " + String(LVLStrings[thisMod->Lvl].c_str()));
      Memo1->Lines->Add("PeerRank:   " + String(thisMod->PeerRank));
      Memo1->Lines->Add("PeerVar:    " + String(thisMod->PeerVar.c_str()));
      Memo1->Lines->Add("GroupCnt:   " + String(thisMod->GroupCnt));
      Memo1->Lines->Add("StructCnt:  " + String(thisMod->StructCnt));
      Memo1->Lines->Add("  ");
      Memo1->Lines->Add("variation:  " + String(thisMod->variation));
      Memo1->Lines->Add("variation_max:  " + String(thisMod->variation_max));
      Memo1->Lines->Add("  ");

      if(thisMod->DLLName == "Macro"){
        if(thisMod->isGroup){
          Memo1->Lines->Add("isGroup:    " + String(T_F[thisMod->isGroup]));
          Memo1->Lines->Add("modules:");
          for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
            Memo1->Lines->Add(" " + thisMacro->GrpStringList->Strings[ii]);
        }

        else if(thisMod->isStruct){
          Memo1->Lines->Add("isStruct:   " + String(T_F[thisMod->isStruct]));
          Memo1->Lines->Add("modules:");
          for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii)
            Memo1->Lines->Add(" " + thisMacro->GrpStringList->Strings[ii]);
        }

        else{
          Memo1->Lines->Add("isMacro: " );
          Memo1->Lines->Add("declarations:");
          for(int ii = Global::MacroModulesList->IndexOf(thisMacro->Name.c_str()) + 1; ii < thisMacro->Begin - 1; ++ii)
            Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);

          Memo1->Lines->Add("code:");
          for(int ii = thisMacro->Begin; ii < thisMacro->End; ++ii)
            Memo1->Lines->Add(" " + Global::MacroModulesList->Strings[ii]);
        }
        Memo1->Lines->Add(" ");
        Memo1->Lines->Add("ObsModule:     " + Pnt((int) thisMacro->ObsModule));
        Memo1->Lines->Add(" ");
      }

      Memo1->Lines->Add("ModuleIndx: " + String(thisMod->ModuleIndx));
      Memo1->Lines->Add("Class ID:   " + String(thisMod->ID.c_str()));
      Memo1->Lines->Add("Module nhru:" + String(thisMod->nhru));

      Memo1->Lines->Add(AnsiString::StringOfChar('*', 25));
      Memo1->Lines->Add("");
    }
  }
  else if(Label1->Tag == 3){
    ClassPar *thisPar  = (ClassPar *) ListBox1->Items->Objects[ListBox1->ItemIndex];
    if(thisPar != NULL){
      Memo1->Lines->Add("module:   " + String(thisPar->module.c_str()));
      Memo1->Lines->Add("basemodule:   " + String(thisPar->basemodule.c_str()));
      Memo1->Lines->Add("param:    " + String(thisPar->param.c_str()));
      Memo1->Lines->Add("help:     " + String(thisPar->help.c_str()));
      Memo1->Lines->Add("units:    " + String(thisPar->units.c_str()));
      Memo1->Lines->Add("this:     " + Pnt((int) thisPar));
      Memo1->Lines->Add("  ");
      Memo1->Lines->Add("varType:  " + String(varTypes[thisPar->varType]));
      Memo1->Lines->Add("dimen:    " + String(dimens[thisPar->dimen]));
      Memo1->Lines->Add("dim:      " + String(thisPar->dim));
      Memo1->Lines->Add("lay:      " + String(thisPar->lay));
      Memo1->Lines->Add("Visibility:     " + String(V_D_H[thisPar->visibility]));
      Memo1->Lines->Add("Inhibit_share:     " + String(Linked[thisPar->Inhibit_share]));
      Memo1->Lines->Add("variation_set:  " + String(thisPar->variation_set));
      Memo1->Lines->Add("Identical:      " + Pnt((int) thisPar->Identical));

      Memo1->Lines->Add(AnsiString::StringOfChar('*', 25));
      Memo1->Lines->Add("");
    }
  }
  else if(Label1->Tag == 4){
    ClassModule *thisMod  = (ClassModule *) ListBox1->Items->Objects[ListBox1->ItemIndex];
    ExtractGroupFile(Sender, thisMod);
  }
  else if(Label1->Tag == 5){ // Rename Group
    int ii = ListBox1->ItemIndex;
    Edit->Text = ListBox1->Items->Strings[ii];

    Edit->Visible = true;
    Edit->SetFocus();
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::getvar1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "getvar (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapgetvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
//      SS = itMap->second.first + " " + itMap->second.second;
//      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::putvar1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "putvar (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapputvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
//      SS = itMap->second.first + " " + itMap->second.second;
//      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::readvar1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "readvar (variation visibility)";
  Label1->Tag = 0;

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapreadvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
//      SS = itMap->second.first + " " + itMap->second.second;
//      SS = String(S.c_str()) + " " + SS;
      if(Memo1->Lines->IndexOf(SS) < 0)
        Memo1->Lines->Add(SS);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::declobs1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "declobs (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapdeclobs.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
//      SS = itMap->second.first + " " + itMap->second.second;
//      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::declpar1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "declpar (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapdeclpar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::AllModulesList1Click(TObject *Sender)
{
  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "AllModulesList";
  Label1->Tag = 2;

  for(int ii = 0; ii < Global::AllModulesList->Count; ++ii){
    String S = Global::AllModulesList->Strings[ii];
    ClassModule* thisModule = (ClassModule*) Global::AllModulesList->Objects[ii];
    if(thisModule->variation){
      String AA = "#0";
      AA[2] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }
    ListBox1->Items->AddObject(S, Global::AllModulesList->Objects[ii]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::OurModulesList1Click(TObject *Sender)
{
  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "OurModulesList";
  Label1->Tag = 2;

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii]; // add variation
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    if(thisModule->variation != 0){
      String AA("#0");
      AA[2] += log(thisModule->variation)/log(2) + 1;
      S += AA;
    }
    ListBox1->Items->AddObject(S, Global::OurModulesList->Objects[ii]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Label1Click(TObject *Sender)
{
  Execution1->Enabled = true;
  Chart1->Enabled = true;
  Bld1->Enabled = true;
  Lists1->Enabled = true;
  Global1->Enabled = true;
  AKA2->Enabled = true;
  Hierarchy1->Enabled = true;
  ExtractGroup->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::declstat1Click(TObject *Sender)
{
  String S, SS;
  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  Label1->Caption = "declstat (variation visibility)";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    range = Global::Mapdeclstat.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      VandP V; V.Set(itMap->second.second);
      SS = itMap->second.first + " " + V.GetV() + " " + V.GetP();
      Memo1->Lines->Add(String(String(S.c_str()) + " " + SS));
//      SS = itMap->second.first + " " + itMap->second.second;
//      Memo1->Lines->Add(SS);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Global1Click(TObject *Sender)
{
  Label1->Caption = "Global";
  Label1->Tag = 0;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  Memo1->Lines->Add("Global::Freq:     " + String(Global::Freq));
  Memo1->Lines->Add("Global::Interval: " + String(Global::Interval));
  Memo1->Lines->Add("");
  Memo1->Lines->Add("Global::nhru:   " + String(Global::nhru));
  Memo1->Lines->Add("Global::maxhru: " + String(Global::maxhru));
  Memo1->Lines->Add("Global::nlay:   " + String(Global::nlay));
  Memo1->Lines->Add("Global::maxlay: " + String(Global::maxlay));
  Memo1->Lines->Add("Global::nobs:   " + String(Global::nobs));
  Memo1->Lines->Add("Global::maxobs: " + String(Global::maxobs));
  Memo1->Lines->Add("");
  Memo1->Lines->Add("Global::GroupCntTrk: " + String(Global::GroupCntTrk));
  Memo1->Lines->Add("Global::StructCntTrk: " + String(Global::StructCntTrk));
  Memo1->Lines->Add("");
  Memo1->Lines->Add("DTstart:  " + String(Global::DTstart));
  Memo1->Lines->Add("DTend:    " + String(Global::DTend));
  Memo1->Lines->Add("DTnow:    " + String((double) Global::DTnow));
  Memo1->Lines->Add("DTmin:    " + String(Global::DTmin));
  Memo1->Lines->Add("DTmax:    " + String(Global::DTmax));
  Memo1->Lines->Add("DTindx:   " + String(Global::DTindx));
  Memo1->Lines->Add("");
  Memo1->Lines->Add("IndxMin:    " + String(Global::IndxMin));
  Memo1->Lines->Add("IndxMax:    " + String(Global::IndxMax));
  Memo1->Lines->Add("");

  Memo1->Lines->Add("BuildFlag:    " + String(Global::BuildFlag));
  Memo1->Lines->Add("OBS_AS_IS:      " + String(Global::OBS_AS_IS));
  Memo1->Lines->Add("RH_EA_obs:      " + String(Global::RH_EA_obs));
  Memo1->Lines->Add("*OBS_AS_IS:      " + String(Global::OBS_AS_IS));
  Memo1->Lines->Add("");

  Memo1->Lines->Add("**OBS_ELEV:    " + Pnt((int) Global::OBS_ELEV));
  Memo1->Lines->Add("**HRU_OBS:    " + Pnt((int) Global::HRU_OBS));
  Memo1->Lines->Add("**obs_t:    " + Pnt((int) Global::obs_t));
  Memo1->Lines->Add("**obs_ea:    " + Pnt((int) Global::obs_ea));
  Memo1->Lines->Add("**obs_rh:    " + Pnt((int) Global::obs_rh));
  Memo1->Lines->Add("**obs_t_obs:    " + Pnt((int) Global::obs_t_obs));
  Memo1->Lines->Add("*lapse_rate:    " + Pnt((int) Global::lapse_rate));
  Memo1->Lines->Add("*hru_elev:    " + Pnt((int) Global::hru_elev));
  Memo1->Lines->Add("*Warming_t:      " + Pnt((int) Global::Warming_t));
  Memo1->Lines->Add("*Warming_p:      " + Pnt((int) Global::Warming_p));
  Memo1->Lines->Add("*RH_VP_flag:      " + Pnt((int) Global::RH_VP_flag));
  Memo1->Lines->Add("*RH_VP_flag2:      " + Pnt((int) Global::RH_VP_flag2));

  Memo1->Lines->Add("");

  Memo1->Lines->Add(AnsiString::StringOfChar('*', 25));
  Memo1->Lines->Add("");
}
//---------------------------------------------------------------------------

void __fastcall TRprt::AKA1Click(TObject *Sender)
{
  if(!Global::MapAKA.empty()) {

    Label1->Caption = "AKA list";
    Label1->Tag = 0;

    ListBox1->Clear();
    Memo1->Lines->Clear();

    Mapstr2::iterator it;

    for (it = Global::MapAKA.begin(); it !=  Global::MapAKA.end(); ++it) {
      string Var = (*it).first + " :-> " + (*it).second; // module, type and name
      Memo1->Lines->Add(Var.c_str());
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MacroModulesList1Click(TObject *Sender)
{
  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "MacroModulesList";
  Label1->Tag = 0;

  for(int ii = 0; ii < Global::MacroModulesList->Count; ++ii){
    Memo1->Lines->Add(Global::MacroModulesList->Strings[ii]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Chart1Click(TObject *Sender)
{
  ClassVar *thisVar;
  MapVar::iterator itVar;
  String S;

  Label1->Caption = "Chart";
  Label1->Tag = 1;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(int ii = 0; ii < Main->Chart->SeriesCount(); ii++) {
    S = Main->Chart->Series[ii]->Title;
    if(S.Length() == 0) S = Main->Chart->Series[ii]->Name;
    ClassVar *thisVar = (ClassVar*) Main->Chart->Series[ii]->Tag;
    ListBox1->Items->AddObject(S, (TObject*) thisVar);
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::HierarchyList(TObject *Sender)
{
  String S, SS, S1, S2, Entry;
  bool Self;
  long Indx, offset = ListBox1->Items->Count, Act_ii, List_start;

  pair<Mapstr::iterator, Mapstr::iterator> range;
  Mapstr::iterator itMap;

  offset = ListBox1->Count;

  for(long ii = 0; ii < Global::OurModulesList->Count; ++ii){
    ClassModule* thisModule = (ClassModule*) Global::OurModulesList->Objects[ii];
    long Variation = thisModule->variation;
    String S = Global::OurModulesList->Strings[ii];

    if(thisModule->DLLName == "Macro")
      Expand_Grp_to_OurModuleList(Sender, ii); // Changes OurModulelist to GrpStringList, calls decl and then restores current OurModulelist

    String AA = "";
    if(Variation){
      AA = "#0";
      AA[2] += log(thisModule->variation)/log(2) + 1;
    }

    ListBox1->AddItem(S+AA, (TObject*) 0);
    Act_ii = ListBox1->Count-1;

    if(!thisModule->PeerVar.IsEmpty()){
      S1 = thisModule->NameRoot.c_str(); // module
      S2 = thisModule->PeerVar.c_str(); // variable

      Indx = findvar(Sender, S, S2, Self);

      if(Indx > -1){
        long Indx2 = findstatvar(Sender, S, S2, Self);
        Entry = String(String(S.c_str()) + " " + Global::OurModulesList->Strings[Indx] + "->" + S2 + " *** Peer Variable");
        if(Indx2 == -1){ // not state variable
          int Twos = (int) ListBox1->Items->Objects[Act_ii];

          int Or = Twos | long(powl(2, Indx));
          (TObject *) ListBox1->Items->Objects[Act_ii] = (TObject *)(Or);
        }
        else
          Entry = Entry + " *** Peer Variable";

        Memo1->Lines->Add(Entry);

      }
    }

    range = Global::Mapgetvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {

      SS = itMap->second.first;
      int jj = SS.Pos(" ");
      S1 = SS.SubString(1, jj-1); // module
      S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
      if(S1 == "*"){
        Indx = findvar(Sender, S, S2, Self);
      }
      else
        Indx = Global::OurModulesList->IndexOf(S1);

      if(Indx > -1){
        long Indx2 = findstatvar(Sender, S, S2, Self);
        Entry = String(String(S.c_str()) + " " + itMap->second.first + " from " + Global::OurModulesList->Strings[Indx]);
        if(Indx2 == -1){ // not state variable
          int Twos = (int) ListBox1->Items->Objects[Act_ii];

          int Or = Twos | long(powl(2, Indx));
          (TObject *) ListBox1->Items->Objects[Act_ii] = (TObject *)(Or);
        }
        else
          Entry = Entry + " *** State Variable";

        Memo1->Lines->Add(Entry);
      }
    } // for

    range = Global::Mapputvar.equal_range(S);
    for(itMap = range.first; itMap != range.second; ++itMap) {
      SS = itMap->second.first;
      int jj = SS.Pos(" ");
      S1 = SS.SubString(1, jj-1); // module
      S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
      if(S1 == "*"){
        Indx = findvar(Sender, S, S2, Self);
      }
      else
        Indx = Global::OurModulesList->IndexOf(S1);

      if(Indx > -1) // otherwise in group
        Memo1->Lines->Add(String(String(S.c_str()) + " " + itMap->second.first + " from " + Global::OurModulesList->Strings[Indx]) + " *** Put");
    }
  } // for

  bool OK = true;
  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){

    int Twos = (int) ListBox1->Items->Objects[ii + offset];
    int N = powl(2, ii);
    if(Twos > N)
      OK = false;

    char P[80];
    strcpy(P, ListBox1->Items->Strings[ii + offset].c_str());

    TVarRec args[3] = {N, P, Twos};

    String X = Format("%6d  %-30s  %-8d", args, 2);

    ListBox1->Items->Strings[ii + offset] =  X;
  }

  ListBox1->Items->Add("");
  if(OK)
    ListBox1->Items->Add("Module order is good");
  else
    ListBox1->Items->Add("Module Order is not correct");

}
//---------------------------------------------------------------------------

void __fastcall TRprt::Hierarchy1Click(TObject *Sender)
{
  ClassModule *thisModule;
  ClassMacro *thisMacro;
  long Variation;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "hierarchy";
  Label1->Tag = 0;

  HierarchyList(Sender);

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    long Indx = Global::AllModulesList->IndexOf(S);
    thisModule  = (ClassModule *) Global::AllModulesList->Objects[Indx];
    if(thisModule->DLLName == "Macro"){
      thisMacro  = dynamic_cast<ClassMacro *> (thisModule);
      if(thisModule->isGroup){
        ListBox1->Items->Add("");
        ListBox1->Items->Add(S);
        ListBox1->Items->Add("");
        Memo1->Lines->Add(" ");
        Memo1->Lines->Add(S);
        Memo1->Lines->Add(" ");

        TStringList *GrpModuleList = new TStringList;
        TStringList *TempModuleList = new TStringList;
        long *Oldvariation = new long [thisMacro->GrpStringList->Count];

        for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii){
         GrpModuleList->Add(thisMacro->GrpStringList->Strings[ii]);
        }

        for(int ii = 0; ii < GrpModuleList->Count; ++ii) {
          int Pos = GrpModuleList->Strings[ii].Pos("#");
          if(Pos){
            Variation = pow(2, GrpModuleList->Strings[ii][Pos+1] - char('1'));
            GrpModuleList->Strings[ii] = GrpModuleList->Strings[ii].SubString(1, Pos-1);
          }
          else
            Variation = 0;

          int jj = Global::AllModulesList->IndexOf(GrpModuleList->Strings[ii]);

          if(jj > -1){ // Update group Module address
            GrpModuleList->Objects[ii] = Global::AllModulesList->Objects[jj];
            ClassModule* thisModule = (ClassModule*) GrpModuleList->Objects[ii];
            Oldvariation[ii] = thisModule->variation; // save original variation
            thisModule->variation = Variation;
          }
        }

        Global::Mapgetvar.clear();
        Global::Mapputvar.clear();
        Global::Mapreadvar.clear();
        Global::Mapdeclvar.clear();
        Global::Mapdeclstat.clear();
        Global::Mapdeclpar.clear();
        Global::Mapdeclobs.clear();

        Global::BuildFlag = CRHM::BUILD; // default value

        TempModuleList->Assign(Global::OurModulesList);
        Global::OurModulesList->Assign(GrpModuleList);

        for(int ii = 0; ii < Global::OurModulesList->Count; ++ii)
          ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();

        HierarchyList(Sender);

        for(int ii = 0; ii < GrpModuleList->Count; ++ii) {
          ClassModule* thisModule = (ClassModule*) GrpModuleList->Objects[ii];
          thisModule->variation = Oldvariation[ii]; // restore original variation
        }

        Global::OurModulesList->Assign(TempModuleList);

        Global::Mapgetvar.clear();
        Global::Mapputvar.clear();
        Global::Mapreadvar.clear();
        Global::Mapdeclvar.clear();
        Global::Mapdeclstat.clear();
        Global::Mapdeclpar.clear();
        Global::Mapdeclobs.clear();


        for(int ii = 0; ii < Global::OurModulesList->Count; ++ii)
          ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();

        Global::BuildFlag = CRHM::DECL; // model loaded

        delete GrpModuleList;
        delete TempModuleList;
        delete[] Oldvariation;

      } // isGroup
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Expand_Grp_to_OurModuleList(TObject *Sender, long ii){

  ClassModule *thisModule;
  ClassMacro *thisMacro;
  long Variation;

  String S = Global::OurModulesList->Strings[ii];
  long Indx = Global::AllModulesList->IndexOf(S);
  thisModule  = (ClassModule *) Global::AllModulesList->Objects[Indx];
  thisMacro  = dynamic_cast<ClassMacro *> (thisModule);

  if(thisMacro->GrpStringList == NULL || thisMacro->GrpStringList->Count <= 0) return; // uses no modules

  TStringList *GrpModuleList = new TStringList;
  TStringList *TempModuleList = new TStringList;
  long *Oldvariation = new long [thisMacro->GrpStringList->Count];

  for(int ii = 0; ii < thisMacro->GrpStringList->Count; ++ii){
   GrpModuleList->Add(thisMacro->GrpStringList->Strings[ii]);
  }

  for(int ii = 0; ii < GrpModuleList->Count; ++ii) {
    int Pos = GrpModuleList->Strings[ii].Pos("#");
    if(Pos){
      Variation = pow(2, GrpModuleList->Strings[ii][Pos+1] - char('1'));
      GrpModuleList->Strings[ii] = GrpModuleList->Strings[ii].SubString(1, Pos-1);
    }
    else
      Variation = 0;

    int jj = Global::AllModulesList->IndexOf(GrpModuleList->Strings[ii]);

    if(jj > -1){ // Update group Module address
      GrpModuleList->Objects[ii] = Global::AllModulesList->Objects[jj];
      ClassModule* thisModule = (ClassModule*) GrpModuleList->Objects[ii];
      Oldvariation[ii] = thisModule->variation; // save original variation
      thisModule->variation = Variation;
    }
  }

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::BuildFlag = CRHM::BUILD; // default value

  TempModuleList->Assign(Global::OurModulesList);
  Global::OurModulesList->Assign(GrpModuleList);

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii)
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();

  for(int ii = 0; ii < GrpModuleList->Count; ++ii) {
    ClassModule* thisModule = (ClassModule*) GrpModuleList->Objects[ii];
    thisModule->variation = Oldvariation[ii]; // restore original variation
  }

  Global::OurModulesList->Assign(TempModuleList);

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::BuildFlag = CRHM::DECL; // model loaded

  delete GrpModuleList;
  delete TempModuleList;
  delete[] Oldvariation;
}

//---------------------------------------------------------------------------

long __fastcall TRprt::findvar(TObject *Sender, String who, String what, bool &Self){
  Mapstr::iterator itMap;
  int Pos;
  String S1, S2;
  long GrpSrc = -1;

  for(itMap = Global::Mapdeclvar.begin(); itMap !=  Global::Mapdeclvar.end(); ++itMap) {
    if(itMap->second.first == what){  // root variable
      if(itMap->first == who){
        Self = true;
        return (-1);
      }
      else
        return (Global::OurModulesList->IndexOf(itMap->first));
    }
  }

  for(itMap = Global::Mapdeclvar.begin(); itMap !=  Global::Mapdeclvar.end(); ++itMap) {
    if(Pos = what.Pos("@")){ // remove @... from module rquiring input
      S1 = what.SubString(1, Pos-1);
      if(itMap->second.first == S1)
        return(Global::OurModulesList->IndexOf(itMap->first));
    }
    else
      S1 = what;

    if(Pos = itMap->second.first.Pos("@")){ // remove @... from possible source module
      S2 = itMap->second.first.SubString(1, Pos-1);
      if(S1 == S2){
        if(itMap->second.first == what)
          return(Global::OurModulesList->IndexOf(itMap->first));
        else
          GrpSrc = Global::OurModulesList->IndexOf(itMap->first);
      }
    }
  }
  
  if(GrpSrc != -1)
    return GrpSrc;
  else
    return (-1);
}
//---------------------------------------------------------------------------

long __fastcall TRprt::findstatvar(TObject *Sender, String who, String what, bool &Self){
  Mapstr::iterator itMap;
  int Pos;
  String S1, S2;

  for(itMap = Global::Mapdeclstat.begin(); itMap !=  Global::Mapdeclstat.end(); ++itMap) {
    String SS = itMap->second.first;
    int jj = SS.Pos(" ");
    String S2 = SS.SubString(jj+1, SS.Length() - jj); // variable
    if(S2 == what){
      if(itMap->first == who)
        Self = true;
      else
          return (Global::OurModulesList->IndexOf(itMap->first));
    }

    if(Pos = what.Pos("@")){
      S1 = what.SubString(1, Pos-1);
      if(S2 == S1)
        return(Global::OurModulesList->IndexOf(itMap->first));
    }
  }
  
  return (-1);
}

void __fastcall TRprt::AKA2Click(TObject *Sender)
{
  Label1->Caption = "active AKAs";

  Global::ReportList = new TStringList; //
  Global::ReportList->Sorted = true;

  Global::Mapgetvar.clear();
  Global::Mapputvar.clear();
  Global::Mapreadvar.clear();
  Global::Mapdeclvar.clear();
  Global::Mapdeclstat.clear();
  Global::Mapdeclpar.clear();
  Global::Mapdeclobs.clear();

  Global::BuildFlag = CRHM::BUILD; // default value

  for(int ii = 0; ii < Global::OurModulesList->Count; ii++)
    ((ClassModule*) Global::OurModulesList->Objects[ii])->decl();

  Global::BuildFlag = CRHM::DECL; // model loaded

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(long ii = 0; ii < Global::ReportList->Count; ++ii){
    Memo1->Lines->Add(Global::ReportList->Strings[ii]);
  }

  delete Global::ReportList;
  Global::ReportList = NULL;
}
//---------------------------------------------------------------------------



void __fastcall TRprt::DeclRootList1Click(TObject *Sender)
{
  Label1->Caption = "DeclRootList";

  if(Global::DeclRootList->Count <= 0){
    Application->MessageBox("A model must be run to gather data", "warning", MB_OK);
    return;
  }

  Label1->Tag = 0;
  ListBox1->Clear();
  Memo1->Lines->Clear();

  for(long ii = 0; ii < Global::DeclRootList->Count; ++ii){
    Memo1->Lines->Add(Global::DeclRootList->Strings[ii]);
  }
}
//---------------------------------------------------------------------------

bool __fastcall TRprt::Not_Obs(String Mod, String Var){

  pair<Mapstr::iterator, Mapstr::iterator> rangeIobs = Global::Mapreadvar.equal_range(Mod);

  for(Mapstr::iterator itMap = rangeIobs.first; itMap != rangeIobs.second; ++itMap)
    if(Var == itMap->second.first)
      return false;

  return true;
}
//---------------------------------------------------------------------------

String  __fastcall TRprt::Pnt(int P){
  if(!P)
    return "NULL";
  String Fred;
  Fred.printf(":%p", P);
  return Fred;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Mapvarsget1Click(TObject *Sender)
{
  ClassVar *thisVar;
  MapVar::iterator itVar;
  string S;

  Label1->Caption = "Mapvarsget";
  Label1->Tag = 1;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itVar = Global::MapVarsGet.begin(); itVar != Global::MapVarsGet.end(); itVar++){
    thisVar = (*itVar).second;
    if(thisVar != NULL){
      S = (*itVar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisVar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Mapobsget1Click(TObject *Sender)
{
  ClassVar *thisVar;
  MapVar::iterator itVar;
  string S;

  Label1->Caption = "Mapobsget";
  Label1->Tag = 1;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itVar = Global::MapObsGet.begin(); itVar != Global::MapObsGet.end(); itVar++){
    thisVar = (*itVar).second;
    if(thisVar != NULL){
      S = (*itVar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisVar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::Mapvarsput1Click(TObject *Sender)
{
  ClassVar *thisVar;
  MapVar::iterator itVar;
  string S;

  Label1->Caption = "Mapvarsput";
  Label1->Tag = 1;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itVar = Global::MapVarsPut.begin(); itVar != Global::MapVarsPut.end(); itVar++){
    thisVar = (*itVar).second;
    if(thisVar != NULL){
      S = (*itVar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisVar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MapSharedpars1Click(TObject *Sender)
{
  ClassPar *thisPar;
  MapPar::iterator itPar;
  string S;

  Label1->Caption = "MapSharedpars";
  Label1->Tag = 3;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  for (itPar = Global::SharedMapPars.begin(); itPar != Global::SharedMapPars.end(); itPar++){
    thisPar = (*itPar).second;
    if(thisPar != NULL){
      S = (*itPar).first;
      ListBox1->AddItem(S.c_str(), (TObject*) thisPar);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::ExtractGroupClick(TObject *Sender) {

  ClassModule *thisMod;

  ListBox1->Clear();
  Memo1->Lines->Clear();

  Label1->Caption = "ExtractGroup";
  Label1->Tag = 4;

  for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
    String S = Global::OurModulesList->Strings[ii];
    long Indx = Global::AllModulesList->IndexOf(S);
    thisMod  = (ClassModule *) Global::AllModulesList->Objects[Indx];
    if(thisMod->isGroup)
          ListBox1->AddItem(S, (TObject*) thisMod);
  } // for
}
//---------------------------------------------------------------------------

void __fastcall TRprt::ExtractGroupFile(TObject *Sender, ClassModule *thisModule) {

  ClassMacro *thisMacro;
  String S, SS;
  long Variation;
  MapPar::iterator itPar;
  ClassPar *thisPar;

  if(thisModule->isGroup)
    thisMacro  = dynamic_cast<ClassMacro *> (thisModule);
  else
    return;

  Memo1->Lines->Clear();

  S = thisMacro->Name.c_str();

  Memo1->Lines->Add("*** extracted group: '" + S + "' from '" + Main->OpenDialogPrj->FileName + "' ***");

  Memo1->Lines->Add("######");
  Memo1->Lines->Add("Dimensions:");
  Memo1->Lines->Add("######");
  Memo1->Lines->Add(String("nhru " + String(Add_NHRU(S, Global::MacroModulesList))));
  Memo1->Lines->Add(String("nlay " + String(Global::nlay)));
  Memo1->Lines->Add(String("nobs " + String(1)));
  Memo1->Lines->Add("######");

  Memo1->Lines->Add("Macros:");
  Memo1->Lines->Add("######");

  long MacroPos = Memo1->Lines->Count;
  Memo1->Lines->Add("######");

  Memo1->Lines->Add("Modules:");
  Memo1->Lines->Add("######");

  list<ModulePtr> ::iterator iterM;
  iterM = ((ClassMacro *) thisModule)->Modules.begin();
  while(iterM != ((ClassMacro *) thisModule)->Modules.end()) {
    boost::weak_ptr<ClassModule> MP((*iterM));
    S = (*iterM)->NameRoot.c_str();

    if((*iterM)->DLLName == "Macro")
      AddMacroCode(S, Global::MacroModulesList, Memo1->Lines, MacroPos);

    if((*iterM)->variation > 0){
      String AA("#0 ");
      AA[2] += log((*iterM)->variation)/log(2) + 1;
      S = S + AA.c_str();
    }
    else
      S = S + " ";

    S = S + (*iterM)->DLLName + " ";
    S = S + (*iterM)->Version;
    Memo1->Lines->Add(S);
    ++iterM;
  } // while

  Memo1->Lines->Add("######");

  Main->RemoveSharedParams();
  
  Memo1->Lines->Add("Parameters:");
  Memo1->Lines->Add("######");

  S = thisMacro->Name.c_str();

  for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
    thisPar = (*itPar).second;
    if(S == thisPar->module.c_str()){
      if(thisPar->param == "HRU_group")
        continue;

      String S = String("Shared " + String(thisPar->param.c_str()));

      if(thisPar->varType != CRHM::Txt)
        S += "\t<\t" + FloatToStrF(thisPar->minVal, ffGeneral, 4, 0)+ "\t" + FloatToStrF(thisPar->maxVal, ffGeneral, 4, 0) + "\t>";

      Memo1->Lines->Add(S);

      for(int jj = 0; jj<thisPar->lay; jj++) {
        S = "";
        for(int ii = 0; ii < thisPar->dim; ii++) {
          if(thisPar->varType == CRHM::Float)
              S = S + FloatToStrF(thisPar->layvalues[jj][ii], ffGeneral, 4, 0) + "\t";
          else if(thisPar->varType == CRHM::Int)
              S = S + FloatToStrF(thisPar->ilayvalues[jj][ii], ffFixed, 8, 0) + "\t";
          else if(thisPar->varType == CRHM::Txt)
            if(thisPar->Strings->Count > ii)
              S = S + "'" + thisPar->Strings->Strings[ii] + "'\t";
            else
              S = "''\t"; // handle null string

          if(ii%16 == 15) {
            Memo1->Lines->Add(S);
            S = "";
          }
        } // for dim
        if(!S.IsEmpty()) {Memo1->Lines->Add(S); S = "";}
      } // for layers
      if(!S.IsEmpty()) Memo1->Lines->Add(S);
    }
  } // for MapPars

  Memo1->Lines->Add("######");

  Main->SqueezeParams(Sender);  // converts identical parameters to shared parameters
}

void __fastcall TRprt::AddMacroCode(String S, TStringList *MacroModulesList, TStrings* Memo1, long &MacroPos){

  for (int ii = 0; ii < MacroModulesList->Count; ++ii){
    if(MacroModulesList->Strings[ii].Pos(S)){
      Memo1->Insert(MacroPos++, "'" + MacroModulesList->Strings[ii] + "'");
      do{
        ++ii;
        Memo1->Insert(MacroPos++, "'" + MacroModulesList->Strings[ii] + "'");
      }
      while(!(MacroModulesList->Strings[ii].Pos("end") && MacroModulesList->Strings[ii].Length() == 3) && ii < MacroModulesList->Count-1);
      break;
    }
  }
}

long __fastcall TRprt::Add_NHRU(String S, TStringList *MacroModulesList){

  for (int ii = 0; ii < MacroModulesList->Count; ++ii){
    if(MacroModulesList->Strings[ii].Pos(S)){
      String Trim = MacroModulesList->Strings[++ii].TrimLeft();
      long len = Trim.Length();
      if(len < 11)
        return Global::nhru;
      else{
        long n = StrToInt(Trim.SubString(11, len - 10));
        if(n <= 0)
          return Global::nhru;
        else
          return n;
      }
    }
  }
}
void __fastcall TRprt::RenameGroupClick(TObject *Sender){

  ClassModule *thisMod;

  if(!In_Rename){
    In_Rename = true;
    ListBox1->Clear();
    Memo1->Lines->Clear();

    Memo1->Lines->Add("");
    Memo1->Lines->Add("How to Rename groups in a project.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Ensure that current work is saved to a project in order not to lose earlier work.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Select group name to be changed.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Edit name and press enter. The esc key will discard current changes.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Repeat as necessary.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("When finished press 'RenameGroup' again to proceed to the next step.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Follow prompts to save/cancel changes and exit.");
    Memo1->Lines->Add("");
    Memo1->Lines->Add("Renamed group parameter values are kept. They do not revert to default values.");
    Memo1->Lines->Add("");

    Main->RemoveSharedParams(); // change shared parameters to module parameters

    Label1->Caption = "RenameGroup - Not finished";
    Label1->Tag = 5;

    for(int ii = 0; ii < Global::OurModulesList->Count; ++ii){
      String S = Global::OurModulesList->Strings[ii];
      long Indx = Global::AllModulesList->IndexOf(S);
      thisMod  = (ClassModule *) Global::AllModulesList->Objects[Indx];
      if(thisMod->isGroup)
        ListBox1->AddItem(S, (TObject*) thisMod);
    } // for
  }
  else{
    In_Rename = false;
    if(Rename_Changes){
      int result = Application->MessageBox("Do you want to save your changes to a project file?", "Group names have been changed.", MB_YESNO);
      if(result  == IDYES){

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
        Main->PrjSaveAsClick(Sender);
        Main->PrjCloseClick(Sender);
        Close();
      }
    }

//    Main->SqueezeParams(Sender);  // converts identical parameters to shared parameters
    ListBox1->Clear();
    Memo1->Lines->Clear();
    Rename_Changes = false;
  }
}

//---------------------------------------------------------------------------


void __fastcall TRprt::EditKeyPress(TObject *Sender, char &Key){

  ClassModule *thisMod;

  ClassVar *thisVar;
  MapVar::iterator itVar;

  ClassPar *thisPar;
  MapPar::iterator itPar;

  int ii = ListBox1->ItemIndex;
  int Indx;
  String Snew;
  string sold, snew;

  if(Key == VK_RETURN && Edit->Text != ListBox1->Items->Strings[ii]){

    ListBox1->Items->Delete(ii);
    ListBox1->Items->Insert(ii, Edit->Text);
    
    Snew = ListBox1->Items->Strings[ii];
    snew = Snew.c_str();

    Key = 0;
    Edit->Visible = false;

// Rename groups

    String S = Global::OurModulesList->Strings[ii];
    sold = S.c_str();
    Indx = Global::AllModulesList->IndexOf(S);
    thisMod  = (ClassModule *) Global::AllModulesList->Objects[Indx];
    if(thisMod->isGroup){
      Global::OurModulesList->Strings[ii] = Snew;
      thisMod->Name = Snew.c_str();
      thisMod->NameRoot = Snew.c_str();
      thisMod->ID = Snew.c_str();
// Change parameters

      for (itPar = Global::MapPars.begin(); itPar != Global::MapPars.end(); itPar++){
        thisPar = (*itPar).second;
        if(thisPar != NULL){
          if(sold == thisPar->module){
            thisPar->module = snew;
          }
        }
      }

// Change variables

      for (itVar = Global::MapVars.begin(); itVar != Global::MapVars.end(); itVar++){
        thisVar = (*itVar).second;
        if(thisVar != NULL){
          if(sold == thisVar->module){
            thisVar->module = snew;
          }
        }
      }
    }

    for (int ii = 0; ii < Global::MacroModulesList->Count; ++ii){
      Indx = Global::MacroModulesList->Strings[ii].Pos(S);
        if(Indx > 0){
          String Line = Global::MacroModulesList->Strings[ii];
          Global::MacroModulesList->Strings[ii] = Line.SubString( 1, Indx-1) + Snew + Line.SubString(Indx + Line.Length() + 1, Line.Length());
        }
    }
    Rename_Changes = true;

}
  else if(Key == VK_ESCAPE){
    Key = 0;
    Edit->Visible = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::CheckNan1Click(TObject *Sender){

  if(Global::NaNcheck){
    Global::NaNcheck = false;
    CheckNan1->Caption = "NaN_check OFF";
  }
  else{
    Global::NaNcheck = true;
    CheckNan1->Caption = "NaN_check ON";
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::CheckNan1Init(TObject *Sender){

  if(Global::NaNcheck)
    CheckNan1->Caption = "NaN_check ON";
  else
    CheckNan1->Caption = "NaN_check OFF";
}
//---------------------------------------------------------------------------

void __fastcall TRprt::LOGVARLOAD1Click(TObject *Sender){
  if(Global::LOGVARLOAD){
    Global::LOGVARLOAD = false;
    LOGVARLOAD1->Caption = "LogVarLoad OFF";
  }
  else{
    Global::LOGVARLOAD = true;
    LOGVARLOAD1->Caption = "LogVarLoad ON";
  }
}
//---------------------------------------------------------------------------

void __fastcall TRprt::LOGVARLOAD1Init(TObject *Sender){

  if(Global::LOGVARLOAD)
    LOGVARLOAD1->Caption = "LogVarLoad ON";
  else
    LOGVARLOAD1->Caption = "LogVarLoad OFF";
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MSTime1Click(TObject *Sender){

  MSTime1->Checked = true;
  MMDDYYYY1->Checked = false;
  YYYYMMDD1->Checked = false;

  Global::TimeFormat = CRHM::MS;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::MMDDYYYY1Click(TObject *Sender){

  MSTime1->Checked = false;
  MMDDYYYY1->Checked = true;
  YYYYMMDD1->Checked = false;

  Global::TimeFormat = CRHM::MMDDYYYY;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::YYYYMMDD1Click(TObject *Sender){

  MSTime1->Checked = false;
  MMDDYYYY1->Checked = false;
  YYYYMMDD1->Checked = true;

  Global::TimeFormat = CRHM::YYYYMMDD;
}
//---------------------------------------------------------------------------

void __fastcall TRprt::FormShow(TObject *Sender)
{
  if(Global::LOGVARLOAD)
    LOGVARLOAD1->Caption = "LogVarLoad ON";
  else
    LOGVARLOAD1->Caption = "LogVarLoad OFF";

  if(Global::NaNcheck)
    CheckNan1->Caption = "NaN_check ON";
  else
    CheckNan1->Caption = "NaN_check OFF";

  switch (Global::TimeFormat){
    case CRHM::MS:
      MSTime1Click(Sender);
      break;
    case CRHM::MMDDYYYY:
      MMDDYYYY1Click(Sender);
      break;
    case CRHM::YYYYMMDD:
      YYYYMMDD1Click(Sender);
      break;
  }
}
//---------------------------------------------------------------------------

