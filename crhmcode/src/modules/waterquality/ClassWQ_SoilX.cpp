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
#include "ClassWQ_SoilX.h"

const long i_pp = 5; // particulate phosphorus

ClassWQ_SoilX* ClassWQ_SoilX::klone(string name) const {
    return new ClassWQ_SoilX(name);
}

void ClassWQ_SoilX::decl(void) {

    Description = "'Handles soil moisture throughout the year.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.' \
                 'Version with Tile drainage calculated ssr.'";

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

    declparam("channel_slope", TDim::NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

    declparam("side_slope", TDim::NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

    declparam("culvert_diam", TDim::NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

    declparam("culvert_water_Dmax", TDim::NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

    declparam("number_culverts", TDim::NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

    declparam("culvert_type", TDim::NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


    variation_set = VARIATION_2;

    declvar("tile_flow", TDim::NHRU, "flow in tile drainage.", "(m^3/s)", &tile_flow);

    declvar("tile_flow_conc", TDim::NDEFN, "Concentration: tile flow.", "(mg/l)", &tile_flow_conc, &tile_flow_conc_lay, numsubstances);

    declvar("Dequiv_depth", TDim::NHRU, "closed-form expression for equivalent depth.", "(m)", &Dequiv_depth);

    declvar("x", TDim::NHRU, ".", "(m)", &x);

    declvar("Dw", TDim::NHRU, "steady state depth of the watertable midway between the drain.", "(m)", &Dw);

    declparam("Ka", TDim::NHRU, "[1]", "0.1", "4", "hydraulic conductivity of the soil above drain level.", "(m/d)", &Ka);

    declparam("Kb", TDim::NHRU, "[1]", "0.1", "4", "hydraulic conductivity of the soil below drain level.", "(m/d)", &Kb);

    declparam("Di", TDim::NHRU, "[2]", "0", "10", "depth of the impermeable layer below drain level.", "(m)", &Di);

    declparam("Dd", TDim::NHRU, "[0.5]", "0", "4", "depth of drains.", "(m)", &Dd);

    declparam("soil_poro_moist", TDim::NHRU, "[0.5]", "0", "1", "soil porosity of moist layer.", "()", &soil_poro_moist);

    declparam("L", TDim::NHRU, "[2]", "0", "20", "spacing between drains.", "(m)", &L);

    declparam("r", TDim::NHRU, "[0.1]", "0.01", "1", "drain radius.", "(m)", &r);


    variation_set = VARIATION_ORG;

    if (Global::nlay < 2) {
        Global::nlay = 2;
        Global::maxlay = 2;
    }

    declvar("current_getstep", TDim::BASIN, "current getstep", "()", &current_getstep);

    declvar("redirected_residual", TDim::NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

    declvar("redirected_residual_conc", TDim::NDEFN, "Concentration:: redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mg/l)", &redirected_residual_conc, &redirected_residual_conc_lay, numsubstances);

    declstatdiag("cum_redirected_residual", TDim::NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

    declstatdiag("cum_redirected_residual_mWQ", TDim::NDEFN, "mass of solute redirected_residual to another HRU.", "(mg/l * mm*km^2/int)", &cum_redirected_residual_mWQ, &cum_redirected_residual_mWQ_lay, numsubstances);

    declstatvar("Sd", TDim::NHRU, "Depression storage.", "(mm)", &Sd);

    declstatvar("Sd_conc", TDim::NDEFN, "Concentration: Depression storage.", "(mg/l)", &Sd_conc, &Sd_conc_lay, numsubstances);

    declstatvar("gw", TDim::NHRU, "ground water storage.", "(mm)", &gw);

    declstatvar("gw_conc", TDim::NDEFN, "Concentration: ground water storage.", "(mg/l)", &gw_conc, &gw_conc_lay, numsubstances);

    declvar("solute_deposit", TDim::NHRU, "solute deposit left by evaporation.", "(mg)", &solute_deposit);

    declstatvar("cum_solute_deposit", TDim::NHRU, "cumulative solute deposit left by evaporation.", "(mg)", &cum_solute_deposit);

    declstatvar("soil_rechr", TDim::NHRU, "moisture content of soil recharge zone, ie, the"//
        "portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

    declstatvar("soil_moist", TDim::NHRU, "moisture content of soil profile to the depth"//
        "of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

    declstatvar("soil_moist_conc", TDim::NDEFN, "Concentration: moisture content of soil profile to the depth.", "(mg/l)", &soil_moist_conc, &soil_moist_conc_lay, numsubstances);

    declstatvar("potential", TDim::NHRU, ".", "(mm)", &potential);

    declstatvar("direct_excs", TDim::NHRU, ".", "(mm)", &direct_excs);

    declstatvar("potential_mWQ", TDim::NDEFN, ".", "(mg/l * mm*km^2/int)", &potential_mWQ, &potential_mWQ_lay, numsubstances);

    declstatvar("direct_excs_mWQ", TDim::NDEFN, ".", "(mg/l * mm*km^2/int)", &direct_excs_mWQ, &direct_excs_mWQ_lay, numsubstances);

    declstatvar("soil_lower_max", TDim::NHRU, "maximum moisture content of lower soil profile to the depth"//
        "of the rooting zone of the major vegetation type on the HRU. (N.B. not Hype lower layer)", "(mm)", &soil_lower_max);

    declstatvar("soil_lower", TDim::NHRU, "moisture content of lower soil profile to the depth"//
        "of the rooting zone of the major vegetation type on the HRU. (N.B. not Hype lower layer)", "(mm)", &soil_lower);

    decllocal("cum_hru_condense", TDim::NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

    declvar("cum_Sd_evap", TDim::NHRU, "cumulative Sd evaporation(included in hru_actet).", "(mm)", &cum_Sd_evap);

    declstatvar("cum_Sd_ssr", TDim::NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_Sd_ssr);

    declstatvar("cum_Sd_gw", TDim::NHRU, "Accumulation of Sd excess from a HRU to gw.", "(mm)", &cum_Sd_gw);

    declstatvar("cum_lower_ssr", TDim::NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_lower_ssr);

// vvvvvvvvvvv    Additions for XG algorithm
    declvar("depth_layers", TDim::NDEFN, "thickness of soil layer.", "(m)", &depth_layers, &depth_layers_lay, depths_size);

    declvar("thaw_layers", TDim::NDEFN, "fraction of layer thawed.", "()", &thaw_layers, &thaw_layers_lay, depths_size);
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    declvar("soil_gw", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

    declvar("soil_gw_conc", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mg/l)", &soil_gw_conc, &soil_gw_conc_lay, numsubstances);

    declvar("soil_gw_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

    declvar("gw_flow", TDim::NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

    declvar("gw_flow_conc", TDim::NDEFN, "Concentration: Drainage from HRU ground water reservoir.", "(mg/l)", &gw_flow_conc, &gw_flow_conc_lay, numsubstances);

    declvar("gw_flow_D", TDim::NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

    declvar("infil_act", TDim::NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

    declvar("infil_act_conc", TDim::NDEFN, "Concentration: Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act_conc, &infil_act_conc_lay, numsubstances);

    declvar("cum_infil_act", TDim::NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

    declvar("cum_infil_act_mWQ", TDim::NDEFN, "mass of solute infiltrating the soil on each HRU.", "(mg/l * mm*km^2/int)", &cum_infil_act_mWQ, &cum_infil_act_mWQ_lay, numsubstances);

    declvar("infil_act_D", TDim::NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

    declstatvar("cum_gw_flow", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

    declstatvar("cum_gw_flow_mWQ", TDim::NDEFN, "mass of solute from a HRU that enters groundwater reservoirs.", "(mg/l * mm*km^2/int)", &cum_gw_flow_mWQ, &cum_gw_flow_mWQ_lay, numsubstances);

    declvar("soil_ssr", TDim::NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

    declvar("soil_ssr_conc", TDim::NDEFN, "Concentration: Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mg/l)", &soil_ssr_conc, &soil_ssr_conc_lay, numsubstances);

    declvar("rechr_ssr", TDim::NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

    declvar("rechr_ssr_conc", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mg/l)", &rechr_ssr_conc, &rechr_ssr_conc_lay, numsubstances);

    declvar("scf", TDim::NHRU, "Snow-cover fraction calculated from snow-cover depletion curves(Essery&Pomeroy,2004).", "()", &scf);

    declstatvar("cum_soil_ssr", TDim::NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

    declstatvar("cum_soil_ssr_mWQ", TDim::NDEFN, "mass of solute from a HRU to ssr.", "(mg/l * mm*km^2/int)", &cum_soil_ssr_mWQ, &cum_soil_ssr_mWQ_lay, numsubstances);

    declstatvar("cum_rechr_ssr", TDim::NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

    declstatvar("cum_rechr_ssr_mWQ", TDim::NDEFN, "mass of solute portion of excess from a HRU to ssr.", "(mg/l * mm*km^2/int)", &cum_rechr_ssr_mWQ, &cum_rechr_ssr_mWQ_lay, numsubstances);

    declvar("soil_ssr_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

    declvar("soil_runoff", TDim::NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

    declvar("soil_runoff_cWQ", TDim::NDEFN, "Concentration: Portion of excess soil water from a HRU to runoff.", "()", &soil_runoff_cWQ, &soil_runoff_cWQ_lay, numsubstances);
    declparam("P_is_sediment", TDim::BASIN, "[1]", "0", "1", "Output sediment in the Phosphorus channel", "()", &P_is_sediment);

    declstatvar("cum_soil_runoff", TDim::NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

    declstatvar("cum_soil_runoff_mWQ", TDim::NDEFN, "mass of solute of portion of excess soil water from a HRU to runoff.", "(mg/l * mm*km^2/int)", &cum_soil_runoff_mWQ, &cum_soil_runoff_mWQ_lay, numsubstances);

    declvar("soil_runoff_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

    declstatvar("cum_runoff_to_Sd", TDim::NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

    declstatvar("cum_runoff_to_Sd_mWQ", TDim::NDEFN, "mass of solute portion of runoff to depression storage.", "(mg/l * mm*km^2/int)", &cum_runoff_to_Sd_mWQ, &cum_runoff_to_Sd_mWQ_lay, numsubstances);

    declstatvar("cum_runoff_to_ssr", TDim::NHRU, "Cumulative portion of runoff to interflow(ssr).", "(mm/int)", &cum_runoff_to_ssr);

    declstatvar("cum_soil_gw", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);

    declstatvar("cum_soil_gw_mWQ", TDim::NDEFN, "mass of solute of excess soil water from a HRU that enters groundwater reservoirs.", "(mg/l * mm*km^2/int)", &cum_soil_gw_mWQ, &cum_soil_gw_mWQ_lay, numsubstances);

    decllocal("snowinfil_buf", TDim::NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

    decllocal("runoff_buf", TDim::NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

    decllocal("meltrunoff_buf", TDim::NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

    decllocal("hru_evap_buf", TDim::NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

    decllocal("soil_rechr_Init", TDim::NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

    decllocal("soil_moist_Init", TDim::NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

    decllocal("soil_bottom_Init", TDim::NHRU, "initial bottom soil moisture.", "(mm)", &soil_bottom_Init);

    decllocal("Sd_Init", TDim::NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

    decllocal("gw_Init", TDim::NHRU, "initial ground water storage.", "(mm)", &gw_Init);

    declvar("soil_moist_conc_Init", TDim::NDEFN, "initial soil moisture conc.", "(mg/l)", &soil_moist_conc_Init, &soil_moist_conc_Init_lay, numsubstances);

    declvar("soil_bottom_conc_Init", TDim::NDEFN, "initial bottom soil moisture conc.", "(mg/l)", &soil_bottom_conc_Init, &soil_bottom_conc_Init_lay, numsubstances);

    declvar("soil_top_conc_Init", TDim::NDEFN, "initial top soil moisture conc.", "(mg/l)", &soil_top_conc_Init, &soil_top_conc_Init_lay, numsubstances);

    declvar("Sd_conc_Init", TDim::NDEFN, "initial concentration of nutrient species “layer” in the initial depression storage.", "(mg/l)", &Sd_conc_Init, &Sd_conc_Init_lay, numsubstances);

    declvar("gw_conc_Init", TDim::NDEFN, "initial concentration of nutrient species “layer”  in the groundwater reservoir.", "(mg/l)", &gw_conc_Init, &gw_conc_Init_lay, numsubstances);

    declparam("calcN", TDim::NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);

    declparam("calcP", TDim::NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);

    declparam("calcC", TDim::NHRU, "[0]", "0", "1", "flag for carbon simulation", "()", &calcC);

    declparam("sr_mix_rate", TDim::NHRU, "[0.01]", "0", "1", "Soil-runoff nutrient mass mixing rate.", "(1/int)", &sr_mix_rate);

    declparam("parleach", TDim::NHRU, "[1]", "0", "1", "Leaching from surfsoil to soil_rechr", "(1/T)", &parleach);

    declparam("CV_SWE", TDim::NHRU, "[1]", "0", "1", "Coefficient of variation: values can be taken from Gray, D. M., Toth, B., Zhao, L., Pomeroy, J. W., & Granger, R. J. (2001). Estimating areal snowmelt infiltration into frozen soils. Hydrological Processes, 15(16), 3095–3111. https://doi.org/10.1002/hyp.320", "()", &CV_SWE);

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

    declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

    declparam("Sdinit", TDim::NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

    declparam("Sd_conc_init", TDim::NDEFN, "[0]", "0.0", "10.0", "Initial depression storage.", "(mg/l)", &Sd_conc_init, &Sd_conc_init_lay, numsubstances);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
        "and transpiration).  Must be less than or equal to soil_moist.", "( )", &soil_rechr_max);

    declparam("soil_rechr_init", TDim::NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
        "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

    declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

    declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "5000.0",
        "Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

    declparam("soil_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
        "that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

    declparam("gw_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

    declparam("gw_init", TDim::NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

    declparam("gw_conc_init", TDim::NDEFN, "[1]", "0.0", "1.0", "Initial value of available water in ground water reservoir.", "(mg/l)", &gw_conc_init, &gw_conc_init_lay, numsubstances);

    declparam("gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

    declparam("rechr_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

    declparam("lower_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

    declparam("Sd_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

    declparam("Sd_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

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

    declparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit.", "()", &inhibit_evap);

    declparam("rain_conc", TDim::NDEFN, "0", "0", "1000", "rain solute concentration", "(mg/l)", &rain_conc, &rain_conc_lay, numsubstances);

    declparam("atmos_mWQ", TDim::NDEFN, "0", "0", "3", "atmospheric solute deposit", "(mg/int)", &atmos_mWQ, &atmos_mWQ_lay, numsubstances);

    declparam("soil_withdrawal", TDim::NDEFN, "[3]", "1", "4",
        "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
        &soil_withdrawal, &soil_withdrawal_Tables, 2);

    declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

    declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);

// vvvvvvvvvvvvvvvvv Added for XG

    declgetvar("*", "Zdt", "(m)", &Zdt);

    declgetvar("*", "Zdf", "(m)", &Zdf);

    declgetvar("*", "Zd_front", "(m)", &Zd_front, &Zd_front_array);

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

    declgetvar("*", "SWE", "(mm)", &SWE);

    declgetvar("*", "SWE_max", "(mm)", &SWE_max);

    declgetvar("*", "SWE_conc", "(mg/l)", &SWE_conc, &SWE_conc_lay);

    declputvar("*", "conc_soil_rechr", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay);

    declputvar("*", "surfsoil_solub_mWQ", "(mg/l)", &surfsoil_solub_mWQ, &surfsoil_solub_mWQ_lay);

    declputvar("*", "conc_soil_lower", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay);

    //declstatvar("*", "conc_soil_moist", "(mg/l)", &conc_soil_moist, &conc_soil_moist_lay);

    declstatvar("conc_soil_moist", TDim::NDEFN, "concentration in soil_moist: (i_no3n=0) NO3-N, (i_nh4n=1) NH4-1, (i_don=2) DON, "
        "(i_srp=3) SRP, (i_dop=4) DOP, (i_pp=5) PP, (i_oc=6) OC", "(mg/l)", &conc_soil_moist, &conc_soil_moist_lay, numsubstances);

    declgetvar("*", "infil", "(mm/int)", &infil);

    snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

    runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

    meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);

    decllocal("redirected_residual_0", TDim::NHRU, "", "", &redirected_residual_0);

    decllocal("Sd_0", TDim::NHRU, "Depression storage.", "(mm)", &Sd_0);

    decllocal("gw_0", TDim::NHRU, "ground water storage.", "(mm)", &gw_0);

    decllocal("soil_rechr_0", TDim::NHRU, "moisture content of soil recharge zone.", "(mm)", &soil_rechr_0);

    decllocal("soil_moist_0", TDim::NHRU, "moisture content of soil profile to the depth.", "(mm)", &soil_moist_0);

    decllocal("soil_lower_0", TDim::NHRU, "moisture content of soil profile to the depth.", "(mm)", &soil_lower_0);

    decllocal("gw_flow_0", TDim::NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow_0);

    decllocal("hru_cum_actet_0", TDim::NHRU, "cumulative saved evaporation.", "(mm*km^2)", &hru_cum_actet_0);

    decllocal("cum_soil_runoff_0", TDim::NHRU, "cumulative saved runoff.", "(mm*km^2)", &cum_soil_runoff_0);

    decllocal("cum_redirected_residual_0", TDim::NHRU, "cumulative saved redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual_0);

    decllocal("cum_soil_ssr_0", TDim::NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr_0);

    decllocal("cum_rechr_ssr_0", TDim::NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr_0);

    decllocal("hru_actet_0", TDim::NDEFN, "", "(mm/int)", &hru_actet_0);

    decllocal("cum_hru_condense_0", TDim::NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense_0);

    decllocal("cum_Sd_evap_0", TDim::NHRU, "cumulative Sd evaporation(included in hru_actet).", "(mm)", &cum_Sd_evap_0);

    decllocal("cum_Sd_ssr_0", TDim::NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_Sd_ssr_0);

    declstatvar("cum_Sd_gw_0", TDim::NHRU, "Accumulation of Sd excess from a HRU to gw.", "(mm)", &cum_Sd_gw_0);

    decllocal("cum_lower_ssr_0", TDim::NHRU, "Accumulation of Sd excess from a HRU to ssr.", "(mm)", &cum_lower_ssr_0);

    decllocal("cum_infil_act_0", TDim::NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act_0);

    decllocal("cum_gw_flow_0", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow_0);

    decllocal("cum_soil_runoff_0", TDim::NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff_0);

    decllocal("cum_runoff_to_Sd_0", TDim::NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd_0);

    decllocal("cum_runoff_to_ssr_0", TDim::NHRU, "Cumulative portion of runoff to interflow(ssr).", "(mm/int)", &cum_runoff_to_ssr_0);

    decllocal("cum_soil_gw_0", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw_0);

    decllocal("cum_solute_deposit_0", TDim::NHRU, "cumulative solute deposit left by evaporation.", "(mg)", &cum_solute_deposit_0);

}

void ClassWQ_SoilX::init(void) {

    if (Global::nlay < numsubstances) {
        Global::nlay = numsubstances;
        Global::maxlay = numsubstances;
    }

    FaultsAllowed = 0;
    nhru = getdim(TDim::NHRU);
    nlay = getdim(TDim::NLAY);

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

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        for (hh = 0; hh < nhru; ++hh) {
            if (Sub == 0) {
                soil_rechr[hh] = soil_rechr_init[hh];
                soil_moist[hh] = soil_moist_init[hh];

                soil_lower_max[hh] = soil_moist_max[hh] - soil_rechr_max[hh];
                soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];

                soil_moist_conc_lay[Sub][hh] = 0.0;

                solute_deposit[hh] = 0.0;
                cum_solute_deposit[hh] = 0.0;

                soil_runoff_D[hh] = 0.0;
                soil_ssr_D[hh] = 0.0;
                soil_gw_D[hh] = 0.0;
                gw_flow_D[hh] = 0.0;
                infil_act_D[hh] = 0.0;

                hru_cum_actet[hh] = 0.0;
                cum_hru_condense[hh] = 0.0;
                cum_Sd_evap[hh] = 0.0;

                cum_Sd_ssr[hh] = 0.0;
                cum_Sd_gw[hh] = 0.0;
                cum_lower_ssr[hh] = 0.0;
                cum_runoff_to_ssr[hh] = 0.0;

                if (soil_rechr[hh] > soil_moist[hh]) {
                    soil_rechr[hh] = soil_moist[hh];
                    string S = string("'") + Name + " (Soil)' Soil_rechr greater than soil_moist, soil_rechr set to soil_moist, hru = " + to_string(hh).c_str();
                    CRHMException TExcept(S.c_str(), TExcept::WARNING);
                    LogError(TExcept);
                    // Exceptions should not be thrown for just a warning (PRL)
//                    throw TExcept;
                }

                if (soil_rechr_max[hh] > soil_moist_max[hh]) {
                    string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + to_string(hh + 1).c_str();
                    CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
                    LogError(TExcept);
                    throw TExcept;
                }

                if (Sdinit[hh] > Sdmax[hh]) {
                    string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + to_string(hh + 1).c_str();
                    CRHMException Except(S.c_str(), TExcept::TERMINATE);
                    LogError(Except);
                    throw Except;
                }

                if (variation == VARIATION_1) {
                    if (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) {
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
                    tile_flow[hh] = 0.0;
                    tile_flow_conc_lay[Sub][hh] = 0.0;
                    x[hh] = 2.0 * M_PI * (Di[hh] - Dd[hh]) / L[hh];
                    Dequiv_depth[hh] = M_PI * L[hh] / 8.0 * (M_PI * log(L[hh] / (r[hh])) + FunctX(x[hh]));
                    Dw[hh] = soil_moist_init[hh] / soil_poro_moist[hh];
                }

                // vvvvvvvvvvv    Additions for XG algorithm

                depth_layers_lay[0][hh] = soil_rechr_max[hh] / porosity_upper[hh] / 1000.0;
                depth_layers_lay[1][hh] = (soil_moist_max[hh] - soil_rechr_max[hh]) / porosity_lower[hh] / 1000.0;

                thaw_layers_lay[0][hh] = 1.0; // unfrozen
                thaw_layers_lay[1][hh] = 1.0; // unfrozen

                // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

            } // if Sub == 0

            Reset_WQ(hh, infil_act, infil_act_conc_lay[Sub]);

            Reset_WQ(hh, redirected_residual, redirected_residual_conc_lay[Sub]);
            Reset_WQ(hh, cum_redirected_residual, cum_redirected_residual_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_infil_act, cum_infil_act_mWQ_lay[Sub]);


            Reset_WQ(hh, cum_soil_runoff, cum_soil_runoff_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_soil_ssr, cum_soil_ssr_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_rechr_ssr, cum_rechr_ssr_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_soil_gw, cum_soil_gw_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_gw_flow, cum_gw_flow_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_runoff_to_Sd, cum_runoff_to_Sd_mWQ_lay[Sub]);
            Reset_WQ(hh, cum_runoff_to_Sd, cum_runoff_to_Sd_mWQ_lay[Sub]);

            Set_WQ(hh, Sd, Sd_conc_lay[Sub], Sdinit[hh], Sd_conc_init_lay[Sub][hh]);
            Set_WQ(hh, gw, gw_conc_lay[Sub], gw_init[hh], gw_conc_init_lay[Sub][hh]);
        } // hh
    } // Sub

}

void ClassWQ_SoilX::run(void) {

    try {
        double excs, excs_mWQ, condense, et, direct_excs_Saved{ 0.0 }, direct_excs_mWQ_lay_Saved{ 0.0 }, potential_Saved, potential_mWQ_lay_Saved,
            leaching_mWQ;

        long step = getstep();
        current_getstep[0] = step;
        long nstep = step % Global::Freq;

        for (long Sub = 0; Sub < numsubstances; ++Sub) {

            if (Sub == 0) // saves all HRUs, non WQ variables the first time
                Save();

            if (step == 1) { // First Time only
                string S = string("Initial Substance# ") + to_string(Sub + 1);
                LogDebug(S.c_str());
                LogMessage(" ");

                for (hh = 0; chkStruct(); ++hh) {
                    soil_top_conc_Init_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh];
                    soil_bottom_conc_Init_lay[Sub][hh] = conc_soil_lower_lay[Sub][hh];
                    if (soil_rechr[hh] + soil_lower[hh] > 0.0)
                        soil_moist_conc_Init_lay[Sub][hh] = (soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh] + soil_lower[hh] * conc_soil_lower_lay[Sub][hh]) / (soil_rechr[hh] + soil_lower[hh]); // mg/l
                    else
                        soil_moist_conc_Init_lay[Sub][hh] = 0.0; // mg/l

                    soil_moist_Init[hh] = soil_moist[hh];
                    soil_rechr_Init[hh] = soil_rechr[hh];

                    Sd_Init[hh] = Sd[hh];
                    Sd_conc_Init_lay[Sub][hh] = Sd_conc_lay[Sub][hh];

                    gw_Init[hh] = gw[hh];
                    gw_conc_Init_lay[Sub][hh] = gw_conc_lay[Sub][hh];

                    // soil_rechr_conc, soil_lower_conc and soil_moist_conc use the Hype initial values

                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_init_conc     (mm) (mm*hru) (mm*hru/basin): ").c_str(), conc_soil_rechr_lay[Sub][hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_init_conc     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist_conc_Init_lay[Sub][hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_lower_init_conc     (mm) (mm*hru) (mm*hru/basin): ").c_str(), conc_soil_lower_lay[Sub][hh], hru_area[hh], basin_area[0]);

                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sdinit              (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Sd_init_conc             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd_conc_lay[Sub][hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
                    LogMessageA(hh, string("'" + Name + " (Soil_WQ)' gw_init_conc             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw_conc_lay[Sub][hh], hru_area[hh], basin_area[0]);
                    LogDebug(" ");
                } // for
            } // if step == 1

            for (hh = 0; chkStruct(); ++hh) {

                if (Sub != 0)
                    Restore(hh);

                if (snowinfilDiv == 1) // interval value
                    snowinfil_buf[hh] = snowinfil[hh];

                if (runoffDiv == 1) // interval value
                    runoff_buf[hh] = runoff[hh];

                if (meltrunoffDiv == 1) // interval value
                    meltrunoff_buf[hh] = meltrunoff[hh];

                if (evapDiv == 1) // interval value
                    hru_evap_buf[hh] = hru_evap[hh];

                // vvvvvvvvvvv    Additions for XG algorithm

                if ((Sub == 0) && (nstep == 0)) {

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


                //      if(nstep == 1){ // beginning of every day

                // update for WQ

                if (soil_rechr[hh] + soil_lower[hh] > 0.0)
                    soil_moist_conc_lay[Sub][hh] = (soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh] + soil_lower[hh] * conc_soil_lower_lay[Sub][hh]) / (soil_rechr[hh] + soil_lower[hh]); // mg/l
                else
                    soil_moist_conc_lay[Sub][hh] = 0.0; // mg/l

                soil_runoff_D[hh] = 0.0;
                soil_ssr_D[hh] = 0.0;
                soil_gw_D[hh] = 0.0;
                gw_flow_D[hh] = 0.0;
                infil_act_D[hh] = 0.0;
                leaching_mWQ = 0.0f;
                //      } // if

                solute_deposit[hh] = 0.0;
                hru_actet[hh] = 0.0;

                Reset_WQ(hh, soil_gw, soil_gw_conc_lay[Sub]);
                Reset_WQ(hh, soil_ssr, soil_ssr_conc_lay[Sub]);
                Reset_WQ(hh, rechr_ssr, rechr_ssr_conc_lay[Sub]);
                Reset_WQ(hh, infil_act, infil_act_conc_lay[Sub]);
                if ((Sub == i_pp) && (P_is_sediment[0] == 1)) {
                    soil_runoff[hh] = 0;
                } else {
                    Reset_WQ(hh, soil_runoff, soil_runoff_cWQ_lay[Sub]);
                }

                if (hru_evap_buf[hh] < 0.0) {
                    condense = -hru_evap_buf[hh];
                    cum_hru_condense[hh] += condense;
                    hru_evap_buf[hh] = 0.0;
                }
                else
                    condense = 0.0;

                //******Add infiltration to soil and compute excess

                if (soil_moist_max[hh] > 0.0) {

                    potential[hh] = infil[hh] + snowinfil_buf[hh] + condense;

                    // vvvvvvvvvvv    Additions for XG algorithm

                    double possible = thaw_layers_lay[0][hh] * (soil_rechr_max[hh] - soil_rechr[hh]);
                    if ((!NO_Freeze[hh]) && (possible < potential[hh])) {
                        soil_runoff[hh] = potential[hh] - possible;
                        potential[hh] = possible;
                    }

                    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

                    if (potential[hh] > 0.0) {
                        potential_mWQ_lay[Sub][hh] = (infil[hh] + condense) * rain_conc_lay[Sub][hh] + snowinfil_buf[hh] * SWE_conc_lay[Sub][hh];
                        if (!inhibit_evap[hh]) // only when no snowcover
                            potential_mWQ_lay[Sub][hh] += atmos_mWQ_lay[Sub][hh]; // ?? Diogo units need to be checkedd: from the calculation it should be in: mg/l * mm * km^2/in
                    }
                    else
                        potential_mWQ_lay[Sub][hh] = 0.0;

                    potential_Saved = potential[hh];
                    potential_mWQ_lay_Saved = potential_mWQ_lay[Sub][hh];

                    if (potential[hh] > 0.0) {
                        if  (soil_moist[hh] + potential[hh] > soil_moist_max[hh]) { // limit infil and snowinfil to soil_moist_max
                            direct_excs[hh] = soil_moist[hh] + potential[hh] - soil_moist_max[hh];
                            direct_excs_Saved = direct_excs[hh];
                            direct_excs_mWQ_lay[Sub][hh] = potential_mWQ_lay[Sub][hh] * (potential[hh] - direct_excs[hh]) / potential[hh];
                            direct_excs_mWQ_lay_Saved = direct_excs_mWQ_lay[Sub][hh];
                            potential_mWQ_lay[Sub][hh] = std::fmax(potential_mWQ_lay[Sub][hh] - direct_excs_mWQ_lay[Sub][hh], 0.0f);
                            potential[hh] -= direct_excs[hh];
                        }
                        else {
                            direct_excs[hh] = 0.0;
                            direct_excs_Saved = 0.0;
                            direct_excs_mWQ_lay[Sub][hh] = 0.0;
                            direct_excs_mWQ_lay_Saved = 0.0;
                        }
                    }

                    soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];

                    if (potential[hh] > 0.0) {
                        // Diogo -> removed; it seems redundant
                        //if(soil_lower[hh])
                        //  conc_soil_lower_lay[Sub][hh] = (soil_moist_conc_lay[Sub][hh]*soil_moist[hh] - conc_soil_rechr_lay[Sub][hh]*soil_rechr[hh])/soil_lower[hh];
                        //else
                        //  conc_soil_lower_lay[Sub][hh] = 0.0;

                        if (soil_rechr[hh] + potential[hh] > soil_rechr_max[hh]) { // limit infil and snowinfil to soil_rechr_max
                            excs = soil_rechr[hh] + potential[hh] - soil_rechr_max[hh];
                            leaching_mWQ = parleach[hh] * (potential[hh] - excs) * surfsoil_solub_mWQ_lay[Sub][hh];
                            leaching_mWQ = std::fmax(0.0f, std::fmin(leaching_mWQ, surfsoil_solub_mWQ_lay[Sub][hh]));
                            surfsoil_solub_mWQ_lay[Sub][hh] -= leaching_mWQ;
                            conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + leaching_mWQ + potential_mWQ_lay[Sub][hh] * ((potential[hh] - excs) / potential[hh]);
                            conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + excs);
                            excs_mWQ = conc_soil_rechr_lay[Sub][hh] * excs;
                            soil_rechr[hh] = soil_rechr_max[hh];

                        }
                        else {
                            excs = 0.0;
                            excs_mWQ = 0.0;
                            leaching_mWQ = parleach[hh] * (potential[hh] - excs) * surfsoil_solub_mWQ_lay[Sub][hh];
                            leaching_mWQ = std::fmax(0.0f, std::fmin(leaching_mWQ, surfsoil_solub_mWQ_lay[Sub][hh]));
                            surfsoil_solub_mWQ_lay[Sub][hh] -= leaching_mWQ;
                            if (soil_rechr[hh] > 0.0) { // !!!! CAUTION !!!: this piece of code has a huge impact on the conc_soil_rechr_lay[Sub][hh] values 
                                conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + leaching_mWQ + potential_mWQ_lay[Sub][hh];
                                conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + potential[hh]);
                            }
                            else {
                                conc_soil_rechr_lay[Sub][hh] = 0.0;
                            }
                            soil_rechr[hh] += potential[hh];
                        }
                    }

                    if (excs > 0.0) { // put remaning excs_mWQ in lower (some already in rechr)

                        conc_soil_lower_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + excs_mWQ);
                        soil_lower[hh] += excs;
                        conc_soil_lower_lay[Sub][hh] /= soil_lower[hh];

                        leaching_mWQ = parleach[hh] * (excs)*surfsoil_solub_mWQ_lay[Sub][hh];
                        leaching_mWQ = std::fmax(0.0f, std::fmin(leaching_mWQ, surfsoil_solub_mWQ_lay[Sub][hh]));
                        surfsoil_solub_mWQ_lay[Sub][hh] -= leaching_mWQ;
                        soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];
                        soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + leaching_mWQ + conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh]) / soil_moist[hh];

                        if (soil_moist[hh] > soil_moist_max[hh]) {
                            double excs0 = soil_moist[hh] - soil_moist_max[hh];
                            soil_moist_conc_lay[Sub][hh] = (soil_moist_conc_lay[Sub][hh] * soil_moist[hh] - excs_mWQ * excs0 / excs); // amount used

                            conc_soil_lower_lay[Sub][hh] = (soil_moist_conc_lay[Sub][hh] - conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh]); // amount used

                            soil_moist[hh] = soil_moist_max[hh];
                            soil_moist_conc_lay[Sub][hh] /= soil_moist_max[hh]; // amount used

                            soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];
                            conc_soil_lower_lay[Sub][hh] /= soil_lower[hh]; // amount used

                            excs_mWQ = excs_mWQ * excs0 / excs;
                            excs = excs0;
                        }
                        else {
                            soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];
                            //soil_moist[hh] = soil_lower[hh] + soil_rechr[hh]
                            conc_soil_lower_lay[Sub][hh] = (soil_moist_conc_lay[Sub][hh] * soil_moist[hh] - conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh]) / soil_lower[hh]; // amount used

                            excs = 0.0;
                            excs_mWQ = 0.0;
                        }
                    }
                    else {
                        soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];
                        soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh]) / soil_moist[hh]; // amount used
                    }


                    infil_act[hh] = potential[hh];
                    cum_infil_act[hh] += infil_act[hh];
                    infil_act_D[hh] += infil_act[hh];
                    infil_act_conc_lay[Sub][hh] = potential_mWQ_lay[Sub][hh];
                    cum_infil_act_mWQ_lay[Sub][hh] += infil_act_conc_lay[Sub][hh];

                    potential[hh] = potential_Saved;
                    potential_mWQ_lay[Sub][hh] = potential_mWQ_lay_Saved;


                    //  Handle subsurface runoff - does not affect WQ - concentrates

                    if (!inhibit_evap[hh]) {
                        if (variation == VARIATION_2) { // handle tile drainage
                            Dw[hh] = soil_moist_init[hh] / soil_poro_moist[hh] / 1000;  // convert mm -> m
                            tile_flow[hh] = 8.0 * Kb[hh] * Dequiv_depth[hh] * (Dd[hh] - Dw[hh]) + 4.0 * Ka[hh] * pow(Dd[hh] - Dw[hh], 2) / pow(L[hh], 2); // based on Moriasi et al., 2013
                            tile_flow[hh] /= Global::Freq;

                            //  tile_flow[hh][1]=((8*Ksatd2[1]*Dimpbt[1]*((soil_WLmm[hh][1])-Dimpbt[1])+4*Ksatu1[1]*((soil_WLmm[hh][1])-Dimpbt[1])^2)/(tilspc[1])^2) // [mm/h] -> based on Moriasi et al., 2013 '
                            //'		soil_moist[hh][1]=soil_moist[hh][1]-tile_flow[hh][1] // pipe is below recharge layer'
                            //'		soil_rechr[hh][1]=soil_rechr[hh][1]-tile_flow[hh][1]'
                            //'               tile_flowV[hh][1]=tile_flow[hh][1]*hru_area[1]// tile flow in HRU1 in mm*km^2/hr''

                            if (tile_flow[hh] > 0.0) {
                                // double Actual = soil_rechr[hh]/soil_rechr_max[hh]*tile_flow[hh]; // take out of recharge layer
                                double Actual = tile_flow[hh]; // take out of recharge layer (Diogo: not sure -> Tom's version is above)
                                double from_soil_rechr_to_tile_wq = 0.0f;
                                double from_soil_lower_to_tile_wq = 0.0f;
                                if (Actual > soil_rechr[hh]) {// limit to available water
                                  // rechr_ssr[hh] = soil_rechr[hh];
                                    double from_soil_rechr_to_tile_wq = soil_rechr[hh];
                                    soil_rechr[hh] = 0.0f;
                                    if (Actual > soil_moist[hh]) { // removed all soil_moist
                                        tile_flow[hh] = soil_moist[hh];
                                        soil_moist[hh] = 0.0f;
                                        from_soil_lower_to_tile_wq = soil_moist[hh] - soil_rechr[hh];
                                    }
                                    else {
                                        soil_moist[hh] -= Actual;
                                        from_soil_lower_to_tile_wq = Actual - from_soil_rechr_to_tile_wq;
                                    }
                                }
                                else {
                                    soil_rechr[hh] -= Actual;
                                    soil_moist[hh] -= Actual;
                                    double from_soil_rechr_to_tile = Actual;
                                };

                                soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];

                                tile_flow_conc_lay[Sub][hh] = (from_soil_rechr_to_tile_wq * conc_soil_rechr_lay[Sub][hh] + from_soil_lower_to_tile_wq * conc_soil_lower_lay[Sub][hh]);
                                tile_flow_conc_lay[Sub][hh] /= (from_soil_rechr_to_tile_wq + from_soil_lower_to_tile_wq);
                            }

                        } // handle tile drainage

                        rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;

                        // vvvvvvvvvvv    Additions for XG algorithm

                        if (rechr_ssr[hh] > soil_rechr[hh] * thaw_layers_lay[0][hh])
                            rechr_ssr[hh] = soil_rechr[hh] * thaw_layers_lay[0][hh];

                        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


                        if (rechr_ssr[hh] > 0.0) {
                            soil_ssr[hh] = rechr_ssr[hh];
                            soil_ssr_conc_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh];

                            soil_rechr[hh] -= rechr_ssr[hh];
                            rechr_ssr_conc_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh];

                            if (soil_rechr[hh] < 0.0)
                            {
                                soil_moist[hh] -= soil_rechr[hh];
                                soil_rechr[hh] = 0.0;
                                conc_soil_rechr_lay[Sub][hh] = 0.0;
                            }
                            else
                            {
                                soil_moist[hh] -= rechr_ssr[hh];
                            }

                            soil_lower[hh] = soil_moist[hh] - soil_rechr[hh];
                            soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh]) / soil_moist[hh];
                        } // handle non variation ssr

                        cum_rechr_ssr[hh] += rechr_ssr[hh];
                        cum_rechr_ssr_mWQ_lay[Sub][hh] += rechr_ssr_conc_lay[Sub][hh] * rechr_ssr[hh];
                    } // !inhibit_evap

                    //  Handle excess to gw

// Version without XG:
//                    double s2gw_k = soil_gw_K[hh] / Global::Freq;

                    // vvvvvvvvvvv    Modification for XG algorithm

                    double s2gw_k = soil_gw_K[hh] / Global::Freq * thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer

                    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

                    if (s2gw_k > 0)
                        if (direct_excs[hh] >= s2gw_k)
                        { // to gw 03/04/10 changed from >
                            soil_gw[hh] = s2gw_k; // soil_gw[hh] = s2gw_k; // ?? Diogo: shouldn't it be += ?
                            soil_gw_conc_lay[Sub][hh] = direct_excs_mWQ_lay[Sub][hh] / direct_excs[hh]; // ?? Diogo: if the above question is true, then this needs to be changed
                            direct_excs_mWQ_lay[Sub][hh] -= soil_gw_conc_lay[Sub][hh] * s2gw_k;
                            direct_excs[hh] -= s2gw_k;
                        }
                        else
                        {
                            // to gw
                            soil_gw[hh] = direct_excs[hh]; // ?? Diogo: shouldn't it be += ?
                            soil_gw_conc_lay[Sub][hh] = direct_excs_mWQ_lay[Sub][hh] / direct_excs[hh]; // ?? Diogo: if the above question is true, then this needs to be changed
                            direct_excs[hh] = 0.0;
                            direct_excs_mWQ_lay[Sub][hh] = 0.0;
                        }

                    //  Handle excess to interflow or runoff

                    if (!soil_ssr_runoff[hh] && direct_excs[hh] > 0.0) { // to interflow
                        soil_ssr_conc_lay[Sub][hh] = soil_ssr_conc_lay[Sub][hh] * soil_ssr[hh] + direct_excs_mWQ_lay[Sub][hh];

// Previous version:
//                        soil_ssr[hh] += direct_excs[hh];
// Modified for XG:
                        soil_ssr[hh] += direct_excs[hh] * thaw_layers_lay[1][hh];

                        if (soil_ssr[hh] > 0.0)
                            soil_ssr_conc_lay[Sub][hh] /= soil_ssr[hh];
                        else
                            soil_ssr_conc_lay[Sub][hh] = 0.0;

// Previous version:
//                        direct_excs[hh] = 0.0;
//                        direct_excs_mWQ_lay[Sub][hh] = 0.0;
// Modified for XG:
                        direct_excs[hh] = direct_excs[hh] * (1.0 - thaw_layers_lay[1][hh]);
                        direct_excs_mWQ_lay[Sub][hh] = direct_excs_mWQ_lay[Sub][hh] * (1.0 - thaw_layers_lay[1][hh]);
                    }
                }
                else { // soil_moist_max <= 0.0, i.e. Pond
                    excs = infil[hh] + snowinfil_buf[hh] + condense;
                    excs_mWQ = (infil[hh] + condense) * rain_conc_lay[Sub][hh] + snowinfil_buf[hh] * SWE_conc_lay[Sub][hh];
                    if (!inhibit_evap[hh]) // only when no snowcover
                        excs_mWQ += atmos_mWQ_lay[Sub][hh];
                }

                double runoff_to_Sd = 0.0;

// Previous version:
//                soil_runoff[hh] = direct_excs[hh] + meltrunoff_buf[hh] + runoff_buf[hh] + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int) -> critical for outflow calc
// Modified for XG:
                soil_runoff[hh] += direct_excs[hh] + meltrunoff_buf[hh] + runoff_buf[hh] + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int) -> critical for outflow calc

                if (soil_runoff[hh] > minFlow_WQ) {
                    if (SWE[hh] > 0.0 && SWE_max[hh] > 0.0)
                        scf[hh] = tanh(1.26 * SWE[hh] / (CV_SWE[hh] * SWE_max[hh]));
                    else
                        scf[hh] = 0.0;

                    double amount_surfs = sr_mix_rate[hh] * surfsoil_solub_mWQ_lay[Sub][hh] * (1.0 - scf[hh]);

                    amount_surfs = std::fmin(std::max(amount_surfs, 0.0), surfsoil_solub_mWQ_lay[Sub][hh]);
                    surfsoil_solub_mWQ_lay[Sub][hh] -= amount_surfs;

                    if ((Sub == i_pp) && (P_is_sediment[0] == 1)) {
                        // do nothing for now (PRL)
                    } else {
                        soil_runoff_cWQ_lay[Sub][hh] = (excs_mWQ + direct_excs_mWQ_lay[Sub][hh] + meltrunoff_buf[hh] * SWE_conc_lay[Sub][hh] +
                            runoff_buf[hh] * rain_conc_lay[Sub][hh] + redirected_residual_conc_lay[Sub][hh] * redirected_residual[hh] / hru_area[hh]
                            + amount_surfs); // last term (mm*km^2/int)
                        soil_runoff_cWQ_lay[Sub][hh] /= soil_runoff[hh];
                    }

                }
                else {
                    soil_runoff_cWQ_lay[Sub][hh] = 0.0f;
                }


                direct_excs_mWQ_lay[Sub][hh] = direct_excs_mWQ_lay_Saved;
                direct_excs[hh] = direct_excs_Saved;

                cum_redirected_residual_mWQ_lay[Sub][hh] += redirected_residual_conc_lay[Sub][hh] * redirected_residual[hh] / hru_area[hh];
                cum_redirected_residual[hh] += redirected_residual[hh];

                redirected_residual[hh] = 0;
                redirected_residual_conc_lay[Sub][hh] = 0.0;

                if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
                    double Fix = -12.0;
                    if (soil_runoff[hh] / Sdmax[hh] < 12.0) // Diogo: what is this? (comes from an equation that is need below?)
                        Fix = -soil_runoff[hh] / Sdmax[hh];

                    double Ds = (Sdmax[hh] - Sd[hh]) * (1 - exp(Fix));

                    if (soil_moist_max[hh] <= 0.0) // handle pond
                        Ds = Sdmax[hh] - Sd[hh];

                    if (Ds > 0.0) {
                        if (soil_runoff[hh] > Ds) {
                            soil_runoff[hh] -= Ds;
                            if (soil_runoff[hh] < 0.0) {
                                soil_runoff[hh] = 0.0;
                                soil_runoff_cWQ_lay[Sub][hh] = 0.0;
                            }
                            Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + soil_runoff_cWQ_lay[Sub][hh] * Ds;
                            Sd[hh] += Ds;
                            Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] / Sd[hh];
                            runoff_to_Sd += Ds;
                        }
                        else {
                            Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + soil_runoff_cWQ_lay[Sub][hh] * soil_runoff[hh];
                            Sd[hh] += soil_runoff[hh];
                            if (Sd[hh] + soil_runoff[hh] > 0.0f) {
                                Sd_conc_lay[Sub][hh] /= Sd[hh];
                            }
                            else {
                                Sd_conc_lay[Sub][hh] = 0.0f;
                            };
                            runoff_to_Sd += soil_runoff[hh];
                            soil_runoff[hh] = 0.0;
                            soil_runoff_cWQ_lay[Sub][hh] = 0.0;
                        }
                    }
                }

                if (variation == VARIATION_1) {

                    double culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

                    culvert_water_H[hh] = 0.0;
                    culvert_water_A[hh] = 0.0;
                    culvert_over_Q[hh] = 0.0;
                    culvert_Q[hh] = 0.0;
                    culvert_evap[hh] = 0.0;

                    if ((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
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

                                cum_culvert_over[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
                                soil_runoff[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
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
                cum_soil_runoff_mWQ_lay[Sub][hh] += soil_runoff[hh] * soil_runoff_cWQ_lay[Sub][hh];
                cum_runoff_to_Sd[hh] += runoff_to_Sd;
                cum_runoff_to_Sd_mWQ_lay[Sub][hh] += runoff_to_Sd * soil_runoff_cWQ_lay[Sub][hh];

                if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
                    double Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
                    if (Sd2gw_k > Sd[hh])
                        Sd2gw_k = Sd[hh];

                    soil_gw_conc_lay[Sub][hh] = soil_gw_conc_lay[Sub][hh] * soil_gw[hh] + Sd_conc_lay[Sub][hh] * Sd2gw_k;
                    soil_gw[hh] += Sd2gw_k; // ?? Diogo: this was commented out but Tom suggested that it should be (but strangely flow results don't change!!!) -> but it is needed for WQ 

                    if (soil_gw[hh] > 0.0)
                        soil_gw_conc_lay[Sub][hh] /= soil_gw[hh];
                    else
                        soil_gw_conc_lay[Sub][hh] = 0.0;

                    Sd[hh] -= Sd2gw_k;

                    if (Sd[hh] < 0.0) {
                        Sd[hh] = 0.0;
                        Sd_conc_lay[Sub][hh] = 0.0;
                    }
                    cum_Sd_gw[hh] += Sd2gw_k;
                }

                soil_gw_D[hh] += soil_gw[hh];
                cum_soil_gw[hh] += soil_gw[hh];
                cum_soil_gw_mWQ_lay[Sub][hh] += soil_gw[hh] * Sd_conc_lay[Sub][hh];

                gw_conc_lay[Sub][hh] = gw[hh] * gw_conc_lay[Sub][hh] + soil_gw[hh] * soil_gw_conc_lay[Sub][hh];
                gw[hh] += soil_gw[hh];
                if (gw[hh] > 0.0)
                    gw_conc_lay[Sub][hh] /= gw[hh];
                else
                    gw_conc_lay[Sub][hh] = 0.0;

                gw_flow[hh] = 0.0;
                gw_flow_conc_lay[Sub][hh] = 0.0;

                if (gw[hh] > gw_max[hh]) {
                    gw_flow_conc_lay[Sub][hh] = gw_conc_lay[Sub][hh];
                    gw_flow[hh] += gw[hh] - gw_max[hh];
                    gw[hh] = gw_max[hh];
                }

                if (gw_max[hh] > 0.0 && gw_K[hh]) { // prevents divide by zero error // ?? Diogo: what is the basis for this splitting? don't understand
                    gw_flow_conc_lay[Sub][hh] = gw_conc_lay[Sub][hh];

                    double spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
                    gw[hh] -= spill;
                    gw_flow[hh] += spill;
                }

                gw_flow_D[hh] += gw_flow[hh];
                cum_gw_flow[hh] += gw_flow[hh];
                cum_gw_flow_mWQ_lay[Sub][hh] += gw_flow[hh] * gw_conc_lay[Sub][hh];

                if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
                    double Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
                    if (Sd2ssr_k >= Sd[hh])
                        Sd2ssr_k = Sd[hh];

                    soil_ssr_conc_lay[Sub][hh] = soil_ssr_conc_lay[Sub][hh] * soil_ssr[hh] + Sd_conc_lay[Sub][hh] * Sd2ssr_k;
                    soil_ssr[hh] += Sd2ssr_k;
                    if (soil_ssr[hh] > 0.0)
                        soil_ssr_conc_lay[Sub][hh] /= soil_ssr[hh];
                    else
                        soil_ssr_conc_lay[Sub][hh] = 0.0;

                    if (Sd[hh] - Sd2ssr_k < 0.0) {
                        Sd[hh] = 0.0;
                        Sd_conc_lay[Sub][hh] = 0.0;
                    }
                    else {
                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] - Sd_conc_lay[Sub][hh] * Sd2ssr_k;
                        Sd[hh] -= Sd2ssr_k;
                        if (Sd[hh] > 0.0)
                            Sd_conc_lay[Sub][hh] /= Sd[hh];
                        else
                            Sd_conc_lay[Sub][hh] = 0.0;
                    }
                }

// Previous version:
//                double s2ssr_k = lower_ssr_K[hh] / Global::Freq;
// Modified for XG:
                double s2ssr_k = lower_ssr_K[hh] / Global::Freq * thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer

                if (s2ssr_k > 0.00001) {
                    double avail = soil_lower[hh];
                    if (s2ssr_k >= avail)
                        s2ssr_k = avail;

                    soil_lower[hh] -= s2ssr_k; // soil lower concentration stays the same

                    soil_ssr_conc_lay[Sub][hh] = soil_ssr_conc_lay[Sub][hh] * soil_ssr[hh] + conc_soil_lower_lay[Sub][hh] * s2ssr_k;
                    soil_ssr[hh] += s2ssr_k;

                    if (soil_ssr[hh] > 0.0)
                        soil_ssr_conc_lay[Sub][hh] /= soil_ssr[hh];
                    else
                        soil_ssr_conc_lay[Sub][hh] = 0.0;

                    soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];
                    soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh]) / soil_moist[hh];

                    cum_lower_ssr[hh] += s2ssr_k;
                }

                cum_soil_ssr[hh] += soil_ssr[hh];
                cum_soil_ssr_mWQ_lay[Sub][hh] += soil_ssr[hh] * soil_moist_conc_lay[Sub][hh];
                soil_ssr_D[hh] += soil_ssr[hh];

                //******Compute actual evapotranspiration

                double culvert_pond = 0.0; // convert m3 to mm

                double culvert_evapL = 0;

                if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation
                    culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
                    culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

                    if (culvert_evapL > culvert_pond) // limit to amount available
                        culvert_evapL = culvert_pond;

                    culvert_evap[hh] = culvert_evapL;
                    hru_actet[hh] += culvert_evapL;
                    culvert_water_V[hh] = (culvert_pond - culvert_evapL) * (hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
                }

                double avail_evap = hru_evap_buf[hh] - culvert_evapL;
                if (Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
                    avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
                else
                    avail_evap = 0.0;

                if (Sd[hh] > 0.0 && avail_evap > 0.0) {
                    if (Sd[hh] >= avail_evap) {
                        if (Sd[hh] - avail_evap < 0.0) {
                            double Sdmass_2_soil = Sd_conc_lay[Sub][hh] * Sd[hh];
                            Sd[hh] -= avail_evap;
                            Sd[hh] = 0.0;
                            Sd_conc_lay[Sub][hh] = 0.0;
                            Sd_to_soil_mass(Sdmass_2_soil); // function: add Sd mass to soil
                        }
                        else {
                            Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh];// -  Sd_conc_lay[Sub][hh]*avail_evap; // Diogo: it will get more concentrated
                            Sd[hh] -= avail_evap;

                            if (Sd[hh] > 0.05) { // Diogo: needed to avoid instability -> the water will be added to conc_soil_rechr
                                Sd_conc_lay[Sub][hh] /= Sd[hh];
                            }
                            else {
                                double Sdmass_2_soil = Sd_conc_lay[Sub][hh] * Sd[hh];
                                Sd_conc_lay[Sub][hh] = 0.0;
                                Sd_to_soil_mass(Sdmass_2_soil); // function: add Sd mass to soil
                            }
                        }
                    }
                    else {
                        avail_evap = Sd[hh];
                        double Sdmass_2_soil = Sd_conc_lay[Sub][hh] * avail_evap;
                        Sd_conc_lay[Sub][hh] = 0.0;
                        Sd[hh] = 0.0;
                        Sd_to_soil_mass(Sdmass_2_soil); // function: add Sd mass to soil
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

                //******Soil moisture accounting  Remember that soil_rechr[hh] includes soil_moist[hh]

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
                            soil_lower[hh] = 0.0;
                        }
                        else {
                            et = etr + etl;
                            soil_moist[hh] = soil_moist[hh] - et;

                            if (etr > soil_rechr[hh]) {
                                soil_lower[hh] = soil_lower[hh] - (et - soil_rechr[hh]);
                                soil_rechr[hh] = 0.0;
                            }
                            else {
                                soil_rechr[hh] = soil_rechr[hh] - etr;
                                soil_lower[hh] = soil_lower[hh] - etl;
                            }
                        }
                        break;
                    } // switch

                    hru_actet[hh] += et;

                } // soil_moist[hh] > 0.0

                if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
                    hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

                hru_cum_actet[hh] += hru_actet[hh];
                cum_solute_deposit[hh] += solute_deposit[hh];

                // Calculating conc_soil_moist
                if (soil_moist[hh] > 0.0f) {
                    conc_soil_moist_lay[Sub][hh] = (conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] +
                        conc_soil_lower_lay[Sub][hh] * soil_lower[hh]) / soil_moist[hh];
                }
                else
                {
                    conc_soil_moist_lay[Sub][hh] = 0.0f;
                }


            } // for hh
        } // for Sub

        for (hh = 0; chkStruct(); ++hh) {

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
        } // for hh
    }  // try
    catch (...)
    {

        string moduleName;
        for (
            std::list<std::pair<std::string, ClassModule*>>::iterator it = Global::OurModulesList->begin();
            it != Global::OurModulesList->end();
            it++
            )
        {
            if (it->first == Global::CurrentModuleRun)
            {
                moduleName = it->first;
            }
        }

        string S = "Error" + string(" at ") + StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " (" + to_string(getstep()) + ") in '" + moduleName +
            "'" + " (" + FloatToStrF(Global::DTnow, TFloatFormat::ffGeneral, 10, 6) + ") hh = " + FloatToStrF(hh, TFloatFormat::ffGeneral, 6, 0) + " Sub = " + FloatToStrF(Sub, TFloatFormat::ffGeneral, 6, 0);
        LogError(S, TExcept::WARNING);
        std::cout << "Diogo: Exception occurred in \"ClassWQ_SoilX::run\" " << std::endl;
        if (++FaultsAllowed == 1)
            throw;
    }
}

void ClassWQ_SoilX::finish(bool good) {

    double Allcum_soil_runoff = 0.0;
    double Allcum_soil_ssr = 0.0;
    double Allcum_rechr_ssr = 0.0;
    double Allcum_soil_gw = 0.0;
    double Allcum_gw_flow = 0.0;
    double Allcum_infil_act = 0.0;
    double Allcum_soil_moist_change = 0.0;
    double Allcum_Sd_change = 0.0;
    double Allcum_gw_change = 0.0;
    double Allcum_evap = 0.0;
    double Allcum_solute_deposit = 0.0;

    double Allcum_soil_runoff_mWQ = 0.0;
    double Allcum_soil_ssr_mWQ = 0.0;
    double Allcum_rechr_ssr_mWQ = 0.0;
    double Allcum_soil_gw_mWQ = 0.0;
    double Allcum_gw_flow_mWQ = 0.0;
    double Allcum_infil_act_mWQ = 0.0;
    double Allcum_soil_moist_change_mWQ = 0.0;
    double Allcum_Sd_change_mWQ = 0.0;
    double Allcum_gw_change_mWQ = 0.0;

    double AllTotal = 0.0;

    string S = string("H2O");
    LogDebug(S.c_str());
    LogMessage(" ");

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_rechr_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (Soil_WQ)' cum_rechr_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (Soil_WQ)' soil_moist_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_lower                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_lower_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh] - soil_bottom_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' hru_cum_actet               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_Sd_evap                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_evap[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'hru_cum_actet'.");
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_hru_condense            (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_infil_act(all)          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_gw                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_runoff             (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_rechr_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_ssr                (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Sd                          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Sd_change                   (mm)   (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_runoff_to_Sd            (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_Sd_ssr                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_lower_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_lower_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' gw                          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' gw_change                   (mm)   (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_gw_flow                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_redirected_residual     (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
        LogDebug(" ");

        double Total = cum_soil_runoff[hh] + cum_soil_ssr[hh] + cum_soil_gw[hh]
            + cum_runoff_to_Sd[hh] + cum_gw_flow[hh]
            + (soil_moist[hh] - soil_moist_Init[hh]) + (Sd[hh] - Sd_Init[hh]) + (gw[hh] - gw_Init[hh]) + hru_cum_actet[hh]
            - cum_redirected_residual[hh] / hru_area[hh];
        AllTotal += Total;
        LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Total                       (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total / hru_area[hh], hru_area[hh], basin_area[0], " *** HRU mass balance");
        LogDebug(" ");

        if (variation == VARIATION_1) {
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
            LogDebug(" ");
        }


        LogDebug(" ");

        Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
        Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
        Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
        Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
        Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
        Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
        Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh]) * hru_area[hh];
        Allcum_Sd_change += (Sd[hh] - Sd_Init[hh]) * hru_area[hh];
        Allcum_gw_change += (gw[hh] - gw_Init[hh]) * hru_area[hh];

        Allcum_evap += hru_cum_actet[hh] * hru_area[hh];
    } // hh

    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_runoff (mm*basin):           ").c_str(), Allcum_soil_runoff);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_ssr (mm*basin):              ").c_str(), Allcum_soil_ssr);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_rechr_ssr (mm*basin):             ").c_str(), Allcum_rechr_ssr);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_gw (mm*basin):               ").c_str(), Allcum_soil_gw);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_flow (mm*basin):               ").c_str(), Allcum_gw_flow);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_infil_act (mm*basin):             ").c_str(), Allcum_infil_act);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_moist_change (mm*basin):     ").c_str(), Allcum_soil_moist_change);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_Sd_change (mm*basin):             ").c_str(), Allcum_Sd_change);
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_change (mm*basin):             ").c_str(), Allcum_gw_change);
    LogDebug(" ");
    LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_actet (mm*basin):                 ").c_str(), Allcum_evap);
    LogDebug(" ");

    LogMessage(string("'" + Name + " (WQ_Soil)' AllTotal              (mm*basin):        ").c_str(), AllTotal);
    LogDebug(" ");

    for (long Sub = 0; Sub < 1; ++Sub) {

        string S = string("Substance# ") + to_string(Sub + 1);
        LogDebug(S.c_str());
        LogMessage(" ");

        Allcum_soil_runoff = 0.0;
        Allcum_soil_ssr = 0.0;
        Allcum_rechr_ssr = 0.0;
        Allcum_soil_gw = 0.0;
        Allcum_gw_flow = 0.0;
        Allcum_infil_act = 0.0;
        Allcum_soil_moist_change = 0.0;
        Allcum_Sd_change = 0.0;
        Allcum_gw_change = 0.0;
        Allcum_evap = 0.0;
        Allcum_solute_deposit = 0.0;

        Allcum_soil_runoff_mWQ = 0.0;
        Allcum_soil_ssr_mWQ = 0.0;
        Allcum_rechr_ssr_mWQ = 0.0;
        Allcum_soil_gw_mWQ = 0.0;
        Allcum_gw_flow_mWQ = 0.0;
        Allcum_infil_act_mWQ = 0.0;
        Allcum_soil_moist_change_mWQ = 0.0;
        Allcum_Sd_change_mWQ = 0.0;
        Allcum_gw_change_mWQ = 0.0;

        double AllTotal = 0.0;

        for (hh = 0; chkStruct(); ++hh) {
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_rechr                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_rechr_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_rechr_conc             (mg/l) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh], hru_area[hh], basin_area[0]);

            //      soil_rechr_change_mWQ_lay[Sub][hh] = soil_rechr[hh]*conc_soil_rechr_lay[Sub][hh] - soil_rechr_Init[hh]*soil_top_conc_Init_lay[Sub][hh];
            //      LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_rechr_mWQ_change       (mg)   (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr_change_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_rechr_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_rechr_ssr_mWQ           (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_rechr_ssr_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_moist                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_moist_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_moist_conc             (mg/l) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] * soil_moist_conc_lay[Sub][hh], hru_area[hh], basin_area[0]);

            //      soil_moist_change_mWQ_lay[Sub][hh] = soil_moist[hh]*soil_moist_conc_lay[Sub][hh] - soil_moist_Init[hh]*soil_moist_conc_Init_lay[Sub][hh];
            //      LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_moist_mWQ_change       (mg)   (mm*hru) (mm*hru/basin): ").c_str(), soil_moist_change_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_lower                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_lower_change           (mm)   (mm*hru) (mm*hru/basin): ").c_str(), soil_lower[hh] - soil_bottom_Init[hh], hru_area[hh], basin_area[0]);

            //      soil_bottom_change_mWQ_lay[Sub][hh] = soil_lower[hh]*conc_soil_lower_lay[Sub][hh] - soil_bottom_Init[hh]*soil_bottom_conc_Init_lay[Sub][hh];
            //      LogMessageA(hh, string("'" + Name + " (WQ_Soil)' soil_bottom_mWQ_change      (mg)   (mm*hru) (mm*hru/basin): ").c_str(), soil_bottom_change_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' hru_cum_actet               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_Sd_evap                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_evap[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'hru_cum_actet'.");
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_hru_condense            (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_infil_act(all)          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_infil_act_mWQ(all)      hh(mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_infil_act_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_gw                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_gw_mWQ             (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_soil_gw_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_runoff             (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_runoff_mWQ         (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_soil_runoff_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_rechr_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_rechr_ssr_mWQ           (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_rechr_ssr_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_ssr                (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_soil_ssr_mWQ            (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_soil_ssr_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Sd                          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Sd_change                   (mm)   (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Sd_conc                     (mm)   (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] * Sd_conc_lay[Sub][hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_runoff_to_Sd            (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_runoff_to_Sd_mWQ        (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_runoff_to_Sd_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_Sd_ssr                  (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_ssr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_lower_ssr               (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_lower_ssr[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' gw                          (mm)   (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' gw_change                   (mm)   (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' gw_conc                     (mg/l) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] * gw_conc_lay[Sub][hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_gw_flow                 (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_gw_flow_mWQ             (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_gw_flow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_redirected_residual     (mm)   (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_redirected_residual_mWQ (mg)   (mg*hru) (mg*hru/basin): ").c_str(), cum_redirected_residual_mWQ_lay[Sub][hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
            LogDebug(" ");

            double Total = cum_soil_runoff[hh] + cum_soil_ssr[hh] + cum_soil_gw[hh]
                + cum_runoff_to_Sd[hh] + cum_gw_flow[hh]
                + (soil_moist[hh] - soil_moist_Init[hh]) + (Sd[hh] - Sd_Init[hh]) + (gw[hh] - gw_Init[hh]) + hru_cum_actet[hh]
                - cum_redirected_residual[hh] / hru_area[hh];
            AllTotal += Total;
            LogMessageA(hh, string("'" + Name + " (WQ_Soil)' Total                       (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total / hru_area[hh], hru_area[hh], basin_area[0], " *** HRU mass balance");
            LogDebug(" ");

            if (variation == VARIATION_1) {
                LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
                LogMessageA(hh, string("'" + Name + " (WQ_Soil)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
                LogDebug(" ");
            }


            LogDebug(" ");

            Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
            Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
            Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
            Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
            Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
            Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
            Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh]) * hru_area[hh];
            Allcum_Sd_change += (Sd[hh] - Sd_Init[hh]) * hru_area[hh];
            Allcum_gw_change += (gw[hh] - gw_Init[hh]) * hru_area[hh];

            Allcum_soil_runoff_mWQ += cum_soil_runoff_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_soil_ssr_mWQ += cum_soil_ssr_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_rechr_ssr_mWQ += cum_rechr_ssr_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_soil_gw_mWQ += cum_soil_gw_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_gw_flow_mWQ += cum_gw_flow_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_infil_act_mWQ += cum_infil_act_mWQ_lay[Sub][hh] * hru_area[hh];
            Allcum_soil_moist_change_mWQ += (soil_moist[hh] * soil_moist_conc_lay[Sub][hh] - soil_moist_Init[hh] * soil_moist_conc_Init[hh]) * hru_area[hh];
            Allcum_Sd_change_mWQ += (Sd[hh] * Sd_conc_lay[Sub][hh] - Sd_Init[hh] * Sd_conc_Init_lay[Sub][hh]) * hru_area[hh];
            Allcum_gw_change_mWQ += (gw[hh] * gw_conc_lay[Sub][hh] - gw_Init[hh] * gw_conc_Init_lay[Sub][hh]) * hru_area[hh];
            Allcum_evap += hru_cum_actet[hh] * hru_area[hh];
            Allcum_solute_deposit += cum_solute_deposit[hh] * hru_area[hh];
        }

        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_runoff (mm*basin):           ").c_str(), Allcum_soil_runoff);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_runoff_mWQ (mg*basin):       ").c_str(), Allcum_soil_runoff_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_ssr (mm*basin):              ").c_str(), Allcum_soil_ssr);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_ssr_mWQ (mg*basin):          ").c_str(), Allcum_soil_ssr_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_rechr_ssr (mm*basin):             ").c_str(), Allcum_rechr_ssr);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_rechr_ssr_mWQ (mg*basin):         ").c_str(), Allcum_rechr_ssr_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_gw (mm*basin):               ").c_str(), Allcum_soil_gw);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_gw_mWQ (mg*basin):           ").c_str(), Allcum_soil_gw_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_flow (mm*basin):               ").c_str(), Allcum_gw_flow);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_flow_mWQ (mg*basin):           ").c_str(), Allcum_gw_flow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_infil_act (mm*basin):             ").c_str(), Allcum_infil_act);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_infil_act_mWQ (mg*basin):         ").c_str(), Allcum_infil_act_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_moist_change (mm*basin):     ").c_str(), Allcum_soil_moist_change);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_soil_moist_change_mWQ (mg*basin): ").c_str(), Allcum_soil_moist_change_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_Sd_change (mm*basin):             ").c_str(), Allcum_Sd_change);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_Sd_change_mWQ (mg*basin):         ").c_str(), Allcum_Sd_change_mWQ);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_change (mm*basin):             ").c_str(), Allcum_gw_change);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_gw_change_mWQ (mg*basin):         ").c_str(), Allcum_gw_change_mWQ);
        LogDebug(" ");
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_actet (mm*basin):                 ").c_str(), Allcum_evap);
        LogMessage(string("'" + Name + " (WQ_Soil)' Allcum_solute_deposit (mg*basin):        ").c_str(), Allcum_solute_deposit);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Soil)' AllTotal              (mm*basin):        ").c_str(), AllTotal);
        LogDebug(" ");
    } // sub 
}

double ClassWQ_SoilX::FunctX(const double x) {
    double X = 0.0, F;
    for (long n = 1; n < 100; ++n) {
        double y = -2.0 * n * x;
        F = 4.0 * exp(y) / (n * (1.0 - exp(y)));
        X += F;
        if (fabs(F) < 0.001)
            return X;
    }
    return X;
}

void ClassWQ_SoilX::Sd_to_soil_mass(double add_mass) {
    if (soil_rechr[hh] > 0.0f) { // Diogo: goes to rechr if existant
        conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + add_mass; // Diogo: just mass
        conc_soil_rechr_lay[Sub][hh] /= soil_rechr[hh];
    }
    else if (soil_moist[hh] > 0.0f)
    {
        conc_soil_rechr_lay[Sub][hh] = 0.0f;
        conc_soil_lower_lay[Sub][hh] = conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + add_mass; // Diogo: just mass
        conc_soil_lower_lay[Sub][hh] /= conc_soil_lower_lay[Sub][hh];
    }
};

void ClassWQ_SoilX::Set_WQ(const long hru, double* var, double* var_cWQ, double amount, double amount_cWQ) {

    var[hru] = amount;
    if (amount > 0.0)
        var_cWQ[hru] = amount_cWQ;
    else
        var_cWQ[hru] = 0.0;
}

void ClassWQ_SoilX::copy_array(double* from, double* to) {
    for (hh = 0; chkStruct(); ++hh)
        to[hh] = from[hh];
}

void ClassWQ_SoilX::restore_hru(double* from, double* to, long hh) {
    to[hh] = from[hh];
}

void ClassWQ_SoilX::Restore(long hh) {

    restore_hru(redirected_residual_0, redirected_residual, hh);
    restore_hru(Sd_0, Sd, hh);
    restore_hru(gw_0, gw, hh);
    restore_hru(soil_rechr_0, soil_rechr, hh);
    restore_hru(soil_moist_0, soil_moist, hh);
    restore_hru(soil_lower_0, soil_lower, hh);
    restore_hru(gw_flow_0, gw_flow, hh);
    restore_hru(hru_actet_0, hru_actet, hh);
    restore_hru(hru_cum_actet_0, hru_cum_actet, hh);
    restore_hru(cum_soil_runoff_0, cum_soil_runoff, hh);
    restore_hru(cum_redirected_residual_0, cum_redirected_residual, hh);
    restore_hru(cum_hru_condense_0, cum_hru_condense, hh);
    restore_hru(cum_Sd_evap_0, cum_Sd_evap, hh);
    restore_hru(cum_Sd_ssr_0, cum_Sd_ssr, hh);
    restore_hru(cum_Sd_gw_0, cum_Sd_gw, hh);
    restore_hru(cum_lower_ssr_0, cum_lower_ssr, hh);
    restore_hru(cum_infil_act_0, cum_infil_act, hh);
    restore_hru(cum_gw_flow_0, cum_gw_flow, hh);
    restore_hru(cum_soil_ssr_0, cum_soil_ssr, hh);
    restore_hru(cum_rechr_ssr_0, cum_rechr_ssr, hh);
    restore_hru(cum_runoff_to_Sd_0, cum_runoff_to_Sd, hh);
    restore_hru(cum_runoff_to_ssr_0, cum_runoff_to_ssr, hh);
    restore_hru(cum_soil_gw_0, cum_soil_gw, hh);
    restore_hru(cum_infil_act_0, cum_infil_act, hh);
    restore_hru(cum_solute_deposit_0, cum_solute_deposit, hh);
}

void ClassWQ_SoilX::Save() {

    copy_array(redirected_residual, redirected_residual_0);
    copy_array(Sd, Sd_0);
    copy_array(gw, gw_0);
    copy_array(soil_rechr, soil_rechr_0);
    copy_array(soil_moist, soil_moist_0);
    copy_array(soil_lower, soil_lower_0);
    copy_array(gw_flow, gw_flow_0);
    copy_array(hru_actet, hru_actet_0);
    copy_array(hru_cum_actet, hru_cum_actet_0);
    copy_array(cum_soil_runoff, cum_soil_runoff_0);
    copy_array(cum_redirected_residual, cum_redirected_residual_0);
    copy_array(cum_hru_condense, cum_hru_condense_0);
    copy_array(cum_Sd_evap, cum_Sd_evap_0);
    copy_array(cum_Sd_ssr, cum_Sd_ssr_0);
    copy_array(cum_Sd_gw, cum_Sd_gw_0);
    copy_array(cum_lower_ssr, cum_lower_ssr_0);
    copy_array(cum_gw_flow, cum_gw_flow_0);
    copy_array(cum_soil_ssr, cum_soil_ssr_0);
    copy_array(cum_rechr_ssr, cum_rechr_ssr_0);
    copy_array(cum_runoff_to_Sd, cum_runoff_to_Sd_0);
    copy_array(cum_runoff_to_ssr, cum_runoff_to_ssr_0);
    copy_array(cum_soil_gw, cum_soil_gw_0);
    copy_array(cum_infil_act, cum_infil_act_0);
    copy_array(cum_solute_deposit, cum_solute_deposit_0);
}

void ClassWQ_SoilX::Reset_WQ(long hru, double* var, double* var_cWQ) {
    var[hru] = 0.0;
    var_cWQ[hru] = 0.0;
}

void ClassWQ_SoilX::Reset_WQ(long hru, double* var, double** var_cWQ_lay) {
    var[hru] = 0.0;
    for (long Sub = 0; Sub < numsubstances; Sub++) {
        var_cWQ_lay[Sub][hru] = 0.0;
    }
}