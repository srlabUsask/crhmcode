#include "execbase.h"
#include "../../InstrumentLogger.h"

long execbase :: Index;

execbase :: execbase (const execbase & Cl): eval (Cl.eval), oper (Cl.oper)
{
InstrumentLogger::instance()->log_instrument_log("<execbase::execbase(const execbase & Cl): eval (Cl.eval), oper (Cl.oper)@@@execbase.cpp>");
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;
InstrumentLogger::instance()->log_instrument_log("</execbase::execbase(const execbase & Cl): eval (Cl.eval), oper (Cl.oper)@@@execbase.cpp>");
}
execbase & execbase :: operator = (const execbase & Cl)
{
InstrumentLogger::instance()->log_instrument_log("<execbase::operator=(const execbase & Cl)@@@execbase.cpp>");
    if (this == & Cl)
    {

InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@execbase.cpp>");
        return * this;
    }

    eval = Cl.eval;
    oper = Cl.oper;
    s = Cl.s;
    Lvar = Cl.Lvar;
    OurIndex = Cl.OurIndex;
    OurOrder = Cl.OurOrder;

InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@execbase.cpp>");
    return * this;
InstrumentLogger::instance()->log_instrument_log("</execbase::operator=(const execbase & Cl)@@@execbase.cpp>");
}