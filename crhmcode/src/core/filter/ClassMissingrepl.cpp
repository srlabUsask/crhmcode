#include "../Classfilter.h"
#include "ClassMissingrepl.h"
#include "../InstrumentLogger.h"

using namespace std;
void ClassMissingrepl :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingrepl::doFunc(long Obs, long Line)@@@ClassMissingrepl.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = Data [1] [Obs] [Line];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingrepl::doFunc(long Obs, long Line)@@@ClassMissingrepl.cpp>");
}