#include "../Classfilter.h"
#include "ClasssubV.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClasssubV :: ClasssubV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClasssubV::ClasssubV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClasssubV.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClasssubV::ClasssubV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClasssubV.cpp>");
}
void ClasssubV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClasssubV::doFunc(long Obs, long Line)@@@ClasssubV.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] - Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClasssubV::doFunc(long Obs, long Line)@@@ClasssubV.cpp>");
}