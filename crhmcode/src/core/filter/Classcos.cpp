#include "../Classfilter.h"
#include "Classcos.h"
#include "../InstrumentLogger.h"

Classcos :: Classcos (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classcos::Classcos(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classcos.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classcos::Classcos(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classcos.cpp>");
}
void Classcos :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classcos::doFunc(long Obs, long Line)@@@Classcos.cpp>");
    if (! Error)
    {
        if (FirstTime)
        {
            period = (long) (Constants [0] * MyObs -> Freq);
            phase = (long) (Constants [1] * MyObs -> Freq);
            if (Constants [2] > MyObs -> Dt1 && Constants [2] < MyObs -> Dt2)
            {
                delay = (long) ((Constants [2] - MyObs -> Dt1) * MyObs -> Freq);
            }

            else
            {
                delay = 0;
            }

            if (Constants [3] > 0.0)
            {
                duration = (long) ((Constants [3] - MyObs -> Dt1) * MyObs -> Freq - 1);
                if (duration <= 0)
                {
                    duration = MyObs -> IndxMax;
                }

            }

            else
            {
                duration = MyObs -> IndxMax;
            }

            FirstTime = false;
        }

        if (Line <= delay || Line > duration)
        {
            Data [Vs - 1] [Obs] [Line] = 0.0;
        }

        else
        {
            Data [Vs - 1] [Obs] [Line] = (double) cos ((double (Line) / period - double (phase) / period) * 2 * M_PI);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classcos::doFunc(long Obs, long Line)@@@Classcos.cpp>");
}using namespace std;
