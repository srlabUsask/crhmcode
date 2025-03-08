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

#include "ClassCanSnobalCRHM.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassCanSnobalCRHM* ClassCanSnobalCRHM::klone(string name) const{
  return new ClassCanSnobalCRHM(name);
}

void ClassCanSnobalCRHM::decl(void) {

    Description = "'A model using the energy balance to calculate the canopy snow mass and energy balance following the surface snowpack routine (Marks, et. al (1997)). Standard CRHM module.' \
                 'use Qsi (W/m^2) and Qli (W/m^2) observations,' \
                 'use variables Qsisn_Var (W/m^2) and Qlisn_Var (W/m^2) from module CanopyClearing.' \
                 'use observation Qsi (W/m^2) and QliVt_Var (W/m^2) from module longVt.' \
                 'use variables QsiS_Var (W/m^2) from Annandale and QliVt_Var (W/m^2) from module longVt.'";

    declstatvar("isothermal", TDim::NHRU, "melting: 0/1", "()", &isothermal);
    declstatvar("vegsnowcover", TDim::NHRU, "snow on veg at start of current timestep: 0/1", "()", &vegsnowcover);
    declstatvar("vegliquidcover", TDim::NHRU, "liquid on veg at start of current timestep: 0/1", "()", &vegsnowcover);

    declvar("Qn_veg", TDim::NHRU, "net allwave radiation wrt the canopy", "(W/m^2)", &Qn_veg);
    declvar("Qh_veg", TDim::NHRU, "sensible heat xfr wrt the canopy", "(W/m^2)", &Qh_veg);
    declvar("Ql_veg", TDim::NHRU, "latent heat xfr wrt the canopy", "(W/m^2)", &Ql_veg);
    declvar("Qh_ice_sphere", TDim::NHRU, "sensible heat flux + to ice sphere surface", "(J/s)", &Qh_ice_sphere);
    declvar("Qe_ice_sphere", TDim::NHRU, "latent heat flux + to ice sphere surface", "(J/s)", &Qe_ice_sphere);
    declvar("Qp", TDim::NHRU, "advected heat from precip wrt the canopy", "(W/m^2)", &Qp);
    declvar("delta_Q_veg", TDim::NHRU, "change in snowcover's energy wrt the canopy", "(W/m^2)", &delta_Q_veg);

    declstatvar("cc_s_veg", TDim::NHRU, "snowcover's cold content", "(J/m^2)", &cc_s_veg);
    declstatvar("liq_h2o_veg", TDim::NHRU, "canopy liquid h2o load as specific mass", "(kg/m^2)", &liq_h2o_veg);
    declstatvar("snow_h2o_veg", TDim::NHRU, "canopy snow load as specific mass", "(kg/m^2)", &snow_h2o_veg);

    decllocal("delsub_veg", TDim::NHRU, "mass of subl/evap from canopy snow/liquid (+to surface)", "(kg/m^2*int)", &delsub_veg);
    decllocal("qsub_veg", TDim::NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &qsub_veg);
    decllocal("delmelt_veg", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &delmelt_veg);
    declvar("deldrip_veg", TDim::NHRU, "predicted specific runoff", "(kg/m^2)", &deldrip_veg);

    declvar("delsub_veg_int", TDim::NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &delsub_veg_int);
    declvar("delmelt_veg_int", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &delmelt_veg_int);
    declvar("delunld_int", TDim::NHRU, "specific mass of canopy snow unloaded to subcanopy", "(kg/m^2*int)", &delunld_int);
    declvar("delunld", TDim::NHRU, "canopy snow unloading rate", "(kg/m^2*int)", &delunld);
    declvar("delunld_wind", TDim::NHRU, "solid snow unloading from the canopy induced by wind", "(kg/m^2*int)", &delunld_wind);
    declvar("delunld_melt", TDim::NHRU, "canopy snow unloading rate due to melting", "(kg/m^2*int)", &delunld_melt);
    declvar("delunld_subl", TDim::NHRU, "canopy snow unloading due to sublimation", "(kg/m^2*int)", &delunld_subl);
    declvar("delL", TDim::NHRU, "interval change in SWE", "(kg/m^2*int)", &delL);
    declvar("delmelt_veg_day", TDim::NHRU, "daily snow melt", "(mm/d)", &delmelt_veg_day);
    decllocal("cmlmelt_veg_day", TDim::NHRU, "daily snow melt accumulator", "(mm/d)", &cmlmelt_veg_day);
    declvar("cmlmelt_veg", TDim::NHRU, "cumulative melt", "(mm)", &cmlmelt_veg);

    declstatvar("z_veg_s", TDim::NHRU, "total snowcover thickness", "(m)", &z_veg_s);

    declstatvar("rho_veg", TDim::NHRU, "average snowcover density", "(kg/m^3)", &rho_veg);

    declstatvar("m_s_veg", TDim::NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s_veg);

    declstatvar("T_s_veg", TDim::NHRU, "average snowcover temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s_veg);

    declstatvar("h2o_sat_veg", TDim::NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat_veg);
    declvar("h2o_vol_veg", TDim::NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol_veg);

    declvar("h2o_sat_veg_snow", TDim::NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_veg_snow);

    declvar("precip_now_veg", TDim::NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now_veg);
    declvar("T_rain_veg", TDim::NHRU, "rain's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_rain_veg);
    declvar("T_sf", TDim::NHRU, "snowfall's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_sf);

    decllocal("S_n_L", TDim::NHRU, "net solar radiation", "(W/m^2)", &S_n);
    decllocal("I_lw_L", TDim::NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
    decllocal("T_a_L", TDim::NHRU, "air temp", "(" + string(DEGREE_CELSIUS) + ")", &T_a);
    decllocal("e_a_L", TDim::NHRU, "vapor pressure", "(Pa)", &e_a);
    decllocal("u_L", TDim::NHRU, "wind speed", "(m/s)", &u);
    decllocal("T_g_L", TDim::NHRU, "soil temp at depth z_g", "(" + string(DEGREE_CELSIUS) + ")", &T_g);
    decllocal("F_g_L", TDim::NHRU, "soil flux at depth z_g", "(W/m^2)", &F_g);
    decllocal("I_LW_atm", TDim::NHRU, "Downwelling longwave from the atmoshpere", "(W/m^2)", &I_LW_atm);
    decllocal("I_LW_gnd", TDim::NHRU, "Upwelling longwave from the ground", "(W/m^2)", &I_LW_gnd);
    decllocal("I_LW_cpy_2_cpy", TDim::NHRU, "Longwave from the canopy reflected off the surface back to the canopy", "(W/m^2)", &I_LW_cpy_2_cpy);
    decllocal("I_LW_cpy", TDim::NHRU, "Incoming longwave radiation emitted from the canopy", "(W/m^2)", &I_LW_cpy);
    decllocal("O_LW_cpysnow", TDim::NHRU, "Outgoing longwave radiation emitted from the canopy snow", "(W/m^2)", &O_LW_cpysnow);
    decllocal("CanSnowFrac", TDim::NHRU, "Fraction of canopy covered by snow after Pomeroy 1998", "(-)", &CanSnowFrac);
    decllocal("niter_ice_sphere", TDim::NHRU, "N iterations for the ice sphere energy balance", "(-)", &niter_ice_sphere);
    decllocal("Tstep_ice_sphere", TDim::NHRU, "Temp increment the ice sphere energy balance", "(" + string(DEGREE_CELSIUS) + ")", &Tstep_ice_sphere);

    decllocal("albedo_now", TDim::NHRU, "Albedo of the canopy considering how much snow is on it", "(-)", &albedo_now);


    decllocal("m_precip_L", TDim::NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    declvar("rain_on_snow_veg", TDim::NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
    decllocal("m_snow_L", TDim::NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
    decllocal("rho_snow_L", TDim::NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
    decllocal("T_pp_L", TDim::NHRU, "precip temp", "(" + string(DEGREE_CELSIUS) + ")", &T_pp);

    decllocal("P_a", TDim::NHRU, "air pressure", "(Pa)", &P_a);

    decllocal("m_precip_cum", TDim::NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
    decllocal("m_rain_cum", TDim::NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
    decllocal("m_snow_cum", TDim::NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
    decllocal("E_s_cum", TDim::NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
    decllocal("melt_direct_cum", TDim::NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

    decllocal("stop_no_snow", TDim::NHRU, "snow flag", "()", &stop_no_snow);
    declparam("max_liq_veg", TDim::NHRU, "[0.0001]", "0.0001", "0.2", "max liquid h2o content as specific mass", "(kg/m^2)", &max_liq_veg);
    declparam("Albedo_vegsnow", TDim::NHRU, "[0.6]", "0.6", "0.9", "Albedo_vegsnow", "(-)", &Albedo_vegsnow);

    declgetparam("*", "z_g", "()", &z_g); // depth of soil temp meas (m)
    declgetparam("*", "z_u", "()", &z_u); // height of wind measurement (m)
    declgetparam("*", "z_T", "()", &z_T); // height of air temp & vapor pressure measurement(m)
    declgetparam("*", "hru_elev", "()", &hru_elev); // altitude (m)
    declgetparam("*", "basin_area", "()", &basin_area); // total basin area (km^2)
    declgetparam("*", "hru_area", "()", &hru_area); // hru area (km^2)
    declgetparam("*", "hru_rho_snow", "()", &rho_snow_X); // rho of falling snow (kg/m^3)
    declgetparam("*", "Cc", "()", &Cc); // canopy coverage, (1-sky view fraction)
    declgetparam("*", "Lmax", "()", &Lmax); // canopy coverage, (1-sky view fraction)
    declgetparam("*", "Ht", "()", &Ht); 
    declgetparam("*", "CanopyWindSwitch", "()", &CanopyWindSwitch); 
    declgetparam("*", "melt_drip_ratio", "()", &melt_drip_ratio); 
    declgetparam("*", "relative_hts", "()", &relative_hts); 

    declgetparam("*", "Alpha_c", "()", &Albedo_veg); // canopy albedo
    declgetvar("*", "Albedo", "()", &Albedo_surface);
    declgetvar("*", "Tauc", "(r)", &Tauc);

    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_a_X);
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_pp_X); // default precipitation temperature to air
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);
    declgetvar("*", "T_s_0", "(" + string(DEGREE_CELSIUS) + ")", &T_s_0); 
    declreadobs("obs_snow_load", TDim::NHRU, "Weighed tree canopy snow load", "(kg/m^2)", &obs_snow_load, HRU_OBS_misc);


    declgetvar("*", "intercepted_snow", "(kg/m^2)", &new_snow); // new snow intercepted in canopy before ablation processes have kicked in
    declgetvar("*", "intercepted_rain", "(kg/m^2)", &new_rain); // new snow intercepted in canopy before ablation processes have kicked in
    declgetvar("*", "hru_evap", "(kg/m^2)", &del_liq_evap); 


    variation_set = VARIATION_0 + VARIATION_2;

    declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

    variation_set = VARIATION_0;

    declreadobs("Qli", TDim::NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

    variation_set = VARIATION_1;

    declgetvar("*", "QsiS_Var", "(W/m^2)", &Qsw_in_veg); // downwelling SW to slope
    declgetvar("*", "QliVt_Var", "(W/m^2)", &Qlw_out_atm); // downwelling longwave radiation from the atmosphere, adjusted for terrain emission as well


    variation_set = VARIATION_ORG;
}

void ClassCanSnobalCRHM::init(void) {

  ClassCanSnobalBase::init();
  for (hh = 0; chkStruct(); ++hh) {
    delmelt_veg_day[hh] = 0.0;
  }
}

void ClassCanSnobalCRHM::run(void) { // executed every interval

  long nstep = getstep() % Global::Freq;

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(snow_h2o_veg[hh] <= 0)
        vegsnowcover[hh] = 0;
      else{
          vegsnowcover[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    switch (variation){
      case VARIATION_ORG:
        input_rec2[hh].S_n  = Qsi[hh];
        input_rec2[hh].I_lw = Qli[hh];
      break;
      case VARIATION_1: // default if no obs radiation available
        input_rec2[hh].S_n  = Qsw_in_veg[hh]; // after CLASSIC just take the incoming solar to slope which is multiplied by 1 - canopy albedo later on. Differs slightly from class which uses incoming SW to horizontal surface where this is the SW to slope 
        I_LW_atm[hh] = (CAN_EMISSIVITY + (1.0 - CAN_EMISSIVITY)*(1.0 - SNOW_EMISSIVITY)*CAN_EMISSIVITY)*Qlw_out_atm[hh]; //  ! downward atmospheric longwave radiation absorbed by the canopy (W m-2) from SUMMA

        // using veg temp instead of surface snowpack
        // if(T_s_0[hh] == MIN_SNOW_TEMP){
        //   I_LW_gnd[hh] = CAN_EMISSIVITY*(CRHM_constants::sbc * SNOW_EMISSIVITY * pow(T_a_X[hh] + FREEZE, 4.0f)); // subcanopy snow pack not initilized yet
        // } else {
        //   I_LW_gnd[hh] = CAN_EMISSIVITY*(CRHM_constants::sbc * SNOW_EMISSIVITY * pow(T_s_0[hh] + FREEZE, 4.0f)); 
        // }
 
        input_rec2[hh].I_lw = I_LW_atm[hh]; // TODO consider modifying to add pomeroy 2009 solar rad adjustment for additional lonwave emitted from the bare veg elements as well (i.e. + 1.0-CanSnowFrac*(B_canopy[hh]*Kstar_H)), not including outgoing LW from surfance snow as should be relatively similar to canopy.
      break;
      case VARIATION_2:
        input_rec2[hh].S_n  = Qsi[hh];
        input_rec2[hh].I_lw = Qlw_out_atm[hh];
      break;
    }

    input_rec2[hh].T_a  = T_a_X[hh] + FREEZE;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];

    // handles non throughfall precip
    m_precip[hh] = new_snow[hh] + new_rain[hh];
    m_rain[hh] = new_rain[hh];
    m_snow[hh] = new_snow[hh];

    m_precip_cum[hh] += m_precip[hh]; // change
    m_rain_cum[hh] += m_rain[hh];
    m_snow_cum[hh] += m_snow[hh];

    T_pp[hh]     = T_pp_X[hh] + FREEZE;

// clear interval values

    delmelt_veg_int[hh] = 0.0;
    delsub_veg_int[hh] = 0.0;
    delunld_int[hh] = 0.0;
    deldrip_veg[hh] = 0.0;

    long Step = getstep();
    if(getstep() > 1){ // Not first step

      if (m_precip[hh] > 0.0)
      {
        stop_no_snow[hh] = 0;
        precip_now_veg[hh] = true;
      }
      else
      {
        if (vegsnowcover[hh] == 0)
          stop_no_snow[hh] = 1;
        precip_now_veg[hh] = false;
      }

      do_data_tstep_veg(); // executes Snobal code

    }
    else if(m_precip[hh] > 0.0) {
         CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", TExcept::WARNING);
         LogError(TExcept);
    }

    Step = Step % Global::Freq;
    if(Step == 1)
       cmlmelt_veg_day[hh] = delmelt_veg_int[hh];
    else
       cmlmelt_veg_day[hh] += delmelt_veg_int[hh];

    if(Step == 0){
      delmelt_veg_day[hh] = cmlmelt_veg_day[hh];
      cmlmelt_veg_day[hh] = 0.0;
    }

    input_rec1[hh].S_n  = input_rec2[hh].S_n;
    input_rec1[hh].I_lw = input_rec2[hh].I_lw;
    input_rec1[hh].T_a  = input_rec2[hh].T_a;
    input_rec1[hh].e_a  = input_rec2[hh].e_a;
    input_rec1[hh].u    = input_rec2[hh].u;
    input_rec1[hh].T_g  = input_rec2[hh].T_g;
    input_rec1[hh].F_g  = input_rec2[hh].F_g;

    E_s_cum[hh] += delsub_veg_int[hh];
    delL[hh] += m_s_veg[hh];
    cmlmelt_veg[hh] += delmelt_veg_int[hh];
    melt_direct_cum[hh] += delmelt_veg_int[hh];

        // set assimilate observed snow load for begining of select events
    if(obs_snow_load[hh] < 9999){
      m_s_veg[hh] = obs_snow_load[hh];
      snow_h2o_veg[hh] = obs_snow_load[hh];
      liq_h2o_veg[hh] = 0.0; // could be incorrect for first timestep but will be small impact as all liq water assumed to drain on each timestep
      delmelt_veg_int[hh] = 0.0;
      delsub_veg_int[hh] = 0.0;
      delunld_int[hh] = 0.0;
      deldrip_veg[hh] = 0.0;
    }

  }
}

void ClassCanSnobalCRHM::finish(bool good) { // only required for local storage and final output

  ClassCanSnobalBase::finish(good);
}
