#include "../Classfilter.h"
#include "ClassMissingFlagAfter.h"
#include "../../InstrumentLogger.h"

using namespace std;
void ClassMissingFlagAfter :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlagAfter::doFunc(long Obs, long Line)@@@ClassMissingFlagAfter.cpp>");
    if (FirstTime)
    {
        First = Line;
        FirstTime = false;
    }

    else
    {
        Last = Line;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlagAfter::doFunc(long Obs, long Line)@@@ClassMissingFlagAfter.cpp>");
}
ClassMissingFlagAfter :: ~ClassMissingFlagAfter ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingFlagAfter::~ClassMissingFlagAfter()@@@ClassMissingFlagAfter.cpp>");
    for (int Obs = 0; Obs < ObsCnt; ++ Obs)
        for (int Line = First; Line <= Last; ++ Line) {
            if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
            {
                Data [Vs - 1] [Obs] [Line] = 1.0;
            }

            else
            {
                Data [Vs - 1] [Obs] [Line] = 0.0;
            }

        }
InstrumentLogger::instance()->log_instrument_log("</ClassMissingFlagAfter::~ClassMissingFlagAfter()@@@ClassMissingFlagAfter.cpp>");
}