//created by Manishankar Mondal

#include "ClassSnobalX.h"
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

ClassSnobalX* ClassSnobalX::klone(string name) const{
  return new ClassSnobalX(name);
}

void ClassSnobalX::decl(void) {

    Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Non standard module.'";

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
    declstatvar("sum", TDim::NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
    declvar("snowmelt_int", TDim::NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
    declvar("snowmeltD", TDim::NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
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

    declvar("h2o_sat", TDim::NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
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
    decllocal("T_g_L", TDim::NHRU, "soil temp at depth z_g", "(" + string(DEGREE_CELSIUS) + ")", &T_g); // should be K but causes unit fault

    decllocal("m_precip_L", TDim::NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
    decllocal("m_rain_L", TDim::NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
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

    decldiagparam("relative_hts", TDim::NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

    declparam("z_g", TDim::NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
    declparam("z_u", TDim::NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
    declparam("z_T", TDim::NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
    declparam("z_0", TDim::NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

    declparam("max_z_s_0", TDim::NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
    declparam("max_h2o_vol", TDim::NHRU, "[0.0001]", "0.0", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

    declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("KT_sand", TDim::NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

    declgetvar("*", "hru_S_n", "(W/m^2)", &S_n_X);
    declgetvar("*", "hru_I_lw", "(W/m^2)", &I_lw_X);
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &T_a_X);
    declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
    declgetvar("*", "hru_u", "(m/s)", &u_X);
    declgetvar("*", "hru_T_g", "(" + string(DEGREE_CELSIUS) + ")", &T_g_X);

    declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
    declgetvar("*", "net_rain", "(kg/m^2)", &m_rain_X);
    declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
    declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
    declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
    declgetvar("*", "hru_rho_snow", "(kg/m^3)", &rho_snow_X);
    declgetvar("*", "hru_T_pp", "(" + string(DEGREE_CELSIUS) + ")", &T_pp_X);
}


void ClassSnobalX::init(void) {
  ClassSnobalBase::init();
}

void ClassSnobalX::run(void) { // executed every interval

  if(getstep() == 1){ // beginning of model run. Handle initial state file problems
    for (hh = 0; chkStruct(); ++hh) {
      if(m_s[hh] <= 0)
        layer_count[hh] = 0;
      else{
        rho[hh] = m_s[hh]/z_s[hh];
        if(layer_count[hh] <= 0)
          layer_count[hh] = 1;
      }
    }
  }

  for (hh = 0; chkStruct(); ++hh) {

    T_s[hh]    += CRHM_constants::Tm; // temperatures inside Snobal model are °K
    T_s_0[hh]  += CRHM_constants::Tm;
    T_s_l[hh]  += CRHM_constants::Tm;

    T_snow[hh] += CRHM_constants::Tm;
    T_rain[hh] += CRHM_constants::Tm;

    input_rec2[hh].S_n  = S_n_X[hh];
    input_rec2[hh].I_lw = I_lw_X[hh];
    input_rec2[hh].T_a  = T_a_X[hh] + CRHM_constants::Tm;
    input_rec2[hh].e_a  = e_a_X[hh]*1000;
    input_rec2[hh].u    = u_X[hh];
    input_rec2[hh].T_g  = T_g_X[hh] + CRHM_constants::Tm;

    m_precip[hh] = m_precip_X[hh];
    m_snow[hh]   = m_snow_X[hh];
    m_drift[hh]  = m_drift_X[hh];
    m_subl[hh]  = m_subl_X[hh];
    m_rain[hh]   = m_rain_X[hh];
    rho_snow[hh] = rho_snow_X[hh];

    m_precip_cum[hh] += m_precip[hh];
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

    if(Step % Global::Freq == 1)
       snowmeltD[hh] = snowmelt_int[hh];
    else
       snowmeltD[hh] += snowmelt_int[hh];

    input_rec1[hh].S_n  = input_rec2[hh].S_n;
    input_rec1[hh].I_lw = input_rec2[hh].I_lw;
    input_rec1[hh].T_a  = input_rec2[hh].T_a;
    input_rec1[hh].e_a  = input_rec2[hh].e_a;
    input_rec1[hh].u    = input_rec2[hh].u;
    input_rec1[hh].T_g  = input_rec2[hh].T_g;

    E_s_cum[hh] += E_s_int[hh];
    sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
    cumsnowmelt[hh] += snowmelt_int[hh];
    melt_direct_cum[hh] += melt_direct_int[hh];

    T_s[hh]   -= CRHM_constants::Tm; // temperatures outside Snobal model are °C
    T_s_0[hh] -= CRHM_constants::Tm;
    T_s_l[hh] -= CRHM_constants::Tm;

    T_snow[hh] -= CRHM_constants::Tm;
    T_rain[hh] -= CRHM_constants::Tm;
  }
}


void ClassSnobalX::finish(bool good) { // only required for local storage and final output

  ClassSnobalBase::finish(good);
}