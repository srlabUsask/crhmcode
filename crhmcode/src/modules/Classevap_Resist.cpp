/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "Classevap_Resist.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

string Evap_Resist_names[] = {"Penman-Monteith", "Dalton Bulk transfer", "Priestley_Taylor"};

Classevap_Resist* Classevap_Resist::klone(string name) const {
    return new Classevap_Resist(name);
}

void Classevap_Resist::decl(void) {

    Description = "'Evaluation evaporation model using Penman-Monteith, Dalton Bulk transfer and Priestley-Taylor.' \
                 'Uses observation Qsi (W/m^2), ' \
                 'Uses variable QsiS_Var (W/m^2)(slope) from Annandale, '\
                 'Uses variable QsiA_Var (W/m^2)(horizontal) from Annandale, '";

    declvar("hru_actet", TDim::NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

    declstatdiag("hru_cum_actet", TDim::NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

    declvar("hru_evap", TDim::NHRU, "interval evaporation", "(mm/int)", &evap);

    declvar("hru_evapD", TDim::NHRU, "daily sum of interval evaporation", "(mm/d)", &evapD);

    declstatdiag("hru_cum_evap", TDim::NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

    decldiag("rc", TDim::NHRU, "stomatal resistance (Penman-Monteith)", "(s/m)", &rc);

    decllocal("Pa", TDim::NHRU, "Atmospheric pressure", "(kPa)", &Pa);


    declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

    decldiagparam("Zwind", TDim::NHRU, "[10.0]", "0.0", "100.0", "Wind instrument height", "(m)", &Zwind);

    declparam("evap_type", TDim::NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Penman-Monteith, 1 = Dalton bulk transfer, 2 = Priestley-Taylor",
        "()", &evap_type);

    declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

    declparam("basin_area", TDim::BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

    decldiagparam("F_Qg", TDim::NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

    declparam("rcs", TDim::NHRU, "[25]", "25.0", "5000.0", "minimum stomatal resistance", "(s/m)", &rcs);

    declparam("Htmax", TDim::NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (Penman-Monteith)", "(m)", &Htmax);

    declparam("LAImax", TDim::NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImax);

    declparam("LAImin", TDim::NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImin);

    declparam("s", TDim::NHRU, "[1]", "0", "1", "seasonal growth index (Penman-Monteith)", "()", &s);

    declparam("PMmethod", TDim::NHRU, "[0]", "0", "1", "Penman-Monteith method, 0 = RC min, 1 = LAI", "()", &PM_method);

    declparam("soil_type", TDim::NHRU, "[2]", "1", "12",
        "HRU soil type (1->11): sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay",
        "()", &soil_type);

    declparam("soil_Depth", TDim::NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

    declgetvar("*", "Rn", "(mm/m^2*int)", &Rn);
    declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
    declgetvar("*", "RnD_POS", "(mm/m^2*d)", &RnD_POS);

    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
    declgetvar("*", "hru_u", "(m/s)", &hru_u);
    declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

    declgetvar("*", "hru_tmean", "(" + string(DEGREE_CELSIUS) + ")", &hru_tmean);
    declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
    declgetvar("*", "hru_eamean", "(kPa)", &hru_eamean);

    declgetvar("*", "soil_moist", "(mm)", &soil_moist);

    declreadobs("Ts", TDim::NHRU, "surface temperature", "(" + string(DEGREE_CELSIUS) + ")", &Ts, HRU_OBS_misc, true);

    declreadobs("RnObs", TDim::NHRU, "all-wave", "(W/m^2)", &RnObs, HRU_OBS_Q, true);

    variation_set = VARIATION_0;

    declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, false);

    variation_set = VARIATION_1;

    declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);


    variation_set = VARIATION_2;

    declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


    variation_set = VARIATION_ORG;
}

void Classevap_Resist::init(void) {

    for (hh = 0; chkStruct(); ++hh) {

        if (evap_type[hh] == 1 && Ts == NULL) {
            CRHMException TExcept("'evap_Resist' Ts observation not available for Dalton bulk transfer!", TExcept::TERMINATE);
            LogError(TExcept);
        }

        Pa[hh] = 101.3f * pow((293.0f - 0.0065f * hru_elev[hh]) / 293.0f, 5.26f);  // kPa
        cum_evap[hh] = 0.0;
        evapD[hh] = 0.0;
        hru_cum_actet[hh] = 0.0;

        if (Ht[hh] > Zwind[hh] / 0.67 && evap_type[hh] != 0) {
            CRHMException TExcept("Vegetation height greater than wind reference height, i.e. (Ht > Zwind/0.67)!", TExcept::WARNING);
            LogError(TExcept);
        }
    }
    BeforeCorrectionRCS = rcs[0] < 0;

}

void Classevap_Resist::run(void) {

    double Q, rcstar, LAI, Z0, d, U, f1, f2, f3, f4, ra, ratio_rs_ra, p;

    const double Cp = 1.005; // (kJ/kg/K)

    if (getstep() == 1 && rcs[0] < 0)
        const_cast<double*> (rcs)[0] = -rcs[0];

    long nstep = getstep() % Global::Freq;

    for (hh = 0; chkStruct(); ++hh) {

        if (nstep == 1 || Global::Freq == 1) // beginning of day
            evapD[hh] = 0.0;

        evap[hh] = 0.0;
        hru_actet[hh] = 0.0;

        if (inhibit_evap[hh])
            continue;

        switch (variation) {
        case VARIATION_ORG:
            Qsi_ = Qsi[hh];
            break;
        case VARIATION_1:
            Qsi_ = QsiS_Var[hh];
            break;
        case VARIATION_2:
            Qsi_ = QsiA_Var[hh];
            break;
        } // switch

    // calculated every interval

        Q = Rn[hh] * (1.0 - F_Qg[hh]); // (mm/int) 28May2024: change the incorrect comment mm/d for units

        double Soil_Moist = (soil_moist[hh] / soil_Depth[hh] + SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][3];

        switch (evap_type[hh]) {

        case 0: // Penman-Monteith

            if (soil_moist[hh] > 0.0) { // else ignore

                Z0 = Ht[hh] / 7.6;
                d = Ht[hh] * 0.67;
                U = hru_u[hh];
                ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa) * U);

                rcstar = rcs[hh]; // rc min

                if (PM_method[hh] == 1) { // LAI
                    LAI = Ht[hh] / Htmax[hh] * (LAImin[hh] + s[hh] * (LAImax[hh] - LAImin[hh]));
                    rcstar = rcs[hh] * LAImax[hh] / LAI;
                }

                f1 = 1.0;
                if (Qsi_ > 0.0)
                    f1 = max <double>(1.0, 500.0 / (Qsi_)-1.5);

                f2 = max <double>(1.0, 2.0 * (estar(hru_t[hh]) - hru_ea[hh])); // 06/09/20: retoring f2 to correct formula in CRHM_041420, as pressur in f2 needs be coverted from kPa to mb

                p = soilproperties[soil_type[hh]][AIRENT] *
                    pow(1.0 / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]); // 05/21/20 correcting pow(soilproperties[soil_type[hh]][PORE]/Soil_Moist, soilproperties[soil_type[hh]][PORESZ]);

                f3 = max <double>(1.0, p / 40.0);

                f4 = 1.0;
                if (hru_t[hh] < 0.0 || hru_t[hh] > 40.0)
                    f4 = 5000 / rcs[hh]; // 05/21/20 correcting f4 = 5000/50;

                if (RnObs != NULL && RnObs[hh] <= 0)
                    rc[hh] = 5000.0;
                else if (Qsi_ <= 0)
                    rc[hh] = 5000.0;
                else {
                    rc[hh] = rcstar * f1 * f2 * f3 * f4;
                    if (rc[hh] > 5000.0 && !BeforeCorrectionRCS)
                        rc[hh] = 5000.0;
                }

                ratio_rs_ra = rc[hh] / ra;

                evap[hh] = (delta(hru_t[hh]) * Q * Global::Freq + (RHOa(hru_t[hh], hru_ea[hh], Pa[hh])
                    * Cp / (lambda(hru_t[hh]) * 1e3) * (Common::estar(hru_t[hh]) - hru_ea[hh]) / (ra / 86400)))
                    / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]) * (1.0 + ratio_rs_ra)) / Global::Freq;
            }

            break;

        case 1: // Dalton Bulk transfer

            if (soil_moist[hh] > 0.0) { // else ignore

                Z0 = Ht[hh] / 7.6;
                d = Ht[hh] * 0.67;
                U = hru_u[hh];
                ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa) * U);

                rcstar = rcs[hh]; // rc min

                f1 = 1.0;
                if (Qsi_ > 0.0)
                    f1 = max <double>(1.0, 500.0 / (Qsi_)-1.5);

                f2 = max <double>(1.0, 2.0 * (estar(hru_t[hh]) - hru_ea[hh])); // 06/09/20: retoring f2 to correct formula in CRHM_041420, as pressur in f2 needs be coverted from kPa to mb

                p = soilproperties[soil_type[hh]][AIRENT] *
                    pow(1.0 / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]); // 05/21/20 correcting pow(soilproperties[soil_type[hh]][PORE]/Sil_Moist, soilproperties[soil_type[hh]][PORESZ]);

                f3 = max <double>(1.0, p / 40.0);

                f4 = 1.0;
                if (hru_t[hh] < 5.0 || hru_t[hh] > 40.0)
                    f4 = 5000 / rcs[hh]; // 05/21/20 correcting f4 = 5000/50;

                if (RnObs != NULL && RnObs[hh] <= 0)
                    rc[hh] = 5000.0;
                else if (Qsi_ <= 0)
                    rc[hh] = 5000.0;
                else {
                    rc[hh] = rcstar * f1 * f2 * f3 * f4;
                    if (rc[hh] > 5000.0 && !BeforeCorrectionRCS)
                        rc[hh] = 5000.0;
                }

                double qs = 0.622 * Common::estar(Ts[hh]) / (Pa[hh] - Common::estar(Ts[hh]) * 0.378); // Specific humidity (kg/kg)
                double q = 0.622 * hru_ea[hh] / (Pa[hh] - hru_ea[hh] * 0.378);

                evap[hh] = RHOa(hru_t[hh], hru_ea[hh], Pa[hh]) * (qs - q) / ((ra + rc[hh]) / 86400) / Global::Freq;
            }
            break;

        case 2: // Priestley-Taylor
            if (Q > 0.0)
                evap[hh] = 1.26 * delta(hru_t[hh]) * Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])); // restored amount to ground flux 11/21/16
            else
                evap[hh] = 0.0;
            break;

        } // switch

        if (evap[hh] < 0.0)
            evap[hh] = 0.0;

        cum_evap[hh] += evap[hh];
        evapD[hh] += evap[hh];
    } // for
}

void Classevap_Resist::finish(bool good) {

    for (hh = 0; chkStruct(); ++hh) {

        string s = "'" + Name + " (evap_Resist)' " + Evap_Resist_names[evap_type[hh]] + " hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ";
        LogMessageA(hh, s.c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (evap_Resist)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }
}

double Classevap_Resist::gamma(double Pa, double t) // Psychrometric constant (kPa/DEGREE_CELCIUS)
{
    return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg DEGREE_CELCIUS))
}

double Classevap_Resist::lambda(double t) // Latent heat of vaporization (mJ/(kg DEGREE_CELCIUS))
{
    return(2.501 - 0.002361 * t);
}

double Classevap_Resist::delta(double t) // Slope of sat vap p vs t, kPa/DEGREE_CELCIUS
{
    if (t > 0.0)
        return(2504.0 * exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
    else
        return(3549.0 * exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

double Classevap_Resist::RHOa(double t, double ea, double Pa) // atmospheric density (kg/m^3)
{
    const double R0 = 2870;
    return (1E4 * Pa / (R0 * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa))); //
}
