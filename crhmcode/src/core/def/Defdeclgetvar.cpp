#include "Defdeclgetvar.h"
#include "../InstrumentLogger.h"

Defdeclgetvar :: Defdeclgetvar (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::Defdeclgetvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclgetvar.cpp>");
    module = DefStringList -> at (1);
    name = DefStringList -> at (2);
    Units = DefStringList -> at (3);
InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::Defdeclgetvar(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclgetvar.cpp>");
}
void Defdeclgetvar :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::CallDecl()@@@Defdeclgetvar.cpp>");
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
        Macro -> declgetvar (module, name, Units, & fix_long_const, & fix2_long_const);
    }

    else
    {
        Macro -> declgetvar (module, name, Units, & fix_const, & fix2_const);
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
            if (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN)
            {
                FP -> second.kind = TV :: CRHMint2;
                FP -> second.ivalue2 = const_cast < long ** > (fix2_long_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHMint;
                FP -> second.ivalue = const_cast < long * > (fix_long_const);
            }

        }

        else
        {
            if (Global :: thisVar != NULL && (((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEF || ((ClassVar *) Global :: thisVar) -> dimen == TDim :: NDEFN))
            {
                FP -> second.kind = TV :: CRHM2;
                FP -> second.value2 = const_cast < double ** > (fix2_const);
            }

            else
            {
                FP -> second.kind = TV :: CRHM;
                FP -> second.value = const_cast < double * > (fix_const);
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::CallDecl()@@@Defdeclgetvar.cpp>");
}
void Defdeclgetvar :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclgetvar::CallInit(long nhru, long nlay)@@@Defdeclgetvar.cpp>");
    FP -> second.IndexMax = nhru - 1;
InstrumentLogger::instance()->log_instrument_log("</Defdeclgetvar::CallInit(long nhru, long nlay)@@@Defdeclgetvar.cpp>");
}