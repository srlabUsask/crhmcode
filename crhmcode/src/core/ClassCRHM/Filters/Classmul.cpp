#include "../Classfilter.h"
#include "Classmul.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classmul :: Classmul (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classmul::Classmul(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classmul.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classmul::Classmul(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classmul.cpp>");
}
void Classmul :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classmul::doFunc(long Obs, long Line)@@@Classmul.cpp>");
    Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line] * (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</Classmul::doFunc(long Obs, long Line)@@@Classmul.cpp>");
}