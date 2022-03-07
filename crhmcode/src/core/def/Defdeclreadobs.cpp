#include "Defdeclreadobs.h"
#include "../InstrumentLogger.h"

Defdeclreadobs :: Defdeclreadobs (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclreadobs::Defdeclreadobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclreadobs.cpp>");
    name = DefStringList -> at (1);
    Dim = getTDim (DefStringList -> at (2));
    Description = DefStringList -> at (3);
    Units = DefStringList -> at (4);
    if (DefCRHM :: DefStringList -> size () > 5)
    {
        HRU_OBS_indexed = Strtolong (DefStringList -> at (5));
    }

    else
    {
        HRU_OBS_indexed = 0;
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclreadobs::Defdeclreadobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclreadobs.cpp>");
}
void Defdeclreadobs :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclreadobs::CallDecl()@@@Defdeclreadobs.cpp>");
    long cnt = Macro -> declreadobs (name, Dim, Description, Units, & fix_const, HRU_OBS_indexed);
    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    FP -> second.kind = TV :: CRHM;
    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = cnt;
    FP -> second.value = const_cast < double * > (fix_const);
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclreadobs::CallDecl()@@@Defdeclreadobs.cpp>");
}