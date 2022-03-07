#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassREWroute2.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassREWroute2 * ClassREWroute2 :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::klone(string name) const@@@ClassREWroute2.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::klone(string name) const@@@ClassREWroute2.cpp>");
    return new ClassREWroute2 (name);
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::klone(string name) const@@@ClassREWroute2.cpp>");
}
void ClassREWroute2 :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::decl(void)@@@ClassREWroute2.cpp>");
    Description = "'Handles the routing of surface and subsurface runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.' \
                    'uses Muskingum and culverts,' \
                    'uses Clark and culverts.'";
    variation_set = VARIATION_ORG;
    inflowCnt = declgrpvar ("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", & rew, & inflow_All);
    declvar ("WS_inflow", TDim :: NHRU, "inflow from each RB", "(m^3/int)", & inflow);
    declstatdiag ("cum_WSinflow", TDim :: NHRU, "cumulative inflow from each RB", "(m^3)", & cuminflow);
    declvar ("WS_outflow", TDim :: NHRU, "outflow of each RB", "(m^3/int)", & outflow);
    declstatdiag ("cum_WSoutflow", TDim :: NHRU, "cumulative outflow of each RB", "(m^3)", & cumoutflow);
    declvar ("WS_flow", TDim :: BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", & flow);
    declvar ("WS_flow_s", TDim :: BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", & flow_s);
    declstatdiag ("cum_WSflow", TDim :: BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", & cumflow);
    gwCnt = declgrpvar ("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", & gwrew, & gw_All);
    declvar ("WS_gwinflow", TDim :: NHRU, "inflow from each RB", "(m^3/int)", & gwinflow);
    declstatdiag ("cum_WSgwinflow", TDim :: NHRU, "cumulative inflow from each RB", "(m^3)", & cumgwinflow);
    declvar ("WS_gwoutflow", TDim :: NHRU, "outflow of each RB", "(m^3/int)", & gwoutflow);
    declstatdiag ("cum_WSgwoutflow", TDim :: NHRU, "cumulative outflow of each RB", "(m^3)", & cumgwoutflow);
    declvar ("WS_gwflow", TDim :: BASIN, "watershed ground water outflow", "(m^3/int)", & gwflow);
    declvar ("WS_gwflow_s", TDim :: BASIN, "watershed ground water outflow", "(m^3/s)", & gwflow_s);
    declstatdiag ("cum_WSgwflow", TDim :: BASIN, "cumulative watershed ground water outflow", "(m^3)", & cumgwflow);
    declparam ("WS_whereto", TDim :: NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", & WS_whereto);
    declparam ("WS_order", TDim :: NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", & WS_order);
    declparam ("WS_gwwhereto", TDim :: NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", & WS_gwwhereto);
    declparam ("WS_gworder", TDim :: NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", & WS_gworder);
    declparam ("WS_Lag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", & WS_Lag);
    declparam ("WS_gwLag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", & WS_gwLag);
    variation_set = VARIATION_2 + VARIATION_3;
    declvar ("WS_culvert_Q", TDim :: NHRU, "flow in culvert", "(m^3/s)", & culvert_Q);
    declvar ("WS_culvert_water_H", TDim :: NHRU, "depth of pond at culvert inlet", "(m)", & culvert_water_H);
    declvar ("WS_culvert_water_A", TDim :: NHRU, "surface area of culvert pond", "(m^2)", & culvert_water_A);
    declvar ("WS_culvert_water_V", TDim :: NHRU, "volume of water in culvert pond", "(m^3)", & culvert_water_V);
    declvar ("WS_culvert_over_Q", TDim :: NHRU, "flow over the road", "(m^3/s)", & culvert_over_Q);
    declvar ("WS_culvert_evap", TDim :: NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", & culvert_evap);
    declvar ("WS_cum_culvert", TDim :: NHRU, "Cumulative culvert HRU flow", "(m^3)", & cum_culvert);
    declvar ("WS_cum_culvert_over", TDim :: NHRU, "Cumulative culvert HRU overflow", "(m^3)", & cum_culvert_over);
    declstatdiag ("WS_HD", TDim :: NHRU, "ratio of depth of water at culvert/culvert diameter", "()", & HD);
    declparam ("WS_channel_slope", TDim :: NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert", "()", & WS_channel_slope);
    declparam ("WS_side_slope", TDim :: NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope", "()", & WS_side_slope);
    declparam ("WS_culvert_diam", TDim :: NHRU, "[0.5]", "0.1", "5.0", "culvert diameter", "(m)", & WS_culvert_diam);
    declparam ("WS_culvert_water_Dmax", TDim :: NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet", "(m)", & WS_culvert_water_Dmax);
    declparam ("WS_number_culverts", TDim :: NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert", "()", & WS_number_culverts);
    declparam ("WS_culvert_type", TDim :: NHRU, "[4]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet", "()", & WS_culvert_type);
    variation_set = VARIATION_0 + VARIATION_2;
    decldiag ("WS_Ktravel_var", TDim :: NHRU, "inflow storage constant", "(d)", & WS_Ktravel_var);
    decldiag ("WS_gwKtravel_var", TDim :: NHRU, "gw storage constant", "(d)", & WS_gwKtravel_var);
    declparam ("WS_route_n", TDim :: NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", & WS_route_n);
    declparam ("WS_route_R", TDim :: NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "()", & WS_route_R);
    declparam ("WS_route_S0", TDim :: NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", & WS_route_S0);
    declparam ("WS_route_L", TDim :: NHRU, "[3.69]", "0.01", "1.0E10", "routing length", "(m)", & WS_route_L);
    declparam ("WS_Channel_shp", TDim :: NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", & WS_Channel_shp);
    declparam ("WS_X_M", TDim :: NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", & WS_route_X_M);
    declparam ("WS_gwX_M", TDim :: NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", & WS_gwroute_X_M);
    variation_set = VARIATION_1 + VARIATION_3;
    declparam ("WS_Kstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", & WS_Kstorage);
    declparam ("WS_gwKstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", & WS_gwKstorage);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::decl(void)@@@ClassREWroute2.cpp>");
}
void ClassREWroute2 :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::init(void)@@@ClassREWroute2.cpp>");
    if (nhru < inflowCnt)
    {
        CRHMException Except ("Module REW route # of HRUs must be >= # of groups.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }

    if (WS_whereto [WS_order [nhru - 1] - 1] != 0)
    {
        CRHMException Except ("In module REW route 'whereto' for last RB must be zero.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }

    if (WS_gwwhereto [WS_gworder [nhru - 1] - 1] != 0)
    {
        CRHMException Except ("In module REW route 'gwwhereto' for last RB must be zero.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }

    if (variation == VARIATION_ORG || variation == VARIATION_2)
    {
        const double Vw [3] = {1.67, 1.44, 1.33};
        for (hh = 0; hh < nhru; ++ hh) {
            double Vavg = (1.0 / WS_route_n [hh]) * pow (WS_route_R [hh], 2.0f / 3.0f) * pow (WS_route_S0 [hh], 0.5f);
            WS_gwKtravel_var [hh] = WS_route_L [hh] / (Vw [WS_Channel_shp [hh]] * Vavg) / 86400.0;
            WS_Ktravel_var [hh] = WS_route_L [hh] / (Vw [WS_Channel_shp [hh]] * Vavg) / 86400.0;
        }
        inflowDelay = new ClassMuskingum (inflow, outflow, WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
        gwDelay = new ClassMuskingum (gwinflow, gwoutflow, WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);
        for (hh = 0; hh < nhru; ++ hh) {
            if (WS_gwKtravel_var [hh] >= (Global :: Interval / (2.0 * WS_gwroute_X_M [hh])))
            {
                string S = string ("'" + Name + " (REW_route) GW Muskingum coefficient negative in HRU ").c_str ();
                CRHMException TExcept (S.c_str (), TExcept :: WARNING);
                LogError (TExcept);
            }

            if (gwDelay -> c0 [hh] < 0.0)
            {
                gwDelay -> c0 [hh] = 0.0;
                gwDelay -> c1 [hh] = 1.0;
                gwDelay -> c2 [hh] = 0.0;
            }

            if (WS_Ktravel_var [hh] >= (Global :: Interval / (2.0 * WS_route_X_M [hh])))
            {
                string S = string ("'" + Name + " (REW_route) inflow Muskingum coefficient negative in HRU ").c_str ();
                CRHMException TExcept (S.c_str (), TExcept :: WARNING);
                LogError (TExcept);
            }

            if (WS_Ktravel_var [hh] < (Global :: Interval / (2.0 * (1.0 - WS_route_X_M [hh]))))
            {
                inflowDelay -> c0 [hh] = 0.0;
                inflowDelay -> c1 [hh] = 1.0;
                inflowDelay -> c2 [hh] = 0.0;
            }

        }
    }

    else
    if (variation == VARIATION_1 || variation == VARIATION_3)
    {
        Clark_inflowDelay = new ClassClark (inflow, outflow, WS_Kstorage, WS_Lag, nhru);
        Clark_gwDelay = new ClassClark (inflow, outflow, WS_gwKstorage, WS_gwLag, nhru);
    }

    flow [0] = 0.0;
    flow_s [0] = 0.0;
    cumflow [0] = 0.0;
    gwflow [0] = 0.0;
    gwflow_s [0] = 0.0;
    cumgwflow [0] = 0.0;
    for (hh = 0; hh < nhru; ++ hh) {
        inflow [hh] = 0.0;
        cuminflow [hh] = 0.0;
        outflow [hh] = 0.0;
        cumoutflow [hh] = 0.0;
        gwinflow [hh] = 0.0;
        cumgwinflow [hh] = 0.0;
        gwoutflow [hh] = 0.0;
        cumgwoutflow [hh] = 0.0;
        if (variation == VARIATION_2 || variation == VARIATION_3)
        {
            culvert_water_V [hh] = 0.0;
            culvert_water_H [hh] = 0.0;
            culvert_water_A [hh] = 0.0;
            culvert_over_Q [hh] = 0.0;
            culvert_Q [hh] = 0.0;
            HD [hh] = 0.0;
            culvert_evap [hh] = 0.0;
            cum_culvert [hh] = 0.0;
            cum_culvert_over [hh] = 0.0;
            if (WS_number_culverts [hh] > 0.0)
            {
                if (WS_culvert_water_Dmax [hh] / WS_culvert_diam [hh] > 2.5)
                {
                    string S = "soil: " + string (Name.c_str ()) + " ratio of H/D > 2.5 in HRU " + to_string (hh + 1);
                    CRHMException TExcept (S.c_str (), TExcept :: WARNING);
                    LogError (TExcept);
                }

            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::init(void)@@@ClassREWroute2.cpp>");
}
void ClassREWroute2 :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::run(void)@@@ClassREWroute2.cpp>");
    flow [0] = 0.0;
    gwflow [0] = 0.0;
    for (long jj = 0; jj < inflowCnt; ++ jj) {
        int hh = WS_order [jj] - 1;
        if (rew [hh])
        {
            inflow [hh] = inflow_All [hh] [0];
        }

        else
        {
            inflow [hh] = 0;
        }

        for (long hhh = 0; chkStruct (hhh); ++ hhh) {
            if (WS_whereto [hhh] - 1 == hh && outflow [hhh] > 0.0)
            {
                if (outflow [hhh] > 0.0)
                {
                    inflow [hh] += outflow [hhh];
                }

            }

        }
        cuminflow [hh] += inflow [hh];
        if (variation == VARIATION_2 || variation == VARIATION_3)
        {
            Culvert (hh);
        }

        if (variation == VARIATION_ORG || variation == VARIATION_2)
        {
            inflowDelay -> DoMuskingum (hh);
        }

        else
        if (variation == VARIATION_1 || variation == VARIATION_3)
        {
            Clark_inflowDelay -> DoClark (hh);
        }

        cumoutflow [hh] += outflow [hh];
        if (WS_whereto [hh] == 0)
        {
            flow [0] += outflow [hh];
            flow_s [0] = flow [0] * Global :: Freq / 86400.0;
        }

    }
    for (long jj = 0; jj < gwCnt; ++ jj) {
        int hh = WS_gworder [jj] - 1;
        if (gwrew [hh])
        {
            gwinflow [hh] = gw_All [hh] [0];
        }

        else
        {
            gwinflow [hh] = 0;
        }

        for (long hhh = 0; chkStruct (hhh); ++ hhh) {
            if (WS_gwwhereto [hhh] - 1 == hh && gwoutflow [hhh] > 0.0)
            {
                if (gwoutflow [hhh] > 0.0)
                {
                    gwinflow [hh] += gwoutflow [hhh];
                }

            }

        }
        cumgwinflow [hh] += gwinflow [hh];
        if (variation == VARIATION_ORG || variation == VARIATION_2)
        {
            gwDelay -> DoMuskingum (hh);
        }

        else
        if (variation == VARIATION_1 || variation == VARIATION_3)
        {
            Clark_gwDelay -> DoClark (hh);
        }

        cumgwoutflow [hh] += gwoutflow [hh];
        if (WS_gwwhereto [hh] == 0)
        {
            gwflow [0] += gwoutflow [hh];
            gwflow_s [0] = gwflow [0] * Global :: Freq / 86400.0;
        }

    }
    cumflow [0] += flow [0];
    cumgwflow [0] += gwflow [0];
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::run(void)@@@ClassREWroute2.cpp>");
}
void ClassREWroute2 :: Culvert (long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::Culvert(long hh)@@@ClassREWroute2.cpp>");
    double culvert_C [5] = {0.5, 0.6, 0.7, 0.75, 0.97};
    culvert_water_A [hh] = 0.0;
    culvert_water_H [hh] = 0.0;
    culvert_over_Q [hh] = 0.0;
    culvert_Q [hh] = 0.0;
    HD [hh] = 0.0;
    culvert_evap [hh] = 0.0;
    if ((inflow [hh] > 0.0 || culvert_water_V [hh] > 0.0) && WS_number_culverts [hh] > 0.0)
    {
        culvert_water_V [hh] += inflow [hh];
        inflow [hh] = 0.0;
        culvert_water_H [hh] = pow (3.0 * culvert_water_V [hh] * WS_channel_slope [hh] * WS_side_slope [hh], 1.0 / 3.0);
        if (culvert_water_H [hh] > 0.0)
        {
            culvert_water_H [hh] = pow (3.0 * culvert_water_V [hh] * WS_channel_slope [hh] * WS_side_slope [hh], 1.0 / 3.0);
            if (culvert_water_H [hh] > WS_culvert_water_Dmax [hh])
            {
                culvert_water_H [hh] = WS_culvert_water_Dmax [hh];
                double maxVol = pow (WS_culvert_water_Dmax [hh], 3.0) / (3.0 * WS_channel_slope [hh] * WS_side_slope [hh]);
                culvert_over_Q [hh] = (culvert_water_V [hh] - maxVol) / 86400 * Global :: Freq;
                culvert_water_V [hh] = maxVol;
                cum_culvert_over [hh] += culvert_over_Q [hh];
                cum_culvert [hh] += culvert_Q [hh] * 86400 / Global :: Freq;
                inflow [hh] += culvert_over_Q [hh] * 86400 / Global :: Freq;
            }

            HD [hh] = culvert_water_H [hh] / WS_culvert_diam [hh];
            if (HD [hh] <= 0.0)
            {
                culvert_Q [hh] = 0.0;
            }

            else
            if (HD [hh] < 1.5)
            {
                culvert_Q [hh] = max < double > ((- 0.544443 * pow (HD [hh], 4.0) + 0.221892 * pow (HD [hh], 3.0) + 2.29756 * pow (HD [hh], 2.0) + 0.159413 * HD [hh] + 0.00772254) * culvert_C [WS_culvert_type [hh]] * WS_number_culverts [hh] * pow (WS_culvert_diam [hh], 2.5), 0.0);
            }

            else
            {
                culvert_Q [hh] = culvert_C [WS_culvert_type [hh]] * WS_number_culverts [hh] * 0.785 * pow (WS_culvert_diam [hh], 2.5) * sqrt (2.0 * 9.81 * (HD [hh] - 0.5));
            }

            if (culvert_water_V [hh] > culvert_Q [hh] * 86400 / Global :: Freq)
            {
                culvert_water_V [hh] -= culvert_Q [hh] * 86400 / Global :: Freq;
            }

            else
            {
                culvert_Q [hh] = culvert_water_V [hh] / 86400 * Global :: Freq;
                culvert_water_V [hh] = 0.0;
            }

            inflow [hh] += culvert_Q [hh] * 86400 / Global :: Freq;
            cum_culvert [hh] += culvert_Q [hh] * 86400 / Global :: Freq;
            culvert_water_A [hh] = sqr (culvert_water_H [hh]) / (WS_channel_slope [hh] * WS_side_slope [hh]);
        }

    }

InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::Culvert(long hh)@@@ClassREWroute2.cpp>");
}
void ClassREWroute2 :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute2::finish(bool good)@@@ClassREWroute2.cpp>");
    for (hh = 0; hh < inflowCnt; ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (REW_route2)' cuminflow          (m^3) (m^3): ").c_str (), cuminflow [hh], 1.0);
        LogMessageA (hh, string ("'" + Name + " (REW_route2)' cumoutflow         (m^3) (m^3): ").c_str (), cumoutflow [hh], 1.0);
        if (variation == VARIATION_ORG || variation == VARIATION_2)
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route2)' inflowDelay_in_storage (m^3) (m^3): ").c_str (), inflowDelay -> Left (hh), 1.0);
        }

        else
        if (variation == VARIATION_1 || variation == VARIATION_3)
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route2)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str (), Clark_inflowDelay -> Left (hh), 1.0);
        }

        LogMessageA (hh, string ("'" + Name + " (REW_route2)' cumgwinflow  (m^3) (m^3): ").c_str (), cumgwinflow [hh], 1.0);
        LogMessageA (hh, string ("'" + Name + " (REW_route2)' cumgwoutflow (m^3) (m^3): ").c_str (), cumgwoutflow [hh], 1.0);
        if (variation == VARIATION_ORG || variation == VARIATION_2)
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route2)' gwDelay_in_storage (m^3) (m^3): ").c_str (), gwDelay -> Left (hh), 1.0);
        }

        else
        if (variation == VARIATION_1 || variation == VARIATION_3)
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route2)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str (), Clark_gwDelay -> Left (hh), 1.0);
        }

        LogDebug (" ");
    }
    LogMessage (string ("'" + Name + " (REW_route2)' cumflow (m^3): ").c_str (), cumflow [0]);
    LogMessage (string ("'" + Name + " (REW_route2)' cumgwflow (m^3): ").c_str (), cumgwflow [0]);
    LogDebug (" ");
    if (variation == VARIATION_ORG || variation == VARIATION_2)
    {
        delete inflowDelay;
        delete gwDelay;
    }

    else
    if (variation == VARIATION_1 || variation == VARIATION_3)
    {
        delete Clark_inflowDelay;
        delete Clark_gwDelay;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassREWroute2::finish(bool good)@@@ClassREWroute2.cpp>");
}