#include "../Classfilter.h"
#include "Classjulian.h"
#include "../InstrumentLogger.h"

using namespace std;
Classjulian :: Classjulian (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classjulian::Classjulian(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classjulian.cpp>");
    readargs ();
    if (! Error)
    {
        option = (int) Constants [0];
    }

InstrumentLogger::instance()->log_instrument_log("</Classjulian::Classjulian(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classjulian.cpp>");
}
void Classjulian :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classjulian::doFunc(long Obs, long Line)@@@Classjulian.cpp>");
    switch (option) {
    case 0:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("now");
        break;
    case 1:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("start");
        break;
    case 2:
        Data [Vs - 1] [Obs] [Line] = (double) julian ("end");
        break;
    default:
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</Classjulian::doFunc(long Obs, long Line)@@@Classjulian.cpp>");
}