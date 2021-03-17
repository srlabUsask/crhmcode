//created by Manishankar Mondal

#include "Classsbsm.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;


Classsbsm* Classsbsm::klone(string name) const {
    return new Classsbsm(name);
}

void Classsbsm::decl(void) {

    Description = "'Simplified blowing snow model (Richard Essery,  Long Li and John Pomeroy, 1999).'";

    declstatvar("SWE", TDim::NHRU, "snow water equivalent", "(mm)", &SWE);

    declvar("wet_snow", TDim::NHRU, "wet snow (T was above zero)", "(mm)", &wet_snow);

    declvar("Subl", TDim::NHRU, "interval sublimation", "(mm /int)", &Subl);

    declvar("Drift", TDim::NHRU, "interval transport", "(mm /int)", &Drift);

    declvar("BasinSnowLoss", TDim::BASIN, "transport out of basin", "(mm /int)", &BasinSnowLoss);

    declstatdiag("cumSubl", TDim::NHRU, "cumulative sublimation", "(mm)", &cumSubl);

    declstatdiag("cumDrift", TDim::NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

    declstatdiag("cumDriftIn", TDim::NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

    declstatdiag("cumBasinSnowLoss", TDim::BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

    decllocal("cumBasinSnowGain", TDim::BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

    decllocal("cumSno", TDim::NHRU, "cumulative snow", "(mm)", &cumSno);

    decllocal("Prob", TDim::NHRU, "Probability", "()", &Prob);

    decllocal("snow_age", TDim::NHRU, "snow age", "(h)", &snow_age);

    declvar("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);



    /* parameters */

    declparam("fetch", TDim::NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

    declparam("basin_area", TDim::BASIN, "3.0", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

    declparam("zr", TDim::NHRU, "[ 0.1,   0.1,   0.05,  0.05,  0.05,  0.05,  0.08 ]", "0.001", "100.0", "Ratio of aerodynamic roughness length to vegetation height", "()", &zr);

    declparam("distrib", TDim::NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - do not have to sum to 1", "()", &distrib);

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);
    
    decldiagparam("SWEmin_inhibit_evap", TDim::NHRU, "[0.0]", "0.0", "10.0", "SWE threshold to inhibit evaporation, SWE > SWEmin_inhibit_evap: inhibit_evap = 1 -> inhibit evap", "()", &SWEmin_inhibit_evap); // modification on 24Feb2021

    decldiagparam("inhibit_subl", TDim::NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
    declgetvar("*", "hru_rh", "(%)", &hru_rh);
    declgetvar("*", "hru_u", "(m/s)", &hru_u);
    declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
    declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void Classsbsm::init(void) {

    nhru = getdim(TDim::NHRU);

    hru_basin = new double[nhru];

    dt = 3600 * 24 / Global::Freq;

    cumBasinSnowLoss[0] = 0.0;
    cumBasinSnowGain[0] = 0.0;

    for (hh = 0; hh < nhru; ++hh) {
        SWE[hh] = 0.0;
        wet_snow[hh] = 0.0;
        cumSno[hh] = 0.0;
        Drift[hh] = 0.0;
        cumDrift[hh] = 0.0;
        cumDriftIn[hh] = 0.0;
        Subl[hh] = 0.0;
        cumSubl[hh] = 0.0;
        Prob[hh] = 0.0;
        snow_age[hh] = 0.0;
        hru_basin[hh] = hru_area[hh] / basin_area[0];
        snowdepth[hh] = 0.0;
    }
}

void Classsbsm::run(void) {

    double SumDrift, total, SWE_Max, trans;

    for (hh = 0; chkStruct(); ++hh) {

        if (net_snow[hh] > 0.0) {
            SWE[hh] = SWE[hh] + net_snow[hh];
            cumSno[hh] = cumSno[hh] + net_snow[hh];
            snow_age[hh] = 1.0;
        }
        else
            snow_age[hh] += dt / 3600;


        if (hru_t[hh] >= 0.0)
            wet_snow[hh] = SWE[hh];
        else
            wet_snow[hh] = min<double>(SWE[hh], wet_snow[hh]);

        Drift[hh] = 0.0;
        Subl[hh] = 0.0;

        if (hru_u[hh] > 3.0 && SWE[hh] > 0.0) {

            prob();

            if (Prob[hh] > 0.0) {
                double RH = hru_rh[hh];
                if (RH > 1.01)
                    RH /= 100.0;
                Drift[hh] = Prob[hh] * transport() * dt / fetch[hh];
                if (!inhibit_subl[hh])
                    Subl[hh] = Prob[hh] * ((1.0 - RH) / scale()) * sublimation() * dt;

                // handle insufficient snow pack

                if (Drift[hh] + Subl[hh] > SWE[hh]) {
                    Subl[hh] = SWE[hh] * Subl[hh] / (Subl[hh] + Drift[hh]);
                    Drift[hh] = SWE[hh] - Subl[hh];
                } // end if

                cumDrift[hh] += Drift[hh];
                cumSubl[hh] += Subl[hh];

                SWE[hh] = SWE[hh] - Subl[hh] - Drift[hh];
            }
        }
    } // for

   // distribute drift


    if (distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
        double Drft = Drift[0] * distrib[0];
        SWE[0] += Drft;
        cumDriftIn[0] += Drft;
        cumBasinSnowGain[0] += Drft * hru_basin[0];
    }

    BasinSnowLoss[0] = 0.0;
    long LastN = 0;

    for (long nn = 0; chkStruct(nn); ++nn) {
        if (distrib[nn] >= 0.0 && nn + 1 < nhru)
            continue;

        SumDrift = 0.0;
        for (long hh = LastN; chkStruct(hh, nn + 1); ++hh)
            if (distrib[nn] != 0.0)
                SumDrift += Drift[hh] * hru_basin[hh];

        if (SumDrift > 0.0) {
            for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {
                SWE_Max = SWEfromDepth(Ht[hh]);

                if (hh == nn) {
                    SWE[hh] += SumDrift / hru_basin[hh];
                    cumDriftIn[hh] += SumDrift / hru_basin[hh];
                    if (SWE[hh] > SWE_Max) {
                        if (SWE[hh] - SWE_Max >= Drift[hh]) {
                            SWE[hh] -= Drift[hh];
                            BasinSnowLoss[0] = Drift[hh];
                        }
                        else {
                            SWE[hh] = SWE_Max;
                            BasinSnowLoss[0] = SWE[hh] - SWE_Max;
                        }
                        BasinSnowLoss[0] *= hru_basin[hh];
                        cumBasinSnowLoss[0] += BasinSnowLoss[0];
                    }

                }
                else if (SWE_Max > SWE[hh] && distrib[hh] > 0.0) {

                    total = 0.0;
                    for (long jj = hh; chkStruct(jj, nn); jj++)
                        total = total + fabs(distrib[jj]);

                    trans = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];

                    if (SWE_Max > SWE[hh] + trans) {
                        SWE[hh] += trans;
                    }
                    else {
                        trans = SWE_Max - SWE[hh];
                        SWE[hh] = SWE_Max;
                    }
                    SumDrift -= trans * hru_basin[hh];
                    cumDriftIn[hh] += trans;
                }
            } // end for (hh)
        } // end if
        LastN = nn + 1;
    } // end for (nn)

    for (hh = 0; chkStruct(); ++hh) {
        if (SWE[hh] > SWEmin_inhibit_evap[hh]) { // modification on 24Feb2021: add SWEmin_inhibit_evap parameter
            const_cast<long*> (inhibit_evap)[hh] = 1;
            snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
        }
        else {
            const_cast<long*> (inhibit_evap)[hh] = 0;
            snowdepth[hh] = 0;
        }
    } // for
}

void Classsbsm::finish(bool good) {

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (sbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (sbsm)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (sbsm)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (sbsm)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (sbsm)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }

    LogMessage("'sbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
    LogMessage("'sbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);
    LogDebug(" ");

    delete[] hru_basin;
    hru_basin = NULL;
}

//=======================================================================
double Classsbsm::transport(void) {
    //=======================================================================
    return ((0.00096f * sqr(hru_t[hh]) + 0.5298f * hru_t[hh] + 666.82f) * pow(hru_u[hh] / 25.0f, 4.0f)) / 1000.0f;
}

//=======================================================================
double Classsbsm::sublimation(void) {
    //=======================================================================
    return  137.6f * pow(hru_u[hh] / 25.0f, 5.0f) / 1000.0f;
}

//=======================================================================
double Classsbsm::scale(void) {
    //=======================================================================
    double
        cond,       // Thermal conductivity of air (W/m/K)
        diff,       // Diffusivity of water vapour in air (m^2/s)
        rsat,       // Saturation density of water vapour (kg/m3)
        tk;         // Temperature (K)

    double const ls = 2.838e6; // Latent heat of sublimation (J/kg)
    double const m = 18.01;    // Molecular weight of water (kg/kmole)
    double const r = 8313.0;   // Universal gas constant (J/kmole/K)

    tk = hru_t[hh] + 273.0f;
    diff = 2.06e-5f * pow(tk / 273.0f, 1.75f);
    rsat = m * 611.15f * exp(22.45 * hru_t[hh] / tk) / (r * tk);
    cond = 0.000076843 * tk + 0.003130762;
    return ((ls * m / (r * tk)) - 1.0f) / (cond * (hru_t[hh] + 273.0f)) + 1.0f / (ls * diff * rsat);
}

//=======================================================================
void Classsbsm::prob(void) {
    //=======================================================================

    double
        mean        // Mean of cumulative normal distribution
        , var         // Standard deviation
        , rho         // Snow density (kg/m3)
        , sd          // Snow depth (m)
        , us;

    //  double const ht[] = { 0.01,  0.01,  0.08,  0.08,  1.0,   1.0,   3.   };// Vegetation height (m)
    //  double const zr[] = { 0.1,   0.1,   0.05,  0.05,  0.05,  0.05,  0.08 };// Ratio of aerodynamic roughness length to vegetation height
    //     1 - water      2 - soil      3 - open tundra
    //     4 - sparse shrub tundra      5 - shrub tundra
    //     6 - dense shrub tundra       7 - sparse forest

    bool dry_snow = hru_t[hh] < 0.0;

    mean = 0.365 * hru_t[hh] + 0.00706 * sqr(hru_t[hh]) + 0.91 * log(snow_age[hh]) + 11.0;
    var = 0.145 * hru_t[hh] + 0.00196 * sqr(hru_t[hh]) + 4.23;

    if (!dry_snow) {
        mean = 21.0;
        var = 7.0;
    }

    rho = 240.;
    if (SWE[hh] > 145.45)
        rho = 69.856 * log(SWE[hh]) - 74.732;
    sd = SWE[hh] / rho;
    us = hru_u[hh];
    if (sd < Ht[hh])
        us = us / sqrt(1. + PBSM_constants::Beta * 2 * zr[hh] * (Ht[hh] - sd));

    Prob[hh] = 1.0 / (1.0 + exp(1.7 * (mean - us) / var));

    if (SWE[hh] <= wet_snow[hh]) {
        Prob[hh] = 1 / (1. + exp(1.7 * (21.0 - us) / 7.0));
        if (us <= 7.0) Prob[hh] = 0.0;
    }

    if (sd <= 0.01) Prob[hh] = 0.0;

    if (dry_snow) {
        if (us <= 3.0)
            Prob[hh] = 0.0;
    }
    else {
        if (us <= 7.0)
            Prob[hh] = 0.0;
    }
}
