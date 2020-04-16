#pragma once
// 02/21/18
//---------------------------------------------------------------------------
//#include <vcl.h>
#pragma hdrstop
#include "stdafx.h"
#include "Hype_CRHM.h"
#include "NewModules.h"
#include "GlobalDll.h"

#include <math.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma init_seg

//---------------------------------------------------------------------------

using namespace std;
using namespace CRHM;

//---------------------------------------------------------------------------

/*
const long i_in = 0; // inorganic nitrogen
const long i_on = 1; // organic nitrogen
const long i_sp = 2; // soluble (reactive) phosphorus, i.e. phosphate
const long i_pp = 3; // particulate phosphorus
const long i_oc = 4; // (dissolved) organic carbon
*/

					 //==============================================================================

ClassWQ_Soil* ClassWQ_Soil::klone(string name) const {
	return new ClassWQ_Soil(name);
}

void ClassWQ_Soil::decl(void) {

	Description = "'Handles soil moisture throughout the year.' \
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

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

	declvar("redirected_residual_conc", NDEFN, "Concentration:: redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mg/l)", &redirected_residual_conc, &redirected_residual_conc_lay, numsubstances);

	declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

	declstatdiag("cum_redirected_residual_mWQ", NHRU, "mass of solute redirected_residual to another HRU.", "(mg*km^2)", &cum_redirected_residual_mWQ);

	declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

	declstatvar("Sd_conc", NDEFN, "Concentration: Depression storage.", "(mg/l)", &Sd_conc, &Sd_conc_lay, numsubstances);

	declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

	declstatvar("gw_conc", NDEFN, "Concentration: ground water storage.", "(mg/l)", &gw_conc, &gw_conc_lay, numsubstances);

	declvar("solute_deposit", NHRU, "solute deposit left by evaporation.", "(mg)", &solute_deposit);

	declstatvar("cumsolute_deposit", NHRU, "cumulative solute deposit left by evaporation.", "(mg)", &cumsolute_deposit);

	declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
		"portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

	declstatvar("soil_rechr_conc", NDEFN, "Concentration: moisture content of soil recharge zone.", "(mg/l)", &soil_rechr_conc, &soil_rechr_conc_lay, numsubstances);

	declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

	declstatvar("soil_moist_conc", NDEFN, "Concentration: moisture content of soil profile to the depth.", "(mg/l)", &soil_moist_conc, &soil_moist_conc_lay, numsubstances);

	declstatvar("soil_lower", NHRU, "moisture content of lower soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU. (N.B. not Hype lower layer)", "(mm)", &soil_lower);

	declstatvar("soil_lower_conc", NDEFN, "Concentration: moisture content of lower soil profile to the depth.(N.B. not Hype lower layer)", "(mg/l)", &soil_lower_conc, &soil_lower_conc_lay, numsubstances);

	decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

	decllocal("cum_Sd_evap", NHRU, "cumulative Sd evaporation(included in hru_actet).", "(mm)", &cum_Sd_evap);

	declstatdiag("cum_Sd_ssr", NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_Sd_ssr);

	declstatdiag("cum_Sd_gw", NHRU, "Accumulation of Sd excess from a HRU to gw.", "(mm)", &cum_Sd_gw);

	declstatdiag("cum_lower_ssr", NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_lower_ssr);

	declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

	declvar("soil_gw_conc", NDEFN, "Concentration: Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mg/l)", &soil_gw_conc, &soil_gw_conc_lay, numsubstances);

	declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

	declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

	declvar("gw_flow_conc", NDEFN, "Concentration: Drainage from HRU ground water reservoir.", "(mg/l)", &gw_flow_conc, &gw_flow_conc_lay, numsubstances);

	declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

	declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

	declvar("infil_act_conc", NDEFN, "Concentration: Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act_conc, &infil_act_conc_lay, numsubstances);

	declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

	declvar("cum_infil_act_mWQ", NHRU, "mass of solute infiltrating the soil on each HRU.", "(mg)", &cum_infil_act_mWQ);

	declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

	declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

	declstatdiag("cum_gw_flow_mWQ", NHRU, "mass of solute from a HRU that enters groundwater reservoirs.", "(mg)", &cum_gw_flow_mWQ);

	declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

	declvar("soil_ssr_conc", NDEFN, "Concentration: Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mg/l)", &soil_ssr_conc, &soil_ssr_conc_lay, numsubstances);

	declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

	declvar("rechr_ssr_conc", NHRU, "Concentration: Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mg/l)", &rechr_ssr_conc);

	declvar("soil_rechr_to_Hype_conc", NHRU, "solute added to layer 1.", "(mg)", &soil_rechr_to_Hype_conc);

	declvar("soil_rechr_to_Hype_D_mWQ", NHRU, "daily solute added to layer 1 previous day.", "(mg)", &soil_rechr_to_Hype_D_mWQ);

	decllocal("soil_rechr_to_Hype_Acc_mWQ", NHRU, "solute accumulator for layer 1.", "(mg)", &soil_rechr_to_Hype_Acc_mWQ);

	declvar("soil_lower_to_Hype_mWQ", NHRU, "daily solute added to layer 2.", "(mg)", &soil_lower_to_Hype_mWQ);

	declvar("soil_lower_to_Hype_D_mWQ", NHRU, "solute added to layer 2.", "(mg)", &soil_lower_to_Hype_D_mWQ);

	declvar("soil_lower_to_Hype_Acc_mWQ", NHRU, "solute accumulator for layer 2.", "(mg)", &soil_lower_to_Hype_Acc_mWQ);


	declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

	declstatdiag("cum_soil_ssr_mWQ", NHRU, "mass of solute from a HRU to ssr.", "(mg)", &cum_soil_ssr_mWQ);

	declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

	declstatdiag("cum_rechr_ssr_mWQ", NHRU, "mass of solute portion of excess from a HRU to ssr.", "(mg)", &cum_rechr_ssr_mWQ);

	declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

	declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

	declvar("soil_runoff_conc", NHRU, "Concentration: Portion of excess soil water from a HRU to runoff.", "()", &soil_runoff_conc);

	declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

	declstatdiag("cum_soil_runoff_mWQ", NHRU, "mass of solute of portion of excess soil water from a HRU to runoff.", "(mg)", &cum_soil_runoff_mWQ);

	declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

	declstatdiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

	declstatdiag("cum_runoff_to_Sd_mWQ", NHRU, "mass of solute portion of runoff to depression storage.", "(mg)", &cum_runoff_to_Sd_mWQ);

	declstatdiag("cum_runoff_to_ssr", NHRU, "Cumulative portion of runoff to interflow(ssr).", "(mm/int)", &cum_runoff_to_ssr);

	declstatdiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);

	declstatdiag("cum_soil_gw_mWQ", NHRU, "mass of solute of excess soil water from a HRU that enters groundwater reservoirs.", "(mg)", &cum_soil_gw_mWQ);


	decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

	decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

	decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

	decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

	decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

	decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

	decllocal("soil_lower_Init", NHRU, "initial lower soil moisture.", "(mm)", &soil_lower_Init);

	decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

	decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);

	decllocal("soil_rechr_conc_Init", NHRU, "initial soil recharge.", "(mg)", &soil_rechr_conc_Init);

	decllocal("soil_moist_conc_Init", NHRU, "initial soil moisture.", "(mg)", &soil_moist_conc_Init);

	decllocal("soil_lower_conc_Init", NHRU, "initial lower soil moisture.", "(mg)", &soil_lower_conc_Init);

	decllocal("Sd_conc_Init", NHRU, "initial Depression storage.", "(mg)", &Sd_conc_Init);

	decllocal("gw_conc_Init", NHRU, "initial ground water storage.", "(mg)", &gw_conc_Init);


	declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);

	declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);

	declparam("calcC", NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", &calcC);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

	declparam("Sd_init", NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sd_init);

	declparam("Sd_conc_init", NDEFN, "[1]", "0.0", "10.0", "Initial depression storage.", "(mg/l)", &Sd_conc_init, &Sd_conc_init_lay, numsubstances);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

	declparam("soil_rechr_conc_init", NDEFN, "[1.0]", "0.0", "10.0", "Initial value for soil recharge zone.", "(mg/l)", &soil_rechr_conc_init, &soil_rechr_conc_init_lay, numsubstances);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
		"Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

	declparam("soil_moist_conc_init", NDEFN, "[1.0]", "0.0", "10.0", "Concentration: Initial value of available water in soil profile.", "(mg/l)", &soil_moist_conc_init, &soil_moist_conc_init_lay, numsubstances);

	declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
		"that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

	declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

	declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

	declparam("gw_conc_init", NDEFN, "[1]", "0.0", "10.0", "Initial value of available water in ground water reservoir.", "(mg/l)", &gw_conc_init, &gw_conc_init_lay, numsubstances);

	declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

	declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

	declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

	declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

	declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

	declparam("cov_type", NHRU,
		"[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
		"0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

	declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

	declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit.", "()", &inhibit_evap);

	declparam("c_rain_N_cWQ", NHRU, "0", "0", "1000", "rain solute concentration", "(mg/l)", &c_rain_N_cWQ);

	declparam("Atmos_N_mWQ", NHRU, "0", "0", "3", "atmospheric solute deposit", "(mg/int)", &Atmos_N_mWQ);

	declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
		"Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
		&soil_withdrawal, &soil_withdrawal_Tables, 2);


	declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

	declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


	evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);


	declgetvar("*", "SWE_conc", "(mg/l)", &SWE_conc);

	declgetvar("*", "conc_top", "(mg/m^2)", &conc_top, &conc_top_lay);

	declgetvar("*", "conc_bottom", "(mg/m^2)", &conc_bottom, &conc_bottom_lay);

	declgetvar("*", "conc_below", "(mg/m^2)", &conc_below, &conc_below_lay);

	declgetvar("*", "infil", "(mm/int)", &infil);

	snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

	runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

	meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);
}

void ClassWQ_Soil::init(void) {

	if (Global::nlay < numsubstances) {
		Global::nlay = numsubstances;
		Global::maxlay = numsubstances;
	}

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);

	if (snowinfilDiv > 1) {
	 string S = "Soil:  \"snowinfil\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (evapDiv > 1) {
	 string S = "Soil:  \"hru_evap\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (meltrunoffDiv > 1) {
	 string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (runoffDiv > 1) {
	 string S = "Netroute:  \"runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {
		for (long ss = 0; ss < numsubstances; ++ss) {

			Set_WQ(hh, soil_rechr, soil_rechr_conc, soil_rechr_init[hh], soil_rechr_conc_init[hh]);

			Set_WQ(hh, soil_moist, soil_moist_conc, soil_moist_init[hh], soil_moist_conc_init[hh]);

			if (soil_rechr[hh] > soil_moist[hh]) {
				soil_rechr[hh] = soil_moist[hh];
			 string S = string("'") + Name + " (Soil)' Soil_rechr greater than soil_moist, soil_rechr set to soil_moist, hru = " + std::to_string(hh).c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
				throw TExcept;
			}

			if (soil_rechr_max[hh] > soil_moist_max[hh]) {
			 string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
				CRHMException TExcept(S.c_str(), TERMINATE);
				LogError(TExcept);
				throw TExcept;
			}

			Sub_WQ(hh, soil_lower, soil_lower_conc, soil_moist, soil_moist_conc, soil_rechr, soil_rechr_conc);

			if (Sd_init[hh] > Sdmax[hh]) {
			 string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
				CRHMException Except(S.c_str(), TERMINATE);
				LogError(Except);
				throw Except;
			}

			Reset_WQ(hh, redirected_residual, redirected_residual_conc);
			cum_redirected_residual[hh] = 0.0;
			cum_redirected_residual_mWQ[hh] = 0.0;

			Set_WQ(hh, Sd, Sd_conc, Sd_init[hh], Sd_conc_init[hh]);

			Set_WQ(hh, gw, gw_conc, gw_init[hh], gw_conc_init[hh]);

			Reset_WQ(hh, infil_act, infil_act_conc);
			infil_act_D[hh] = 0.0;

			solute_deposit[hh] = 0.0;
			cumsolute_deposit[hh] = 0.0;

			hru_cum_actet[hh] = 0.0;
			cum_hru_condense[hh] = 0.0;
			cum_Sd_evap[hh] = 0.0;
			cum_infil_act[hh] = 0.0;
			cum_infil_act_mWQ[hh] = 0.0;

			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;

			cum_soil_runoff[hh] = 0.0;
			cum_soil_runoff_mWQ[hh] = 0.0;
			cum_soil_ssr[hh] = 0.0;
			cum_soil_ssr_mWQ[hh] = 0.0;
			cum_rechr_ssr[hh] = 0.0;
			cum_rechr_ssr_mWQ[hh] = 0.0;
			cum_Sd_ssr[hh] = 0.0;
			cum_Sd_gw[hh] = 0.0;
			cum_lower_ssr[hh] = 0.0;
			cum_soil_gw[hh] = 0.0;
			cum_soil_gw_mWQ[hh] = 0.0;
			cum_gw_flow[hh] = 0.0;
			cum_gw_flow_mWQ[hh] = 0.0;

			cum_runoff_to_ssr[hh] = 0.0;
			cum_runoff_to_Sd[hh] = 0.0;
			cum_runoff_to_Sd_mWQ[hh] = 0.0;

			if (variation == VARIATION_1) {
				if (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) {
				 string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + std::to_string(hh + 1);
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
		}  // ss
	} // hh
}

void ClassWQ_Soil::run(void) {

	float excs, temp_excs, excs_mWQ, temp_mWQ, potential, potential_mWQ, condense, temp, temp2;
	float et;

	long nstep = getstep();
	long step = nstep;
	if (nstep == 1) { // First Time only
		for (hh = 0; chkStruct(); ++hh) {
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");

			soil_rechr_Init[hh] = soil_rechr[hh];
			soil_moist_Init[hh] = soil_moist[hh];
			soil_lower_Init[hh] = soil_lower[hh];
			Sd_Init[hh] = Sd[hh];
			gw_Init[hh] = gw[hh];

			// soil_rechr_conc and soil_moist_conc use the Hype initial values

			soil_rechr_conc[hh] = conc_top_lay[i_in][hh]; // mg/l
			soil_lower_conc[hh] = conc_bottom_lay[i_in][hh]; // mg/l
			soil_moist_conc[hh] = soil_rechr_conc[hh] + soil_lower_conc[hh]; // mg/l

			soil_rechr_conc_Init[hh] = soil_rechr_conc[hh];
			soil_moist_conc_Init[hh] = soil_moist_conc[hh];
			soil_lower_conc_Init[hh] = soil_moist_conc[hh] - soil_rechr_conc[hh];

			Sd_conc_Init[hh] = Sd_conc[hh];
			gw_conc_Init[hh] = gw_conc[hh];
			soil_rechr_to_Hype_D_mWQ[hh] = 0.0;
			soil_lower_to_Hype_D_mWQ[hh] = 0.0;

			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_conc_Init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr_conc_Init[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_conc_Init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist_conc_Init[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_conc_Init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower_conc_Init[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_conc_Init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd_conc_Init[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_conc_Init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw_conc_Init[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
		} // for
	} // if

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (snowinfilDiv == 1) // interval value
			snowinfil_buf[hh] = snowinfil[hh];

		if (runoffDiv == 1) // interval value
			runoff_buf[hh] = runoff[hh];

		if (meltrunoffDiv == 1) // interval value
			meltrunoff_buf[hh] = meltrunoff[hh];

		if (evapDiv == 1) // interval value
			hru_evap_buf[hh] = hru_evap[hh];

		if (nstep == 1) { // beginning of every day

						  // update Hype

			soil_rechr_conc[hh] = conc_top_lay[i_on][hh]; // mg/l
			soil_moist_conc[hh] = (conc_bottom_lay[i_on][hh] + conc_top_lay[i_on][hh]);
			//      add_source_to_water(const float vol, long n, float conc, float source)

			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;
			infil_act_D[hh] = 0.0;
			soil_rechr_to_Hype_Acc_mWQ[hh] = 0.0;
			soil_lower_to_Hype_Acc_mWQ[hh] = 0.0;
		}

		solute_deposit[hh] = 0.0;
		hru_actet[hh] = 0.0;
		soil_rechr_to_Hype_conc[hh] = 0.0;
		soil_lower_to_Hype_mWQ[hh] = 0.0;

		Reset_WQ(hh, soil_gw, soil_gw_conc); // soil_gw[hh] = 0.0;
		Reset_WQ(hh, soil_ssr, soil_ssr_conc); // soil_ssr[hh] = 0.0;
		Reset_WQ(hh, rechr_ssr, rechr_ssr_conc); // rechr_ssr[hh] = 0.0;
		Reset_WQ(hh, infil_act, infil_act_conc);

		if (hru_evap_buf[hh] < 0.0) {
			condense = -hru_evap_buf[hh];
			cum_hru_condense[hh] += condense;
			hru_evap_buf[hh] = 0.0;
		}
		else
			condense = 0.0;

		//******Add infiltration to soil and compute excess

		if (soil_moist_max[hh] > 0.0) {
			soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];
			soil_lower_conc[hh] = soil_moist_conc[hh] - soil_rechr_conc[hh];

			potential = infil[hh] + snowinfil_buf[hh] + condense;

			if (potential > 0.0) {
				potential_mWQ = (infil[hh] + condense)*c_rain_N_cWQ[hh] + snowinfil_buf[hh] * SWE_conc[hh];
				if (!inhibit_evap[hh]) // only when no snowcover
					potential_mWQ += Atmos_N_mWQ[hh];
			}
			else
				potential_mWQ = 0.0;

			soil_rechr[hh] = soil_rechr[hh] + potential;

			if (soil_rechr[hh] > soil_rechr_max[hh]) {
				excs = soil_rechr[hh] - soil_rechr_max[hh];
				soil_rechr[hh] = soil_rechr_max[hh];
				soil_lower[hh] = soil_lower[hh] + excs;

				temp_mWQ = potential_mWQ * (potential - excs) / potential; // amount used
				soil_rechr_to_Hype_conc[hh] += temp_mWQ;
				excs_mWQ = potential_mWQ - temp_mWQ;
				soil_lower_to_Hype_mWQ[hh] += excs_mWQ;
			}
			else {
				soil_rechr_to_Hype_conc[hh] += potential_mWQ;
				excs = 0.0;
				excs_mWQ = 0.0;
			}
			soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];

			if (soil_moist[hh] > soil_moist_max[hh]) {
				excs = soil_moist[hh] - soil_moist_max[hh];
				soil_moist[hh] = soil_moist_max[hh];

				temp_mWQ = excs_mWQ * (potential - excs) / potential; // amount used
				excs_mWQ = potential_mWQ - temp_mWQ;
				soil_lower_to_Hype_mWQ[hh] += temp_mWQ;
			}
			else {
				excs = 0.0;
				soil_lower_to_Hype_mWQ[hh] += excs_mWQ;
				excs_mWQ = 0.0;
			}

			infil_act_conc[hh] = potential_mWQ - excs_mWQ;
			cum_infil_act_mWQ[hh] += infil_act_conc[hh];

			infil_act[hh] = potential - excs;
			cum_infil_act[hh] += infil_act[hh];
			infil_act_D[hh] += infil_act[hh];

			//  Handle subsurface runoff - does not affect WQ - concentrates

			if (!inhibit_evap[hh]) {
				rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;
				if (rechr_ssr[hh] > soil_rechr[hh]) {
					rechr_ssr[hh] = soil_rechr[hh];
					soil_rechr_to_Hype_conc[hh] -= soil_rechr_conc[hh];
				}

				soil_rechr[hh] -= rechr_ssr[hh];

				if (soil_rechr[hh] < 0.0) {
					soil_rechr[hh] = 0.0;
					soil_rechr_to_Hype_conc[hh] -= soil_rechr_conc[hh];
				}
				soil_moist[hh] -= rechr_ssr[hh];
				soil_ssr[hh] = rechr_ssr[hh];
				cum_rechr_ssr[hh] += rechr_ssr[hh];
			}

			//  Handle excess to gw

			float s2gw_k = soil_gw_K[hh] / Global::Freq;

			if (excs > s2gw_k)
				if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
					soil_gw[hh] = s2gw_k; // soil_gw[hh] = s2gw_k;
					soil_gw_conc[hh] = s2gw_k / excs * excs_mWQ;
					excs_mWQ -= soil_gw_conc[hh];
					excs -= s2gw_k;
				}
				else { // to gw
					soil_gw[hh] = excs;
					soil_gw_conc[hh] = excs_mWQ;
					excs = 0.0;
					excs_mWQ = 0.0;
				}

				//  Handle excess to interflow or runoff

				if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow
					soil_ssr[hh] += excs;
					soil_ssr_conc[hh] += excs_mWQ;
					excs = 0.0;
					excs_mWQ = 0.0;
				}
		}
		else { // soil_moist_max <= 0.0, i.e. Pond
			excs = infil[hh] + snowinfil_buf[hh] + condense;
			excs_mWQ = (infil[hh] + condense)*c_rain_N_cWQ[hh] + snowinfil_buf[hh] * SWE_conc[hh];
			if (!inhibit_evap[hh]) // only when no snowcover
				excs_mWQ += Atmos_N_mWQ[hh];
		}

		float runoff_to_Sd = 0.0;
		float runoff_to_Sd_mWQ = 0.0;

		soil_runoff[hh] = excs + meltrunoff_buf[hh] + runoff_buf[hh] + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int)

		soil_runoff_conc[hh] = excs_mWQ + meltrunoff_buf[hh] * SWE_conc[hh] + runoff_buf[hh] * c_rain_N_cWQ[hh] + redirected_residual_conc[hh] / hru_area[hh]; // last term (mm*km^2/int)

		cum_redirected_residual[hh] += redirected_residual[hh];

		redirected_residual[hh] = 0;

		if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
			float Fix = -12.0;
			if (soil_runoff[hh] / Sdmax[hh] < 12.0)
				Fix = -soil_runoff[hh] / Sdmax[hh];
			float Ds = (Sdmax[hh] - Sd[hh])*(1 - exp(Fix));

			if (soil_moist_max[hh] <= 0.0) // handle pond
				Ds = Sdmax[hh] - Sd[hh];

			if (Ds > 0.0) {
				if (soil_runoff[hh] > Ds) {
					soil_runoff_conc[hh] -= Ds / soil_runoff[hh] * soil_runoff_conc[hh];
					soil_runoff[hh] -= Ds;
					if (soil_runoff[hh] < 0.0) {
						soil_runoff[hh] = 0.0;
						soil_runoff_conc[hh] = 0.0;
					}
					Sd_conc[hh] += Ds / soil_runoff[hh] * soil_runoff_conc[hh];
					Sd[hh] += Ds;
					runoff_to_Sd += Ds / soil_runoff[hh] * soil_runoff_conc[hh];
				}
				else {
					Sd[hh] += soil_runoff[hh];
					Sd_conc[hh] += soil_runoff_conc[hh];
					runoff_to_Sd += soil_runoff[hh];
					runoff_to_Sd_mWQ += soil_runoff_conc[hh];
					soil_runoff[hh] = 0.0;
					soil_runoff_conc[hh] = 0.0;
				}
			}
		}

		if (variation == VARIATION_1) {

			float culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;

			if ((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
				culvert_water_V[hh] += soil_runoff[hh] * (hru_area[hh] * 1000.0); // convert mm to m3
				soil_runoff[hh] = 0.0;

				culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

				if (culvert_water_H[hh] > 0.0) {

					// calculate overflow if culvert level exceeds Dmax

					culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

					if (culvert_water_H[hh] > culvert_water_Dmax[hh]) { // (m) overflow over road
						culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
						float maxVol = pow(culvert_water_Dmax[hh], 3.0) / (3.0*channel_slope[hh] * side_slope[hh]); // (m3)

						culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400.0*Global::Freq; // (m3) to (m3/int)
						culvert_water_V[hh] = maxVol; // (m3)

						cum_culvert_over[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
						soil_runoff[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
					}
					HD[hh] = culvert_water_H[hh] / culvert_diam[hh];

					// calculate flow through culvert

					if (HD[hh] <= 0.0)
						culvert_Q[hh] = 0.0;
					else if (HD[hh] < 1.5)
						culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
							+ 0.159413*HD[hh] + 0.00772254)*culvert_C[culvert_type[hh]] * number_culverts[hh] * pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
					else
						culvert_Q[hh] = culvert_C[culvert_type[hh]] * number_culverts[hh] * 0.785*pow(culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

					if (culvert_water_V[hh] > culvert_Q[hh] * 86400.0 / Global::Freq) // (m3/s) to (m3))
						culvert_water_V[hh] -= culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
					else {
						culvert_Q[hh] = culvert_water_V[hh] * Global::Freq / 86400.0;  // (m3) to (m3/s)
						culvert_water_V[hh] = 0.0;
					}

					cum_culvert[hh] += culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3/int)
					soil_runoff[hh] += culvert_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
				}
				culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (channel_slope[hh] * side_slope[hh]); // used for evaporation
			} // culvert addition
		}

		soil_runoff_D[hh] += soil_runoff[hh];
		cum_soil_runoff[hh] += soil_runoff[hh];
		cum_soil_runoff_mWQ[hh] += soil_runoff[hh] * soil_runoff_conc[hh];
		cum_runoff_to_Sd[hh] += runoff_to_Sd;
		cum_runoff_to_Sd_mWQ[hh] += runoff_to_Sd * soil_runoff_conc[hh];

		if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
			float Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
			if (Sd2gw_k > Sd[hh])
				Sd2gw_k = Sd[hh];
			Add_WQ(hh, soil_gw, soil_gw_conc, Sd2gw_k, Sd_conc[hh]); // soil_gw[hh] += Sd2gw_k;
			Sub_WQ(hh, Sd, Sd_conc, Sd2gw_k, Sd_conc[hh]);           // Sd[hh] -= Sd2gw_k;
			cum_Sd_gw[hh] += Sd2gw_k;
		}

		soil_gw_D[hh] += soil_gw[hh];
		cum_soil_gw[hh] += soil_gw[hh];
		cum_soil_gw_mWQ[hh] += soil_gw[hh] * Sd_conc[hh];

		Add_WQ(hh, gw, gw_conc, soil_gw[hh], soil_gw_conc[hh]); // gw[hh] += soil_gw[hh];
		Reset_WQ(hh, gw_flow, gw_flow_conc);                //gw_flow[hh] = 0.0;
		if (gw[hh] > gw_max[hh]) {
			Add_WQ(hh, gw_flow, gw_flow_conc, gw[hh] - gw_max[hh], gw_conc[hh]); // gw_flow[hh] += (gw[hh] - gw_max[hh]);
			Set_WQ(hh, gw, gw_conc, gw_max[hh], gw_conc[hh]);                 // gw = gw_max[hh];
		}

		if (gw_max[hh] > 0.0) { // prevents divide by zero error
			float spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
			Sub_WQ(hh, gw, gw_conc, spill, gw_conc[hh]);         // gw[hh] -= spill;
			Add_WQ(hh, gw_flow, gw_flow_conc, spill, gw_conc[hh]); // gw_flow[hh] += spill;
		}

		gw_flow_D[hh] += gw_flow[hh];
		cum_gw_flow[hh] += gw_flow[hh];
		cum_gw_flow_mWQ[hh] += gw_flow[hh] * gw_conc[hh];

		if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
			float Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
			if (Sd2ssr_k >= Sd[hh])
				Sd2ssr_k = Sd[hh];
			Add_WQ(hh, soil_ssr, soil_ssr_conc, Sd2ssr_k, Sd_conc[hh]); // soil_ssr[hh] += Sd2ssr_k;
			Sub_WQ(hh, Sd, Sd_conc, Sd2ssr_k, Sd_conc[hh]); // Sd[hh] -= Sd2ssr_k;
			cum_Sd_ssr[hh] += Sd2ssr_k;
		}

		float s2ssr_k = lower_ssr_K[hh] / Global::Freq;
		if (s2ssr_k > 0.0) {
			float avail = soil_moist[hh] - soil_rechr[hh];
			if (s2ssr_k >= avail)
				s2ssr_k = avail;
			Sub_WQ(hh, soil_moist, soil_moist_conc, s2ssr_k, soil_moist_conc[hh]); // soil_moist[hh] -= s2ssr_k;
			Add_WQ(hh, soil_ssr, soil_ssr_conc, s2ssr_k, soil_moist_conc[hh]);      // soil_ssr[hh] += s2ssr_k;
			cum_lower_ssr[hh] += s2ssr_k;
		}

		cum_soil_ssr[hh] += soil_ssr[hh];
		cum_soil_ssr_mWQ[hh] += soil_ssr[hh] * soil_moist_conc[hh];
		soil_ssr_D[hh] += soil_ssr[hh];

		//******Compute actual evapotranspiration

		float culvert_pond = 0.0; // convert m3 to mm

		float culvert_evapL = 0;

		if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation
			culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
			culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

			if (culvert_evapL > culvert_pond) // limit to amount available
				culvert_evapL = culvert_pond;

			culvert_evap[hh] = culvert_evapL;
			hru_actet[hh] += culvert_evapL;
			culvert_water_V[hh] = (culvert_pond - culvert_evapL)*(hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
		}

		float avail_evap = hru_evap_buf[hh] - culvert_evapL;
		if (Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
			avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
		else
			avail_evap = 0.0;

		if (Sd[hh] > 0.0 && avail_evap > 0.0) {
			if (Sd[hh] >= avail_evap) {
				Sd[hh] -= avail_evap;
				if (Sd[hh] < 0.0)
					Reset_WQ(hh, Sd, Sd_conc);
			}
			else {
				avail_evap = Sd[hh];
				Sd[hh] = 0.0;
			}
			cum_Sd_evap[hh] += avail_evap;
			hru_actet[hh] += avail_evap;
		}
		else
			avail_evap = 0.0;

		avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

		if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

			float pctl, pctr, etl, ets, etr;

			if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
				pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				pctl = 0.0;

			pctr = soil_rechr[hh] / soil_rechr_max[hh];

			etr = avail_evap; // default

			switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
			case 1: //******sandy soil
				if (pctr < 0.25)
					etr = 0.5*pctr*avail_evap;
				break;
			case 2: //******loam soil
				if (pctr < 0.5)
					etr = pctr * avail_evap;
				break;
			case 3: //******clay soil
				if (pctr <= 0.33)
					etr = 0.5*pctr*avail_evap;
				else if (pctr < 0.67)
					etr = pctr * avail_evap;
				break;
			case 4: //******organic soil
					//         use default above etr = avail_evap;
				break;
			} // recharge switch

			if (etr > avail_evap) {
				etl = 0.0; // default value
				etr = avail_evap;
			}
			else
				etl = avail_evap - etr; // default value

			switch (soil_withdrawal_Tables[1][hh]) {  // handle lower layer
			case 1: //******sandy soil
				if (pctl < 0.25)
					etl = 0.5*pctl*etl;
				break;
			case 2: //******loam soil
				if (pctl < 0.5)
					etl = pctl * etl;
				break;
			case 3: //******clay soil
				if (pctl <= 0.33)
					etl = 0.5*pctl*etl;
				else if (pctr < 0.67)
					etl = pctl * etl;
				break;
			case 4: //******organic soil
					//         use default above etl = avail_evap - etr;
				break;
			} // lower switch

			  //******Soil moisture accounting  Remember that soil_rechr[hh] includes soil_moist[hh]

			long et_type = cov_type[hh];

			//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
			//****** et_type = 1 - recharge layer only, crops - cov_type = 1
			//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

			if (transp_limited[hh] == 1 && et_type == 2)
				et_type = 1;

			et = 0.0;

			switch (et_type) {  // handle evaporation
			case 0:  // avail_evap <= 0
				break;
			case -1:  // avail_evap <= 0
				break;
			case 1:
				if (etr > soil_rechr[hh]) {
					soil_rechr[hh] = 0.0;
					et = soil_rechr[hh];
				}
				else {
					soil_rechr[hh] = soil_rechr[hh] - etr;
					et = etr;
				}
				soil_moist[hh] = soil_moist[hh] - et;
				break;
			case 2:
				if (etr + etl >= soil_moist[hh]) {
					et = soil_moist[hh];
					soil_moist[hh] = 0.0;
					soil_rechr[hh] = 0.0;
				}
				else {
					et = etr + etl;
					soil_moist[hh] = soil_moist[hh] - et;

					if (etr > soil_rechr[hh]) {
						soil_rechr[hh] = 0.0;
					}
					else
						soil_rechr[hh] = soil_rechr[hh] - etr;
				}
				break;
			} // switch

			hru_actet[hh] += et;

		} // soil_moist[hh] > 0.0

		if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
			hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

		hru_cum_actet[hh] += hru_actet[hh];
		cumsolute_deposit[hh] += solute_deposit[hh];

		if (nstep == 0) { // end of every day
			if (snowinfilDiv > 1) // daily value - ready for next day
				snowinfil_buf[hh] = snowinfil[hh] / snowinfilDiv;

			if (runoffDiv > 1) // daily value - ready for next day
				runoff_buf[hh] = runoff[hh] / runoffDiv;

			if (meltrunoffDiv > 1) // daily value - ready for next day
				meltrunoff_buf[hh] = meltrunoff[hh] / meltrunoffDiv;

			if (evapDiv > 1) // daily value - ready for next day
				hru_evap_buf[hh] = hru_evap[hh] / evapDiv;
		}

		soil_rechr_to_Hype_Acc_mWQ[hh] += soil_rechr_to_Hype_conc[hh];
		soil_rechr_to_Hype_D_mWQ[hh] = soil_rechr_to_Hype_Acc_mWQ[hh];
		soil_rechr_to_Hype_Acc_mWQ[hh] = 0.0;

		soil_lower_to_Hype_Acc_mWQ[hh] += soil_lower_to_Hype_mWQ[hh];
		soil_lower_to_Hype_D_mWQ[hh] = soil_lower_to_Hype_Acc_mWQ[hh];
		soil_lower_to_Hype_Acc_mWQ[hh] = 0.0;

		Sub_WQ(hh, soil_lower, soil_lower_conc, soil_moist, soil_moist_conc, soil_rechr, soil_rechr_conc);

	} // for
}

void ClassWQ_Soil::finish(bool good) {

	float Allcum_soil_runoff = 0.0;
	float Allcum_soil_ssr = 0.0;
	float Allcum_rechr_ssr = 0.0;
	float Allcum_soil_gw = 0.0;
	float Allcum_gw_flow = 0.0;
	float Allcum_infil_act = 0.0;
	float Allcum_soil_moist_change = 0.0;
	float Allcum_Sd_change = 0.0;
	float Allcum_gw_change = 0.0;
	float Allcum_evap = 0.0;
	float Allcum_solute_deposit = 0.0;

	float Allcum_soil_runoff_mWQ = 0.0;
	float Allcum_soil_ssr_mWQ = 0.0;
	float Allcum_rechr_ssr_mWQ = 0.0;
	float Allcum_soil_gw_mWQ = 0.0;
	float Allcum_gw_flow_mWQ = 0.0;
	float Allcum_infil_act_mWQ = 0.0;
	float Allcum_soil_moist_change_mWQ = 0.0;
	float Allcum_Sd_change_mWQ = 0.0;
	float Allcum_gw_change_mWQ = 0.0;
	float AllTotal = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr                  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_change           (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_conc              (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] * soil_rechr_conc[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_conc_change       (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr_conc[hh] - soil_rechr_conc_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_rechr_ssr               (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_rechr_ssr_mWQ           (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist                  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_change           (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_conc              (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] * soil_moist_conc[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_conc_change       (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist_conc[hh] - soil_moist_conc_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower                  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_change           (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh] - soil_lower_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_conc              (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh] * soil_lower_conc[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_conc_change       (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower_conc[hh] - soil_lower_conc_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' hru_cum_actet               (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_Sd_evap                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_evap[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'hru_cum_actet'.");
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_hru_condense            (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_infil_act(all)          (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_infil_act_mWQ(all)      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_gw_mWQ             (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_runoff             (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_runoff_mWQ         (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_rechr_ssr               (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_rechr_ssr_mWQ           (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_ssr                (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_soil_ssr_mWQ            (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd                          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_change                   (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_conc                      (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] * Sd_conc[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_conc_change               (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd_conc[hh] - Sd_conc_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_runoff_to_Sd            (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_runoff_to_Sd_mWQ        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_Sd_ssr                  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_lower_ssr               (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_lower_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw                          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_change                   (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_conc                      (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] * gw_conc[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_conc_change               (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw_conc[hh] - gw_conc_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_gw_flow                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_gw_flow_mWQ             (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_redirected_residual     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_redirected_residual_mWQ (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual_mWQ[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_redirected_residual_mWQ (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual_mWQ[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogDebug(" ");

		float Total = cum_soil_runoff[hh] + cum_soil_ssr[hh] + cum_soil_gw[hh]
			+ cum_runoff_to_Sd[hh] + cum_gw_flow[hh]
			+ (soil_moist[hh] - soil_moist_Init[hh]) + (Sd[hh] - Sd_Init[hh]) + (gw[hh] - gw_Init[hh]) + hru_cum_actet[hh]
			- cum_redirected_residual[hh] / hru_area[hh];
		AllTotal += Total;
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Total                       (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total / hru_area[hh], hru_area[hh], basin_area[0], " *** HRU mass balance");
		LogDebug(" ");

		if (variation == VARIATION_1) {
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
		}


		LogDebug(" ");

		Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
		Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
		Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
		Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
		Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
		Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
		Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
		Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
		Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];

		Allcum_soil_runoff_mWQ += cum_soil_runoff_mWQ[hh] * hru_area[hh];
		Allcum_soil_ssr_mWQ += cum_soil_ssr_mWQ[hh] * hru_area[hh];
		Allcum_rechr_ssr_mWQ += cum_rechr_ssr_mWQ[hh] * hru_area[hh];
		Allcum_soil_gw_mWQ += cum_soil_gw_mWQ[hh] * hru_area[hh];
		Allcum_gw_flow_mWQ += cum_gw_flow_mWQ[hh] * hru_area[hh];
		Allcum_infil_act_mWQ += cum_infil_act_mWQ[hh] * hru_area[hh];
		Allcum_soil_moist_change_mWQ += (soil_moist[hh] * soil_moist_conc[hh] - soil_moist_Init[hh] * soil_moist_conc_Init[hh])*hru_area[hh];
		Allcum_Sd_change_mWQ += (Sd[hh] * Sd_conc[hh] - Sd_Init[hh] * Sd_conc_Init[hh])*hru_area[hh];
		Allcum_gw_change_mWQ += (gw[hh] * gw_conc[hh] - gw_Init[hh] * gw_conc_Init[hh])*hru_area[hh];
		Allcum_evap += hru_cum_actet[hh] * hru_area[hh];
		Allcum_solute_deposit += cumsolute_deposit[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_runoff (mm*basin):           ").c_str(), Allcum_soil_runoff);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_runoff_mWQ (mm*basin):       ").c_str(), Allcum_soil_runoff_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_ssr (mm*basin):              ").c_str(), Allcum_soil_ssr);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_ssr_mWQ (mm*basin):          ").c_str(), Allcum_soil_ssr_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_rechr_ssr (mm*basin):             ").c_str(), Allcum_rechr_ssr);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_rechr_ssr_mWQ (mm*basin):         ").c_str(), Allcum_rechr_ssr_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_gw (mm*basin):               ").c_str(), Allcum_soil_gw);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_gw_mWQ (mm*basin):           ").c_str(), Allcum_soil_gw_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_gw_flow (mm*basin):               ").c_str(), Allcum_gw_flow);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_gw_flow_mWQ (mm*basin):           ").c_str(), Allcum_gw_flow_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_infil_act (mm*basin):             ").c_str(), Allcum_infil_act);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_infil_act_mWQ (mm*basin):         ").c_str(), Allcum_infil_act_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_moist_change (mm*basin):     ").c_str(), Allcum_soil_moist_change);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_soil_moist_change_mWQ (mm*basin): ").c_str(), Allcum_soil_moist_change_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_Sd_change (mm*basin):             ").c_str(), Allcum_Sd_change);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_Sd_change_mWQ (mm*basin):         ").c_str(), Allcum_Sd_change_mWQ);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_gw_change (mm*basin):             ").c_str(), Allcum_gw_change);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_gw_change_mWQ (mm*basin):         ").c_str(), Allcum_gw_change_mWQ);
	LogDebug(" ");
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_actet (mm*basin):                 ").c_str(), Allcum_evap);
	LogMessage(string("'" + Name + " (Soil_WQ)' Allcum_solute_deposit (mm*basin):        ").c_str(), Allcum_solute_deposit);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Soil_WQ)' AllTotal              (mm*basin):        ").c_str(), AllTotal);
	LogDebug(" ");
}

void ClassWQ_Soil::Add_WQ(const long hru, float *var, float *var_conc, float amount, float amount_conc) {

	var_conc[hru] = (var_conc[hru] * var[hru] + amount * amount_conc);
	var[hru] += amount;

	if (var[hru] > 0.0 && var_conc[hru] > 0.0)
		var_conc[hru] /= var[hru];
	else {
		var_conc[hru] = 0.0;
	}
}

void ClassWQ_Soil::Add_WQ(const long hru, float *var, float *var_conc, float *var2, float *var2_conc, float *var3, float *var3_conc) {

	var_conc[hru] = var2[hru] * var2_conc[hru] + var3[hru] * var2_conc[hru];

	var[hru] = var2[hru] + var3[hru];

	var_conc[hru] /= var[hru];
}

void ClassWQ_Soil::Sub_WQ(const long hru, float *var, float *var_conc, float *var2, float *var2_conc, float *var3, float *var3_conc) {

	var_conc[hru] = var2[hru] * var2_conc[hru] - var3[hru] * var2_conc[hru];

	var[hru] = (var2[hru] - var3[hru]);

	if (var[hru] > 0.0 && var_conc[hru] > 0.0)
		var_conc[hru] /= var[hru];
	else {
		var_conc[hru] = 0.0;
	}
}

void ClassWQ_Soil::Set_WQ(const long hru, float *var, float *var_conc, float amount, float amount_conc) {

	var[hru] = amount;
	if (amount > 0.0)
		var_conc[hru] = amount_conc;
	else
		var_conc[hru] = 0.0;
}

void ClassWQ_Soil::Sub_WQ(const long hru, float *var, float *var_conc, float amount, float amount_conc) {

	var_conc[hru] = var[hru] * var_conc[hru] - amount * amount_conc;
	var[hru] -= amount;
	if (var[hru] > 0.0 && var_conc[hru] > 0.0)
		var_conc[hru] /= var[hru];
	else {
		var_conc[hru] = 0.0;
	}
}

void ClassWQ_Soil::Reset_WQ(const long hru, float *var, float *var_conc) {
	var[hru] = 0.0;
	var_conc[hru] = 0.0;
}

ClassWQ_Netroute* ClassWQ_Netroute::klone(string name) const {
	return new ClassWQ_Netroute(name);
}

float ClassWQ_Netroute::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassWQ_Netroute::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassWQ_Netroute::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declvar("inflow_conc", NHRU, "Concentration: inflow from other HRUs", "(mg/l)", &inflow_conc);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declstatdiag("cuminflow_mWQ", NHRU, "cumulative mass of solute inflow from other HRUs", "(mg)", &cuminflow_mWQ);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declvar("outflow_conc", NHRU, "Concentration: HRU outflow", "(mg/l)", &outflow_conc);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	declstatdiag("cumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(mg)", &cumoutflow_mWQ);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	decldiag("outflow_diverted_conc", NHRU, "Concentration: HRU outflow diverted to another HRU", "(mg/l)", &outflow_diverted_conc);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	declstatdiag("cumoutflow_diverted_mWQ", NHRU, "cumulative mass of solute HRU outflow diverted to another HRU", "(mg)", &cumoutflow_diverted_mWQ);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_Sd_mWQ", NHRU, "cumulative mass of solute from other HRU to depressional storage (Sd) of this HRU", "(mg)", &cum_to_Sd_mWQ);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declstatdiag("cum_to_soil_rechr_mWQ", NHRU, "cumulative mass of solute from other HRU to soil_rechr of this HRU", "(mg)", &cum_to_soil_rechr_mWQ);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declvar("gwinflow_conc", NHRU, "Concentration: ground water inflow", "(mg/l)", &gwinflow_conc);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declstatdiag("gwcuminflow_mWQ", NHRU, "cumulative mass of solute gw inflow", "(mg)", &gwcuminflow_mWQ);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declvar("gwoutflow_conc", NHRU, "Concentration: HRU gw outflow", "(mg/l)", &gwoutflow_conc);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	declstatdiag("gwcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU gw outflow", "(mg)", &gwcumoutflow_mWQ);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	decldiag("gwoutflow_diverted_conc", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted_conc);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted_mWQ", NHRU, "cumulative mass of solute HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted_mWQ);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declvar("ssrinflow_conc", NHRU, "Concentration: inflow from other HRUs", "(mg/l)", &ssrinflow_conc);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declstatdiag("ssrcuminflow_mWQ", NHRU, "cumulative mass of solute of inflow from other HRUs", "(mg)", &ssrcuminflow_mWQ);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declvar("ssroutflow_conc", NHRU, "Concentration: HRU outflow", "(mg/l)", &ssroutflow_conc);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("ssrcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(mg)", &ssrcumoutflow_mWQ);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declstatdiag("HRU_cumbasinflow_conc", NHRU, "cumulative mass of solute HRU to basinflow", "(mg)", &HRU_cumbasinflow_conc);

	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declvar("runinflow_conc", NHRU, "Concentration: inflow from other HRUs", "(mg/l)", &runinflow_conc);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declstatdiag("runcuminflow_mWQ", NHRU, "cumulative mass of solute inflow from other HRUs", "(mg)", &runcuminflow_mWQ);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declvar("runoutflow_conc", NHRU, "Concentration: HRU outflow", "(mg/l)", &runoutflow_conc);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("runcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(mg)", &runcumoutflow_mWQ);


	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	declvar("basinflow_conc", BASIN, "basin surface and sub-surface outflow", "(mg/l)", &basinflow_conc);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declstatdiag("cumbasinflow_mWQ", BASIN, "cumulative mass of solute basin surface and sub-surface outflow", "(m^3)", &cumbasinflow_mWQ);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	declvar("basingw_conc", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw_conc);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	declstatdiag("cumbasingw_mWQ", BASIN, "cumulative mass of solute basin groundwater outflow", "(m^3)", &cumbasingw_mWQ);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Kstorage", NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", &Kstorage);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", &Lag);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("whereto", NHRU, "[0]", "0", "1000", "send to; 0 - basin outflow, or HRU input", "()", &whereto);

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	declgetvar("*", "gw_flow_conc", "(mg)", &soil_gw_conc);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	declgetvar("*", "soil_ssr_conc", "(mg)", &soil_ssr_conc);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

	declgetvar("*", "soil_runoff_conc", "(mg)", &soil_runoff_conc);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "Sd_conc", "(mg)", &Sd_conc);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_moist_conc", "(mg)", &soil_moist_conc);

	declputvar("*", "soil_lower", "(mm)", &soil_lower);

	declputvar("*", "soil_lower_conc", "(mg)", &soil_lower_conc);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "soil_rechr_conc", "(mg)", &soil_rechr_conc);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "redirected_residual_conc", "(mg)", &redirected_residual_conc);

	declputvar("*", "cum_redirected_residual", "(mm*km^2/int)", &cum_redirected_residual);

	declputvar("*", "cum_redirected_residual_mWQ", "(mg)", &cum_redirected_residual_mWQ);

	declputvar("*", "gw", "(mm)", &gw);

	declputvar("*", "gw_conc", "(mg)", &gw_conc);
}

void ClassWQ_Netroute::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "Netroute:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "Netroute:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	hruDelay_cWQ = new ClassClark(inflow_conc, outflow_conc, Kstorage, Lag, nhru);
	ssrDelay_cWQ = new ClassClark(ssrinflow_conc, ssroutflow_conc, ssrKstorage, ssrLag, nhru);
	runDelay_cWQ = new ClassClark(runinflow_conc, runoutflow_conc, runKstorage, runLag, nhru);
	gwDelay_cWQ = new ClassClark(gwinflow_conc, gwoutflow_conc, gwKstorage, gwLag, nhru);

	Reset_WQ(0, basinflow, basinflow_conc);
	basinflow_s[0] = 0.0;
	cumbasinflow[0] = 0.0;
	cumbasinflow_mWQ[0] = 0.0;
	Reset_WQ(0, basingw, basingw_conc);
	basingw_s[0] = 0.0;
	cumbasingw[0] = 0.0;
	cumbasingw_mWQ[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {

		Reset_WQ(hh, HRU_cumbasinflow, HRU_cumbasinflow_conc); HRU_cumbasinflow[hh] = 0.0;

		Reset_WQ(hh, inflow, inflow_conc);
		cuminflow[hh] = 0.0;
		cuminflow_mWQ[hh] = 0.0;
		Reset_WQ(hh, outflow, outflow_conc);
		cumoutflow[hh] = 0.0;
		cumoutflow_mWQ[hh] = 0.0;

		Reset_WQ(hh, gwinflow, gwinflow_conc); ;
		gwcuminflow[hh] = 0.0;
		gwcuminflow_mWQ[hh] = 0.0;
		Reset_WQ(hh, gwoutflow, gwoutflow_conc);
		gwcumoutflow[hh] = 0.0;
		gwcumoutflow_mWQ[hh] = 0.0;

		Reset_WQ(hh, ssrinflow, ssrinflow_conc);
		ssrcuminflow[hh] = 0.0;
		ssrcuminflow_mWQ[hh] = 0.0;
		Reset_WQ(hh, ssroutflow, ssroutflow_conc);
		ssrcumoutflow[hh] = 0.0;
		ssrcumoutflow_mWQ[hh] = 0.0;

		Reset_WQ(hh, runinflow, runinflow_conc);
		runcuminflow[hh] = 0.0;
		runcuminflow_mWQ[hh] = 0.0;
		Reset_WQ(hh, runoutflow, runoutflow_conc);
		runcumoutflow[hh] = 0.0;
		runcumoutflow_mWQ[hh] = 0.0;

		Reset_WQ(hh, outflow_diverted, outflow_diverted_conc);
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow_diverted_mWQ[hh] = 0.0;

		Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc);
		gwcumoutflow_diverted[hh] = 0.0;
		gwcumoutflow_diverted_mWQ[hh] = 0.0;

		cum_to_Sd[hh] = 0.0;
		cum_to_Sd_mWQ[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_to_soil_rechr_mWQ[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (Netroute)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassWQ_Netroute::run(void) {

	long step = getstep();
	long nstep = step % Global::Freq;

	Reset_WQ(0, basinflow, basinflow_conc);
	Reset_WQ(0, basingw, basingw_conc);

	for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

		for (hh = 0; chkStruct(hh); ++hh)
			if (order[hh] - 1 == jj)
				break;

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];
		gwinflow_conc[hh] = soil_gw_conc[hh];

		Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc);

		float gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0

				Set_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc, gwoutflow[hhh] / hru_area[hh], gwoutflow_conc[hhh]); // gwoutflow_diverted[hh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hh]; // units (mm*km^2/int)

				gwcumoutflow_diverted[hh] += gw_amount;
				gwcumoutflow_diverted_mWQ[hh] += gw_amount * gwoutflow_conc[hhh];

				gw_amount /= hru_area[hh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount) { // units (mm*km^2/int)

								Add_WQ(hh, soil_rechr, soil_rechr_conc, gw_amount, gwoutflow_conc[hh]); // soil_rechr[hh] += gw_amount/hru_area[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, gw_amount, gwoutflow_conc[hh]); // soil_moist[hh] += gw_amount/hru_area[hh];

								cum_to_soil_rechr[hh] += gw_amount;
								cum_to_soil_rechr_mWQ[hh] += gw_amount * gwoutflow_conc[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount - free);
								cum_to_soil_rechr[hh] += free;
								cum_to_soil_rechr_mWQ[hh] += free * gwoutflow_conc[hh];

								Set_WQ(hh, soil_rechr, soil_rechr_conc, soil_rechr_max[hh], gwoutflow_conc[hh]); // soil_rechr[hh] = soil_rechr_max[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, free, gwoutflow_conc[hh]); // soil_moist[hh] += free;
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount) { // units (mm*km^2/int)

								Add_WQ(hh, Sd, Sd_conc, gw_amount, gwoutflow_conc[hhh]); // Sd[hh] += gw_amount/hru_area[hh];
								cum_to_Sd[hh] += gw_amount;
								cum_to_Sd_mWQ[hh] += gw_amount * gwoutflow_conc[hhh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount - free);
								cum_to_Sd[hh] += free;
								cum_to_Sd_mWQ[hh] += free * gwoutflow_conc[hhh];
								Set_WQ(hh, Sd, Sd_conc, Sdmax[hh], gwoutflow_conc[hh]); // Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						Add_WQ(hh, gw, gw_conc, gw_amount / hru_area[hh], gwoutflow_conc[hh]); // gw[hh] +=  gw_amount/hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU

				if (gw_amount > 0.0) { // handle excess
					Add_WQ(hh, redirected_residual, redirected_residual_conc, gw_amount*hru_area[hh], gwoutflow_conc[hhh]); // redirected_residual[hh] +=  outflow[hhh]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)
					cum_redirected_residual[hh] += redirected_residual[hh];
					cum_redirected_residual_mWQ[hh] += redirected_residual[hh] * redirected_residual_conc[hh];
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];
		gwcuminflow_mWQ[hh] += gwinflow[hh] * gwinflow_conc[hh];

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		Set_WQ(hh, runinflow, runinflow_conc, soil_runoff_Buf[hh] * hru_area[hh], soil_runoff_conc[hh]); // runinflow[hh] = soil_runoff_Buf[hh]*hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];
		runcuminflow_mWQ[hh] += runinflow[hh] * soil_runoff_conc[hh];


		Set_WQ(hh, ssrinflow, ssrinflow_conc, soil_ssr_Buf[hh] * hru_area[hh], soil_ssr_conc[hh]); // ssrinflow[hh] = soil_ssr_Buf[hh]*hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];
		ssrcuminflow_mWQ[hh] += ssrinflow[hh] * soil_ssr_conc[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		ssrcumoutflow_mWQ[hh] += ssroutflow[hh] * ssroutflow_conc[hh];
		runcumoutflow[hh] += runoutflow[hh];
		runcumoutflow_mWQ[hh] += runoutflow[hh] * runoutflow_conc[hh];

		inflow[hh] = runoutflow[hh] + ssroutflow[hh]; // add this HRU runoff and subsurface flow
		if (inflow[hh])
			inflow_conc[hh] = (runoutflow[hh] * runoutflow_conc[hh] + ssroutflow_conc[hh] * ssroutflow[hh]) / inflow[hh];
		else
			inflow_conc[hh] = 0.0;

		Add_WQ(hh, cuminflow, cuminflow_mWQ, inflow[hh], inflow[hh] * inflow_conc[hh]);

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {

				Set_WQ(hh, outflow_diverted, outflow_diverted_conc, outflow[hhh] / hru_area[hh], outflow_conc[hhh]); // outflow_diverted[hhh] = outflow[hhh];
				float Amount = outflow_diverted[hh];

				cumoutflow_diverted[hh] += Amount;
				cumoutflow_diverted_mWQ[hh] += Amount * outflow_conc[hhh];

				Amount /= hru_area[hh];

				float free = soil_rechr_max[hh] - soil_rechr[hh];
				if (free > 0.0 && !soil_rechr_ByPass[hh]) {
					if (free > Amount) { // units (mm*km^2/int)
						Add_WQ(hh, soil_rechr, soil_rechr_conc, Amount, outflow_conc[hhh]); // soil_rechr[hh] += outflow[hhh]/hru_area[hh];
						Add_WQ(hh, soil_moist, soil_moist_conc, Amount, outflow_conc[hhh]); // soil_moist[hh] += outflow[hhh]/hru_area[hh];
						cum_to_soil_rechr[hh] += Amount;
						cum_to_soil_rechr_mWQ[hh] += Amount * outflow_conc[hhh];
						Amount = 0.0; // outflow[hhh] = 0.0;
					}
					else {
						Amount = (Amount - free); // outflow[hhh] = (outflow[hhh]/hru_area[hh] - free)*hru_area[hh];
						cum_to_soil_rechr[hh] += free;
						cum_to_soil_rechr_mWQ[hh] += free * outflow_conc[hhh];

						Set_WQ(hh, soil_rechr, soil_rechr_conc, soil_rechr_max[hh], outflow_conc[hh]); // soil_rechr[hh] = soil_rechr_max[hh];
						Add_WQ(hh, soil_moist, soil_moist_conc, free, outflow_conc[hh]); // soil_moist[hh] += free;
					}
				}

				free = Sdmax[hh] - Sd[hh];
				if (free > 0.0 && !Sd_ByPass[hh] && Amount > 0.0) {
					if (free > Amount) { // units (mm*km^2/int)
						Add_WQ(hh, Sd, Sd_conc, Amount, outflow_conc[hhh]); // Sd[hh] += outflow[hhh]/hru_area[hh];
						cum_to_Sd[hh] += Amount;
						cum_to_Sd_mWQ[hh] += Amount * outflow_conc[hhh];
						Amount = 0.0; // outflow[hhh] = 0.0;
					}
					else {
						Amount = (Amount - free); // outflow[hhh] = (outflow[hhh]/hru_area[hh] - free)*hru_area[hh];
						cum_to_Sd[hh] += free;
						cum_to_Sd_mWQ[hh] += free * outflow_conc[hhh];
						Set_WQ(hh, Sd, Sd_conc, Sdmax[hh], outflow_conc[hh]); // Sd[hh] = Sdmax[hh];
					} // if
				} // if

				if (Amount > 0.0) { // handle excess
					Add_WQ(hh, redirected_residual, redirected_residual_conc, Amount*hru_area[hh], outflow_conc[hhh]); // redirected_residual[hh] +=  outflow[hhh]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)
					cum_redirected_residual[hh] += redirected_residual[hh];
					cum_redirected_residual_mWQ[hh] += redirected_residual[hh] * redirected_residual_conc[hh];

				}
			} // if
		} // for hhh

		hruDelay->DoClark(hh); // need to update for later HRUs
		hruDelay_cWQ->DoClark(hh); // need to update for later HRUs

		if (outflow[hh] > 0.0 && whereto[hh] == 0) { // move to basinflow
			basinflow[0] += outflow[hh] * 1000; // (m3)
			HRU_cumbasinflow[hh] += outflow[hh];
			HRU_cumbasinflow_conc[hh] += outflow[hh] * outflow_conc[hh];
			cumoutflow[hh] += outflow[hh];
			cumoutflow_mWQ[hh] += outflow[hh] * outflow_conc[hh];
		}
		if (gwoutflow[hh]> 0.0 && (gwwhereto[hh] == 0 || abs(gwwhereto[hh]) <= nhru)) { // move to basin gw
			Add_WQ(0, basingw, basingw_conc, gwoutflow[hh] * 1000, gwoutflow_conc[hh]); // basingw[0] += gwoutflow[hh]*1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
			gwcumoutflow_mWQ[hh] += gwoutflow[hh] * gwoutflow_conc[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		} // end if

		Sub_WQ(hh, soil_lower, soil_lower_conc, soil_moist, soil_moist_conc, soil_rechr, soil_rechr_conc);
	} // for hh

	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	runDelay_cWQ->DoClark();
	ssrDelay_cWQ->DoClark();
	gwDelay_cWQ->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasinflow_mWQ[0] += basinflow[0] * outflow_conc[hh];
	cumbasingw[0] += basingw[0];
	cumbasingw_mWQ[0] += basingw[0] * gwoutflow_conc[hh];
}

void ClassWQ_Netroute::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allcuminflow_mWQ = 0.0;
	float Allcumoutflow_mWQ = 0.0;
	float Allcumoutflowdiverted_mWQ = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allgwcuminflow_mWQ = 0.0;
	float Allgwcumoutflow_mWQ = 0.0;
	float Allgwcumoutflowdiverted_mWQ = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float Allssrcuminflow_mWQ = 0.0;
	float Allssrcumoutflow_mWQ = 0.0;
	float Allruncuminflow_mWQ = 0.0;
	float Allruncumoutflow_mWQ = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	float AllSdcuminflow_mWQ = 0.0;
	float Allrechrcuminflow_mWQ = 0.0;
	float AllTotal = 0.0;
	float Total;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cuminflow_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cumoutflow_mWQ              (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cumoutflow_diverted_mWQ     (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' ssrcuminflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' ssrcumoutflow_mWQ           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' runoffcuminflow_mWQ         (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' runoffcumoutflow_mWQ        (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcum_diverted              (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcuminflow_mWQ             (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcumoutflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' gwcumoutflow_diverted_mWQ   (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_to_Sd_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd_mWQ[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_to_soil_rechr_mWQ       (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr_mWQ[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' cum_redirected_residual_mWQ (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_WQ)' HRU_cumbasinflow_conc        (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow_conc[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Total = cumoutflow[hh] + gwcumoutflow[hh] - HRU_cumbasinflow[hh] - cum_to_Sd_mWQ[hh] - cum_to_soil_rechr[hh] - gwcumoutflow[hh]
			+ cumoutflow_diverted[hh] + gwcumoutflow_diverted[hh] - cum_redirected_residual[hh];
		AllTotal += Total;
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Total                           (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total, hru_area[hh], basin_area[0], " *** HRU mass balance");
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh];

		Allcuminflow_mWQ += cuminflow_mWQ[hh];
		Allcumoutflow_mWQ += cumoutflow_mWQ[hh];
		Allcumoutflowdiverted_mWQ += cumoutflow_diverted_mWQ[hh];

		Allgwcuminflow_mWQ += gwcuminflow_mWQ[hh];
		Allgwcumoutflow_mWQ += gwcumoutflow_mWQ[hh];
		Allgwcumoutflowdiverted_mWQ += gwcumoutflow_diverted_mWQ[hh];

		Allssrcumoutflow_mWQ += ssrcumoutflow_mWQ[hh];
		Allssrcuminflow_mWQ += ssrcuminflow_mWQ[hh];
		Allruncuminflow_mWQ += runcuminflow_mWQ[hh];
		Allruncumoutflow_mWQ += runcumoutflow_mWQ[hh];

		AllSdcuminflow_mWQ += cum_to_Sd_mWQ[hh];
		Allrechrcuminflow_mWQ += cum_to_soil_rechr_mWQ[hh];
	}

	LogMessage(string("'" + Name + " (Netroute_WQ)' cumbasinflow (m^3):                     ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute_WQ)' cumbasinflow_mWQ ():                    ").c_str(), cumbasinflow_mWQ[0]);
	LogMessage(string("'" + Name + " (Netroute_WQ)' cumbasingw   (m^3):                     ").c_str(), cumbasingw[0]);
	LogMessage(string("'" + Name + " (Netroute_WQ)' cumbasingw_mWQ ():                      ").c_str(), cumbasingw_mWQ[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcuminflow_mWQ (mm*basin):          ").c_str(), Allgwcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcumoutflow_mWQ (mm*basin):         ").c_str(), Allgwcumoutflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allgwcumoutflowdiverted_mWQ (mm*basin): ").c_str(), Allgwcumoutflowdiverted_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcuminflow_mWQ (mm*basin):            ").c_str(), Allcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcumoutflow (mm*basin):               ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allcumoutflowdiverted_mWQ (mm*basin):   ").c_str(), Allcumoutflowdiverted_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_WQ)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allssrcuminflow_mWQ (mm*basin):         ").c_str(), Allssrcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allssrcumoutflow_mWQ (mm*basin):        ").c_str(), Allssrcumoutflow_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_WQ)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allruncuminflow_mWQ (mm*basin):         ").c_str(), Allruncuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allruncumoutflow_mWQ (mm*basin):        ").c_str(), Allruncumoutflow_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_WQ)' AllSdcuminflow (mm*basin):              ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' AllSdcuminflow_mWQ (mm*basin):          ").c_str(), AllSdcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allrechrcuminflow (mm*basin):           ").c_str(), Allrechrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_WQ)' Allrechrcuminflow_mWQ (mm*basin):       ").c_str(), Allrechrcuminflow_mWQ);
	LogDebug(" ");
	LogMessage(string("'" + Name + " (Netroute_WQ)' AllTotal              (mm*basin):       ").c_str(), AllTotal);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}

void ClassWQ_Netroute::Add_WQ(long hru, float *var, float *var_conc, float amount, float amount_conc) {

	var_conc[hru] = (var_conc[hru] * var[hru] + amount * amount_conc);
	var[hru] += amount;

	if (var[hru] > 0.0 && var_conc[hru] > 0.0)
		var_conc[hru] /= var[hru];
	else {
		//    var[hru] = 0.0;
		var_conc[hru] = 0.0;
	}
}

void ClassWQ_Netroute::Set_WQ(long hru, float *var, float *var_conc, float amount, float amount_conc) {

	var[hru] = amount;
	if (amount > 0.0)
		var_conc[hru] = amount_conc;
	else
		var_conc[hru] = 0.0;
}

void ClassWQ_Netroute::Sub_WQ(long hru, float *var, float *var_conc, float *var2, float *var2_conc, float *var3, float *var3_conc) {

	var_conc[hru] = var2[hru] * var2_conc[hru] - var3[hru] * var2_conc[hru];

	var[hru] = (var2[hru] - var3[hru]);

	if (var[hru] > 0.0 && var_conc[hru] > 0.0)
		var_conc[hru] /= var[hru];
	else {
		//    var[hru] = 0.0;
		var_conc[hru] = 0.0;
	}
}

void ClassWQ_Netroute::Reset_WQ(long hru, float *var, float *var_conc) {
	var[hru] = 0.0;
	var_conc[hru] = 0.0;
}

ClassWQ_ion* ClassWQ_ion::klone(string name) const {
	return new ClassWQ_ion(name);
}

void ClassWQ_ion::decl(void) {

	Description = "'Ion exclusion.'";

	decllocal("ni_cur", NHRU, "top layer - current time step", "()", &ni_cur);

	decllocal("ni_prev", NHRU, "top layer - previous time step", "()", &ni_prev);

	decllocal("SWE_prev", NHRU, "top layer - previous time step", "(mm)", &SWE_prev);


	declvar("layer_Csnow", NDEFN, "concentration", "()", &layer_Csnow, &Csnow_layers, Global::nlay);

	declvar("layer_Csnow_prev", NDEFN, "previous time step concentration", "()", &layer_Csnow_prev, &Csnow_layers_prev, Global::nlay);


	declparam("N_snow_layers", NHRU, "[2]", "1", "20", "number of snow layers. Must be less than or equal nlay. Must be >= ceil(maximum SWE/dz).", "()", &N_snow_layers);

	declparam("dz", NHRU, "[10]", "1", "1000", "thickness of snowpack layers", "(mm)", &dz);

	declparam("Uz", NHRU, "[10]", "1", "1000", "vertical advection of ions through the snowpack", "(mm/h)", &Uz);

	//  declparam("Dz", NHRU, "[10]", "1", "1000", "vertical diffusion of ions through the snowpack", "(mm2/h)", &Dz);


	declgetvar("*", "SWE", "(mm/int)", &SWE);

	declgetvar("*", "snowmelt_int_mWQ", "(mg/int)", &snowmelt_int_mWQ);

}

void ClassWQ_ion::init(void) {

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);
	for (hh = 0; hh < nhru; ++hh) {

		if (N_snow_layers[hh] > nlay) {
			CRHMException TExcept("nlay cannot be less than N_snow_layers.", TERMINATE);
			LogError(TExcept);
		}

		ni_cur[hh] = 0;
		ni_prev[hh] = 0;

		for (long ll = 0; ll < N_snow_layers[hh]; ++ll) {
			Csnow_layers[ll][hh] = 0.0;
		}
	}
}

void ClassWQ_ion::run(void) {

	for (hh = 0; chkStruct(); ++hh) {
		if (SWE[hh] > dz[hh] / 2.0) {
			ni_cur[hh] = ceil(SWE[hh] / dz[hh]);

			adjust_layers();

			calc_layers();

			SWE_prev[hh] = SWE[hh];
			ni_prev[hh] = ni_cur[hh];

			for (long ll = 0; ll < ni_cur[hh]; ++ll)
				Csnow_layers_prev[ll][hh] = Csnow_layers[ll][hh];

		} // snowfall > 0.0
	} // for hh
}

void ClassWQ_ion::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		//    LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
	LogDebug(" ");
}

void ClassWQ_ion::adjust_layers(void) {

	// LOADING
	if (ni_cur[hh] == ni_prev[hh])
		Csnow_layers[ni_cur[hh]][hh] = Csnow_layers_prev[ni_prev[hh]][hh] + snowmelt_int_mWQ[hh]; // balance on the top layer only
	else if (ni_cur[hh] != ni_prev[hh]) {
		float dz_prev = ni_prev[hh] * dz[hh] - SWE_prev[hh];
		float dz_cur = SWE[hh] - ni_prev[hh] * dz[hh];
		float dz_prev_perc = dz_prev / (dz_prev + dz_cur);
		float dz_cur_perc = 1.0 - dz_prev_perc;
		Csnow_layers[ni_prev[hh]][hh] = snowmelt_int_mWQ[hh] * dz_prev_perc / dz_prev;
		Csnow_layers[ni_cur[hh]][hh] = snowmelt_int_mWQ[hh] * dz_cur_perc / dz_cur;
	}
}

void ClassWQ_ion::calc_layers(void) {

	// ADVECTION AND DISPERSION

	for (long ll = 0; ll < ni_cur[hh]; ++ll) { // loop for each layer - to compute the vertical distribution of contaminant in the snowpack

		float Adv = Uz[hh] * (Csnow_layers[ll][hh] - Csnow_layers_prev[ll][hh]) / dz[hh];
		//    float Disp = Dz[hh]*(Csnow_layers(t-1,i+1)-2*Csnow_layers(t-1,i)+Csnow_layers(t-1,i-1))/(dz^2)
		Csnow_layers[ll][hh] = Csnow_layers_prev[ll][hh] + Adv; // +Disp;
	}
}

ClassWQ_pbsm* ClassWQ_pbsm::klone(string name) const {
	return new ClassWQ_pbsm(name);
}

void ClassWQ_pbsm::decl(void) {

	Description = "'calculates snow transport and sublimation (Pomeroy and Li, 1999).' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

	variation_set = VARIATION_0 + VARIATION_2;

	declgetvar("*", "hru_u", "(m/s)", &hru_u);


	variation_set = VARIATION_1 + VARIATION_3;

	declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


	variation_set = VARIATION_2 + VARIATION_3;

	declparam("u_D", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

	declparam("Drift_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

	declparam("Drift_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

	declparam("Subl_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

	declparam("Subl_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


	variation_set = VARIATION_ORG;


	declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

	declstatvar("SWE_conc", NHRU, "snow water equivalent", "(mg/l)", &SWE_conc);

	declvar("Subl", NHRU, "interval sublimation", "(mm/int)", &Subl);

	declvar("Drift_in", NHRU, "interval transport into HRU", "(mm/int)", &Drift_in);

	declvar("Drift_in_cWQ", NHRU, "interval transport into HRU", "(mg/l)", &Drift_in_cWQ);

	declvar("Drift_out", NHRU, "interval transport out of HRU", "(mm/int)", &Drift_out);

	declvar("Drift_out_cWQ", NHRU, "interval transport out of HRU", "(mg/l)", &Drift_out_cWQ);

	decldiag("DriftH", NHRU, "interval transport", "(mm/int)", &DriftH);

	decldiag("SublH", NHRU, "interval sublimation", "(mm/int)", &SublH);

	decldiag("BasinSnowLoss", BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

	decldiag("BasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm/int)", &BasinSnowGain);

	declstatdiag("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

	declstatdiag("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

	declstatdiag("cumDrift_mWQ", NHRU, "mass solute from HRU", "(mg)", &cumDrift_mWQ);

	declstatdiag("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

	declstatdiag("cumBasinSnowLoss_mWQ", BASIN, "cumulative mass of solute transport out of basin", "(mg)", &cumBasinSnowLoss_mWQ);

	declstatdiag("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

	declstatdiag("cumBasinSnowGain_mWQ", BASIN, "cumulative mass of solute transport to basin estimated from HRU 1", "(mg)", &cumBasinSnowGain_mWQ);

	declstatdiag("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

	declstatdiag("cumDriftIn_mWQ", NHRU, "cumulative mass of solute transport to HRU", "(mg)", &cumDriftIn_mWQ);

	decllocal("hru_basin", NHRU, "conversion factor", "()", &hru_basin);

	decldiag("DrySnow", NHRU, "DrySnow", "()", &DrySnow);

	declstatdiag("SnowAge", NHRU, "SnowAge", "()", &SnowAge);

	declstatdiag("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

	declstatdiag("cumSno_mWQ", NHRU, "cumulative mass of solute snow", "(mg)", &cumSno_mWQ);

	declvar("Prob", NHRU, "Probability", "()", &Prob);

	declvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

	decllocal("SWE_Init", NHRU, "initial SWE", "(mm)", &SWE_Init);

	// parameters

	declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	declparam("distrib", NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

	decldiagparam("N_S", NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

	decldiagparam("A_S", NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("inhibit_bs", NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

	decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

	declparam("c_snow_N_cWQ", NHRU, "0", "0", "1000", "rain solute concentration", "(mg/l)", &c_snow_N_cWQ);

	declparam("Atmos_N_mWQ", NHRU, "0", "0", "10", "total basin area", "(mg/int)", &Atmos_N_mWQ);

	declgetvar("*", "hru_t", "(°C)", &hru_t);
	declgetvar("*", "hru_rh", "(%)", &hru_rh);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClassWQ_pbsm::init(void) {

	nhru = getdim(NHRU);

	cumBasinSnowLoss[0] = 0.0;
	cumBasinSnowGain[0] = 0.0;

	cumBasinSnowLoss_mWQ[0] = 0.0;
	cumBasinSnowGain_mWQ[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		Reset_WQ(hh, SWE, SWE_conc);
		Reset_WQ(hh, Drift_in, Drift_in_cWQ);
		Reset_WQ(hh, Drift_out, Drift_out_cWQ);

		cumDrift[hh] = 0.0;
		cumDriftIn[hh] = 0.0;
		cumSubl[hh] = 0.0;
		cumSno[hh] = 0.0;

		cumDrift_mWQ[hh] = 0.0;
		cumDriftIn_mWQ[hh] = 0.0;
		cumSno_mWQ[hh] = 0.0;

		SnowAge[hh] = 0.0;
		DrySnow[hh] = 0;
		snowdepth[hh] = 0.0;

		if ((hh > 0) && (Ht[hh] < Ht[hh - 1]) && distrib[hh - 1] > 0) {
			CRHMException TExcept(string("'" + Name + " (pbsm)' vegetation heights not in ascending order.").c_str(), WARNING);
			LogError(TExcept);
		}
	}

	for (hh = 0; hh < nhru; ++hh)
		hru_basin[hh] = hru_area[hh] / basin_area[0];
}


void ClassWQ_pbsm::run(void) {

	float Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
	float SumDrift, SumDrift_cWQ, total, SWE_Max, transport;

	if (getstep() == 1)
		for (hh = 0; chkStruct(); ++hh)
			SWE_Init[hh] = SWE[hh];

	for (hh = 0; chkStruct(); ++hh) {

		if (net_snow[hh] > 0.0) {
			Add_WQ(hh, SWE, SWE_conc, net_snow[hh], c_snow_N_cWQ[hh]);
			cumSno[hh] = cumSno[hh] + net_snow[hh];
			cumSno_mWQ[hh] += net_snow[hh] * c_snow_N_cWQ[hh];
		}

		if (variation == VARIATION_ORG || variation == VARIATION_2)
			hru_u_ = hru_u[hh];
		else
			hru_u_ = hru_Uadjust[hh];

		if (variation == VARIATION_2 || variation == VARIATION_3)
			hru_u_ = u_D[hh] * hru_u_;

		Reset_WQ(hh, Drift_in, Drift_in_cWQ);
		Reset_WQ(hh, Drift_out, Drift_out_cWQ);

		Subl[hh] = 0.0;
		DriftH[hh] = 0.0;

		SublH[hh] = 0.0;
		Prob[hh] = 0.0;

		if (SWE[hh] > 0.0)
			SWE_conc[hh] = (SWE_conc[hh] * SWE[hh] + Atmos_N_mWQ[hh]) / SWE[hh];

		if (SWE[hh] > 0.0 && !inhibit_bs[hh]) {

			E_StubHt = Ht[hh] - DepthofSnow(SWE[hh]); // depths(m) SWE(mm)
			if (E_StubHt < 0.0001) E_StubHt = 0.0001;

			Ustar = 0.02264*pow(hru_u_, 1.295f); // Eq. 6.2 rev.,  Ustar over fallow

			if (E_StubHt > 0.01) {
				Znod = (sqr(Ustar) / 163.3f) + 0.5*N_S[hh] * E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
				Lambda = N_S[hh] * A_S[hh] * E_StubHt;  // Raupach Eq. 1

				Ustn = Ustar * sqrt((PBSM_constants::Beta*Lambda) / (1.0 + PBSM_constants::Beta*Lambda));

				Uten_Prob = (log(10.0 / Znod)) / PBSM_constants::KARMAN *min <float>(0.0, Ustar - Ustn);
			}
			else
			{
				Uten_Prob = hru_u_;
			} // end if


			ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, hru_newsnow[hh], SnowAge[hh], DrySnow[hh]);

			if (Prob[hh] > 0.001) {
				Ut = Ut * 0.8;

				Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, hru_rh[hh], fetch[hh], N_S[hh], A_S[hh]);

				if (variation == VARIATION_2 || variation == VARIATION_3) {
					DriftH[hh] = Drift_offset[hh] + DriftH[hh] * Drift_slope[hh];
					SublH[hh] = Subl_offset[hh] + SublH[hh] * Subl_slope[hh];
				}

				Drift_out[hh] = DriftH[hh] * Prob[hh] / fetch[hh];
				if (!inhibit_subl[hh])
					Subl[hh] = SublH[hh] * Prob[hh];

				// handle insufficient snow pack

				if (Drift_out[hh] + Subl[hh] > SWE[hh]) {
					Drift_out_cWQ[hh] = SWE[hh] * SWE_conc[hh]; // mass of solute
					Subl[hh] = SWE[hh] * Subl[hh] / (Subl[hh] + Drift_out[hh]);
					Drift_out[hh] = SWE[hh] - Subl[hh];
					Drift_out_cWQ[hh] /= Drift_out[hh]; // update to concentration
				} // end if
				else
					Drift_out_cWQ[hh] = SWE_conc[hh];

				cumDrift[hh] = cumDrift[hh] + Drift_out[hh];
				cumDrift_mWQ[hh] += Drift_out[hh] * Drift_out_cWQ[hh];
				cumSubl[hh] = cumSubl[hh] + Subl[hh];

				SWE_conc[hh] = SWE_conc[hh] * SWE[hh] / (SWE[hh] - Subl[hh]); // concentrate SWE_conc
				SWE[hh] = SWE[hh] - Subl[hh];
				Sub_WQ(hh, SWE, SWE_conc, Drift_out[hh], SWE_conc[hh]); // subtract Drift_out
			}
		} // end if
	} // end for (hh)

	  // distribute drift

	if (distrib[0] > 0.0 && Drift_out[0] > 0.0) { // simulate transport entering basin using HRU 1
		float Drft = Drift_out[0] * distrib[0];
		Add_WQ(0, SWE, SWE_conc, Drft, SWE_conc[0]); // SWE[0] += Drft;
		cumDriftIn[0] += Drft;
		cumDriftIn_mWQ[0] += Drft * SWE_conc[0];
		BasinSnowGain[0] = Drft * hru_basin[0];
		cumBasinSnowGain[0] += BasinSnowGain[0];  // **** hru_basin = hru_area/basin_area ****
		cumBasinSnowGain_mWQ[0] += BasinSnowGain[0] * SWE_conc[0];  // **** hru_basin = hru_area/basin_area ****
	}

	BasinSnowLoss[0] = 0.0;
	long LastN = 0;

	if (!inhibit_bs[0] && nhru == 1) {
		BasinSnowLoss[0] = Drift_out[0];
		cumBasinSnowLoss[0] += BasinSnowLoss[0];
		cumBasinSnowLoss_mWQ[0] += BasinSnowLoss[0] * SWE_conc[0]; // Not correct - source of snow?
	}

	for (long nn = LastN; chkStruct(nn); ++nn) {
		if (distrib[nn] >= 0.0 && nn + 1 < nhru) // skip till last HRU or -ve distribution
			continue;

		SumDrift = 0.0; SumDrift_cWQ = 0.0;
		for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) { // sum drift over range
			if (Drift_out[hhh] > 0.0) {
				SumDrift_cWQ = SumDrift * SumDrift_cWQ + Drift_out[hhh] * hru_basin[hhh] * SWE_conc[hhh];
				SumDrift += Drift_out[hhh] * hru_basin[hhh];
				SumDrift_cWQ /= SumDrift;
			}
		}
		if (SumDrift > 0.0) { // drift has occurred!
			for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {
				SWE_Max = SWEfromDepth(Ht[hh]);

				if (hh == nn) { // handle last HRU
					if (distrib[nn] > 0) {
						float In = SumDrift / hru_basin[hh]; // remaining drift
						if (SWE_Max > SWE[hh] + In) { // fill snowpack, remainder leaves basin
							Add_to_Drift_in_cWQ(hh, In, SumDrift_cWQ);
							Add_WQ(hh, SWE, SWE_conc, In, SumDrift_cWQ); // can handle all
							cumDriftIn[hh] += In;
							cumDriftIn_mWQ[hh] += In * SumDrift_cWQ;
							transport = 0.0;
						}
						else if (SWE_Max > SWE[hh]) { // cannot handle all
							Add_to_Drift_in_cWQ(hh, SWE_Max - SWE[hh], SumDrift_cWQ);
							cumDriftIn[hh] += SWE_Max - SWE[hh];
							cumDriftIn_mWQ[hh] += (SWE_Max - SWE[hh])*SumDrift_cWQ;
							transport -= (In - (SWE_Max - SWE[hh]))*hru_basin[hh];
							Add_WQ(hh, SWE, SWE_conc, SWE_Max - SWE[hh], SumDrift_cWQ); //  has to come last
						}
						else // zero or -ve - happens during melt??
							transport = SumDrift;
					}
					else if (distrib[nn] < 0) { // all drift deposited
						SWE[hh] += SumDrift / hru_basin[hh]; // can handle all
						cumDriftIn[hh] += SumDrift / hru_basin[hh];
						cumDriftIn_mWQ[hh] += SumDrift / hru_basin[hh] * SumDrift_cWQ;
						transport = 0.0;
					}
					else // distrib[nn] == 0 -> all excess drift leaves basin
						transport = SumDrift;

					BasinSnowLoss[0] += (transport + Drift_out[hh] * hru_basin[hh]);
					cumBasinSnowLoss[0] += (transport + Drift_out[hh] * hru_basin[hh]);
					cumBasinSnowLoss_mWQ[0] += (transport*SumDrift_cWQ + Drift_out[hh] * Drift_out_cWQ[hh] * hru_basin[hh]); // check
				}
				else if (SWE_Max > SWE[hh] && distrib[hh] > 0.0) {
					// handle intermediate HRUs with available storage and distrib > 0
					total = 0.0;
					for (long jj = hh; chkStruct(jj, nn + 1); jj++) // calculate denominator        !!!! nn+1
						total += fabs(distrib[jj]);
					// determine contribution and scale
					transport = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];
					if (SWE_Max > SWE[hh] + transport) { // sufficient capacity
						SWE[hh] += transport;
						Add_to_Drift_in_cWQ(hh, transport, SumDrift_cWQ);
					}
					else {
						transport = SWE_Max - SWE[hh];  // insufficient capacity
						Add_to_Drift_in_cWQ(hh, transport, SumDrift_cWQ);
						SWE[hh] = SWE_Max;
					}
					SumDrift_cWQ = SumDrift * SumDrift_cWQ - transport * hru_basin[hh] * SumDrift_cWQ;
					SumDrift -= transport * hru_basin[hh]; // remove drift used from total available
					cumDriftIn[hh] += transport;
					cumDriftIn_mWQ[hh] += transport * SumDrift_cWQ;
					SumDrift_cWQ = SumDrift_cWQ / SumDrift;
				} // end if
			} // end for (hh)
		} // end if
		LastN = nn + 1;
	} // end for (nn)

	for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation

		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0.0;
		}
	} // end for (hh)
}

void ClassWQ_pbsm::finish(bool good) {

	if (!good) return;

	float AllcumSubl = 0.0;
	float AllcumCover = cumBasinSnowGain[0] - cumBasinSnowLoss[0];

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh] + cumDriftIn[hh] - cumDrift[hh] - cumSubl[hh], hru_area[hh], basin_area[0], "*** SWE just before melt");
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' SWE_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh] - SWE_Init[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		AllcumSubl += cumSubl[hh] * hru_area[hh];
		AllcumCover += (cumSno[hh] + cumDriftIn[hh] - cumDrift[hh] - cumSubl[hh])*hru_area[hh];
		LogDebug(" ");

		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumSno_mWQ     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumDrift_mWQ   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_WQ)' cumDriftIn_mWQ (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn_mWQ[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (pbsm_WQ)' AllcumSubl  (mm*basin): ").c_str(), AllcumSubl, "*** cumulative sum of all HRUs cumSubl");
	LogMessage(string("'" + Name + " (pbsm_WQ)' AllcumCover (mm*basin): ").c_str(), AllcumCover, "*** SWE just before melt cumulative sum of all HRUs cumCover");

	LogDebug(" ");
	LogMessage("'pbsm_WQ' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
	LogMessage("'pbsm_WQ' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);

	LogDebug(" ");
	LogMessage("'pbsm_WQ' cumBasinSnowLoss_mWQ (mm): ", cumBasinSnowLoss_mWQ[0]);
	LogMessage("'pbsm_WQ' cumBasinSnowGain_mWQ (mm): ", cumBasinSnowGain_mWQ[0]);
	LogDebug(" ");

}

void ClassWQ_pbsm::Add_to_Drift_in_cWQ(long hru, float transport, float transport_cWQ) {
	Drift_in_cWQ[hru] = Drift_in_cWQ[hru] * Drift_in[hru] + transport_cWQ * transport;
	Drift_in[hru] += transport;
	Drift_in_cWQ[hru] /= Drift_in[hru];
}

void ClassWQ_pbsm::Reset_WQ(long hru, float *var, float *var_cWQ) {
	var[hru] = 0.0;
	var_cWQ[hru] = 0.0;
}


void ClassWQ_pbsm::Add_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ) {
	var_cWQ[hru] = (var_cWQ[hru] * var[hru] + amount * amount_cWQ);
	var[hru] += amount;
	var_cWQ[hru] /= var[hru];
}

void ClassWQ_pbsm::Sub_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ) {

	var_cWQ[hru] = var[hru] * var_cWQ[hru] - amount * amount_cWQ;
	var[hru] -= amount;
	if (var[hru] > 0.0 && var_cWQ[hru] > 0.0)
		var_cWQ[hru] /= var[hru];
	else {
		var[hru] = 0.0;
		var_cWQ[hru] = 0.0;
	}
}


