// 11/27/06
//---------------------------------------------------------------------------

#ifndef ShapeH
#define ShapeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TeeComma.hpp"
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "TeeEdit.hpp"
#include <Dialogs.hpp>
#include <TeCanvas.hpp>
#include "TeeMapSeries.hpp"
#include "TeeSurfa.hpp"
//---------------------------------------------------------------------------

class TShapeForm : public TForm
{
__published:	// IDE-managed Components
  TChart *Chart;
        TTeeCommander *TeeCommander1;
        TOpenDialog *OpenDialogShape;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMapSeries *Series1;
        TPanel *Panel1;
        TListBox *ListBox1;
        TPanel *Panel2;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TMenuItem *Display1;
        TMenuItem *Variables1;
        TMenuItem *Parameters1;
  TChartPreviewer *ChartPreviewer1;
  TChartEditor *ChartEditor1;
        TMenuItem *Open1;
        TMenuItem *Grid1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall File1Click(TObject *Sender);
        void __fastcall DateTimePicker2Change(TObject *Sender);
        void __fastcall DateTimePicker1Change(TObject *Sender);
        void __fastcall Variables1Click(TObject *Sender);
        void __fastcall Parameters1Click(TObject *Sender);
        void __fastcall Grid1Click(TObject *Sender);
private:	// User declarations
        long Cnt;
        long nhru;
        int Column_Count;
        int Row_Count;
public:		// User declarations
        __fastcall TShapeForm(TComponent* Owner);
        int __fastcall IndexOf(TListBox *Box, const AnsiString S);
};
//---------------------------------------------------------------------------
extern PACKAGE TShapeForm *ShapeForm;
//---------------------------------------------------------------------------
#endif
