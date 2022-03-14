#include "../Classfilter.h"
#include "ClassReplace.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassReplace :: ClassReplace (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)
{
InstrumentLogger::instance()->log_instrument_log("<ClassReplace::ClassReplace(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassReplace.cpp>");
    readargs ();
InstrumentLogger::instance()->log_instrument_log("</ClassReplace::ClassReplace(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes)@@@ClassReplace.cpp>");
}
void ClassReplace :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassReplace::doFunc(long Obs, long Line)@@@ClassReplace.cpp>");
    long shift = thisVar -> FileData -> IndxMin;
    for (int Obs = 0; Obs < ObsCnt; ++ Obs)
        outVar -> FileData -> Data [Obs + DataIndx [Vs - 1]] [Line + shift] = Data [0] [Obs] [Line];
InstrumentLogger::instance()->log_instrument_log("</ClassReplace::doFunc(long Obs, long Line)@@@ClassReplace.cpp>");
}