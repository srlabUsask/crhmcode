// 12/20/13
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Log.h"
#include "DefCRHMGlobal.h"
#include <string>
#include "ClassModule.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;

TLogForm *LogForm;

//---------------------------------------------------------------------------
__fastcall TLogForm::TLogForm(TComponent* Owner)
  : TForm(Owner)
{
  LogForm->Warnings = 0;
  LogForm->Errors = 0;
  LogForm->DeclErrors = 0;

  if(!Printer()->Printers->Count){
    TMenuItem *FileItem3 = File->Items[3]; // Print1Click
    FileItem3->Enabled = false;
    TMenuItem *FileItem4 = File->Items[4]; // PrinterSetup1Click
    FileItem4->Enabled = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::LogError(CRHMException Except){
// No exceptions are thrown here.  Only in ClassCRHM LogError
  String S = Except.Message.c_str();
  switch (Except.Kind){
    case WARNING:
      LogForm->MemoLog->Lines->Add("Warning: " + S);
      LogForm->Warnings++;
      break;
    case ERR:
      LogForm->MemoLog->Lines->Add("Error:   " + S);
      LogForm->Errors++;
      break;
    case TERMINATE:
      LogForm->MemoLog->Lines->Add("Fatal Error: " + S);
      LogForm->Errors++;
      break;
    case DECLERR:
      LogForm->MemoLog->Lines->Add("Declaration Error: " + S);
      LogForm->DeclErrors++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::LogError(String S, TExcept Kind){

  switch (Kind){
    case WARNING:
      LogForm->MemoLog->Lines->Add("Warning: " + S);
      LogForm->Warnings++;
      break;
    case ERR:
      LogForm->MemoLog->Lines->Add("Error:   " + S);
      LogForm->Errors++;
      break;
    case TERMINATE:
      LogForm->MemoLog->Lines->Add("Fatal Error: " + S);
      LogForm->Errors++;
      break;
    case DECLERR:
      LogForm->MemoLog->Lines->Add("Declaration Error: " + S);
      LogForm->DeclErrors++;
      break;
    default:
      LogForm->MemoLog->Lines->Add("Unknown Error(should not happen): " + S);
      LogForm->DeclErrors++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::ClearAllLogs(void){

  LogForm->MemoLog->Clear();
  LogForm->MemoDebug->Clear();
  LogForm->Warnings = 0;
  LogForm->Errors = 0;
  LogForm->DeclErrors = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::ClearRunLogs(void){

  LogForm->MemoLog->Clear();
  LogForm->MemoDebug->Clear();
  LogForm->Warnings = 0;
  LogForm->Errors = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Exit1Click(TObject *Sender)
{
  this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::FileSaveClick(TObject *Sender)
{
  if(!SaveDialog1->FileName.IsEmpty())
    if(MemoSel == LOG)
      MemoLog->Lines->SaveToFile(SaveDialog1->FileName);
    else
      MemoDebug->Lines->SaveToFile(SaveDialog1->FileName);
  else FileSaveAsClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::FileSaveAsClick(TObject *Sender)
{
  SaveDialog1->Title = "Save As";

  if(MemoSel == LOG) {
    SaveDialog1->DefaultExt = "log";
    SaveDialog1->Filter = "Log Files (*.log)|*.log";
    if(SaveDialog1->Execute()){
      SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
      if(SaveDialog1->InitialDir.IsEmpty())
        SaveDialog1->InitialDir = GetCurrentDir();

      MemoLog->Lines->SaveToFile(SaveDialog1->FileName);
    }
  }
  else {
    SaveDialog1->DefaultExt = "txt";
    SaveDialog1->Filter = "Debug Files (*.txt)|*.txt";
    if(SaveDialog1->Execute()){
      SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
      if(SaveDialog1->InitialDir.IsEmpty())
        SaveDialog1->InitialDir = GetCurrentDir();

      MemoDebug->Lines->SaveToFile(SaveDialog1->FileName);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::MemoLogEnter(TObject *Sender)
{
  MemoSel = LOG;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::MemoDebugEnter(TObject *Sender)
{
  MemoSel = DEBUG;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::WMLogException(TMessage &Message)
{
  LogError(*((CRHMException*) Message.WParam));
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::WMLogException1(TMessage &Message)
{
  String S = *((String*) Message.WParam);
  LogError(S, (TExcept) *(int*) Message.LParam);
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::WMLogDebug(TMessage &Message)
{
  int POS;
  String S = *((String*) Message.WParam);
  if((S.SubString(1, 3)).Pos("HRU")){
    if(POS = S.Pos("_Grp"))
      S = S.SubString(1, 8) + S.SubString(++POS, 150);
  }
  else if(S.Pos("'")){ // handle "'"
    if(POS = S.Pos("_Grp"))
      S = S.SubString(++POS, S.Length());
  }
  LogForm->MemoDebug->Lines->Add(S);
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::ClearErrorsClick(TObject *Sender)
{
  LogForm->MemoLog->Clear();
  LogForm->Warnings = 0;
  LogForm->Errors = 0;
  LogForm->DeclErrors = 0;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::ClearDebugClick(TObject *Sender)
{
  LogForm->MemoDebug->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Print1Click(TObject *Sender) {

  int LineOnPage, LinesPerPage;
  int StartLine, EndLine, PagesInDoc, FromPage, ToPage;
  int x, y, z, PageNumber;
  bool NewPageRequired;

  TMemo *Memo1;

  TPrinter *OurPrinter = Printer();

  TPrintDialog *PrintDialog1 = new TPrintDialog(LogForm);
  TFontDialog *FontDialog1 = new TFontDialog(LogForm);

  if(MemoSel == LOG)
    Memo1 = MemoLog;
  else
    Memo1 = MemoDebug;

  if(Memo1->Lines->Count == 0) return;

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

void __fastcall TLogForm::PrinterSetup1Click(TObject *Sender)
{

  TPrinter *OurPrinter = Printer();

  TPrinterSetupDialog *PrinterSetupDialog1 = new TPrinterSetupDialog(LogForm);
  TFontDialog *FontDialog1 = new TFontDialog(LogForm);

  //Bring up the print setup dialog box
  if(PrinterSetupDialog1->Execute()) //Change the font of the printer just in case user changed

    OurPrinter->Canvas->Font = FontDialog1->Font;

  delete PrinterSetupDialog1;
  delete FontDialog1;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Font1Click(TObject *Sender){

  TPrinter *OurPrinter = Printer();
  TFontDialog *FontDialog1 = new TFontDialog(LogForm);

  //If the user pressed OK on the font dialog
  if (FontDialog1->Execute()) //Change the font of the printer
    OurPrinter->Canvas->Font = FontDialog1->Font;

  delete FontDialog1;
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::FormActivate(TObject *Sender){

  if(SaveDialog1->InitialDir.IsEmpty())
    SaveDialog1->InitialDir = GetCurrentDir();
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Flags1Click(TObject *Sender)
{
  MapPar::iterator itPar;
  ClassPar *thisPar;
  String Smod, Sv, SS;
  bool First;

  SaveDebugLog(Sender); // save contents
  
  LogForm->MemoDebug->Clear();

  for(int ii = -1; ii < Global::OurModulesList->Count; ++ii){
    if(ii == -1)
      Smod = "Shared";
    else
      Smod = Global::OurModulesList->Strings[ii];

    First = true;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {
      thisPar = (*itPar).second;
      if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
        continue;

      if(thisPar->ivalues && !(thisPar->basemodule == "basin")){
        if(First){
          LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
          LogForm->MemoDebug->Lines->Add("");
          First = false;
        }

        Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
        LogForm->MemoDebug->Lines->Add(Sv);

        if(thisPar->lay == 1){
          Sv = "";
          for (int hh = 0; hh < thisPar->dim; ++hh)
            Sv = Sv + FloatToStrF(thisPar->ivalues[hh], ffGeneral, 8, 0) + "\t";
          LogForm->MemoDebug->Lines->Add(Sv);
        }
        else{
          LogForm->MemoDebug->Lines->Add("");
          for (int ll = 0; ll < thisPar->lay; ++ll){
            Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
            for (int hh = 0; hh < thisPar->dim; ++hh)
              Sv = Sv + FloatToStrF(thisPar->ilayvalues[ll][hh], ffGeneral, 8, 0) + "\t";
            LogForm->MemoDebug->Lines->Add(Sv);
          }
        }

        LogForm->MemoDebug->Lines->Add("");
      }
    }
  } // for OurModuleList
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Coefficients1Click(TObject *Sender)
{
  MapPar::iterator itPar;
  ClassPar *thisPar;
  String Smod, Sv, SS;
  bool First;

  SaveDebugLog(Sender); // save contents

  LogForm->MemoDebug->Clear();

  for(int ii = -1; ii < Global::OurModulesList->Count; ++ii){
    if(ii == -1)
      Smod = "Shared";
    else
      Smod = Global::OurModulesList->Strings[ii];

    First = true;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {

      thisPar = (*itPar).second;
      if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
        continue;

      bool IsCoeff = (String(thisPar->param.c_str()).Pos("_K") > 0);
      if(thisPar->values && IsCoeff && !(thisPar->basemodule == "basin")){
        if(First){
          LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
          LogForm->MemoDebug->Lines->Add("");
          First = false;
        }

        Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
        LogForm->MemoDebug->Lines->Add(Sv);

        if(thisPar->lay == 1){
          Sv = "";
          for (int hh = 0; hh < thisPar->dim; ++hh)
            Sv = Sv + FloatToStrF(thisPar->values[hh], ffGeneral, 4, 0) + "\t";
          LogForm->MemoDebug->Lines->Add(Sv);
        }
        else{
          LogForm->MemoDebug->Lines->Add("");
          for (int ll = 0; ll < thisPar->lay; ++ll){
            Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
            for (int hh = 0; hh < thisPar->dim; ++hh)
              Sv = Sv + FloatToStrF(thisPar->layvalues[ll][hh], ffGeneral, 8, 0) + "\t";
            LogForm->MemoDebug->Lines->Add(Sv);
          }
        }

        LogForm->MemoDebug->Lines->Add("");
      }
    }
  } // for OurModuleList
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::Parameters1Click(TObject *Sender)
{
   MapPar::iterator itPar;
  ClassPar *thisPar;
  String Smod, Sv, SS;
  bool First;

  SaveDebugLog(Sender); // save contents

  LogForm->MemoDebug->Clear();

  for(int ii = -1; ii < Global::OurModulesList->Count; ++ii){
    if(ii == -1)
      Smod = "Shared";
    else
      Smod = Global::OurModulesList->Strings[ii];

    First = true;

    for (itPar = Global::MapPars.begin(); itPar !=  Global::MapPars.end(); itPar++) {

      thisPar = (*itPar).second;
      if(thisPar->module == "basin" || !(thisPar->module == Smod.c_str()))
        continue;

      if(thisPar->values && !(thisPar->basemodule == "basin")){
        if(First){
          LogForm->MemoDebug->Lines->Add(String("****** '") + Smod + "' ******");
          LogForm->MemoDebug->Lines->Add("");
          First = false;
        }

        Sv = String(thisPar->param.c_str()) + "   \"" + thisPar->help.c_str() + "\"";
        LogForm->MemoDebug->Lines->Add(Sv);

        if(thisPar->lay == 1){
          Sv = "";
          for (int hh = 0; hh < thisPar->dim; ++hh)
            Sv = Sv + FloatToStrF(thisPar->values[hh], ffGeneral, 4, 0) + "\t";
          LogForm->MemoDebug->Lines->Add(Sv);
        }
        else{
          LogForm->MemoDebug->Lines->Add("");
          for (int ll = 0; ll < thisPar->lay; ++ll){
            Sv = String(thisPar->param.c_str()) + "[" + IntToStr(ll+1) + "]\t";
            for (int hh = 0; hh < thisPar->dim; ++hh)
              Sv = Sv + FloatToStrF(thisPar->layvalues[ll][hh], ffGeneral, 8, 0) + "\t";
            LogForm->MemoDebug->Lines->Add(Sv);
          }
        }

        LogForm->MemoDebug->Lines->Add("");
      }
    }
  } // for OurModuleList
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::FormClose(TObject *Sender, TCloseAction &Action){

  if(MemoDebugBkup){
    MemoDebug->Clear();

    for(long ii = 0; ii < MemoDebugBkup->Count; ++ii){
      MemoDebug->Lines->Add(MemoDebugBkup->Strings[ii]);
    }

    delete MemoDebugBkup;
    MemoDebugBkup = NULL;
  }

  if(MemoLogBkup){
    MemoLog->Clear();

    for(long ii = 0; ii < MemoLogBkup->Count; ++ii){
      MemoLog->Lines->Add(MemoLogBkup->Strings[ii]);
    }

    delete MemoLogBkup;
    MemoLogBkup = NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::SaveDebugLog(TObject *Sender){

  if(MemoDebugBkup)
    return;

  MemoDebugBkup = new TStringList;

  for(long ii = 0; ii < MemoDebug->Lines->Count; ++ii)
    MemoDebugBkup->Add(MemoDebug->Lines->Strings[ii]);
}
//---------------------------------------------------------------------------

void __fastcall TLogForm::SaveMemoLog(TObject *Sender){

  if(MemoLogBkup)
    return;

  MemoLogBkup = new TStringList;

  for(long ii = 0; ii < MemoLog->Lines->Count; ++ii)
    MemoLogBkup->Add(MemoLog->Lines->Strings[ii]);
  
}
//---------------------------------------------------------------------------



