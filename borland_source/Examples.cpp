//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Examples.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLibForm *LibForm;
//---------------------------------------------------------------------------
__fastcall TLibForm::TLibForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TLibForm::FormActivate(TObject *Sender)
{
  StringGrid1->RowCount = 20;
  StringGrid1->ColCount = 10;

  StringGrid1->Cells[0] [0] = "Options";
  StringGrid1->Cells[3] [0] = "Selections";

  long indx = 2;
  StringGrid1->Cells[0] [indx] = "Qsi";
  StringGrid1->Cells[1] [indx] = "Yes";

  indx += 2;
  StringGrid1->Cells[0] [indx] = "Qli";
  StringGrid1->Cells[1] [indx] = "Yes";

  indx += 2;
  StringGrid1->Cells[0] [indx] = "Evaporation";

  indx += 2;
  StringGrid1->Cells[0] [indx] = "Interception";
  StringGrid1->Cells[1] [indx] = "intcp";
  StringGrid1->Cells[2] [indx] = "CanopyClearing";

  indx += 2;
  StringGrid1->Cells[0][indx] = "Infiltration";
  StringGrid1->Cells[0][indx+1] = "(unfrozen soil)";
  StringGrid1->Cells[1][indx] = "Ayers";
  StringGrid1->Cells[2][indx] = "GreenAmt";

  indx += 2;
  StringGrid1->Cells[0][indx] = "Infiltration";
  StringGrid1->Cells[0][indx+1] = "(frozen soil)";
  StringGrid1->Cells[1][indx] = "crack";
  StringGrid1->Cells[2][indx] = "PrairieInfiltration";
  StringGrid1->Cells[3][indx] = "GreenCrack";

  indx += 2;
  StringGrid1->Cells[0][indx] = "Melt";
  StringGrid1->Cells[1][indx] = "ebsm";
  StringGrid1->Cells[2][indx] = "Snobal";

  indx += 2;
  StringGrid1->Cells[0][indx] = "Soil";

  indx += 2;
  StringGrid1->Cells[0][indx] = "Routing";
  StringGrid1->Cells[1][indx] = "NetRoute";
  StringGrid1->Cells[2][indx] = "NetRoute_D";
  StringGrid1->Cells[3][indx] = "NetRoute_M";
  StringGrid1->Cells[4][indx] = "NetRoute_D_M";

}
//---------------------------------------------------------------------------

