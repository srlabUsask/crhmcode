#include "../Classfilter.h"
#include "Classramp.h"
#include "../InstrumentLogger.h"

using namespace std;
Classramp :: Classramp (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classramp::Classramp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classramp.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classramp::Classramp(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classramp.cpp>");
}
void Classramp :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classramp::doFunc(long Obs, long Line)@@@Classramp.cpp>");
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
            Data [Vs - 1] [Obs] [Line] = 0.0;
            double X = (double) fmod (double (static_cast < long long > (Line) - static_cast < long long > (delay)) / double (period) * 2.0, 1.0);
            if (((Line + phase - delay) % period) >= period / 2)
            {
                Data [Vs - 1] [Obs] [Line] = (double) 1.0 - X;
            }

            else
            {
                Data [Vs - 1] [Obs] [Line] = X;
            }

        }

    }

InstrumentLogger::instance()->log_instrument_log("</Classramp::doFunc(long Obs, long Line)@@@Classramp.cpp>");
}