#include "../Classfilter.h"
#include "ClassMissingC.h"
#include "../InstrumentLogger.h"

using namespace std;
void ClassMissingC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingC::doFunc(long Obs, long Line)@@@ClassMissingC.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = (double) Constants [2];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingC::doFunc(long Obs, long Line)@@@ClassMissingC.cpp>");
}