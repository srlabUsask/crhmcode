#include "ClassSimpleRichard.h"
#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
ClassSimpleRichard * ClassSimpleRichard :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::klone(string name) const@@@ClassSimpleRichard.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::klone(string name) const@@@ClassSimpleRichard.cpp>");
    return new ClassSimpleRichard (name);
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::klone(string name) const@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::decl(void)@@@ClassSimpleRichard.cpp>");
    Description = "'A simple snow melt model (R. Essery).'";
    declvar ("alb", TDim :: NHRU, "Snow albedo", "()", & alb);
    declvar ("snowmelt", TDim :: NHRU, "snow melt", "(kg/m^2)", & snowmelt);
    declvar ("sursubl", TDim :: NHRU, "Surface sublimation", "(kg/m^2)", & sursubl);
    declvar ("meltclark", TDim :: NHRU, "snow melt delayed", "(kg/m^2)", & meltclark);
    declvar ("T0", TDim :: NHRU, "Surface temperature", "(" + string (DEGREE_CELSIUS) + ")", & T0);
    declvar ("LE", TDim :: NHRU, "Latent heat flux", "(W/m^2)", & LE);
    declvar ("H", TDim :: NHRU, "Sensible heat flux", "(W/m^2)", & H);
    declvar ("Hsm", TDim :: NHRU, "Snowmelt heat flux", "(W/m^2)", & Hsm);
    declvar ("LWn", TDim :: NHRU, "Net longwave radiation", "(W/m^2)", & LWn);
    declvar ("SWn", TDim :: NHRU, "Net shortwave radiation", "(W/m^2)", & SWn);
    declreadobs ("Qsi", TDim :: NHRU, "short-wave incoming", "W/m^2", & Qsi, HRU_OBS_Q);
    declreadobs ("Qli", TDim :: NHRU, "long-wave incoming", "W/m^2", & Qli, HRU_OBS_Q);
    declreadobs ("snow", TDim :: NHRU, "snowfall rate", "mm/int", & snow, HRU_OBS_misc);
    declreadobs ("t", TDim :: NHRU, "air temperature", "(" + string (DEGREE_CELSIUS) + ")", & t, HRU_OBS_t_rh_ea);
    declreadobs ("u", TDim :: NHRU, "windspeed", "m/s", & u, HRU_OBS_u);
    declreadobs ("rh", TDim :: NHRU, "relative humidity", "rh", & rh, HRU_OBS_t_rh_ea);
    decldiagparam ("a1", TDim :: NHRU, "[1.08e7]", "0.0", "1.0e8", "Albedo decay time constant for cold snow", "(s)", & a1);
    decldiagparam ("a2", TDim :: NHRU, "[7.2e5]", "0.0", "1.0e8", "Albedo decay time constant for melting snow", "(s)", & a2);
    decldiagparam ("amin", TDim :: NHRU, "[0.5]", "0.0", "1.0", "Minimum albedo for aged snow", "()", & amin);
    decldiagparam ("amax", TDim :: NHRU, "[0.84]", "0.0", "1.0", "Maximum albedo for fresh snow", "()", & amax);
    decldiagparam ("smin", TDim :: NHRU, "[10]", "0.0", "20", "Minimum snowfall to refresh snow albedo", "(mm)", & smin);
    declparam ("Z0snow", TDim :: NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", & Z0snow);
    declparam ("Zref", TDim :: NHRU, "[2]", "0.0", "100.0", "Reference height", "(m)", & Zref);
    decldiagparam ("Pa", TDim :: NHRU, "[84]", "10", "1e3", "Average surface pressure", "(KPa)", & Pa);
    decldiagparam ("Kstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "storage constant", "(d)", & Kstorage);
    decldiagparam ("Lag", TDim :: NHRU, "[0.0]", "0.0", "960.0", "lag delay", "(h)", & Lag);
    declputvar ("*", "SWE", "(mm)", & SWE);
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::decl(void)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::init(void)@@@ClassSimpleRichard.cpp>");
    nhru = getdim (TDim :: NHRU);
    Delays = new ClassClark (snowmelt, meltclark, Kstorage, Lag, nhru);
    dt = 3600 * 24 / Global :: Freq;
    for (hh = 0; hh < nhru; ++ hh) {
        T0 [hh] = 0.0;
        SWE [hh] = 0.0;
        alb [hh] = 0.84;
        LE [hh] = 0.0;
        H [hh] = 0.0;
        Hsm [hh] = 0.0;
        LWn [hh] = 0.0;
        SWn [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::init(void)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::run(void)@@@ClassSimpleRichard.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        double Q1 = (rh [hh] / 100.) * Common :: Qs (Pa [hh], t [hh]);
        double U1 = max < double > (u [hh], 1.0e-3);
        SURF (hh, Q1, U1);
        U1 = 0;
    }
    Delays -> DoClark ();
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::run(void)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: EXCH (long hh, double Q1, double U1, double & CH)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::EXCH(long hh, double Q1, double U1, double & CH)@@@ClassSimpleRichard.cpp>");
    double CHn, RiB, fh, fz, dT, dQ;
    CHn = sqr (0.4) / (log (Zref [hh] / Z0snow [hh]) * log (Zref [hh] / Z0snow [hh]));
    dT = t [hh] - T0 [hh];
    dQ = Q1 - Common :: Qs (Pa [hh], T0 [hh]);
    RiB = 9.81 * Zref [hh] * (dT / (t [hh] + CRHM_constants :: Tm) + 0.61 * dQ) / sqr (U1);
    if (RiB >= 0.0)
    {
        fh = 1.0 / (1.0 + 10.0 * RiB);
    }

    else
    {
        fz = sqrt (Z0snow [hh] / (Zref [hh] + Z0snow [hh])) / 4.0;
        fh = 1.0 - 1.0 * RiB / (1.0 + 10.0 * CHn * sqrt (- RiB) / fz);
    }

    CH = CHn * fh;
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::EXCH(long hh, double Q1, double U1, double & CH)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: ALBEDO (long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::ALBEDO(long hh)@@@ClassSimpleRichard.cpp>");
    if (T0 [hh] < 0)
    {
        alb [hh] = alb [hh] - dt / a1 [hh];
    }

    else
    {
        alb [hh] = (alb [hh] - amin [hh]) * exp (- dt / a2 [hh]) + amin [hh];
    }

    alb [hh] = alb [hh] + (amax [hh] - alb [hh]) * snow [hh] / smin [hh];
    if (alb [hh] < amin [hh])
    {
        alb [hh] = amin [hh];
    }

    if (alb [hh] > amax [hh])
    {
        alb [hh] = amax [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::ALBEDO(long hh)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: SURF (long hh, double Q1, double U1)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::SURF(long hh, double Q1, double U1)@@@ClassSimpleRichard.cpp>");
    double A1;
    double Ch;
    double dQ1;
    double D;
    double R1;
    double rho;
    double rKh;
    double rKPM;
    EXCH (hh, Q1, U1, Ch);
    A1 = 4 * CRHM_constants :: sbc * pow (t [hh] + CRHM_constants :: Tm, 3.0f);
    dQ1 = Common :: Qs (Pa [hh], t [hh]) - Q1;
    D = 0.62 * CRHM_constants :: Ls * Common :: Qs (Pa [hh], t [hh]) / (CRHM_constants :: Rgas * sqr (t [hh] + CRHM_constants :: Tm));
    R1 = (1.0f - alb [hh]) * Qsi [hh] + Qli [hh] - CRHM_constants :: sbc * pow (t [hh] + CRHM_constants :: Tm, 4.0f);
    rho = Pa [hh] * 1000.0f / (CRHM_constants :: Rgas * CRHM_constants :: Tm);
    rKh = rho * Ch * U1;
    rKPM = rKh / ((CRHM_constants :: Cp + CRHM_constants :: Ls * D) * rKh + A1);
    LE [hh] = CRHM_constants :: Ls * rKPM * (D * R1 + (CRHM_constants :: Cp * rKh + A1) * dQ1);
    H [hh] = CRHM_constants :: Cp * rKPM * (R1 - CRHM_constants :: Ls * rKh * dQ1);
    SWn [hh] = (1.0 - alb [hh]) * Qsi [hh];
    LWn [hh] = H [hh] + LE [hh] - SWn [hh];
    T0 [hh] = t [hh] + (R1 - H [hh] - LE [hh]) / A1;
    Hsm [hh] = 0.0;
    if (T0 [hh] > 0 && SWE [hh] > 0.0)
    {
        T0 [hh] = 0.0;
        LE [hh] = CRHM_constants :: Ls * rKh * (dQ1 + D * (T0 [hh] - t [hh]));
        H [hh] = CRHM_constants :: Cp * rKh * (T0 [hh] - t [hh]);
        SWn [hh] = (1.0 - alb [hh]) * Qsi [hh];
        LWn [hh] = Qli [hh] - CRHM_constants :: sbc * pow (t [hh] + CRHM_constants :: Tm, 4.0f) + A1 * (t [hh] - T0 [hh]);
        Hsm [hh] = SWn [hh] + LWn [hh] - LE [hh] - H [hh];
    }

    SWE [hh] = SWE [hh] + snow [hh];
    snowmelt [hh] = Hsm [hh] / CRHM_constants :: Lf * dt;
    sursubl [hh] = - LE [hh] / CRHM_constants :: Ls * dt;
    if (snowmelt [hh] + sursubl [hh] > SWE [hh])
    {
        snowmelt [hh] = SWE [hh] - sursubl [hh];
        if (snowmelt [hh] < 0.0)
        {
            snowmelt [hh] = 0.0;
            sursubl [hh] = SWE [hh];
        }

    }

    SWE [hh] -= (snowmelt [hh] + sursubl [hh]);
    SWE [hh] = max < double > (SWE [hh], 0.0);
    ALBEDO (hh);
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::SURF(long hh, double Q1, double U1)@@@ClassSimpleRichard.cpp>");
}
void ClassSimpleRichard :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSimpleRichard::finish(bool good)@@@ClassSimpleRichard.cpp>");
    delete Delays;
InstrumentLogger::instance()->log_instrument_log("</ClassSimpleRichard::finish(bool good)@@@ClassSimpleRichard.cpp>");
}