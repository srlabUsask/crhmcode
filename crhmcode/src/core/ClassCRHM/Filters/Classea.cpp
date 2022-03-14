#include "../Classfilter.h"
#include "Classea.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classea :: Classea (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classea::Classea(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classea.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classea::Classea(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classea.cpp>");
}
void Classea :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classea::doFunc(long Obs, long Line)@@@Classea.cpp>");
    if (Line == MyObs -> IndxMax)
    {
        for (int Obs = 0; Obs < ObsCnt; ++ Obs)
            for (long Line = MyObs -> IndxMin; Line <= MyObs -> IndxMax; ++ Line)
                Data [Vs - 1] [Obs] [Line] = (double) (estar (Data [0] [Obs] [Line]) * Data [1] [Obs] [Line] / 100.0);
    }

InstrumentLogger::instance()->log_instrument_log("</Classea::doFunc(long Obs, long Line)@@@Classea.cpp>");
}