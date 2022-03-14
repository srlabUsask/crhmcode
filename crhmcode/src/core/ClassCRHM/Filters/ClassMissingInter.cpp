#include "../Classfilter.h"
#include "ClassMissingInter.h"
#include "../../InstrumentLogger.h"

using namespace std;
ClassMissingInter :: ClassMissingInter (ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::ClassMissingInter(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassMissingInter.cpp>");
    readargs ();
    GoodData = new double [ObsCnt];
    LastGoodData = new long [ObsCnt];
InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::ClassMissingInter(ClassData * MyObs, string ToVar, string args, string argtypes): Classfilter (MyObs, ToVar, args, argtypes), GoodData (NULL)@@@ClassMissingInter.cpp>");
}
void ClassMissingInter :: doFunc (long Obs, long Line)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::doFunc(long Obs, long Line)@@@ClassMissingInter.cpp>");
    static bool Warned = false;
    if (FirstTime)
    {
        if ((Data [0] [Obs] [Line] <= Constants [0] || Data [0] [Obs] [Line] >= Constants [1]) && ! Warned)
        {
            LogError ("Missing data in first interval of " + MyObs -> DataFileName, TExcept :: WARNING);
            Warned = true;
            LastGoodData [Obs] = - 1;

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassMissingInter.cpp>");
            return;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        LastGoodData [Obs] = Line;
        if (Obs + 1 >= ObsCnt)
        {
            FirstTime = false;
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassMissingInter.cpp>");
        return;
    }

    if (Data [0] [Obs] [Line] > Constants [0] && Data [0] [Obs] [Line] < Constants [1])
    {
        if (Line - 1 > LastGoodData [Obs] && LastGoodData [Obs] != - 1)
        {
            double dif = (Data [0] [Obs] [Line] - GoodData [Obs]) / (static_cast < long long > (Line) - static_cast < long long > (LastGoodData [Obs]));
            for (int ii = LastGoodData [Obs] + 1; ii < Line; ++ ii)
                Data [Vs - 1] [Obs] [ii] = Data [Vs - 1] [Obs] [ii - 1] + dif;
        }

        Data [Vs - 1] [Obs] [Line] = Data [0] [Obs] [Line];
        GoodData [Obs] = Data [0] [Obs] [Line];
        LastGoodData [Obs] = Line;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::doFunc(long Obs, long Line)@@@ClassMissingInter.cpp>");
}
ClassMissingInter :: ~ClassMissingInter ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMissingInter::~ClassMissingInter()@@@ClassMissingInter.cpp>");
    delete [] GoodData;
    delete [] LastGoodData;
InstrumentLogger::instance()->log_instrument_log("</ClassMissingInter::~ClassMissingInter()@@@ClassMissingInter.cpp>");
}