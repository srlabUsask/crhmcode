#if defined (_WIN32)
    #include "stdafx.h"
#endif

#include <stdio.h>
#include "CRHM_parse.h"
#include "../../core/InstrumentLogger.h"

using namespace std;
VarCHRM :: ~VarCHRM ()
{
    if (Me == NULL && (kind == TV :: CRHM || kind == TV :: CRHM2))
    {
        switch (kind) {
        case TV :: CRHM:
            delete [] value;
            value = NULL;
            break;
        case TV :: CRHM2:
            for (int ii = 0; ii <= IndexMaxLay; ii ++)
                delete [] value2 [ii];
            delete [] value2;
            value2 = NULL;
            break;
        default:
            break;
        }
    }

}
;

VarCHRM :: VarCHRM (const VarCHRM & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<VarCHRM::VarCHRM(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
    kind = Cl.kind;
    val = Cl.val;
    value = Cl.value;
    ivalue = Cl.ivalue;
    value2 = Cl.value2;
    ivalue2 = Cl.ivalue2;
    Ihh = Cl.Ihh;
    Ill = Cl.Ill;
    IndexMax = Cl.IndexMax;
    IndexMaxLay = Cl.IndexMaxLay;
    name = Cl.name;
    Me = Cl.Me;
InstrumentLogger::instance()->log_instrument_log("</VarCHRM::VarCHRM(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
}
VarCHRM & VarCHRM :: operator = (const VarCHRM & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<VarCHRM::operator=(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::operator=(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
        return * this;
    }

    kind = Cl.kind;
    val = Cl.val;
    value = Cl.value;
    ivalue = Cl.ivalue;
    value2 = Cl.value2;
    ivalue2 = Cl.ivalue2;
    Ihh = Cl.Ihh;
    Ill = Cl.Ill;
    IndexMax = Cl.IndexMax;
    IndexMaxLay = Cl.IndexMaxLay;
    name = Cl.name;

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::operator=(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</VarCHRM::operator=(const VarCHRM & Cl)@@@CRHM_parse.cpp>");
}
void VarCHRM :: put (double val_)
{
InstrumentLogger::instance()->log_instrument_log("<VarCHRM::put(double val_)@@@CRHM_parse.cpp>");
    switch (kind) {
    case TV :: LOCAL:
        val = val_;
        break;
    case TV :: CRHM:
        value [min < long > (Ihh, IndexMax)] = val_;
        break;
    case TV :: CRHM2:
        value2 [min < long > (Ill, IndexMaxLay)] [min < long > (Ihh, IndexMax)] = val_;
        break;
    case TV :: CRHMint:
        ivalue [min < long > (Ihh, IndexMax)] = (long) val_;
        break;
    case TV :: CRHMint2:
        ivalue2 [min < long > (Ill, IndexMaxLay)] [min < long > (Ihh, IndexMax)] = (long) val_;
        break;
    case TV :: FUNobs:
        if (name == "ReadAheadObs")
        {
            val = ! Me -> ReadAheadObsMacro ((long) val_);
        }

        else
        {
            val = ! Me -> WriteAheadObsMacro ((long) val_);
        }

        break;
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</VarCHRM::put(double val_)@@@CRHM_parse.cpp>");
}
double VarCHRM :: get (void)
{
InstrumentLogger::instance()->log_instrument_log("<VarCHRM::get(void)@@@CRHM_parse.cpp>");
    switch (kind) {
    case TV :: LOCAL:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return val;
    case TV :: CRHM:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return value [min < long > (Ihh, IndexMax)];
    case TV :: CRHM2:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return value2 [min < long > (Ill, IndexMaxLay)] [min < long > (Ihh, IndexMax)];
    case TV :: CRHMint:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return ivalue [min < long > (Ihh, IndexMax)];
    case TV :: CRHMint2:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return ivalue2 [min < long > (Ill, IndexMaxLay)] [min < long > (Ihh, IndexMax)];
    case TV :: FUNget:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return (* pget) ();
    case TV :: FUNobs:

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
        return (val);
    default:
        break;
    }

InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
    return - 999;
InstrumentLogger::instance()->log_instrument_log("</VarCHRM::get(void)@@@CRHM_parse.cpp>");
}long execbase :: Index;

execbase :: execbase (const execbase & Cl): eval (Cl.eval), oper (Cl.oper)
{
InstrumentLogger::instance()->log_instrument_log("<execbase::execbase(const execbase & Cl): eval (Cl.eval), oper (Cl.oper)@@@CRHM_parse.cpp>");
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;
InstrumentLogger::instance()->log_instrument_log("</execbase::execbase(const execbase & Cl): eval (Cl.eval), oper (Cl.oper)@@@CRHM_parse.cpp>");
}
execbase & execbase :: operator = (const execbase & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<execbase::operator=(const execbase & Cl)@@@CRHM_parse.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@CRHM_parse.cpp>");
        return * this;
    }

    eval = Cl.eval;
    oper = Cl.oper;
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;

InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@CRHM_parse.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@CRHM_parse.cpp>");
}