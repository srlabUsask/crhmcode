#include "../Classfilter.h"
#include "Classrefwind.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classrefwind :: Classrefwind (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrefwind::Classrefwind(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrefwind.cpp>");
    readargs ();
    if (! Error)
    {
        double d = (double) (Constants [2] * 2.0 / 3.0);
        double Z = (double) (Constants [2] * 0.123);
        Const = (double) (log ((Constants [1] - d) / Z) / log ((Constants [0] - d) / Z));
    }

InstrumentLogger::instance()->log_instrument_log("</Classrefwind::Classrefwind(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrefwind.cpp>");
}
void Classrefwind :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrefwind::doFunc(long Obs, long Line)@@@Classrefwind.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * Const;
InstrumentLogger::instance()->log_instrument_log("</Classrefwind::doFunc(long Obs, long Line)@@@Classrefwind.cpp>");
}