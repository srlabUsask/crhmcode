#include "../Classfilter.h"
#include "Classdiv.h"
#include "../InstrumentLogger.h"

using namespace std;
Classdiv :: Classdiv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classdiv::Classdiv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classdiv.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classdiv::Classdiv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classdiv.cpp>");
}
void Classdiv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classdiv::doFunc(long Obs, long Line)@@@Classdiv.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] / (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classdiv::doFunc(long Obs, long Line)@@@Classdiv.cpp>");
}