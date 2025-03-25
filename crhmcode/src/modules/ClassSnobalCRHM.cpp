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

#include "ClassSnobalCRHM.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassSnobalCRHM* ClassSnobalCRHM::klone(string name) const{
  return new ClassSnobalCRHM(name);
}

void ClassSnobalCRHM::decl(void) {

    Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Standard CRHM module.' \
                 'use Qsi (W/m^2) and Qli (W/m^2) observations,' \
                 'use variables Qsisn_Var (W/m^2) and Qlisn_Var (W/m^2) from module CanopyClearing.' \
                 'use observation Qsi (W/m^2) and QliVt_Var (W/m^2) from module longVt.' \
                 'use variables QsiS_Var (W/m^2) from Annandale and QliVt_Var (W/m^2) from module longVt.'";

    declstatvar("layer_count", TDim::NHRU, "number of layers in snowcover: 0, 1, or 2", "()", &layer_count);
    declstatvar("isothermal", TDim::NHRU, "melting: 0/1", "()", &isothermal);
    declstatvar("snowcover", TDim::NHRU, "snow on gnd at start of current timestep: 0/1", "()", &snowcover);

    declvar("R_n", TDim::NHRU, "net allwave radiation", "(W/m^2)", &R_n);
    declvar("H", TDim::NHRU, "sensible heat xfr", "(W/m^2)", &H);
    declvar("L_v_E", TDim::NHRU, "latent heat xfr", "(W/m^2)", &L_v_E);
    declvar("G", TDim::NHRU, "heat xfr by conduction & diffusion from soil to snowcover", "(W/m^2)", &G);
    declvar("M", TDim::NHRU, "advected heat from precip", "(W/m^2)", &M);
    declvar("delta_Q", TDim::NHRU, "change in snowcover's energy", "(W/m^2)", &delta_Q);
    declvar("G_0", TDim::NHRU, "heat xfr by conduction & diffusion from soil or lower layer to active layer", "(W/m^2)", &G_0);
    declvar("delta_Q_0", TDim::NHRU, "change in active layer's energy", "(W/m^2)", &delta_Q_0);

    declstatvar("cc_s_0", TDim::NHRU, "active layer cold content", "(J/m^2)", &cc_s_0);
    declstatvar("cc_s_l", TDim::NHRU, "lower layer cold content", "(J/m^2)", &cc_s_l);
    declstatvar("cc_s", TDim::NHRU, "snowcover's cold content", "(J/m^2)", &cc_s);
    declstatvar("h2o", TDim::NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o);

    decllocal("E_s", TDim::NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2)", &E_s);
    decllocal("E", TDim::NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &E);
    decllocal("E_s_0", TDim::NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0);
    decllocal("E_s_l", TDim::NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l);
    decllocal("melt", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &melt);
    declvar("ro_predict", TDim::NHRU, "predicted specific runoff", "(m/s)", &ro_predict);
    declvar("h2o_total", TDim::NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total);

    decldiag("E_s_int", TDim::NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &E_s_int);
    decldiag("E_int", TDim::NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &E_int);
    decldiag("E_s_0_int", TDim::NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0_int);
    decldiag("E_s_l_int", TDim::NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l_int);
    declvar("melt_direct_int", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &melt_direct_int);
    declvar("sum", TDim::NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
    declvar("SWE_change", TDim::NHRU, "interval change in SWE", "(mm)", &SWE_change);
    declvar("snowmelt_int", TDim::NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
    declvar("snowmeltD", TDim::NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
    decllocal("snowmeltD_acc", TDim::NHRU, "daily snow melt accumulator", "(mm/d)", &snowmeltD_acc);
    declvar("cumsnowmelt", TDim::NHRU, "cumulative melt", "(mm)", &cumsnowmelt);


    declstatvar("z_s_0", TDim::NHRU, "active layer depth", "(m)", &z_s_0);
    declstatvar("z_s_l", TDim::NHRU, "lower layer depth", "(m)", &z_s_l);
    declstatvar("z_s", TDim::NHRU, "total snowcover thickness", "(m)", &z_s);

    declstatvar("rho", TDim::NHRU, "average snowcover density", "(kg/m^3)", &rho);

    declstatvar("m_s_0", TDim::NHRU, "active layer specific mass", "(kg/m^2)", &m_s_0);
    declstatvar("m_s_l", TDim::NHRU, "lower layer specific mass", "(kg/m^2)", &m_s_l);
    declstatvar("SWE", TDim::NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s);

    declstatvar("T_s_0", TDim::NHRU, "active snow layer temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s_0);
    declstatvar("T_s_l", TDim::NHRU, "lower layer temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s_l);
    declstatvar("T_s", TDim::NHRU, "average snowcover temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s);

    declstatvar("h2o_sat", TDim::NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
    declvar("h2o_vol", TDim::NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol);
    declvar("h2o_max", TDim::NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max);

    declvar("z_snow", TDim::NHRU, "depth of snow in precip", "(m)", &z_snow);
    declvar("h2o_sat_snow", TDim::NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_snow);

    declvar("precip_now", TDim::NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now);
    declvar("T_rain", TDim::NHRU, "rain's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_rain);
    declvar("T_snow", TDim::NHRU, "snowfall's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_snow);

    decllocal("S_n_L", TDim::NHRU, "net solar radiation", "(W/m^2)", &S_n);
    decllocal("I_lw_L", TDim::NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
    decllocal("T_a_L", TDim::NHRU, "air temp", "(" + string(DEGREE_CELSIUS) + ")", &T_a);
    decllocal("e_a_L", TDim::NHRU, "vapor pressure", "(Pa)", &e_a);
    decllocal("u_L", TDim::NHRU, "wind speed", "(m/s)", &u);
    decllocal("T_g_L", TDim::NHRU, "soil temp at depth z_g", "(" + string(DEGREE_CELSIUS) + ")", &T_g);
    decllocal("F_g_L", TDim::NHRU, "soil flux at depth z_g", "(W/m^2)", &F_g);

    decllocal("m_precip_L", TDim::NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    declvar("rain_on_snow", TDim::NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
    decllocal("m_snow_L", TDim::NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
    decllocal("m_drift_L", TDim::NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_drift);
    decllocal("m_subl_L", TDim::NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
    decllocal("rho_snow_L", TDim::NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
    decllocal("T_pp_L", TDim::NHRU, "precip temp", "(" + string(DEGREE_CELSIUS) + ")", &T_pp);

    decllocal("P_a", TDim::NHRU, "air pressure", "(Pa)", &P_a);

    decllocal("m_precip_cum", TDim::NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
    decllocal("m_rain_cum", TDim::NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
    decllocal("m_snow_cum", TDim::NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
    decllocal("m_drift_cum", TDim::NHRU, "cumulative specific mass of total drifting snow", "(kg/m^2)", &m_drift_cum);
    decllocal("m_subl_cum", TDim::NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
    decllocal("E_s_cum", TDim::NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
    decllocal("melt_direct_cum", TDim::NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

    decllocal("stop_no_snow", TDim::NHRU, "snow flag", "()", &stop_no_snow);
    decllocal("snow_store", TDim::NHRU, "accumulates snow till significant", "()", &snow_store);

    decldiagparam("relative_hts", TDim::NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

    declparam("z_g", TDim::NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
    declparam("z_u", TDim::NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
    declparam("z_T", TDim::NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
    declparam("z_0", TDim::NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

    declparam("max_z_s_0", TDim::NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
    declparam("max_h2o_vol", TDim::NHRU, "[0.0001]", "0.0001", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

    declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
    declparam("hru_rho_snow", TDim::NHRU, "[100]", "50", "1000", "rho of falling snow", "(kg/m^3)", &rho_snow_X);
    declparam("hru_T_g", TDim::NHRU, "[-4]", "-50", "50", "ground temperature used when observation T_g not available", "(" + string(DEGREE_CELSIUS) + ")", &T_g_X);
    declparam("hru_F_g", TDim::NHRU, "[0]", "-50", "50", "ground flux used when observation F_g not available", "(W/m^2)", &F_g_X);
    declparam("T_g_or_G_flux", TDim::NHRU, "[0]", "0", "1", "0 - calculate ground flux from ground temperature, 1 - use ground flux value", "()", &T_g_or_G_flux);

    decldiagparam("rain_soil_snow", TDim::NHRU, "[0]", "0", "1", "0 - handle only snow (module Soil handles rain), 1 - handle snow and rain in this module (when SWE > 0.02mm).", "()", &rain_soil_snow);

    declparam("KT_sand", TDim::NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_a_X);
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_pp_X); // default precipitation temperature to air
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);

    declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
    declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
    declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
    declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
    declgetvar("*", "Albedo", "()", &Albedo);

    declputvar("*", "net_rain", "(kg/m^2)", &m_rain_X);

    declreadobs("T_g", TDim::NHRU, "ground temperature", "(" + string(DEGREE_CELSIUS) + ")", &T_g_Obs, HRU_OBS_misc, true);

    declreadobs("F_g", TDim::NHRU, "ground flux", "(W/m^2)", &F_g_Obs, HRU_OBS_misc, true);

    variation_set = VARIATION_0 + VARIATION_2;

    declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

    variation_set = VARIATION_0;

    declreadobs("Qli", TDim::NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

    variation_set = VARIATION_1;

    declgetvar("*", "Qsisn_Var", "(W/m^2)", &Qsisn_Var);

    declgetvar("*", "Qlisn_Var", "(W/m^2)", &Qlisn_Var);

    variation_set = VARIATION_2 + VARIATION_3;

    declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

    variation_set = VARIATION_3;

    declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

    variation_set = VARIATION_ORG;
}

void ClassSnobalCRHM::init(void) {

  ClassSnobalBase::init();
  if(!T_g_Obs){
    CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground temperature T_g observation not available using parameter hru_T_g.").c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  if(!F_g_Obs){
    CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground flux F_g observation not available using parameter hru_F_g.").c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  for (hh = 0; chkStruct(); ++hh) {
    snow_store[hh] = 0.0;
    snowmeltD[hh] = 0.0;
  }
}

void ClassSnobalCRHM::run(void) { // executed every interval

  long nstep = getstep() % Global::Freq;

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(m_s[hh] <= 0)
        layer_count[hh] = 0;
      else{
        if(z_s[hh] <= 0.0)
          rho[hh] = 0.0;
        else
          rho[hh] = m_s[hh]/z_s[hh];

        if(layer_count[hh] <= 0)
          layer_count[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    T_s[hh]    += CRHM_constants::Tm; // temperatures inside Snobal model are K
    T_s_0[hh]  += CRHM_constants::Tm;
    T_s_l[hh]  += CRHM_constants::Tm;

    T_snow[hh] += CRHM_constants::Tm;
    T_rain[hh] += CRHM_constants::Tm;

    SWE_change[hh] = -m_s[hh];

    switch (variation){
      case VARIATION_ORG:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = Qli[hh];
      break;
      case VARIATION_1: // this is the default
        input_rec2[hh].S_n  = Qsisn_Var[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = Qlisn_Var[hh];
      break;
      case VARIATION_2:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = QliVt_Var[hh];
      break;
      case VARIATION_3:
        input_rec2[hh].S_n  = QsiS_Var[hh]*(1.0 - Albedo[hh]);
        input_rec2[hh].I_lw = QliVt_Var[hh];
      break;
    }


    input_rec2[hh].T_a  = T_a_X[hh] + CRHM_constants::Tm;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];

    if(F_g_Obs)
      input_rec2[hh].F_g  = F_g_Obs[hh];
    else
      input_rec2[hh].F_g  = F_g_X[hh];

    if(T_g_Obs) // only convert degrees not fluxes
      input_rec2[hh].T_g  = T_g_Obs[hh] + CRHM_constants::Tm;
    else
      input_rec2[hh].T_g  = T_g_X[hh] + CRHM_constants::Tm;

    if(m_snow_X[hh] == 0){
      m_snow[hh] = 0.0;
    }      

    if(snowcover[hh]){
      m_snow[hh]  = m_snow_X[hh];
    }
    else {
      if(m_snow_X[hh] > 0.0){
        snow_store[hh] += m_snow_X[hh];
      } else {
          m_snow[hh] = 0.0;
      }
    }

    if((nstep == 1 && snow_store[hh] > 0.0) || snow_store[hh] > 1.0){
      m_snow[hh]  = snow_store[hh];
      snow_store[hh] = 0.0;
    }

    if(rain_soil_snow[hh] && snowcover[hh]){ // handle snow and rain over snow cover
      m_precip[hh] = m_precip_X[hh];
      m_rain[hh]   = m_rain_X[hh];
      m_rain_X[hh] = 0.0;
    }
    else{ // handle only snow. Infitration routine handles rain
      m_precip[hh] = m_snow_X[hh];
      m_rain[hh]   = 0.0;
    }

    m_drift[hh]  = m_drift_X[hh];
    m_subl[hh]  = m_subl_X[hh];
    rho_snow[hh] = rho_snow_X[hh];

    m_precip_cum[hh] += m_precip[hh]; // change
    m_rain_cum[hh] += m_rain[hh];
    m_snow_cum[hh] += m_snow[hh];
    m_drift_cum[hh] += m_drift[hh];
    m_subl_cum[hh] += m_subl[hh];

    if(m_snow[hh] > 0.0){
      if (rho_snow[hh] <= 0.0){
        CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TExcept::TERMINATE);
        LogError(TExcept);
      }
      z_snow[hh]   = m_snow[hh] / rho_snow[hh];
    }
    else
      z_snow[hh]   = 0.0;

    T_pp[hh]     = T_pp_X[hh] + CRHM_constants::Tm;

// clear interval values

    snowmelt_int[hh] = 0.0;
    melt_direct_int[hh] = 0.0;
    sum[hh] = 0.0;
    E_s_int[hh] = 0.0;
    E_int[hh] = 0.0;
    E_s_0_int[hh] = 0.0;
    E_s_l_int[hh] = 0.0;
    ro_predict[hh] = 0.0;

    long Step = getstep();
    if(getstep() > 1){ // Not first step

      if(m_precip[hh] > 0.0){
        stop_no_snow[hh] = 0;
        precip_now[hh]= true;
      }
      else{
        if(layer_count[hh] == 0)
          stop_no_snow[hh] = 1;
        precip_now[hh]= false;
      }

// process blowing snow event
      _drift();

      do_data_tstep(); // executes Snobal code

    }
    else if(m_precip[hh] > 0.0) {
         CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", TExcept::WARNING);
         LogError(TExcept);
    }

    Step = Step % Global::Freq;
    if(Step == 1)
       snowmeltD_acc[hh] = snowmelt_int[hh];
    else
       snowmeltD_acc[hh] += snowmelt_int[hh];

    if(Step == 0){
      snowmeltD[hh] = snowmeltD_acc[hh];
      snowmeltD_acc[hh] = 0.0;
    }

    input_rec1[hh].S_n  = input_rec2[hh].S_n;
    input_rec1[hh].I_lw = input_rec2[hh].I_lw;
    input_rec1[hh].T_a  = input_rec2[hh].T_a;
    input_rec1[hh].e_a  = input_rec2[hh].e_a;
    input_rec1[hh].u    = input_rec2[hh].u;
    input_rec1[hh].T_g  = input_rec2[hh].T_g;
    input_rec1[hh].F_g  = input_rec2[hh].F_g;

    E_s_cum[hh] += E_s_int[hh];
    sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
    SWE_change[hh] += m_s[hh];
    cumsnowmelt[hh] += snowmelt_int[hh];
    melt_direct_cum[hh] += melt_direct_int[hh];

    T_s[hh]   -= CRHM_constants::Tm; // temperatures outside Snobal model are DEGREE_CELCIUS
    T_s_0[hh] -= CRHM_constants::Tm;
    T_s_l[hh] -= CRHM_constants::Tm;

    T_snow[hh] -= CRHM_constants::Tm;
    T_rain[hh] -= CRHM_constants::Tm;
  }
}

void ClassSnobalCRHM::finish(bool good) { // only required for local storage and final output

  ClassSnobalBase::finish(good);
}
