#include "ClassNetroute_D.h"
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
ClassNetroute_D * ClassNetroute_D :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::klone(string name) const@@@ClassNetroute_D.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::klone(string name) const@@@ClassNetroute_D.cpp>");
    return new ClassNetroute_D (name);
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::klone(string name) const@@@ClassNetroute_D.cpp>");
}
double ClassNetroute_D :: Function1 (double * I, long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::Function1(double * I, long hh)@@@ClassNetroute_D.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::Function1(double * I, long hh)@@@ClassNetroute_D.cpp>");
    return runDelay -> ChangeLag (I, hh);
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::Function1(double * I, long hh)@@@ClassNetroute_D.cpp>");
}
double ClassNetroute_D :: Function2 (double * X, long hh)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::Function2(double * X, long hh)@@@ClassNetroute_D.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::Function2(double * X, long hh)@@@ClassNetroute_D.cpp>");
    return runDelay -> ChangeStorage (X, hh);
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::Function2(double * X, long hh)@@@ClassNetroute_D.cpp>");
}
void ClassNetroute_D :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::decl(void)@@@ClassNetroute_D.cpp>");
    Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method. Distributed flow.'";
    declvar ("inflow", TDim :: NHRU, "inflow from other HRUs", "(mm*km^2/int)", & inflow);
    declstatdiag ("cuminflow", TDim :: NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", & cuminflow);
    declvar ("outflow", TDim :: NHRU, "HRU outflow", "(mm*km^2/int)", & outflow);
    declstatdiag ("cumoutflow", TDim :: NHRU, "cumulative HRU outflow", "(mm*km^2)", & cumoutflow);
    decldiag ("outflow_diverted", TDim :: NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", & outflow_diverted);
    declstatdiag ("cumoutflow_diverted", TDim :: NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", & cumoutflow_diverted);
    decldiag ("gwoutflow_diverted", TDim :: NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", & gwoutflow_diverted);
    declstatdiag ("gwcumoutflow_diverted", TDim :: NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", & gwcumoutflow_diverted);
    declstatdiag ("cum_to_Sd", TDim :: NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", & cum_to_Sd);
    declstatdiag ("cum_to_soil_rechr", TDim :: NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", & cum_to_soil_rechr);
    declvar ("gwinflow", TDim :: NHRU, "ground water inflow", "(mm*km^2/int)", & gwinflow);
    declstatdiag ("gwcuminflow", TDim :: NHRU, "cumulative gw inflow", "(mm*km^2)", & gwcuminflow);
    declvar ("gwoutflow", TDim :: NHRU, "HRU gw outflow", "(mm*km^2/int)", & gwoutflow);
    declstatdiag ("gwcumoutflow", TDim :: NHRU, "cumulative HRU gw outflow", "(mm*km^2)", & gwcumoutflow);
    declvar ("ssrinflow", TDim :: NHRU, "inflow from other HRUs", "(mm*km^2/int)", & ssrinflow);
    declstatdiag ("ssrcuminflow", TDim :: NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", & ssrcuminflow);
    declvar ("ssroutflow", TDim :: NHRU, "HRU outflow", "(mm*km^2/int)", & ssroutflow);
    declstatdiag ("ssrcumoutflow", TDim :: NHRU, "cumulative HRU outflow", "(mm*km^2)", & ssrcumoutflow);
    declstatdiag ("HRU_cumbasinflow", TDim :: NHRU, "cumulative HRU to basinflow", "(mm*km^2)", & HRU_cumbasinflow);
    declstatdiag ("cum_preferential_flow_to_gw", TDim :: NHRU, "cumulative other HRU's runoff to this HRU's gw via preferential flow path", "(mm)", & cum_preferential_flow_to_gw);
    declparam ("preferential_flow", TDim :: NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", & preferential_flow);
    declvar ("runinflow", TDim :: NHRU, "inflow from other HRUs", "(mm*km^2/int)", & runinflow);
    declstatdiag ("runcuminflow", TDim :: NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", & runcuminflow);
    declvar ("runoutflow", TDim :: NHRU, "HRU outflow", "(mm*km^2/int)", & runoutflow);
    declstatdiag ("runcumoutflow", TDim :: NHRU, "cumulative HRU outflow", "(mm*km^2)", & runcumoutflow);
    declstatdiag ("cumscaling_boost", TDim :: NHRU, "cumulative amout inflow boosted", "(mm*km^2)", & cumscaling_boost);
    declvar ("basinflow", TDim :: BASIN, "basin surface and sub-surface outflow", "(m^3/int)", & basinflow);
    decldiag ("basinflow_s", TDim :: BASIN, "basin surface and sub-surface outflow", "(m^3/s)", & basinflow_s);
    declstatdiag ("cumbasinflow", TDim :: BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", & cumbasinflow);
    declvar ("basingw", TDim :: BASIN, "cumulative basin groundwater outflow", "(m^3/int)", & basingw);
    decldiag ("basingw_s", TDim :: BASIN, "cumulative basin groundwater outflow", "(m^3/s)", & basingw_s);
    declstatdiag ("cumbasingw", TDim :: BASIN, "cumulative basin groundwater outflow", "(m^3)", & cumbasingw);
    decllocal ("soil_ssr_Buf", TDim :: NHRU, "buffer subsurface runoff", "(mm/d)", & soil_ssr_Buf);
    decllocal ("soil_runoff_Buf", TDim :: NHRU, "buffer rain runoff", "(mm/d)", & soil_runoff_Buf);
    decllocal ("soil_gw_Buf", TDim :: NHRU, "buffer rain runoff", "(mm/d)", & soil_gw_Buf);
    decllocal ("distrib_sum", TDim :: NHRU, "HRU distribution sum", "()", & distrib_sum);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", & hru_area);
    declparam ("Kstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", & Kstorage);
    declparam ("Lag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", & Lag);
    declparam ("ssrKstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", & ssrKstorage);
    declparam ("ssrLag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", & ssrLag);
    declparam ("runKstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", & runKstorage);
    declparam ("runLag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", & runLag);
    declparam ("gwKstorage", TDim :: NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", & gwKstorage);
    declparam ("gwLag", TDim :: NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", & gwLag);
    declparam ("distrib_Route", TDim :: NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", & distrib, & distrib_hru, nhru);
    declparam ("distrib_Basin", TDim :: NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", & distrib_Basin);
    declparam ("gwwhereto", TDim :: NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", & gwwhereto);
    declparam ("Sdmax", TDim :: NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", & Sdmax);
    declparam ("soil_rechr_max", TDim :: NHRU, "[60.0]", "0.0", "350.0", "Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "
        "and transpiration). Must be less than or equal to soil_moist.", "(mm)", & soil_rechr_max);
    decldiagparam ("Sd_ByPass", TDim :: NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", & Sd_ByPass);
    decldiagparam ("soil_rechr_ByPass", TDim :: NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", & soil_rechr_ByPass);
    decldiagparam ("scaling_factor", TDim :: NHRU, "[1.0]", "0.0", "1.0E6", "multiplies the input to Muskingum by this scaling factor.", "()", & scaling_factor);
    declparam ("order", TDim :: NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", & order);
    soil_gwDiv = declgetvar ("*", "gw_flow", "(mm/int)", & soil_gw);
    soil_ssrDiv = declgetvar ("*", "soil_ssr", "(mm/int)", & soil_ssr);
    soil_runoffDiv = declgetvar ("*", "soil_runoff", "(mm/int)", & soil_runoff);
    declputvar ("*", "Sd", "(mm)", & Sd);
    declputvar ("*", "soil_moist", "(mm)", & soil_moist);
    declputvar ("*", "soil_rechr", "(mm)", & soil_rechr);
    declputvar ("*", "redirected_residual", "(mm*km^2/int)", & redirected_residual);
    declputvar ("*", "gw", "(mm)", & gw);
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::decl(void)@@@ClassNetroute_D.cpp>");
}
void ClassNetroute_D :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::init(void)@@@ClassNetroute_D.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (soil_ssrDiv > 1)
    {
        string S = "Netroute_D:  \"soil_ssr\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (soil_runoffDiv > 1)
    {
        string S = "Netroute_D:  \"soil_runoff\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    if (soil_gwDiv > 1)
    {
        string S = "Netroute:  \"gw_flow\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    hruDelay = new ClassClark (inflow, outflow, Kstorage, Lag, nhru);
    ssrDelay = new ClassClark (ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
    runDelay = new ClassClark (runinflow, runoutflow, runKstorage, runLag, nhru);
    gwDelay = new ClassClark (gwinflow, gwoutflow, gwKstorage, gwLag, nhru);
    basinflow [0] = 0.0;
    basinflow_s [0] = 0.0;
    cumbasinflow [0] = 0.0;
    basingw [0] = 0.0;
    basingw_s [0] = 0.0;
    cumbasingw [0] = 0.0;
    for (hh = 0; hh < nhru; ++ hh) {
        inflow [hh] = 0.0;
        cuminflow [hh] = 0.0;
        outflow [hh] = 0.0;
        outflow_diverted [hh] = 0.0;
        cumoutflow_diverted [hh] = 0.0;
        cumoutflow [hh] = 0.0;
        cumscaling_boost [hh] = 0.0;
        cum_to_Sd [hh] = 0.0;
        cum_to_soil_rechr [hh] = 0.0;
        cum_preferential_flow_to_gw [hh] = 0.0;
        gwinflow [hh] = 0.0;
        gwcuminflow [hh] = 0.0;
        gwcumoutflow [hh] = 0.0;
        gwcumoutflow_diverted [hh] = 0.0;
        HRU_cumbasinflow [hh] = 0.0;
        ssrinflow [hh] = 0.0;
        ssrcuminflow [hh] = 0.0;
        ssroutflow [hh] = 0.0;
        ssrcumoutflow [hh] = 0.0;
        runinflow [hh] = 0.0;
        runcuminflow [hh] = 0.0;
        runoutflow [hh] = 0.0;
        runcumoutflow [hh] = 0.0;
        soil_ssr_Buf [hh] = 0.0;
        soil_runoff_Buf [hh] = 0.0;
        soil_gw_Buf [hh] = 0.0;
        bool OK = false;
        for (long jj = 0; chkStruct (jj); ++ jj)
            if (order [jj] - 1 == hh)
            {
                OK = true;
                break;
            }

        if (! OK)
        {
            string SS = string ("'" + Name + " (Netroute_D)' the 'order' parameter does not have a unique value for each HRU");
            CRHMException Except (SS.c_str (), TExcept :: ERR);
            LogError (Except);
            throw Except;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::init(void)@@@ClassNetroute_D.cpp>");
}
void ClassNetroute_D :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::run(void)@@@ClassNetroute_D.cpp>");
    long nstep = getstep () % Global :: Freq;
    basinflow [0] = 0.0;
    basingw [0] = 0.0;
    if (getstep () == 1)
    {
        for (hh = 0; chkStruct (hh); ++ hh) {
            distrib_sum [hh] = 0.0;
            for (long hhh = 0; chkStruct (hhh); ++ hhh) {
                if (distrib_hru [hh] [hhh] < 0.0)
                {
                    const_cast < double ** > (distrib_hru) [hh] [hhh] = - distrib_hru [hh] [hhh] * hru_area [hh];
                }

                distrib_sum [hh] += distrib_hru [hh] [hhh];
            }
            if (distrib_sum [hh] <= 0 && distrib_Basin [hh] <= 0.0)
            {
                const_cast < double * > (distrib_Basin) [hh] = 1;
            }

            distrib_sum [hh] += distrib_Basin [hh];
        }
    }

    double gw_amount;
    for (long jj = 0; chkStruct (jj); ++ jj) {
        for (hh = 0; chkStruct (hh); ++ hh) {
            if (order [hh] - 1 == jj)
            {
                break;
            }

        }
        if (soil_gwDiv == 1)
        {
            soil_gw_Buf [hh] = soil_gw [hh];
        }

        gwinflow [hh] = soil_gw_Buf [hh] * hru_area [hh];
        gwoutflow_diverted [hh] = 0.0;
        gw_amount = 0.0;
        for (long hhh = 0; chkStruct (hhh); ++ hhh) {
            if (gwoutflow [hhh] > 0.0 && gwwhereto [hhh] && (abs (gwwhereto [hhh]) - 1 == hh || abs (gwwhereto [hhh]) > nhru))
            {
                gwoutflow_diverted [hhh] = gwoutflow [hhh];
                gw_amount = gwoutflow_diverted [hhh];
                gwoutflow [hhh] = 0.0;
                gwcumoutflow_diverted [hhh] += gwoutflow_diverted [hhh];
                if (abs (gwwhereto [hhh]) <= nhru)
                {
                    if (gwwhereto [hhh] > 0)
                    {
                        double free = soil_rechr_max [hh] - soil_rechr [hh];
                        if (free > 0.0 && ! soil_rechr_ByPass [hh])
                        {
                            if (free > gw_amount / hru_area [hh])
                            {
                                soil_rechr [hh] += gw_amount / hru_area [hh];
                                soil_moist [hh] += gw_amount / hru_area [hh];
                                cum_to_soil_rechr [hh] += gw_amount / hru_area [hh];
                                gw_amount = 0.0;
                            }

                            else
                            {
                                gw_amount = (gw_amount / hru_area [hh] - free) * hru_area [hh];
                                cum_to_soil_rechr [hh] += free;
                                soil_moist [hh] += free;
                                soil_rechr [hh] = soil_rechr_max [hh];
                            }

                        }

                        free = Sdmax [hh] - Sd [hh];
                        if (free > 0.0 && gw_amount > 0.0 && ! Sd_ByPass [hh])
                        {
                            if (free > gw_amount / hru_area [hh])
                            {
                                Sd [hh] += gw_amount / hru_area [hh];
                                cum_to_Sd [hh] += gw_amount / hru_area [hh];
                                gw_amount = 0.0;
                            }

                            else
                            {
                                gw_amount = (gw_amount / hru_area [hh] - free) * hru_area [hh];
                                cum_to_Sd [hh] += free;
                                Sd [hh] = Sdmax [hh];
                            }

                        }

                    }

                    else
                    {
                        gw [hh] += gw_amount / hru_area [hh];
                        gw_amount = 0.0;
                    }

                }

                else
                {
                    basinflow [0] += gw_amount * 1000;
                    HRU_cumbasinflow [hh] = gw_amount;
                    cumoutflow [hh] += gw_amount;
                    gw_amount = 0.0;
                }

            }

        }
        gwcuminflow [hh] += gwinflow [hh];
        inflow [hh] = gw_amount;
        outflow_diverted [hh] = 0.0;
    }
    for (hh = 0; chkStruct (hh); ++ hh) {
        if (soil_ssrDiv == 1)
        {
            soil_ssr_Buf [hh] = soil_ssr [hh];
        }

        if (soil_runoffDiv == 1)
        {
            soil_runoff_Buf [hh] = soil_runoff [hh];
        }

        runinflow [hh] = soil_runoff_Buf [hh] * hru_area [hh];
        runcuminflow [hh] += runinflow [hh];
        ssrinflow [hh] = soil_ssr_Buf [hh] * hru_area [hh];
        ssrcuminflow [hh] += ssrinflow [hh];
        ssrcumoutflow [hh] += ssroutflow [hh];
        runcumoutflow [hh] += runoutflow [hh];
        inflow [hh] += scaling_factor [hh] * (runoutflow [hh] + ssroutflow [hh]);
        if (outflow [hh] > 0.0)
        {
            double Used = outflow [hh] * distrib_Basin [hh] / distrib_sum [hh];
            if (distrib_Basin [hh] > 0.0)
            {
                basinflow [0] += Used * 1000;
                HRU_cumbasinflow [hh] += Used;
                cumoutflow [hh] += Used;
            }

            for (long To = 0; chkStruct (To); ++ To) {
                if (hh != To && distrib_hru [hh] [To] > 0.0)
                {
                    double Amount = (outflow [hh] - Used) / hru_area [To] * distrib_hru [hh] [To] / (distrib_sum [hh] - distrib_Basin [hh]);
                    if (preferential_flow [hh])
                    {
                        gw [To] += Amount;
                        cum_preferential_flow_to_gw [To] += Amount;
                        Amount = 0.0;
                    }

                    else
                    {
                        double free = soil_rechr_max [To] - soil_rechr [To];
                        if (free > 0.0 && ! soil_rechr_ByPass [To])
                        {
                            if (free > Amount)
                            {
                                soil_rechr [To] += Amount;
                                soil_moist [To] += Amount;
                                cum_to_soil_rechr [To] += Amount;
                                Amount = 0.0;
                            }

                            else
                            {
                                Amount -= free;
                                cum_to_soil_rechr [To] += free;
                                soil_moist [To] += free;
                                soil_rechr [To] = soil_rechr_max [To];
                            }

                        }

                        free = Sdmax [To] - Sd [To];
                        if (free > 0.0 && ! Sd_ByPass [To] && Amount > 0.0)
                        {
                            if (free > Amount)
                            {
                                Sd [To] += Amount;
                                cum_to_Sd [To] += Amount;
                                Amount = 0.0;
                            }

                            else
                            {
                                Amount -= free;
                                cum_to_Sd [To] += free;
                                Sd [To] = Sdmax [To];
                            }

                        }

                    }

                    if (Amount > 0.0)
                    {
                        redirected_residual [To] += Amount * hru_area [To];
                    }

                }

            }
        }

        if (gwwhereto [hh] == 0)
        {
            basingw [0] += gwoutflow [hh] * 1000;
            gwcumoutflow [hh] += gwoutflow [hh];
        }

        if (nstep == 0)
        {
            if (soil_ssrDiv > 1)
            {
                soil_ssr_Buf [hh] = soil_ssr [hh] / soil_ssrDiv;
            }

            if (soil_runoffDiv > 1)
            {
                soil_runoff_Buf [hh] = soil_runoff [hh] / soil_runoffDiv;
            }

            if (soil_gwDiv > 1)
            {
                soil_gw_Buf [hh] = soil_gw [hh] / soil_gwDiv;
            }

        }

    }
    for (hh = 0; chkStruct (hh); ++ hh) {
        cuminflow [hh] += inflow [hh];
        cumscaling_boost [hh] += inflow [hh] * (scaling_factor [hh] - 1.0);
        outflow_diverted [hh] = 0.0;
        if (distrib_sum [hh] > 0.0)
        {
            for (long hhh = 0; chkStruct (hhh); ++ hhh) {
                outflow_diverted [hh] += outflow [hh] * distrib_hru [hh] [hhh] / distrib_sum [hh];
            }
        }

        cumoutflow_diverted [hh] += outflow_diverted [hh];
    }
    hruDelay -> DoClark ();
    runDelay -> DoClark ();
    ssrDelay -> DoClark ();
    gwDelay -> DoClark ();
    basinflow_s [0] = basinflow [0] * Global :: Freq / 86400.0;
    basingw_s [0] = basingw [0] * Global :: Freq / 86400.0;
    cumbasinflow [0] += basinflow [0];
    cumbasingw [0] += basingw [0];
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::run(void)@@@ClassNetroute_D.cpp>");
}
void ClassNetroute_D :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNetroute_D::finish(bool good)@@@ClassNetroute_D.cpp>");
    double Allcuminflow = 0.0;
    double Allcumoutflow = 0.0;
    double Allcumoutflowdiverted = 0.0;
    double Allgwcuminflow = 0.0;
    double Allgwcumoutflow = 0.0;
    double Allgwcumoutflowdiverted = 0.0;
    double Allssrcuminflow = 0.0;
    double Allssrcumoutflow = 0.0;
    double Allruncuminflow = 0.0;
    double Allruncumoutflow = 0.0;
    double AllSdcuminflow = 0.0;
    double Allrechrcuminflow = 0.0;
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str (), cuminflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str (), cumoutflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str (), cumoutflow_diverted [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str (), hruDelay -> Left (hh) / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' scaling_boost          (mm) (mm*km^2) (mm*basin): ").c_str (), cumscaling_boost [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str (), ssrcuminflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str (), ssrcumoutflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str (), ssrDelay -> Left (hh) / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str (), runcuminflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str (), runcumoutflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str (), runDelay -> Left (hh) / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str (), gwcuminflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str (), gwcumoutflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str (), gwcumoutflow_diverted [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' gwDelay_in_storage           (mm) (mm*km^2) (mm*basin): ").c_str (), gwDelay -> Left (hh) / hru_area [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str (), cum_to_Sd [hh], hru_area [hh], basin_area [0], " *** Added to this HRU Sd");
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str (), cum_to_soil_rechr [hh], hru_area [hh], basin_area [0], " *** Added to this HRU recharge");
        LogMessageA (hh, string ("'" + Name + " (Netroute_D)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str (), HRU_cumbasinflow [hh] / hru_area [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
        Allcuminflow += cuminflow [hh];
        Allcumoutflow += cumoutflow [hh];
        Allcumoutflowdiverted += cumoutflow_diverted [hh];
        Allgwcuminflow += gwcuminflow [hh];
        Allgwcumoutflow += gwcumoutflow [hh];
        Allgwcumoutflowdiverted += gwcumoutflow_diverted [hh];
        Allssrcumoutflow += ssrcumoutflow [hh];
        Allssrcuminflow += ssrcuminflow [hh];
        Allruncuminflow += runcuminflow [hh];
        Allruncumoutflow += runcumoutflow [hh];
        AllSdcuminflow += cum_to_Sd [hh] * hru_area [hh];
        Allrechrcuminflow += cum_to_soil_rechr [hh] * hru_area [hh];
    }
    LogMessage (string ("'" + Name + " (Netroute_D)' cumbasinflow (m^3): ").c_str (), cumbasinflow [0]);
    LogMessage (string ("'" + Name + " (Netroute_D)' cumbasingw  (m^3): ").c_str (), cumbasingw [0]);
    LogDebug (" ");
    LogMessage (string ("'" + Name + " (Netroute_D)' Allgwcuminflow (mm*basin): ").c_str (), Allgwcuminflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allgwcumoutflow (mm*basin): ").c_str (), Allgwcumoutflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allgwcumoutflowdiverted (mm*basin): ").c_str (), Allgwcumoutflowdiverted);
    LogDebug (" ");
    LogMessage (string ("'" + Name + " (Netroute_D)' Allcuminflow (mm*basin): ").c_str (), Allcuminflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allcumoutflow (mm*basin): ").c_str (), Allcumoutflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allcumoutflowdiverted (mm*basin): ").c_str (), Allcumoutflowdiverted);
    LogDebug (" ");
    LogMessage (string ("'" + Name + " (Netroute_D)' Allssrcuminflow (mm*basin): ").c_str (), Allssrcuminflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allssrcumoutflow (mm*basin): ").c_str (), Allssrcumoutflow);
    LogDebug (" ");
    LogMessage (string ("'" + Name + " (Netroute_D)' Allruncuminflow (mm*basin): ").c_str (), Allruncuminflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allruncumoutflow (mm*basin): ").c_str (), Allruncumoutflow);
    LogDebug (" ");
    LogMessage (string ("'" + Name + " (Netroute_D)' AllSdcuminflow (mm*basin): ").c_str (), AllSdcuminflow);
    LogMessage (string ("'" + Name + " (Netroute_D)' Allrechrcuminflow (mm*basin): ").c_str (), Allrechrcuminflow);
    LogDebug (" ");
    delete hruDelay;
    delete ssrDelay;
    delete runDelay;
    delete gwDelay;
InstrumentLogger::instance()->log_instrument_log("</ClassNetroute_D::finish(bool good)@@@ClassNetroute_D.cpp>");
}