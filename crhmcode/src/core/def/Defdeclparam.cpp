#include "DefCRHM.h"
#include "../InstrumentLogger.h"

Defdeclparam :: Defdeclparam (ClassMacro * Macro_): DefCRHM (Macro_)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::Defdeclparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclparam.cpp>");
    if (DefStringList -> at (0) == "decldiagparam")
    {
        visibility = TVISIBLE :: DIAGNOSTIC;
    }

    else
    {
        visibility = TVISIBLE :: USUAL;
    }

    name = DefStringList -> at (1);
    Dim = getTDim (DefStringList -> at (2));
    Default = DefStringList -> at (3);
    Min = DefStringList -> at (4);
    Max = DefStringList -> at (5);
    Description = DefStringList -> at (6);
    Units = DefStringList -> at (7);
    if (DefCRHM :: DefStringList -> size () > 8 && DefStringList -> at (8) == "Int")
    {
        Int = true;
    }

    else
    {
        Int = false;
    }

    if (DefCRHM :: DefStringList -> size () > 9)
    {
        nlay = Strtolong (DefStringList -> at (9));
    }

InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::Defdeclparam(ClassMacro * Macro_): DefCRHM (Macro_)@@@Defdeclparam.cpp>");
}
void Defdeclparam :: CallDecl ()
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::CallDecl()@@@Defdeclparam.cpp>");
    if (Int)
    {
        Macro -> declparam (name, Dim, Default, Min, Max, Description, Units, & fix_long_const, & fix2_long_const, nlay, visibility);
    }

    else
    {
        Macro -> declparam (name, Dim, Default, Min, Max, Description, Units, & fix_const, & fix2_const, Macro -> nhru, visibility);
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
        FP -> second.IndexMax = Macro -> nhru - 1;
        FP -> second.IndexMaxLay = Macro -> nhru - 1;
        FP -> second.Me = Macro;
        if (Int)
        {
            if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
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
            if (Dim == TDim :: NDEF || Dim == TDim :: NDEFN)
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

InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::CallDecl()@@@Defdeclparam.cpp>");
}
void Defdeclparam :: CallInit (long nhru, long nlay)
{
InstrumentLogger::instance()->log_instrument_log("<Defdeclparam::CallInit(long nhru, long nlay)@@@Defdeclparam.cpp>");
InstrumentLogger::instance()->log_instrument_log("</Defdeclparam::CallInit(long nhru, long nlay)@@@Defdeclparam.cpp>");
}