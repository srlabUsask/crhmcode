//created by Manishankar Mondal

#include "ClassSoilDS.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassSoilDS* ClassSoilDS::klone(string name) const{
  return new ClassSoilDS(name);
}

void ClassSoilDS::decl(void) {

  Description = "' Handles soil moisture throughout the year. Expanded to handle detention layer.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'";

  variation_set = VARIATION_1;

  declvar("culvert_Q", NHRU, "flow in culvert.", "(m^3/s)", &culvert_Q);

  declvar("culvert_water_H", NHRU, "depth of pond at culvert inlet.", "(m)", &culvert_water_H);

  declvar("culvert_water_A", NHRU, "surface area of culvert pond.", "(m^2)", &culvert_water_A);

  declvar("culvert_water_V", NHRU, "volume of water in culvert pond.", "(m^3)", &culvert_water_V);

  declvar("culvert_over_Q", NHRU, "flow over the road.", "(m^3/s)", &culvert_over_Q);

  declvar("culvert_evap", NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

  declstatdiag("cum_culvert", NHRU, "Cumulative culvert HRU flow.", "(m^3)", &cum_culvert);

  declstatdiag("cum_culvert_over", NHRU, "Cumulative culvert HRU overflow.", "(m^3)", &cum_culvert_over);

  decldiag("HD", NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", &HD);

  declparam("channel_slope", NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

  declparam("side_slope", NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

  declparam("culvert_diam", NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

  declparam("culvert_water_Dmax", NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

  declparam("number_culverts", NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

  declparam("culvert_type", NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


  variation_set = VARIATION_ORG;

  if(Global::nlay < 2){
    Global::nlay = 2;
    Global::maxlay = 2;
  }

  declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

  declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

  declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

  declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

  declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
    "portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

  declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
    "of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

  decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

  decllocal("Dts_runoff_K", NHRU, "daily detention storage runoff drainage factor. Values from parameters Dts_snow_runoff_K or Dts_organic_runoff_K determined from snowcover.", "mm/d", &Dts_runoff_K);

  declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

  declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

  declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

  declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

  declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

  declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

  declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

  declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

  declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

  declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

  declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

  declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

  declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

  declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

  declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

  declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

  declstatdiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

  declstatdiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);


  decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

  decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

  decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

  decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

  decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

  decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

  decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

  decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);


  declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

  declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

  declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0","Maximum depression storage.", "(mm)", &Sdmax);

  declparam("Sdinit", NHRU, "[0]", "0.0", "5000.0","Initial depression storage.", "(mm)", &Sdinit);

  declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
    "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
    "and transpiration).  Must be less than or equal to soil_moist.","(mm)", &soil_rechr_max);

  declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
    "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

  declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
    "Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

  declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
    "Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

  declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
    "that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

  declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

  declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

  declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

  declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

  declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

  declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

  declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

  declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
      "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
      &soil_withdrawal, &soil_withdrawal_Tables, 2);

  declparam("cov_type", NHRU,
    "[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
    "0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

  declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

  declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

  declgetparam("*", "inhibit_evap", "()", &inhibit_evap); // used since no declgetparam defined

  declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

  declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


  evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);


  declgetvar("*", "infil", "(mm/int)", &infil);

  snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

  runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

  meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);

  declparam("Dts_snow_max", NHRU, "[0]", "0.0", "5000.0","Maximum detention storage in snowcover period.", "(mm)", &Dts_snow_max);

  declparam("Dts_organic_max", NHRU, "[0]", "0.0", "5000.0","Maximum detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_max);

  declparam("Dts_snow_init", NHRU, "[0]", "0.0", "5000.0","Initial detention storage in snowcover period.", "(mm)", &Dts_snow_init);

  declparam("Dts_snow_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of snow runoff drainage factor.", "(mm/d)", &Dts_snow_runoff_K);

  declparam("Dts_organic_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of organic layer runoff drainage factor.", "(mm/d)", &Dts_organic_runoff_K);

  declparam("Dts_organic_init", NHRU, "[0]", "0.0", "5000.0","Initial detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_init);

  declvar("Dts", NHRU, "Detention storage.", "(mm)", &Dts);

  declvar("Dts_max", NHRU, "Maximum detention storage.", "(mm)", &Dts_max);
}

void ClassSoilDS::init(void) {

  nhru = getdim(NHRU);

  if(snowinfilDiv > 1){
    string S = "Soil:  \"snowinfil\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), WARNING);
    LogError(TExcept);
  }

  if(evapDiv > 1){
    string S = "Soil:  \"hru_evap\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), WARNING);
    LogError(TExcept);
  }

  if(meltrunoffDiv > 1){
    string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), WARNING);
    LogError(TExcept);
  }

  if(runoffDiv > 1){
    string S = "Netroute:  \"runoff\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), WARNING);
    LogError(TExcept);
  }

  for(hh = 0; hh < nhru; ++hh) {

    if(soil_moist[hh] > soil_moist_max[hh]) {
      string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + to_string(hh+1).c_str();
      CRHMException TExcept(S.c_str(), TERMINATE);
      LogError(TExcept);
      throw TExcept;
    }

    if(soil_rechr[hh] > soil_rechr_max[hh]) {
      string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + to_string(hh+1).c_str();
      CRHMException TExcept(S.c_str(), TERMINATE);
      LogError(TExcept);
      throw TExcept;
    }
    if(soil_rechr_max[hh] > soil_moist_max[hh]) {
      string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + to_string(hh+1).c_str();
      CRHMException TExcept(S.c_str(), WARNING);
      LogError(TExcept);
      throw TExcept;
    }

    if(Sdinit[hh] > Sdmax[hh]) {
      string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + to_string(hh+1).c_str();
      CRHMException Except(S.c_str() ,TERMINATE);
      LogError(Except);
      throw Except;
    }

    if(gw_init[hh] > gw_max[hh]) {
      string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + to_string(hh+1).c_str();
      CRHMException Except(S.c_str() ,TERMINATE);
      LogError(Except);
      throw Except;
    }

    soil_rechr[hh] = soil_rechr_init[hh];
    soil_moist[hh] = soil_moist_init[hh];

    redirected_residual[hh] = 0.0;
    cum_redirected_residual[hh] = 0.0;

    Sd[hh] = Sdinit[hh];

    gw[hh] = gw_init[hh];

    hru_cum_actet[hh] = 0.0;
    cum_hru_condense[hh] = 0.0;
    cum_infil_act[hh] = 0.0;

    soil_runoff_D[hh] = 0.0;
    soil_ssr_D[hh] = 0.0;
    soil_gw_D[hh] = 0.0;
    gw_flow_D[hh] = 0.0;
    infil_act[hh] = 0.0;
    infil_act_D[hh] = 0.0;

    cum_soil_runoff[hh] = 0.0;
    cum_soil_ssr[hh] = 0.0;
    cum_rechr_ssr[hh] = 0.0;
    cum_soil_gw[hh] = 0.0;
    cum_gw_flow[hh] = 0.0;

    cum_runoff_to_Sd[hh] = 0.0;

    if(inhibit_evap[hh] == 1) {  // when snowcover
      Dts_max[hh] = Dts_snow_max[hh];
      Dts[hh] = Dts_snow_init[hh];
    }
    else if(inhibit_evap[hh] == 0) {  // when no snowcover
      Dts_max[hh] = Dts_organic_max[hh];
      Dts[hh] = Dts_organic_init[hh];
    }

    if(variation == VARIATION_1){
      if(culvert_water_Dmax[hh]/culvert_diam[hh] > 2.5){
        string S = "soil: " + string(Name.c_str()) +  " ratio of H/D > 2.5 in HRU " + to_string(hh+1);
        CRHMException TExcept(S.c_str(), WARNING);
        LogError(TExcept);
      }
      culvert_water_V[hh] = 0.0;
      culvert_water_H[hh] = 0.0;
      culvert_water_A[hh] = 0.0;
      culvert_over_Q[hh] = 0.0;
      culvert_Q[hh] = 0.0;
      culvert_evap[hh] = 0.0;
      cum_culvert[hh] = 0.0;
      cum_culvert_over[hh] = 0.0;
    }
  }
}

void ClassSoilDS::run(void) {

  float soil_lower, excs, condense,Dss;
  float et;

  long nstep = getstep();

  if(nstep == 1)
    for(hh = 0; chkStruct(); ++hh) {
      LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
      LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
      LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh],         hru_area[hh], basin_area[0]);
      LogMessageA(hh, string("'" + Name + " (SoilDS)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh],         hru_area[hh], basin_area[0]);
      LogDebug(" ");
      soil_moist_Init[hh] = soil_moist[hh];
      soil_rechr_Init[hh] = soil_rechr[hh];
      Sd_Init[hh] = Sd[hh];
      gw_Init[hh] = gw[hh];
    }

  nstep = nstep%Global::Freq;

  for(hh = 0; chkStruct(); ++hh) {

    if(snowinfilDiv == 1) // interval value
       snowinfil_buf[hh] = snowinfil[hh];

    if(runoffDiv == 1) // interval value
       runoff_buf[hh] = runoff[hh];

    if(meltrunoffDiv == 1) // interval value
       meltrunoff_buf[hh] = meltrunoff[hh];

    if(evapDiv == 1) // interval value
       hru_evap_buf[hh] = hru_evap[hh];

    if(nstep == 1){ // beginning of every day
      soil_runoff_D[hh] = 0.0;
      soil_ssr_D[hh] = 0.0;
      soil_gw_D[hh] = 0.0;
      gw_flow_D[hh] = 0.0;
      infil_act_D[hh] = 0.0;
    }

    hru_actet[hh] = 0.0;
    infil_act[hh] = 0.0;
    soil_gw[hh] = 0.0;
    soil_ssr[hh] = 0.0;
    rechr_ssr[hh] = 0.0;

    if(hru_evap_buf[hh] < 0.0) {
      condense = -hru_evap_buf[hh];
      cum_hru_condense[hh] += condense;
      hru_evap_buf[hh] = 0.0;
    }
    else
      condense = 0.0;

//******Add infiltration to soil and compute excess

    if(soil_moist_max[hh] > 0.0){
      soil_lower = soil_moist[hh] - soil_rechr[hh];

      float potential = infil[hh] + snowinfil_buf[hh] + condense;

      soil_rechr[hh] = soil_rechr[hh] + potential;

      if(soil_rechr[hh] > soil_rechr_max[hh]) {
        excs = soil_rechr[hh] - soil_rechr_max[hh];
        soil_rechr[hh] = soil_rechr_max[hh];
        soil_lower = soil_lower + excs;
      }

      soil_moist[hh] = soil_lower + soil_rechr[hh];

      if(soil_moist[hh] > soil_moist_max[hh]) {
        excs = soil_moist[hh] - soil_moist_max[hh];
        soil_moist[hh] = soil_moist_max[hh];
      }
      else
        excs = 0.0;

      infil_act[hh] = potential - excs;
      cum_infil_act[hh] += infil_act[hh];
      infil_act_D[hh] += infil_act[hh];

//  Handle subsurface runoff

      if(!inhibit_evap[hh]){ // only when no snowcover
        rechr_ssr[hh] = soil_rechr[hh]/soil_rechr_max[hh]*rechr_ssr_K[hh]/Global::Freq;
        if(rechr_ssr[hh] > soil_rechr[hh])
          rechr_ssr[hh] = soil_rechr[hh];

        soil_rechr[hh] -= rechr_ssr[hh];
        if(soil_rechr[hh] < 0.0)
          soil_rechr[hh] = 0.0;

        soil_moist[hh] -= rechr_ssr[hh];
        soil_ssr[hh] = rechr_ssr[hh];
        cum_rechr_ssr[hh] += rechr_ssr[hh];
      }

      float s2gw_k = soil_gw_K[hh]/Global::Freq;

//  Handle excess to gw

      if(excs >= s2gw_k) { // to gw 03/04/10 changed from >
        soil_gw[hh] = s2gw_k;
      	excs -= s2gw_k;
      }
      else { // to gw
        soil_gw[hh] = excs;
      	excs = 0.0;
      }

//  Handle excess to interflow or runoff

      if(!soil_ssr_runoff[hh] && excs > 0.0){ // to interflow
	      soil_ssr[hh] += excs;
        excs = 0.0;
      }
    }
    else{ // soil_moist_max <= 0.0, i.e. Pond
      excs = infil[hh] + snowinfil_buf[hh] + condense;
    }

    float runoff_to_Sd = 0.0;

    soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh]/hru_area[hh]; // last term (mm*km^2/int)

    cum_redirected_residual[hh] += redirected_residual[hh];

    redirected_residual[hh] = 0;

     if(soil_runoff[hh] > 0.0 && Dts_max[hh] > 0.0){

       if(inhibit_evap[hh] == 1) // when snowcover
         Dts_max[hh] = Dts_snow_max[hh];

       else if(inhibit_evap[hh] == 0) // when no snowcover
         Dts_max[hh] = Dts_organic_max[hh];

       Dss = Dts_max[hh] - Dts[hh];

       if(Dss > 0.0){
         if(soil_runoff[hh] > Dss){
           soil_runoff[hh] -= Dss;
           if(soil_runoff[hh] < 0.0)
             soil_runoff[hh] = 0.0;
           Dts[hh] += Dss;
         }
         else{
           Dts[hh] += soil_runoff[hh];
           soil_runoff[hh] = 0.0;
         }
       }
     }

     // lateral drainage of detention storage to soil_runoff
     if(inhibit_evap[hh] == 1)  // when snowcover
       Dts_runoff_K[hh] = Dts_snow_runoff_K[hh];
     if(inhibit_evap[hh] == 0)  // when no snowcover
       Dts_runoff_K[hh] = Dts_organic_runoff_K[hh];

     if(Dts[hh] > 0.0 && Dts_runoff_K[hh] > 0.0){
       float Dss2runoff_k = Dts_runoff_K[hh]/Global::Freq;
       if(Dss2runoff_k >= Dts[hh])
         Dss2runoff_k = Dts[hh];
       soil_runoff[hh] += Dss2runoff_k;
       Dts[hh] -= Dss2runoff_k;
     }

     if(Dts[hh] < 0.0001)
       Dts[hh] = 0.0;

     if(soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0){
       float Fix = -12.0;
       if(soil_runoff[hh]/Sdmax[hh] < 12.0)
         Fix = -soil_runoff[hh]/Sdmax[hh];
        Dss = (Sdmax[hh] - Sd[hh])*(1 - exp(Fix));

        if(soil_moist_max[hh] <= 0.0) // handle pond
         Dss = Sdmax[hh] - Sd[hh];

        if(Dss > 0.0){
          if(soil_runoff[hh] > Dss){
            soil_runoff[hh] -= Dss;
            if(soil_runoff[hh] < 0.0)
              soil_runoff[hh] = 0.0;
            Sd[hh] += Dss;
            runoff_to_Sd += Dss;
          }
          else{
            Sd[hh] += soil_runoff[hh];
            runoff_to_Sd += soil_runoff[hh];
            soil_runoff[hh] = 0.0;
          }
      }
    }

    if(variation == VARIATION_1){

      float culvert_C[5] = {0.5, 0.6, 0.7, 0.75, 0.97};

      culvert_water_H[hh] = 0.0;
      culvert_water_A[hh] = 0.0;
      culvert_over_Q[hh] = 0.0;
      culvert_Q[hh] = 0.0;
      culvert_evap[hh] = 0.0;

      if((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0){ // culvert addition. Inputs are in (mm)
        culvert_water_V[hh] += soil_runoff[hh]*(hru_area[hh]*1000.0); // convert mm to m3
        soil_runoff[hh] = 0.0;

        culvert_water_H[hh] = pow(3.0*culvert_water_V[hh]*channel_slope[hh]*side_slope[hh], 1.0/3.0); // (m)

        if(culvert_water_H[hh] > 0.0){

// calculate overflow if culvert level exceeds Dmax

          culvert_water_H[hh] = pow(3.0*culvert_water_V[hh]*channel_slope[hh]*side_slope[hh], 1.0/3.0); // (m)

          if(culvert_water_H[hh] > culvert_water_Dmax[hh]){ // (m) overflow over road
            culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
            float maxVol = pow(culvert_water_Dmax[hh], 3.0)/(3.0*channel_slope[hh]*side_slope[hh]); // (m3)

            culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol)/86400.0*Global::Freq; // (m3) to (m3/int)
            culvert_water_V[hh] = maxVol; // (m3)

            cum_culvert_over[hh] += culvert_over_Q[hh]*86400.0/Global::Freq; // (m3/s) to (m3)
            soil_runoff[hh] += culvert_over_Q[hh]*86400.0/Global::Freq/(hru_area[hh]*1000.0); // (m3/s) to (mm/int)
          }
          HD[hh] = culvert_water_H[hh]/culvert_diam[hh];

// calculate flow through culvert

          if(HD[hh] <= 0.0)
            culvert_Q[hh] = 0.0;
          else if(HD[hh] < 1.5)
            culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
                 + 0.159413*HD[hh] + 0.00772254)*culvert_C[culvert_type[hh]]*number_culverts[hh]*pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
          else
            culvert_Q[hh] = culvert_C[culvert_type[hh]]*number_culverts[hh]*0.785*pow(culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

          if(culvert_water_V[hh] > culvert_Q[hh]*86400.0/Global::Freq) // (m3/s) to (m3))
            culvert_water_V[hh] -= culvert_Q[hh]*86400.0/Global::Freq; // (m3/s) to (m3)
          else{
            culvert_Q[hh] = culvert_water_V[hh]*Global::Freq/86400.0;  // (m3) to (m3/s)
            culvert_water_V[hh] = 0.0;
          }

          cum_culvert[hh] += culvert_Q[hh]*86400.0/Global::Freq; // (m3/s) to (m3/int)
          soil_runoff[hh] += culvert_Q[hh]*86400.0/Global::Freq/(hru_area[hh]*1000.0); // (m3/s) to (mm/int)
        }
        culvert_water_A[hh] = sqr(culvert_water_H[hh])/(channel_slope[hh]*side_slope[hh]); // used for evaporation
      } // culvert addition
    }

    soil_runoff_D[hh] += soil_runoff[hh];
    cum_soil_runoff[hh] += soil_runoff[hh];
    cum_runoff_to_Sd[hh] += runoff_to_Sd;

    if(Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0){
      float Sd2gw_k = Sd_gw_K[hh]/Global::Freq;
      if(Sd2gw_k > Sd[hh])
        Sd2gw_k = Sd[hh];
      soil_gw[hh] += Sd2gw_k;
      Sd[hh] -= Sd2gw_k;
      if(Sd[hh] < 0.0)
        Sd[hh] = 0.0;
    }

    soil_gw_D[hh] += soil_gw[hh];
    cum_soil_gw[hh] += soil_gw[hh];

    gw[hh] += soil_gw[hh];
    gw_flow[hh] = 0.0;
    if(gw[hh] > gw_max[hh]){
      gw_flow[hh] += (gw[hh] - gw_max[hh]);
      gw[hh] = gw_max[hh];
    }

    if(gw_max[hh] > 0.0){ // prevents divide by zero error
      float spill = gw[hh]/gw_max[hh]*gw_K[hh]/Global::Freq;
      gw[hh] -= spill;
      gw_flow[hh] += spill;
    }

    gw_flow_D[hh] += gw_flow[hh];
    cum_gw_flow[hh] += gw_flow[hh];

    if(Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0){
      float Sd2ssr_k = Sd_ssr_K[hh]/Global::Freq; // WHY not proportional?
      if(Sd2ssr_k >= Sd[hh])
        Sd2ssr_k = Sd[hh];
      soil_ssr[hh] += Sd2ssr_k;
      Sd[hh] -= Sd2ssr_k;
      if(Sd[hh] < 0.0)
        Sd[hh] = 0.0;
    }

    float s2ssr_k = lower_ssr_K[hh]/Global::Freq;
    if(s2ssr_k > 0.0){
      float avail = soil_moist[hh] - soil_rechr[hh];
      if(s2ssr_k >= avail)
        s2ssr_k = avail;
      soil_moist[hh] -= s2ssr_k;
      soil_ssr[hh] += s2ssr_k;
    }

    cum_soil_ssr[hh] += soil_ssr[hh];
    soil_ssr_D[hh] += soil_ssr[hh];

//******Compute actual evapotranspiration

    float culvert_pond = 0.0; // convert m3 to mm

    float culvert_evapL = 0;

    if(variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0){ // conditions for culvert evaporation
      culvert_pond = culvert_water_V[hh]/(hru_area[hh]*1000.0); // convert m3 to mm over HRU area
      culvert_evapL = hru_evap_buf[hh]*culvert_water_A[hh]/(hru_area[hh]*1e6); // calculate potential evaporation from pond

      if(culvert_evapL > culvert_pond) // limit to amount available
        culvert_evapL = culvert_pond;

      culvert_evap[hh] = culvert_evapL;
      hru_actet[hh] += culvert_evapL;
      culvert_water_V[hh] = (culvert_pond - culvert_evapL)*(hru_area[hh]*1000.0); // remove evaporation from culvert pond and convert to volume
    }

    float avail_evap = hru_evap_buf[hh] - culvert_evapL;
    if(Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
      avail_evap *= (Sd[hh]/(Sd[hh] + soil_moist[hh]));
    else
      avail_evap = 0.0;

    if(Sd[hh] > 0.0 && avail_evap > 0.0){
      if(Sd[hh] >= avail_evap){
        Sd[hh] -= avail_evap;
        if(Sd[hh] < 0.0)
          Sd[hh] = 0.0;
      }
      else {
        avail_evap = Sd[hh];
        Sd[hh] = 0.0;
      }
      hru_actet[hh] += avail_evap;
    }
    else
      avail_evap = 0.0;

    avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

    if(avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0){

      float pctl, pctr, etl, ets, etr;

      if((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
        pctl = (soil_moist[hh] - soil_rechr[hh])/(soil_moist_max[hh] - soil_rechr_max[hh]);
      else
        pctl = 0.0;

      pctr = soil_rechr[hh]/soil_rechr_max[hh];

      etr = avail_evap; // default

      switch (soil_withdrawal_Tables[0][hh]){  // handle recharge layer
        case 1: //******sandy soil
          if(pctr < 0.25)
            etr = 0.5*pctr*avail_evap;
        break;
        case 2: //******loam soil
          if(pctr < 0.5)
            etr = pctr*avail_evap;
        break;
        case 3: //******clay soil
          if(pctr <= 0.33)
            etr = 0.5*pctr*avail_evap;
          else if(pctr < 0.67)
            etr = pctr*avail_evap;
        break;
        case 4: //******organic soil
//         use default above etr = avail_evap;
        break;
      } // recharge switch

      if(etr > avail_evap){
        etl = 0.0; // default value
        etr = avail_evap;
      }
      else
        etl = avail_evap - etr; // default value

      switch (soil_withdrawal_Tables[1][hh]){  // handle lower layer
        case 1: //******sandy soil
          if(pctl < 0.25)
            etl = 0.5*pctl*etl;
        break;
        case 2: //******loam soil
          if(pctl < 0.5)
            etl = pctl*etl;
        break;
        case 3: //******clay soil
          if(pctl <= 0.33)
            etl = 0.5*pctl*etl;
          else if(pctr < 0.67)
            etl = pctl*etl;
        break;
        case 4: //******organic soil
//         use default above etl = avail_evap - etr;
        break;
      } // lower switch

//******Soil moisture accounting  Remember that soil_moist includes soil_rechr[hh][hh]

      long et_type = cov_type[hh];

//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
//****** et_type = 1 - recharge layer only, crops - cov_type = 1
//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

      if(transp_limited[hh] == 1 && et_type == 2)
        et_type = 1;

      et = 0.0;

      switch (et_type){  // handle evaporation
        case 0: case -1:  // avail_evap <= 0
          break;
        case 1:
          if(etr > soil_rechr[hh]) {
            soil_rechr[hh] = 0.0;
            et = soil_rechr[hh];
          }
          else{
            soil_rechr[hh] = soil_rechr[hh] - etr;
            et = etr;
          }
          soil_moist[hh] = soil_moist[hh] - et;
          break;
        case 2:
          if(etr + etl >= soil_moist[hh]) {
            et = soil_moist[hh];
            soil_moist[hh] = 0.0;
            soil_rechr[hh] = 0.0;
          }
          else {
            et = etr + etl;
            soil_moist[hh] = soil_moist[hh] - et;

            if(etr > soil_rechr[hh]) {
              soil_rechr[hh] = 0.0;
            }
            else
              soil_rechr[hh] = soil_rechr[hh] - etr;
          }
          break;
      } // switch

      hru_actet[hh] += et;

    } // soil_moist[hh] > 0.0

    if(soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
      hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

    hru_cum_actet[hh] += hru_actet[hh];

    if(nstep == 0){ // end of every day
      if(snowinfilDiv > 1) // daily value - ready for next day
         snowinfil_buf[hh] = snowinfil[hh]/snowinfilDiv;

      if(runoffDiv > 1) // daily value - ready for next day
         runoff_buf[hh] = runoff[hh]/runoffDiv;

      if(meltrunoffDiv > 1) // daily value - ready for next day
         meltrunoff_buf[hh] = meltrunoff[hh]/meltrunoffDiv;

      if(evapDiv > 1) // daily value - ready for next day
         hru_evap_buf[hh] = hru_evap[hh]/evapDiv;
    }
  } // for
}

void ClassSoilDS::finish(bool good) {

  float Allcum_soil_runoff = 0.0;
  float Allcum_soil_ssr = 0.0;
  float Allcum_rechr_ssr = 0.0;
  float Allcum_soil_gw = 0.0;
  float Allcum_gw_flow = 0.0;
  float Allcum_infil_act = 0.0;
  float Allcum_soil_moist_change = 0.0;
  float Allcum_Sd_change = 0.0;
  float Allcum_gw_change = 0.0;

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
    LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
    LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
    LogMessageA(hh, string("'" + Name + " (Soil)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh]/hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
    LogDebug(" ");

    if(variation == VARIATION_1){
      LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
      LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
      LogDebug(" ");
    }

    Allcum_soil_runoff += cum_soil_runoff[hh]*hru_area[hh];
    Allcum_soil_ssr += cum_soil_ssr[hh]*hru_area[hh];
    Allcum_rechr_ssr += cum_rechr_ssr[hh]*hru_area[hh];
    Allcum_soil_gw += cum_soil_gw[hh]*hru_area[hh];
    Allcum_gw_flow += cum_gw_flow[hh]*hru_area[hh];
    Allcum_infil_act += cum_infil_act[hh]*hru_area[hh];
    Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
    Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
    Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];
  } // hh

  LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
  LogMessage(string("'" + Name + " (SoilDS)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
  LogDebug(" ");
}