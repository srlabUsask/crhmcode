#include "../Classfilter.h"
#include "ClassKtoC.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassKtoC :: ClassKtoC (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKtoC::ClassKtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassKtoC.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassKtoC::ClassKtoC(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassKtoC.cpp>");
}
void ClassKtoC :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassKtoC::doFunc(long Obs, long Line)@@@ClassKtoC.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) (Data [0] [Obs] [Line] - 273.15);
InstrumentLogger::instance()->log_instrument_log("</ClassKtoC::doFunc(long Obs, long Line)@@@ClassKtoC.cpp>");
}