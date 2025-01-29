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
// created by Manishankar Mondal

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

ClassCRHMCanopyVectorBased *ClassCRHMCanopyVectorBased::klone(string name) const
{
  return new ClassCRHMCanopyVectorBased(name);
}

void ClassCRHMCanopyVectorBased::decl(void)
{

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

  declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

  variation_set = VARIATION_2 + VARIATION_3;

  declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

  variation_set = VARIATION_4;

  declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);

  variation_set = VARIATION_ORG;

  declreadobs("obs_snow_load", TDim::NHRU, "Weighed tree canopy snow load", "(kg/m^2)", &obs_snow_load, HRU_OBS_misc);

  // get variables:

  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);

  declgetvar("*", "hru_u", "(m/s)", &hru_u);

  declgetvar("*", "hru_rh", "()", &hru_rh);

  declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

  declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

  declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

  declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

  declgetvar("*", "SolAng", "(r)", &SolAng);

  declgetvar("*", "cosxs", "(r)", &cosxs);

  declgetvar("*", "cosxsflat", "(r)", &cosxsflat);

  declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);

  declgetvar("*", "Albedo", "()", &Albedo);

  declputvar("*", "SWE", "(mm)", &SWE);

  // declputvar("*", "TCanSnow", "(" + string(DEGREE_CELSIUS) + ")", &TCanSnow); found better performance when just using the ice bulb temp so no need for pspNew module

  // declared observations

  declvar("Ts", TDim::NHRU, "snow surface temperature", "(" + string(DEGREE_CELSIUS) + ")", &Ts);

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

  declvar("canopy_snowmelt", TDim::NHRU, "amount of snow intercepted in the canopy that is melted ", "(mm/int)", &canopy_snowmelt);

  declvar("SUnloadMelt", TDim::NHRU, "solid snow unloaded from the canopy proportional to melt. ", "(mm/int)", &SUnloadMelt);

  declvar("SUnloadWind", TDim::NHRU, "solid snow unloading from the canopy induced by wind.", "(mm/int)", &SUnloadWind);

  declvar("Cp_h2o", TDim::NHRU, "Bulk volumetric heat capacity of frozen and liquid h2o intercepted in the canopy.", "(j m-2 K-1)", &Cp_h2o);

  declvar("SUnload", TDim::NHRU, "unloaded canopy snow", "(mm/int)", &SUnload);

  declvar("SUnload_H2O", TDim::NHRU, "unloaded canopy snow as water", "(mm/int)", &SUnload_H2O);

  declstatdiag("cum_SUnload_H2O", TDim::NHRU, "Cumulative unloaded canopy snow as water", "(mm)", &cum_SUnload_H2O);

  declstatdiag("cum_SUnload", TDim::NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", &cum_SUnload);

  declvar("net_snow", TDim::NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

  declstatdiag("cum_net_snow", TDim::NHRU, "Cumulative hru_snow minus interception", "(mm)", &cum_net_snow);

  declvar("net_p", TDim::NHRU, "total precipitation after interception", "(mm/int)", &net_p);

  decldiag("u_FHt", TDim::NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

  decldiag("u_1_third_Ht", TDim::NHRU, "wind speed at one-third forest height (z = 1/3*Ht) for the Cebulski & Pomeroy vector based param.", "(m/s)", &u_1_third_Ht);

  declvar("Clca", TDim::NHRU, "Leaf contact area adjusted for hydrometeor trajectory angle.", "(s-1)", &Clca);

  declvar("LAI_", TDim::NHRU, "Leaf area index adjusted for snow cover", "(-)", &LAI_);

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

  declparam("Cc", TDim::NHRU, "[1]", "0", "1", "canopy coverage, (1-sky view fraction)", "()", &Cc);

  declparam("LAI", TDim::NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

  declparam("Sbar", TDim::NHRU, "[6.6]", "0.0", "20.0", "Uncorrected snow capacity", "(kg/m^2)", &Sbar);

  declparam("Lmax", TDim::NHRU, "[50]", "0.0", "100.0", "maximum canopy snow interception load, currently just used for sublimation exposure coef. 50 based on max observed in Storck et al. 2002 and Cebulski & Pomeroy", "(kg/m^2)", &Lmax);

  declparam("alpha", TDim::NHRU, "[0.836]", "0.0", "1.0", "$alpha$ is an efficiency constant which determines the fraction of snowflakes that contact the $C_p$ elements and are stored in the canopy (i.e., intercepted) before canopy snow unloading or ablation processes begin. Default is based on Cebulski & Pomeroy plot scale observations at Fortress Mountain PWL and Forest Tower plots.", "()", &alpha);

  declparam("Zvent", TDim::NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

  declparam("unload_t", TDim::NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(" + string(DEGREE_CELSIUS) + ")", &unload_t);

  declparam("unload_t_water", TDim::NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(" + string(DEGREE_CELSIUS) + ")", &unload_t_water);

  declparam("u_mid_th", TDim::NHRU, "[0.0]", "0.0", "20.0", "Minimum wind speed for wind induced unloading to occur.", "m/s", &u_mid_th);

  declparam("CanopyClearing", TDim::NHRU, "[0]", "0", "2", "canopy - 0/clearing - 1/gap - 2", "()", &CanopyClearing);

  declparam("SublimationSwitch", TDim::NHRU, "[1]", "0", "1", "Pomeroy 1998 sublimation parameterisation, off - 0, on - 1", "()", &SublimationSwitch);

  declparam("MassUnloadingSwitch", TDim::NHRU, "[1]", "0", "1", "Canopy snow mass unloading parameterisation options: Hedstrom & Pomeroy 1998 constant time based unloading - 0, Cebulski & Pomeroy exponential curves for wind induced unloading, temperature based unloading, and time based unloading - 1", "()", &MassUnloadingSwitch);

  declparam("MeltwaterSwitch", TDim::NHRU, "[0]", "0", "1", "Canopy snow meltwater drip parameterisation options: Ellis et al. (2010) and Floyd (2012) - 0, CLASS - 1", "()", &MeltwaterSwitch);

  declparam("CanopyWindSwitch", TDim::NHRU, "[0]", "0", "1", "Canopy wind model to use at height Zcan, 0 - for Cionco, 1 - for Prandtl-von Kármán log-linear relationship", "()", &CanopyWindSwitch);

  declparam("melt_drip_ratio", TDim::NHRU, "[2]", "0.0", "10", "Ratio of mass unloading of solid snow due to melt compared to canopy snowmelt.", "(-)", &melt_drip_ratio);

  decldiagparam("Alpha_c", TDim::NHRU, "[0.1]", "0.05", "0.2", "canopy albedo, used for longwave-radiation enhancement estimation", "()", &Alpha_c);

  decldiagparam("B_canopy", TDim::NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter for longwave-radiation. Suggestions are Colorado - 0.023 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopyVectorBased::init(void)
{

  nhru = getdim(TDim::NHRU); // transfers current # of HRU's to module

  for (hh = 0; hh < nhru; ++hh)
  {

    Pa[hh] = 101.3f * pow((293.0f - 0.0065f * hru_elev[hh]) / 293.0f, 5.26f); // kPa

    rain_load[hh] = 0.0;
    Snow_load[hh] = 0.0;

    cum_net_snow[hh] = 0.0;
    cum_net_rain[hh] = 0.0;
    cum_Subl_Cpy[hh] = 0.0;
    cum_intcp_evap[hh] = 0.0;
    cum_SUnload[hh] = 0.0;
    cum_SUnload_H2O[hh] = 0.0;

    if (Ht[hh] > Zwind[hh])
    {
      CRHMException TExcept(string("'" + Name + " (CanopyVectorBased)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), TExcept::WARNING);
      LogError(TExcept);
    }
  }
}

void ClassCRHMCanopyVectorBased::run(void)
{ 

  double Exposure, Vf, Vf_, Kstar_H, Kd;
  LAI_[hh] = 0.0; 
  // double Tau; variable is unreferenced commenting out for now - jhs507

  double U_sink; // energy required to increase h2o in the canopy to 0 deg. IOW the energy sink available to freeze water. As water freezes this sink will decrease as the other parts of the canopy warm as latent heat is released from the freezing process.
  double U_conv; // energy sink needed to freeze all liquid water
  double rain_frozen; // rain frozen based on energy sink available
  double dUdt; // internal energy change to the snowpack
  double U_cool; // available energy sink left over after freezing all liquid water used to cool canopy snow
  double U_melt; // energy available for melting snow intercepted in the canopy
  double U_warm; // remaining energy left over to heat the canopy h2o after melting all snow intercepted in the canopy
  double u_mid; // wind speed at half canopy height

  for (hh = 0; chkStruct(); ++hh)
  {

    switch (variation)
    {
    case VARIATION_ORG:
      Qsi_ = Qsi[hh];
      Qli_ = Qli[hh];
      break;
    case VARIATION_1:
      Qsi_ = Qsi[hh];
      Qli_ = QliVt_Var[hh];
      break;
    case VARIATION_2:
      Qsi_ = QsiS_Var[hh];
      Qli_ = Qli[hh];
      break;
    case VARIATION_3:
      Qsi_ = QsiS_Var[hh];
      Qli_ = QliVt_Var[hh];
      break;
    case VARIATION_4:
      Qsi_ = QsiA_Var[hh];
      Qli_ = QliVt_Var[hh];
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
    canopy_snowmelt[hh] = 0.0;
    SUnloadMelt[hh] = 0.0;
    SUnloadWind[hh] = 0.0;

    // Canopy temperature is approximated by the air temperature.

    double T1 = hru_t[hh] + CRHM_constants::Tm; // deg. C to kelvin conversion

    double rho = Pa[hh] * 1000 / (CRHM_constants::Rgas * T1);

    double U1 = hru_u[hh]; // Wind speed (m/s)

    ra[hh] = (log(Zref[hh] / Z0snow[hh]) * log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

    double deltaX = 0.622 * CRHM_constants::Ls * Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas * sqr(T1));

    double q = (hru_rh[hh] / 100) * Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)

    Ts[hh] = T1 + (CRHM_constants::emiss * (Qli_ - CRHM_constants::sbc * pow(T1, 4.0f)) + CRHM_constants::Ls * (q - Common::Qs(Pa[hh], T1)) * rho / ra[hh]) /
                      (4 * CRHM_constants::emiss * CRHM_constants::sbc * pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls * deltaX) * rho / ra[hh]);

    Ts[hh] -= CRHM_constants::Tm;  // back to deg. C

    if (Ts[hh] > 0.0 || SWE[hh] <= 0.0)
      Ts[hh] = 0.0;

    switch (CanopyClearing[hh])
    {
    case 0: // canopy

      Exposure = Ht[hh] - Common::DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
      if (Exposure < 0.0)
        Exposure = 0.0;

      LAI_[hh] = LAI[hh] * Exposure / Ht[hh];

      Vf = Cc[hh];
      Vf_ = Vf;

      //Vf_ = Vf + (1.0 - Vf) * sin((Ht[hh] - Exposure) / Ht[hh] * M_PI_2);

      if (SolAng[hh] > 0.001 && cosxs[hh] > 0.001 && cosxsflat[hh] > 0.001)
      {
        k[hh] = 1.081 * SolAng[hh] * cos(SolAng[hh]) / sin(SolAng[hh]); // Eq. 8 from Pomeroy 2009
        double limit = cosxsflat[hh] / cosxs[hh];
        if (limit > 2.0)
          limit = 2.0;
        Tauc[hh] = exp(-k[hh] * LAI_[hh] * limit);
      }
      else
      {
        k[hh] = 0.0;
        Tauc[hh] = 0.0;
      }

      Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh])); // Eq. 6 from Pomeroy 2009

      Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_) * CRHM_constants::emiss_c * CRHM_constants::sbc * pow(T1, 4.0f) + B_canopy[hh] * Kstar_H; // looks like modification of Eq. 10 from Pomeroy 2009

      Qlisn_Var[hh] = Qlisn[hh];

      Qsisn[hh] = Qsi_ * Tauc[hh];

      Qsisn_Var[hh] = Qsisn[hh];

      Qlosn[hh] = CRHM_constants::emiss * CRHM_constants::sbc * pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

      Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

      Qnsn_Var[hh] = Qnsn[hh];

      break;
    case 1: // clearing

      Qlisn[hh] = Qli_;

      Qlisn_Var[hh] = Qlisn[hh];

      Qsisn[hh] = Qsi_;

      Qsisn_Var[hh] = Qsisn[hh];

      Qlosn[hh] = CRHM_constants::emiss * CRHM_constants::sbc * pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

      Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

      Qnsn_Var[hh] = Qnsn[hh];

      break;
    case 2:                                                         // gap
      Exposure = Surrounding_Ht[hh] - Common::DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
      if (Exposure < 0.0)
        Exposure = 0.0;

      LAI_[hh] = LAI[hh] * Exposure / Surrounding_Ht[hh];

      Vf = 0.45 - 0.29 * log(LAI[hh]);

      double Tau_d = Vf + (1.0 - Vf) * sin((Surrounding_Ht[hh] - Exposure) / Surrounding_Ht[hh] * M_PI_2); // previously Vf_

      // calculate forest clearing sky view factor (Vgap) via Reifsnyder and Lull?s (1965) expression:

      double Vgap = sqr(sin(atan2(Gap_diameter[hh], 2.0 * Surrounding_Ht[hh])));

      // calculate beam pathlength correction (variable Gap_beam_corr) for gap:

      double Gap_beam_corr = 0;
      if (Qsi_ > 0.0 && SolAng[hh] > 0.001)
      {
        double cosxsLim = 3;
        if (cosxs[hh] > 0.33)
          cosxsLim = 1.0 / cosxs[hh];

        Gap_beam_corr = cosxsLim * Surrounding_Ht[hh] * (1.0 / cos(SolAng[hh]) - Gap_diameter[hh] / (2.0 * Surrounding_Ht[hh]) / sin(SolAng[hh]));
        if (Gap_beam_corr > 10.0)
          Gap_beam_corr = 10.0;
        else if (Gap_beam_corr < 0.0)
          Gap_beam_corr = 0.0;
      }
      // calculate beam shortwave transmittance of the gap:

      double product = LAI[hh] * Gap_beam_corr;
      if (product > 50)
        product = 50;

      double Tau_b_gap = exp(-product);

      Kd = Qsi_ * (1.0 - Alpha_c[hh] - Tau_b_gap * (1.0 - Albedo[hh]));

      Qlisn[hh] = Vgap * Qli_ + (1.0 - Vgap) * ((Qli_ * Tau_b_gap + (1.0 - Tau_b_gap) * CRHM_constants::emiss_c * CRHM_constants::sbc * pow(T1, 4.0f)) + B_canopy[hh] * Kd);

      Qlisn_Var[hh] = Qlisn[hh];

      Qsisn[hh] = cosxs[hh] * Qdfo[hh] * Tau_b_gap + Vgap * (Qsi_ - Qdfo[hh]) + (1.0 - Vgap) * Tau_d * (Qsi_ - Qdfo[hh]);
      if (Qsisn[hh] < 0.0)
        Qsisn[hh] = 0.0;

      Qsisn_Var[hh] = Qsisn[hh];

      Qlosn[hh] = CRHM_constants::emiss * CRHM_constants::sbc * pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

      Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1 - Albedo[hh]);

      Qnsn_Var[hh] = Qnsn[hh];

      break;
    } // switch

    switch (CanopyClearing[hh])
    {
    case 0: // canopy
      //==============================================================================
      // coupled forest snow interception and sublimation routine:
      // after Cebulski & Pomeroy 2025:

      if ((Snow_load[hh] > 0.0 || rain_load[hh] > 0.0 || hru_snow[hh] > 0.0))
      {                            // calculate increase in Snow_load and direct_snow if we are in canopy (i.e., Cc > 0)
        const double k_cp = 20;    // rate of increase of the sigmoidal curve below
        const double v_snow = 0.8; // terminal fall velocity of snowfall taken from Isyumov, 1971
        Clca[hh] = 0.0;              // leaf contact area (Clca) based on trajectory angle
        double IP = 0.0;             // interception efficiency (IP)
        double dL = 0.0;             // change in canopy snow load

        if (hru_u[hh] > 0.0 && Cc[hh] < 1.0 && Cc[hh] > 0.0)
        { // increase leaf contact area (Clca) based on wind speed and canopy coverage (Cc)
          double Ht_1_third = Ht[hh] * (1.0 / 3.0);
          double Cp_inc = 0;
          switch (CanopyWindSwitch[hh])
          {
            case 0:
            {  // original using Cionco wind model for dense canopies

              // wind speed used for vector based initial snow interception
              if ((Ht[hh] - (2.0 / 3.0) * Zwind[hh]) > 0.0){
                u_FHt[hh] = hru_u[hh] * log((Ht[hh] - (2.0 / 3.0) * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]);
                double A = 2.4338 + 3.45753 * exp(-u_FHt[hh]);                       /* Modified Cionco wind model */
                u_1_third_Ht[hh] = u_FHt[hh] * exp(A * ((Ht_1_third) / (Ht[hh])-1.0)); /* calculates canopy windspd  */
              } else {
                u_1_third_Ht[hh] = 0.0;
              }
              break;
            } // case 0

            case 1:
            { // Canopy wind profile developed at Fortress sparse canopy
              double d0 = 0.5791121; // displacement height observed at sparse forest around Fortress Forest Tower
              double z0m = 0.4995565; // roughness length observed at above site
              
              // wind speed used for vector based initial snow interception
              if ((Ht_1_third - d0) > z0m){
                double Ustar = hru_u[hh]*PBSM_constants::KARMAN/(log((Zwind[hh]-d0)/z0m));
                u_1_third_Ht[hh] = Ustar/PBSM_constants::KARMAN * log((Ht_1_third - d0)/z0m);
              } else {
                 u_1_third_Ht[hh] = 0.0;
              }
              break;
            } // case 1
          } // end of switch CanopyWind

          if(u_1_third_Ht[hh] > 0.0){
            double snow_traj_angle = atan(u_1_third_Ht[hh] / v_snow);                         // in radians
            Cp_inc = (1 - Cc[hh]) / (1 + exp(-k_cp * (sin(snow_traj_angle) - (1 - Cc[hh])))); // fractional increas in leaf contact area (Clca) based on horizontal trajectory. This is modified from Cebulski & Pomeroy snow interception paper. Has only been tested on forest plots with Cc of .3 and .5.
            Clca[hh] = Cc[hh] + Cp_inc; // calculated leaf contact area (Clca) based on trajectory angle
            } else {
              Clca[hh] = Cc[hh]; // use leaf contact area from nadir i.e., Clca == 1 for Cc == 1 and Clca == 0 when Cc == 0
            }
        } else {
          Clca[hh] = Cc[hh]; // use leaf contact area from nadir i.e., Clca == 1 for Cc == 1 and Clca == 0 when Cc == 0
        }
          
        IP = Clca[hh] * alpha[hh]; // interception efficiency (IP)
        dL = IP * hru_snow[hh];    // change in canopy snow load

        Snow_load[hh] += dL;

        // calculate canopy snow throughfall before unloading:

        direct_snow[hh] += (1 - IP) * hru_snow[hh];

        // Finished initial loading now start the ablation paramaterisations

        double Vi = 0;       // submilation rate coefficient for exposed snow (s-1)
        double IceBulbT = 0; // ice bulb temperature of canopy snow
        double U = 0;        // unloading rate coefficient used in Hedstrom & Pomeroy 1998 param.

        switch (SublimationSwitch[hh])
        {
        case 0:
        { // do not sublimate, used for debugging or experiments, recommend using case 1 otherwise.

          std::cout << "SublimationSwitch Case 0: No canopy snow sublimation applied.\n";
          break;
        } // case 0

        case 1:
        { // canopy snow sublimation with Pomeroy et al. (1998) paramaterisation

          // Pomeroy et al. (1998) sublimation routine
          // calculate snow ventilation windspeed:

          //=============================================================================
          const double gamma = 1.15;
          const double AlbedoIce = 0.8;   // albedo of ideal ice sphere
          const double Radius = 5.0e-4;   // radii of single 'ideal' ice sphere in, m)
          const double KinVisc = 1.88e-5; // kinematic viscosity of air (Sask. avg. value)
          const double ks = 0.0114;       // snow shape coefficient for jack pine
          const double Fract = 0.37;      // fractal dimension of intercepted snow
                                          // const double Hs = 2.838e6;          // heat of sublimation (MJ/kg) changed to PBSM_constants::LATH which has same value.
                                          //==============================================================================

          double xi2 = 1 - Zvent[hh];
          double windExt2 = (gamma * LAI[hh] * xi2);

          // Calculate wind speed at canopy top for sublimation calculation, moved from initial interception chunk by Alex Cebulski November 2024

          if (Ht[hh] - 2.0 / 3.0 * Zwind[hh] > 0.0)
            u_FHt[hh] = hru_u[hh] * log((Ht[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]);
          else
            u_FHt[hh] = 0.0;

          double uVent = u_FHt[hh] * exp(-1 * windExt2);

          // calculate sublimation of intercepted snow from ideal intercepted ice sphere (500 microns diameter):

          double Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;

          double Es = 611.15f * exp(22.452f * hru_t[hh] / (hru_t[hh] + 273.0f)); // {sat pressure}

          double SvDens = Es * PBSM_constants::M / (PBSM_constants::R * (hru_t[hh] + 273.0f)); // {sat density}

          Lamb = 6.3e-4 * (hru_t[hh] + 273.0) + 0.0673;           // thermal conductivity of atmosphere
          Nr = 2.0 * Radius * uVent / KinVisc;                    // Reynolds number
          Nu = 1.79 + 0.606 * sqrt((double)Nr);                   // Nusselt number
          SStar = M_PI * sqr(Radius) * (1.0f - AlbedoIce) * Qsi_; // SW to snow particle !!!! changed
          A1 = Lamb * (hru_t[hh] + 273) * Nu;
          B1 = PBSM_constants::LATH * PBSM_constants::M / (PBSM_constants::R * (hru_t[hh] + 273.0f)) - 1.0;
          J = B1 / A1;
          Sigma2 = hru_rh[hh] / 100 - 1;
          D = 2.06e-5 * pow((hru_t[hh] + 273.0f) / 273.0f, -1.75f); // diffusivity of water vapour
          C1 = 1.0 / (D * SvDens * Nu);

          // Alpha = 5.0;
          Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Radius * Radius * Radius; // 18Mar2022: remove Gamma Distribution Correction term, *(1.0 + 3.0/Alpha + 2.0/sqr(Alpha));
                                                                                    // sublimation rate of single 'ideal' ice sphere:

          double Vs = (2.0 * M_PI * Radius * Sigma2 - SStar * J) / (PBSM_constants::LATH * J + C1) / Mpm;

          pot_subl_cpy[hh] = Vs; // export the dimensionless sublimation rate (s-1) added by alex 2023-07-21

          // snow exposure coefficient (Ce):

          // double RhoS = 67.92 + 51.25*exp(hru_t[hh]/2.59);
          // double Lstar = Sbar[hh]*(0.27 + 46.0/RhoS)*LAI[hh];

          double Ce; 
          if ((Snow_load[hh] / Lmax[hh]) <= 0.0) // Using Lmax instead of Lstar as gives more appropriate index of canopy fullness
            Ce = 0.07;
          else
            Ce = ks * pow((Snow_load[hh] / Lmax[hh]), -Fract); // Ce is higher when the canopy is less full with snow as more of it is exposed, TODO maybe limit snow canopy fraction to 1.0 also need to reconsider Lstar 

          // calculate 'potential' canopy sublimation:

          Vi = Vs * Ce;

          // limit sublimation to canopy snow available and take sublimated snow away from canopy snow at timestep start

          Subl_Cpy[hh] = -Snow_load[hh] * Vi * Global::Interval * 24 * 3600;
          if (Subl_Cpy[hh] > Snow_load[hh])
          {
            Subl_Cpy[hh] = Snow_load[hh];
            Snow_load[hh] = 0.0;
          }
          else
          {
            Snow_load[hh] -= Subl_Cpy[hh];
            if (Snow_load[hh] < 0.0)
              Snow_load[hh] = 0.0;
          }
          break;
        } // case 1
        } // sublimation switch

                // Meltwater (drip) Section
        // Enters different parameterisations for meltwater drip of canopy snow based on switch.
        // =============================================================================

        switch (MeltwaterSwitch[hh])
        {
        case 0:
        { // do not melt, used for debugging or experiments or with the HP98 mass unloading which calculates drip empirically, recommend using case 1 otherwise.
          break;
        } // case 0

        case 1:
        { // Block for case 1
          // This is the meltwater drip parameterisation adapted from CLASSIC v1.0.1 https://gitlab.com/cccma/classic/-/releases
          // The algorithm calculates the change in internal energy of the vegetation canopy as a result of the phase change processes
          // Currently the canopy snow temperature is approximated by the classPSPnew module which was developed by Parv. & Pomeroy 2000.
          
          Cp_h2o[hh] = (CRHM_constants::cw * rain_load[hh]) + (CRHM_constants::ci * Snow_load[hh]); // volumetric heat capacity of frozen and liquid h2o intercepted in the canopy (j m-2 K-1). This is different from CLASS who incorporates the vegetation elements here too but since PSPnew treats veg temp as different we do not have the same here.
          IceBulbT = hru_t[hh] - (Vi * PBSM_constants::LATH / CRHM_constants::ci);

          // Energy sink available for freezing liquid water intercepted in the canopy canopy only if T_snow < 0
          if (rain_load[hh] > 0 && IceBulbT < 0){

            U_sink = Cp_h2o[hh] * (0 - IceBulbT); 
            U_conv = rain_load[hh] * LH_FUS(FREEZE); 
            
            if (U_sink <= U_conv){ // not enough energy sink to freeze all liquid water so calculating the portion that will freeze here
              rain_frozen = U_sink / LH_FUS(FREEZE); 
              Snow_load[hh] += rain_frozen; // frozen rain is added to the canopy snow load, this is what is done in CLASS but should maybe treat this differently as will have different adhesion to the canopy
              rain_load[hh] -= rain_frozen;
              IceBulbT = 0.0; // canopy snow is set to freezing temp, this will be used as the snow temp initilization in PSPnew
              // dUdt = dUdt + LH_FUS(FREEZE) * rain_frozen / dt; // release energy from freezing water into the snow in the canopy
              
            } else { // energy sink is large enough to freeze all liquid water intercepted in the canopy
              Snow_load[hh] += rain_load[hh];
              U_cool = U_sink - U_conv; 
              //TCanSnow[hh] = -U_cool / (CRHM_constants::ci * Snow_load[hh]); // temperature of snow intercepted in the canopy after freezing liquid water, this will be used as the snow temp initilization in PSPnew
              // dUdt = dUdt + LH_FUS(FREEZE) * rain_load[hh] / dt; // internal energy change to the snowpack due to freezing, adding energy here as energy is released by freezing liquid water
              rain_load[hh] = 0.0;
            }
          }

          if (Snow_load[hh] > 0 && IceBulbT > 0){ // Canopy snow temperature is above 0
            U_melt = Cp_h2o[hh] * (IceBulbT);
            U_conv = Snow_load[hh] * LH_FUS(FREEZE); // energy required to melt all snow intercepted in the canopy

            if (U_melt <= U_conv){ // not eneough energy to melt all canopy snow
              canopy_snowmelt[hh] = MELT(U_melt);
              Snow_load[hh] -= canopy_snowmelt[hh];
              drip_Cpy[hh] = canopy_snowmelt[hh]; // no holding capacity for canopy snowmelt immediately drips off and does not evaporate, this is how the original routine was and better matches obs at fortress
              //rain_load[hh] += canopy_snowmelt[hh]; // melting snow will drip off canopy based on rainwater routine below this is different from the Ellis 2010 param above which immediately drips off canopy snow melt with no holding capacity.
             // TCanSnow[hh] = 0; // canopy snow is melting so set to 0 deg. C, this will be used as the snow temp initilization in PSPnew
              // dUdt = dUdt - LH_FUS(FREEZE) * canopy_snowmelt[hh] / dt; // internal energy change to the snowpack due to melt, subtracting energy here as energy is required to melt snow
            } else { // all snow in the canopy will be melted
              canopy_snowmelt[hh] = Snow_load[hh];
              drip_Cpy[hh] = canopy_snowmelt[hh]; // no holding capacity for canopy snowmelt immediately drips off and does not evaporate, this is how the original routine was and better matches obs at fortress
              //rain_load[hh] += Snow_load[hh]; // move all snow into the rain store
              U_warm = U_melt - U_conv; 
             // TCanSnow[hh] = U_warm / (CRHM_constants::cw * rain_load[hh]); // temperature of snow intercepted in the canopy after freezing liquid water, this will be used as the snow temp initilization in PSPnew
              // dUdt = dUdt + LH_FUS(FREEZE) * Snow_load[hh] / dt; // internal energy change to the snowpack due to melt, subtracting energy here as energy is required to melt snow
              Snow_load[hh] = 0; // empty the canopy snow store
            }
          }

          // Final part of CLASS phase change to update the heat capacity of h2o in the canopy
          Cp_h2o[hh] = (CRHM_constants::cw * rain_load[hh]) + (CRHM_constants::ci * Snow_load[hh]); // volumetric heat capacity of frozen and liquid h2o intercepted in the canopy (j m-2 K-1). This is different from CLASS who incorporates the vegetation elements here too but since PSPnew treats veg temp as different we do not have the same here.
          break;
        } // Meltwater Switch case [1]


        } // Meltwater Switch 

        // Mass Unloading Section
        // Enters different parameterisations for mass unloading of canopy snow based on switch.
        // =============================================================================

        switch (MassUnloadingSwitch[hh])
        {
        case 0:
        { // This is the mass unloading portion of the latest iteration of the Hedstrom & Pomeroy 1998 unloading with modifications by Ellis et al. (2010) and Floyd (2012). Generally used with MeltwaterSwitch == 0.
          // calculate 'ice-bulb' temperature of intercepted snow:
          IceBulbT = hru_t[hh] - (Vi * PBSM_constants::LATH / CRHM_constants::ci);
          const double U = -1 * log(0.678) / (24 * 7 * Global::Freq / 24); // weekly dimensionless unloading coefficient -> to CRHM time interval // 21Mar2022 correction: invert the term 24/Global::Freq, use unloading rate coefficient U = -log(c)/t for snow unloading determined by inverse function of c = e^(-Ut) = 0.678 based on Eq. 14 in Hedstrom and Pomeroy (1998)
          double Six_Hour_Divisor = Global::Freq / 4.0;                    // Unload over 6 hours

          // determine whether canopy snow is unloaded as meltwater or mass clumps:
          if (IceBulbT >= unload_t_water[hh])
          {
            drip_Cpy[hh] = Snow_load[hh] / Six_Hour_Divisor;
            SUnload_H2O[hh] = drip_Cpy[hh];
            Snow_load[hh] -= SUnload_H2O[hh];
            cum_SUnload_H2O[hh] += SUnload_H2O[hh];
          }
          else if (IceBulbT >= unload_t[hh])
          {
            SUnload[hh] = Snow_load[hh] / Six_Hour_Divisor;
            Snow_load[hh] -= SUnload[hh];
            cum_SUnload[hh] += SUnload[hh];
          }
          else if (IceBulbT < unload_t[hh])
          {                                  // has to be at least one interval. Trip on half step
            SUnload[hh] = Snow_load[hh] * U; // the dimensionless unloading coefficient already /interval, 21Mar2022 correction: use unloading rate coefficient U
            if (SUnload[hh] > Snow_load[hh])
            {
              SUnload[hh] = Snow_load[hh];
              Snow_load[hh] = 0.0;
            }
            else
              Snow_load[hh] -= SUnload[hh];

            cum_SUnload[hh] += SUnload[hh];
          }
          break;
        } // case 0

        case 1:
        { // This is the updated mass snow unloading parameterisations from Cebulski & Pomeroy to unload based on wind
          
          // check maximum canopy snow load
          if (Snow_load[hh] > Lmax[hh])
          {
            SUnload[hh] = Snow_load[hh] - Lmax[hh];
          }

          // melt induced mass unloading of solid snow based on ratio relative to canopy snowmelt similar method from Andreadis et al., (2009) based on Storck's measurements
          SUnloadMelt[hh] = canopy_snowmelt[hh] * melt_drip_ratio[hh];

          // mechanical wind induced unloading
          const double a_u = 2.418377e-06;      // Cebulski & Pomeroy coef from exponential function of unloading as function of wind speed, air temperature and canopy load when air temp < -6 C.
          const double b_u = 2.649564e-01;      // Cebulski & Pomeroy coef from exponential function of unloading as function of wind speed, air temperature and canopy load when air temp < -6 C.
          const double c_u = 5.367029e-02;      // Cebulski & Pomeroy coef from exponential function of unloading as function of wind speed, air temperature and canopy load when air temp < -6 C.
          double fu = 0.0;

           switch (CanopyWindSwitch[hh])
          {
            case 0:
            {  // original using Cionco wind model for dense canopies
              // wind speed for wind induced unloading at 1/2 canopy height 
              if ((Ht[hh] - (2.0 / 3.0) * Zwind[hh]) > 0.0){
                u_FHt[hh] = hru_u[hh] * log((Ht[hh] - (2.0 / 3.0) * Zwind[hh]) / 0.123 * Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0 * Zwind[hh]) / 0.123 * Zwind[hh]);
                double A = 2.4338 + 3.45753 * exp(-u_FHt[hh]);                       /* Modified Cionco wind model */
                u_mid = u_FHt[hh] * exp(A * ((Ht[hh]/2) / (Ht[hh])-1.0)); /* calculates canopy windspd  */
              } else {
                u_mid = 0.0;
              }
              break;
            } // case 0

            case 1:
            { // Canopy wind profile developed at Fortress sparse canopy
              double d0 = 0.5791121; // displacement height observed at sparse forest around Fortress Forest Tower
              double z0m = 0.4995565; // roughness length observed at above site

              // wind speed for wind induced unloading at 1/2 canopy height 
              if ((Ht[hh]/2 - d0) > z0m){
                double Ustar = hru_u[hh]*PBSM_constants::KARMAN/(log((Zwind[hh]-d0)/z0m));
                u_mid = Ustar/PBSM_constants::KARMAN * log((Ht[hh]/2 - d0)/z0m);
              } else {
                u_mid = 0.0;
              }

              break;
            } // case 1
          } // end of switch CanopyWind

          if(u_mid >= u_mid_th[hh]){
            fu = u_mid * a_u * exp(b_u * u_mid) * exp(-c_u * (hru_t[hh] + 20.0)); // unloading rate due to wind (s-1)
          } else {
            fu = 0.0; // less than wind induced unloading threshold so set equal to 0.
          }

          double dt = Global::Interval * 24 * 60 * 60;       // converts the interval which is a time period (i.e., time/cycles, 1 day/# obs) to timestep in seconds.

          // ablation via temperature, wind, and duration based unloading
          // SUnload[hh] = Snow_load[hh] * (fT + fu + ft) * dt; // ODE solution: calculate solid snow unloading over the time interval

          // analytical solution which is more exact over longer time intervals, following from Cebulski & Pomeroy derivation of the HP98 unloading parameterisation
          SUnloadWind[hh] = Snow_load[hh] * (1-exp(-fu * dt)); // analytical solution for ODE equation 30 in Cebulski & Pomeroy 2025 Wires WATER Review
          SUnload[hh] += SUnloadWind[hh]; 
          SUnload[hh] += SUnloadMelt[hh];

          if (SUnload[hh] > Snow_load[hh])
          {
            SUnload[hh] = Snow_load[hh];
            Snow_load[hh] = 0.0;
          }
          else
          {
            Snow_load[hh] -= SUnload[hh];
          }

          cum_SUnload[hh] += SUnload[hh];
          break;          

        } // case 1

        case 2:
        { // This is the mass snow unloading parameterisation from Andreadis et al., 2009 based on the snowmelt rate. No wind induced unloading.
          
          // check maximum canopy snow load
          if (Snow_load[hh] > Lmax[hh])
          {
            SUnload[hh] = Snow_load[hh] - Lmax[hh];
          }

          double Lres = 5.0; // threshold above which melt unloading starts to occur.

          if (Snow_load[hh] > Lres)
          {
            SUnloadMelt[hh] = canopy_snowmelt[hh] * melt_drip_ratio[hh];
          } else {
            SUnloadMelt[hh] = 0.0; // snow load is below threshold and can only melt or sublimate
          }

          SUnload[hh] += SUnloadMelt[hh];

          if (SUnload[hh] > Snow_load[hh])
          {
            SUnload[hh] = Snow_load[hh];
            Snow_load[hh] = 0.0;
          }
          else
          {
            Snow_load[hh] -= SUnload[hh];
          }

          cum_SUnload[hh] += SUnload[hh];
          break;          

        } // case 2

        case 3:
        { // This is the mass snow unloading parameterisation from Roesch et al., 2001 based on a temperature and wind speed function.
          
          // check maximum canopy snow load
          if (Snow_load[hh] > Lmax[hh])
          {
            SUnload[hh] = Snow_load[hh] - Lmax[hh];
          }

          // Mass unloading of canopy snow due to melt

          const double Tm = 270.15; // threshold in Kelvin below which temp unloading is equal to 0
          const double C1 = 1.87e5; // constant provided in Roesch et al., 2001
          double fT = 0.0; // unloading rate per second.

          if ((hru_t[hh] + CRHM_constants::Tm) < Tm) // Follows equation 31 in Cebulski & Pomeroy 2025 Wires WATER Review.
          {
            fT = 0.0;
          } else {
            fT = ((hru_t[hh] + CRHM_constants::Tm) - Tm)/C1;
          }

          double dt = Global::Interval * 24 * 60 * 60;       // converts the interval which is a time period (i.e., time/cycles, 1 day/# obs) to timestep in seconds.

          SUnloadMelt[hh] = Snow_load[hh] * (1-exp(-(fT) * dt)); // analytical solution for ODE equation 30 in Cebulski & Pomeroy 2025 Wires WATER Review

          // Mass unloading of canopy snow due to mechanical removal from wind at canopy top
          const double C2 = 1.56e5; // wind unloading constant from Roesch et al., 2001
          double fu = 0.0;

          if(u_FHt[hh] < u_mid_th[hh]){
            fu = 0.0; // unloading rate due to wind (s-1)
          } else {
            fu = u_FHt[hh]/C2; 
          }

          SUnloadWind[hh] = Snow_load[hh] * (1-exp(-(fu) * dt)); // analytical solution for ODE equation 30 in Cebulski & Pomeroy 2025 Wires WATER Review

          // Unload canopy snow
          SUnload[hh] += SUnloadWind[hh]; 
          SUnload[hh] += SUnloadMelt[hh];

          if (SUnload[hh] > Snow_load[hh])
          {
            SUnload[hh] = Snow_load[hh];
            Snow_load[hh] = 0.0;
          }
          else
          {
            Snow_load[hh] -= SUnload[hh];
          }

          cum_SUnload[hh] += SUnload[hh];
          break;        

        } // case 3
        } // MassUnloadingSwitch

        // calculate total sub-canopy snow:

        net_snow[hh] = direct_snow[hh] + SUnload[hh];
        break;
      } // case canopy
    case 1: // clearing
    case 2: // gap
      net_snow[hh] = hru_snow[hh];
      net_rain[hh] = hru_rain[hh];
      break;
    } // switch

    // Canopy Liquid Water Routine

    double smax, Q; // cannot be in switch structure

    switch (CanopyClearing[hh])
    {

    case 0: // canopy

      smax = Cc[hh] * LAI[hh] * 0.2;

      //  Forest rain interception and evaporation model
      // 'sparse' Rutter interception model (i.e. Valente 1997):

      // calculate direct throughfall and drip:

      if (hru_rain[hh] > 0.0 || rain_load[hh] > 0.0){

        direct_rain[hh] = hru_rain[hh] * (1 - Cc[hh]);

        // calculate rain accumulation on canopy before evap loss:

        if (rain_load[hh] + hru_rain[hh] * Cc[hh] > smax){
          drip_Cpy[hh] += (rain_load[hh] + hru_rain[hh] * Cc[hh] - smax);
          rain_load[hh] = smax;
        }
        else {
          rain_load[hh] += hru_rain[hh] * Cc[hh];
        }


      } // if hru_rain[hh] > 0.0

      // calculate 'actual evap' of water from canopy and canopy storage after evaporation::

      if (rain_load[hh] > 0.0)
      {
        if (inhibit_evap[hh] == 0)
        { // use Granger when no snowcover
          if (rain_load[hh] >= hru_evap[hh] * Cc[hh])
          {                                         // (evaporation in mm)
            intcp_evap[hh] = hru_evap[hh] * Cc[hh]; //
            rain_load[hh] -= hru_evap[hh] * Cc[hh];
          }
          else
          {
            intcp_evap[hh] = rain_load[hh];
            rain_load[hh] = 0.0;
          }
        }
        else
        {                                                            // use Priestley-Taylor when snowcover
          Q = Qsi_ * 86400 / Global::Freq / 1e6 / lambda(hru_t[hh]); // convert w/m2 to mm/m2/int

          if (Qsi_ > 0.0)
            Pevap[hh] = 1.26 * delta(hru_t[hh]) * Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
          else
            Pevap[hh] = 0.0;

          if (rain_load[hh] >= Pevap[hh] * Cc[hh])
          {                                      // (evaporation in mm)
            intcp_evap[hh] = Pevap[hh] * Cc[hh]; // check
            rain_load[hh] -= Pevap[hh] * Cc[hh];
          }
          else
          {
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
    default: // clearing and gap
      break;
    } // switch

    net_p[hh] = net_rain[hh] + net_snow[hh];
    cum_net_rain[hh] += net_rain[hh];
    cum_net_snow[hh] += net_snow[hh];

    // set assimilate observed snow load for begining of select events
    if(obs_snow_load[hh] < 9999){
      Snow_load[hh] = obs_snow_load[hh];
      SUnload[hh] = 0.0;
      canopy_snowmelt[hh] = 0.0;
      Subl_Cpy[hh] = 0.0;
    }
  } // end for
}

void ClassCRHMCanopyVectorBased::finish(bool good)
{
  for (hh = 0; chkStruct(); ++hh)
  {
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
    return (2504.0 * exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
  else
    return (3549.0 * exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

double ClassCRHMCanopyVectorBased::lambda(double t) // Latent heat of vaporization (mJ/(kg DEGREE_CELSIUS))
{
  return (2.501 - 0.002361 * t);
}

double ClassCRHMCanopyVectorBased::gamma(double Pa, double t) // Psychrometric constant (kPa/DEGREE_CELSIUS)
{
  return (0.00163 * Pa / lambda(t)); // lambda (mJ/(kg DEGREE_CELSIUS))
}

double ClassCRHMCanopyVectorBased::RHOa(double t, double ea, double Pa) // atmospheric density (kg/m^3)
{
  const double R = 2870;
  return (1E4 * Pa / (R * (273.15 + t)) * (1.0 - 0.379 * (ea / Pa))); //
}
