// 07/11/15
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Analy.h"
#include "CRHMmain.h"
#include "DefCRHMGlobal.h"
#include "math.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeeComma"
#pragma link "TeeEdiGene"
#pragma link "TeeNavigator"
#pragma link "TeeEdit"
#pragma link "TeeTools"
#pragma link "TeeThemeEditor"
#pragma link "TeeEdit"
#pragma resource "*.dfm"

using namespace std;

TAnalysis *Analysis;

CRHM::TFitType Plot::FitType = CRHM::POLY;
CRHM::TAgainst Plot::Against = CRHM::myTIME;

TLineSeries* Plot::FirstSeries = NULL; // static. Used by Variable for X base and MLR for Y

char Errors[][21] = {"No error",                // 0
                     "NumPoints < 2",           // 1
                     "NumTerms < 1",            // 2
                     "NumTerms > NumPoints",    // 3
                     "No solution ",            // 4
                     "X data not positve",      // 5
                     "Y data not same sign",    // 6
                     "X data not same sign",    // 7
                     "Other error"};            // 8

//---------------------------------------------------------------------------
void Plot::OutFit(TLineSeries *OutSeries) {

  for(long ii = 0; ii < MyFit->NumPoints; ii++)
    OutSeries->AddXY(MyFit->XData[ii], MyFit->YFit[ii], "", clTeeColor);
}

//---------------------------------------------------------------------------
Plot::Plot(long Index) : Error(0) {

  double **Basis;
  TLineSeries *BoxSeries = (TLineSeries *) Main->Chart->Series[Index]; // Y series for Variable and Time

  if(Plot::Against == CRHM::VARIABLE) {  // handle variable
    MySeries = (TLineSeries *) new TPointSeries(Analysis);

    MySeries->Color = clTeeColor;
    MySeries->Title = BoxSeries->Title;
    MySeries->Pointer->Visible = true;
    MySeries->Pointer->Style = psCircle; // psSmallDot;
    MySeries->Pointer->HorizSize = 2;
    MySeries->Pointer->VertSize = 2;

    if(!Analysis->Chart->Foot->Text->Count)
      Analysis->Chart->Foot->Text->Add(FirstSeries->Title);

    long Foff = 0;
    long Boff = 0;
    for(long ii = 0; ii+Foff < FirstSeries->Count() && ii+Boff < BoxSeries->Count(); ++ii) {
      if(FirstSeries->XValue[Foff+ii] >= Global::DTend) break;
      if(FirstSeries->XValue[Foff+ii] != BoxSeries->XValue[Boff+ii])
        if(FirstSeries->XValue[Foff+ii] > BoxSeries->XValue[Boff+ii]) {
          do
            ++Boff;
          while (FirstSeries->XValue[Foff+ii] > BoxSeries->XValue[Boff+ii]);
        }
        else {
          do
            ++Foff;
          while (FirstSeries->XValue[Foff+ii] < BoxSeries->XValue[Boff+ii]);
        }

      MySeries->AddXY(FirstSeries->YValue[ii], BoxSeries->YValue[ii], "", clTeeColor);
      
    }
    MySeries->ParentChart = Analysis->Chart;
    MySeries->XValues->DateTime = false;
  }
  else if(Plot::FitType == CRHM::MLR) { // Multiple Linear regression

    MySeries = (TLineSeries *) new TPointSeries(Analysis);

    MySeries->Color = clTeeColor;
    MySeries->Title = FirstSeries->Title;
    MySeries->Pointer->Visible = true;
    MySeries->Pointer->Style = psCircle; // psSmallDot;
    MySeries->Pointer->HorizSize = 2;
    MySeries->Pointer->VertSize = 2;

    Analysis->Chart->Foot->Text->Clear();
    Analysis->Chart->Foot->Text->Add(FirstSeries->Title);

    double Xmin = max<float> (FirstSeries->MinXValue(), (double) Analysis->DateTimePicker1->Date);
    double I;
    Xmin = floor(Xmin) + modf(FirstSeries->MinXValue(), &I); // put interval back

    float Xmax = min<float> (FirstSeries->MaxXValue(), (double) Analysis->DateTimePicker2->Date);
    NumTerms = Analysis->ListBox2->Items->Count;

    long TimeIndx = Analysis->ListBox2->Items->IndexOf("Time");

    for(long ss = 1; ss < NumTerms; ++ss) {
      if(TimeIndx == ss)
        continue;
      long Idx = (long) Analysis->ListBox2->Items->Objects[ss];
      TLineSeries *ThisSeries = (TLineSeries *) Main->Chart->Series[Idx];
      if(Xmin < ThisSeries->MinXValue())
        Xmin = ThisSeries->MinXValue();
      if(Xmax > ThisSeries->MaxXValue())
        Xmax = ThisSeries->MaxXValue();
    }

    for(long ii = 0; ii < FirstSeries->Count(); ii++)
      if(FirstSeries->XValue[ii] >= Xmin && FirstSeries->XValue[ii] <= Xmax)
        MySeries->AddXY(FirstSeries->XValue[ii], FirstSeries->YValue[ii], "", clTeeColor);

    long NumPoints = MySeries->Count();
    
    MySeries->ParentChart = Analysis->Chart;
    MySeries->XValues->DateTime = true;

    Basis = new double* [NumPoints];

    for(long ii = 0; ii < NumPoints; ii++) {
       Basis[ii] = new double [NumTerms];
       Basis[ii][0] = 1.0;
       if(TimeIndx > -1)
         Basis[ii][TimeIndx] = MySeries->XValue[ii] - MySeries->XValue[0];
    }

    for(long ss = 1; ss < NumTerms; ++ss) {
      if(TimeIndx == ss)
        continue;
      long Idx = (long) Analysis->ListBox2->Items->Objects[ss];
      TLineSeries *ThisSeries = (TLineSeries *) Main->Chart->Series[Idx];
      long jj = 0;
      for(long ii = 0; ii < ThisSeries->Count(); ii++)
        if(FirstSeries->XValue[ii] >= Xmin && FirstSeries->XValue[ii] <= Xmax)
          Basis[jj++][ss] = ThisSeries->YValue[ii];
    }
  }
  else { // handle time

    MySeries = new TLineSeries(Analysis);

    MySeries->Color = clTeeColor;
    MySeries->Title = BoxSeries->Title;

    for(long ii = 0; ii < BoxSeries->Count(); ii++)
      if(BoxSeries->XValue[ii] >= Analysis->DateTimePicker1->Date && BoxSeries->XValue[ii] <= Analysis->DateTimePicker2->Date)
        MySeries->AddXY(BoxSeries->XValue[ii], BoxSeries->YValue[ii], "", clTeeColor);
    MySeries->ParentChart = Analysis->Chart;
    MySeries->XValues->DateTime = true;
  }

  switch(FitType) {
      case CRHM::POLY      : { MyFit = new Numerical::Poly(MySeries, Plot::Against == CRHM::myTIME, Analysis->UpDown1->Position); break;}
      case CRHM::FOURIER   : { MyFit = new Fourier(MySeries, Plot::Against == CRHM::myTIME, Analysis->UpDown1->Position); break;}
      case CRHM::MLR       : { MyFit = new MLinReg(MySeries, Analysis->ListBox2->Items->Count, Basis); break;}
      case CRHM::POWER     : { MyFit = new Numerical::Power(MySeries, Plot::Against == CRHM::myTIME); break;}
      case CRHM::EXPO      : { MyFit = new Expo(MySeries, Plot::Against == CRHM::myTIME); break;}
      case CRHM::LOGARITHM : { MyFit = new Log(MySeries, Plot::Against == CRHM::myTIME); break;}
  }

  Error = MyFit->Error;  // move error from class LeastSquares
  
  if(Error != 0)
    return;
  
  NumTerms = MyFit->NumTerms;

  FitSeries = new TLineSeries(Analysis);

  OutFit(FitSeries);
  
  FitSeries->Color = clTeeColor;
  FitSeries->ParentChart = Analysis->Chart;
  
  if(Plot::FitType == CRHM::MLR)
    FitSeries->Title = MyFit->Desc + "_" + FirstSeries->Title;
  else
    FitSeries->Title = MyFit->Desc + "_" + BoxSeries->Title;
}

//---------------------------------------------------------------------------
Plot::~Plot() {

  Analysis->Chart->Foot->Text->Clear();
  
  if(!(Plot::Against == CRHM::VARIABLE && MySeries == NULL)) {
    if(Error == 0) {
      FitSeries->ParentChart = NULL;
      FitSeries->Clear();
    }

    MySeries->ParentChart = NULL;  // remove series from chart
    MySeries->Clear(); // destroy series
  }
  else { // VARIABLE and MySeries NULL
    FirstSeries = NULL;
    FitSeries->ParentChart = NULL;
    FitSeries->Clear();
  }
  delete MyFit;
}

//---------------------------------------------------------------------------
__fastcall TAnalysis::TAnalysis(TComponent* Owner) : TForm(Owner) {

}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::FormDestroy(TObject *Sender) {

  long Stop = ListBox2->Items->Count;
  if(Plot::FitType == CRHM::MLR)
    if(Stop > 1) Stop = 1;

  for(long ii = 0; ii < Stop; ii++)
    if((Plot *) ListBox2->Items->Objects[ii] != NULL)
     delete (Plot *) ListBox2->Items->Objects[ii];

  ListBox2->Items->Clear();
  Memo1->Lines->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::FormCreate(TObject *Sender) {

  Chart->Legend->LegendStyle = lsSeries;
  Chart->Title->Text->Clear();
  Chart->Title->Text->Add("Regression");
  ShowLines = 0;

  TCommanderControls Tcntrls[4] = {tcbEdit,tcbSeparator,tcbPrintPreview,tcbSeparator};
  TeeCommander1->CreateControls(Tcntrls, 4);

  TColor *OurColors = new TColor[MaxDefaultColors];

  for(long jj = 0; jj < MaxDefaultColors; ++jj)
    OurColors[jj] = GetDefaultColor(jj);

  OurColors[2] = OurColors[0]; // overwrite yellow

  SetDefaultColorPalette(OurColors, MaxDefaultColors);

  delete[] OurColors;
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::FormActivate(TObject *Sender) {

  if(SaveDialog1->InitialDir.IsEmpty())
    SaveDialog1->InitialDir = GetCurrentDir();

  ListBox1->Items->Clear();
  ListBox2->Items->Clear();

  Memo1->Lines->Clear();

  long jj = Main->Chart->SeriesCount();
  String S;

  for(long ii = 0; ii < Main->Chart->SeriesCount(); ++ii) {
    S = Main->Chart->Series[ii]->Title;
    if(S.Length() == 0) S = Main->Chart->Series[ii]->Name;
    ListBox1->Items->AddObject(S, (TObject*) ii);
  }

  RadioGroup1->ItemIndex = 0;
  RadioGroup1Click(Sender);

  DateTimePicker1->Date = Main->DateTimePicker1->Date;
  DateTimePicker2->Date = Main->DateTimePicker2->Date;
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::ListBox1Click(TObject *Sender) {

  Memo1->Lines->Clear();

  long jj = ListBox1->ItemIndex;

  long ii = IndexOf(ListBox2, ListBox1->Items->Strings[jj]);

  if(ii == -1) { // Variable first time
      if((Plot::Against == CRHM::VARIABLE || Plot::FitType == CRHM::MLR) && ListBox2->Items->Count == 0) {
        ListBox2->Items->AddObject(ListBox1->Items->Strings[jj], (TObject*) NULL);
        ListBox2->ItemIndex = ListBox2->Items->Count-1;
        long Index = (long) ListBox1->Items->Objects[jj];
        Plot::FirstSeries = (TLineSeries *) Main->Chart->Series[Index];
        return;
      }

      if(Plot::FitType == CRHM::MLR){
        ListBox2->Items->AddObject(ListBox1->Items->Strings[jj], (TObject*) jj);
        if((Plot *) ListBox2->Items->Objects[0] != NULL){
          delete (Plot *) ListBox2->Items->Objects[0];
          (TObject*) ListBox2->Items->Objects[0] = NULL;
        }
        return;
      }

      if(Plot::Against == CRHM::VARIABLE && Plot::FirstSeries->Count() != ((TLineSeries *) Main->Chart->Series[(long) ListBox1->Items->Objects[jj]])->Count()){
        Application->MessageBox("different series time intervals or series lengths", "Cannot plot together", MB_OK);
        return;
      }

      Plot * TryPlot = new Plot((long) ListBox1->Items->Objects[jj]); // plot TIME and VARIABLE

      if(TryPlot->Error == 0)
        ListBox2->Items->AddObject(ListBox1->Items->Strings[jj], (TObject*) TryPlot);
      else {
        Application->MessageBox(String(String("Curve fit error ") +
            Errors[TryPlot->Error]).c_str(), "Runtime Error", MB_OK);
        delete TryPlot;
        return;
      }
      
      ListBox2->ItemIndex = ListBox2->Items->Count-1;
      Button1Click(Sender); // display memo text
  }
  else // second selection for VARIABLE or MLR

    if(ii == 0 && Plot::Against == CRHM::VARIABLE){ // clear ALL
      for(long kk = 0; kk < ListBox2->Items->Count; kk++) 
        delete (Plot *) ListBox2->Items->Objects[kk];

      ListBox2->Clear();
    }
    else if(Plot::FitType == CRHM::MLR) {
      if(ii == 0) { // clear first
        if((Plot *) ListBox2->Items->Objects[0] != NULL)
          delete (Plot *) ListBox2->Items->Objects[0];
          (TObject*) ListBox2->Items->Objects[0] = NULL;

        ListBox2->Clear();
      }
      else {
        ListBox2->Items->Delete(ii);
        if((Plot *) ListBox2->Items->Objects[0] != NULL) {
          delete (Plot *) ListBox2->Items->Objects[0];
          (TObject*) ListBox2->Items->Objects[0] = NULL;
        }
      }
    }
    else { // time display
      delete (Plot *) ListBox2->Items->Objects[ii];
      ListBox2->Items->Delete(ii);
    }
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::ListBox2Click(TObject *Sender) {

 long ii = ListBox2->ItemIndex;

  if(Plot::FitType == CRHM::MLR){
    if(ii == 0){
      if((Plot *) ListBox2->Items->Objects[0] != NULL) {
        delete (Plot *) ListBox2->Items->Objects[0];
        ListBox2->Clear();
        return;
      }
      Plot * TryPlot = new Plot((long) 0);  // plot MLR. TObject not used

      if(TryPlot->Error == 0)
        ListBox2->Items->Objects[0] = (TObject*) TryPlot;
      else {
        Application->MessageBox(String(String("Curve fit error ") +
            Errors[TryPlot->Error]).c_str(), "Runtime Error", MB_OK);
        delete TryPlot;
        return;
      }
      
      ListBox2->ItemIndex = 0;
      Button1Click(Sender); // display memo text
    }
    else {
      if((Plot *) ListBox2->Items->Objects[0] != NULL){
        delete (Plot *) ListBox2->Items->Objects[0];
        (TObject*) ListBox2->Items->Objects[0] = NULL;
      }
      
      ListBox2->Items->Delete(ii);
    }

    return;
  }

  if(ii == 0 && Plot::Against == CRHM::VARIABLE) {
    for(long kk = 1; kk < ListBox2->Items->Count; kk++)
      if((Plot *) ListBox2->Items->Objects[kk] != NULL)
        delete (Plot *) ListBox2->Items->Objects[kk];
    ListBox2->Clear();
  }
  else {
    delete (Plot *) ListBox2->Items->Objects[ii];
    ListBox2->Items->Delete(ii);
  }
  Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TAnalysis::FormClose(TObject *Sender, TCloseAction &Action) {

  long Stop = ListBox2->Items->Count;
  if(Plot::FitType == CRHM::MLR)
    if(Stop > 1) Stop = 1;

  for(long ii = 0; ii < Stop; ii++)
    if((Plot *) ListBox2->Items->Objects[ii] != NULL)
     delete (Plot *) ListBox2->Items->Objects[ii];

  ListBox2->Items->Clear();
  Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TAnalysis::UpDown1Click(TObject *Sender, TUDBtnType Button) {

  if(Plot::FitType == CRHM::FOURIER && UpDown1->Position < 3)
    UpDown1->Position = 3;

  Label1->Caption = "Order " + String(UpDown1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TAnalysis::RadioGroup1Click(TObject *Sender) {

  CleanUp(Sender);

  RadioGroup2->Visible = true;
  ListBox1->Items->Delete(ListBox1->Items->IndexOf("Time"));

  if(RadioGroup1->ItemIndex == 0 || RadioGroup1->ItemIndex == 1) {
    Label1->Visible = true;
    UpDown1->Visible = true;
  }
  else {
    Label1->Visible = false;
    UpDown1->Visible = false;
  }
  switch(RadioGroup1->ItemIndex){
    case 0 : {Plot::FitType = CRHM::POLY; break;}
    case 1 : {Plot::FitType = CRHM::FOURIER;
              if(UpDown1->Position < 3){
                UpDown1->Position = 3;
                Label1->Caption = "Order " + String(UpDown1->Position);
              }
    break;}
    case 2 : {Plot::FitType = CRHM::POWER; break;}
    case 3 : {Plot::FitType = CRHM::EXPO; break;}
    case 4 : {Plot::FitType = CRHM::LOGARITHM; break;}
    case 5 : {Plot::FitType = CRHM::MLR;
               RadioGroup2->ItemIndex = 0;
               RadioGroup2->Visible = false;
               ListBox1->Items->AddObject("Time", (TObject*) NULL);
               Plot::Against = CRHM::myTIME;
               break;}
  }
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::RadioGroup2Click(TObject *Sender) {

  for(long ii = 0; ii < ListBox2->Items->Count; ii++)
    delete (Plot *) ListBox2->Items->Objects[ii];
  ListBox2->Clear();
  Memo1->Lines->Clear();

  switch(RadioGroup2->ItemIndex){
    case 0 : {Plot::Against = CRHM::myTIME;
              Dsply = CRHM::OBS;
              Button2->Caption = "Obs";
              break;}
    case 1 : {Plot::Against = CRHM::VARIABLE;
              Dsply = CRHM::XY;
              Button2->Caption = "X/Y";
              break;}
  }
}
//---------------------------------------------------------------------------

void __fastcall TAnalysis::SaveClick(TObject *Sender) {

  if(!SaveDialog1->FileName.IsEmpty()) 
    DoSave(Sender);
  else SaveAsClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAnalysis::SaveAsClick(TObject *Sender) {

  SaveDialog1->Title = "Save As";

  if(Dsply == CRHM::OBS || Dsply == CRHM::FRACT){
    SaveDialog1->DefaultExt = "obs";
    SaveDialog1->Filter = "Obs Files (*.obs)|*.obs";
  }
  else {
    SaveDialog1->DefaultExt = "txt";
    SaveDialog1->Filter = "Text Files (*.txt)|*.txt";
  }
  
  if(SaveDialog1->Execute()) {
    SaveDialog1->InitialDir = ExtractFilePath(SaveDialog1->FileName);
    if(SaveDialog1->InitialDir.IsEmpty())
      SaveDialog1->InitialDir = GetCurrentDir();
    DoSave(Sender);
  }
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::ExitClick(TObject *Sender) {

  Close();
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::DoSave(TObject *Sender) {

  String Sx, Sy;

  TStringList *ExportList = new TStringList;

  if(ListBox2->Items->Count == 0) return;

  long Indx = ListBox2->ItemIndex;

  if(Indx == -1) return;

  if(Indx == 0 && Plot::Against == CRHM::VARIABLE) return;
  
  Plot *thisPlot =  (Plot *) ListBox2->Items->Objects[Indx];

  Sx = thisPlot->MyFit->Desc;
  ExportList->Add(Sx);

  Sx = "Number of terms " + String(thisPlot->NumTerms);
  ExportList->Add(Sx);

  Sx = "Coefficients";
  for(long kk = 0; kk < thisPlot->NumTerms; kk++)
    Sx = Sx + " " + FloatToStrF(thisPlot->MyFit->Solution[kk], ffGeneral, 4, 0);
  ExportList->Add(Sx);

  if(Plot::Against == CRHM::VARIABLE) {  // handle variable
    Sx = "R2 " + FloatToStrF(thisPlot->MyFit->R2, ffGeneral, 4, 0);
    Memo1->Lines->Add(Sx);
  }

  Sx = "X 1"; ExportList->Add(Sx);

  Sx = "Y 1"; ExportList->Add(Sx);

  Sx = "YFit 1"; ExportList->Add(Sx);

  ExportList->Add("######");

    for (long ii = 0; ii < thisPlot->MyFit->NumPoints; ii++) {
      float X;
      if(Plot::Against == CRHM::VARIABLE)
        X = Plot::FirstSeries->XValue[ii];
      else
        X = thisPlot->MyFit->XData[ii];

      if(Dsply == CRHM::MDY) {
        TDateTime Dt = TDateTime (X);
        Sx = Dt.DateString()+  FormatDateTime(" hh:mm ", Dt)+ " ";
      }
      else if(Dsply == CRHM::FRACT)
        Sx = FloatToStrF(X, ffGeneral, 10, 0);
      else if(Dsply == CRHM::OBS){
        unsigned short year, month, day, hr, min, sec, msec;
        TDateTime Dt = TDateTime (X);
        Dt.DecodeDate(&year, &month, &day);
        Dt.DecodeTime(&hr, &min, &sec, &msec);
        char buff[30];
        sprintf(buff, "%4d %2d %2d %2d %2d ",
            year, month, day, hr, min);
        Sx = String(buff);
      }

      if(Plot::Against == CRHM::VARIABLE) {
        if(Dsply == CRHM::XY) Sx = "";

        Sx = Sx + "\t" + FloatToStrF(thisPlot->MyFit->XData[ii], ffGeneral, 4, 0);
      }

      Sy = FloatToStrF(thisPlot->MyFit->YData[ii], ffGeneral, 4, 0);
      Sy = Sy + "\t" + FloatToStrF(thisPlot->MyFit->YFit[ii], ffGeneral, 4, 0);
      Sx = Sx + "\t" + Sy;

      ExportList->Add(Sx);
    }
    ExportList->SaveToFile(SaveDialog1->FileName);

    delete ExportList;
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::Button1Click(TObject *Sender) { // display memo text

  String Sx, Sy;

  Memo1->Lines->Clear();

  if(ListBox2->Items->Count == 0) return;

  long Indx = ListBox2->ItemIndex;

  if(Indx == -1) return;

  Plot *thisPlot =  (Plot *) ListBox2->Items->Objects[Indx];

  if(ShowLines >= thisPlot->MyFit->NumPoints) ShowLines = 0;

  long ShowTo = ShowLines + 500;

  Sx = thisPlot->MyFit->Type;
  Memo1->Lines->Add(Sx);

  Sx = "Number of terms " + String(thisPlot->NumTerms);
  Memo1->Lines->Add(Sx);

  Sx = "Coefficients";
  for(long kk = 0; kk < thisPlot->NumTerms; kk++)
    Sx = Sx + "\t" + FloatToStrF(thisPlot->MyFit->Solution[kk], ffGeneral, 4, 0);
  Memo1->Lines->Add(Sx);

  Sx = "R2 = " + FloatToStrF(thisPlot->MyFit->R2, ffGeneral, 4, 0);
  Memo1->Lines->Add(Sx);

  Sx = "X 1"; Memo1->Lines->Add(Sx);

  Sx = "Y 1"; Memo1->Lines->Add(Sx);

  Sx = "YFit 1"; Memo1->Lines->Add(Sx);

  Memo1->Lines->Add("######");

    for (long ii = 0; ii < thisPlot->MyFit->NumPoints; ii++) {

      if(Plot::Against == CRHM::VARIABLE) {
        Sx = FloatToStrF(thisPlot->MyFit->XData[ii], ffGeneral, 4, 0);
      }
      else if(Dsply == CRHM::MDY) {
        TDateTime Dt = TDateTime (thisPlot->MyFit->XData[ii]);
        Sx = Dt.DateString()+  FormatDateTime(" hh:mm ", Dt)+ " ";
      }
      else if(Dsply == CRHM::FRACT)
        Sx = FloatToStrF(thisPlot->MyFit->XData[ii], ffGeneral, 10, 0);
      else if(Dsply == CRHM::OBS){
        unsigned short year, month, day, hr, min, sec, msec;
        TDateTime Dt = TDateTime (thisPlot->MyFit->XData[ii]);
        Dt.DecodeDate(&year, &month, &day);
        Dt.DecodeTime(&hr, &min, &sec, &msec);
        char buff[30];
        sprintf(buff, "%4d %2d %2d %2d %2d ",
            year, month, day, hr, min);
        Sx = String(buff);
      }

      Sy = FloatToStrF(thisPlot->MyFit->YData[ii], ffGeneral, 4, 0);
      Sy = Sy + "\t" + FloatToStrF(thisPlot->MyFit->YFit[ii], ffGeneral, 4, 0);
      Sx = Sx + "\t" + Sy;

//      Memo1->Lines->Add(Sx);
      if(ii > ShowTo) break;
    }

    ShowLines = ShowTo;

    Memo1->SelStart = 0;
    Memo1->SelLength = 1;
}

//---------------------------------------------------------------------------
void __fastcall TAnalysis::Button2Click(TObject *Sender) {

  switch (Dsply)
  {
    case   CRHM::OBS:
      Dsply = CRHM::FRACT;
      Button2->Caption = "Excel";
      break;
    case CRHM::FRACT:
      Dsply = CRHM::MDY;
      Button2->Caption = "MM/DD/YY hh:mm";
      break;
    case CRHM::MDY:
      if(Dsply == CRHM::myTIME) {
        Dsply = CRHM::OBS;
        Button2->Caption = "Obs";
      }
      else {
        Dsply = CRHM::XY;
        Button2->Caption = "X/Y";
      }
      break;
    case CRHM::XY:
      Dsply = CRHM::OBS;
      Button2->Caption = "Obs";
  }
}
//---------------------------------------------------------------------------
void __fastcall TAnalysis::CleanUp(TObject *Sender){

  long Stop = ListBox2->Items->Count;
  if(Plot::FitType == CRHM::MLR)
    if(Stop > 1) Stop = 1;

  for(long ii = 0; ii < Stop; ii++)
    if((Plot *) ListBox2->Items->Objects[ii] != NULL)
     delete (Plot *) ListBox2->Items->Objects[ii];

  ListBox2->Items->Clear();
  Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
long __fastcall TAnalysis::IndexOf(TListBox *Box, const AnsiString S){
  for(long ii = 0; ii < Box->Count; ++ii){
    if(Box->Items->Strings[ii] == S)
    return ii;
  }
  return -1;
}
//---------------------------------------------------------------------------

