#include "ClassSoilPrairie.h"
#include "../../core/InstrumentLogger.h"

ClassSoilPrairie * ClassSoilPrairie :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::klone(string name) const@@@ClassSoilPrairie.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::klone(string name) const@@@ClassSoilPrairie.cpp>");
    return new ClassSoilPrairie (name);
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::klone(string name) const@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::decl(void)@@@ClassSoilPrairie.cpp>");
    Description = "'Handles soil moisture throughout the year.' \
                 'Parametric contibuting fraction model,' \
                 'Pothole Cascade Model of contributing fraction,' \
                 'PDMROF model of contributing fraction.'";
    variation_set = VARIATION_1;
    decllocal ("total_slough_basin_area", TDim :: NHRU, "total_basin_area", "(m^2)", & total_basin_area);
    decllocal ("final_area", TDim :: NHRU, "final_area", "(m^2)", & final_area);
    decllocal ("max_slough_area", TDim :: NHRU, "max_slough_area", "(m^2)", & max_slough_area);
    decllocal ("outflow_volume", TDim :: NHRU, "outflow_volume", "(m^3)", & outflow_volume);
    decllocal ("delta_vol", TDim :: NHRU, "delta_vol - change in volume", "(m^3)", & delta_vol);
    decllocal ("final_vol", TDim :: NHRU, "final_vol", "(m^3)", & final_vol);
    decllocal ("max_slough_volume", TDim :: NHRU, "max_slough_volume", "(m^3)", & max_slough_volume);
    decllocal ("areafrac", TDim :: NHRU, "areafrac", "()", & areafrac);
    decllocal ("runofffrac", TDim :: NHRU, "runofffrac", "()", & runofffrac);
    decllocal ("total_slough_basin_area", TDim :: NHRU, "total_slough_basin_area", "()", & total_slough_basin_area);
    decllocal ("PCM_runoff_multiplier", TDim :: NHRU, "PCM_runoff_multiplier", "()", & PCM_runoff_multiplier);
    decllocal ("PCM_Sdmax", TDim :: NHRU, "PCM_Sdmax", "(mm)", & PCM_Sdmax);
    decllocal ("total_slough_volume", TDim :: NHRU, "total_slough_volume", "(m^3)", & total_slough_volume);
    decllocal ("PCM_outflow", TDim :: NHRU, "PCM_outflow", "(m^3)", & PCM_outflow);
    declparam ("max_water_frac", TDim :: NHRU, "[0.24]", "0.0", "1.0", "Max. possible fraction of the HRU area covered by water.", "()", & max_water_frac);
    declparam ("basin_area", TDim :: NHRU, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("numSloughs", TDim :: NHRU, "[1]", "1", "2000", "Number of sloughs", "()", & numSloughs);
    declparam ("Max_V", TDim :: NHRU, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^3)", & Max_V, & Max_V_N, 736);
    declparam ("Max_A", TDim :: NHRU, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^2)", & Max_A, & Max_A_N, 736);
    declparam ("Init_V", TDim :: NHRU, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^3)", & Init_V, & Init_V_N, 736);
    declparam ("Connect", TDim :: NHRU, "[1]", "0", "1000", "Slough maximum volumes", "()", & Connect, & Connect_N, 736);
    declparam ("p1", TDim :: NHRU, "[1.72]", "0.1", "5", "pond p1", "()", & p1);
    declparam ("p2", TDim :: NHRU, "[3.33]", "0.1", "5", "pond p2", "()", & p2);
    declparam ("maxPondArea_p1", TDim :: NHRU, "[10000]", "10", "100000", "Max area for p1", "(m^2)", & maxPondArea_p1);
    declparam ("minPondBasinArea", TDim :: NHRU, "[2893.887]", "10", "100000", "Min allowable pond basin area", "(m^2)", & minPondBasinArea);
    declparam ("minPondArea", TDim :: NHRU, "[10000]", "10", "100000", "Min pond area for basin calculation", "(m^2)", & minPondArea);
    declparam ("basinarea_c1", TDim :: NHRU, "[3.44329]", "0.01", "100", "Pond basin area constant c1", "()", & basinarea_c1);
    declparam ("basinarea_c2", TDim :: NHRU, "[0.738377]", "0.01", "100", "Pond basin area constant c2", "()", & basinarea_c2);
    variation_set = VARIATION_2;
    declparam ("CMAX", TDim :: NHRU, "[0.1]", "0.01", "100", "MAXIMUM POTHOLE PONDING CAPACITY", "(m)", & CMAX);
    declparam ("CMIN", TDim :: NHRU, "[0.1]", "0.01", "100", "MINIMUM POTHOLE PONDING CAPACITY", "(m)", & CMIN);
    declparam ("B", TDim :: NHRU, "[1.1]", "0.01", "10", "SHAPE FACTOR OF THE PARETO DISTRIBUTION FUNCTION", "(m)", & B);
    variation_set = VARIATION_ORG;
    if (Global :: nlay < 2)
    {
        Global :: nlay = 2;
        Global :: maxlay = 2;
    }

    declvar ("redirected_residual", TDim :: NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", & redirected_residual);
    declstatdiag ("cum_redirected_residual", TDim :: NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", & cum_redirected_residual);
    declvar ("direct_rain", TDim :: NHRU, "direct rainfall through canopy", "(mm/int)", & direct_rain);
    declstatvar ("Sd", TDim :: NHRU, "Depression storage.", "(mm)", & Sd);
    declstatvar ("gw", TDim :: NHRU, "ground water storage.", "(mm)", & gw);
    declstatvar ("soil_rechr", TDim :: NHRU, " available moisture content of soil recharge zone , ie, the"
        "portion of the soil profile from which evaporation can take place.", "(mm)", & soil_rechr);
    declstatvar ("soil_moist", TDim :: NHRU, " available moisture content of soil profile to the depth "
        "of the rooting zone of the major vegetation type on the HRU.", "(mm)", & soil_moist);
    decllocal ("cum_hru_condense", TDim :: NHRU, "cumulative condensation over HRU.", "(mm)", & cum_hru_condense);
    declvar ("soil_gw", TDim :: NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", & soil_gw);
    declvar ("soil_gw_D", TDim :: NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", & soil_gw_D);
    declvar ("gw_flow", TDim :: NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", & gw_flow);
    declvar ("gw_flow_D", TDim :: NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", & gw_flow_D);
    declvar ("infil_act", TDim :: NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", & infil_act);
    declvar ("cum_infil_act", TDim :: NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", & cum_infil_act);
    declvar ("infil_act_D", TDim :: NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", & infil_act_D);
    declstatdiag ("cum_gw_flow", TDim :: NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", & cum_gw_flow);
    declvar ("soil_ssr", TDim :: NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", & soil_ssr);
    declvar ("rechr_ssr", TDim :: NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", & rechr_ssr);
    declstatdiag ("cum_soil_ssr", TDim :: NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", & cum_soil_ssr);
    declstatdiag ("cum_rechr_ssr", TDim :: NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", & cum_rechr_ssr);
    declvar ("soil_ssr_D", TDim :: NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", & soil_ssr_D);
    declvar ("soil_runoff", TDim :: NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", & soil_runoff);
    declstatdiag ("cum_soil_runoff", TDim :: NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", & cum_soil_runoff);
    declvar ("soil_runoff_D", TDim :: NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", & soil_runoff_D);
    decldiag ("cum_runoff_to_Sd", TDim :: NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", & cum_runoff_to_Sd);
    decldiag ("cum_soil_gw", TDim :: NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", & cum_soil_gw);
    declvar ("Sd_water_frac", TDim :: NHRU, "fraction of the maximum possible Sd HRU fraction that is under water.", "()", & Sd_water_frac);
    declvar ("contrib_frac", TDim :: NHRU, "Fraction of the wetlands contributing water.", "()", & contrib_frac);
    declvar ("wetlands_evap", TDim :: NHRU, "Depth of water evaporating from wetlands using Priestley-Taylor.", "(mm/int)", & wetlands_evap);
    declvar ("total_evap", TDim :: NHRU, "Control variable based on running sum of evap.", "(mm)", & total_evap);
    decllocal ("snowinfil_buf", TDim :: NHRU, "buffer snow infiltration.", "(mm/d)", & snowinfil_buf);
    decllocal ("runoff_buf", TDim :: NHRU, "buffer runoff.", "(mm/d)", & runoff_buf);
    decllocal ("meltrunoff_buf", TDim :: NHRU, "buffer melt runoff.", "(mm/d)", & meltrunoff_buf);
    decllocal ("hru_evap_buf", TDim :: NHRU, "buffer evaporation.", "(mm/d)", & hru_evap_buf);
    decllocal ("hru_evap_PT_buf", TDim :: NHRU, "Priestley-Taylor buffer evaporation", "(mm/d)", & hru_evap_PT_buf);
    decllocal ("soil_moist_Init", TDim :: NHRU, "initial soil moisture.", "(mm)", & soil_moist_Init);
    decllocal ("soil_rechr_Init", TDim :: NHRU, "initial soil recharge.", "(mm)", & soil_rechr_Init);
    decllocal ("Sd_Init", TDim :: NHRU, "initial Depression storage.", "(mm)", & Sd_Init);
    decllocal ("gw_Init", TDim :: NHRU, "initial ground water storage.", "(mm)", & gw_Init);
    declparam ("basin_area", TDim :: NHRU, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", & hru_area);
    declparam ("Sdmax", TDim :: NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", & Sdmax);
    declparam ("Sdinit", TDim :: NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", & Sdinit);
    declparam ("soil_rechr_max", TDim :: NHRU, "[60.0]", "0.0", "350.0", " Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", & soil_rechr_max);
    declparam ("soil_rechr_init", TDim :: NHRU, "[30.0]", "0.0", "250.0", " Initial value of available water for soil recharge zone (upper part of "
        "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", & soil_rechr_init);
    declparam ("soil_moist_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."
        "Soil profile is surface to bottom of rooting zone.", "(mm)", & soil_moist_max);
    declparam ("soil_moist_init", TDim :: NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in soil profile.", "(mm)", & soil_moist_init);
    declparam ("soil_gw_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "
        "that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", & soil_gw_K);
    declparam ("gw_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", & gw_max);
    declparam ("gw_init", TDim :: NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", & gw_init);
    declparam ("gw_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", & gw_K);
    declparam ("rechr_ssr_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", & rechr_ssr_K);
    declparam ("lower_ssr_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", & lower_ssr_K);
    declparam ("Sd_ssr_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", & Sd_ssr_K);
    declparam ("Sd_gw_K", TDim :: NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", & Sd_gw_K);
    declparam ("Sd_water_frac_max", TDim :: NHRU, "[0.24]", "0.0", "1.0", "Maximum fraction of the HRU area that can be water.", "()", & Sd_water_frac_max);
    declparam ("contrib_frac_init", TDim :: NHRU, "[0.0]", "0.0", "1.0", "Fraction of the HRU area contributing water.", "()", & contrib_frac_init);
    declparam ("evap_threshold", TDim :: NHRU, "[10]", "0.0", "20.0", "Threshold evaporation necessary for setting the contribution fraction to zero.", "(mm)", & evap_threshold);
    declparam ("soil_withdrawal", TDim :: NHRU, "[3]", "1", "4", "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()", & soil_withdrawal, & soil_withdrawal_Tables, 2);
    declparam ("cov_type", TDim :: NHRU, "[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "
        "0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", & cov_type);
    declparam ("transp_limited", TDim :: NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", & transp_limited);
    declparam ("soil_ssr_runoff", TDim :: NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", & soil_ssr_runoff);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit.", "()", & inhibit_evap);
    declparam ("vol_frac_pt1", TDim :: NHRU, "[0.0]", "0", "1", "pt 1 volume fraction", "()", & vol_frac_pt1);
    declparam ("contrib_frac_pt1", TDim :: NHRU, "[0.0]", "0", "1", "pt 1 contrib fraction", "()", & contrib_frac_pt1);
    declparam ("vol_frac_pt2", TDim :: NHRU, "[0.0]", "0", "1", "pt 2 volume fraction", "()", & vol_frac_pt2);
    declparam ("contrib_frac_pt2", TDim :: NHRU, "[0.0]", "0", "1", "pt 2 contrib fraction", "()", & contrib_frac_pt2);
    declparam ("Sd_normal", TDim :: NHRU, "[0]", "0", "1", "inhibit special handling of depressional storage", "()", & Sd_normal);
    declputvar ("*", "hru_actet", "(mm/int)", & hru_actet);
    declputvar ("*", "hru_cum_actet", "(mm)", & hru_cum_actet);
    evapDiv = declgetvar ("*", "hru_evap", "(mm/int)", & hru_evap);
    declgetvar ("*", "hru_evap_PT", "(mm/int)", & hru_evap_PT);
    declgetvar ("*", "infil", "(mm/int)", & infil);
    snowinfilDiv = declgetvar ("*", "snowinfil", "(mm/int)", & snowinfil);
    runoffDiv = declgetvar ("*", "runoff", "(mm/int)", & runoff);
    meltrunoffDiv = declgetvar ("*", "meltrunoff", "(mm/int)", & meltrunoff);
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::decl(void)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::init(void)@@@ClassSoilPrairie.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (snowinfilDiv > 1)
    {
        string S = "Soil:  \"snowinfil\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (evapDiv > 1)
    {
        string S = "Soil:  \"hru_evap\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (meltrunoffDiv > 1)
    {
        string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (runoffDiv > 1)
    {
        string S = "Netroute:  \"runoff\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    double s_val;
    double h_val;
    for (hh = 0; hh < nhru; ++ hh) {
        if (soil_moist [hh] > soil_moist_max [hh])
        {
            string S = string ("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + to_string (hh + 1).c_str ();
            CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
            throw TExcept;
        }

        if (soil_rechr [hh] > soil_rechr_max [hh])
        {
            string S = string ("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + to_string (hh + 1).c_str ();
            CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
            LogError (TExcept);
            throw TExcept;
        }

        if (soil_rechr_max [hh] > soil_moist_max [hh])
        {
            string S = string ("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + to_string (hh + 1).c_str ();
            CRHMException TExcept (S.c_str (), TExcept :: WARNING);
            LogError (TExcept);
            throw TExcept;
        }

        if (Sdinit [hh] > Sdmax [hh])
        {
            string S = string ("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + to_string (hh + 1).c_str ();
            CRHMException Except (S.c_str (), TExcept :: TERMINATE);
            LogError (Except);
            throw Except;
        }

        if (gw_init [hh] > gw_max [hh])
        {
            string S = string ("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + to_string (hh + 1).c_str ();
            CRHMException Except (S.c_str (), TExcept :: TERMINATE);
            LogError (Except);
            throw Except;
        }

        soil_rechr [hh] = soil_rechr_init [hh];
        soil_moist [hh] = soil_moist_init [hh];
        redirected_residual [hh] = 0.0;
        cum_redirected_residual [hh] = 0.0;
        Sd [hh] = Sdinit [hh];
        gw [hh] = gw_init [hh];
        hru_cum_actet [hh] = 0.0;
        cum_hru_condense [hh] = 0.0;
        cum_infil_act [hh] = 0.0;
        soil_runoff_D [hh] = 0.0;
        soil_ssr_D [hh] = 0.0;
        soil_gw_D [hh] = 0.0;
        gw_flow_D [hh] = 0.0;
        infil_act [hh] = 0.0;
        infil_act_D [hh] = 0.0;
        cum_soil_runoff [hh] = 0.0;
        cum_soil_ssr [hh] = 0.0;
        cum_rechr_ssr [hh] = 0.0;
        cum_soil_gw [hh] = 0.0;
        cum_gw_flow [hh] = 0.0;
        cum_runoff_to_Sd [hh] = 0.0;
        if (Sdmax [hh] > 0.0 && soil_moist_max [hh] > 0.0)
        {
            Sd_water_frac [hh] = parametric_area_frac (Sd [hh] / Sdmax [hh]);
        }

        else
        {
            Sd_water_frac [hh] = 0.0;
        }

        contrib_frac [hh] = contrib_frac_init [hh];
        if (Sdmax [hh] > 0.0 && soil_moist_max [hh] > 0.0)
        {
            if (contrib_frac [hh] > Sd [hh] / Sdmax [hh])
            {
                contrib_frac [hh] = Sd [hh] / Sdmax [hh];
            }

        }

        total_evap [hh] = 0.0;
        if (variation == VARIATION_1)
        {
            if (Sd_normal [hh] == 0)
            {
                try {
                    current_area = new double * [(int) numSloughs [hh]];
                    current_depth = new double * [(int) numSloughs [hh]];
                    current_volume = new double * [(int) numSloughs [hh]];
                    S_values = new double * [(int) numSloughs [hh]];
                    h_values = new double * [(int) numSloughs [hh]];
                    wetland_drainage = new double * [(int) numSloughs [hh]];
                    for (int jj = 0; jj < (int) numSloughs [hh]; ++ jj) {
                        current_area [jj] = new double [nhru];
                        current_depth [jj] = new double [nhru];
                        current_volume [jj] = new double [nhru];
                        S_values [jj] = new double [nhru];
                        h_values [jj] = new double [nhru];
                        wetland_drainage [jj] = new double [nhru];
                        PCM_calc_h_and_S (Max_V_N [jj] [hh], Max_A_N [jj] [hh], s_val, h_val);
                        S_values [jj] [hh] = s_val;
                        h_values [jj] [hh] = h_val;
                    }
                }
                catch (std :: bad_alloc) {
                    CRHMException Except ("Could not allocate arrays in module PCM.", TExcept :: TERMINATE);
                    LogError (Except);
                    throw Except;
                }
                for (hh = 0; chkStruct (); ++ hh) {
                    max_slough_volume [hh] = 0.0;
                    max_slough_area [hh] = 0.0;
                    total_slough_basin_area [hh] = 0.0;
                    for (int jj = 0; jj < (int) numSloughs [hh]; ++ jj) {
                        if (hh < nhru)
                        {
                            current_volume [jj] [hh] = Init_V_N [jj] [hh];
                            wetland_drainage [jj] [hh] = PCM_wetland_drainage_area (Max_A_N [jj] [hh]);
                            max_slough_volume [hh] += Max_V_N [jj] [hh];
                            max_slough_area [hh] += Max_A_N [jj] [hh];
                            total_slough_basin_area [hh] += wetland_drainage [jj] [hh];
                        }

                    }
                    PCM_runoff_multiplier [hh] = hru_area [hh] / total_slough_basin_area [hh];
                    PCM_Sdmax [hh] = (max_slough_volume [hh] / hru_area [hh]) * 1000.0;
                }
                contrib_frac [hh] = contrib_frac_init [hh];
                if (Sdmax [hh] > 0.0 && soil_moist_max [hh] > 0.0)
                {
                    if (contrib_frac [hh] > Sd [hh] / Sdmax [hh])
                    {
                        contrib_frac [hh] = Sd [hh] / Sdmax [hh];
                    }

                }

            }

        }

        if (variation == VARIATION_2)
        {
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::init(void)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::run(void)@@@ClassSoilPrairie.cpp>");
    double soil_lower, excs, condense;
    double et;
    long nstep = getstep ();
    if (nstep == 1)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            LogMessageA (hh, string ("'" + Name + " (Soil)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_rechr [hh], hru_area [hh], basin_area [0]);
            LogMessageA (hh, string ("'" + Name + " (Soil)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_moist [hh], hru_area [hh], basin_area [0]);
            LogMessageA (hh, string ("'" + Name + " (Soil)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str (), Sd [hh], hru_area [hh], basin_area [0]);
            LogMessageA (hh, string ("'" + Name + " (Soil)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str (), gw [hh], hru_area [hh], basin_area [0]);
            LogDebug (" ");
            soil_moist_Init [hh] = soil_moist [hh];
            soil_rechr_Init [hh] = soil_rechr [hh];
            Sd_Init [hh] = Sd [hh];
            gw_Init [hh] = gw [hh];
        }
    }

    nstep = nstep % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (snowinfilDiv == 1)
        {
            snowinfil_buf [hh] = snowinfil [hh];
        }

        if (runoffDiv == 1)
        {
            runoff_buf [hh] = runoff [hh];
        }

        if (meltrunoffDiv == 1)
        {
            meltrunoff_buf [hh] = meltrunoff [hh];
        }

        if (evapDiv == 1)
        {
            hru_evap_buf [hh] = hru_evap [hh];
            hru_evap_PT_buf [hh] = hru_evap_PT [hh];
        }

        if (nstep == 1)
        {
            soil_runoff_D [hh] = 0.0;
            soil_ssr_D [hh] = 0.0;
            soil_gw_D [hh] = 0.0;
            gw_flow_D [hh] = 0.0;
            infil_act_D [hh] = 0.0;
        }

        hru_actet [hh] = 0.0;
        infil_act [hh] = 0.0;
        soil_gw [hh] = 0.0;
        soil_ssr [hh] = 0.0;
        rechr_ssr [hh] = 0.0;
        if (hru_evap_buf [hh] < 0.0)
        {
            condense = - hru_evap_buf [hh];
            cum_hru_condense [hh] += condense;
            hru_evap_buf [hh] = 0.0;
        }

        else
        {
            condense = 0.0;
        }

        if (soil_moist_max [hh] > 0.0)
        {
            soil_lower = soil_moist [hh] - soil_rechr [hh];
            double potential = infil [hh] + snowinfil_buf [hh] + condense;
            soil_rechr [hh] = soil_rechr [hh] + potential;
            if (soil_rechr [hh] > soil_rechr_max [hh])
            {
                excs = soil_rechr [hh] - soil_rechr_max [hh];
                soil_rechr [hh] = soil_rechr_max [hh];
                soil_lower = soil_lower + excs;
            }

            soil_moist [hh] = soil_lower + soil_rechr [hh];
            if (soil_moist [hh] > soil_moist_max [hh])
            {
                excs = soil_moist [hh] - soil_moist_max [hh];
                soil_moist [hh] = soil_moist_max [hh];
            }

            else
            {
                excs = 0.0;
            }

            infil_act [hh] = potential - excs;
            cum_infil_act [hh] += infil_act [hh];
            infil_act_D [hh] += infil_act [hh];
            if (! inhibit_evap [hh])
            {
                if (soil_rechr_max [hh] > 0.0)
                {
                    rechr_ssr [hh] = soil_rechr [hh] / soil_rechr_max [hh] * rechr_ssr_K [hh] / Global :: Freq;
                }

                if (rechr_ssr [hh] > soil_rechr [hh])
                {
                    rechr_ssr [hh] = soil_rechr [hh];
                }

                soil_rechr [hh] -= rechr_ssr [hh];
                if (soil_rechr [hh] < 0.0)
                {
                    soil_rechr [hh] = 0.0;
                }

                soil_moist [hh] -= rechr_ssr [hh];
                soil_ssr [hh] = rechr_ssr [hh];
                cum_rechr_ssr [hh] += rechr_ssr [hh];
            }

            double s2gw_k = soil_gw_K [hh] / Global :: Freq;
            if (excs >= s2gw_k)
            {
                soil_gw [hh] = s2gw_k;
                excs -= s2gw_k;
            }

            else
            {
                soil_gw [hh] = excs;
                excs = 0.0;
            }

            if (! soil_ssr_runoff [hh] && excs > 0.0)
            {
                soil_ssr [hh] += excs;
                excs = 0.0;
            }

        }

        else
        {
            excs = infil [hh] + snowinfil_buf [hh] + condense;
        }

        double runoff_to_Sd = 0.0;
        soil_runoff [hh] = meltrunoff_buf [hh] + runoff_buf [hh] + excs;
        if (soil_runoff [hh] > 0.0 || redirected_residual [hh] > 0.0)
        {
            if (variation == VARIATION_ORG && Sd_normal [hh] == 0)
            {
                runoff_to_Sd = parametric_Sd_add (soil_runoff [hh]);
                if (soil_runoff [hh] - runoff_to_Sd < 0.0)
                {
                    double Diff = runoff_to_Sd - soil_runoff [hh];
                    soil_runoff [hh] = Diff;
                    Sd [hh] = Sd [hh] - Diff;
                }

                else
                {
                    soil_runoff [hh] -= runoff_to_Sd;
                }

                if (redirected_residual [hh] > 0.0)
                {
                    runoff_to_Sd = parametric_Sd_add (redirected_residual [hh] / hru_area [hh]);
                    if (redirected_residual [hh] - runoff_to_Sd < 0.0)
                    {
                        runoff_to_Sd = redirected_residual [hh];
                        redirected_residual [hh] = 0.0;
                    }

                    else
                    {
                        redirected_residual [hh] -= runoff_to_Sd * hru_area [hh];
                        soil_runoff [hh] += redirected_residual [hh];
                    }

                }

            }

            else
            if (variation == VARIATION_1 && Sdmax [hh] > 0.0 && Sd_normal [hh] == 0)
            {
                PCM_runoff ();
                soil_runoff [hh] = (redirected_residual [hh] / hru_area [hh]);
                PCM_runoff ();
                soil_runoff [hh] = soil_runoff [hh] * PCM_runoff_multiplier [hh];
            }

            else
            if (variation == VARIATION_2 && Sdmax [hh] > 0.0 && Sd_normal [hh] == 0)
            {
                PDMROF_add_subtract ((meltrunoff_buf [hh] + runoff_buf [hh] + excs));
                PDMROF_add_subtract (redirected_residual [hh] / hru_area [hh]);
            }

            else
            {
                soil_runoff [hh] = meltrunoff_buf [hh] + runoff_buf [hh] + excs + (redirected_residual [hh] / hru_area [hh]);
                redirected_residual [hh] = 0.0;
            }

        }

        cum_redirected_residual [hh] += (redirected_residual [hh] / hru_area [hh]);
        redirected_residual [hh] = 0;
        soil_runoff_D [hh] += soil_runoff [hh];
        cum_soil_runoff [hh] += soil_runoff [hh];
        cum_runoff_to_Sd [hh] += runoff_to_Sd;
        if (Sd [hh] > 0.0 && Sd_gw_K [hh] > 0.0)
        {
            double Sd2gw_k = Sd_gw_K [hh] / Global :: Freq;
            if (Sd2gw_k > Sd [hh])
            {
                Sd2gw_k = Sd [hh];
            }

            soil_gw [hh] += Sd2gw_k;
            Sd [hh] -= Sd2gw_k;
            if (Sd [hh] < 0.0)
            {
                Sd [hh] = 0.0;
            }

        }

        soil_gw_D [hh] += soil_gw [hh];
        cum_soil_gw [hh] += soil_gw [hh];
        gw [hh] += soil_gw [hh];
        gw_flow [hh] = 0.0;
        if (gw [hh] > gw_max [hh])
        {
            gw_flow [hh] += (gw [hh] - gw_max [hh]);
            gw [hh] = gw_max [hh];
        }

        if (gw_max [hh] > 0.0)
        {
            double spill = gw [hh] / gw_max [hh] * gw_K [hh] / Global :: Freq;
            gw [hh] -= spill;
            gw_flow [hh] += spill;
        }

        gw_flow_D [hh] += gw_flow [hh];
        cum_gw_flow [hh] += gw_flow [hh];
        if (Sd [hh] > 0.0 && Sd_ssr_K [hh] > 0.0)
        {
            double Sd2ssr_k = Sd_ssr_K [hh] / Global :: Freq;
            if (Sd2ssr_k >= Sd [hh])
            {
                Sd2ssr_k = Sd [hh];
            }

            soil_ssr [hh] += Sd2ssr_k;
            Sd [hh] -= Sd2ssr_k;
            if (Sd [hh] < 0.0)
            {
                Sd [hh] = 0.0;
            }

        }

        double s2ssr_k = lower_ssr_K [hh] / Global :: Freq;
        if (s2ssr_k > 0.0)
        {
            double avail = soil_moist [hh] - soil_rechr [hh];
            if (s2ssr_k >= avail)
            {
                s2ssr_k = avail;
            }

            soil_moist [hh] -= s2ssr_k;
            soil_ssr [hh] += s2ssr_k;
        }

        cum_soil_ssr [hh] += soil_ssr [hh];
        soil_ssr_D [hh] += soil_ssr [hh];
        if ((Sd [hh] > 0.0 || soil_moist_max [hh] > 0.0) && hru_evap_PT_buf [hh] > 0.0)
        {
            if (variation == VARIATION_ORG && Sd_normal [hh] == 0)
            {
                wetlands_evap [hh] = parametric_Sd_subtract (hru_evap_PT_buf [hh]);
                hru_actet [hh] += wetlands_evap [hh];
            }

            else
            if (variation == VARIATION_1 && Sd_normal [hh] == 0)
            {
                PCM_evap (hru_evap_PT_buf [hh]);
                wetlands_evap [hh] = hru_evap_PT_buf [hh];
                hru_actet [hh] += wetlands_evap [hh];
            }

            else
            if (variation == VARIATION_2 && Sd_normal [hh] == 0)
            {
                wetlands_evap [hh] = hru_evap_PT_buf [hh];
                hru_actet [hh] += wetlands_evap [hh];
                PDMROF_add_subtract (hru_evap_PT_buf [hh]);
            }

        }

        else
        {
            wetlands_evap [hh] = 0.0;
        }

        double avail_evap = hru_evap_buf [hh] * (1.0 - Sd_water_frac [hh] * Sd_water_frac_max [hh]);
        if (avail_evap > 0.0 && soil_moist [hh] > 0.0 && cov_type [hh] > 0)
        {
            double pctl, pctr, etl, etr;
            if ((soil_moist_max [hh] - soil_rechr_max [hh]) > 0.0)
            {
                pctl = (soil_moist [hh] - soil_rechr [hh]) / (soil_moist_max [hh] - soil_rechr_max [hh]);
            }

            else
            {
                pctl = 0.0;
            }

            if (soil_rechr_max [hh] > 0.0)
            {
                pctr = soil_rechr [hh] / soil_rechr_max [hh];
            }

            else
            {
                pctr = 0.0;
            }

            etr = avail_evap;
            switch (soil_withdrawal_Tables [0] [hh]) {
            case 1:
                if (pctr < 0.25)
                {
                    etr = 0.5 * pctr * avail_evap;
                }

                break;
            case 2:
                if (pctr < 0.5)
                {
                    etr = pctr * avail_evap;
                }

                break;
            case 3:
                if (pctr <= 0.33)
                {
                    etr = 0.5 * pctr * avail_evap;
                }

                else
                if (pctr < 0.67)
                {
                    etr = pctr * avail_evap;
                }

                break;
            case 4:
                break;
            }
            if (etr > avail_evap)
            {
                etl = 0.0;
                etr = avail_evap;
            }

            else
            {
                etl = avail_evap - etr;
            }

            switch (soil_withdrawal_Tables [1] [hh]) {
            case 1:
                if (pctl < 0.25)
                {
                    etl = 0.5 * pctl * etl;
                }

                break;
            case 2:
                if (pctl < 0.5)
                {
                    etl = pctl * etl;
                }

                break;
            case 3:
                if (pctl <= 0.33)
                {
                    etl = 0.5 * pctl * etl;
                }

                else
                if (pctr < 0.67)
                {
                    etl = pctl * etl;
                }

                break;
            case 4:
                break;
            }
            long et_type = cov_type [hh];
            if (transp_limited [hh] == 1 && et_type == 2)
            {
                et_type = 1;
            }

            et = 0.0;
            switch (et_type) {
            case 0 - 1:
                break;
            case 1:
                if (etr > soil_rechr [hh])
                {
                    soil_rechr [hh] = 0.0;
                    et = soil_rechr [hh];
                }

                else
                {
                    soil_rechr [hh] = soil_rechr [hh] - etr;
                    et = etr;
                }

                soil_moist [hh] = soil_moist [hh] - et;
                break;
            case 2:
                if (etr + etl >= soil_moist [hh])
                {
                    et = soil_moist [hh];
                    soil_moist [hh] = 0.0;
                    soil_rechr [hh] = 0.0;
                }

                else
                {
                    et = etr + etl;
                    soil_moist [hh] = soil_moist [hh] - et;
                    if (etr > soil_rechr [hh])
                    {
                        soil_rechr [hh] = 0.0;
                    }

                    else
                    {
                        soil_rechr [hh] = soil_rechr [hh] - etr;
                    }

                }

                break;
            }
            hru_actet [hh] += et;
        }

        if (soil_moist_max [hh] <= 0.0 && Sdmax [hh] <= 0.0)
        {
            hru_actet [hh] = hru_evap_buf [hh];
        }

        hru_cum_actet [hh] += hru_actet [hh];
        if (nstep == 0)
        {
            if (snowinfilDiv > 1)
            {
                snowinfil_buf [hh] = snowinfil [hh] / snowinfilDiv;
            }

            if (runoffDiv > 1)
            {
                runoff_buf [hh] = runoff [hh] / runoffDiv;
            }

            if (meltrunoffDiv > 1)
            {
                meltrunoff_buf [hh] = meltrunoff [hh] / meltrunoffDiv;
            }

            if (evapDiv > 1)
            {
                hru_evap_buf [hh] = hru_evap [hh] / evapDiv;
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::run(void)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::finish(bool good)@@@ClassSoilPrairie.cpp>");
    if (variation == VARIATION_1)
    {
        if (Sd_normal [hh] == 0)
        {
            delete current_area;
            delete current_depth;
            delete current_volume;
            delete S_values;
            delete h_values;
            delete wetland_drainage;
        }

    }

    double Allcum_soil_runoff = 0.0;
    double Allcum_soil_ssr = 0.0;
    double Allcum_rechr_ssr = 0.0;
    double Allcum_soil_gw = 0.0;
    double Allcum_gw_flow = 0.0;
    double Allcum_infil_act = 0.0;
    double Allcum_soil_moist_change = 0.0;
    double Allcum_Sd_change = 0.0;
    double Allcum_gw_change = 0.0;
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_rechr [hh], hru_area [hh], basin_area [0], " *** information only - already included in 'soil_moist'.");
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_rechr [hh] - soil_rechr_Init [hh], hru_area [hh], basin_area [0], " *** information only - already included in 'soil_moist'.");
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_moist [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_moist [hh] - soil_moist_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str (), hru_cum_actet [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_hru_condense [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_infil_act [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_gw [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_runoff [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_rechr_ssr [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_ssr [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str (), Sd [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str (), Sd [hh] - Sd_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_runoff_to_Sd [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str (), gw [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str (), gw [hh] - gw_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_gw_flow [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        LogMessageA (hh, string ("'" + Name + " (SoilPrairie)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_redirected_residual [hh] / hru_area [hh], hru_area [hh], basin_area [0], " *** Added to this HRU surface runoff");
        LogDebug (" ");
        if (variation == VARIATION_1)
        {
            LogDebug (" ");
        }

        Allcum_soil_runoff += cum_soil_runoff [hh] * hru_area [hh];
        Allcum_soil_ssr += cum_soil_ssr [hh] * hru_area [hh];
        Allcum_rechr_ssr += cum_rechr_ssr [hh] * hru_area [hh];
        Allcum_soil_gw += cum_soil_gw [hh] * hru_area [hh];
        Allcum_gw_flow += cum_gw_flow [hh] * hru_area [hh];
        Allcum_infil_act += cum_infil_act [hh] * hru_area [hh];
        Allcum_soil_moist_change += (soil_moist [hh] - soil_moist_Init [hh]) * hru_area [hh];
        Allcum_Sd_change += (Sd [hh] - Sd_Init [hh]) * hru_area [hh];
        Allcum_gw_change += (gw [hh] - gw_Init [hh]) * hru_area [hh];
    }
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_soil_runoff (mm*basin): ").c_str (), Allcum_soil_runoff);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_soil_ssr (mm*basin): ").c_str (), Allcum_soil_ssr);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_rechr_ssr (mm*basin): ").c_str (), Allcum_rechr_ssr);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_soil_gw (mm*basin): ").c_str (), Allcum_soil_gw);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_gw_flow (mm*basin): ").c_str (), Allcum_gw_flow);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_infil_act (mm*basin): ").c_str (), Allcum_infil_act);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_soil_moist_change (mm*basin): ").c_str (), Allcum_soil_moist_change);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_Sd_change (mm*basin): ").c_str (), Allcum_Sd_change);
    LogMessage (string ("'" + Name + " (SoilPrairie)' Allcum_gw_change (mm*basin): ").c_str (), Allcum_gw_change);
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::finish(bool good)@@@ClassSoilPrairie.cpp>");
}const double maxerror = 0.00001;
const double maxiterations = 1000;

double ClassSoilPrairie :: parametric_contrib_frac_add (const double contrib_frac_slice, const double delta_Sd)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
    double vol_frac = 0.0;
    double vol_frac_delta = 0.0;
    double R = 0.0;
    double dest_vol_frac = 0.0;
    double dest_contrib_frac = 0.0;
    double source_vol_frac = 0.0;
    double source_contrib_frac = 0.0;
    double delta_y = 0.0;
    double delta_x = 0.0;
    double filling_curve_val = 0.0;
    if (Sdmax [hh] > 0.0)
    {
        vol_frac = Sd [hh] / Sdmax [hh];
        vol_frac_delta = delta_Sd / Sdmax [hh];
    }

    if (vol_frac >= 1.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
        return 1.0;
    }

    else
    if (vol_frac <= 0.0)
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
        return 0.0;
    }

    else
    {
        if (vol_frac < (vol_frac_pt1 [hh] - 0.01))
        {
            dest_vol_frac = vol_frac_pt1 [hh];
            dest_contrib_frac = contrib_frac_pt1 [hh];
            source_vol_frac = 0.0;
            source_contrib_frac = 0.0;
        }

        else
        if (vol_frac < (vol_frac_pt2 [hh] - 0.01))
        {
            dest_vol_frac = vol_frac_pt2 [hh];
            dest_contrib_frac = contrib_frac_pt2 [hh];
            source_vol_frac = vol_frac_pt1 [hh];
            source_contrib_frac = contrib_frac_pt1 [hh];
        }

        else
        {
            dest_vol_frac = 1.0;
            dest_contrib_frac = 1.0;
            source_vol_frac = vol_frac_pt2 [hh];
            source_contrib_frac = contrib_frac_pt2 [hh];
        }

        filling_curve_val = source_contrib_frac + ((dest_contrib_frac - source_contrib_frac) / (dest_vol_frac - source_vol_frac)) * (vol_frac - source_vol_frac);
        if (dest_contrib_frac < 0.001)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
            return dest_contrib_frac;
        }

        else
        if (contrib_frac_slice >= filling_curve_val)
        {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
            return filling_curve_val;
        }

        else
        {
            delta_y = max < double > (dest_contrib_frac - contrib_frac_slice, 0);
            delta_x = max < double > (dest_vol_frac - vol_frac, 0.001);
            double slope = delta_y / delta_x;
            slope = max < double > (slope, 0.0);
            R = min < double > (contrib_frac_slice + vol_frac_delta * slope, 1.0);
            R = max < double > (R, 0.0);

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
            return R;
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: parametric_Sd_add (const double applied_depth)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::parametric_Sd_add(const double applied_depth)@@@ClassSoilPrairie.cpp>");
    double Sd_initial;
    double delta_Sd;
    double delta_volfrac;
    double tolerance = 0.01;
    double contrib_frac_mean;
    double contrib_frac_new;
    double contrib_frac_slice;
    double Sd_total;
    double contrib_frac_error;
    double depth_frac;
    int slices;
    Sd_initial = Sd [hh];
    delta_Sd = (1.0 - contrib_frac [hh]) * applied_depth;
    if (Sdmax [hh] > 0.0)
    {
        delta_volfrac = delta_Sd / Sdmax [hh];
    }

    else
    {
        delta_volfrac = 0;
    }

    contrib_frac_new = parametric_contrib_frac_add (contrib_frac [hh], delta_Sd);
    if (contrib_frac [hh] > 0.0)
    {
        contrib_frac_error = fabs ((contrib_frac [hh] - contrib_frac_new) / contrib_frac [hh]);
    }

    else
    {
        contrib_frac_error = tolerance;
    }

    if (contrib_frac_error < tolerance)
    {
        contrib_frac_mean = (contrib_frac [hh] + contrib_frac_new) / 2.0;
        Sd_total = Sd [hh] + applied_depth * (1.0 - contrib_frac_mean);
        contrib_frac [hh] = contrib_frac_new;
    }

    else
    {
        slices = (int) min < double > (max < double > (contrib_frac_error / tolerance, 2.0), 100);
        depth_frac = applied_depth / slices;
        Sd_total = Sd [hh];
        contrib_frac_slice = contrib_frac [hh];
        for (long ii = 0; ii < slices; ++ ii) {
            delta_Sd = (1.0 - contrib_frac_slice) * depth_frac;
            Sd_total = Sd_total + delta_Sd;
            if (Sdmax [hh] > 0.0)
            {
                delta_volfrac = delta_Sd / Sdmax [hh];
            }

            else
            {
                delta_volfrac = 0.0;
            }

            contrib_frac_slice = parametric_contrib_frac_add (contrib_frac_slice, delta_Sd);
        }
        contrib_frac [hh] = contrib_frac_slice;
        if (contrib_frac [hh] < 0.0001)
        {
            contrib_frac [hh] = 0.0;
        }

    }

    delta_Sd = Sd_total - Sd [hh];
    Sd [hh] = Sd_total;
    total_evap [hh] = 0.0;
    if (Sdmax [hh] > 0.0)
    {
        Sd_water_frac [hh] = parametric_area_frac (Sd [hh] / Sdmax [hh]);
    }

    else
    {
        Sd_water_frac [hh] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_Sd_add(const double applied_depth)@@@ClassSoilPrairie.cpp>");
    return delta_Sd;
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_Sd_add(const double applied_depth)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: parametric_Sd_subtract (const double applied_depth)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::parametric_Sd_subtract(const double applied_depth)@@@ClassSoilPrairie.cpp>");
    double Sd_initial;
    double delta_Sd;
    double tolerance = 0.01;
    double water_area_frac_mean;
    double water_area_frac_new;
    double water_area_frac_slice;
    double Sd_total;
    double volfrac;
    double water_area_frac_error;
    int slices;
    Sd_initial = Sd [hh];
    delta_Sd = Sd_water_frac_max [hh] * Sd_water_frac [hh] * applied_depth;
    if (Sdmax [hh] > 0.0)
    {
        water_area_frac_new = parametric_area_frac ((Sd [hh] - delta_Sd) / Sdmax [hh]);
    }

    else
    {
        water_area_frac_new = 0.0;
    }

    if (Sd_water_frac [hh] > 0.0)
    {
        water_area_frac_error = fabs ((Sd_water_frac [hh] - water_area_frac_new) / Sd_water_frac [hh]);
    }

    else
    {
        water_area_frac_error = 0.0;
    }

    if (water_area_frac_error < tolerance)
    {
        water_area_frac_mean = (Sd_water_frac [hh] + water_area_frac_new) / 2.0;
        Sd_total = Sd [hh] - applied_depth * Sd_water_frac_max [hh] * water_area_frac_mean;
    }

    else
    {
        slices = (int) max < double > (water_area_frac_error / tolerance, 2.0);
        double depth_frac = applied_depth / slices;
        Sd_total = Sd_initial;
        water_area_frac_slice = Sd_water_frac [hh];
        for (long ii = 0; ii < slices; ++ ii) {
            delta_Sd = Sd_water_frac_max [hh] * water_area_frac_slice * depth_frac;
            Sd_total = Sd_total + delta_Sd;
            if (Sdmax [hh] > 0.0)
            {
                volfrac = Sd_total / Sdmax [hh];
            }

            else
            {
                volfrac = 0.0;
            }

            water_area_frac_slice = parametric_area_frac (volfrac);
        }
    }

    delta_Sd = Sd [hh] - Sd_total;
    Sd [hh] = Sd_total;
    total_evap [hh] += delta_Sd;
    if (Sdmax [hh] > 0.0)
    {
        Sd_water_frac [hh] = parametric_area_frac (Sd [hh] / Sdmax [hh]);
    }

    else
    {
        Sd_water_frac [hh] = 0.0;
    }

    contrib_frac [hh] = parametric_contrib_frac_subtract ();
    if (contrib_frac [hh] < 0.0001)
    {
        contrib_frac [hh] = 0.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_Sd_subtract(const double applied_depth)@@@ClassSoilPrairie.cpp>");
    return delta_Sd;
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_Sd_subtract(const double applied_depth)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: parametric_area_frac (const double vol_frac)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::parametric_area_frac(const double vol_frac)@@@ClassSoilPrairie.cpp>");
    double c1 = - 0.254337;
    double c2 = 1.22233;
    double c3 = 0.0261854;
    double ZZ = c1 * sqr (vol_frac) + c2 * vol_frac + c3;
    if (ZZ < 0.0)
    {
        ZZ = 0.0;
    }

    else
    if (ZZ > 1.0)
    {
        ZZ = 1.0;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_area_frac(const double vol_frac)@@@ClassSoilPrairie.cpp>");
    return ZZ;
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_area_frac(const double vol_frac)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: parametric_contrib_frac_subtract (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::parametric_contrib_frac_subtract(void)@@@ClassSoilPrairie.cpp>");
    if (total_evap [hh] > evap_threshold [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_subtract(void)@@@ClassSoilPrairie.cpp>");
        return 0.0;
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_subtract(void)@@@ClassSoilPrairie.cpp>");
        return max < double > (min < double > ((1.0 - total_evap [hh] / evap_threshold [hh]) * contrib_frac [hh], 1.0), 0.0);
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::parametric_contrib_frac_subtract(void)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: PCM_area_frac (double maxarea, double volume, double S, double h)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_area_frac(double maxarea, double volume, double S, double h)@@@ClassSoilPrairie.cpp>");
    double pval, areafrac;
    double currentdepth, currentarea;
    if (maxarea < maxPondArea_p1 [hh])
    {
        pval = p1 [hh];
    }

    else
    {
        pval = p2 [hh];
    }

    currentdepth = pow (volume * (1.0 + 2.0 / pval) / S, 1.0 / (1.0 + 2.0 / pval));
    currentdepth = min < double > (currentdepth, h);
    currentarea = S * pow (currentdepth, 2.0 / pval);
    areafrac = currentarea / maxarea;
    areafrac = min < double > (areafrac, 1.0);
    areafrac = max < double > (areafrac, 0.0);

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_area_frac(double maxarea, double volume, double S, double h)@@@ClassSoilPrairie.cpp>");
    return areafrac;
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_area_frac(double maxarea, double volume, double S, double h)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PCM_calc_h_and_S (double maxvolume, double maxarea, double & S, double & h)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_calc_h_and_S(double maxvolume, double maxarea, double & S, double & h)@@@ClassSoilPrairie.cpp>");
    double est_area, area_error, pval;
    int iterations;
    bool done;
    if (maxarea < maxPondArea_p1 [hh])
    {
        pval = p1 [hh];
    }

    else
    {
        pval = p2 [hh];
    }

    h = 1.0;
    done = false;
    iterations = 0;
    while (! done) {
        S = maxarea / pow (h, 2.0 / pval);
        h = pow ((maxvolume * (1.0 + 2.0 / pval)) / S, 1.0 / (1.0 + 2.0 / pval));
        est_area = S * pow (h, 2.0 / pval);
        area_error = fabs (est_area - maxarea) / maxarea;
        if ((area_error < maxerror) || (iterations > maxiterations))
        {
            done = true;
        }

        else
        {
            iterations = iterations + 1;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_calc_h_and_S(double maxvolume, double maxarea, double & S, double & h)@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: PCM_wetland_drainage_area (double maxarea)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_wetland_drainage_area(double maxarea)@@@ClassSoilPrairie.cpp>");
    if (maxarea > minPondArea [hh])
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_wetland_drainage_area(double maxarea)@@@ClassSoilPrairie.cpp>");
        return exp (basinarea_c1 [hh]) * pow (maxarea, basinarea_c2 [hh]);
    }

    else
    {

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_wetland_drainage_area(double maxarea)@@@ClassSoilPrairie.cpp>");
        return minPondBasinArea [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_wetland_drainage_area(double maxarea)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PCM_evap (double evap)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_evap(double evap)@@@ClassSoilPrairie.cpp>");
    if (evap > 0.0)
    {
        outflow_volume [hh] = 0.0;
        long i_evap = int (- 1.0 * evap);
        double evap_m = 1.0 / 1000.0;
        for (long jj = 0; jj < (long) numSloughs [hh]; ++ jj) {
            for (long pp = 0; pp < i_evap; ++ pp)
                current_volume [jj] [hh] = max < double > ((current_volume [jj] [hh] - (evap_m * Max_A_N [jj] [hh])), 0.0);
        }
    }

    PCM_set_Sd ();
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_evap(double evap)@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PCM_set_Sd ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_set_Sd()@@@ClassSoilPrairie.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        total_slough_volume [hh] = 0.0;
        for (long jj = 0; jj < (long) numSloughs [hh]; ++ jj) {
            total_slough_volume [hh] += current_volume [jj] [hh];
        }
        Sd [hh] = (total_slough_volume [hh] / hru_area [hh]) * 1000.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_set_Sd()@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PCM_rain ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_rain()@@@ClassSoilPrairie.cpp>");
    bool done;
    for (hh = 0; chkStruct (); ++ hh) {
        if (direct_rain [hh] > 0.0)
        {
            done = true;
            for (long jj = 0; jj < (long) numSloughs [hh]; ++ jj) {
                areafrac [hh] = PCM_area_frac (Max_A_N [jj] [hh], current_volume [jj] [hh], S_values [jj] [hh], h_values [jj] [hh]);
                current_volume [jj] [hh] = current_volume [jj] [hh] + (direct_rain [hh] * Max_A_N [jj] [hh] * areafrac [hh]) / 1000.0;
                if (current_volume [jj] [hh] >= Max_V_N [jj] [hh])
                {
                    done = false;
                }

            }
            if (! done)
            {
                PCM_outflow [hh] = PCM_outflow [hh] + PCM_route_excess ();
            }

        }

    }
    PCM_set_Sd ();
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_rain()@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PCM_runoff ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_runoff()@@@ClassSoilPrairie.cpp>");
    bool done;
    for (hh = 0; chkStruct (); ++ hh) {
        if (soil_runoff [hh] > 0.0)
        {
            done = true;
            for (long jj = 0; jj < (long) numSloughs [hh]; ++ jj) {
                current_volume [jj] [hh] = current_volume [jj] [hh] + (soil_runoff [hh] * wetland_drainage [jj] [hh]) / 1000.0;
                if (current_volume [jj] [hh] >= Max_V_N [jj] [hh])
                {
                    done = false;
                }

            }
            if (! done)
            {
                PCM_outflow [hh] = PCM_route_excess ();
            }

        }

    }
    PCM_set_Sd ();
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_runoff()@@@ClassSoilPrairie.cpp>");
}
double ClassSoilPrairie :: PCM_route_excess ()
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PCM_route_excess()@@@ClassSoilPrairie.cpp>");
    double largest_value, transferred_volume;
    bool done = false;
    const double tolerance = 0.1;
    long iter_count, destination;
    long const iter_max = 100;
    iter_count = 1;
    while (! done) {
        largest_value = 0.0;
        for (long jj = ((long) numSloughs [hh]) - 1; 0 < jj; -- jj) {
            if (current_volume [jj] [hh] > Max_V_N [jj] [hh])
            {
                transferred_volume = current_volume [jj] [hh] - Max_V_N [jj] [hh];
                current_volume [jj] [hh] = Max_V_N [jj] [hh];
                destination = Connect_N [jj] [hh] - 1;
                current_volume [destination] [hh] = current_volume [destination] [hh] + transferred_volume;
            }

            else
            {
                transferred_volume = 0.0;
            }

            if (transferred_volume > largest_value)
            {
                largest_value = transferred_volume;
            }

        }
        if ((largest_value <= tolerance) || (iter_count > iter_max))
        {
            done = true;
        }

        else
        {
            iter_count = iter_count + 1;
        }

    }
    outflow_volume [hh] = max < double > (current_volume [0] [hh] - Max_V_N [0] [hh], 0.0);
    current_volume [0] [hh] = min < double > (current_volume [0] [hh], Max_V_N [0] [hh]);

InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_route_excess()@@@ClassSoilPrairie.cpp>");
    return (outflow_volume [hh]);
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PCM_route_excess()@@@ClassSoilPrairie.cpp>");
}
void ClassSoilPrairie :: PDMROF_add_subtract (double deltaSd)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoilPrairie::PDMROF_add_subtract(double deltaSd)@@@ClassSoilPrairie.cpp>");
    double BP1;
    double IBP1;
    double SMXMCMN;
    double CMXMCMN;
    double SMAX;
    double CSTR;
    double FSTR;
    double RNET;
    double S;
    double SPRE;
    double CMIN_local;
    double CMAX_local;
    double U;
    CMIN_local = max < double > (0.0, CMIN [hh]);
    CMAX_local = max < double > (CMIN_local, CMAX [hh]);
    SPRE = Sd [hh] / 1000;
    S = SPRE + (deltaSd / 1000);
    SPRE = max < double > (CMIN_local, SPRE);
    BP1 = B [hh] + 1.0;
    IBP1 = 1.0 / BP1;
    CMXMCMN = CMAX_local - CMIN_local;
    SMAX = IBP1 * B [hh] * CMIN_local + CMAX_local;
    SMXMCMN = SMAX - CMIN_local;
    CSTR = CMIN [hh] + CMXMCMN * (1.0 - pow (((SMAX - SPRE) / SMXMCMN), IBP1));
    RNET = S - SPRE;
    if ((RNET > 1.0E-06) && (S > CMIN_local))
    {
        CSTR = min < double > (CMAX_local, CSTR + RNET);
        S = CMIN_local + SMXMCMN * (1.0 - pow (((CMAX_local - CSTR) / CMXMCMN), BP1));
        U = max < double > (0.0, RNET - (S - SPRE));
        Sd [hh] = min < double > (max < double > (0, S / 1000), Sdmax [hh]);
        soil_runoff [hh] += (U / 1000);
    }

    if (RNET < - 1.0E-06)
    {
        CSTR = min < double > (CMAX_local, CSTR + RNET);
        S = SPRE + RNET;
        Sd [hh] = min < double > (max < double > (0, S / 1000), Sdmax [hh]);
    }

    FSTR = 1.0 - pow ((1.0 - CSTR / CMAX_local), B [hh]);
    contrib_frac [hh] = FSTR;
InstrumentLogger::instance()->log_instrument_log("</ClassSoilPrairie::PDMROF_add_subtract(double deltaSd)@@@ClassSoilPrairie.cpp>");
}