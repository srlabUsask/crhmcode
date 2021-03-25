//---------------------------------------------------------------------------

#ifndef ExamplesH
#define ExamplesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TLibForm : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
        void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TLibForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLibForm *LibForm;
//---------------------------------------------------------------------------
#endif
