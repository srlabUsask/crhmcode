#include "Defdeclobsfunc.h"
#include "../InstrumentLogger.h"

Defdeclobsfunc :: Defdeclobsfunc (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobsfunc::Defdeclobsfunc(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclobsfunc.cpp>");
    obs = DefStringList -> at (1);
    name = DefStringList -> at (2);
    typeFun = getTFunc (DefStringList -> at (3));
InstrumentLogger::instance()->log_instrument_log("</Defdeclobsfunc::Defdeclobsfunc(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclobsfunc.cpp>");
}
void Defdeclobsfunc :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclobsfunc::CallDecl()@@@Defdeclobsfunc.cpp>");
    long cnt = Macro -> declobsfunc (obs, name, & fix, typeFun);
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
    FP -> second.value = fix;
    FP -> second.Me = Macro;
InstrumentLogger::instance()->log_instrument_log("</Defdeclobsfunc::CallDecl()@@@Defdeclobsfunc.cpp>");
}