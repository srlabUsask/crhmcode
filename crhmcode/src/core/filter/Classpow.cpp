#include "../Classfilter.h"
#include "Classpow.h"
#include "../InstrumentLogger.h"

using namespace std;
Classpow :: Classpow (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpow::Classpow(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpow.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpow::Classpow(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpow.cpp>");
}
void Classpow :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpow::doFunc(long Obs, long Line)@@@Classpow.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            if (Constants [0] >= MyObs -> Dt1 && Constants [0] <= MyObs -> Dt2)
            {
                delay = (long) ((Constants [0] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = - 1;
            }

            if (Constants [1] > 0.0)
            {
                duration = (long) ((Constants [1] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            A = (double) Constants [2];
            B = (double) Constants [3];
            FirstTime = false;
        }

        if (Line < delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = A * pow ((static_cast < long long > (Line) - static_cast < long long > (delay) + 1) / double (MyObs -> Freq), B);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classpow::doFunc(long Obs, long Line)@@@Classpow.cpp>");
}