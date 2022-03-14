#include "Defdeclputparam.h"
#include "../../InstrumentLogger.h"

Defdeclputparam :: Defdeclputparam (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::Defdeclputparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclputparam.cpp>");
    module = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    Units = DefStringList -> Strings [3];
InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::Defdeclputparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclputparam.cpp>");
}
void Defdeclputparam :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::CallDecl()@@@Defdeclputparam.cpp>");
    MapPar :: iterator itPar;
    ClassPar * thisPar = NULL;
    int GetUnit;
    GetUnit = Macro -> FindWildParFloat (name, thisPar, false, false);
    if (thisPar != NULL && thisPar -> varType == TVar :: Int)
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (Int)
    {
        Macro -> declputparam (module, name, Units, & fix_long);
    }

    else
    {
        Macro -> declputparam (module, name, Units, & fix, & fix2);
    }

    if (Global :: BuildFlag == TBuild :: INIT)
    {
        FP = Macro -> vars.find (name);
        if (FP == Macro -> vars.end ())
        {
            Macro -> vars.insert (make_pair (name, VarCHRM ()));
            FP = Macro -> vars.find (name);
        }

        FP -> second.name = name;
        FP -> second.Ihh = 0;
        FP -> second.Ill = 0;
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            FP -> second.kind = TV :: CRHMint;
            FP -> second.ivalue = const_cast < long * > (fix_long);
        }

        else
        if (thisPar != NULL && (thisPar -> dimen == TDim :: NDEF || thisPar -> dimen == TDim :: NDEFN))
        {
            FP -> second.kind = TV :: CRHM2;
            FP -> second.value2 = const_cast < double ** > (fix2);
        }

        else
        {
            FP -> second.kind = TV :: CRHM;
            FP -> second.value = const_cast < double * > (fix);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::CallDecl()@@@Defdeclputparam.cpp>");
}
void Defdeclputparam :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputparam::CallInit(long nhru, long nlay)@@@Defdeclputparam.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclputparam::CallInit(long nhru, long nlay)@@@Defdeclputparam.cpp>");
}