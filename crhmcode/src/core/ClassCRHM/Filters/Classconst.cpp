#include "../Classfilter.h"
#include "Classconst.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classconst :: Classconst (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classconst::Classconst(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classconst.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classconst::Classconst(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classconst.cpp>");
}
void Classconst :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classconst::doFunc(long Obs, long Line)@@@Classconst.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classconst::doFunc(long Obs, long Line)@@@Classconst.cpp>");
}