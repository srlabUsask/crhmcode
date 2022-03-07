#include "../Classfilter.h"
#include "ClassFtoC.h"
#include "../InstrumentLogger.h"

using namespace std;
Classrandom :: Classrandom (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classrandom::Classrandom(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrandom.cpp>");
    readargs ();
    if (! Error)
    {
        srand ((unsigned) Constants [0]);
    }

InstrumentLogger::instance()->log_instrument_log("</Classrandom::Classrandom(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classrandom.cpp>");
}
void Classrandom :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classrandom::doFunc(long Obs, long Line)@@@Classrandom.cpp>");
    Data [Vs - 1] [Obs] [Line] = (double) rand () / RAND_MAX;
InstrumentLogger::instance()->log_instrument_log("</Classrandom::doFunc(long Obs, long Line)@@@Classrandom.cpp>");
}