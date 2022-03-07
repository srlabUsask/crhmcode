#include "../Classfilter.h"
#include "ClassFtoC.h"
#include "../InstrumentLogger.h"

using namespace std;
ClassFtoC :: ClassFtoC (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassFtoC::ClassFtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassFtoC.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassFtoC::ClassFtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassFtoC.cpp>");
}
void ClassFtoC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassFtoC::doFunc(long Obs, long Line)@@@ClassFtoC.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) ((Data [0] [Obs] [Line] - 32.0) * 5.0 / 9.0);
InstrumentLogger::instance()->log_instrument_log("</ClassFtoC::doFunc(long Obs, long Line)@@@ClassFtoC.cpp>");
}