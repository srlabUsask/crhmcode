#include "../Classfilter.h"
#include "ClassaddV.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassaddV :: ClassaddV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassaddV::ClassaddV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassaddV.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassaddV::ClassaddV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassaddV.cpp>");
}
void ClassaddV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassaddV::doFunc(long Obs, long Line)@@@ClassaddV.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] + Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassaddV::doFunc(long Obs, long Line)@@@ClassaddV.cpp>");
}