#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassSed_SoilX.h"
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM.h"
//#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassSed_SoilX* ClassSed_SoilX::klone(string name) const {
    return new ClassSed_SoilX(name);
}

void ClassSed_SoilX::decl(void) {

    Description = "'Handles soil moisture throughout the year.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'\
                 'Version with Weir limited runoff.'";

    depths_size = 2; // handles recharge and lower layers

    variation_set = VARIATION_1;

    declvar("culvert_Q", TDim::NHRU, "flow in culvert.", "(m^3/s)", &culvert_Q);

    declvar("culvert_water_H", TDim::NHRU, "depth of pond at culvert inlet.", "(m)", &culvert_water_H);

    declvar("culvert_water_A", TDim::NHRU, "surface area of culvert pond.", "(m^2)", &culvert_water_A);

    declvar("culvert_water_V", TDim::NHRU, "volume of water in culvert pond.", "(m^3)", &culvert_water_V);

    declvar("culvert_over_Q", TDim::NHRU, "flow over the road.", "(m^3/s)", &culvert_over_Q);

    declvar("culvert_evap", TDim::NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

    declstatdiag("cum_culvert", TDim::NHRU, "Cumulative culvert HRU flow.", "(m^3)", &cum_culvert);

    declstatdiag("cum_culvert_over", TDim::NHRU, "Cumulative culvert HRU overflow.", "(m^3)", &cum_culvert_over);

    decldiag("HD", TDim::NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", &HD);

    declparam("stream_runoff", TDim::NHRU, "[0.0]", "0.0", "1.0", "fraction of stream returned to runoff.", "()", &stream_runoff);


    declparam("channel_slope", TDim::NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

    declparam("side_slope", TDim::NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

    declparam("culvert_diam", TDim::NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

    declparam("culvert_water_Dmax", TDim::NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

    declparam("number_culverts", TDim::NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

    declparam("culvert_type", TDim::NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


    variation_set = VARIATION_2;

    declvar("weir_outflow", TDim::NHRU, "weir_outflow.", "(m^3/int)", &weir_outflow);

    declvar("weir_outflow_m3s", TDim::NHRU, "weir_outflow.", "(m^3/s)", &weir_outflow_m3s);

    declvar("weir_water_A", TDim::NHRU, "surface area of weir pond.", "(m^2)", &weir_water_A);

    declvar("weir_water_V", TDim::NHRU, "volume of weir pond.", "(m^3)", &weir_water_V);

    declvar("weir_water_h", TDim::NHRU, "depth of weir pond.", "(m)", &weir_water_h);

    declvar("weir_evap", TDim::NHRU, "Depth of water evaporating from weir pond.", "(mm/int)", &weir_evap);

    declvar("weir_crest_volume", TDim::NHRU, "volume of pond at weir crest.", "(m^3)", &weir_crest_volume);

    declstatdiag("cum_weir_over_m3", TDim::NHRU, "Cumulative weir HRU overflow.", "(m^3)", &cum_weir_over_m3);


    declvar("stream_to_Sd", TDim::NHRU, "amount of soil runoff to stream.", "(mm/int)", &stream_to_Sd);

    declparam("stream_Sd", TDim::NHRU, "[0.0]", "0.0", "1.0", "fraction of stream returned to Sd.", "()", &stream_Sd);

    declparam("weir_crest", TDim::NHRU, "[10]", "0.0", "200.0", "weir crest height.", "()", &weir_crest);

    declparam("weir_coefficient", TDim::NHRU, "[1.705]", "0.01", "2.0", "weir_coefficient.", "()", &weir_coefficient);

    declparam("weir_mult", TDim::NHRU, "[1.0]", "0.01", "2.0", "weir_multiplier)", "()", &weir_mult);

    declparam("weir_b", TDim::NHRU, "[0.0]", "0.0", "1000.0", "breadth of weir. . Zero = no weir", "(m)", &weir_b);

    declparam("lake_mult", TDim::NHRU, "[1.0]", "1.0", "1.0e6", "lake rating curve multiplier.", "()", &lake_mult);

    declparam("lake_power", TDim::NHRU, "[1.0]", "0.1", "5.0", "lake rating curve power.", "()", &lake_power);

    declparam("lake_p", TDim::NHRU, "[1.72]", "1.0", "10.0", "lake shape factor.", "()", &lake_p);

    declparam("lake_S", TDim::NHRU, "[1.72]", "1000.0", "200000.0", "lake shape factor.", "()", &lake_S);


    variation_set = VARIATION_1 + VARIATION_2;

    declvar("soil_runoff_stream", TDim::NHRU, "amount of soil runoff to stream.", "(m^3)", &soil_runoff_stream);

    declparam("runoff_stream", TDim::NHRU, "[0.0]", "0.0", "1.0", "fraction of runoff diverted to stream.", "()", &runoff_stream);

    declvar("stream", TDim::NHRU, "Portion of runoff water retained in HRU as streamflow.", "(mm*km^2/int)", &stream);

    declvar("cum_stream", TDim::NHRU, "cumulative portion of runoff water retained in HRU as streamflow.", "(mm*km^2/int)", &cum_stream);

    declvar("stream_Grp_in", TDim::NHRU, "streamflow from other group (sub-basin.", "(mm*km^2/int)", &stream_Grp_in);

    declvar("stream_Grp_loss", TDim::BASIN, "amount of stream flow out of this sub-basin.", "(m^3)", &stream_Grp_loss);

    declvar("cum_stream_Grp_loss", TDim::BASIN, "cumulative amount of stream flow out of this sub-basin.", "(m^3)", &cum_stream_Grp_loss);


    variation_set = VARIATION_ORG;

    if (Global::nlay < 2) {
        Global::nlay = 2;
        Global::maxlay = 2;
    }

    declvar("current_getstep", TDim::BASIN, "current getstep", "()", &current_getstep);

    declvar("redirected_residual", TDim::NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);
    declstatdiag("cum_redirected_residual", TDim::NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);
    declvar("redirected_residual_conc", TDim::NDEFN, "Concentration:: redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mg/l)", &redirected_residual_conc, &redirected_residual_conc_lay, numsubstances);

    declstatvar("Sd", TDim::NHRU, "Depression storage.", "(mm)", &Sd);
    declstatvar("Sd_conc", TDim::NDEFN, "Concentration: Depression storage.", "(mg/l)", &Sd_conc, &Sd_conc_lay, numsubstances);

    declstatvar("gw", TDim::NHRU, "ground water storage.", "(mm)", &gw);
    declstatvar("gw_conc", TDim::NDEFN, "Concentration: ground water storage.", "(mg/l)", &gw_conc, &gw_conc_lay, numsubstances);

    declstatvar("soil_moist", TDim::NHRU, " available moisture content of soil profile to the depth "//
        "of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);
    declstatvar("soil_moist_conc", TDim::NDEFN, "Concentration: moisture content of soil profile to the depth.", "(mg/l)", &soil_moist_conc, &soil_moist_conc_lay, numsubstances);
    decllocal("soil_moist_Init", TDim::NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

    declstatvar("soil_rechr", TDim::NHRU, " available moisture content of soil recharge zone , ie, the"//
        "portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);
    declparam("soil_rechr_init", TDim::NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
        "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);
    declputvar("*", "conc_soil_rechr", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay);

    declstatvar("soil_lower", TDim::NHRU, "moisture content of lower soil profile to the depth"//
        "of the rooting zone of the major vegetation type on the HRU. (N.B. not Hype lower layer)", "(mm)", &soil_lower);
    declputvar("*", "conc_soil_lower", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay);

    decllocal("cum_hru_condense", TDim::NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

    declvar("cum_Sd_evap", TDim::NHRU, "cumulative Sd evap over HRU.", "(mm)", &cum_Sd_evap);

// vvvvvvvvvvv    Additions for XG algorithm
    declvar("depth_layers", TDim::NDEFN, "thickness of soil layer.", "(m)", &depth_layers, &depth_layers_lay, depths_size);

    declvar("thaw_layers", TDim::NDEFN, "fraction of layer thawed.", "()", &thaw_layers, &thaw_layers_lay, depths_size);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    declvar("soil_gw", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);
    declvar("soil_gw_conc", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mg/l)", &soil_gw_conc, &soil_gw_conc_lay, numsubstances);

    declvar("Sd_gw", TDim::NHRU, "Portion of excess Sd from a HRU that enters groundwater reservoirs.", "(mm/int)", &Sd_gw);

    declvar("soil_gw_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

    declvar("gw_flow", TDim::NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

    declvar("gw_flow_D", TDim::NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

    declvar("infil_act", TDim::NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

    declvar("cum_infil_act", TDim::NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

    declvar("infil_act_D", TDim::NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

    declstatdiag("cum_gw_flow", TDim::NHRU, "cumulative groundwater flow from HRU groundwater reservoirs.", "(mm)", &cum_gw_flow);

    declvar("soil_ssr", TDim::NHRU, "subsurface runoff from soil layers and depressional storage.", "(mm/int)", &soil_ssr);
    declvar("soil_ssr_conc", TDim::NDEFN, "Concentration: Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mg/l)", &soil_ssr_conc, &soil_ssr_conc_lay, numsubstances);

    declvar("rechr_ssr", TDim::NHRU, "subsurface runoff from soil recharge layer.", "(mm/int)", &rechr_ssr);
    declvar("rechr_ssr_conc", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mg/l)", &rechr_ssr_conc, &rechr_ssr_conc_lay, numsubstances);

/* Additions for snow cover fraction */
    declvar("scf", TDim::NHRU, "Snow-cover fraction calculated from snow-cover depletion curves(Essery&Pomeroy,2004).", "()", &scf);

    declstatdiag("cum_soil_ssr", TDim::NHRU, "cumulative subsurface runoff from layers and depressional storage.", "(mm)", &cum_soil_ssr);

    declstatdiag("cum_rechr_ssr", TDim::NHRU, "cumulative subsurface runoff from soil recharge layer.", "(mm)", &cum_rechr_ssr);

    declvar("soil_ssr_D", TDim::NHRU, "daily accumulation of soil_ssr.", "(mm/d)", &soil_ssr_D);

    declvar("soil_runoff", TDim::NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);
    declvar("soil_runoff_cWQ", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU to runoff.", "()", &soil_runoff_cWQ, &soil_runoff_cWQ_lay, numsubstances);

    declstatdiag("cum_soil_runoff", TDim::NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

    declvar("soil_runoff_D", TDim::NHRU, "daily accumulation of soil_runoff.", "(mm/d)", &soil_runoff_D);

    declstatdiag("cum_runoff_to_Sd", TDim::NHRU, "Cumulative portion of runoff to depression storage.", "(mm)", &cum_runoff_to_Sd);

    declstatdiag("cum_soil_gw", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);

    declstatdiag("cum_Sd_gw", TDim::NHRU, "cumulative excess from Sd  that enters groundwater reservoirs.", "(mm)", &cum_Sd_gw);


    decllocal("snowinfil_buf", TDim::NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

    decllocal("runoff_buf", TDim::NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

    decllocal("meltrunoff_buf", TDim::NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

    decllocal("hru_evap_buf", TDim::NHRU, "buffer evaporation.", "(mm/int)", &hru_evap_buf);

    decllocal("soil_rechr_Init", TDim::NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

    decllocal("Sd_Init", TDim::NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

    decllocal("gw_Init", TDim::NHRU, "initial ground water storage.", "(mm)", &gw_Init);

/* Additions for snow cover fraction */
    declparam("CV_SWE", TDim::NHRU, "[1]", "0", "1", "Coefficient of variation: values can be taken from Gray, D. M., Toth, B., Zhao, L., Pomeroy, J. W., & Granger, R. J. (2001). Estimating areal snowmelt infiltration into frozen soils. Hydrological Processes, 15(16), 3095–3111. https://doi.org/10.1002/hyp.320", "()", &CV_SWE);

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

    declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

    declparam("Sdinit", TDim::NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);


    declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

    declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "5000.0",
        "Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

    declparam("soil_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
        "that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

    declparam("gw_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

    declparam("gw_init", TDim::NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

    declparam("gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

    declparam("rechr_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge layer (soil_rechr).", "(mm/d)", &rechr_ssr_K);

    declparam("lower_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from lower soil layer (soil_moist - soil_rechr).", "(mm/d)", &lower_ssr_K);

    declparam("Sd_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage factor from depression storage.", "(mm/d)", &Sd_ssr_K);

    declparam("Sd_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily drainage factor to groundwater reservoir from depression storage.", "(mm/d)", &Sd_gw_K);

    declparam("soil_withdrawal", TDim::NDEFN, "[3]", "1", "4",
        "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
        &soil_withdrawal, &soil_withdrawal_Tables, 2);

    declparam("cov_type", TDim::NHRU,
        "[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
        "0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

    declparam("transp_limited", TDim::NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

    declparam("soil_ssr_runoff", TDim::NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

// vvvvvvvvvvvvvvvvv Added for XR

    declparam("porosity_upper", TDim::NHRU, "[0.5]", "0.0", "1.0", "upper soil porosity (recharge layer).", "(m^3/m^3)", &porosity_upper);

    declparam("porosity_lower", TDim::NHRU, "[0.5]", "0.0", "1.0", "lower soil porosity.", "(m^3/m^3)", &porosity_lower);

//    declparam("evap_from_runoff", TDim::NHRU, "[0]", "0", "1", "when equal to 1, allow evaporation from runoff.", "()", &evap_from_runoff);

    declparam("NO_Freeze", TDim::NHRU, "[0]", "0", "1", "when equal to 1, keeps soil from freezing.", "()", &NO_Freeze);

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit.", "()", &inhibit_evap);

    decldiagparam("Wetlands_scaling_factor", TDim::NHRU, "[1.0]", "-1.0", "1.0", "Scaling ratio for available evaporation from wetland: no scaling applied when default value 1; using Sd/(Sd + soil_moist) as scale ratio when -1<= Wetlands_scaling_factor <0; using Wetlands_scaling_factor value as scale ratio when 0<= Wetlands_scaling_factor <1", "()", &Wetlands_scaling_factor); // Modification 02/01/2021


    declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

    declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);

// vvvvvvvvvvvvvvvvv Added for XG

    declgetvar("*", "Zdt", "(m)", &Zdt);

    declgetvar("*", "Zdf", "(m)", &Zdf);

    declgetvar("*", "Zd_front", "(m)", &Zd_front, &Zd_front_array);

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

/* Additions for snow cover fraction */
    declgetvar("*", "SWE", "(mm)", &SWE);
    declgetvar("*", "SWE_max", "(mm)", &SWE_max);

    declgetvar("*", "infil", "(mm/int)", &infil);

    snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

    runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

    meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);
}

void ClassSed_SoilX::init(void) {

    nhru = getdim(TDim::NHRU);

    if (snowinfilDiv > 1) {
        string S = "Soil:  \"snowinfil\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (evapDiv > 1) {
        string S = "Soil:  \"hru_evap\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (meltrunoffDiv > 1) {
        string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (runoffDiv > 1) {
        string S = "Netroute:  \"runoff\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    for (hh = 0; hh < nhru; ++hh) {

        if (soil_moist[hh] > soil_moist_max[hh]) {
            string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + to_string(hh + 1).c_str();
            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
            LogError(TExcept);
            throw TExcept;
        }

        if (soil_rechr[hh] > soil_rechr_max[hh]) {
            string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + to_string(hh + 1).c_str();
            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
            LogError(TExcept);
            throw TExcept;
        }

        if (soil_rechr_max[hh] > soil_moist_max[hh]) {
            string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + to_string(hh + 1).c_str();
            CRHMException TExcept(S.c_str(), TExcept::WARNING);
            LogError(TExcept);
            throw TExcept;
        }

        if (Sdinit[hh] > Sdmax[hh]) {
            string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + to_string(hh + 1).c_str();
            CRHMException Except(S.c_str(), TExcept::TERMINATE);
            LogError(Except);
            throw Except;
        }

        if (gw_init[hh] > gw_max[hh]) {
            string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + to_string(hh + 1).c_str();
            CRHMException Except(S.c_str(), TExcept::TERMINATE);
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
        cum_Sd_evap[hh] = 0.0;
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
        cum_Sd_gw[hh] = 0.0;
        cum_gw_flow[hh] = 0.0;

        cum_runoff_to_Sd[hh] = 0.0;


        for (long Sub = 0; Sub < numsubstances; ++Sub) {
            Sd_conc_lay[Sub][hh] = 0.0;
            redirected_residual_conc_lay[Sub][hh] = 0.0;
            soil_moist_conc_lay[Sub][hh] = 0.0;
            conc_soil_rechr_lay[Sub][hh] = 0.0;
            conc_soil_lower_lay[Sub][hh] = 0.0;
            gw_conc_lay[Sub][hh] = 0.0;
            soil_gw_conc_lay[Sub][hh] = 0.0;
            soil_ssr_conc_lay[Sub][hh] = 0.0;
            rechr_ssr_conc_lay[Sub][hh] = 0.0;
            soil_runoff_cWQ_lay[Sub][hh] = 0.0;
        }



        if (variation == VARIATION_1 || variation == VARIATION_2) {
            stream[hh] = 0.0; // must be here to reset all
            stream_Grp_in[hh] = 0.0; // must be here to reset all
            stream_Grp_loss[hh] = 0.0;
            cum_stream_Grp_loss[hh] = 0.0;
            soil_runoff_stream[hh] = 0.0;
        }

        if (variation == VARIATION_1) {
            if ((number_culverts[hh] > 0) && 
                            (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) ) {
                string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + to_string(hh + 1);
                CRHMException TExcept(S.c_str(), TExcept::WARNING);
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

        if (variation == VARIATION_2) {
            weir_outflow[hh] = 0.0;
            weir_outflow_m3s[hh] = 0.0;
            weir_water_A[hh] = 0.0;
            cum_weir_over_m3[hh] = 0.0;
            stream_to_Sd[hh] = 0.0;

            // find volume of weir pond at weir crest height.
            // iterate towards weir_crest_volume.

            double H;
            weir_crest_volume[hh] = 10.0; // (m3)
            H = pow(weir_crest_volume[hh] * (1.0 + 2.0 / lake_p[hh]) / lake_S[hh], 1.0 / (1.0 + 2.0 / lake_p[hh]));
            while (fabs(weir_crest[hh] - H) > 0.001) {
                weir_crest_volume[hh] += ((weir_crest[hh] - H) / weir_crest[hh] * weir_crest_volume[hh]);
                H = pow(weir_crest_volume[hh] * (1.0 + 2.0 / lake_p[hh]) / lake_S[hh], 1.0 / (1.0 + 2.0 / lake_p[hh]));
            } //while
        }

        // vvvvvvvvvvv    Additions for XG algorithm

        depth_layers_lay[0][hh] = soil_rechr_max[hh] / porosity_upper[hh] / 1000.0;
        depth_layers_lay[1][hh] = (soil_moist_max[hh] - soil_rechr_max[hh]) / porosity_lower[hh] / 1000.0;

        thaw_layers_lay[0][hh] = 1.0; // unfrozen
        thaw_layers_lay[1][hh] = 1.0; // unfrozen

        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    }
}

void ClassSed_SoilX::run(void) {

    double excs, condense;
    double et;
    double interval_secs = static_cast<double>(86400l) / Global::Freq;

    long nstep = getstep();
    current_getstep[0] = nstep;

    if (nstep == 1) {
        for (hh = 0; chkStruct(); ++hh) {
            LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (Soil)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (Soil)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
            LogDebug(" ");
            soil_moist_Init[hh] = soil_moist[hh];
            soil_rechr_Init[hh] = soil_rechr[hh];
            Sd_Init[hh] = Sd[hh];
            gw_Init[hh] = gw[hh];
        }
    }

    nstep = nstep % Global::Freq;

    if (variation == VARIATION_1 || variation == VARIATION_2) { // any difference is input from other sub-basin contributed by 'REW_route_stream' (ClassREWroute_stream)

        stream_Grp_loss[0] = stream[nhru - 1];
        cum_stream_Grp_loss[0] += stream_Grp_loss[0];

        for (hh = nhru - 1; hh > 0; --hh)
            stream[hh] = stream[hh - 1];

        stream[0] = 0.0;

        for (hh = 0; chkStruct(); ++hh) {
            stream[hh] = stream[hh] + stream_Grp_in[hh]; // stream equals this hru stream. stream_Grp_in is from REW_route_stream redirection from other group

        } // for
    }

    for (hh = 0; chkStruct(); ++hh) {

/* Additions for snow cover fraction */
        if (SWE[hh] > 0.0 && SWE_max[hh] > 0.0)
            scf[hh] = tanh(1.26 * SWE[hh] / (CV_SWE[hh] * SWE_max[hh]));
        else
            scf[hh] = 0.0;

        // Addition for XG because XG includes a second input to soil_runoff
        soil_runoff[hh] = 0.0;

        if (snowinfilDiv == 1) // interval value
            snowinfil_buf[hh] = snowinfil[hh];

        if (runoffDiv == 1) { // interval value
            runoff_buf[hh] = runoff[hh];

            if (variation == VARIATION_1) { // For culvert stream flow is put into complete soil module. For weir is put into depressional storage
                if (stream[hh] > 0.0 && stream_runoff[hh] > 0.0) {
                    runoff_buf[hh] += stream[hh - 1] * stream_runoff[hh] / hru_area[hh]; // convert to (mm/int)
                    stream[hh] = stream[hh] * (1.0 - stream_runoff[hh]); // volume (mm*km^2)
                }
            }
        }

        if (meltrunoffDiv == 1) // interval value
            meltrunoff_buf[hh] = meltrunoff[hh];

        if (evapDiv == 1) // interval value
            hru_evap_buf[hh] = hru_evap[hh];


        // vvvvvvvvvvv    Additions for XG algorithm

        if (nstep == 0) {

            for (long ll = 0; ll < depths_size; ++ll)
                if (NO_Freeze[hh])
                    thaw_layers_lay[ll][hh] = 1.0; // all unfrozen
                else
                    thaw_layers_lay[ll][hh] = 0.0; // all frozen

            if (soil_moist_max[hh] > 0.0 && !NO_Freeze[hh] && Zd_front_array[0][hh] > 0.0) {

                double layer_start = 0.0; // start of current layer
                double layer_end = 0.0; // end of current layer
                long ll = 0;

                while (ll < depths_size && Zdt[hh] > 0.0) {
                    layer_end += depth_layers_lay[ll][hh];
                    if (Zdt[hh] >= layer_end) { // frozen to bottom of layer
                        thaw_layers_lay[ll][hh] = 1.0; // all unfrozen
                        layer_start = layer_end;
                        ++ll;
                    }
                    else { // no
                        if (Zdt[hh] >= layer_start && Zdt[hh] < layer_end) { // in layer ?
                            thaw_layers_lay[ll][hh] = (Zdt[hh] - layer_start) / depth_layers_lay[ll][hh];
                            ++ll;
                            break;
                        }
                    } // else
                } // while ll
            }
        } // finished daily upgrade

        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


        if (nstep == 1) { // beginning of every day   // FIXME: is nstep = 0 or 1 at beggining of day? (PRL)
            soil_runoff_D[hh] = 0.0;
            soil_ssr_D[hh] = 0.0;
            soil_gw_D[hh] = 0.0;
            gw_flow_D[hh] = 0.0;
            infil_act_D[hh] = 0.0;
        }

        hru_actet[hh] = 0.0;
        infil_act[hh] = 0.0;
        soil_gw[hh] = 0.0;
        Sd_gw[hh] = 0.0;
        soil_ssr[hh] = 0.0;
        rechr_ssr[hh] = 0.0;

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

            double potential = infil[hh] + snowinfil_buf[hh] + condense;

            // vvvvvvvvvvv    Additions for XG algorithm

            double possible = thaw_layers_lay[0][hh] * (soil_rechr_max[hh] - soil_rechr[hh]);
            if ((!NO_Freeze[hh]) && (possible < potential)) {
                soil_runoff[hh] = potential - possible;
                potential = possible;
            }

            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

            soil_rechr[hh] = soil_rechr[hh] + potential;

            if (soil_rechr[hh] > soil_rechr_max[hh]) {
                excs = soil_rechr[hh] - soil_rechr_max[hh];
                soil_rechr[hh] = soil_rechr_max[hh];
                soil_lower[hh] = soil_lower[hh] + excs;
            }

            soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];

            if (soil_moist[hh] > soil_moist_max[hh]) {
                excs = soil_moist[hh] - soil_moist_max[hh];
                soil_moist[hh] = soil_moist_max[hh];
            }
            else
                excs = 0.0;

            infil_act[hh] = potential - excs;
            cum_infil_act[hh] += infil_act[hh];
            infil_act_D[hh] += infil_act[hh];

            //  Handle subsurface runoff

            if (!inhibit_evap[hh]) { // only when no snowcover
                rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;

                // vvvvvvvvvvv    Additions for XG algorithm

                if (rechr_ssr[hh] > soil_rechr[hh] * thaw_layers_lay[0][hh])
                    rechr_ssr[hh] = soil_rechr[hh] * thaw_layers_lay[0][hh];

                // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

                if (rechr_ssr[hh] > soil_rechr[hh])
                    rechr_ssr[hh] = soil_rechr[hh];

                soil_rechr[hh] -= rechr_ssr[hh];
                if (soil_rechr[hh] < 0.0)
                    soil_rechr[hh] = 0.0;

                soil_moist[hh] -= rechr_ssr[hh];
                soil_ssr[hh] = rechr_ssr[hh];
                cum_rechr_ssr[hh] += rechr_ssr[hh];
            }

            //****** Version without XG:
            // double s2gw_k = soil_gw_K[hh] / Global::Freq;
            //****** Modification for XG algorithm
            double s2gw_k = soil_gw_K[hh] / Global::Freq * thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer

            //  Handle excess to gw

            if (s2gw_k > 0.0)
                if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
                    soil_gw[hh] = s2gw_k;
                    excs -= s2gw_k;
                }
                else { // to gw
                    soil_gw[hh] = excs;
                    excs = 0.0;
                }

            //  Handle excess to interflow or runoff

            if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow
// Previous version:
            //  soil_ssr[hh] += direct_excs[hh];
              //  excs = 0.0;
// Modified for XG:
                soil_ssr[hh] += excs * thaw_layers_lay[1][hh];
                excs = excs * (1.0 - thaw_layers_lay[1][hh]);
            }
        }
        else { // soil_moist_max <= 0.0, i.e. Pond
            excs = infil[hh] + snowinfil_buf[hh] + condense;
        }

        double runoff_to_Sd = 0.0;

        // Previous version:
        //  soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int)
        // Modified for XG:
        soil_runoff[hh] += meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int)

        cum_redirected_residual[hh] += redirected_residual[hh];

        redirected_residual[hh] = 0;

        if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
            double Fix = -12.0;
            if (soil_runoff[hh] / Sdmax[hh] < 12.0)
                Fix = -soil_runoff[hh] / Sdmax[hh];
            double Ds = (Sdmax[hh] - Sd[hh]) * (1 - exp(Fix));

            if (soil_moist_max[hh] <= 0.0) // handle pond
                Ds = Sdmax[hh] - Sd[hh];

            if (Ds > 0.0) {
                if (soil_runoff[hh] > Ds) {
                    soil_runoff[hh] -= Ds;
                    if (soil_runoff[hh] < 0.0)
                        soil_runoff[hh] = 0.0;
                    Sd[hh] += Ds;
                    runoff_to_Sd += Ds;
                }
                else {
                    Sd[hh] += soil_runoff[hh];
                    runoff_to_Sd += soil_runoff[hh];
                    soil_runoff[hh] = 0.0;
                }
            }
        }

        if (variation == VARIATION_1) { // For culvert the soil_runoff is put into stream
            if ((soil_runoff[hh] > 0.0001 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
                double culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };
                culvert_water_H[hh] = 0.0;
                culvert_water_A[hh] = 0.0;
                culvert_over_Q[hh] = 0.0;
                culvert_Q[hh] = 0.0;
                culvert_evap[hh] = 0.0;
                culvert_water_V[hh] += soil_runoff[hh] * (hru_area[hh] * 1000.0); // convert mm to m3
                soil_runoff[hh] = 0.0;

                culvert_water_H[hh] = pow(3.0 * culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

                if (culvert_water_H[hh] > 0.0) {

                    // calculate overflow if culvert level exceeds Dmax

                    culvert_water_H[hh] = pow(3.0 * culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

                    if (culvert_water_H[hh] > culvert_water_Dmax[hh]) { // (m) overflow over road
                        culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
                        double maxVol = pow(culvert_water_Dmax[hh], 3.0) / (3.0 * channel_slope[hh] * side_slope[hh]); // (m3)

                        culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400.0 * Global::Freq; // (m3) to (m3/int)
                        culvert_water_V[hh] = maxVol; // (m3)

                        cum_culvert_over[hh] += culvert_over_Q[hh] * interval_secs; // (m3/s) to (m3)
                        soil_runoff[hh] += culvert_over_Q[hh] * interval_secs / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
                    }
                    HD[hh] = culvert_water_H[hh] / culvert_diam[hh];

                    // calculate flow through culvert

                    if (HD[hh] <= 0.0)
                        culvert_Q[hh] = 0.0;
                    else if (HD[hh] < 1.5)
                        culvert_Q[hh] = max <double>((-0.544443 * pow(HD[hh], 4.0) + 0.221892 * pow(HD[hh], 3.0) + 2.29756 * pow(HD[hh], 2.0)
                            + 0.159413 * HD[hh] + 0.00772254) * culvert_C[culvert_type[hh]] * number_culverts[hh] * pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
                    else
                        culvert_Q[hh] = culvert_C[culvert_type[hh]] * number_culverts[hh] * 0.785 * pow(culvert_diam[hh], 2.5) * sqrt(2.0 * 9.81 * (HD[hh] - 0.5));

                    if (culvert_water_V[hh] > culvert_Q[hh] * interval_secs) // (m3/s) to (m3))
                        culvert_water_V[hh] -= culvert_Q[hh] * interval_secs; // (m3/s) to (m3)
                    else {
                        culvert_Q[hh] = culvert_water_V[hh] / interval_secs;  // (m3) to (m3/s)
                        culvert_water_V[hh] = 0.0;
                    }

                    cum_culvert[hh] += culvert_Q[hh] * interval_secs; // (m3/s) to (m3/int)
                    soil_runoff[hh] += culvert_Q[hh] * interval_secs / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
                }
                culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (channel_slope[hh] * side_slope[hh]); // used for evaporation

                if (runoff_stream[hh] > 0.0 && soil_runoff[hh] > 0.0) { // do not put in last HRU
                    soil_runoff_stream[hh] = soil_runoff[hh] * runoff_stream[hh] * hru_area[hh]; // (mm*km^2/int)
                    stream[hh] += soil_runoff_stream[hh]; // (mm*km^2/int)
                    soil_runoff[hh] = soil_runoff[hh] * (1.0 - runoff_stream[hh]);
                }
            } // culvert addition
        }

        if (variation == VARIATION_2) {
            stream_to_Sd[hh] = 0.0;
            if (stream[hh] > 0.0001 && stream_Sd[hh] > 0.0001) { // For weir the stream flow is put into Sd
                double possible = stream[hh] * stream_Sd[hh] / hru_area[hh];
                if (Sd[hh] + possible > Sdmax[hh])
                    possible = Sdmax[hh] - Sd[hh];

                Sd[hh] += possible; // convert to (mm/int)
                stream_to_Sd[hh] = possible;

                stream[hh] = stream[hh] - possible * hru_area[hh]; // volume (mm*km^2)
            }

            if (weir_b[hh] > 0.0) { // soil_runoff already added to Sd
                if (Sd[hh] > 0.0) {
                    weir_water_V[hh] = Sd[hh] * hru_area[hh] * 1000; // (m3) hru_area - (km2) Sd - (mm)

                    weir_water_h[hh] = pow(weir_water_V[hh] * (1.0 + 2.0 / lake_p[hh]) / lake_S[hh], 1.0 / (1.0 + 2.0 / lake_p[hh]));

                    weir_water_A[hh] = lake_S[hh] * pow(weir_water_h[hh], 2.0 / lake_p[hh]); // surface area before any discarge

              // calculate outflow

                    double diff = weir_water_h[hh] - weir_crest[hh];

                    if (diff > 0.0) {

                        weir_outflow_m3s[hh] = weir_b[hh] * weir_mult[hh] * pow(diff, weir_coefficient[hh]); // (m3/s)

                        if (weir_outflow_m3s[hh] > (weir_water_V[hh] - weir_crest_volume[hh])) // less than crest height during strp

                            weir_outflow_m3s[hh] = (weir_water_V[hh] - weir_crest_volume[hh] / interval_secs);

                        cum_weir_over_m3[hh] += weir_outflow_m3s[hh]; // (m3)

                        weir_water_V[hh] -= weir_outflow_m3s[hh] * interval_secs; // (mm/int)

                        weir_outflow[hh] = weir_outflow_m3s[hh] * interval_secs; // (m3/s) to (m3)  hru_area - (km2) Sd - (mm)

                        Sd[hh] = Sd[hh] - weir_outflow[hh] / hru_area[hh] / 1000.0; // (mm)

                        weir_water_h[hh] = pow(weir_water_V[hh] * (1.0 + 2.0 / lake_p[hh]) / lake_S[hh], 1.0 / (1.0 + 2.0 / lake_p[hh]));

                        weir_water_A[hh] = lake_S[hh] * pow(weir_water_h[hh], 2.0 / lake_p[hh]); // surface area before any discarge

                        soil_runoff[hh] += weir_outflow[hh] / hru_area[hh] / 1000.0; // (m3/s) to (mm/int)

                    }
                    else {
                        weir_outflow[hh] = 0.0;
                        weir_outflow_m3s[hh] = 0.0;
                    }
                }
                else {
                    weir_water_V[hh] = 0.0;
                    weir_water_h[hh] = 0.0;
                    weir_water_A[hh] = 0.0;
                    weir_outflow[hh] = 0.0;
                    weir_outflow_m3s[hh] = 0.0;
                }
            } // weir defined

            if (runoff_stream[hh] > 0.0 && soil_runoff[hh] > 0.0) {
                soil_runoff_stream[hh] = soil_runoff[hh] * runoff_stream[hh] * hru_area[hh]; // (mm*km^2/int)
                stream[hh] += soil_runoff_stream[hh]; // (mm*km^2/int)
                soil_runoff[hh] = soil_runoff[hh] * (1.0 - runoff_stream[hh]);
            }
        } // weir addition

        soil_runoff_D[hh] += soil_runoff[hh];
        cum_soil_runoff[hh] += soil_runoff[hh];
        cum_runoff_to_Sd[hh] += runoff_to_Sd;

        if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
            double Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
            if (Sd2gw_k > Sd[hh])
                Sd2gw_k = Sd[hh];
            //      soil_gw[hh] += Sd2gw_k;
            Sd_gw[hh] += Sd2gw_k;
            Sd[hh] -= Sd2gw_k;
            if (Sd[hh] < 0.0)
                Sd[hh] = 0.0;
        }

        soil_gw_D[hh] += soil_gw[hh];
        cum_soil_gw[hh] += soil_gw[hh];
        cum_Sd_gw[hh] += Sd_gw[hh];

        gw[hh] += (soil_gw[hh] + Sd_gw[hh]);
        gw_flow[hh] = 0.0;
        if (gw[hh] > gw_max[hh]) {
            gw_flow[hh] += (gw[hh] - gw_max[hh]);
            gw[hh] = gw_max[hh];
        }

        if (gw_max[hh] > 0.0) { // prevents divide by zero error
            double spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
            gw[hh] -= spill;
            gw_flow[hh] += spill;
        }

        gw_flow_D[hh] += gw_flow[hh];
        cum_gw_flow[hh] += gw_flow[hh];

        if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
            double Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
            if (Sd2ssr_k >= Sd[hh])
                Sd2ssr_k = Sd[hh];
            soil_ssr[hh] += Sd2ssr_k;
            Sd[hh] -= Sd2ssr_k;
            if (Sd[hh] < 0.0)
                Sd[hh] = 0.0;
        }

        // Previous version:
        //  double s2ssr_k = lower_ssr_K[hh] / Global::Freq;
        // Modified for XG:
        double s2ssr_k = lower_ssr_K[hh] / Global::Freq * thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer

        if (s2ssr_k > 0.0) {
            double avail = soil_moist[hh] - soil_rechr[hh];
            if (s2ssr_k >= avail)
                s2ssr_k = avail;
            soil_moist[hh] -= s2ssr_k;
            soil_ssr[hh] += s2ssr_k;
        }

        cum_soil_ssr[hh] += soil_ssr[hh];
        soil_ssr_D[hh] += soil_ssr[hh];

        //******Compute actual evapotranspiration

        double culvert_evapL = 0;
        double culvert_pond = 0;

        if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation

            culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
            culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

            if (culvert_evapL > culvert_pond) // limit to amount available
                culvert_evapL = culvert_pond;

            culvert_evap[hh] = culvert_evapL;
            hru_actet[hh] += culvert_evapL;
            culvert_water_V[hh] = (culvert_pond - culvert_evapL) * (hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
        }

        double weir_evapL = 0;
        double weir_pond = 0;

        if (variation == VARIATION_2 && weir_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation

            weir_pond = weir_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
            weir_evapL = hru_evap_buf[hh] * weir_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

            if (weir_evapL > weir_pond) // limit to amount available
                weir_evapL = weir_pond;

            weir_evap[hh] = weir_evapL;
            hru_actet[hh] += weir_evapL;
            weir_water_V[hh] = (weir_pond - weir_evapL) * (hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
        }

        double avail_evap = hru_evap_buf[hh] - culvert_evapL - weir_evapL;

        if (Sd[hh] + soil_moist[hh] + weir_pond > 0.0) {
            if (Wetlands_scaling_factor[hh] < 0.0)
                avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
            else
                avail_evap *= Wetlands_scaling_factor[hh];
        }
        else
            avail_evap = 0.0;

        if (Sd[hh] > 0.0 && avail_evap > 0.0) {
            if (Sd[hh] >= avail_evap) {
                Sd[hh] -= avail_evap;
                if (Sd[hh] < 0.0)
                    Sd[hh] = 0.0;
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

            double pctl, pctr, etl, etr;
            //double ets; varible is unreferenced commenting out for now - jhs507

            if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
                pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
            else
                pctl = 0.0;

            pctr = soil_rechr[hh] / soil_rechr_max[hh];

            etr = avail_evap; // default

            switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
            case 1: //******sandy soil
                if (pctr < 0.25)
                    etr = 0.5 * pctr * avail_evap;
                break;
            case 2: //******loam soil
                if (pctr < 0.5)
                    etr = pctr * avail_evap;
                break;
            case 3: //******clay soil
                if (pctr <= 0.33)
                    etr = 0.5 * pctr * avail_evap;
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
                    etl = 0.5 * pctl * etl;
                break;
            case 2: //******loam soil
                if (pctl < 0.5)
                    etl = pctl * etl;
                break;
            case 3: //******clay soil
                if (pctl <= 0.33)
                    etl = 0.5 * pctl * etl;
                else if (pctr < 0.67)
                    etl = pctl * etl;
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

            if (transp_limited[hh] == 1 && et_type == 2)
                et_type = 1;

            et = 0.0;

            switch (et_type) {  // handle evaporation
            case 0: case -1:  // avail_evap <= 0
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

        soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];

    } // for

    if (variation == VARIATION_1 || variation == VARIATION_2) { // advance stream flow to next HRU

        for (hh = 0; chkStruct(); ++hh) {
            stream_Grp_in[hh] = 0.0;
            cum_stream[hh] += stream[hh];
        }
    }
}

void ClassSed_SoilX::finish(bool good) {

    double Allcum_soil_runoff = 0.0;
    double Allcum_soil_ssr = 0.0;
    double Allcum_rechr_ssr = 0.0;
    double Allcum_soil_gw = 0.0;
    double Allcum_gw_flow = 0.0;
    double Allcum_infil_act = 0.0;
    double Allcum_soil_moist_change = 0.0;
    double Allcum_Sd_change = 0.0;
    double Allcum_gw_change = 0.0;
    double Allcum_stream_Grp_loss = 0.0;

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_Sd_evap        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_evap[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'hru_actet'.");
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_Sd_gw          (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
        LogMessageA(hh, string("'" + Name + " (Soil)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
        LogDebug(" ");

        if (variation == VARIATION_1) {
            LogMessageA(hh, string("'" + Name + " (Soil)' cum_culvert         (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (Soil)' cum_culvert_over    (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
            LogDebug(" ");
        }

        if (variation == VARIATION_1 || variation == VARIATION_2) {
            LogMessageA(hh, string("'" + Name + " (Soil)' cum_stream          (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_stream[hh], hru_area[hh], basin_area[0]);
            LogDebug(" ");
        }

        Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
        Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
        Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
        Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
        Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
        Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
        Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh]) * hru_area[hh];
        Allcum_Sd_change += (Sd[hh] - Sd_Init[hh]) * hru_area[hh];
        Allcum_gw_change += (gw[hh] - gw_Init[hh]) * hru_area[hh];

        if (variation == VARIATION_1 || variation == VARIATION_2) {
            Allcum_stream_Grp_loss += cum_stream[hh];
        }

        if (variation == VARIATION_1 || variation == VARIATION_2)
            LogMessage(string("'" + Name + " (Soil)' Allcum_stream_Grp_loss (mm*basin): ").c_str(), Allcum_stream_Grp_loss);

        LogDebug(" ");
    } // hh

    LogMessage(string("'" + Name + " (Soil)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
    LogMessage(string("'" + Name + " (Soil)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
    LogMessage(string("'" + Name + " (Soil)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
    LogMessage(string("'" + Name + " (Soil)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
    LogMessage(string("'" + Name + " (Soil)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
    LogMessage(string("'" + Name + " (Soil)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
    LogMessage(string("'" + Name + " (Soil)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
    LogMessage(string("'" + Name + " (Soil)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
    LogMessage(string("'" + Name + " (Soil)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
    LogDebug(" ");
}
