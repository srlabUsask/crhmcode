#include "../Classfilter.h"
#include "ClassTimeshift.h"
#include "../InstrumentLogger.h"

using namespace std;
ClassTimeshift :: ClassTimeshift (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassTimeshift::ClassTimeshift(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassTimeshift.cpp>");
    readargs ();
    MyObs -> TimeShiftFilter = (double) Constants [0];
InstrumentLogger::instance()->log_instrument_log("</ClassTimeshift::ClassTimeshift(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassTimeshift.cpp>");
}