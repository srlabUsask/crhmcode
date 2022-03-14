#include "../Classfilter.h"
#include "ClassForce.h"
#include "../../InstrumentLogger.h"

using namespace std;
void ClassForce :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassForce::doFunc(long Obs, long Line)@@@ClassForce.cpp>");
InstrumentLogger::instance()->log_instrument_log("</ClassForce::doFunc(long Obs, long Line)@@@ClassForce.cpp>");
}
ClassForce :: ClassForce (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassForce::ClassForce(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassForce.cpp>");
    readargs ();
    if (MyObs -> FilterCnt > 0)
    {
        error ("ForceFilter filter must be the first filter.");
    }

    if (Constants [0] > 288)
    {
        error ("ForceFilter filter interval cannot be less than 5 minutes ");
    }

    if (Constants [0] < 1)
    {
        error ("ForceFilter filter interval cannot be greater than daily ");
    }

    MyObs -> ForceInterval = (long) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</ClassForce::ClassForce(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassForce.cpp>");
}