#include "Defdeclobs.h"
#include "../InstrumentLogger.h"

Defdeclobs :: Defdeclobs (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::Defdeclobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclobs.cpp>");
    string S = DefStringList -> at (1);
    string :: size_type Pos = S.find ("#");
    if (Pos == string :: npos)
    {
        S += "#";
    }

    else
    {
        S = S.substr (0, Pos + 1);
    }

    name = S;
    Dim = getTDim (DefStringList -> at (2));
    Description = DefStringList -> at (3);
    Units = DefStringList -> at (4);
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::Defdeclobs(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclobs.cpp>");
}
void Defdeclobs :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::CallDecl()@@@Defdeclobs.cpp>");
    long cnt = Macro -> declobs (Macro -> Name, name, Dim, Description, Units, & fix);
    FP = Macro -> vars.find (name);
    if (FP == Macro -> vars.end ())
    {
        Macro -> vars.insert (make_pair (name, VarCHRM ()));
        FP = Macro -> vars.find (name);
    }

    if (fix)
    {
        FP -> second.kind = TV :: CRHM;
    }

    else
    {
        FP -> second.kind = TV :: NOP;
    }

    FP -> second.name = name;
    FP -> second.Ihh = 0;
    FP -> second.IndexMax = cnt;
    FP -> second.value = fix;
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::CallDecl()@@@Defdeclobs.cpp>");
}
void Defdeclobs :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobs::CallInit(long nhru, long nlay)@@@Defdeclobs.cpp>");
    for (int hh = 0; hh <= FP -> second.IndexMax; ++ hh) {
        FP -> second.Ihh = hh;
        FP -> second.put (0.0);
    }
InstrumentLogger::instance()->log_instrument_log("</Defdeclobs::CallInit(long nhru, long nlay)@@@Defdeclobs.cpp>");
}