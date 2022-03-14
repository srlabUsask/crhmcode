#include "../Classfilter.h"
#include "ClassMissing0.h"
#include "../../InstrumentLogger.h"

using namespace std;
void ClassMissing0 :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing0::doFunc(long Obs, long Line)@@@ClassMissing0.cpp>");
    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = 0.0;
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing0::doFunc(long Obs, long Line)@@@ClassMissing0.cpp>");
}