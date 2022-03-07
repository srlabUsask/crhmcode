#include "../Classfilter.h"
#include "Classrh.h"
#include "../InstrumentLogger.h"

using namespace std;
Classrh :: Classrh (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrh::Classrh(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrh.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classrh::Classrh(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrh.cpp>");
}
void Classrh :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrh::doFunc(long Obs, long Line)@@@Classrh.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) (Data [1] [Obs] [Line] / estar (Data [0] [Obs] [Line]) * 100.0);
InstrumentLogger::instance()->log_instrument_log("</Classrh::doFunc(long Obs, long Line)@@@Classrh.cpp>");
}