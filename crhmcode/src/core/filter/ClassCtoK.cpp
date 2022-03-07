#include "../Classfilter.h"
#include "ClassCtoK.h"
#include "../InstrumentLogger.h"

using namespace std;
ClassCtoK :: ClassCtoK (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCtoK::ClassCtoK(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCtoK.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassCtoK::ClassCtoK(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassCtoK.cpp>");
}
void ClassCtoK :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassCtoK::doFunc(long Obs, long Line)@@@ClassCtoK.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) ((Data [0] [Obs] [Line] + 273.15));
InstrumentLogger::instance()->log_instrument_log("</ClassCtoK::doFunc(long Obs, long Line)@@@ClassCtoK.cpp>");
}