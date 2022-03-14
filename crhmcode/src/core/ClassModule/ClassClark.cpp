#include "ClassClark.h"
#include "../InstrumentLogger.h"

ClassClark :: ClassClark (const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ClassClark(const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)@@@ClassClark.cpp>");
    LastIn = new double [nhru];
    LastOut = new double [nhru];
    c01 = new double [nhru];
    c2 = new double [nhru];
    NO_lag_release = new double [nhru];
    ilag = new long [nhru];
    maxlag = new long [nhru];
    ulag = new long [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        c01 [hh] = Global :: Interval * 0.5 / (kstorage [hh] + Global :: Interval * 0.5);
        c2 [hh] = (kstorage [hh] - Global :: Interval * 0.5) / (kstorage [hh] + Global :: Interval * 0.5);
        ilag [hh] = (long) (max < double > (lag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
        if (setlag == - 1 || ilag [hh] > setlag)
        {
            maxlag [hh] = ilag [hh] + 1;
        }

        else
        {
            maxlag [hh] = setlag + 1;
        }

        ulag [hh] = 0;
        LastIn [hh] = 0.0;
        LastOut [hh] = 0.0;
        NO_lag_release [hh] = 0.0;
    }
    LagArray = new double * [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] = new double [maxlag [hh]];
        for (long jj = 0; jj < maxlag [hh]; jj ++)
            LagArray [hh] [jj] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ClassClark(const double * inVar, double * outVar, const double * kstorage, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), kstorage (kstorage), nhru (nhru)@@@ClassClark.cpp>");
}
ClassClark :: ~ClassClark ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::~ClassClark()@@@ClassClark.cpp>");
    delete [] LastIn;
    delete [] LastOut;
    delete [] c01;
    delete [] c2;
    delete [] NO_lag_release;
    delete [] ilag;
    delete [] maxlag;
    delete [] ulag;
    for (long hh = 0; hh < nhru; hh ++)
        delete [] LagArray [hh];
    delete [] LagArray;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::~ClassClark()@@@ClassClark.cpp>");
}
double ClassClark :: ChangeStorage (const double * kstorage, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassClark.cpp>");
    double Last_c01 = c01 [hh];
    double Last_c2 = c2 [hh];
    if (c2 [hh] >= 1.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassClark.cpp>");
        return 0.0;
    }

    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c01 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);
    c01 [hh] = Global :: Interval * 0.5 / (kstorage [hh] + Global :: Interval * 0.5);
    c2 [hh] = (kstorage [hh] - Global :: Interval * 0.5) / (kstorage [hh] + Global :: Interval * 0.5);
    if (Sstorage <= 0.0 || Last_c01 == c01 [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassClark.cpp>");
        return 0.0;
    }

    LastOut [hh] = (Sstorage * (1.0 - c2 [hh]) - c01 [hh] * LastIn [hh]) / c2 [hh];

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassClark.cpp>");
    return Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeStorage(const double * kstorage, const long hh)@@@ClassClark.cpp>");
}
double ClassClark :: ChangeLag (const double * newlag, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassClark.cpp>");
    double LastValue;
    double Lag_storage = 0.0;
    long newilag = (long) (max < double > (newlag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Lag_storage += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    if (newilag == ilag [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassClark.cpp>");
        return Lag_storage;
    }

    double * AccArray = new double [ilag [hh]];
    AccArray [0] = 0.0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        AccArray [ii] = AccArray [ii - 1] + LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    NO_lag_release [hh] = 0.0;
    delete [] LagArray [hh];
    LagArray [hh] = new double [newilag];
    ulag [hh] = 0;
    LagArray [hh] [ulag [hh]] = 0;
    for (int ii = 1; ii < newilag; ++ ii)
        LagArray [hh] [ii] = 0.0;
    if (newilag == 1)
    {
        NO_lag_release [hh] = AccArray [ilag [hh] - 1];
    }

    else
    if (ilag [hh] > 1 && AccArray [ilag [hh] - 1] > 0.0)
    {
        LastValue = 0.0;
        for (int mm = 1; mm < newilag - 1; ++ mm) {
            double Y = double (mm) / ((long long) newilag - 1ll) * ((long long) ilag [hh] - 1ll);
            int Yint = (int) (Y + 0.0001);
            double Ydif = Y - Yint;
            double NewValue = AccArray [Yint] + Ydif * (AccArray [Yint + 1] - AccArray [Yint]);
            LagArray [hh] [(ulag [hh] + mm) % newilag] = NewValue - LastValue;
            LastValue = NewValue;
        }
        LagArray [hh] [(ulag [hh] + newilag - 1) % newilag] = AccArray [ilag [hh] - 1] - LastValue;
    }

    delete [] AccArray;
    ilag [hh] = newilag;

InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassClark.cpp>");
    return Lag_storage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::ChangeLag(const double * newlag, const long hh)@@@ClassClark.cpp>");
}
void ClassClark :: DoClark ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::DoClark()@@@ClassClark.cpp>");
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] [ulag [hh]] = inVar [hh] + NO_lag_release [hh];
        NO_lag_release [hh] = 0.0;
        ulag [hh] = ++ ulag [hh] % ilag [hh];
        outVar [hh] = c01 [hh] * (LagArray [hh] [ulag [hh]] + LastIn [hh]) + c2 [hh] * LastOut [hh];
        LastIn [hh] = LagArray [hh] [ulag [hh]];
        LastOut [hh] = outVar [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassClark::DoClark()@@@ClassClark.cpp>");
}
void ClassClark :: DoClark (const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::DoClark(const long hh)@@@ClassClark.cpp>");
    LagArray [hh] [ulag [hh]] = inVar [hh] + NO_lag_release [hh];
    NO_lag_release [hh] = 0.0;
    ulag [hh] = ++ ulag [hh] % ilag [hh];
    outVar [hh] = c01 [hh] * (LagArray [hh] [ulag [hh]] + LastIn [hh]) + c2 [hh] * LastOut [hh];
    LastIn [hh] = LagArray [hh] [ulag [hh]];
    LastOut [hh] = outVar [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassClark::DoClark(const long hh)@@@ClassClark.cpp>");
}
double ClassClark :: Left (int hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassClark::Left(int hh)@@@ClassClark.cpp>");
    double Slag = 0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Slag += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    if (c2 [hh] >= 1.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassClark.cpp>");
        return 0.0;
    }

    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c01 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);

InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassClark.cpp>");
    return Slag + Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassClark::Left(int hh)@@@ClassClark.cpp>");
}