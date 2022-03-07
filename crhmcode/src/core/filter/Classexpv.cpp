#include "../Classfilter.h"
#include "Classexpv.h"
#include "../InstrumentLogger.h"

using namespace std;
Classexpv :: Classexpv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classexpv::Classexpv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classexpv.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) Constants [0];
        B = (double) Constants [0];
    }

InstrumentLogger::instance()->log_instrument_log("</Classexpv::Classexpv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classexpv.cpp>");
}
void Classexpv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classexpv::doFunc(long Obs, long Line)@@@Classexpv.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * exp (B * Data [0] [Obs] [Line]);
InstrumentLogger::instance()->log_instrument_log("</Classexpv::doFunc(long Obs, long Line)@@@Classexpv.cpp>");
}