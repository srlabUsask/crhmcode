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

#include "ClassCRHMCanopyVectorBased.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassCRHMCanopyVectorBased* ClassCRHMCanopyVectorBased::klone(string name) const{
  return new ClassCRHMCanopyVectorBased(name);
}

void ClassCRHMCanopyVectorBased::decl(void) {

  Description = "'Prototype all season canopy/clearing module. Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2).'";

// Observations

  variation_set = VARIATION_0 + VARIATION_1;

  declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);


  variation_set = VARIATION_0 + VARIATION_2;

  declreadobs("Qli", TDim::NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


  variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

  declgetvar("*",  "QliVt_Var", "(W/m^2)", &QliVt_Var);


  variation_set = VARIATION_2 + VARIATION_3;

  declgetvar("*",  "QsiS_Var", "(W/m^2)", &QsiS_Var);

  variation_set = VARIATION_4;

  declgetvar("*",  "QsiA_Var", "(W/m^2)", &QsiA_Var);


  variation_set = VARIATION_ORG;

// get variables:

  declgetvar("*",  "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);

  declgetvar("*",  "hru_u", "(m/s)", &hru_u);

  declgetvar("*",  "hru_rh", "()", &hru_rh);

  declgetvar("*",  "hru_ea", "(kPa)", &hru_ea);

  declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

  declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

  declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

  declgetvar("*", "SolAng", "(r)", &SolAng);

  declgetvar("*", "cosxs", "(r)", &cosxs);

  declgetvar("*", "cosxsflat", "(r)", &cosxsflat);

  declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);

  declgetvar("*", "Albedo", "()", &Albedo);

  declputvar("*", "SWE", "(mm)", &SWE);

// declared observations

  declobs("Ts", TDim::NHRU, "snow surface temperature", "(" + string(DEGREE_CELSIUS) + ")", &Ts);

  declobs("Qnsn", TDim::NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn);

  declvar("Qnsn_Var", TDim::NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn_Var);

  declobs("Qsisn", TDim::NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn);

  declvar("Qsisn_Var", TDim::NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn_Var);

  declobs("Qlisn", TDim::NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn);

  declvar("Qlisn_Var", TDim::NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn_Var);

  declobs("Qlosn", TDim::NHRU, "reflected long-wave at surface", "(W/m^2)", &Qlosn);

// declared variables

  decldiag("k", TDim::NHRU, "extinction coefficient", "()", &k);

  decldiag("Tauc", TDim::NHRU, "short-wave transmissivity", "", &Tauc);

  decllocal("Pa", TDim::NHRU, "Average surface pressure", "(kPa)", &Pa);

  declvar("ra", TDim::NHRU, "resistance", "(s/m)", &ra);

  declvar("drip_cpy", TDim::NHRU, "canopy drip", "(mm/int)", &drip_Cpy);

  declvar("direct_rain", TDim::NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

  declvar("net_rain", TDim::NHRU, " direct_rain + drip", "(mm/int)", &net_rain);

  declstatdiag("cum_net_rain", TDim::NHRU, "cumulative direct_rain + drip", "(mm)", &cum_net_rain);

  declvar("pot_subl_cpy", TDim::NHRU, "sublimation rate coefficient for single ice spheres aka potential sublimation rate to be multiplied by canopy snow load and the exposure coeficient", "(s-1)", &pot_subl_cpy);

  declvar("Subl_Cpy", TDim::NHRU, "canopy snow sublimation", "(mm/int)", &Subl_Cpy);

  declstatdiag("cum_Subl_Cpy", TDim::NHRU, "cumulative canopy snow sublimation", "(mm)", &cum_Subl_Cpy);

  decldiag("Pevap", TDim::NHRU, "used when ground is snow covered to calculate canopy evaporation (Priestley-Taylor)", "(mm)", &Pevap);

  declstatvar("rain_load", TDim::NHRU, "canopy rain load", "(mm)", &rain_load);

  declstatvar("Snow_load", TDim::NHRU, "canopy snow load (timetep start)", "(mm)", &Snow_load);

  declvar("direct_snow", TDim::NHRU, "snow 'direct' through canopy", "(mm/int)", &direct_snow);

  declvar("SUnload", TDim::NHRU, "unloaded canopy snow", "(mm)", &SUnload);

  declvar("SUnload_H2O", TDim::NHRU, "unloaded canopy snow as water", "(mm)", &SUnload_H2O);

  declstatdiag("cum_SUnload_H2O", TDim::NHRU, "Cumulative unloaded canopy snow as water", "(mm)", &cum_SUnload_H2O);

  declstatdiag("cum_SUnload", TDim::NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", &cum_SUnload);

  declvar("net_snow", TDim::NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

  declstatdiag("cum_net_snow", TDim::NHRU, "Cumulative hru_snow minus interception", "(mm)", &cum_net_snow);

  declvar("net_p", TDim::NHRU, "total precipitation after interception", "(mm/int)", &net_p);

  decldiag("u_FHt", TDim::NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

  decldiag("u_1_third_Ht", TDim::NHRU, "wind speed at one-third forest height (z = 1/3*Ht) for the Cebulski & Pomeroy vector based param.", "(m/s)", &u_1_third_Ht);

  decldiag("Cc", TDim::NHRU, "Canopy coverage", "()", &Cc);

  declvar("Clca", TDim::NHRU, "Leaf contact area adjusted for hydrometeor trajectory angle.", "(s-1)", &Clca);

  declvar("intcp_evap", TDim::NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);

  declstatdiag("cum_intcp_evap", TDim::NHRU, "Cumulative HRU Evaporation from interception", "(mm)", &cum_intcp_evap);


// parameters:

  declparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("Surrounding_Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "surrounding canopy height", "()", &Surrounding_Ht);

  declparam("Gap_diameter", TDim::NHRU, "[100]", "10", "1000", "representative gap diameter", "(m)", &Gap_diameter);


  declparam("Ht", TDim::NHRU, "[20.0]", "0.001", "100.0", "forest/vegetation height", "(m)", &Ht);

  declparam("Zref", TDim::NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

  declparam("Zwind", TDim::NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

  declparam("Z0snow", TDim::NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

  declparam("LAI", TDim::NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

  declparam("Lmax", TDim::NHRU, "[50]", "0.0", "100.0", "maximum canopy snow interception load, currently just used for sublimation exposure coef. 50 based on max observed in Storck et al. 2002 and Cebulski & Pomeroy", "(kg/m^2)", &Lmax);

  declparam("alpha", TDim::NHRU, "[0.836]", "0.0", "1.0", "$alpha$ is an efficiency constant which determines the fraction of snowflakes that contact the $C_p$ elements and are stored in the canopy (i.e., intercepted) before canopy snow unloading or ablation processes begin. Default is based on Cebulski & Pomeroy plot scale observations at Fortress Mountain PWL and Forest Tower plots.", "()", &alpha);

  declparam("Zvent", TDim::NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

  declparam("unload_t", TDim::NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(" + string(DEGREE_CELSIUS) + ")", &unload_t);

  declparam("unload_t_water", TDim::NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(" + string(DEGREE_CELSIUS) + ")", &unload_t_water);

  declparam("CanopyClearing", TDim::NHRU, "[0]", "0", "2", "canopy - 0/clearing - 1/gap - 2", "()", &CanopyClearing);

  declparam("SublimationSwitch", TDim::NHRU, "[1]", "0", "1", "Pomeroy 1998 sublimation parameterisation, off - 0, on - 1", "()", &SublimationSwitch);
  
  declparam("MassUnloadingSwitch", TDim::NHRU, "[1]", "0", "1", "Canopy snow mass unloading parameterisation options: Hedstrom & Pomeroy 1998 constant time based unloading - 0, Cebulski & Pomeroy exponential curves for wind induced unloading, temperature based unloading, and time based unloading - 1", "()", &MassUnloadingSwitch);

  declparam("MeltwaterSwitch", TDim::NHRU, "[0]", "0", "1", "Canopy snow meltwater drip parameterisation options: Ellis et al. (2010) and Floyd (2012) - 0, CLASS - 1", "()", &MeltwaterSwitch);

  decldiagparam("Alpha_c", TDim::NHRU, "[0.1]", "0.05", "0.2", "canopy albedo, used for longwave-radiation enhancement estimation", "()", &Alpha_c);

  decldiagparam("B_canopy", TDim::NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter for longwave-radiation. Suggestions are Colorado - 0.023 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopyVectorBased::init(void) {

  nhru = getdim(TDim::NHRU); // transfers current # of HRU's to module

  for (hh = 0; hh < nhru; ++hh) {

    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa

    rain_load[hh] = 0.0;
    Snow_load[hh] = 0.0;

    cum_net_snow[hh] = 0.0;
    cum_net_rain[hh] = 0.0;
    cum_Subl_Cpy[hh] = 0.0;
    cum_intcp_evap[hh] = 0.0;
    cum_SUnload[hh] = 0.0;
    cum_SUnload_H2O[hh] = 0.0;

    if(Ht[hh] > Zwind[hh]){
      CRHMException TExcept(string("'" + Name + " (CanopyVectorBased)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), TExcept::WARNING);
      LogError(TExcept);
    }
  }
}

void ClassCRHMCanopyVectorBased::run(void){

  double Exposure, LAI_, Vf, Vf_, Kstar_H, Kd;
  //double Tau; variable is unreferenced commenting out for now - jhs507

  for (hh = 0; chkStruct(); ++hh){

    switch (variation){
      case VARIATION_ORG:
      Qsi_ =  Qsi[hh];
      Qli_ =  Qli[hh];
      break;
      case VARIATION_1:
      Qsi_ =  Qsi[hh];
      Qli_ =  QliVt_Var[hh];
      break;
      case VARIATION_2:
      Qsi_ =  QsiS_Var[hh];
      Qli_ =  Qli[hh];
      break;
      case VARIATION_3:
      Qsi_ =  QsiS_Var[hh];
      Qli_ =  QliVt_Var[hh];
      break;
      case VARIATION_4:
      Qsi_ =  QsiA_Var[hh];
      Qli_ =  QliVt_Var[hh];
      break;
    } // switch

    net_rain[hh] = 0.0;
    direct_rain[hh] = 0.0;
    drip_Cpy[hh] = 0.0;
    intcp_evap[hh] = 0.0;

    net_snow[hh] = 0.0;
    direct_snow[hh] = 0.0;
    SUnload[hh] = 0.0;
    SUnload_H2O[hh] = 0.0;
    Subl_Cpy[hh] = 0.0;

// Canopy temperature is approximated by the air temperature.

    double T1 = hru_t[hh] + CRHM_constants::Tm;

    double rho = Pa[hh]*1000/(CRHM_constants::Rgas*T1);

    double U1 = hru_u[hh]; // Wind speed (m/s)

    ra[hh] = (log(Zref[hh]/Z0snow[hh])*log(Zwind[hh]/Z0snow[hh]))/sqr(CRHM_constants::kappa)/U1;

    double deltaX = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1)/(CRHM_constants::Rgas*sqr(T1));

    double q = (hru_rh[hh]/100)*Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)

    Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_ - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho/ra[hh])/
             (4*CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*deltaX)*rho/ra[hh]);

    Ts[hh] -= CRHM_constants::Tm;

    if(Ts[hh] > 0.0 || SWE[hh] <= 0.0)
      Ts[hh] = 0.0;

    switch(CanopyClearing[hh]){
      case 0: // canopy

        Exposure = Ht[hh] - Common::DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
        if(Exposure < 0.0)
          Exposure = 0.0;

        LAI_ = LAI[hh]*Exposure/Ht[hh];

        Vf = 0.45 - 0.29*log(LAI[hh]);

        Vf_ = Vf + (1.0 - Vf)*sin((Ht[hh] - Exposure)/Ht[hh]*M_PI_2);

        if(SolAng[hh] > 0.001 && cosxs[hh] > 0.001 && cosxsflat[hh] > 0.001) {
          k[hh] = 1.081*SolAng[hh]*cos(SolAng[hh])/sin(SolAng[hh]);
          double limit = cosxsflat[hh]/cosxs[hh];
          if(limit > 2.0)
            limit = 2.0;
          Tauc[hh] = exp(-k[hh]*LAI_*limit);
        }
        else{
          k[hh] = 0.0;
          Tauc[hh] = 0.0;
        }

        Kstar_H = Qsi_*(1.0 - Alpha_c[hh] - Tauc[hh]*(1.0 - Albedo[hh]));

        Qlisn[hh] = Qli_*Vf_ + (1.0f - Vf_)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f) + B_canopy[hh]*Kstar_H;

        Qlisn_Var[hh] = Qlisn[hh];

        Qsisn[hh] = Qsi_*Tauc[hh];

        Qsisn_Var[hh] = Qsisn[hh];

        Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

        Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh]*(1.0 - Albedo[hh]);

        Qnsn_Var[hh] = Qnsn[hh];

        break;
      case 1:  // clearing

        Qlisn[hh] = Qli_;

        Qlisn_Var[hh] = Qlisn[hh];

        Qsisn[hh] = Qsi_;

        Qsisn_Var[hh] = Qsisn[hh];

        Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

        Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh]*(1.0 - Albedo[hh]);

        Qnsn_Var[hh] = Qnsn[hh];

        break;
      case 2:  // gap
        Exposure = Surrounding_Ht[hh] - Common::DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
        if(Exposure < 0.0)
          Exposure = 0.0;

        LAI_ = LAI[hh]*Exposure/Surrounding_Ht[hh];

        Vf = 0.45 - 0.29*log(LAI[hh]);

        double Tau_d = Vf + (1.0 - Vf)*sin((Surrounding_Ht[hh] - Exposure)/Surrounding_Ht[hh]*M_PI_2); // previously Vf_

// calculate forest clearing sky view factor (Vgap) via Reifsnyder and Lull?s (1965) expression:

        double Vgap = sqr(sin(atan2(Gap_diameter[hh], 2.0*Surrounding_Ht[hh])));

// calculate beam pathlength correction (variable Gap_beam_corr) for gap:

        double Gap_beam_corr = 0;
        if(Qsi_ > 0.0 && SolAng[hh] > 0.001){
          double cosxsLim = 3;
          if(cosxs[hh] >  0.33)
            cosxsLim = 1.0/cosxs[hh];

          Gap_beam_corr = cosxsLim*Surrounding_Ht[hh]*(1.0/cos(SolAng[hh]) - Gap_diameter[hh]/(2.0*Surrounding_Ht[hh])/sin(SolAng[hh]));
          if(Gap_beam_corr > 10.0)
            Gap_beam_corr = 10.0;
          else if(Gap_beam_corr < 0.0)
            Gap_beam_corr = 0.0;
        }
// calculate beam shortwave transmittance of the gap:

        double product = LAI[hh]*Gap_beam_corr;
        if(product > 50)
          product = 50;

        double Tau_b_gap = exp(-product);

        Kd = Qsi_*(1.0 - Alpha_c[hh] - Tau_b_gap*(1.0 - Albedo[hh]));

        Qlisn[hh] = Vgap*Qli_ + (1.0 - Vgap)*((Qli_*Tau_b_gap + (1.0 - Tau_b_gap)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f)) + B_canopy[hh]*Kd);

        Qlisn_Var[hh] = Qlisn[hh];

        Qsisn[hh] = cosxs[hh]*Qdfo[hh]*Tau_b_gap + Vgap*(Qsi_ - Qdfo[hh]) + (1.0 - Vgap)*Tau_d*(Qsi_ - Qdfo[hh]);
        if(Qsisn[hh] < 0.0)
          Qsisn[hh] = 0.0;

        Qsisn_Var[hh] = Qsisn[hh];

        Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

        Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh]*(1-Albedo[hh]);

        Qnsn_Var[hh] = Qnsn[hh];

        break;
    } // switch

    switch(CanopyClearing[hh]){
      case 0: // canopy
//==============================================================================
// coupled forest snow interception and sublimation routine:
// after Cebulski & Pomeroy 2025:

if ((Snow_load[hh] > 0.0 || hru_snow[hh] > 0.0))
{ // calculate increase in Snow_load and direct_snow if we are in canopy (i.e., Cc > 0)
  const double k_cp = 20;    // rate of increase of the sigmoidal curve below
  const double v_snow = 0.8;  // terminal fall velocity of snowfall taken from Isyumov, 1971
  Clca[hh] = 0; // leaf contact area (Clca) based on trajectory angle
  double IP = 0; // interception efficiency (IP)
  double dL = 0; // change in canopy snow load

  if (hru_u[hh] > 0 && Cc[hh] < 1 && Cc[hh] > 0)
  { // increase leaf contact area (Clca) based on wind speed and canopy coverage (Cc)
    double Ht_1_third = Ht[hh] * (1.0 / 3.0);
    double Cp_inc = 0;
    if ((Ht_1_third - (2.0 / 3.0) * Zwind[hh]) > 0.0)
    {
      u_1_third_Ht[hh] = hru_u[hh] * log((Ht_1_third - (2.0 / 3.0) * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]);
      double snow_traj_angle = atan(u_1_third_Ht[hh] / v_snow);                         // in radians
      Cp_inc = (1 - Cc[hh]) / (1 + exp(-k_cp * (sin(snow_traj_angle) - (1 - Cc[hh])))); // fractional increas in leaf contact area (Clca) based on horizontal trajectory. This is modified from Cebulski & Pomeroy snow interception paper. Has only been tested on forest plots with Cc of .3 and .5.
    }
    Clca[hh] = Cc[hh] + Cp_inc; // calculated leaf contact area (Clca) based on trajectory angle
  }
  else
  {
    Clca[hh] = Cc[hh]; // use leaf contact area from nadir i.e., Clca == 1 for Cc == 1 and Clca == 0 when Cc == 0
  }

  IP = Clca[hh] * alpha[hh]; // interception efficiency (IP)
  dL = IP * hru_snow[hh]; // change in canopy snow load

  Snow_load[hh] += dL;

  // calculate canopy snow throughfall before unloading:

  direct_snow[hh] += (1-IP) * hru_snow[hh];

  // Finished initial loading now start the ablation paramaterisations 

  double Vi = 0; // submilation rate coefficient for exposed snow (s-1)
  double IceBulbT = 0; // ice bulb temperature of canopy snow
  double U = 0; // unloading rate coefficient used in Hedstrom & Pomeroy 1998 param. 

switch(SublimationSwitch[hh]){
case 0: // do not sublimate, used for debugging or experiments, recommend using case 1 otherwise.

      std::cout << "SublimationSwitch Case 0: No canopy snow sublimation applied.\n";
      break;

case 1: // canopy snow sublimation with Pomeroy et al. (1998) paramaterisation

// Pomeroy et al. (1998) sublimation routine modified by Alex Cebulski to change maximum intercepted load from Hedstrom 1998 calculation to constant based on observations from several studies showing much higher intercepted loads.
// calculate snow ventilation windspeed:

//=============================================================================
        const double gamma = 1.15;
        const double AlbedoIce = 0.8;       // albedo of ideal ice sphere
        const double Radius = 5.0e-4;       // radii of single 'ideal' ice sphere in, m)
        const double KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
        const double ks = 0.0114;           // snow shape coefficient for jack pine
        const double Fract = 0.37;          // fractal dimension of intercepted snow
        // const double Hs = 2.838e6;          // heat of sublimation (MJ/kg) changed to PBSM_constants::LATH which has same value.
//==============================================================================

          double xi2 = 1-Zvent[hh];
          double windExt2 = (gamma * LAI[hh] * xi2);
          double uVent = u_FHt[hh] * exp(-1 * windExt2);

// Calculate wind speed at canopy top for sublimation calculation, moved from initial interception chunk by Alex Cebulski November 2024

          if(Ht[hh] - 2.0/3.0*Zwind[hh] > 0.0)
            u_FHt[hh] = hru_u[hh]*log((Ht[hh] - 2.0/3.0*Zwind[hh] )/ 0.123*Zwind[hh])/log((Zwind[hh] - 2.0/3.0*Zwind[hh] )/ 0.123*Zwind[hh]);
          else
            u_FHt[hh] = 0.0;

          double I1 = 0.0;

// calculate sublimation of intercepted snow from ideal intercepted ice sphere (500 microns diameter):

          double Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;

          double Es = 611.15f * exp(22.452f*hru_t[hh]/(hru_t[hh] + 273.0f));  // {sat pressure}

          double SvDens = Es*PBSM_constants::M/(PBSM_constants::R*(hru_t[hh] + 273.0f)); // {sat density}

          Lamb = 6.3e-4*(hru_t[hh]+273.0) + 0.0673;  // thermal conductivity of atmosphere
          Nr = 2.0 * Radius * uVent / KinVisc;  // Reynolds number
          Nu = 1.79 + 0.606 * sqrt((double) Nr); // Nusselt number
          SStar = M_PI * sqr(Radius) * (1.0f - AlbedoIce) * Qsi_;  // SW to snow particle !!!! changed
          A1 = Lamb * (hru_t[hh] + 273) * Nu;
          B1 = PBSM_constants::LATH * PBSM_constants::M /(PBSM_constants::R * (hru_t[hh] + 273.0f))- 1.0;
          J = B1/A1;
          Sigma2 = hru_rh[hh]/100 -1;
          D = 2.06e-5* pow((hru_t[hh]+273.0f)/273.0f, -1.75f); // diffusivity of water vapour
          C1 = 1.0/(D*SvDens*Nu);

          Alpha = 5.0;
          Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Radius * Radius * Radius; // 18Mar2022: remove Gamma Distribution Correction term, *(1.0 + 3.0/Alpha + 2.0/sqr(Alpha));
// sublimation rate of single 'ideal' ice sphere:

          double Vs = (2.0* M_PI* Radius*Sigma2 - SStar* J)/(PBSM_constants::LATH* J + C1)/Mpm;

          pot_subl_cpy[hh] = Vs; // export the dimensionless sublimation rate (s-1) added by alex 2023-07-21

// snow exposure coefficient (Ce):

          double Ce;
          if ((Snow_load[hh]/Lmax[hh]) <= 0.0)
            Ce = 0.07;
          else
            Ce = ks* pow((Snow_load[hh]/Lmax[hh]), -Fract);

// calculate 'potential' canopy sublimation:

          Vi = Vs*Ce;

// limit sublimation to canopy snow available and take sublimated snow away from canopy snow at timestep start

          Subl_Cpy[hh] = -Snow_load[hh]*Vi*PBSM_constants::LATH*Global::Interval*24*3600/PBSM_constants::LATH; // make W/m2
          if(Subl_Cpy[hh] > Snow_load[hh]){
            Subl_Cpy[hh] = Snow_load[hh];
            Snow_load[hh] = 0.0;
          }
          else{
            Snow_load[hh] -= Subl_Cpy[hh];
            if(Snow_load[hh] < 0.0)
              Snow_load[hh] = 0.0;
          }
}

if(MassUnloadingSwitch[hh] == 0 || MeltwaterSwitch[hh] == 0){
  // calculate 'ice-bulb' temperature of intercepted snow:
  double IceBulbT = hru_t[hh] - (Vi* PBSM_constants::LATH/1e6/CRHM_constants::ci);
  const double U = -1 * log(0.678) / (24 * 7 * Global::Freq / 24); // weekly dimensionless unloading coefficient -> to CRHM time interval // 21Mar2022 correction: invert the term 24/Global::Freq, use unloading rate coefficient U = -log(c)/t for snow unloading determined by inverse function of c = e^(-Ut) = 0.678 based on Eq. 14 in Hedstrom and Pomeroy (1998)
}

switch(MassUnloadingSwitch[hh]){
  case 0: // This is the mass unloading portion of the latest iteration of the Hedstrom & Pomeroy 1998 unloading with modifications by Ellis et al. (2010) and Floyd (2012). Generally used with MeltwaterSwitch == 0.
                                                      
    // determine whether canopy snow is unloaded as mass clumps:

            if(IceBulbT < unload_t[hh]){ // has to be at least one interval. Trip on half step
              SUnload[hh] = Snow_load[hh] * U; // the dimensionless unloading coefficient already /interval, 21Mar2022 correction: use unloading rate coefficient U
            }

  case 1: // This is the updated mass snow unloading parameterisations from Cebulski & Pomeroy to unload based on time, wind, and air temperature.
    // temperature induced unloading
    const double a_T = 2.584003e-05; // Cebulski & Pomeroy coef from exponential function of unloading + drip and air temp measurements at Fortress mountain when wind speed <= 1 m/s.
    const double b_T = 1.646875e-01; // Cebulski & Pomeroy coef from exponential function of unloading + drip and air temp measurements at Fortress mountain when wind speed <= 1 m/s.
    
    double fT = a_T * exp(b_T * hru_t[hh]); // unloading rate based on warming of snow in the canopy (s-1), still need to partition out the portion of this that is drip vs mass unloading

    // mechanical wind induced unloading
    const double a_u = 5.204024e-06; // Cebulski & Pomeroy coef from exponential function of unloading + drip and wind speed measurements at Fortress mountain when air temp < -6 C.
    const double b_u = 7.363594e-02; // Cebulski & Pomeroy coef from exponential function of unloading + drip and wind speed measurements at Fortress mountain when air temp < -6 C.
    double Ht_mid = Ht[hh] * (1.0 / 2.0); // half of canopy height
    double u_mid = 0;
    double fu = 0;
    if ((Ht_mid - (2.0 / 3.0) * Zwind[hh]) > 0.0)
    {
      u_mid = hru_u[hh] * log((Ht_mid - (2.0 / 3.0) * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]);
      double fu = u_mid * a_u * exp(b_u * u_mid); // unloading rate due to wind (s-1)
    }

    // duration based unloading
    const double a_t =  8.194345e-06; // Cebulski & Pomeroy coef from exponential function of unloading + drip and duration snow has been intercepted in the canopy at Fortress mountain when wind speed <= 1 m/s and air temperature < -6 C.
    const double b_t = -1.540050e+02; // Cebulski & Pomeroy coef from exponential function of unloading + drip and duration snow has been intercepted in the canopy at Fortress mountain when wind speed <= 1 m/s and air temperature < -6 C.

    double t_snow_in_canopy = 12 * 60 * 60; // duration snow intercepted in the canopy, set to constant of 12 hours. TODO need to track duration that snow has been intercepted in the canopy. Can do this similar to snowpack albedo calculation.
    
    double ft = a_t * exp(b_t * t_snow_in_canopy);

    // ablation via temperature, wind, and duration based unloading
    double dt = Global::Interval * 24 * 60 * 60; // converts the interval which is a time period (i.e., time/cycles, 1 day/# obs) to timestep in seconds.
    SUnload[hh] = Snow_load[hh] * (fT + fu + ft) * dt; // converts our 
}

// handle mass unloading regardless of what parameterisation is chosen
if (SUnload[hh] > Snow_load[hh])
{
  SUnload[hh] = Snow_load[hh];
  Snow_load[hh] = 0.0;
}
else
  Snow_load[hh] -= SUnload[hh];

cum_SUnload[hh] += SUnload[hh];

switch(MeltwaterSwitch[hh]) {
    case 0: { // Block for case 0
        // This is the meltwater drip portion of the latest iteration of the Hedstrom & Pomeroy 1998 unloading with modifications by Ellis et al. (2010) and Floyd (2012).
        double Six_Hour_Divisor = Global::Freq / 4.0; // Unload over 6 hours

        if (IceBulbT >= unload_t_water[hh]) {
            drip_Cpy[hh] = Snow_load[hh] / Six_Hour_Divisor;
            SUnload_H2O[hh] = drip_Cpy[hh];
            Snow_load[hh] -= SUnload_H2O[hh];
            cum_SUnload_H2O[hh] += SUnload_H2O[hh];
        }
        else if (IceBulbT >= unload_t[hh]) {
            SUnload[hh] = Snow_load[hh] / Six_Hour_Divisor;
            Snow_load[hh] -= SUnload[hh];
            cum_SUnload[hh] += SUnload[hh];
        }
        break;
    }

    case 1: { // Block for case 1
        // This is the meltwater drip parameterisation from CLASS
        drip_Cpy[hh] = 0;
        SUnload_H2O[hh] = drip_Cpy[hh];
        Snow_load[hh] -= SUnload_H2O[hh];
        cum_SUnload_H2O[hh] += SUnload_H2O[hh];
        break;
    }
}

// calculate total sub-canopy snow:

          net_snow[hh] = direct_snow[hh] + SUnload[hh];
          break;
      } // case canopy
      case 1:  // clearing
      case 2:  // gap
        net_snow[hh] = hru_snow[hh];
        net_rain[hh] = hru_rain[hh];
        break;
    }  // switch

// calculate horizontal canopy-coverage (Cc):

    double smax, Q; // cannot be in switch structure

     switch(CanopyClearing[hh]){

       case 0:  // canopy

        Cc[hh] = std::min(1.0, 0.29 * std::log(LAI[hh]) + 0.55); // update by Alex so Cc is not greater than 1
        if(Cc[hh] <= 0.0)
          Cc[hh] = 0.0;

        smax = Cc[hh]*LAI[hh]*0.2;

//  Forest rain interception and evaporation model
// 'sparse' Rutter interception model (i.e. Valente 1997):

// calculate direct throughfall:

        if(hru_rain[hh] > 0.0){

          direct_rain[hh] = hru_rain[hh] * (1-Cc[hh]);

  // calculate rain accumulation on canopy before evap loss:

          if (rain_load[hh] + hru_rain[hh]*Cc[hh] > smax){
            drip_Cpy[hh] += (rain_load[hh] + hru_rain[hh]*Cc[hh] - smax);
            rain_load[hh] = smax;
          }
          else
            rain_load[hh] += hru_rain[hh]*Cc[hh];

        }  // if hru_rain[hh] > 0.0

// calculate 'actual evap' of water from canopy and canopy storage after evaporation::

        if(rain_load[hh] > 0.0){
          if(inhibit_evap[hh] == 0){ // use Granger when no snowcover
            if(rain_load[hh] >= hru_evap[hh]*Cc[hh]){ // (evaporation in mm)
              intcp_evap[hh] = hru_evap[hh]*Cc[hh];  //
              rain_load[hh] -= hru_evap[hh]*Cc[hh];
            }
            else{
               intcp_evap[hh] = rain_load[hh];
               rain_load[hh] = 0.0;
            }
          }
          else{ // use Priestley-Taylor when snowcover
            Q = Qsi_*86400/Global::Freq/1e6/lambda(hru_t[hh]); // convert w/m2 to mm/m2/int

            if(Qsi_ > 0.0)
             Pevap[hh] = 1.26*delta(hru_t[hh])*Q/(delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
            else
             Pevap[hh] = 0.0;

            if(rain_load[hh] >= Pevap[hh]*Cc[hh]){  // (evaporation in mm)
               intcp_evap[hh] = Pevap[hh]*Cc[hh];  // check
               rain_load[hh] -= Pevap[hh]*Cc[hh];
            }
            else{
               intcp_evap[hh] = rain_load[hh]; // check
               rain_load[hh] = 0.0;
            }
          }
        } // if rain_load[hh] > 0.0

// cumulative amounts....

        net_rain[hh] = direct_rain[hh] + drip_Cpy[hh];

        cum_intcp_evap[hh] += intcp_evap[hh];
        cum_Subl_Cpy[hh] += Subl_Cpy[hh];
        break;
      default :  // clearing and gap
        break;
    }  // switch

    net_p[hh] = net_rain[hh] + net_snow[hh];
    cum_net_rain[hh] += net_rain[hh];
    cum_net_snow[hh] += net_snow[hh];
  } // end for
}

void ClassCRHMCanopyVectorBased::finish(bool good) {
  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (CanopyVectorBased)'  cum_net_snow    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_snow[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (CanopyVectorBased)'  cum_net_rain    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_rain[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (CanopyVectorBased)'  cum_Subl_Cpy    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Subl_Cpy[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (CanopyVectorBased)'  cum_intcp_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (CanopyVectorBased)'  cum_SUnload_H2O (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}

double ClassCRHMCanopyVectorBased::delta(double t) // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
{
  if (t > 0.0)
    return(2504.0*exp(17.27 * t/(t+237.3)) / sqr(t+237.3));
  else
    return(3549.0*exp( 21.88 * t/(t+265.5)) / sqr(t+265.5));
}

double ClassCRHMCanopyVectorBased::lambda(double t) // Latent heat of vaporization (mJ/(kg DEGREE_CELSIUS))
{
   return( 2.501 - 0.002361 * t );
}

double ClassCRHMCanopyVectorBased::gamma(double Pa, double t) // Psychrometric constant (kPa/DEGREE_CELSIUS)
{
   return( 0.00163 * Pa / lambda(t)); // lambda (mJ/(kg DEGREE_CELSIUS))
}

double ClassCRHMCanopyVectorBased::RHOa(double t, double ea, double Pa) // atmospheric density (kg/m^3)
{
  const double R = 2870;
   return (1E4*Pa /(R*( 273.15 + t))*(1.0 - 0.379*(ea/Pa)) ); //
}
