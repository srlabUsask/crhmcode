//created by Manishankar Mondal

#include "ClassK_Estimate.h"
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

ClassK_Estimate* ClassK_Estimate::klone(string name) const{
  return new ClassK_Estimate(name);
}

void ClassK_Estimate::decl(void) {

  Description = "'K_Estimate.' \
                 'original interval version,' \
                 'estimates Dts_snow_runoff_K and Dts_organic_runoff_K for module SoilDS.'";

  variation_set = VARIATION_ORG;

  declvar("v_L_upper", TDim::NHRU, "Darcy's lateral flow velocity in upper soil column (ie. recharge layer)", "(m/s)", &v_L_upper);
  declvar("v_L_lower", TDim::NHRU, "Darcy's lateral flow velocity in lower soil column", "(m/s)", &v_L_lower);
  declvar("v_V_sd", TDim::NHRU, "Darcy's vertical flow velocity for sd (ie. depression)", "(m/s)", &v_V_sd);
  declvar("v_V_soil", TDim::NHRU, "Darcy's vertical flow velocity for soil column", "(m/s)", &v_V_soil);
  declvar("v_L_gw", TDim::NHRU, "Darcy's lateral flow velocity for groundwater reservoir", "(m/s)", &v_L_gw);

  declputparam("*", "rechr_ssr_K", "(mm/d)", &rechr_ssr_K);
  declputparam("*", "lower_ssr_K", "(mm/d)", &lower_ssr_K);
  declputparam("*", "Sd_ssr_K",    "(mm/d)", &Sd_ssr_K);
  declputparam("*", "Sd_gw_K",     "(mm/d)", &Sd_gw_K);
  declputparam("*", "soil_gw_K",   "(mm/d)", &soil_gw_K);
  declputparam("*", "gw_K",        "(mm/d)", &gw_K);

  declvar("rechr_ssr_K_V", TDim::NHRU, "ssr drainage factor from recharge", "(mm/d)", &rechr_ssr_K_V);
  declvar("lower_ssr_K_V", TDim::NHRU, "ssr drainage factor from soil column", "(mm/d)", &lower_ssr_K_V);
  declvar("Sd_ssr_K_V", TDim::NHRU, "depression storage ssr drainage factor", "(mm/d)", &Sd_ssr_K_V);
  declvar("Sd_gw_K_V", TDim::NHRU, "depression storage gw drainage factor", "(mm/d)", &Sd_gw_K_V);
  declvar("soil_gw_K_V", TDim::NHRU, "The maximum amount of the soil water excess for an HRU that is routed directly to the associated groundwater reservoir each day", "(mm/d)", &soil_gw_K_V);
  declvar("gw_K_V", TDim::NHRU, "ground water drainage factor from gw reservoir each day", "(m/s)", &gw_K_V);

  declparam("Inhibit_K_set", TDim::NHRU, "[0]", "0", "63", "Inhibit setting of rechr_ssr_K/lower_ssr_K/Sd_ssr_K/Sd_gw_K/soil_gw_K/gw_K parameters using 1/2/4/8/16/32", "()", &Inhibit_K_set);

  declparam("Ks_lower", TDim::NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for lower soil", "(m/s)", &Ks_lower);
  declparam("Ks_upper", TDim::NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for upper soil layer", "(m/s)", &Ks_upper);
  declparam("Ks_gw", TDim::NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for groundwater layer", "(m/s)", &Ks_gw);
  declparam("hru_GSL", TDim::NHRU, "[0.0]", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);
  declparam("PSD", TDim::NHRU, "[0.252]", "0.0", "10.0", "pore size distribution", "()", &PSD);
  declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
      "Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
      "and transpiration). Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);
  declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile. Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

  declgetparam("*", "inhibit_evap", "()", &inhibit_evap); // used since no declgetparam defined

  declputvar("*", "soil_rechr", "(mm)", &soil_rechr);
  declputvar("*", "soil_moist", "(mm)", &soil_moist);
  declputvar("*", "gw", "(mm)", &gw);

  variation_set = VARIATION_1;

  declvar("Dts_organic_runoff_K_V", TDim::NHRU, "detention storage of organic layer runoff drainage factor", "(mm/d)", &Dts_organic_runoff_K_V);

  declvar("Dts_snow_runoff_K_V", TDim::NHRU, "detention storage of snow runoff drainage factor", "(mm/d)", &Dts_snow_runoff_K_V);

  declvar("Ks_snow", TDim::NHRU, "saturated hydraulic conductivity for snow slush layer", "(m/s)", &Ks_snow);

  declvar("v_L_organic", TDim::NHRU, "Darcy's lateral flow velocity in organic layer", "(m/s)", &v_L_organic);

  declvar("v_L_snow", TDim::NHRU, "Darcy's lateral flow velocity in snow slush layer", "(m/s)", &v_L_snow);


  declputparam("*", "Dts_organic_runoff_K", "(mm/d)", &Dts_organic_runoff_K);

  declputparam("*", "Dts_snow_runoff_K", "(mm/d)", &Dts_snow_runoff_K);


  declparam("d_g", TDim::NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

  declparam("Ks_organic", TDim::NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for organic layer", "(m/s)", &Ks_organic);

  declparam("PSD_org", TDim::NHRU, "[0.252]", "0.0", "10.0", "pore size distribution for organic layer", "()", &PSD_org);

  declparam("S_I", TDim::NHRU, "[3.3]", "1.0", "7.0", "soil index", "()", &S_I);


  declgetvar("*", "Dts", "(mm)", &Dts);

  declgetvar("*", "Dts_max", "(mm)", &Dts_max);

  declgetvar("*", "rho", "((kg/m^3))", &rho);

  variation_set = VARIATION_ORG;
}

void ClassK_Estimate::init(void) {

  nhru = getdim(TDim::NHRU);
  for(hh = 0; chkStruct(); ++hh){
    v_L_upper[hh] = 0.0;
    v_L_lower[hh] = 0.0;
    v_V_sd[hh] = 0.0;
    v_V_soil[hh] = 0.0;
    v_L_gw[hh] = 0.0;

    rechr_ssr_K[hh] = 0.0;
    lower_ssr_K[hh] = 0.0;
    Sd_ssr_K[hh] = 0.0;
    Sd_gw_K[hh] = 0.0;
    soil_gw_K[hh] = 0.0;
    gw_K[hh] = 0.0;

    if(variation == VARIATION_1){
      Dts_organic_runoff_K[hh] = 0.0;
      Dts_snow_runoff_K[hh] = 0.0;
      Dts_organic_runoff_K_V[hh] = 0.0;
      Dts_snow_runoff_K_V[hh] = 0.0;
      Ks_snow[hh] = 0.0;
      v_L_organic[hh] = 0.0;
      v_L_snow[hh] = 0.0;
    }
  }
}

void ClassK_Estimate::run(void) {

  
  const double den_water = 1000.0, acc_gravi = 9.8, dyna_visc_water = 0.001787;

  for(hh = 0; chkStruct(); ++hh){
    if(soil_rechr[hh] <= 0.0000001)
      const_cast<double *>  (soil_rechr)[hh] = 0.0;

    if(soil_moist[hh] <= 0.0000001)
      const_cast<double *>  (soil_moist)[hh] = 0.0;

    if(gw[hh] <= 0.0000001)
      const_cast<double *>  (gw)[hh] = 0.0;

    if(soil_rechr[hh] > soil_moist[hh])
      const_cast<double *>  (soil_rechr)[hh] = soil_moist[hh];

    if(!(soil_rechr_max[hh] == 0.0 && soil_moist_max[hh] == 0.0)) {
      if(inhibit_evap[hh] == 1){
        v_L_upper[hh] = 0.0;
        v_L_lower[hh] = Ks_lower[hh]*pow((soil_moist[hh] - soil_rechr[hh])/(soil_moist_max[hh] - soil_rechr_max[hh]), 3.0+2.0/PSD[hh])* tan(hru_GSL[hh]*DEGtoRAD);
        v_V_sd[hh] = 0.0;
        v_V_soil[hh] = Ks_lower[hh]*pow(soil_moist[hh]/soil_moist_max[hh], 3.0+2.0/PSD[hh]);
        v_L_gw[hh] = Ks_gw[hh]*tan(hru_GSL[hh]*DEGtoRAD);
      }

     if(inhibit_evap[hh] == 0){
        v_L_upper[hh] = Ks_upper[hh]*pow(soil_rechr[hh]/soil_rechr_max[hh], 3.0+2.0/PSD[hh])*tan(hru_GSL[hh]*DEGtoRAD);
        v_L_lower[hh] = Ks_lower[hh]*pow((soil_moist[hh] - soil_rechr[hh])/(soil_moist_max[hh] - soil_rechr_max[hh]), 3.0+2.0/PSD[hh])*tan(hru_GSL[hh]*DEGtoRAD);
        v_V_sd[hh] = Ks_lower[hh]*pow(soil_moist[hh]/soil_moist_max[hh], 3.0+2.0/PSD[hh]);
        v_V_soil[hh] = Ks_lower[hh]*pow(soil_moist[hh]/soil_moist_max[hh], 3.0+2.0/PSD[hh]);
        v_L_gw[hh] = Ks_gw[hh]*tan(hru_GSL[hh]*DEGtoRAD);
      }
    }
    bitset<6> Inhibits(Inhibit_K_set[hh]); // Inhibit setting of rechr_ssr_K/lower_ssr_K/Sd_ssr_K/Sd_gw_K/soil_gw_K/gw_K parameters using 1/2/4/8/16/32

    if(!Inhibits[0])
     rechr_ssr_K[hh] = v_L_upper[hh]*soil_rechr_max[hh]*86400;
    if(!Inhibits[1])
      lower_ssr_K[hh] = v_L_lower[hh]*(soil_moist_max[hh] - soil_rechr_max[hh])*86400;
    if(!Inhibits[2])
      Sd_ssr_K[hh] = v_L_lower[hh]*soil_moist_max[hh]*86400;
    if(!Inhibits[3])
      Sd_gw_K[hh] = v_V_sd[hh]*86400000;
    if(!Inhibits[4])
      soil_gw_K[hh] = v_V_soil[hh]*86400000;
    if(!Inhibits[5])
      gw_K[hh] = v_L_gw[hh]*gw[hh]*86400;

// output as variables for tracking
    rechr_ssr_K_V[hh] = rechr_ssr_K[hh];
    lower_ssr_K_V[hh] = lower_ssr_K[hh];
    Sd_ssr_K_V[hh] = Sd_ssr_K[hh];
    Sd_gw_K_V[hh] = Sd_gw_K[hh];
    soil_gw_K_V[hh] = soil_gw_K[hh];
    gw_K_V[hh] = gw_K[hh];

    if(variation == VARIATION_1){
      if(!(Dts_max[hh] == 0.0)) {
        if(inhibit_evap[hh] == 1 && rho[hh] > 100){ // when snowcover, use Shimizu (1970) to estimate sat. hydraulic conductivity of snow
          Ks_snow[hh] = (0.077*sqr((d_g[hh]/1000))*exp(-7.8*(rho[hh]/1000)))*(den_water*acc_gravi/dyna_visc_water);
          v_L_snow[hh] = Ks_snow[hh]*pow(Dts[hh]/Dts_max[hh], S_I[hh])*sin(hru_GSL[hh]*DEGtoRAD);  // Colbeck (1972) formulated Darcy's law for estimating downward flux which is used to calucate the lateral flux
          v_L_organic[hh] = 0.0;
        }

        if(inhibit_evap[hh] == 0 || rho[hh] <= 100){ // when no snowcover, use Brooks-Corey relationship (1964) to estimate hydraulic conductivity of organic layer and then compute lateral Darcy's flux
          v_L_organic[hh] = Ks_organic[hh]*pow(Dts[hh]/Dts_max[hh], 3.0+2.0/PSD_org[hh])*tan(hru_GSL[hh]*DEGtoRAD);
          v_L_snow[hh] = 0.0;
        }
      }

      Dts_organic_runoff_K[hh] = v_L_organic[hh]*Dts_max[hh]*86400;
      Dts_snow_runoff_K[hh] = v_L_snow[hh]*Dts_max[hh]*86400;

// output as variables for tracking
      Dts_organic_runoff_K_V[hh] = Dts_organic_runoff_K[hh];
      Dts_snow_runoff_K_V[hh] = Dts_snow_runoff_K[hh];
    }
  } //for
}

void ClassK_Estimate::finish(bool good) {

}