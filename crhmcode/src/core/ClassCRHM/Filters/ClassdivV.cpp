#include "../Classfilter.h"
#include "ClassdivV.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassdivV :: ClassdivV (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassdivV::ClassdivV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassdivV.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassdivV::ClassdivV(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassdivV.cpp>");
}
void ClassdivV :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassdivV::doFunc(long Obs, long Line)@@@ClassdivV.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] / Data [1] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassdivV::doFunc(long Obs, long Line)@@@ClassdivV.cpp>");
}