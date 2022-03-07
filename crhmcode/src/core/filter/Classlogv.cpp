#include "../Classfilter.h"
#include "Classlogv.h"
#include "../InstrumentLogger.h"

using namespace std;
Classlogv :: Classlogv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classlogv::Classlogv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classlogv.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) fabs (Constants [0]);
        B = (double) fabs (Constants [1]);
    }

InstrumentLogger::instance()->log_instrument_log("</Classlogv::Classlogv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classlogv.cpp>");
}
void Classlogv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classlogv::doFunc(long Obs, long Line)@@@Classlogv.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * log (B * Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classlogv::doFunc(long Obs, long Line)@@@Classlogv.cpp>");
}