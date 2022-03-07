#include "ClassMuskingum.h"
#include "InstrumentLogger.h"

ClassMuskingum :: ClassMuskingum (const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::ClassMuskingum(const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)@@@ClassMuskingum.cpp>");
    LastIn = new double [nhru];
    LastOut = new double [nhru];
    c0 = new double [nhru];
    c1 = new double [nhru];
    c2 = new double [nhru];
    ilag = new long [nhru];
    maxlag = new long [nhru];
    ulag = new long [nhru];
    long Biggest = 0;
    for (long hh = 0; hh < nhru; hh ++) {
        c0 [hh] = (Global :: Interval - 2.0 * k [hh] * X_M [hh]) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        c1 [hh] = (Global :: Interval + 2.0 * k [hh] * X_M [hh]) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        c2 [hh] = (2.0 * k [hh] * (1.0 - X_M [hh]) - Global :: Interval) / (2.0 * k [hh] * (1.0 - X_M [hh]) + Global :: Interval);
        ilag [hh] = (long) (max < double > (lag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
        if (setlag == - 1 || ilag [hh] > setlag)
        {
            maxlag [hh] = ilag [hh];
        }

        else
        {
            maxlag [hh] = setlag;
        }

        ulag [hh] = 0;
        LastIn [hh] = 0.0;
        LastOut [hh] = 0.0;
        if (maxlag [hh] > Biggest)
        {
            Biggest = maxlag [hh];
        }

    }
    LagArray = new double * [nhru];
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] = new double [maxlag [hh]];
        for (long jj = 0; jj < maxlag [hh]; jj ++)
            LagArray [hh] [jj] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ClassMuskingum(const double * inVar, double * outVar, const double * k, const double * X_M, const double * lag, const long nhru, const long setlag): inVar (inVar), outVar (outVar), nhru (nhru)@@@ClassMuskingum.cpp>");
}
ClassMuskingum :: ~ClassMuskingum ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::~ClassMuskingum()@@@ClassMuskingum.cpp>");
    delete [] LastIn;
    delete [] LastOut;
    delete [] c0;
    delete [] c1;
    delete [] c2;
    delete [] ilag;
    delete [] maxlag;
    delete [] ulag;
    for (long hh = 0; hh < nhru; hh ++)
        delete [] LagArray [hh];
    delete [] LagArray;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::~ClassMuskingum()@@@ClassMuskingum.cpp>");
}
void ClassMuskingum :: ChangeLag (const double * newlag, const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassMuskingum.cpp>");
    long newilag = (long) (max < double > (newlag [hh], 0.0) / 24.0 * Global :: Freq + 1.1);
    if (newilag == ilag [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassMuskingum.cpp>");
        return;
    }

    double * AccArray = new double [ilag [hh]];
    AccArray [0] = 0.0;
    for (int ii = 1; ii < ilag [hh]; ++ ii) {
        AccArray [ii] = AccArray [ii - 1] + LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    }
    delete [] LagArray [hh];
    LagArray [hh] = new double [newilag];
    ulag [hh] = 0;
    LagArray [hh] [0] = 0.0;
    double LastValue = 0.0;
    for (int mm = 1; mm < newilag - 1; ++ mm) {
        double Y = double (mm) / ((long long) newilag - 1ll) * ((long long) ilag [hh] - 1ll);
        int Yint = (int) (Y + 0.0001);
        if ((Yint + 1) > ilag [hh] - 1)
        {
            CRHMException Except ("Attempting to read out of bounds array address", TExcept :: TERMINATE);
            LogError (Except);
            throw (Except);
        }

        double Ydif = Y - Yint;
        double NewValue = AccArray [Yint] + Ydif * (AccArray [Yint + 1] - AccArray [Yint]);
        LagArray [hh] [(ulag [hh] + mm) % newilag] = NewValue - LastValue;
        LastValue = NewValue;
    }
    LagArray [hh] [(ulag [hh] + newilag - 1) % newilag] = AccArray [ilag [hh] - 1] - LastValue;
    delete [] AccArray;
    ilag [hh] = newilag;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::ChangeLag(const double * newlag, const long hh)@@@ClassMuskingum.cpp>");
}
void ClassMuskingum :: DoMuskingum ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::DoMuskingum()@@@ClassMuskingum.cpp>");
    for (long hh = 0; hh < nhru; hh ++) {
        LagArray [hh] [ulag [hh]] = inVar [hh];
        ulag [hh] = ++ ulag [hh] % ilag [hh];
        outVar [hh] = c0 [hh] * LagArray [hh] [ulag [hh]] + c1 [hh] * LastIn [hh] + c2 [hh] * LastOut [hh];
        LastIn [hh] = LagArray [hh] [ulag [hh]];
        LastOut [hh] = outVar [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::DoMuskingum()@@@ClassMuskingum.cpp>");
}
void ClassMuskingum :: DoMuskingum (const long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::DoMuskingum(const long hh)@@@ClassMuskingum.cpp>");
    LagArray [hh] [ulag [hh]] = inVar [hh];
    ulag [hh] = ++ ulag [hh] % ilag [hh];
    outVar [hh] = c0 [hh] * LagArray [hh] [ulag [hh]] + c1 [hh] * LastIn [hh] + c2 [hh] * LastOut [hh];
    LastIn [hh] = LagArray [hh] [ulag [hh]];
    LastOut [hh] = outVar [hh];
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::DoMuskingum(const long hh)@@@ClassMuskingum.cpp>");
}
double ClassMuskingum :: Left (int hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMuskingum::Left(int hh)@@@ClassMuskingum.cpp>");
    double Slag = 0;
    for (int ii = 1; ii < ilag [hh]; ++ ii)
        Slag += LagArray [hh] [(ulag [hh] + ii) % ilag [hh]];
    double Sstorage = (1.0 / (1.0 - c2 [hh])) * (c1 [hh] * LastIn [hh] + c2 [hh] * outVar [hh]);

InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::Left(int hh)@@@ClassMuskingum.cpp>");
    return Slag + Sstorage;
InstrumentLogger::instance()->log_instrument_log("</ClassMuskingum::Left(int hh)@@@ClassMuskingum.cpp>");
}