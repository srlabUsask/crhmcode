#include "../Classfilter.h"
#include "ClassRH_WtoI.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassRH_WtoI :: ClassRH_WtoI (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassRH_WtoI::ClassRH_WtoI(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassRH_WtoI.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassRH_WtoI::ClassRH_WtoI(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassRH_WtoI.cpp>");
}
void ClassRH_WtoI :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassRH_WtoI::doFunc(long Obs, long Line)@@@ClassRH_WtoI.cpp>");
    double T = Data [0] [Obs] [Line];
    double RH = Data [1] [Obs] [Line];
    if (T < 0.0)
    {
        Data [Vs - 1] [Obs] [Line] = (double) (RH * 0.9995 * exp (22.452 * T / (272.55 + T)) / exp (17.502 * T / (240.97 + T)));
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = RH;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassRH_WtoI::doFunc(long Obs, long Line)@@@ClassRH_WtoI.cpp>");
}