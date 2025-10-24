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

  Description = "'Calculates initial snow interception after Cebulski & Pomeroy (2025, Hyrological Proc.) canopy snow ablation is handled by the CanopySnowBalance module. Assumptions are for this to be applied on a forested HRU without significant clear cuts/large gaps in the forest with width many times the canopy height. This module also does some radiation calcs for consistency with the CanopyClearingGap module which this one replaces.' \
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

  // get variables:

  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);

  declgetvar("*", "hru_u", "(m/s)", &hru_u);

  declgetvar("*", "hru_rh", "()", &hru_rh);

  declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

  declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

  declgetvar("*", "SolAng", "(r)", &SolAng);

  declgetvar("*", "cosxs", "(r)", &cosxs);

  declgetvar("*", "cosxsflat", "(r)", &cosxsflat);

  declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);

  declgetvar("*", "Albedo", "()", &Albedo);

  declgetvar("*", "QdflatE", "(W/m^2)", &QdflatE);

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

  decldiag("Tauc", TDim::NHRU, "short-wave transmissity", "", &Tauc);

  decllocal("Pa", TDim::NHRU, "Average surface pressure", "(kPa)", &Pa);

  declvar("ra", TDim::NHRU, "resistance", "(s/m)", &ra);

  declvar("throughfall_rain", TDim::NHRU, "throughfall of rain through canopy (not in contact with canopy).", "(mm/int)", &throughfall_rain);

  declvar("throughfall_snow", TDim::NHRU, "throughfall of snow not in contact with the canopy", "(mm/int)", &throughfall_snow);

  declvar("intercepted_snow", TDim::NHRU, "initial interception of snow before ablation kicks in.", "(mm/int)", &intercepted_snow);

  declvar("intercepted_rain", TDim::NHRU, "initial interception of rain before ablation kicks in.", "(mm/int)", &intercepted_rain);

  decldiag("u_FHt", TDim::NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

  decldiag("u_1_third_Ht", TDim::NHRU, "wind speed at one-third forest height (z = 1/3*Ht) for the Cebulski & Pomeroy vector based param.", "(m/s)", &u_1_third_Ht);

  declvar("Clca", TDim::NHRU, "Leaf contact area adjusted for hydrometeor trajectory angle.", "()", &Clca);

  declvar("LAI_", TDim::NHRU, "Leaf area index adjusted for snow cover", "()", &LAI_);
  
  // parameters:

  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("Surrounding_Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "surrounding canopy height", "(m)", &Surrounding_Ht);

  declparam("Gap_diameter", TDim::NHRU, "[100]", "10", "1000", "representative gap diameter", "(m)", &Gap_diameter);

  declparam("Ht", TDim::NHRU, "[20.0]", "0.001", "100.0", "forest/vegetation height", "(m)", &Ht);

  declparam("Zref", TDim::NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

  declparam("Zwind", TDim::NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

  declparam("Z0snow", TDim::NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

  declparam("Cc", TDim::NHRU, "[1]", "0", "1", "canopy coverage, (1-sky view fraction)", "()", &Cc);

  declparam("LAI", TDim::NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

  declparam("alpha", TDim::NHRU, "[0.836]", "0.0", "1.0", "$alpha$ is an efficiency constant which determines the fraction of snowflakes that contact the $C_p$ elements and are stored in the canopy (i.e., intercepted) before canopy snow unloading or ablation processes begin. Default is based on Cebulski & Pomeroy plot scale observations at Fortress Mountain PWL and Forest Tower plots.", "()", &alpha);

  declparam("Zvent", TDim::NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

  declparam("CanopyClearing", TDim::NHRU, "[0]", "0", "2", "canopy - 0/clearing - 1/gap - 2", "()", &CanopyClearing);

  declparam("CanopyWindSwitchIP", TDim::NHRU, "[0]", "0", "1", "Canopy wind model to use at height Zcan, 0 - for Cionco, 1 - for Prandtl-von Kármán log-linear relationship", "()", &CanopyWindSwitchIP);

  decldiagparam("Alpha_c", TDim::NHRU, "[0.1]", "0.05", "0.2", "canopy albedo, used for longwave-radiation enhancement estimation", "()", &Alpha_c);

  decldiagparam("B_canopy", TDim::NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter for longwave-radiation. Suggestions are Colorado - 0.023 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopyVectorBased::init(void)
{

  nhru = getdim(TDim::NHRU); // transfers current # of HRU's to module

  for (hh = 0; hh < nhru; ++hh)
  {

    Pa[hh] = 101.3f * pow((293.0f - 0.0065f * hru_elev[hh]) / 293.0f, 5.26f); // kPa

    if (Ht[hh] > Zwind[hh])
    {
      CRHMException TExcept(string("'" + Name + " (CanopyVectorBased)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), TExcept::WARNING);
      LogError(TExcept);
    }
  }
}

void ClassCRHMCanopyVectorBased::run(void)
{ 
  for (hh = 0; chkStruct(); ++hh)
  {
    throughfall_rain[hh] = 0.0;
    throughfall_snow[hh] = 0.0;

    intercepted_rain[hh] = 0.0;       
    intercepted_snow[hh] = 0.0;  

    choose_solar_data(); // decide what solar data to use based on module variation defined in prj file
    compute_canopy_temp(); // compute canopy temperature as input for surface snow energy balance

    adjust_lai_for_snow_height(Ht[hh]);
    compute_canopy_long_short_rads(); // compute canopy long and short wave radiation components sent to canopy snow ebal and surface snowbal modules

    //==============================================================================
    // coupled forest snow interception routine:
    // after Cebulski & Pomeroy 2025:

    if (hru_snow[hh] > 0.0)
    {                            // calculate increase in Snow_load and throughfall_snow if we are in canopy (i.e., Cc > 0)
      const double v_snow = 0.8; // terminal fall velocity of snowfall taken from Isyumov, 1971
      Clca[hh] = 0.0;              // leaf contact area (Clca) based on trajectory angle
      double IP = 0.0;             // interception efficiency (IP)

      if (hru_u[hh] > 0.0 && Cc[hh] < 1.0 && Cc[hh] > 0.0)
      { // increase leaf contact area (Clca) based on wind speed and canopy coverage (Cc)

        get_wind_for_leaf_contact_calc();
        compute_leaf_contact_area(v_snow);
        
      } else { // do not adjust snow-leaf contact area for wind effects
        Clca[hh] = Cc[hh]; // use leaf contact area from nadir i.e., Clca == 1 for Cc == 1 and Clca == 0 when Cc == 0
      }
        
      IP = Clca[hh] * alpha[hh]; // interception efficiency (IP)
      intercepted_snow[hh] = IP * hru_snow[hh];    // change in canopy snow load

      // calculate canopy snow throughfall before unloading:

      throughfall_snow[hh] = (1.0 - IP) * hru_snow[hh];

      // net snow / rain is computed in can snobal after ablation of intercepted snow.
    } // end snow routine

    if(hru_rain[hh] > 0){
      // Canopy Liquid Water Routine
      throughfall_rain[hh] = hru_rain[hh] * (1.0 - Cc[hh]);
      intercepted_rain[hh] = hru_rain[hh] * Cc[hh];
    }

  } // end for
}

// helper functions

// this function chooses which solar data to use based on the module variation defined in the prj file
void ClassCRHMCanopyVectorBased::choose_solar_data(void)
{
    switch ((int)variation)
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
        default:
            Qsi_ = 0.0;
            Qli_ = 0.0;
            break;
    }
}

// this function computes canopy temperature based on air temperature and radiation balance used in the Snobal module
void ClassCRHMCanopyVectorBased::compute_canopy_temp(void)
{
    // Canopy temperature is approximated by the air temperature
    double T1 = hru_t[hh] + CRHM_constants::Tm; // deg C -> K

    double rho = Pa[hh] * 1000 / (CRHM_constants::Rgas * T1); // air density

    double U1 = hru_u[hh]; // wind speed (m/s)
    ra[hh] = (log(Zref[hh] / Z0snow[hh]) * log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

    double deltaX = 0.622 * CRHM_constants::Ls * Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas * sqr(T1));

    double q = (hru_rh[hh] / 100) * Common::Qs(Pa[hh], T1); // specific humidity

    Ts[hh] = T1 + (CRHM_constants::emiss * (Qli_ - CRHM_constants::sbc * pow(T1, 4.0)) 
                 + CRHM_constants::Ls * (q - Common::Qs(Pa[hh], T1)) * rho / ra[hh])
                 / (4 * CRHM_constants::emiss * CRHM_constants::sbc * pow(T1, 3.0) 
                 + (CRHM_constants::Cp + CRHM_constants::Ls * deltaX) * rho / ra[hh]);

    Ts[hh] -= CRHM_constants::Tm; // back to deg C

    // Apply boundary conditions
    if (Ts[hh] > 0.0 || SWE[hh] <= 0.0)
        Ts[hh] = 0.0;
}

// this function adjusts the effective LAI based on snow height as the bottom of the canopy may be buried in snow
void ClassCRHMCanopyVectorBased::adjust_lai_for_snow_height(double Ht)
{
    // Compute canopy exposure above snow
    double exposure = Ht - Common::DepthofSnow(SWE[hh]); // Ht in meters, SWE in mm
    if (exposure < 0.0)
        exposure = 0.0;

    // Update effective LAI
    LAI_[hh] = LAI[hh] * exposure / Ht;
}

// this function computes canopy longwave and shortwave radiation components sent to canopy snow ebal and surface snowbal modules
void ClassCRHMCanopyVectorBased::compute_canopy_long_short_rads(void)
{
    double T1 = hru_t[hh] + CRHM_constants::Tm; // deg C -> K
    double Vf = 1.0 - Cc[hh]; // changed from approx of LAI to direct calculation from params

    double Vf_ = Vf + (1.0 - Vf) * sin((Ht[hh] - (Ht[hh] - Common::DepthofSnow(SWE[hh]))) / Ht[hh] * M_PI_2);

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
    }

    double Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh])); // Eq. 6 from Pomeroy 2009

    // incoming longwave to the surface 
    Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_) * CRHM_constants::emiss_c * CRHM_constants::sbc * pow(T1, 4.0f) + B_canopy[hh] * Kstar_H; // looks like modification of Eq. 10 from Pomeroy 2009

    Qlisn_Var[hh] = Qlisn[hh]; // goes to snobal module

    // incoming shortwave radiation to the surface
    Qsisn[hh] = Qsi_ * Tauc[hh];

    Qsisn_Var[hh] = Qsisn[hh];

    // incoming longwave to the canopy mid point

    // Qlw_veg_Var[hh] = Qli_ * (1.0 - (Cc[hh]/2)); // canopy snow is partially exposed to atmosphere so reduce based on view factor

    // incoming shortwave radiation to canopy midpoint

    // Qsw_veg_Var[hh] = Qsi_ * Tauc_50; // for PSP like solar to canopy midpoint

    Qlosn[hh] = CRHM_constants::emiss * CRHM_constants::sbc * pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

    Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

    Qnsn_Var[hh] = Qnsn[hh];
}

// this function computes wind speed, variations are defined in the prj file using the CanopyWindSwitchIP parameter
void ClassCRHMCanopyVectorBased::get_wind_for_leaf_contact_calc(void)
{
    double Ht_1_third = Ht[hh] * (1.0 / 3.0);
                
    // wind speed used for vector based initial snow interception
    switch ((int)CanopyWindSwitchIP[hh])
    {
      case 0:
      {  // increase wind speed to canopy top then bring back down using using Cionco wind model for dense canopies, use this one if wind speed is below/within canopy
        adst_wind_cpy_top(Ht[hh], hru_u[hh], Zwind[hh], u_FHt[hh]);
        cionco_canopy_wind_spd(Ht[hh], u_FHt[hh], Ht_1_third, u_1_third_Ht[hh]);
        break;
      } // end case 0

      case 1:
      { // use if forcing wind speed is above/at canopy top
        cionco_canopy_wind_spd(Ht[hh], hru_u[hh], Ht_1_third, u_1_third_Ht[hh]);
        break;
      } // end case 1

      case 2:
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
      } // end case 2
    } // end of switch CanopyWind
}

// this function computes leaf contact area based on hydrometeor trajectory angle as in Cebulski & Pomeroy 2025 (hp)
void ClassCRHMCanopyVectorBased::compute_leaf_contact_area(double v_snow)
{
    if (u_1_third_Ht[hh] > 0.0)
    {
        double snow_traj_angle = atan(u_1_third_Ht[hh] / v_snow); // trajectory angle in radians
        double b_lca = 0.91; // empirical coefficient
        double f_theta = b_lca * pow(sin(snow_traj_angle), 2.0);

        double Cp_inc = (1.0 - Cc[hh]) * f_theta; // fractional increase in leaf contact area
        Clca[hh] = Cc[hh] + Cp_inc;
    }
    else
    {
        Clca[hh] = Cc[hh]; // nadir contact area
    }
}

void ClassCRHMCanopyVectorBased::finish(bool good)
{
  for (hh = 0; chkStruct(); ++hh)
  {
    LogDebug(" ");
  }
}