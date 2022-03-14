#include "../Classfilter.h"
#include "ClassMissingFlag.h"
#include "../../InstrumentLogger.h"

using namespace std;
void ClassMissingFlag :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlag::doFunc(long Obs, long Line)@@@ClassMissingFlag.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = 1.0;
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlag::doFunc(long Obs, long Line)@@@ClassMissingFlag.cpp>");
}