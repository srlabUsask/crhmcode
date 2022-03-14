#include "ClassSoil.h"
#include <algorithm>
#include "../../core/GlobalDll.h"
#include "../../core/ClassCRHM/ClassCRHM.h"
#include "../newmodules/SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
ClassSoil * ClassSoil :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoil::klone(string name) const@@@ClassSoil.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassSoil::klone(string name) const@@@ClassSoil.cpp>");
    return new ClassSoil (name);
InstrumentLogger::instance()->log_instrument_log("</ClassSoil::klone(string name) const@@@ClassSoil.cpp>");
}
void ClassSoil :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoil::decl(void)@@@ClassSoil.cpp>");
    Description = "'Handles soil moisture throughout the year.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'\
                 'Version with Weir limited runoff.'";
    variation_set = VARIATION_1;
    declvar ("culvert_Q", TDim :: NHRU, "flow in culvert.", "(m^3/s)", & culvert_Q);
    declvar ("culvert_water_H", TDim :: NHRU, "depth of pond at culvert inlet.", "(m)", & culvert_water_H);
    declvar ("culvert_water_A", TDim :: NHRU, "surface area of culvert pond.", "(m^2)", & culvert_water_A);
    declvar ("culvert_water_V", TDim :: NHRU, "volume of water in culvert pond.", "(m^3)", & culvert_water_V);
    declvar ("culvert_over_Q", TDim :: NHRU, "flow over the road.", "(m^3/s)", & culvert_over_Q);
    declvar ("culvert_evap", TDim :: NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", & culvert_evap);
    declstatdiag ("cum_culvert", TDim :: NHRU, "Cumulative culvert HRU flow.", "(m^3)", & cum_culvert);
    declstatdiag ("cum_culvert_over", TDim :: NHRU, "Cumulative culvert HRU overflow.", "(m^3)", & cum_culvert_over);
    decldiag ("HD", TDim :: NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", & HD);
    declparam ("stream_runoff", TDim :: NHRU, "[0.0]", "0.0", "1.0", "fraction of stream returned to runoff.", "()", & stream_runoff);
    declparam ("channel_slope", TDim :: NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", & channel_slope);
    declparam ("side_slope", TDim :: NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", & side_slope);
    declparam ("culvert_diam", TDim :: NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", & culvert_diam);
    declparam ("culvert_water_Dmax", TDim :: NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", & culvert_water_Dmax);
    declparam ("number_culverts", TDim :: NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", & number_culverts);
    declparam ("culvert_type", TDim :: NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", & culvert_type);
    variation_set = VARIATION_2;
    declvar ("weir_outflow", TDim :: NHRU, "weir_outflow.", "(m^3/int)", & weir_outflow);
    declvar ("weir_outflow_m3s", TDim :: NHRU, "weir_outflow.", "(m^3/s)", & weir_outflow_m3s);
    declvar ("weir_water_A", TDim :: NHRU, "surface area of weir pond.", "(m^2)", & weir_water_A);
    declvar ("weir_water_V", TDim :: NHRU, "volume of weir pond.", "(m^3)", & weir_water_V);
    declvar ("weir_water_h", TDim :: NHRU, "depth of weir pond.", "(m)", & weir_water_h);
    declvar ("weir_evap", TDim :: NHRU, "Depth of water evaporating from weir pond.", "(mm/int)", & weir_evap);
    declvar ("weir_crest_volume", TDim :: NHRU, "volume of pond at weir crest.", "(m^3)", & weir_crest_volume);
    declstatdiag ("cum_weir_over_m3", TDim :: NHRU, "Cumulative weir HRU overflow.", "(m^3)", & cum_weir_over_m3);
    declvar ("stream_to_Sd", TDim :: NHRU, "amount of soil runoff to stream.", "(mm/int)", & stream_to_Sd);
    declparam ("stream_Sd", TDim :: NHRU, "[0.0]", "0.0", "1.0", "fraction of stream returned to Sd.", "()", & stream_Sd);
    declparam ("weir_crest", TDim :: NHRU, "[10]", "0.0", "200.0", "weir crest height.", "()", & weir_crest);
    declparam ("weir_coefficient", TDim :: NHRU, "[1.705]", "0.01", "2.0", "weir_coefficient.", "()", & weir_coefficient);
    declparam ("weir_mult", TDim :: NHRU, "[1.0]", "0.01", "2.0", "weir_multiplier)", "()", & weir_mult);
    declparam ("weir_b", TDim :: NHRU, "[0.0]", "0.0", "1000.0", "breadth of weir. . Zero = no weir", "(m)", & weir_b);
    declparam ("lake_mult", TDim :: NHRU, "[1.0]", "1.0", "1.0e6", "lake rating curve multiplier.", "()", & lake_mult);
    declparam ("lake_power", TDim :: NHRU, "[1.0]", "0.1", "5.0", "lake rating curve power.", "()", & lake_power);
    declparam ("lake_p", TDim :: NHRU, "[1.72]", "1.0", "10.0", "lake shape factor.", "()", & lake_p);
    declparam ("lake_S", TDim :: NHRU, "[1.72]", "1000.0", "200000.0", "lake shape factor.", "()", & lake_S);
    variation_set = VARIATION_1 + VARIATION_2;
    declvar ("soil_runoff_stream", TDim :: NHRU, "amount of soil runoff to stream.", "(m^3)", & soil_runoff_stream);
    declparam ("runoff_stream", TDim :: NHRU, "[0.0]", "0.0", "1.0", "fraction of runoff diverted to stream.", "()", & runoff_stream);
    declvar ("stream", TDim :: NHRU, "Portion of runoff water retained in HRU as streamflow.", "(mm*km^2/int)", & stream);
    declvar ("cum_stream", TDim :: NHRU, "cumulative portion of runoff water retained in HRU as streamflow.", "(mm*km^2/int)", & cum_stream);
    declvar ("stream_Grp_in", TDim :: NHRU, "streamflow from other group (sub-basin.", "(mm*km^2/int)", & stream_Grp_in);
    declvar ("stream_Grp_loss", TDim :: BASIN, "amount of stream flow out of this sub-basin.", "(m^3)", & stream_Grp_loss);
    declvar ("cum_stream_Grp_loss", TDim :: BASIN, "cumulative amount of stream flow out of this sub-basin.", "(m^3)", & cum_stream_Grp_loss);
    variation_set = VARIATION_ORG;
    if (Global :: nlay < 2)
    {
        Global :: nlay = 2;
        Global :: maxlay = 2;
    }

    declvar ("current_getstep", TDim :: BASIN, "current getstep", "()", & current_getstep);
    declvar ("redirected_residual", TDim :: NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", & redirected_residual);
    declstatdiag ("cum_redirected_residual", TDim :: NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", & cum_redirected_residual);
    declstatvar ("Sd", TDim :: NHRU, "Depression storage.", "(mm)", & Sd);
    declstatvar ("gw", TDim :: NHRU, "ground water storage.", "(mm)", & gw);
    declstatvar ("soil_rechr", TDim :: NHRU, " available moisture content of soil recharge zone , ie, the"
        "portion of the soil profile from which evaporation can take place.", "(mm)", & soil_rechr);
    declstatvar ("soil_moist", TDim :: NHRU, " available moisture content of soil profile to the depth "
        "of the rooting zone of the major vegetation type on the HRU.", "(mm)", & soil_moist);
    decllocal ("cum_hru_condense", TDim :: NHRU, "cumulative condensation over HRU.", "(mm)", & cum_hru_condense);
    declvar ("cum_Sd_evap", TDim :: NHRU, "cumulative Sd evap over HRU.", "(mm)", & cum_Sd_evap);
    declvar ("soil_gw", TDim :: NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", & soil_gw);
    declvar ("Sd_gw", TDim :: NHRU, "Portion of excess Sd from a HRU that enters groundwater reservoirs.", "(mm/int)", & Sd_gw);
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
    declstatdiag ("cum_runoff_to_Sd", TDim :: NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", & cum_runoff_to_Sd);
    declstatdiag ("cum_soil_gw", TDim :: NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", & cum_soil_gw);
    declstatdiag ("cum_Sd_gw", TDim :: NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", & cum_Sd_gw);
    decllocal ("snowinfil_buf", TDim :: NHRU, "buffer snow infiltration.", "(mm/d)", & snowinfil_buf);
    decllocal ("runoff_buf", TDim :: NHRU, "buffer runoff.", "(mm/d)", & runoff_buf);
    decllocal ("meltrunoff_buf", TDim :: NHRU, "buffer melt runoff.", "(mm/d)", & meltrunoff_buf);
    decllocal ("hru_evap_buf", TDim :: NHRU, "buffer evaporation.", "(mm/d)", & hru_evap_buf);
    decllocal ("soil_moist_Init", TDim :: NHRU, "initial soil moisture.", "(mm)", & soil_moist_Init);
    decllocal ("soil_rechr_Init", TDim :: NHRU, "initial soil recharge.", "(mm)", & soil_rechr_Init);
    decllocal ("Sd_Init", TDim :: NHRU, "initial Depression storage.", "(mm)", & Sd_Init);
    decllocal ("gw_Init", TDim :: NHRU, "initial ground water storage.", "(mm)", & gw_Init);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", & hru_area);
    declparam ("Sdmax", TDim :: NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", & Sdmax);
    declparam ("Sdinit", TDim :: NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", & Sdinit);
    declparam ("soil_rechr_max", TDim :: NHRU, "[60.0]", "0.0", "350.0", "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", & soil_rechr_max);
    declparam ("soil_rechr_init", TDim :: NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "
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
    declparam ("soil_withdrawal", TDim :: NDEFN, "[3]", "1", "4", "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()", & soil_withdrawal, & soil_withdrawal_Tables, 2);
    declparam ("cov_type", TDim :: NHRU, "[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "
        "0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", & cov_type);
    declparam ("transp_limited", TDim :: NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", & transp_limited);
    declparam ("soil_ssr_runoff", TDim :: NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", & soil_ssr_runoff);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit.", "()", & inhibit_evap);
    decldiagparam ("Wetlands_scaling_factor", TDim :: NHRU, "[1.0]", "-1.0", "1.0", "Scaling ratio for available evaporation from wetland: no scaling applied when default value 1; using Sd/(Sd + soil_moist) as scale ratio when -1<= Wetlands_scaling_factor <0; using Wetlands_scaling_factor value as scale ratio when 0<= Wetlands_scaling_factor <1", "()", & Wetlands_scaling_factor);
    declputvar ("*", "hru_actet", "(mm/int)", & hru_actet);
    declputvar ("*", "hru_cum_actet", "(mm)", & hru_cum_actet);
    evapDiv = declgetvar ("*", "hru_evap", "(mm/int)", & hru_evap);
    declgetvar ("*", "infil", "(mm/int)", & infil);
    snowinfilDiv = declgetvar ("*", "snowinfil", "(mm/int)", & snowinfil);
    runoffDiv = declgetvar ("*", "runoff", "(mm/int)", & runoff);
    meltrunoffDiv = declgetvar ("*", "meltrunoff", "(mm/int)", & meltrunoff);
InstrumentLogger::instance()->log_instrument_log("</ClassSoil::decl(void)@@@ClassSoil.cpp>");
}
void ClassSoil :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoil::init(void)@@@ClassSoil.cpp>");
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
        cum_Sd_evap [hh] = 0.0;
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
        cum_Sd_gw [hh] = 0.0;
        cum_gw_flow [hh] = 0.0;
        cum_runoff_to_Sd [hh] = 0.0;
        if (variation == VARIATION_1 || variation == VARIATION_2)
        {
            stream [hh] = 0.0;
            stream_Grp_in [hh] = 0.0;
            stream_Grp_loss [hh] = 0.0;
            cum_stream_Grp_loss [hh] = 0.0;
            soil_runoff_stream [hh] = 0.0;
        }

        if (variation == VARIATION_1)
        {
            if (culvert_water_Dmax [hh] / culvert_diam [hh] > 2.5)
            {
                string S = "soil: " + string (Name.c_str ()) + " ratio of H/D > 2.5 in HRU " + to_string (hh + 1);
                CRHMException TExcept (S.c_str (), TExcept :: WARNING);
                LogError (TExcept);
            }

            culvert_water_V [hh] = 0.0;
            culvert_water_H [hh] = 0.0;
            culvert_water_A [hh] = 0.0;
            culvert_over_Q [hh] = 0.0;
            culvert_Q [hh] = 0.0;
            culvert_evap [hh] = 0.0;
            cum_culvert [hh] = 0.0;
            cum_culvert_over [hh] = 0.0;
        }

        if (variation == VARIATION_2)
        {
            weir_outflow [hh] = 0.0;
            weir_outflow_m3s [hh] = 0.0;
            weir_water_A [hh] = 0.0;
            cum_weir_over_m3 [hh] = 0.0;
            stream_to_Sd [hh] = 0.0;
            double H;
            weir_crest_volume [hh] = 10.0;
            H = pow (weir_crest_volume [hh] * (1.0 + 2.0 / lake_p [hh]) / lake_S [hh], 1.0 / (1.0 + 2.0 / lake_p [hh]));
            while (fabs (weir_crest [hh] - H) > 0.001) {
                weir_crest_volume [hh] += ((weir_crest [hh] - H) / weir_crest [hh] * weir_crest_volume [hh]);
                H = pow (weir_crest_volume [hh] * (1.0 + 2.0 / lake_p [hh]) / lake_S [hh], 1.0 / (1.0 + 2.0 / lake_p [hh]));
            }
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSoil::init(void)@@@ClassSoil.cpp>");
}
void ClassSoil :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoil::run(void)@@@ClassSoil.cpp>");
    double soil_lower, excs, condense;
    double et;
    double interval_secs = static_cast < double > (86400l) / Global :: Freq;
    long nstep = getstep ();
    current_getstep [0] = nstep;
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
    if (variation == VARIATION_1 || variation == VARIATION_2)
    {
        stream_Grp_loss [0] = stream [nhru - 1];
        cum_stream_Grp_loss [0] += stream_Grp_loss [0];
        for (hh = nhru - 1; hh > 0; -- hh)
            stream [hh] = stream [hh - 1];
        stream [0] = 0.0;
        for (hh = 0; chkStruct (); ++ hh) {
            stream [hh] = stream [hh] + stream_Grp_in [hh];
        }
    }

    for (hh = 0; chkStruct (); ++ hh) {
        if (snowinfilDiv == 1)
        {
            snowinfil_buf [hh] = snowinfil [hh];
        }

        if (runoffDiv == 1)
        {
            runoff_buf [hh] = runoff [hh];
            if (variation == VARIATION_1)
            {
                if (stream [hh] > 0.0 && stream_runoff [hh] > 0.0)
                {
                    runoff_buf [hh] += stream [hh - 1] * stream_runoff [hh] / hru_area [hh];
                    stream [hh] = stream [hh] * (1.0 - stream_runoff [hh]);
                }

            }

        }

        if (meltrunoffDiv == 1)
        {
            meltrunoff_buf [hh] = meltrunoff [hh];
        }

        if (evapDiv == 1)
        {
            hru_evap_buf [hh] = hru_evap [hh];
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
        Sd_gw [hh] = 0.0;
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
                rechr_ssr [hh] = soil_rechr [hh] / soil_rechr_max [hh] * rechr_ssr_K [hh] / Global :: Freq;
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
            if (s2gw_k > 0.0)
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
        soil_runoff [hh] = meltrunoff_buf [hh] + runoff_buf [hh] + excs + redirected_residual [hh] / hru_area [hh];
        cum_redirected_residual [hh] += redirected_residual [hh];
        redirected_residual [hh] = 0;
        if (soil_runoff [hh] > 0.0 && Sdmax [hh] > 0.0)
        {
            double Fix = - 12.0;
            if (soil_runoff [hh] / Sdmax [hh] < 12.0)
            {
                Fix = - soil_runoff [hh] / Sdmax [hh];
            }

            double Ds = (Sdmax [hh] - Sd [hh]) * (1 - exp (Fix));
            if (soil_moist_max [hh] <= 0.0)
            {
                Ds = Sdmax [hh] - Sd [hh];
            }

            if (Ds > 0.0)
            {
                if (soil_runoff [hh] > Ds)
                {
                    soil_runoff [hh] -= Ds;
                    if (soil_runoff [hh] < 0.0)
                    {
                        soil_runoff [hh] = 0.0;
                    }

                    Sd [hh] += Ds;
                    runoff_to_Sd += Ds;
                }

                else
                {
                    Sd [hh] += soil_runoff [hh];
                    runoff_to_Sd += soil_runoff [hh];
                    soil_runoff [hh] = 0.0;
                }

            }

        }

        if (variation == VARIATION_1)
        {
            if ((soil_runoff [hh] > 0.0001 || culvert_water_V [hh] > 0.0) && number_culverts [hh] > 0.0)
            {
                double culvert_C [5] = {0.5, 0.6, 0.7, 0.75, 0.97};
                culvert_water_H [hh] = 0.0;
                culvert_water_A [hh] = 0.0;
                culvert_over_Q [hh] = 0.0;
                culvert_Q [hh] = 0.0;
                culvert_evap [hh] = 0.0;
                culvert_water_V [hh] += soil_runoff [hh] * (hru_area [hh] * 1000.0);
                soil_runoff [hh] = 0.0;
                culvert_water_H [hh] = pow (3.0 * culvert_water_V [hh] * channel_slope [hh] * side_slope [hh], 1.0 / 3.0);
                if (culvert_water_H [hh] > 0.0)
                {
                    culvert_water_H [hh] = pow (3.0 * culvert_water_V [hh] * channel_slope [hh] * side_slope [hh], 1.0 / 3.0);
                    if (culvert_water_H [hh] > culvert_water_Dmax [hh])
                    {
                        culvert_water_H [hh] = culvert_water_Dmax [hh];
                        double maxVol = pow (culvert_water_Dmax [hh], 3.0) / (3.0 * channel_slope [hh] * side_slope [hh]);
                        culvert_over_Q [hh] = (culvert_water_V [hh] - maxVol) / 86400.0 * Global :: Freq;
                        culvert_water_V [hh] = maxVol;
                        cum_culvert_over [hh] += culvert_over_Q [hh] * interval_secs;
                        soil_runoff [hh] += culvert_over_Q [hh] * interval_secs / (hru_area [hh] * 1000.0);
                    }

                    HD [hh] = culvert_water_H [hh] / culvert_diam [hh];
                    if (HD [hh] <= 0.0)
                    {
                        culvert_Q [hh] = 0.0;
                    }

                    else
                    if (HD [hh] < 1.5)
                    {
                        culvert_Q [hh] = max < double > ((- 0.544443 * pow (HD [hh], 4.0) + 0.221892 * pow (HD [hh], 3.0) + 2.29756 * pow (HD [hh], 2.0) + 0.159413 * HD [hh] + 0.00772254) * culvert_C [culvert_type [hh]] * number_culverts [hh] * pow (culvert_diam [hh], 2.5), 0.0);
                    }

                    else
                    {
                        culvert_Q [hh] = culvert_C [culvert_type [hh]] * number_culverts [hh] * 0.785 * pow (culvert_diam [hh], 2.5) * sqrt (2.0 * 9.81 * (HD [hh] - 0.5));
                    }

                    if (culvert_water_V [hh] > culvert_Q [hh] * interval_secs)
                    {
                        culvert_water_V [hh] -= culvert_Q [hh] * interval_secs;
                    }

                    else
                    {
                        culvert_Q [hh] = culvert_water_V [hh] * interval_secs;
                        culvert_water_V [hh] = 0.0;
                    }

                    cum_culvert [hh] += culvert_Q [hh] * interval_secs;
                    soil_runoff [hh] += culvert_Q [hh] * interval_secs / (hru_area [hh] * 1000.0);
                }

                culvert_water_A [hh] = sqr (culvert_water_H [hh]) / (channel_slope [hh] * side_slope [hh]);
                if (runoff_stream [hh] > 0.0 && soil_runoff [hh] > 0.0)
                {
                    soil_runoff_stream [hh] = soil_runoff [hh] * runoff_stream [hh] * hru_area [hh];
                    stream [hh] += soil_runoff_stream [hh];
                    soil_runoff [hh] = soil_runoff [hh] * (1.0 - runoff_stream [hh]);
                }

            }

        }

        if (variation == VARIATION_2)
        {
            stream_to_Sd [hh] = 0.0;
            if (stream [hh] > 0.0001 && stream_Sd [hh] > 0.0001)
            {
                double possible = stream [hh] * stream_Sd [hh] / hru_area [hh];
                if (Sd [hh] + possible > Sdmax [hh])
                {
                    possible = Sdmax [hh] - Sd [hh];
                }

                Sd [hh] += possible;
                stream_to_Sd [hh] = possible;
                stream [hh] = stream [hh] - possible * hru_area [hh];
            }

            if (weir_b [hh] > 0.0)
            {
                if (Sd [hh] > 0.0)
                {
                    weir_water_V [hh] = Sd [hh] * hru_area [hh] * 1000;
                    weir_water_h [hh] = pow (weir_water_V [hh] * (1.0 + 2.0 / lake_p [hh]) / lake_S [hh], 1.0 / (1.0 + 2.0 / lake_p [hh]));
                    weir_water_A [hh] = lake_S [hh] * pow (weir_water_h [hh], 2.0 / lake_p [hh]);
                    double diff = weir_water_h [hh] - weir_crest [hh];
                    if (diff > 0.0)
                    {
                        weir_outflow_m3s [hh] = weir_b [hh] * weir_mult [hh] * pow (diff, weir_coefficient [hh]);
                        if (weir_outflow_m3s [hh] > (weir_water_V [hh] - weir_crest_volume [hh]))
                        {
                            weir_outflow_m3s [hh] = (weir_water_V [hh] - weir_crest_volume [hh] / interval_secs);
                        }

                        cum_weir_over_m3 [hh] += weir_outflow_m3s [hh];
                        weir_water_V [hh] -= weir_outflow_m3s [hh] * interval_secs;
                        weir_outflow [hh] = weir_outflow_m3s [hh] * interval_secs;
                        Sd [hh] = Sd [hh] - weir_outflow [hh] / hru_area [hh] / 1000.0;
                        weir_water_h [hh] = pow (weir_water_V [hh] * (1.0 + 2.0 / lake_p [hh]) / lake_S [hh], 1.0 / (1.0 + 2.0 / lake_p [hh]));
                        weir_water_A [hh] = lake_S [hh] * pow (weir_water_h [hh], 2.0 / lake_p [hh]);
                        soil_runoff [hh] += weir_outflow [hh] / hru_area [hh] / 1000.0;
                    }

                    else
                    {
                        weir_outflow [hh] = 0.0;
                        weir_outflow_m3s [hh] = 0.0;
                    }

                }

                else
                {
                    weir_water_V [hh] = 0.0;
                    weir_water_h [hh] = 0.0;
                    weir_water_A [hh] = 0.0;
                    weir_outflow [hh] = 0.0;
                    weir_outflow_m3s [hh] = 0.0;
                }

            }

            if (runoff_stream [hh] > 0.0 && soil_runoff [hh] > 0.0)
            {
                soil_runoff_stream [hh] = soil_runoff [hh] * runoff_stream [hh] * hru_area [hh];
                stream [hh] += soil_runoff_stream [hh];
                soil_runoff [hh] = soil_runoff [hh] * (1.0 - runoff_stream [hh]);
            }

        }

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

            Sd_gw [hh] += Sd2gw_k;
            Sd [hh] -= Sd2gw_k;
            if (Sd [hh] < 0.0)
            {
                Sd [hh] = 0.0;
            }

        }

        soil_gw_D [hh] += soil_gw [hh];
        cum_soil_gw [hh] += soil_gw [hh];
        cum_Sd_gw [hh] += Sd_gw [hh];
        gw [hh] += (soil_gw [hh] + Sd_gw [hh]);
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
        double culvert_evapL = 0;
        double culvert_pond = 0;
        if (variation == VARIATION_1 && culvert_water_V [hh] > 0.0 && hru_evap_buf [hh] > 0.0)
        {
            culvert_pond = culvert_water_V [hh] / (hru_area [hh] * 1000.0);
            culvert_evapL = hru_evap_buf [hh] * culvert_water_A [hh] / (hru_area [hh] * 1e6);
            if (culvert_evapL > culvert_pond)
            {
                culvert_evapL = culvert_pond;
            }

            culvert_evap [hh] = culvert_evapL;
            hru_actet [hh] += culvert_evapL;
            culvert_water_V [hh] = (culvert_pond - culvert_evapL) * (hru_area [hh] * 1000.0);
        }

        double weir_evapL = 0;
        double weir_pond = 0;
        if (variation == VARIATION_2 && weir_water_V [hh] > 0.0 && hru_evap_buf [hh] > 0.0)
        {
            weir_pond = weir_water_V [hh] / (hru_area [hh] * 1000.0);
            weir_evapL = hru_evap_buf [hh] * weir_water_A [hh] / (hru_area [hh] * 1e6);
            if (weir_evapL > weir_pond)
            {
                weir_evapL = weir_pond;
            }

            weir_evap [hh] = weir_evapL;
            hru_actet [hh] += weir_evapL;
            weir_water_V [hh] = (weir_pond - weir_evapL) * (hru_area [hh] * 1000.0);
        }

        double avail_evap = hru_evap_buf [hh] - culvert_evapL - weir_evapL;
        if (Sd [hh] + soil_moist [hh] + weir_pond > 0.0)
        {
            if (Wetlands_scaling_factor [hh] < 0.0)
            {
                avail_evap *= (Sd [hh] / (Sd [hh] + soil_moist [hh]));
            }

            else
            {
                avail_evap *= Wetlands_scaling_factor [hh];
            }

        }

        else
        {
            avail_evap = 0.0;
        }

        if (Sd [hh] > 0.0 && avail_evap > 0.0)
        {
            if (Sd [hh] >= avail_evap)
            {
                Sd [hh] -= avail_evap;
                if (Sd [hh] < 0.0)
                {
                    Sd [hh] = 0.0;
                }

            }

            else
            {
                avail_evap = Sd [hh];
                Sd [hh] = 0.0;
            }

            cum_Sd_evap [hh] += avail_evap;
            hru_actet [hh] += avail_evap;
        }

        else
        {
            avail_evap = 0.0;
        }

        avail_evap = hru_evap_buf [hh] - avail_evap - culvert_evapL;
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

            pctr = soil_rechr [hh] / soil_rechr_max [hh];
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
            case 0:
            case - 1:
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
    if (variation == VARIATION_1 || variation == VARIATION_2)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            stream_Grp_in [hh] = 0.0;
            cum_stream [hh] += stream [hh];
        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassSoil::run(void)@@@ClassSoil.cpp>");
}
void ClassSoil :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSoil::finish(bool good)@@@ClassSoil.cpp>");
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
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (Soil)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_rechr [hh], hru_area [hh], basin_area [0], " *** information only - already included in 'soil_moist'.");
        LogMessageA (hh, string ("'" + Name + " (Soil)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_rechr [hh] - soil_rechr_Init [hh], hru_area [hh], basin_area [0], " *** information only - already included in 'soil_moist'.");
        LogMessageA (hh, string ("'" + Name + " (Soil)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_moist [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str (), soil_moist [hh] - soil_moist_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str (), hru_cum_actet [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_Sd_evap        (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_Sd_evap [hh], hru_area [hh], basin_area [0], " *** information only - already included in 'hru_actet'.");
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_hru_condense [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_infil_act [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_gw [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_runoff [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_rechr_ssr [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_soil_ssr [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str (), Sd [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str (), Sd [hh] - Sd_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_runoff_to_Sd [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_Sd_gw          (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_Sd_gw [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str (), gw [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str (), gw [hh] - gw_Init [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_gw_flow [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        LogMessageA (hh, string ("'" + Name + " (Soil)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str (), cum_redirected_residual [hh] / hru_area [hh], hru_area [hh], basin_area [0], " *** Added to this HRU surface runoff");
        LogDebug (" ");
        if (variation == VARIATION_1)
        {
            LogMessageA (hh, string ("'" + Name + " (Soil)' cum_culvert         (m3) (m3*hru) (m3*hru/basin): ").c_str (), cum_culvert [hh], hru_area [hh], basin_area [0]);
            LogMessageA (hh, string ("'" + Name + " (Soil)' cum_culvert_over    (m3) (m3*hru) (m3*hru/basin): ").c_str (), cum_culvert_over [hh], hru_area [hh], basin_area [0]);
            LogDebug (" ");
        }

        if (variation == VARIATION_1 || variation == VARIATION_2)
        {
            LogMessageA (hh, string ("'" + Name + " (Soil)' cum_stream          (m3) (m3*hru) (m3*hru/basin): ").c_str (), cum_stream [hh], hru_area [hh], basin_area [0]);
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
        if (variation == VARIATION_1 || variation == VARIATION_2)
        {
            Allcum_stream_Grp_loss += cum_stream [hh];
        }

        if (variation == VARIATION_1 || variation == VARIATION_2)
        {
            LogMessage (string ("'" + Name + " (Soil)' Allcum_stream_Grp_loss (mm*basin): ").c_str (), Allcum_stream_Grp_loss);
        }

        LogDebug (" ");
    }
    LogMessage (string ("'" + Name + " (Soil)' Allcum_soil_runoff (mm*basin): ").c_str (), Allcum_soil_runoff);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_soil_ssr (mm*basin): ").c_str (), Allcum_soil_ssr);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_rechr_ssr (mm*basin): ").c_str (), Allcum_rechr_ssr);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_soil_gw (mm*basin): ").c_str (), Allcum_soil_gw);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_gw_flow (mm*basin): ").c_str (), Allcum_gw_flow);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_infil_act (mm*basin): ").c_str (), Allcum_infil_act);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_soil_moist_change (mm*basin): ").c_str (), Allcum_soil_moist_change);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_Sd_change (mm*basin): ").c_str (), Allcum_Sd_change);
    LogMessage (string ("'" + Name + " (Soil)' Allcum_gw_change (mm*basin): ").c_str (), Allcum_gw_change);
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassSoil::finish(bool good)@@@ClassSoil.cpp>");
}