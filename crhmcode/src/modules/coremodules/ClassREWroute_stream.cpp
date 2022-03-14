#include "ClassREWroute_stream.h"
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
ClassREWroute_stream * ClassREWroute_stream :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute_stream::klone(string name) const@@@ClassREWroute_stream.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::klone(string name) const@@@ClassREWroute_stream.cpp>");
    return new ClassREWroute_stream (name);
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::klone(string name) const@@@ClassREWroute_stream.cpp>");
}
void ClassREWroute_stream :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute_stream::decl(void)@@@ClassREWroute_stream.cpp>");
    Description = "'Handles the routing of stream runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.'";
    variation_set = VARIATION_ORG;
    instreamflowCnt = declgrpvar ("WS_ALL_instreamflow", "stream", "query variable = 'stream'", "(mm*km^2/int)", & rew, & instreamflow_All);
    instreamflowCnt = declgrpvar ("WS_ALL_instreamflow_Grp_in", "stream_Grp_in", "query variable = 'stream_Grp_in'", "(mm*km^2/int)", & rew, & instreamflow_Grp_out_All);
    declvar ("WS_instreamflow", TDim :: NHRU, "inflow from each RB", "(m^3/int)", & instreamflow);
    declvar ("cum_WSinstreamflow", TDim :: NHRU, "cumulative inflow from each RB", "(m^3)", & cuminstreamflow);
    declvar ("WS_outstreamflow", TDim :: NHRU, "outflow of each RB", "(m^3/int)", & outstreamflow);
    declvar ("cum_WSoutstreamflow", TDim :: NHRU, "cumulative outflow of each RB", "(m^3)", & cumoutstreamflow);
    declvar ("WS_streamflow", TDim :: BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", & streamflow);
    declvar ("WS_streamflow_s", TDim :: BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", & streamflow_s);
    declvar ("cum_WSstreamflow", TDim :: BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", & cumstreamflow);
    declparam ("WS_stream_Lag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", & WS_stream_Lag);
    declparam ("WS_stream_whereto_Grp", TDim :: NHRU, "[0]", "0", "1000", "this stream to this Grp", "()", & WS_stream_whereto_Grp);
    declparam ("WS_stream_whereto_HRU", TDim :: NHRU, "[0]", "0", "1000", "this stream to this HRU in the next Grp", "()", & WS_stream_whereto_HRU);
    declparam ("WS_stream_wherefrom_HRU", TDim :: NHRU, "[0]", "1", "1000", "this stream to this HRU in the next Grp", "()", & WS_stream_wherefrom_HRU);
    declparam ("WS_stream_order", TDim :: NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", & WS_stream_order);
    variation_set = VARIATION_0;
    decldiag ("WS_stream_Ktravel_var", TDim :: NHRU, "inflow storage constant", "(d)", & WS_stream_Ktravel_var);
    declparam ("WS_stream_route_n", TDim :: NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", & WS_stream_route_n);
    declparam ("WS_stream_route_R", TDim :: NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "()", & WS_stream_route_R);
    declparam ("WS_stream_route_S0", TDim :: NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", & WS_stream_route_S0);
    declparam ("WS_stream_route_L", TDim :: NHRU, "[3.69]", "0.01", "1.0E10", "routing length", "(m)", & WS_stream_route_L);
    declparam ("WS_stream_Channel_shp", TDim :: NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", & WS_stream_Channel_shp);
    declparam ("WS_stream_X_M", TDim :: NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", & WS_stream_route_X_M);
    variation_set = VARIATION_1;
    declparam ("WS_stream_Kstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", & WS_stream_Kstorage);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::decl(void)@@@ClassREWroute_stream.cpp>");
}
void ClassREWroute_stream :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute_stream::init(void)@@@ClassREWroute_stream.cpp>");
    if (nhru < instreamflowCnt)
    {
        CRHMException Except ("Module REW route # of HRUs must be >= # of groups.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }

    if (WS_stream_whereto_Grp [WS_stream_order [nhru - 1] - 1] != 0)
    {
        CRHMException Except ("In module REW route 'whereto' for last RB must be zero.", TExcept :: TERMINATE);
        LogError (Except);
        throw Except;
    }

    if (variation == VARIATION_ORG)
    {
        const double Vw [3] = {1.67, 1.44, 1.33};
        for (hh = 0; hh < nhru; ++ hh) {
            double Vavg = (1.0 / WS_stream_route_n [hh]) * pow (WS_stream_route_R [hh], 2.0f / 3.0f) * pow (WS_stream_route_S0 [hh], 0.5f);
            WS_stream_Ktravel_var [hh] = WS_stream_route_L [hh] / (Vw [WS_stream_Channel_shp [hh]] * Vavg) / 86400.0;
        }
        instreamflowDelay = new ClassMuskingum (instreamflow, outstreamflow, WS_stream_Ktravel_var, WS_stream_route_X_M, WS_stream_Lag, nhru);
        for (hh = 0; hh < nhru; ++ hh) {
            cuminstreamflow [hh] = 0.0;
            if (WS_stream_Ktravel_var [hh] >= (Global :: Interval / (2.0 * WS_stream_route_X_M [hh])))
            {
                string S = string ("'" + Name + " (REW_route) inflow Muskingum coefficient negative in HRU ").c_str ();
                CRHMException TExcept (S.c_str (), TExcept :: WARNING);
                LogError (TExcept);
            }

            if (WS_stream_Ktravel_var [hh] < (Global :: Interval / (2.0 * (1.0 - WS_stream_route_X_M [hh]))))
            {
                instreamflowDelay -> c0 [hh] = 0.0;
                instreamflowDelay -> c1 [hh] = 1.0;
                instreamflowDelay -> c2 [hh] = 0.0;
            }

        }
    }

    else
    if (variation == VARIATION_1)
    {
        Clark_instreamflowDelay = new ClassClark (instreamflow, outstreamflow, WS_stream_Kstorage, WS_stream_Lag, nhru);
    }

    streamflow [0] = 0.0;
    streamflow_s [0] = 0.0;
    cumstreamflow [0] = 0.0;
    for (hh = 0; hh < nhru; ++ hh) {
        instreamflow [hh] = 0.0;
        cuminstreamflow [hh] = 0.0;
        outstreamflow [hh] = 0.0;
        cumoutstreamflow [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::init(void)@@@ClassREWroute_stream.cpp>");
}
void ClassREWroute_stream :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute_stream::run(void)@@@ClassREWroute_stream.cpp>");
    streamflow [0] = 0.0;
    for (long jj = 0; jj < instreamflowCnt; ++ jj) {
        int hh = WS_stream_order [jj] - 1;
        instreamflow [hh] = 0.0;
        long to_GRP = WS_stream_whereto_Grp [hh] - 1;
        if (to_GRP > 0 && WS_stream_wherefrom_HRU [hh] > 0)
        {
            instreamflow [hh] = instreamflow_All [hh] [WS_stream_wherefrom_HRU [hh] - 1];
            cuminstreamflow [hh] += instreamflow [hh];
            instreamflow_All [hh] [WS_stream_wherefrom_HRU [hh] - 1] = 0.0;
            if (variation == VARIATION_ORG)
            {
                instreamflowDelay -> DoMuskingum (hh);
            }

            else
            if (variation == VARIATION_1)
            {
                Clark_instreamflowDelay -> DoClark (hh);
            }

            if (outstreamflow [hh] > 0.00001)
            {
                cumoutstreamflow [hh] += outstreamflow [hh];
                if (WS_stream_whereto_HRU [hh] > 0 && WS_stream_whereto_HRU [hh] < rew [to_GRP])
                {
                    instreamflow_Grp_out_All [to_GRP] [WS_stream_whereto_HRU [hh] - 1] += outstreamflow [hh];
                }

                else
                if (WS_stream_whereto_HRU [hh] == 0)
                {
                    streamflow [0] += outstreamflow [hh];
                    streamflow_s [0] = streamflow [0] * Global :: Freq / 86400.0;
                    cumstreamflow [0] += streamflow [0];
                }

            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::run(void)@@@ClassREWroute_stream.cpp>");
}
void ClassREWroute_stream :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassREWroute_stream::finish(bool good)@@@ClassREWroute_stream.cpp>");
    for (hh = 0; hh < instreamflowCnt; ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (REW_route)' cuminstreamflow          (m^3) (m^3): ").c_str (), cuminstreamflow [hh], 1.0);
        LogMessageA (hh, string ("'" + Name + " (REW_route)' cumoutstreamflow         (m^3) (m^3): ").c_str (), cumoutstreamflow [hh], 1.0);
        if (variation == VARIATION_ORG)
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route)' inflowDelay_in_storage (m^3) (m^3): ").c_str (), instreamflowDelay -> Left (hh), 1.0);
        }

        else
        {
            LogMessageA (hh, string ("'" + Name + " (REW_route)' Clark_instreamflowDelay_in_storage (m^3) (m^3): ").c_str (), Clark_instreamflowDelay -> Left (hh), 1.0);
        }

        LogDebug (" ");
    }
    LogMessage (string ("'" + Name + " (REW_route)' cumstreamflow (m^3): ").c_str (), cumstreamflow [0]);
    LogDebug (" ");
    if (variation == VARIATION_ORG)
    {
        delete instreamflowDelay;
    }

    else
    {
        delete Clark_instreamflowDelay;
    }

InstrumentLogger::instance()->log_instrument_log("</ClassREWroute_stream::finish(bool good)@@@ClassREWroute_stream.cpp>");
}