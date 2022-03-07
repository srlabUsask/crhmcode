#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classfrostdepth.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classfrostdepth * Classfrostdepth :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classfrostdepth::klone(string name) const@@@Classfrostdepth.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::klone(string name) const@@@Classfrostdepth.cpp>");
    return new Classfrostdepth (name);
InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::klone(string name) const@@@Classfrostdepth.cpp>");
}
void Classfrostdepth :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classfrostdepth::decl(void)@@@Classfrostdepth.cpp>");
    Description = "'Frost penetration (Van Wijk W. R., (1963) Physics of Plant Environment. North-Holland Publishing Company - Amsterdam, pp.166).'";
    declstatvar ("frostdepth", TDim :: NHRU, "frost penetration", "(m)", & frostdepth);
    declstatvar ("Findex", TDim :: NHRU, "freezing index", "(d* " + string (DEGREE_CELSIUS) + ")", & Findex);
    declstatvar ("Tfreeze", TDim :: NHRU, "duration of freezing period in days", "(d)", & Tfreeze);
    declstatvar ("Lacc", TDim :: NHRU, "cumulative effective latent heat", "(MJ/m^3)", & Lacc);
    declstatvar ("Cacc", TDim :: NHRU, "cumulative effective heat capacity", "(MJ/(m^3*K))", & Cacc);
    declstatvar ("Kacc", TDim :: NHRU, "cumulative effective thermal conductivity", "(W/(m*K))", & Kacc);
    declparam ("Ta", TDim :: NHRU, "[10]", "-10.0", "50.0", "annual air temperature", "(" + string (DEGREE_CELSIUS) + ")", & Ta);
    declparam ("soil_type", TDim :: NLAY, "[2]", "1", "4", "HRU soil type: 1= sand, 2= loam, 3= clay, 4 = organic", "()", & soil_type, & soil_type_lay);
    declparam ("por", TDim :: NLAY, "[0.5]", "0.0", "1.0", "porosity", "(m^3/m^3)", & por, & por_lay);
    declparam ("theta", TDim :: NLAY, "[0.5]", "0.0", "1.0", "degree of saturation", "(m^3/m^3)", & theta, & theta_lay);
    declparam ("d", TDim :: NLAY, "[2.0]", "0.0", "100.0", "layer depth", "(m)", & d, & d_lay);
    declparam ("hru_lat", TDim :: NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string (DEGREE) + ")", & hru_lat);
    declgetvar ("*", "hru_tmean", "(" + string (DEGREE_CELSIUS) + ")", & hru_tmean);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "snowdepth", "(m)", & snowdepth);
InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::decl(void)@@@Classfrostdepth.cpp>");
}const double ko = 0.21;
const double km = 2.50;
const double ka = 0.025;
const double ki = 2.24;
const double kw = 0.57;
const double Cm = 2.000;
const double Cw = 4.185;
const double Ca = 0.001;
const double Co = 0.110;
const double Ci = 1.950;

void Classfrostdepth :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classfrostdepth::init(void)@@@Classfrostdepth.cpp>");
    nlay = getdim (TDim :: NLAY);
    nhru = getdim (TDim :: NHRU);
    k_lay = new double * [nlay];
    L_lay = new double * [nlay];
    c_lay = new double * [nlay];
    for (int nn = 0; nn < nlay; ++ nn) {
        k_lay [nn] = new double [nhru];
        L_lay [nn] = new double [nhru];
        c_lay [nn] = new double [nhru];
    }
    for (hh = 0; hh < nhru; ++ hh) {
        Tfreeze [hh] = 0;
        Findex [hh] = 0.0;
        frostdepth [hh] = 0.0;
        Lacc [hh] = 0.0;
        Cacc [hh] = 0.0;
        Kacc [hh] = 0.0;
        for (long nn = 0; nn < nlay; ++ nn) {
            L_lay [nn] [hh] = theta_lay [nn] [hh] * por_lay [nn] [hh];
            if (soil_type_lay [nn] [hh] != 4)
            {
                k_lay [nn] [hh] = (1.0 - por_lay [nn] [hh]) * km + L_lay [nn] [hh] * kw + (por_lay [nn] [hh] - L_lay [nn] [hh]) * ka;
                c_lay [nn] [hh] = (1.0 - por_lay [nn] [hh]) * Cm + L_lay [nn] [hh] * Cw + (por_lay [nn] [hh] - L_lay [nn] [hh]) * Ca;
            }

            else
            {
                k_lay [nn] [hh] = (1.0 - por_lay [nn] [hh]) * ko + L_lay [nn] [hh] * kw + (por_lay [nn] [hh] - L_lay [nn] [hh]) * ka;
                c_lay [nn] [hh] = (1.0 - por_lay [nn] [hh]) * Co + L_lay [nn] [hh] * Cw + (por_lay [nn] [hh] - L_lay [nn] [hh]) * Ca;
            }

            L_lay [nn] [hh] *= 333.0;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::init(void)@@@Classfrostdepth.cpp>");
}
void Classfrostdepth :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classfrostdepth::run(void)@@@Classfrostdepth.cpp>");
    const double csnow = 0.25 * Ci;
    const double ksnow = 0.25 * ki + 0.75 * ka;
    double FrozenD;
    long FrozenL;
    double dsum;
    double dsoil;
    long nstep = getstep () % Global :: Freq;
    if (nstep != 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::run(void)@@@Classfrostdepth.cpp>");
        return;
    }

    long jday = julian ("now");
    double hemisphere = (hru_lat [0] < 0.0);
    if ((! hemisphere && (jday < 300) || hemisphere && (jday < 117)) && Tfreeze [0] == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::run(void)@@@Classfrostdepth.cpp>");
        return;
    }

    for (hh = 0; chkStruct (); ++ hh) {
        if (hru_tmean [hh] > 0.0)
        {
            if (hru_tmean [hh] > 20.0)
            {
                frostdepth [hh] = 0.0;
                Tfreeze [0] = 0;
            }

            continue;
        }

        else
        {
            double Lastsnowdepth = snowdepth [hh];
            if (snowdepth [hh] > Lastsnowdepth && Lastsnowdepth > 0.05)
            {
                Findex [hh] = (Lacc [hh] + Cacc [hh] * Ta [hh] * 1.8) / (24.0 * 3600 * 1E-6 * Kacc [hh] / sqr (frostdepth [hh] + snowdepth [hh]) - Cacc [hh] / (2.0 * Tfreeze [hh]));
            }

            Tfreeze [hh] ++;
            Findex [hh] += - hru_tmean [hh];
        }

        dsum = snowdepth [hh] + 0.001;
        Lacc [hh] = 0.0;
        Cacc [hh] = dsum * csnow;
        Kacc [hh] = dsum / ksnow;
        dsoil = 0.0;
        FrozenL = 0;
        while (nlay - 1 > FrozenL) {
            if (frostdepth [hh] < dsoil + d_lay [FrozenL] [hh])
            {
                break;
            }

            dsoil += d_lay [FrozenL] [hh];
            dsum += d_lay [FrozenL] [hh];
            Lacc [hh] += L_lay [FrozenL] [hh] * d_lay [FrozenL] [hh];
            Cacc [hh] += c_lay [FrozenL] [hh] * d_lay [FrozenL] [hh];
            Kacc [hh] += d_lay [FrozenL] [hh] / k_lay [FrozenL] [hh];
            FrozenL ++;
        }
        FrozenD = frostdepth [hh] - dsoil;
        dsum += FrozenD;
        Lacc [hh] += L_lay [FrozenL] [hh] * FrozenD;
        Cacc [hh] += c_lay [FrozenL] [hh] * FrozenD;
        Kacc [hh] += FrozenD / k_lay [FrozenL] [hh];
        Lacc [hh] = Lacc [hh] / dsum;
        Cacc [hh] = Cacc [hh] / dsum;
        Kacc [hh] = dsum / Kacc [hh];
        frostdepth [hh] = sqrt ((24.0 * 3600 * 1e-6 * Kacc [hh] * Findex [hh]) / (Lacc [hh] + Cacc [hh] * (Ta [hh] * 1.8 + Findex [hh] / (2.0 * Tfreeze [hh])))) - snowdepth [hh];
        if (frostdepth [hh] < 0.0)
        {
            frostdepth [hh] = 0.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::run(void)@@@Classfrostdepth.cpp>");
}
void Classfrostdepth :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classfrostdepth::finish(bool good)@@@Classfrostdepth.cpp>");
    if (k_lay != NULL)
    {
        for (int nn = 0; nn < nlay; ++ nn) {
            delete [] k_lay [nn];
            delete [] L_lay [nn];
            delete [] c_lay [nn];
        }
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::finish(bool good)@@@Classfrostdepth.cpp>");
        return;
    }

    delete [] k_lay;
    k_lay = NULL;
    delete [] L_lay;
    L_lay = NULL;
    delete [] c_lay;
    c_lay = NULL;
InstrumentLogger::instance()->log_instrument_log("</Classfrostdepth::finish(bool good)@@@Classfrostdepth.cpp>");
}