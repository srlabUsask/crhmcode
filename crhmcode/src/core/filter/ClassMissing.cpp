#include "../Classfilter.h"
#include "ClassMissing.h"
#include "../InstrumentLogger.h"

using namespace std;
ClassMissing :: ClassMissing (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::ClassMissing(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassMissing.cpp>");
    readargs ();
    GoodData = new double [ObsCnt];
InstrumentLogger::instance()->log_instrument_log("</ClassMissing::ClassMissing(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassMissing.cpp>");
}
void ClassMissing :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::doFunc(long Obs, long Line)@@@ClassMissing.cpp>");
    static bool Warned = false;
    if (FirstTime)
    {
        if ((Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1]) && ! Warned)
        {
            LogError ("Missing data in first interval of " + MyObs -> DataFileName, TExcept :: WARNING);
            Warned = true;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        if (Obs + 1 >= ObsCnt)
        {
            FirstTime = false;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing::doFunc(long Obs, long Line)@@@ClassMissing.cpp>");
        return;
    }

    if (Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1])
    {
        Data [Vs - 1] [Obs] [Line] = GoodData [Obs];
    }

    else
    {
        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissing::doFunc(long Obs, long Line)@@@ClassMissing.cpp>");
}
ClassMissing :: ~ClassMissing ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissing::~ClassMissing()@@@ClassMissing.cpp>");
    delete [] GoodData;
InstrumentLogger::instance()->log_instrument_log("</ClassMissing::~ClassMissing()@@@ClassMissing.cpp>");
}