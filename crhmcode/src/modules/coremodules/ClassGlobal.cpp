#include "ClassGlobal.h"
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
Classglobal * Classglobal :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classglobal::klone(string name) const@@@ClassGlobal.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classglobal::klone(string name) const@@@ClassGlobal.cpp>");
    return new Classglobal (name);
InstrumentLogger::instance()->log_instrument_log("</Classglobal::klone(string name) const@@@ClassGlobal.cpp>");
}
void Classglobal :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classglobal::decl(void)@@@ClassGlobal.cpp>");
    Description = "'Calculate theoretical short_wave radiation using method proposed by Garnier and Ohmura (1970).'";
    declvar ("QdroD", TDim :: NHRU, "daily clear-sky direct", "(MJ/m^2*d)", & QdroD);
    declvar ("QdroDext", TDim :: NHRU, "daily ExtraTerrestrial direct", "(MJ/m^2*d)", & QdroDext);
    declvar ("QdfoD", TDim :: NHRU, "daily average clear-sky diffuse", "(MJ/m^2*d)", & QdfoD);
    declvar ("Qdro", TDim :: NHRU, "clear-sky direct", "(W/m^2)", & Qdro);
    declvar ("Qdfo", TDim :: NHRU, "clear-sky diffuse", "(W/m^2)", & Qdfo);
    declvar ("Qdflat", TDim :: NHRU, "clear-sky 'Qdro + Qdfo' on horizontal surface", "(W/m^2)", & Qdflat);
    declvar ("QdflatE", TDim :: NHRU, "'Qdro' on horizontal surface, no atmosheric attenuation", "(W/m^2)", & QdflatE);
    declvar ("QdflatD", TDim :: NHRU, "daily clear-sky Qdro (with diffuse) on horizontal surface", "(MJ/m^2*d)", & QdflatD);
    declvar ("SolAng", TDim :: NHRU, "Solar Angle", "(r)", & SolAng);
    declvar ("SunMax", TDim :: NHRU, "maximum sunshine hours", "(h)", & SunMax);
    declvar ("cosxs", TDim :: NHRU, "cosine of the angle of incidence on the slope", "()", & cosxs);
    declvar ("cosxsflat", TDim :: NHRU, "cosine of the angle of incidence on the horizontal", "()", & cosxsflat);
    declvar ("pQdro", TDim :: NFREQ, "clear-sky direct", "(MJ/m^2*int)", & pQdro, & pQdro_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pQdfo", TDim :: NFREQ, "clear-sky diffuse", "(MJ/m^2*int)", & pQdfo, & pQdfo_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pQdflat", TDim :: NFREQ, "Qdro + Qdfo on horizontal surface", "(MJ/m^2*int)", & pQdflat, & pQdflat_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pQdflatE", TDim :: NFREQ, "Qdro on horizontal surface with no atmospheric attenuation", "(MJ/m^2*int)", & pQdflatE, & pQdflatE_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pSol", TDim :: NFREQ, "Solar Angle", "(r)", & pSol, & pSol_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pCosxs", TDim :: NFREQ, "Cos(x^s)", "(r)", & pCosxs, & pCosxs_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declvar ("pCosxs0", TDim :: NFREQ, "Cos(x^s) on the horizontal", "(r)", & pCosxs0, & pCosxs0_FREQ, 0, true, false, TVISIBLE :: PRIVATE);
    declparam ("hru_lat", TDim :: NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string (DEGREE) + ")", & hru_lat);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("hru_GSL", TDim :: NHRU, "0.0", "-90.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string (DEGREE) + ")", & hru_GSL);
    declparam ("hru_ASL", TDim :: NHRU, "0.0", "-360.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(" + string (DEGREE) + ")", & hru_ASL);
    declparam ("Time_Offset", TDim :: NHRU, "0.0", "-12.0", "12.0", "solar time offset from local time", "(h)", & Time_Offset);
InstrumentLogger::instance()->log_instrument_log("</Classglobal::decl(void)@@@ClassGlobal.cpp>");
}
void Classglobal :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classglobal::init(void)@@@ClassGlobal.cpp>");
    nhru = getdim (TDim :: NHRU);
    int Integer = CalcFreq / Global :: Freq;
    int Remainder = CalcFreq % Global :: Freq;
    if (Remainder != 0 || Integer < 1)
    {
        CRHMException TExcept ("\"288/(first observation frequency)\" must be an integer > one!", TExcept :: TERMINATE);
        LogError (TExcept);
    }

InstrumentLogger::instance()->log_instrument_log("</Classglobal::init(void)@@@ClassGlobal.cpp>");
}
void Classglobal :: air_mass (const double czen, double & oam)
{
InstrumentLogger::instance()->log_instrument_log("<Classglobal::air_mass(const double czen, double & oam)@@@ClassGlobal.cpp>");
    double diff;
    double Z = acos (czen);
    oam = fabs (1.0f / (czen + 0.50572f * pow (96.07995f - Z, - 1.6364f)));
    if (oam < 2.9)
    {

InstrumentLogger::instance()->log_instrument_log("</Classglobal::air_mass(const double czen, double & oam)@@@ClassGlobal.cpp>");
        return;
    }

    else
    if (oam < 16.38)
    {
        diff = pow (10.0f, 2.247f * log10 (oam) - 2.104f);
        oam = oam - diff;

InstrumentLogger::instance()->log_instrument_log("</Classglobal::air_mass(const double czen, double & oam)@@@ClassGlobal.cpp>");
        return;
    }

    else
    if (oam <= 114.6)
    {
        diff = pow (10.0f, 1.576f * log10 (oam) - 1.279f);
        oam = oam - diff;

InstrumentLogger::instance()->log_instrument_log("</Classglobal::air_mass(const double czen, double & oam)@@@ClassGlobal.cpp>");
        return;
    }

    oam = 30.0;
InstrumentLogger::instance()->log_instrument_log("</Classglobal::air_mass(const double czen, double & oam)@@@ClassGlobal.cpp>");
}
void Classglobal :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classglobal::run(void)@@@ClassGlobal.cpp>");
    long Period, Day;
    double Trans, Dec, Rad_vec, Sol, Clat, Slat, Cdec, Sdec, Hr_Ang;
    double Czen, t1, t2, x, y, z, Oam;
    double cosxsL, cosxs0, t10, t20;
    double It, Id, diffuse, Sum_Id, Sum_Diff, Sum_Sol, Sum_cosxs, Sum_cosxs0, Sum_Ext, Sum_Flatd, Sum_Flatf;
    Period = (getstep () - 1) % Global :: Freq;
    if (Period == 0 || getstep () == 1)
    {
        for (hh = 0; hh < nhru; ++ hh) {
            Day = julian ("now");
            if (Global :: Freq <= 1)
            {
                -- Day;
            }

            Trans = 0.818;
            Dec = sin (((long long) Day - 81ll) * DEGtoRAD365) * 0.40928;
            Rad_vec = .01676 * cos (M_PI - 0.017262 * ((long long) Day - 3ll)) + 1.0;
            Sol = 0.0819 / (Rad_vec * Rad_vec);
            Clat = cos (hru_lat [hh] * DEGtoRAD);
            Slat = sin (hru_lat [hh] * DEGtoRAD);
            Cdec = cos (Dec);
            Sdec = sin (Dec);
            SunMax [hh] = 0.0;
            QdroD [hh] = 0.0;
            QdroDext [hh] = 0.0;
            QdfoD [hh] = 0.0;
            QdflatD [hh] = 0.0;
            Sum_Id = 0.0;
            Sum_Diff = 0.0;
            Sum_Sol = 0.0;
            Sum_cosxs = 0.0;
            Sum_cosxs0 = 0.0;
            Sum_Ext = 0.0;
            Sum_Flatd = 0.0;
            Sum_Flatf = 0.0;
            x = - cos (hru_ASL [hh] * DEGtoRAD) * sin (hru_GSL [hh] * DEGtoRAD);
            y = sin (hru_ASL [hh] * DEGtoRAD) * sin (hru_GSL [hh] * DEGtoRAD);
            z = cos (hru_GSL [hh] * DEGtoRAD);
            t1 = (x * Slat + z * Clat) * Cdec;
            t2 = (- x * Clat + z * Slat) * Sdec;
            t10 = Clat * Cdec;
            t20 = Slat * Sdec;
            Hr_Ang = - M_PI * (1.0 + Time_Offset [hh] / 12.0);
            for (long jj = 0; jj < CalcFreq; ++ jj, Hr_Ang += RADxxMIN) {
                Czen = Cdec * Clat * cos (Hr_Ang) + Sdec * Slat;
                diffuse = 0.0;
                if (Czen > 0.0)
                {
                    Sum_Sol = Sum_Sol + M_PI / 2.0f - acos (Czen);
                    SunMax [hh] = SunMax [hh] + MINS_int;
                    It = MINS_int * Sol * Czen;
                    cosxs0 = t10 * cos (Hr_Ang);
                    cosxs0 = cosxs0 + t20;
                    if (cosxs0 > 0.0)
                    {
                        Sum_cosxs0 += cosxs0;
                        air_mass (Czen, Oam);
                        Oam = Oam * pow ((288.0f - 0.0065f * hru_elev [hh]) / 288.0f, 5.256f);
                        Id = MINS_int * Sol * cosxs0;
                        Sum_Ext += Id;
                        Id = Id * pow (Trans, Oam);
                        diffuse = 0.5f * (0.91f * It - Id);
                        Sum_Flatf += diffuse;
                        Sum_Flatd += Id;
                    }

                    cosxsL = - y * sin (Hr_Ang) * Cdec + t1 * cos (Hr_Ang);
                    cosxsL = cosxsL + t2;
                    if (cosxsL > 0.0)
                    {
                        Sum_cosxs += cosxsL;
                        air_mass (Czen, Oam);
                        Oam = Oam * pow ((288.0f - 0.0065f * hru_elev [hh]) / 288.0f, 5.256f);
                        Id = MINS_int * Sol * cosxsL;
                        Id = Id * pow (Trans, Oam);
                        Sum_Id += Id;
                    }

                    diffuse = diffuse * sqr (cos (hru_GSL [hh] / 2.0 * DEGtoRAD));
                    Sum_Diff += diffuse;
                }

                if (! ((jj + 1) % (CalcFreq / Global :: Freq)))
                {
                    int kk = jj / (CalcFreq / Global :: Freq);
                    pQdro_FREQ [kk] [hh] = Sum_Id;
                    pQdfo_FREQ [kk] [hh] = Sum_Diff;
                    pQdflat_FREQ [kk] [hh] = (Sum_Flatd + Sum_Flatf);
                    pQdflatE_FREQ [kk] [hh] = Sum_Ext;
                    pSol_FREQ [kk] [hh] = Sum_Sol / (CalcFreq / Global :: Freq);
                    pCosxs_FREQ [kk] [hh] = Sum_cosxs / (CalcFreq / Global :: Freq);
                    pCosxs0_FREQ [kk] [hh] = Sum_cosxs0 / (CalcFreq / Global :: Freq);
                    QdroD [hh] += Sum_Id;
                    QdroDext [hh] += Sum_Ext;
                    QdfoD [hh] += Sum_Diff;
                    QdflatD [hh] += Sum_Flatd + Sum_Flatf;
                    Sum_Id = 0.0;
                    Sum_Diff = 0.0;
                    Sum_Sol = 0.0;
                    Sum_cosxs = 0.0;
                    Sum_cosxs0 = 0.0;
                    Sum_Ext = 0.0;
                    Sum_Flatd = 0.0;
                    Sum_Flatf = 0.0;
                }

            }
            SunMax [hh] = SunMax [hh] / 60.0;
            Hr_Ang = 0.0;
        }
    }

    for (hh = 0; hh < nhru; ++ hh) {
        Qdro [hh] = pQdro_FREQ [Period] [hh] * 1E6 / 86400 * Global :: Freq;
        Qdfo [hh] = pQdfo_FREQ [Period] [hh] * 1E6 / 86400 * Global :: Freq;
        Qdflat [hh] = pQdflat_FREQ [Period] [hh] * 1E6 / 86400 * Global :: Freq;
        QdflatE [hh] = pQdflatE_FREQ [Period] [hh] * 1E6 / 86400 * Global :: Freq;
        SolAng [hh] = pSol_FREQ [Period] [hh];
        cosxs [hh] = pCosxs_FREQ [Period] [hh];
        cosxsflat [hh] = pCosxs0_FREQ [Period] [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classglobal::run(void)@@@ClassGlobal.cpp>");
}