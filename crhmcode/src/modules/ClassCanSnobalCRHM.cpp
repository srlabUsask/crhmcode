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

    declvar("Qn_veg", TDim::NHRU, "net allwave radiation wrt the canopy", "(W/m^2)", &Qn_veg);
    declvar("Qh_veg", TDim::NHRU, "sensible heat xfr wrt the canopy", "(W/m^2)", &Qh_veg);
    declvar("Ql_veg", TDim::NHRU, "latent heat xfr wrt the canopy", "(W/m^2)", &Ql_veg);
    declvar("Qp", TDim::NHRU, "advected heat from precip wrt the canopy", "(W/m^2)", &Qp);
    declvar("delta_Q_veg", TDim::NHRU, "change in snowcover's energy wrt the canopy", "(W/m^2)", &delta_Q_veg);
    declvar("delta_Q_0_veg", TDim::NHRU, "change in active layer's energy wrt the canopy", "(W/m^2)", &delta_Q_0_veg);

    declstatvar("cc_s_0_veg", TDim::NHRU, "active layer cold content", "(J/m^2)", &cc_s_0_veg);
    declstatvar("cc_s_veg", TDim::NHRU, "snowcover's cold content", "(J/m^2)", &cc_s_veg);
    declstatvar("h2o_veg", TDim::NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o_veg);

    decllocal("delsub_veg", TDim::NHRU, "mass of evap from active and lower canopy snowpack layers", "(kg/m^2*int)", &delsub_veg);
    decllocal("qsub_veg", TDim::NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &qsub_veg);
    decllocal("delsub_veg_0", TDim::NHRU, "mass of evaporation from active layer", "(kg/m^2*int)", &delsub_veg_0);
    decllocal("delmelt_veg", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &delmelt_veg);
    declvar("deldrip_veg", TDim::NHRU, "predicted specific runoff", "(kg/m^2)", &deldrip_veg);
    declvar("h2o_total_veg", TDim::NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total_veg);

    decldiag("delsub_veg_int", TDim::NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &delsub_veg_int);
    decldiag("delsub_veg_0_int", TDim::NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &delsub_veg_0_int);
    decldiag("delsub_veg_0_int2", TDim::NHRU, "mass of evaporation to air", "(kg/m^2*int)", &delsub_veg_0_int2);
    declvar("delmelt_veg_int", TDim::NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &delmelt_veg_int);
    declvar("delL", TDim::NHRU, "interval change in SWE", "(kg/m^2*int)", &delL);
    declvar("delmelt_veg_int2", TDim::NHRU, "snow melt", "(kg/m^2*int)", &delmelt_veg_int2);
    declvar("delmelt_veg_day", TDim::NHRU, "daily snow melt", "(mm/d)", &delmelt_veg_day);
    decllocal("cmlmelt_veg_day", TDim::NHRU, "daily snow melt accumulator", "(mm/d)", &cmlmelt_veg_day);
    declvar("cmlmelt_veg", TDim::NHRU, "cumulative melt", "(mm)", &cmlmelt_veg);

    declstatvar("z_s_veg_0", TDim::NHRU, "active layer depth", "(m)", &z_s_veg_0);
    declstatvar("z_veg_s", TDim::NHRU, "total snowcover thickness", "(m)", &z_veg_s);

    declstatvar("rho_veg", TDim::NHRU, "average snowcover density", "(kg/m^3)", &rho_veg);

    declstatvar("m_s_veg_0", TDim::NHRU, "active layer specific mass", "(kg/m^2)", &m_s_veg_0);
    declstatvar("m_s_veg", TDim::NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s_veg);

    declstatvar("T_s_veg_0", TDim::NHRU, "active snow layer temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s_veg_0);
    declstatvar("T_s_veg", TDim::NHRU, "average snowcover temp", "(" + string(DEGREE_CELSIUS) + ")", &T_s_veg);

    declstatvar("h2o_sat_veg", TDim::NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat_veg);
    declvar("h2o_vol_veg", TDim::NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol_veg);
    declvar("h2o_max_veg", TDim::NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max_veg);

    declvar("z_snow_veg", TDim::NHRU, "depth of snow in precip", "(m)", &z_snow_veg);
    declvar("h2o_sat_veg_snow", TDim::NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_veg_snow);

    declvar("precip_now_veg", TDim::NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now_veg);
    declvar("T_rain_veg", TDim::NHRU, "rain's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_rain_veg);
    declvar("T_snow_veg", TDim::NHRU, "snowfall's temp", "(" + string(DEGREE_CELSIUS) + ")", &T_snow_veg);

    decllocal("S_n_L", TDim::NHRU, "net solar radiation", "(W/m^2)", &S_n);
    decllocal("I_lw_L", TDim::NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
    decllocal("T_a_L", TDim::NHRU, "air temp", "(" + string(DEGREE_CELSIUS) + ")", &T_a);
    decllocal("e_a_L", TDim::NHRU, "vapor pressure", "(Pa)", &e_a);
    decllocal("u_L", TDim::NHRU, "wind speed", "(m/s)", &u);
    decllocal("T_g_L", TDim::NHRU, "soil temp at depth z_g", "(" + string(DEGREE_CELSIUS) + ")", &T_g);
    decllocal("F_g_L", TDim::NHRU, "soil flux at depth z_g", "(W/m^2)", &F_g);

    decllocal("m_precip_L", TDim::NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    declvar("rain_on_snow_veg", TDim::NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
    decllocal("m_snow_L", TDim::NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
    decllocal("m_subl_L", TDim::NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
    decllocal("rho_snow_L", TDim::NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
    decllocal("T_pp_L", TDim::NHRU, "precip temp", "(" + string(DEGREE_CELSIUS) + ")", &T_pp);

    decllocal("P_a", TDim::NHRU, "air pressure", "(Pa)", &P_a);

    decllocal("m_precip_cum", TDim::NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
    decllocal("m_rain_cum", TDim::NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
    decllocal("m_snow_cum", TDim::NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
    decllocal("m_subl_cum", TDim::NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
    decllocal("E_s_cum", TDim::NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
    decllocal("melt_direct_cum", TDim::NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

    decllocal("stop_no_snow", TDim::NHRU, "snow flag", "()", &stop_no_snow);
    decllocal("snow_store", TDim::NHRU, "accumulates snow till significant", "()", &snow_store);

    declparam("max_h2o_vol_veg", TDim::NHRU, "[0.0001]", "0.0001", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol_veg);
    declparam("z_0_veg", TDim::NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0_veg);

    declgetparam("*", "z_g", "()", &z_g); // depth of soil temp meas (m)
    declgetparam("*", "z_u", "()", &z_u); // height of wind measurement (m)
    declgetparam("*", "z_T", "()", &z_T); // height of air temp & vapor pressure measurement(m)
    declgetparam("*", "max_z_s_0", "()", &max_z_s_0); // maximum active layer thickness (m)
    declgetparam("*", "hru_elev", "()", &hru_elev); // altitude (m)
    declgetparam("*", "basin_area", "()", &basin_area); // total basin area (km^2)
    declgetparam("*", "hru_area", "()", &hru_area); // hru area (km^2)
    declgetparam("*", "hru_rho_snow", "()", &rho_snow_X); // rho of falling snow (kg/m^3)
    declgetparam("*", "rain_soil_snow", "()", &rain_soil_snow); // 0 - handle only snow, 1 - handle snow and rain in this module (when SWE > 0.02mm)
    declgetparam("*", "Alpha_c", "()", &Albedo_veg); // canopy albedo
    declgetparam("*", "Albedo_Snow", "()", &Albedo_vegsnow); // canopy snow albedo assumed same as surface snow

    declgetvar("*", "Albedo", "()", &Albedo_surface); // ground albedo
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_a_X);
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_pp_X); // default precipitation temperature to air
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);

    declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
    declgetvar("*", "intercepted_snow", "(kg/m^2)", &m_snow_X); // new snow intercepted in canopy before ablation processes have kicked in
    declputvar("*", "net_rain", "(kg/m^2)", &m_rain_X);

    variation_set = VARIATION_0 + VARIATION_2;

    declreadobs("Qsi", TDim::NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

    variation_set = VARIATION_0;

    declreadobs("Qli", TDim::NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

    variation_set = VARIATION_1;

    declgetvar("*", "Qsw_veg_Var", "(W/m^2)", &Qsw_veg_Var);

    declgetvar("*", "Qlw_veg_Var", "(W/m^2)", &Qlw_veg_Var);

    variation_set = VARIATION_ORG;
}

void ClassCanSnobalCRHM::init(void) {

  ClassCanSnobalBase::init();
  for (hh = 0; chkStruct(); ++hh) {
    snow_store[hh] = 0.0;
    delmelt_veg_day[hh] = 0.0;
  }
}

void ClassCanSnobalCRHM::run(void) { // executed every interval

  long nstep = getstep() % Global::Freq;

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(m_s_veg[hh] <= 0)
        vegsnowcover[hh] = 0;
      else{
        if(z_veg_s[hh] <= 0.0)
          rho_veg[hh] = 0.0;
        else
          rho_veg[hh] = m_s_veg[hh]/z_veg_s[hh];

        if(vegsnowcover[hh] <= 0)
          vegsnowcover[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    T_s_veg[hh]    += CRHM_constants::Tm; // temperatures inside Snobal model are K
    T_s_veg_0[hh]  += CRHM_constants::Tm;

    T_snow_veg[hh] += CRHM_constants::Tm;
    T_rain_veg[hh] += CRHM_constants::Tm;

    delL[hh] = -m_s_veg[hh];

    switch (variation){
      case VARIATION_ORG:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo_vegsnow[hh]);
        input_rec2[hh].I_lw = Qli[hh];
      break;
      case VARIATION_1:
        input_rec2[hh].S_n  = Qsw_veg_Var[hh]*(1.0 - Albedo_vegsnow[hh]);
        input_rec2[hh].I_lw = Qlw_veg_Var[hh];
      break;
      case VARIATION_2:
        input_rec2[hh].S_n  = Qsi[hh]*(1.0 - Albedo_vegsnow[hh]);
        input_rec2[hh].I_lw = Qlw_veg_Var[hh];
      break;
    }


    input_rec2[hh].T_a  = T_a_X[hh] + CRHM_constants::Tm;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];

    if(m_snow_X[hh] == 0){
      m_snow[hh] = 0.0;
    }      

    if(vegsnowcover[hh]){
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

    if(rain_soil_snow[hh] && vegsnowcover[hh]){ // handle snow and rain over snow cover
      m_precip[hh] = m_precip_X[hh];
      m_rain[hh]   = m_rain_X[hh];
      m_rain_X[hh] = 0.0;
    }
    else{ // handle only snow. Infitration routine handles rain
      m_precip[hh] = m_snow_X[hh];
      m_rain[hh]   = 0.0;
    }

    rho_snow[hh] = rho_snow_X[hh];

    m_precip_cum[hh] += m_precip[hh]; // change
    m_rain_cum[hh] += m_rain[hh];
    m_snow_cum[hh] += m_snow[hh];

    if(m_snow[hh] > 0.0){
      if (rho_snow[hh] <= 0.0){
        CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TExcept::TERMINATE);
        LogError(TExcept);
      }
      z_snow_veg[hh]   = m_snow[hh] / rho_snow[hh];
    }
    else
      z_snow_veg[hh]   = 0.0;

    T_pp[hh]     = T_pp_X[hh] + CRHM_constants::Tm;

// clear interval values

    delmelt_veg_int2[hh] = 0.0;
    delmelt_veg_int[hh] = 0.0;
    delsub_veg_int[hh] = 0.0;
    delsub_veg_0_int[hh] = 0.0;
    delsub_veg_0_int2[hh] = 0.0;
    deldrip_veg[hh] = 0.0;

    long Step = getstep();
    if(getstep() > 1){ // Not first step

      if(m_precip[hh] > 0.0){
        stop_no_snow[hh] = 0;
        precip_now_veg[hh]= true;
      }
      else{
        if(vegsnowcover[hh] == 0)
          stop_no_snow[hh] = 1;
        precip_now_veg[hh]= false;
      }

      do_data_tstep(); // executes Snobal code

    }
    else if(m_precip[hh] > 0.0) {
         CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", TExcept::WARNING);
         LogError(TExcept);
    }

    Step = Step % Global::Freq;
    if(Step == 1)
       cmlmelt_veg_day[hh] = delmelt_veg_int2[hh];
    else
       cmlmelt_veg_day[hh] += delmelt_veg_int2[hh];

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
    cmlmelt_veg[hh] += delmelt_veg_int2[hh];
    melt_direct_cum[hh] += delmelt_veg_int[hh];

    T_s_veg[hh]   -= CRHM_constants::Tm; // temperatures outside Snobal model are DEGREE_CELCIUS
    T_s_veg_0[hh] -= CRHM_constants::Tm;

    T_snow_veg[hh] -= CRHM_constants::Tm;
    T_rain_veg[hh] -= CRHM_constants::Tm;
  }
}

void ClassCanSnobalCRHM::finish(bool good) { // only required for local storage and final output

  ClassCanSnobalBase::finish(good);
}
