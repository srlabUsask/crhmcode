#include "../Classfilter.h"
#include "Classpowv.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classpowv :: Classpowv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpowv::Classpowv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpowv.cpp>");
    readargs ();
    if (! Error)
    {
        A = (double) Constants [0];
        B = (double) Constants [1];
    }

InstrumentLogger::instance()->log_instrument_log("</Classpowv::Classpowv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpowv.cpp>");
}
void Classpowv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpowv::doFunc(long Obs, long Line)@@@Classpowv.cpp>");
    Data [Vs - 1] [Obs] [Line] = A * pow (Data [0] [Obs] [Line], B);
InstrumentLogger::instance()->log_instrument_log("</Classpowv::doFunc(long Obs, long Line)@@@Classpowv.cpp>");
}