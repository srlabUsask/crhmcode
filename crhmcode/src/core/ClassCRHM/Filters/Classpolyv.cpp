#include "../Classfilter.h"
#include "ClassFtoC.h"
#include "../../InstrumentLogger.h"

using namespace std;
Classpolyv :: Classpolyv (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<Classpolyv::Classpolyv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpolyv.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</Classpolyv::Classpolyv(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@Classpolyv.cpp>");
}
void Classpolyv :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<Classpolyv::doFunc(long Obs, long Line)@@@Classpolyv.cpp>");
    double x = Data [0] [Obs] [Line];
    Data [Vs - 1] [Obs] [Line] = (double) (Constants [0] + Constants [1] * x + Constants [2] * x * x + Constants [3] * x * x * x + Constants [4] * x * x * x * x);
InstrumentLogger::instance()->log_instrument_log("</Classpolyv::doFunc(long Obs, long Line)@@@Classpolyv.cpp>");
}