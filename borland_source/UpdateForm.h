//---------------------------------------------------------------------------

#ifndef UpdateFormH
#define UpdateFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPlotControl : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *PlotUpdate;
        void __fastcall PlotUpdateClick(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TPlotControl(TComponent* Owner);
        long previous;
        long IntervalLength; // > 1
        long IntervalControl; // 0 or 1
};
//---------------------------------------------------------------------------
extern PACKAGE TPlotControl *PlotControl;
//---------------------------------------------------------------------------
#endif
