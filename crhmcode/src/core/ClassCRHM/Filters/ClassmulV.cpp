#include "../Classfilter.h"
#include "ClassmulV.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassmulV :: ClassmulV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassmulV::ClassmulV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassmulV.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassmulV::ClassmulV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassmulV.cpp>");
}
void ClassmulV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassmulV::doFunc(long Obs, long Line)@@@ClassmulV.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassmulV::doFunc(long Obs, long Line)@@@ClassmulV.cpp>");
}