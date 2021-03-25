// 09/13/11
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UpdateForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlotControl *PlotControl;
//---------------------------------------------------------------------------
__fastcall TPlotControl::TPlotControl(TComponent* Owner)
        : TForm(Owner)
{
    IntervalLength = PlotUpdate->ItemIndex; // synchronises menu and interrupt objects
}
//---------------------------------------------------------------------------
void __fastcall TPlotControl::PlotUpdateClick(TObject *Sender)
{
  FormClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TPlotControl::FormClick(TObject *Sender)
{
  if(PlotUpdate->ItemIndex > 1) // save selection in variables for main
    IntervalLength = PlotUpdate->ItemIndex;
  else
    IntervalControl = PlotUpdate->ItemIndex; // 0 - ignore, 1 - terminate
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TPlotControl::FormActivate(TObject *Sender)
{
  if(PlotUpdate->ItemIndex < 2) // after control resets to interval selection
    PlotUpdate->ItemIndex = IntervalLength; // use last interval
}
//---------------------------------------------------------------------------

