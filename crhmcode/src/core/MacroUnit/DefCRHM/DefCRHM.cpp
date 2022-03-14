#include "DefCRHM.h"
#include "../../InstrumentLogger.h"

TDim DefCRHM :: getTDim (string D)
{
InstrumentLogger::instance()->log_instrument_log("<DefCRHM::getTDim(string D)@@@DefCRHM.cpp>");
    char table [] [7] = {"BASIN", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "NHRU", "NOBS", "NLAY", "NDEF", "NFREQ", "NREB", "NDEFN", "DEFX"};
    for (long ii = 0; ii < 21; ++ ii)
        if (D == table [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@DefCRHM.cpp>");
            return (TDim) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@DefCRHM.cpp>");
    return (TDim) - 1;
InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTDim(string D)@@@DefCRHM.cpp>");
}
TFun DefCRHM :: getTFunc (string D)
{
InstrumentLogger::instance()->log_instrument_log("<DefCRHM::getTFunc(string D)@@@DefCRHM.cpp>");
    char table [] [9] = {"FOBS", "W_MJ", "MJ_W", "AVG", "MIN", "MAX", "DTOT", "POS", "TOT", "FIRST", "LAST", "CNT", "CNT0", "INTVL"};
    for (long ii = 1; ii < 11; ++ ii)
        if (D == table [ii])
        {

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@DefCRHM.cpp>");
            return (TFun) ii;
        }

InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@DefCRHM.cpp>");
    return (TFun) - 1;
InstrumentLogger::instance()->log_instrument_log("</DefCRHM::getTFunc(string D)@@@DefCRHM.cpp>");
}