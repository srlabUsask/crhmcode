#include "../Classfilter.h"
#include "Classsub.h"
#include "../InstrumentLogger.h"

using namespace std;
Classsub :: Classsub (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classsub::Classsub(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classsub.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classsub::Classsub(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classsub.cpp>");
}
void Classsub :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classsub::doFunc(long Obs, long Line)@@@Classsub.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] - (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classsub::doFunc(long Obs, long Line)@@@Classsub.cpp>");
}