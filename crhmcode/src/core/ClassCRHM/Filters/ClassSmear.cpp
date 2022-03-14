#include "../Classfilter.h"
#include "ClassSmear.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassSmear :: ClassSmear (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSmear::ClassSmear(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)@@@ClassSmear.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassSmear::ClassSmear(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), Minus (false)@@@ClassSmear.cpp>");
}
void ClassSmear :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSmear::doFunc(long Obs, long Line)@@@ClassSmear.cpp>");
    if (FirstTime)
    {
        if (Constants [0] < 0.0)
        {
            Minus = true;
        }

        if (Constants [0] <= 0.0)
        {
            Constants [0] = MyObs -> Dt1;
        }

        if (Constants [1] <= 0.0)
        {
            Constants [1] = MyObs -> Dt2;
        }

        Constants [0] = MyObs -> Dt1 - MyObs -> Interval / 2.0;
        Constants [1] = MyObs -> Dt2 + MyObs -> Interval / 2.0;
        FirstTime = false;
    }

    double now = MyObs -> Dt1 + Line * MyObs -> Interval;
    double delta = MyObs -> Interval / 2.0;
    double now0 = fmod (now, 1.0);
    if (now0 > - delta && now0 < delta)
    {
        double value = Data [0] [Obs] [Line - MyObs -> Freq + 1] / MyObs -> Freq;
        if (now > Constants [0] && now < Constants [1] && ((Minus && value < 0.0) || ! Minus))
        {
            if (value < 0.0)
            {
                value = - value;
            }

            for (long ii = 0; ii < MyObs -> Freq; ++ ii) {
                if (Line - ii < 0)
                {
                    break;
                }

                Data [Vs - 1] [Obs] [Line - ii] = value;
            }
        }

        else
        {
            for (long ii = 0; ii < MyObs -> Freq; ++ ii) {
                if (Line - ii < 0)
                {
                    break;
                }

                Data [Vs - 1] [Obs] [Line - ii] = Data [0] [Obs] [Line - ii];
            }
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSmear::doFunc(long Obs, long Line)@@@ClassSmear.cpp>");
}