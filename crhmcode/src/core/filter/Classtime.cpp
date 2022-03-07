#include "../Classfilter.h"
#include "Classtime.h"
#include "../GlobalDll.h"
#include "../InstrumentLogger.h"

using namespace std;
Classtime :: Classtime (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classtime::Classtime(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classtime.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classtime::Classtime(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classtime.cpp>");
}
void Classtime :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classtime::doFunc(long Obs, long Line)@@@Classtime.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            option = (int) Constants [0];
            if (option)
            {
                start = 0.0;
            }

            else
            {
                start = floor (Global :: DTstart);
            }

            FirstTime = false;
        }

        Data [Vs - 1] [Obs] [Line] = double (start + Line / double (MyObs -> Freq));
    }

InstrumentLogger::instance()->log_instrument_log("</Classtime::doFunc(long Obs, long Line)@@@Classtime.cpp>");
}