#include "../Classfilter.h"
#include "Classabs.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classabs :: Classabs (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classabs::Classabs(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classabs.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classabs::Classabs(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classabs.cpp>");
}
void Classabs :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classabs::doFunc(long Obs, long Line)@@@Classabs.cpp>");
    Data [Vs - 1] [Obs] [Line] = abs (Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classabs::doFunc(long Obs, long Line)@@@Classabs.cpp>");
}