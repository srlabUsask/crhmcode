#include "Defdeclputvar.h"
#include "../../InstrumentLogger.h"

Defdeclputvar :: Defdeclputvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::Defdeclputvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclputvar.cpp>");
    module = DefStringList -> Strings [1];
    name = DefStringList -> Strings [2];
    Units = DefStringList -> Strings [3];
InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::Defdeclputvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclputvar.cpp>");
}
void Defdeclputvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::CallDecl()@@@Defdeclputvar.cpp>");
    MapVar :: iterator itVar;
    ClassVar * thisVar = NULL;
    long GetUnit;
    GetUnit = Macro -> FindWildVarFloat (name, thisVar);
    if (Global :: thisVar != NULL && ((ClassVar *) Global :: thisVar) -> varType == TVar :: Int)
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (Int)
    {
        Macro -> declputvar (module, name, Units, & fix_long);
    }

    else
    {
        Macro -> declputvar (module, name, Units, & fix, & fix2);
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
        if (Global :: thisVar != NULL && (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN))
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

InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::CallDecl()@@@Defdeclputvar.cpp>");
}
void Defdeclputvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclputvar::CallInit(long nhru, long nlay)@@@Defdeclputvar.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclputvar::CallInit(long nhru, long nlay)@@@Defdeclputvar.cpp>");
}