#include "../Classfilter.h"
#include "ClassFtoC.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classadd :: Classadd (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classadd::Classadd(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classadd.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classadd::Classadd(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classadd.cpp>");
}
void Classadd :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classadd::doFunc(long Obs, long Line)@@@Classadd.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] + (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classadd::doFunc(long Obs, long Line)@@@Classadd.cpp>");
}