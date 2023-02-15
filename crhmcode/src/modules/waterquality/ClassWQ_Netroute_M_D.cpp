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
#include "ClassWQ_Netroute_M_D.h"


void ClassWQ_Netroute_M_D::decl(void) {

    // kg/km2 = (mg/l)*mm = mg/m2

    Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'\
                    'uses Muskingum,' \
                    'uses Clark.'";

    declvar("inflow", TDim::NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

    declvar("inflow_mWQ", TDim::NDEFN, "Concentration: inflow from other HRUs", "(mg/l * mm*km^2/int)", &inflow_mWQ, &inflow_mWQ_lay, numsubstances);

    declstatvar("cuminflow", TDim::NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

    declstatvar("cuminflow_mWQ", TDim::NDEFN, "cumulative mass of solute inflow from other HRUs", "(g*km^2)", &cuminflow_mWQ, &cuminflow_mWQ_lay, numsubstances);

    declvar("outflow", TDim::NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

    declvar("outflow_mWQ", TDim::NDEFN, "Substance mass: HRU outflow", "(mg/l * mm*km^2/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);

    declvar("outflow_cWQ", TDim::NDEFN, "Substance concentration: HRU outflow", "(mg/l * mm*km^2/int)", &outflow_cWQ, &outflow_cWQ_lay, numsubstances);

    declstatvar("cumoutflow", TDim::NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

    declstatvar("cumoutflow_mWQ", TDim::NDEFN, "cumulative mass of solute HRU outflow", "(mg/l * mm*km^2/int)", &cumoutflow_mWQ, &cumoutflow_mWQ_lay, numsubstances);

    declvar("outflow_diverted", TDim::NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

    declvar("outflow_diverted_conc", TDim::NDEFN, "Concentration: HRU outflow diverted to another HRU", "(g/l)", &outflow_diverted_conc, &outflow_diverted_conc_lay, numsubstances);

    declstatvar("cumoutflow_diverted", TDim::NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

    declstatvar("cumoutflow_diverted_mWQ", TDim::NDEFN, "cumulative mass of solute HRU outflow diverted to another HRU", "(mg/l * mm*km^2/int)", &cumoutflow_diverted_mWQ, &cumoutflow_diverted_mWQ_lay, numsubstances);

    declstatvar("cum_to_Sd", TDim::NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

    declstatvar("cum_to_Sd_mWQ", TDim::NDEFN, "cumulative mass of solute from other HRU to depressional storage (Sd) of this HRU", "(mg/l * mm*km^2/int)", &cum_to_Sd_mWQ, &cum_to_Sd_mWQ_lay, numsubstances);

    declstatvar("cum_to_soil_rechr", TDim::NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

    declstatvar("cum_to_soil_rechr_mWQ", TDim::NDEFN, "cumulative mass of solute from other HRU to soil_rechr of this HRU", "(mg/l * mm*km^2/int)", &cum_to_soil_rechr_mWQ, &cum_to_soil_rechr_mWQ_lay, numsubstances);

    declvar("gwinflow", TDim::NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

    declvar("gwinflow_mWQ", TDim::NDEFN, "Concentration: ground water inflow", "(mg/l * mm*km^2/int)", &gwinflow_mWQ, &gwinflow_mWQ_lay, numsubstances);

    declstatvar("gwcuminflow", TDim::NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

    declstatvar("gwcuminflow_mWQ", TDim::NDEFN, "cumulative mass of solute gw inflow", "(mg/l * mm*km^2/int)", &gwcuminflow_mWQ, &gwcuminflow_mWQ_lay, numsubstances);

    declvar("gwoutflow", TDim::NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

    declvar("gwoutflow_mWQ", TDim::NDEFN, "Concentration: HRU gw outflow", "(mg/l * mm*km^2/int)", &gwoutflow_mWQ, &gwoutflow_mWQ_lay, numsubstances);

    declstatvar("gwcumoutflow", TDim::NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

    declstatvar("gwcumoutflow_mWQ", TDim::NDEFN, "cumulative mass of solute HRU gw outflow", "(mg/l * mm*km^2/int)", &gwcumoutflow_mWQ, &gwcumoutflow_mWQ_lay, numsubstances);

    decldiag("gwoutflow_diverted", TDim::NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

    decldiag("gwoutflow_diverted_conc", TDim::NDEFN, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted_conc, &gwoutflow_diverted_conc_lay, numsubstances);

    declstatvar("gwcumoutflow_diverted", TDim::NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

    declstatvar("gwcumoutflow_diverted_mWQ", TDim::NDEFN, "cumulative mass of solute HRU gw outflow diverted to another HRU", "(mg/l * mm*km^2/int)", &gwcumoutflow_diverted_mWQ, &gwcumoutflow_diverted_mWQ_lay, numsubstances);

    declvar("ssrinflow", TDim::NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

    declvar("ssrinflow_mWQ", TDim::NDEFN, "Concentration: inflow from other HRUs", "(mg/l * mm*km^2/int)", &ssrinflow_mWQ, &ssrinflow_mWQ_lay, numsubstances);

    declstatvar("ssrcuminflow", TDim::NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

    declstatvar("ssrcuminflow_mWQ", TDim::NDEFN, "cumulative mass of solute of inflow from other HRUs", "(mg/l * mm*km^2/int)", &ssrcuminflow_mWQ, &ssrcuminflow_mWQ_lay, numsubstances);

    declvar("ssroutflow", TDim::NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

    declvar("ssroutflow_mWQ", TDim::NDEFN, "Concentration: HRU outflow", "(mg/l * mm*km^2/int)", &ssroutflow_mWQ, &ssroutflow_mWQ_lay, numsubstances);

    declstatvar("ssrcumoutflow", TDim::NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

    declstatvar("ssrcumoutflow_mWQ", TDim::NDEFN, "cumulative mass of solute HRU outflow", "(mg/l * mm*km^2/int)", &ssrcumoutflow_mWQ, &ssrcumoutflow_mWQ_lay, numsubstances);

    declstatvar("HRU_cumbasinflow", TDim::NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

    declstatvar("HRU_cumbasinflow_mWQ", TDim::NDEFN, "cumulative HRU to basinflow", "(mg/l * mm*km^2/int)", &HRU_cumbasinflow_mWQ, &HRU_cumbasinflow_mWQ_lay, numsubstances);

    declvar("runinflow", TDim::NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

    declvar("runinflow_mWQ", TDim::NDEFN, "Concentration: inflow from other HRUs", "(mg/l * mm*km^2/int)", &runinflow_mWQ, &runinflow_mWQ_lay, numsubstances);

    declstatvar("runcuminflow", TDim::NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

    declstatvar("runcuminflow_mWQ", TDim::NDEFN, "cumulative mass of solute inflow from other HRUs", "(mg/l * mm*km^2/int)", &runcuminflow_mWQ, &runcuminflow_mWQ_lay, numsubstances);

    declvar("runoutflow", TDim::NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

    declvar("runoutflow_mWQ", TDim::NDEFN, "Concentration: HRU outflow", "(mg/l * mm*km^2/int)", &runoutflow_mWQ, &runoutflow_mWQ_lay, numsubstances);

    declstatvar("runcumoutflow", TDim::NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

    declstatvar("runcumoutflow_mWQ", TDim::NDEFN, "cumulative mass of solute HRU outflow", "(mg/l * mm*km^2/int)", &runcumoutflow_mWQ, &runcumoutflow_mWQ_lay, numsubstances);

    declstatvar("cum_preferential_flow_to_gw", TDim::NHRU, "cumulative other HRU's runoff to gw of this HRU via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);


    declvar("basinflow", TDim::BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

    declvar("basinflow_mWQ", TDim::NDEF2, "basin surface and sub-surface outflow", "(g/int)", &basinflow_mWQ, NULL, numsubstances);
    declvar("basinflow_conc", TDim::NDEF, "basin surface and sub-surface outflow", "(g/l)", &basinflow_conc, &basinflow_conc_lay, numsubstances);

    declvar("Used", TDim::NHRU, "directed to basinbasin surface and sub-surface outflow", "()", &Used);

    declvar("Used_mWQ", TDim::NDEFN, "directed to basinbasin surface and sub-surface outflow", "(mg/l * mm*km^2/int)", &Used_mWQ, &Used_mWQ_lay, numsubstances);

    decldiag("basinflow_s", TDim::BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

    declstatvar("cumbasinflow", TDim::BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

    declvar("cumbasinflow_mWQ", TDim::NDEF, "cumulative mass of solute basin surface and sub-surface outflow", "(mg/l * mm*km^2/int)", &cumbasinflow_mWQ, &cumbasinflow_mWQ_lay, numsubstances);

    declvar("basingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

    declvar("basingw_conc", TDim::NDEF, "cumulative basin groundwater outflow", "(m^3/int)", &basingw_conc, &basingw_conc_lay, numsubstances);

    decldiag("basingw_s", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

    declstatvar("cumbasingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

    declstatvar("cumbasingw_mWQ", TDim::NDEF, "cumulative mass of solute basin groundwater outflow", "(mg/l * mm*km^2/int)", &cumbasingw_mWQ, &cumbasingw_mWQ_lay, numsubstances);


    decllocal("soil_ssr_Buf", TDim::NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

    declvar("soil_ssr_Buf_conc", TDim::NDEFN, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf_conc, &soil_ssr_Buf_conc_lay, numsubstances);

    decllocal("soil_runoff_Buf", TDim::NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

    declvar("soil_runoff_Buf_conc", TDim::NDEFN, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf_conc, &soil_runoff_Buf_conc_lay, numsubstances);

    decllocal("soil_gw_Buf", TDim::NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

    declvar("soil_gw_Buf_conc", TDim::NDEFN, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf_conc, &soil_gw_Buf_conc_lay, numsubstances);

    decllocal("distrib_sum", TDim::NHRU, "HRU distribution sum", "()", &distrib_sum);


    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

    declparam("Kstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "HRU storage constant", "(d)", &Kstorage);

    declparam("Lag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "HRU lag delay", "(h)", &Lag);

    declparam("ssrKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

    declparam("ssrLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

    declparam("runKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

    declparam("runLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

    declparam("gwKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

    declparam("gwLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

    declparam("gwwhereto", TDim::NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

    declparam("order", TDim::NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

    declparam("distrib_Route", TDim::NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs (distribute by area otherwise by fraction)", "()", &distrib, &distrib_hru, nhru);

    declparam("distrib_Basin", TDim::NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_hru')", "()", &distrib_Basin);

    declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

    declparam("Sd_ByPass", TDim::NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

    declparam("soil_rechr_ByPass", TDim::NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);


    declparam("order", TDim::NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

    declparam("preferential_flow", TDim::NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


    soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

    soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

    soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

    declgetvar("*", "soil_ssr_conc", "(g)", &soil_ssr_conc, &soil_ssr_conc_lay);

    declgetvar("*", "soil_gw_conc", "(mg)", &soil_gw_conc, &soil_gw_conc_lay);

    declgetvar("*", "soil_runoff_cWQ", "(mg)", &soil_runoff_cWQ, &soil_runoff_cWQ_lay);


    declputvar("*", "Sd", "(mm)", &Sd);

    declputvar("*", "Sd_conc", "(g)", &Sd_conc, &Sd_conc_lay);

    declputvar("*", "soil_moist", "(mm)", &soil_moist);

    declputvar("*", "soil_moist_conc", "(g)", &soil_moist_conc, &soil_moist_conc_lay);

    declputvar("*", "soil_lower", "(mm)", &soil_lower);

    declputvar("*", "conc_soil_lower", "(g)", &conc_soil_lower, &conc_soil_lower_lay);

    declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

    declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

    declputvar("*", "redirected_residual_conc", "(g)", &redirected_residual_conc, &redirected_residual_conc_lay);

    declputvar("*", "cum_redirected_residual", "(mm*km^2/int)", &cum_redirected_residual);

    declputvar("*", "cum_redirected_residual_mWQ", "(mg/l * mm*km^2/int)", &cum_redirected_residual_mWQ, &cum_redirected_residual_mWQ_lay);

    declputvar("*", "gw", "(mm)", &gw);

    declputvar("*", "gw_conc", "(mg/l)", &gw_conc, &gw_conc_lay);

    declputvar("*", "conc_soil_rechr", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay);

    declputvar("*", "conc_soil_lower", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay);


    decllocal("gwoutflow_0", TDim::NHRU, "", "", &gwoutflow_0);

    decllocal("outflow_0", TDim::NHRU, "", "", &outflow_0);


    variation_set = VARIATION_0;

    decllocal("Ktravel", TDim::NHRU, "travel time", "(d)", &Ktravel);

    declparam("route_n", TDim::NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &route_n);

    declparam("route_R", TDim::NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "(m)", &route_R);

    declparam("route_S0", TDim::NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &route_S0);

    declparam("route_L", TDim::NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

    declparam("route_X_M", TDim::NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &route_X_M);

    declparam("Channel_shp", TDim::NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);


    variation_set = VARIATION_1;

    declparam("Kstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", &Kstorage);


    variation_set = VARIATION_ORG;

}

void ClassWQ_Netroute_M_D::init(void) {

    nhru = getdim(TDim::NHRU);

    try {
        ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
        runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
        gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

        ssrDelay_mWQ = new ClassClark * [numsubstances];
        runDelay_mWQ = new ClassClark * [numsubstances];
        gwDelay_mWQ = new ClassClark * [numsubstances];

        for (long Sub = 0; Sub < numsubstances; ++Sub) {
            ssrDelay_mWQ[Sub] = new ClassClark(ssrinflow_mWQ_lay[Sub], ssroutflow_mWQ_lay[Sub], ssrKstorage, ssrLag, nhru);
            runDelay_mWQ[Sub] = new ClassClark(runinflow_mWQ_lay[Sub], runoutflow_mWQ_lay[Sub], runKstorage, runLag, nhru);
            gwDelay_mWQ[Sub] = new ClassClark(gwinflow_mWQ_lay[Sub], gwoutflow_mWQ_lay[Sub], gwKstorage, gwLag, nhru);
        }

        if (variation == VARIATION_1) {
            Clark_hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);

            Clark_hruDelay_mWQ = new ClassClark * [numsubstances];

            for (long Sub = 0; Sub < numsubstances; ++Sub)
                Clark_hruDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Kstorage, Lag, nhru);
        }
        else if (variation == VARIATION_ORG) {
            const double Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

            for (hh = 0; hh < nhru; ++hh) {
                double Vavg = (1.0 / route_n[hh]) * pow(route_R[hh], 2.0 / 3.0) * pow(route_S0[hh], 0.5f); // (m/s)
                Ktravel[hh] = route_L[hh] / (Vw[route_Cshp[hh]] * Vavg) / 86400.0; // (d)
            }

            hruDelay = new ClassMuskingum(inflow, outflow, Ktravel, route_X_M, Lag, nhru);

            for (hh = 0; hh < nhru; ++hh) {
                if (Ktravel[hh] >= (Global::Interval / (2.0 * route_X_M[hh]))) {
                    string S = string("'" + Name + " (Netroute_M_D) Muskingum coefficient negative in HRU ").c_str() + to_string(hh + 1);
                    CRHMException TExcept(S.c_str(), TExcept::WARNING);
                    LogError(TExcept);
                }
            } // for


            hruDelay_mWQ = new ClassMuskingum * [numsubstances];

            for (long Sub = 0; Sub < numsubstances; ++Sub)
                hruDelay_mWQ[Sub] = new ClassMuskingum(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Ktravel, route_X_M, Lag, nhru);

            for (hh = 0; hh < nhru; ++hh) {
                if (Ktravel[hh] < (Global::Interval / (2.0 * (1.0 - route_X_M[hh])))) { //    if(hruDelay->c0[hh] < 0.0)
                    hruDelay->c0[hh] = 0.0;
                    hruDelay->c1[hh] = 1.0;
                    hruDelay->c2[hh] = 0.0;

                    for (long Sub = 0; Sub < numsubstances; ++Sub) {
                        hruDelay_mWQ[Sub]->c0[hh] = 0.0;
                        hruDelay_mWQ[Sub]->c1[hh] = 1.0;
                        hruDelay_mWQ[Sub]->c2[hh] = 0.0;
                    }
                }
            } // for
        } // VARIATION_ORG
    } // try
    catch (std::bad_alloc) {
        CRHMException Except("Could not allocate in module Netroute_M_D.", TExcept::TERMINATE);
        LogError(Except);
        throw Except;
    }

    if (soil_ssrDiv > 1) {
        string S = "WQ_Netroute_M_D:  \"soil_ssr\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (soil_runoffDiv > 1) {
        string S = "WQ_Netroute_M_D:  \"soil_runoff\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (soil_gwDiv > 1) {
        string S = "WQ_Netroute_M_D:  \"gw_flow\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    Reset_WQ(0, basinflow, basinflow_conc_lay);
    Reset_WQ(0, cumbasinflow, cumbasinflow_mWQ_lay);
    Reset_WQ(0, basingw, basingw_conc_lay);
    Reset_WQ(0, cumbasingw, cumbasingw_mWQ_lay);

    basinflow_s[0] = 0.0;
    basingw_s[0] = 0.0;

// It seems that we already did this (PRL)
    // for (long Sub = 0; Sub < numsubstances; ++Sub) {

    //     if (variation == VARIATION_0)
    //         Clark_hruDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Kstorage, Lag, nhru);
    //     else // ClassMuskingum
    //         hruDelay_mWQ[Sub] = new ClassMuskingum(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Ktravel, route_X_M, Lag, nhru);

    //     ssrDelay_mWQ[Sub] = new ClassClark(ssrinflow_mWQ_lay[Sub], ssroutflow_mWQ_lay[Sub], ssrKstorage, ssrLag, nhru, -1);
    //     runDelay_mWQ[Sub] = new ClassClark(runinflow_mWQ_lay[Sub], runoutflow_mWQ_lay[Sub], runKstorage, runLag, nhru, -1);
    //     gwDelay_mWQ[Sub] = new ClassClark(gwinflow_mWQ_lay[Sub], gwoutflow_mWQ_lay[Sub], gwKstorage, gwLag, nhru, -1);
    // } // for Sub

    for (hh = 0; hh < nhru; ++hh) {
        Reset_WQ(hh, inflow, inflow_mWQ_lay);
        Reset_WQ(hh, cuminflow, cuminflow_mWQ_lay);

        Reset_WQ(hh, outflow, outflow_mWQ_lay);
        Reset_WQ(hh, cumoutflow, cumoutflow_mWQ_lay);

        Reset_WQ(hh, gwinflow, gwinflow_mWQ_lay);
        Reset_WQ(hh, gwcuminflow, gwcuminflow_mWQ_lay);

        Reset_WQ(hh, gwoutflow, gwoutflow_mWQ_lay);
        Reset_WQ(hh, gwcumoutflow, gwcumoutflow_mWQ_lay);

        Reset_WQ(hh, ssrinflow, ssrinflow_mWQ_lay);
        Reset_WQ(hh, ssrcuminflow, ssrcuminflow_mWQ_lay);

        Reset_WQ(hh, ssroutflow, ssroutflow_mWQ_lay);
        Reset_WQ(hh, ssrcumoutflow, ssrcumoutflow_mWQ_lay);

        Reset_WQ(hh, runinflow, runinflow_mWQ_lay);
        Reset_WQ(hh, runcuminflow, runcuminflow_mWQ_lay);

        Reset_WQ(hh, runoutflow, runoutflow_mWQ_lay);
        Reset_WQ(hh, runcumoutflow, runcumoutflow_mWQ_lay);

        Reset_WQ(hh, outflow_diverted, outflow_diverted_conc_lay);
        Reset_WQ(hh, cumoutflow_diverted, cumoutflow_diverted_mWQ_lay);

        Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc_lay);
        Reset_WQ(hh, gwcumoutflow_diverted, gwcumoutflow_diverted_mWQ_lay);

        Reset_WQ(hh, cum_to_Sd, cum_to_Sd_mWQ_lay);

        Reset_WQ(hh, cum_to_soil_rechr, cum_to_soil_rechr_mWQ_lay);

        Reset_WQ(hh, HRU_cumbasinflow, HRU_cumbasinflow_mWQ_lay);

        cum_preferential_flow_to_gw[hh] = 0.0;
        soil_ssr_Buf[hh] = 0.0;
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
            CRHMException Except(SS.c_str(), TExcept::ERR);
            LogError(Except);
            throw Except;
        }
    } // for hh
} // init

void ClassWQ_Netroute_M_D::run(void) {

    long step = getstep();
    long nstep = step % Global::Freq;

    double Amount = 0.0;
    double Amount_mWQ = 0.0;

    double gw_Amount = 0.0;
    double gw_Amount_mWQ = 0.0;

    basinflow[0] = 0.0;
    basingw[0] = 0.0;

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        basinflow_mWQ[Sub] = 0.0;
    }


    for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
        if (nstep == 1) {
            distrib_sum[hh] = 0.0;

            for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
                if (distrib_hru[hh][hhh] < 0.0) // distribute by area otherwise by fraction
                    const_cast<double**> (distrib_hru)[hh][hhh] = -distrib_hru[hh][hhh] * hru_area[hh];
                distrib_sum[hh] += distrib_hru[hh][hhh];
            }

            if (distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0) {
                const_cast<double*> (distrib_Basin)[hh] = 1;
            }

            distrib_sum[hh] += distrib_Basin[hh];
        }

        Reset_WQ(hh, outflow_diverted, outflow_diverted_conc_lay);
        Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc_lay);

        for (long Sub = 0; Sub < numsubstances; ++Sub) {

            if (soil_gwDiv == 1) { // interval value
                soil_gw_Buf[hh] = soil_gw[hh]; // Buf goes to outflow (critical line for outflow)
                soil_gw_Buf_conc_lay[Sub][hh] = soil_gw_conc_lay[Sub][hh];
            }
            if (soil_ssrDiv == 1) { // interval value
                soil_ssr_Buf[hh] = soil_ssr[hh]; // Buf goes to outflow (critical line for outflow)
                soil_ssr_Buf_conc_lay[Sub][hh] = soil_ssr_conc_lay[Sub][hh];
            }

            if (soil_runoffDiv == 1) { // interval value
                soil_runoff_Buf[hh] = soil_runoff[hh];
                soil_runoff_Buf_conc_lay[Sub][hh] = soil_runoff_cWQ_lay[Sub][hh];
            }
        } // for Sub
    } // for hh

    // Substances loop (outer loop)
    for (long Sub = 0; Sub < numsubstances; ++Sub) {

        if (Sub == 0) // saves all HRUs, non WQ variables the first time
            Save();

        for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

            for (hh = 0; chkStruct(hh); ++hh) {
                if (order[hh] - 1 == jj)
                    break;
            }

            if (Sub != 0)
                Restore(hh);

            gw_Amount = 0.0;
            gw_Amount_mWQ = 0.0;

            gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];

            gwoutflow_diverted[hh] = 0.0;

            if (Sub == numsubstances - 1) {
                gwcuminflow[hh] += gwinflow[hh];
                gwcumoutflow[hh] += gwoutflow[hh];
            }

            gwinflow_mWQ_lay[Sub][hh] = soil_gw_conc_lay[Sub][hh] * gwinflow[hh]; // mg/l * mm*km^2/int
            gwoutflow_diverted_conc_lay[Sub][hh] = 0.0;

            for (long hhh = 0; chkStruct(hhh); ++hhh) {
                if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // Only GW here

                    gw_Amount = gwoutflow[hhh]; // here is units (mm*km^2/int)
                    gwoutflow[hhh] = 0.0;

                    gw_Amount_mWQ = gwoutflow_mWQ_lay[Sub][hhh]; // units (mm*km^2/int)

                    if (Sub == numsubstances - 1) {
                        gwoutflow_diverted[hhh] = gw_Amount;
                        gwcumoutflow_diverted[hhh] += gw_Amount;
                    }

                    gwcumoutflow_diverted_mWQ_lay[Sub][hhh] += gw_Amount_mWQ;

                    if (abs(gwwhereto[hhh]) <= nhru) { // assumes both Amount and Amount_mWQ divided by hru_area
                        gw_Amount /= hru_area[hh]; // assumes both Amount and Amount_mWQ divided by hru_area
                        gw_Amount_mWQ /= hru_area[hh];

                        if (gwwhereto[hhh] > 0) { // direct to HRU surface
                            double Excess = soil_rechr_max[hh] + gw_Amount - soil_rechr[hh];
                            double Free = gw_Amount - Excess;
                            double Free_mWQ = gw_Amount_mWQ * Free / gw_Amount;

                            if (Free > 0.0 && !soil_rechr_ByPass[hh]) {
                                if (Free > gw_Amount) { // units (mm*km^2/int)

                                    if (soil_rechr[hh] + gw_Amount > minFlow_WQ) {
                                        conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + gw_Amount_mWQ;
                                        conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + gw_Amount);
                                    }
                                    else {
                                        conc_soil_rechr_lay[Sub][hh] = 0.0f;
                                    }

                                    soil_moist_conc_lay[Sub][hh] = soil_moist_conc_lay[Sub][hh] * soil_moist[hh] + Amount_mWQ;
                                    soil_moist_conc_lay[Sub][hh] /= (soil_moist[hh] + gw_Amount);

                                    cum_to_soil_rechr_mWQ_lay[Sub][hh] += gw_Amount_mWQ;

                                    if (Sub == numsubstances - 1) {
                                        soil_rechr[hh] += gw_Amount;
                                        soil_moist[hh] += gw_Amount;
                                        cum_to_soil_rechr[hh] += gw_Amount;
                                    }

                                    gw_Amount = 0.0;
                                    gw_Amount_mWQ = 0.0;
                                }
                                else {
                                    gw_Amount_mWQ = gw_Amount_mWQ * Excess / gw_Amount;
                                    gw_Amount = (gw_Amount - Free) * hru_area[hh];

                                    if (soil_rechr_max[hh] > minFlow_WQ) {
                                        conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + Free_mWQ;
                                        conc_soil_rechr_lay[Sub][hh] /= soil_rechr_max[hh];
                                    }
                                    else {
                                        conc_soil_rechr_lay[Sub][hh] = 0.0f;
                                    }

                                    soil_moist_conc_lay[Sub][hh] = soil_moist_conc_lay[Sub][hh] * soil_moist[hh] + Free_mWQ;
                                    soil_moist_conc_lay[Sub][hh] /= (soil_moist[hh] + gw_Amount);

                                    cum_to_soil_rechr_mWQ_lay[Sub][hh] += Free_mWQ;

                                    if (Sub == numsubstances - 1) {
                                        soil_rechr[hh] = soil_rechr_max[hh];
                                        soil_moist[hh] += Free;
                                        cum_to_soil_rechr[hh] += Free;
                                    }
                                }
                            }

                            Excess = Sdmax[hh] + gw_Amount - Sd[hh];
                            Free = Sdmax[hh] - Sd[hh];
                            Free_mWQ = Amount_mWQ * Free / gw_Amount;

                            if (Free > 0.0 && !Sd_ByPass[hh] && gw_Amount > 0.0) {
                                if (Free > gw_Amount) { // units (mm*km^2/int)

                                    if (Sd[hh] + gw_Amount > minFlow_WQ) {
                                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + Amount_mWQ / hru_area[hh];
                                        Sd_conc_lay[Sub][hh] /= (Sd[hh] + gw_Amount);
                                        cum_to_Sd_mWQ_lay[Sub][hh] += Amount_mWQ / hru_area[hh];
                                    }
                                    else {
                                        Sd_conc_lay[Sub][hh] = 0.0f;
                                    }

                                    if (Sub == numsubstances - 1) {
                                        Sd[hh] += gw_Amount;
                                        cum_to_Sd[hh] += gw_Amount;
                                    }

                                    gw_Amount = 0.0;
                                    gw_Amount_mWQ = 0.0;
                                }
                                else {
                                    gw_Amount_mWQ = gw_Amount_mWQ * (Excess) / gw_Amount;

                                    if (Free_mWQ > minFlow_WQ) {
                                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + Free_mWQ;
                                        cum_to_Sd_mWQ_lay[Sub][hh] += Free_mWQ;
                                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] / Sdmax[hh];
                                    }
                                    else {
                                        Sd_conc_lay[Sub][hh] = 0.0f;
                                    }

                                    if (Sub == numsubstances - 1) {
                                        gw_Amount = gw_Amount - Free;
                                        Sd[hh] = Sdmax[hh];
                                        cum_to_Sd[hh] += Free;
                                    }
                                }
                            }
                        } // hh > 0
                        else { // hh < 0
                            if (gw[hh] + gw_Amount > minFlow_WQ) {
                                gw_conc_lay[Sub][hh] = gw_conc_lay[Sub][hh] * gw[hh] + gw_Amount_mWQ * gw_Amount;
                                gw_conc_lay[Sub][hh] /= (gw[hh] + gw_Amount);
                            }
                            else {
                                gw_conc_lay[Sub][hh] = 0.0f;
                            }

                            if (Sub == numsubstances - 1)
                                gw[hh] += gw_Amount;

                            gw_Amount = 0.0;
                            gw_Amount_mWQ = 0.0;
                        }
                    }
                    else { // > nHRU  move to basinflow
                        if (gw_Amount > 0.0) {
                            if (basinflow[0] + gw_Amount * 1000 > minFlow_WQ) {
                                basinflow_conc_lay[Sub][0] = basinflow_conc_lay[Sub][0] * basinflow[0] + gw_Amount_mWQ * 1000;
                                basinflow_conc_lay[Sub][0] /= (basinflow[0] + gw_Amount * 1000);
// TODO: Add code for transferring species from groundwater if not sediment (PRL)
                                cumbasinflow_mWQ_lay[Sub][0] += gw_Amount_mWQ;
                                gwcumoutflow_mWQ_lay[Sub][hh] += gw_Amount_mWQ;
                            }
                            else {
                                basinflow_conc_lay[Sub][0] = 0.0f;
                            }
                        }

                        if (Sub == numsubstances - 1) {
                            basinflow[0] += gw_Amount * 1000; // (m3)
                            HRU_cumbasinflow[hh] += gw_Amount;
                            cumoutflow[hh] += gw_Amount;
                            cumbasinflow[0] += gw_Amount;
                        }

                        gw_Amount = 0.0;
                        gw_Amount_mWQ = 0.0;
                    } // is HRU in range
                } // gwoutflow > 0.0
            } // for hhh

            inflow[hh] = gw_Amount;

            runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh];
            ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh];

            runinflow_mWQ_lay[Sub][hh] = soil_runoff_Buf_conc_lay[Sub][hh] * soil_runoff_Buf[hh] * hru_area[hh]; // in mg/l * mm*km2
            runcuminflow_mWQ_lay[Sub][hh] += runinflow_mWQ_lay[Sub][hh];
            runcumoutflow_mWQ_lay[Sub][hh] += runoutflow_mWQ_lay[Sub][hh];

            ssrinflow_mWQ_lay[Sub][hh] = soil_ssr_Buf_conc_lay[Sub][hh] * soil_ssr_Buf[hh] * hru_area[hh];
            ssrcuminflow_mWQ_lay[Sub][hh] += ssrinflow_mWQ_lay[Sub][hh];
            ssrcumoutflow_mWQ_lay[Sub][hh] += ssroutflow_mWQ_lay[Sub][hh];

            inflow[hh] += runoutflow[hh] + ssroutflow[hh]; // + gw_Amount; // add this HRU runoff and subsurface flow  (Critical line for outflow)
            inflow_mWQ_lay[Sub][hh] = runoutflow_mWQ_lay[Sub][hh] + ssroutflow_mWQ_lay[Sub][hh]; // + gw_Amount_mWQ; // add this HRU runoff and subsurface flow

            //outflow_mWQ_lay[Sub][hh] = outflow_mWQ_lay[Sub][hh] * outflow[hh];

            if (Sub == numsubstances - 1) {
                runcuminflow[hh] += runinflow[hh];
                runcumoutflow[hh] += runoutflow[hh];
                ssrcuminflow[hh] += ssrinflow[hh];
                ssrcumoutflow[hh] += ssroutflow[hh];
                cuminflow[hh] += inflow[hh];
            }

            if (outflow[hh] > 0.0) {
                Amount = outflow[hh]; // unit area
                Amount_mWQ = outflow_mWQ_lay[Sub][hh];

                if (Amount > minFlow_WQ) {
                    outflow_diverted_conc_lay[Sub][hh] = Amount_mWQ / Amount;
                    cumoutflow_mWQ_lay[Sub][hh] += outflow_mWQ_lay[Sub][hh];
                }
                else {
                    outflow_diverted_conc_lay[Sub][hh] = 0.0f;
                }

                if (Sub == numsubstances - 1)
                    outflow_diverted[hh] += Amount;

                Reset_WQ(hh, Used, Used_mWQ_lay);

                if (distrib_Basin[hh] > 0.0) { // direct to basin

                    Used[hh] = Amount * distrib_Basin[hh] / distrib_sum[hh]; // amount over basin area
                    if (distrib_sum[hh] > minFlow_WQ) {
                        Used_mWQ_lay[Sub][hh] = Amount_mWQ * distrib_Basin[hh] / distrib_sum[hh]; // fraction used
                    }
                    else {
                        Used_mWQ_lay[Sub][hh] = 0.0f;
                    }

                    HRU_cumbasinflow_mWQ_lay[Sub][hh] += Used_mWQ_lay[Sub][hh];
                    if ((basinflow[0] + Used[hh]) > minFlow_WQ) {
                        basinflow_conc_lay[Sub][0] = basinflow_conc_lay[Sub][0] * basinflow[0] + Used_mWQ_lay[Sub][hh] * 1000;
                        basinflow_conc_lay[Sub][0] /= (basinflow[0] + Used[hh] * 1000);

//                        basinflow_mWQ[Sub] = basinflow_conc_lay[Sub][0] * basinflow[0] + Used_mWQ_lay[Sub][hh] * 1000;
                    }
                    else {
                        basinflow_conc_lay[Sub][0] = 0.0;
//                        basinflow_mWQ[Sub] = 0.0;
                    }

                    basinflow_mWQ[Sub] += Used_mWQ_lay[Sub][hh] * 1000;
                    if (Sub == numsubstances - 1) {
                        basinflow[0] += Used[hh] * 1000; // (m3)
                        cumbasinflow[0] += basinflow[0];
                        cumoutflow[hh] += Used[hh];
                        HRU_cumbasinflow[hh] += Used[hh];
                    }
                    Amount = 0.0;
                    Amount_mWQ = 0.0;
                }

                for (long To = 0; chkStruct(To); ++To) {

                    if (hh != To && distrib_hru[hh][To] > 0.0) {
                        Amount = outflow[hh] - Used[hh];
                        Amount = Amount / hru_area[To] * distrib_hru[hh][To] / (distrib_sum[hh] - distrib_Basin[hh]); // outflow (mm*km^2/int) to mm

                        if (distrib_sum[hh] - distrib_Basin[hh] > minFlow_WQ) {
                            Amount_mWQ = (outflow_mWQ_lay[Sub][hh] - Used_mWQ_lay[Sub][hh]) / hru_area[To] * distrib_hru[hh][To];
                            Amount_mWQ /= (distrib_sum[hh] - distrib_Basin[hh]);
                            //}else{
                            Amount_mWQ = 0.0f;
                        }


                        if (preferential_flow[hh]) {

                            if (gw[To] + Amount > minFlow_WQ) {
                                gw_conc_lay[Sub][To] = gw_conc_lay[Sub][To] * gw[To] + Amount_mWQ;
                                gw_conc_lay[Sub][To] /= (gw[To] + Amount);
                            }
                            else
                            {
                                gw_conc_lay[Sub][To] = 0.0f;
                            }

                            if (Sub == numsubstances - 1) {
                                gw[To] += Amount;
                                cum_preferential_flow_to_gw[To] += Amount;
                            }

                            Amount = 0.0;
                            Amount_mWQ = 0.0;
                        }
                        else if (!soil_rechr_ByPass[To] && Amount > 0.0) { // assumes both Amount and Amount_mWQ divided by hru_area
                            if (soil_rechr[To] + Amount >= soil_rechr_max[To]) { // units (mm*km^2/int)
                                double Excess = soil_rechr[To] + Amount - soil_rechr_max[To];
                                double Free = Amount - Excess;

                                if (soil_rechr[To] + Amount > minFlow_WQ) {
                                    conc_soil_rechr_lay[Sub][To] = conc_soil_rechr_lay[Sub][To] * soil_rechr[To] + Amount_mWQ;
                                    conc_soil_rechr_lay[Sub][To] /= (soil_rechr[To] + Amount);
                                }
                                else {
                                    conc_soil_rechr_lay[Sub][To] = 0.0f;
                                }

                                if (soil_lower[To] + soil_rechr[To] + Free > minFlow_WQ) {
                                    soil_moist_conc_lay[Sub][To] = (conc_soil_lower_lay[Sub][To] * soil_lower[To] + conc_soil_rechr_lay[Sub][To] * soil_rechr[To] + Amount_mWQ * Free); // present mQW
                                    soil_moist_conc_lay[Sub][To] /= (soil_lower[To] + soil_rechr[To] + Free);
                                }
                                else {
                                    soil_moist_conc_lay[Sub][To] = 0.0f;
                                }

                                if (Sub == numsubstances - 1) {
                                    soil_rechr[To] += Free;
                                    soil_moist[To] = soil_lower[To] + soil_rechr[To];
                                }
                                Amount = Excess;
                                Amount_mWQ = conc_soil_rechr_lay[Sub][To] * Excess;

                            }
                            else {

                                if (soil_rechr[To] + Amount > minFlow_WQ) {
                                    conc_soil_rechr_lay[Sub][To] = conc_soil_rechr_lay[Sub][To] * soil_rechr[To] + Amount_mWQ;
                                    conc_soil_rechr_lay[Sub][To] /= (soil_rechr[To] + Amount);
                                }
                                else {
                                    conc_soil_rechr_lay[Sub][To] = 0.0;
                                }

                                if (soil_lower[To] + soil_rechr[To] + Amount > minFlow_WQ) {
                                    soil_moist_conc_lay[Sub][To] = (conc_soil_lower_lay[Sub][To] * soil_lower[To] + conc_soil_rechr_lay[Sub][To] * (soil_rechr[To] + Amount_mWQ));
                                    soil_moist_conc_lay[Sub][To] /= (soil_lower[To] + soil_rechr[To] + Amount); // amount used
                                }
                                else {
                                    soil_moist_conc_lay[Sub][To] = 0.0f;
                                }

                                if (Sub == numsubstances - 1) {
                                    soil_rechr[To] = soil_rechr[To] + Amount;
                                    soil_moist[To] = soil_lower[To] + soil_rechr[To];
                                }

                                Amount = 0.0;
                                Amount_mWQ = 0.0;
                            }
                        }
                        else if (!Sd_ByPass[To] && Amount > 0.0) {

                            if (Sd[To] + Amount >= Sdmax[To]) { // units (mm*km^2/int)
                                double Excess = Sd[To] + Amount - Sdmax[To];
                                double Free = Amount - Excess;

                                if (Sd[To] + Amount > minFlow_WQ) {
                                    if (Sd[To] + Free == 0) {
                                        Sd_conc_lay[Sub][To] = 0.0f;
                                    } else {
                                        Sd_conc_lay[Sub][To] = Sd_conc_lay[Sub][To] * Sd[To] + Amount_mWQ * Free / Amount;
                                        Sd_conc_lay[Sub][To] /= (Sd[To] + Free);
                                    }
                                }
                                else {
                                    Sd_conc_lay[Sub][To] = 0.0f;
                                }

                                cum_to_Sd_mWQ_lay[Sub][To] += Amount_mWQ * Free / Amount;

                                if (Sub == numsubstances - 1) {
                                    Sd[To] += Free;
                                    cum_to_Sd[To] += Amount;
                                }

                                Amount = Excess;
                                Amount_mWQ = Sd_conc_lay[Sub][To] * Excess;

                            }
                            else {

                                if (Sd[To] + Amount > minFlow_WQ) {
                                    Sd_conc_lay[Sub][To] = Sd_conc_lay[Sub][To] * Sd[To] + Amount_mWQ;
                                    Sd_conc_lay[Sub][To] /= (Sd[To] + Amount);
                                }
                                else {
                                    Sd_conc_lay[Sub][To] = 0.0;
                                }

                                if (Sub == numsubstances - 1) {
                                    Sd[To] = Sd[To] + Amount;
                                    cum_to_Sd[To] += Amount;
                                }

                                Amount = 0.0;
                                Amount_mWQ = 0.0;
                            }
                        } // if !Sd_ByPass

                        if ((redirected_residual[To] + Amount * hru_area[To]) > minFlow_WQ) { // handle excess
                            redirected_residual_conc_lay[Sub][To] = redirected_residual_conc_lay[Sub][To] * redirected_residual[To] + Amount_mWQ * hru_area[To];
                            redirected_residual_conc_lay[Sub][To] /= (redirected_residual[To] + Amount * hru_area[To]);
                        }
                        else {
                            redirected_residual_conc_lay[Sub][To] = 0.0f;
                        } // contribute to this array

                        if (Sub == numsubstances - 1) {
                            redirected_residual[To] += Amount * hru_area[To];
                        }

                        Amount = 0.0;
                        Amount_mWQ = 0.0;
                    }
                } // distribute outflow over HRUs (for)
            } // if outflow > 0.0

            if (nstep == 0 && Sub == numsubstances - 1) { // end of every day and last substance
                if (soil_ssrDiv > 1) // daily value - ready for next day
                    soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

                if (soil_runoffDiv > 1) { // daily value - ready for next day
                    soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;
                }

                if (soil_gwDiv > 1) // daily value - ready for next day
                    soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;

            } // end if

            if (nstep == 0) {
                if (soil_runoffDiv > 1) // daily value - ready for next day
                    soil_runoff_Buf_conc_lay[Sub][hh] = soil_runoff_cWQ_lay[Sub][hh] / soil_runoffDiv;
            }


            if (outflow[hh] > minFlow_WQ) {
                outflow_mWQ_lay[Sub][hh] = std::fmax(outflow_mWQ_lay[Sub][hh], 0.0f);
                outflow_cWQ_lay[Sub][hh] = outflow_mWQ_lay[Sub][hh] / outflow[hh];
            }
            else {
                outflow_cWQ_lay[Sub][hh] = 0.0f;
            }
        } // for jj accessing hh
    } // for Sub

    if (variation == VARIATION_ORG) {
        hruDelay->DoMuskingum(); // need to update for later HRUs
        for (long Sub = 0; Sub < numsubstances; ++Sub)
            hruDelay_mWQ[Sub]->DoMuskingum(); // need to update for later HRUs
    }
    else if (variation == VARIATION_1) {
        Clark_hruDelay->DoClark(); // need to update for later HRUs
        for (long Sub = 0; Sub < numsubstances; ++Sub)
            Clark_hruDelay_mWQ[Sub]->DoClark(); // need to update for later HRUs
    }

    runDelay->DoClark();
    ssrDelay->DoClark();
    gwDelay->DoClark();

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        runDelay_mWQ[Sub]->DoClark();
        ssrDelay_mWQ[Sub]->DoClark();
        gwDelay_mWQ[Sub]->DoClark();
    }

    basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
    basingw_s[0] = basingw[0] * Global::Freq / 86400.0;
} // run

void ClassWQ_Netroute_M_D::finish(bool good) {


    double Allcuminflow = 0.0;
    double Allcumoutflow = 0.0;
    double Allcumoutflowdiverted = 0.0;

    double Allcuminflow_mWQ = 0.0;
    double Allcumoutflow_mWQ = 0.0;
    double Allcumoutflowdiverted_mWQ = 0.0;

    double Allgwcuminflow = 0.0;
    double Allgwcumoutflow = 0.0;
    double Allgwcumoutflowdiverted = 0.0;

    double Allgwcuminflow_mWQ = 0.0;
    double Allgwcumoutflow_mWQ = 0.0;
    double Allgwcumoutflowdiverted_mWQ = 0.0;

    double Allssrcuminflow = 0.0;
    double Allssrcumoutflow = 0.0;
    double Allruncuminflow = 0.0;
    double Allruncumoutflow = 0.0;

    double Allssrcuminflow_mWQ = 0.0;
    double Allssrcumoutflow_mWQ = 0.0;
    double Allruncuminflow_mWQ = 0.0;
    double Allruncumoutflow_mWQ = 0.0;

    double AllSdcuminflow = 0.0;
    double Allrechrcuminflow = 0.0;

    double AllSdcuminflow_mWQ = 0.0;
    double Allrechrcuminflow_mWQ = 0.0;
    double AllTotal = 0.0;
    double Total = 0.0;

    string S = string("*H2O*");
    LogDebug(S.c_str());
    LogMessage(" ");

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);

        if (variation == VARIATION_1)
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), Clark_hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
        else if (variation == VARIATION_ORG)
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow_diverted       (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumbasinflow                (mm) (mm*km^2) (mm*basin): ").c_str(), cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");

        Total = cumoutflow[hh] + gwcumoutflow[hh] - cumbasinflow[hh] - cum_to_soil_rechr[hh] - cum_to_Sd[hh] - gwcumoutflow[hh]
            + cumoutflow_diverted[hh] + gwcumoutflow_diverted[hh] - cum_redirected_residual[hh];

        Allcuminflow += cuminflow[hh];
        Allcumoutflow += cumoutflow[hh];

        Allgwcuminflow += gwcuminflow[hh];
        Allgwcumoutflow += gwcumoutflow[hh];

        Allssrcumoutflow += ssrcumoutflow[hh];
        Allssrcuminflow += ssrcuminflow[hh];
        Allruncuminflow += runcuminflow[hh];
        Allruncumoutflow += runcumoutflow[hh];

        AllSdcuminflow += cum_to_Sd[hh];
        Allrechrcuminflow += cum_to_soil_rechr[hh];

        Allcumoutflowdiverted += cumoutflow_diverted[hh];
        Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

        AllTotal += Total;
    }  // for hh

    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);

    LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Total (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total);
    LogDebug(" ");

    /*  for(long Sub = 0; Sub < numsubstances; ++Sub){

        String S = String("Substance# ") + (Sub+1);
        LogDebug(S.c_str());
        LogMessage(" ");

        Allcuminflow_mWQ = 0.0;
        Allcumoutflow_mWQ = 0.0;
        Allcumoutflowdiverted_mWQ = 0.0;

        Allgwcuminflow_mWQ = 0.0;
        Allgwcumoutflow_mWQ = 0.0;
        Allgwcumoutflowdiverted_mWQ = 0.0;

        Allssrcuminflow_mWQ = 0.0;
        Allssrcumoutflow_mWQ = 0.0;
        Allruncuminflow_mWQ = 0.0;
        Allruncumoutflow_mWQ = 0.0;

        AllSdcuminflow_mWQ = 0.0;
        Allrechrcuminflow_mWQ = 0.0;

        for(hh = 0; chkStruct(); ++hh) {
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cuminflow_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow_mWQ              (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumoutflow_diverted_mWQ     (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          if(variation == VARIATION_1)
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), Clark_hruDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);
          else
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcuminflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrcumoutflow_mWQ           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcuminflow_mWQ         (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runoffcumoutflow_mWQ        (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcuminflow_mWQ             (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow_diverted       (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwcumoutflow_diverted_mWQ   (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_Sd_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_to_soil_rechr_mWQ       (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cum_redirected_residual_mWQ (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumbasinflow                (mm) (mm*km^2) (mm*basin): ").c_str(), cumbasinflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' cumbasinflow_conc           (mm) (mm*km^2) (mm*basin): ").c_str(), cumbasinflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogMessageA(hh, string("'" + Name + " (WQ_Netroute_M_D)' HRU_cumbasinflow_mwq        (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow_mWQ_lay[Sub][hh]/hru_area[hh], hru_area[hh], basin_area[0]);
          LogDebug(" ");


          Allcuminflow_mWQ += cuminflow_mWQ_lay[Sub][hh];
          Allcumoutflow_mWQ += cumoutflow_mWQ_lay[Sub][hh];
          Allcumoutflowdiverted_mWQ += cumoutflow_diverted_mWQ_lay[Sub][hh];

          Allgwcuminflow_mWQ += gwcuminflow_mWQ_lay[Sub][hh];
          Allgwcumoutflow_mWQ += gwcumoutflow_mWQ_lay[Sub][hh];
          Allgwcumoutflowdiverted_mWQ += gwcumoutflow_diverted_mWQ_lay[Sub][hh];

          Allssrcumoutflow_mWQ += ssrcumoutflow_mWQ_lay[Sub][hh];
          Allssrcuminflow_mWQ += ssrcuminflow_mWQ_lay[Sub][hh];
          Allruncuminflow_mWQ += runcuminflow_mWQ_lay[Sub][hh];
          Allruncumoutflow_mWQ += runcumoutflow_mWQ_lay[Sub][hh];

          AllSdcuminflow_mWQ += cum_to_Sd_mWQ_lay[Sub][hh];
          Allrechrcuminflow_mWQ += cum_to_soil_rechr_mWQ_lay[Sub][hh];

          LogMessage(" ");
        }  // for hh

        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' cumbasinflow (m^3):                   ").c_str(), cumbasinflow[0]);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' cumbasinflow_mWQ_lay (mg):            ").c_str(), cumbasinflow_mWQ_lay[Sub][0]);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' cumbasingw   (m^3):                   ").c_str(), cumbasingw[0]);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' cumbasingw_mWQ_lay (mg):              ").c_str(), cumbasingw_mWQ_lay[Sub][0]);
        LogMessage(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcuminflow_mWQ (mm*basin):          ").c_str(), Allgwcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflow_mWQ (mm*basin):         ").c_str(), Allgwcumoutflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allgwcumoutflowdiverted_mWQ (mm*basin): ").c_str(), Allgwcumoutflowdiverted_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcuminflow_mWQ (mm*basin):            ").c_str(), Allcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflow (mm*basin):               ").c_str(), Allcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allcumoutflowdiverted_mWQ (mm*basin):   ").c_str(), Allcumoutflowdiverted_mWQ);
        LogDebug(" ");
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcuminflow_mWQ (mm*basin):         ").c_str(), Allssrcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allssrcumoutflow_mWQ (mm*basin):        ").c_str(), Allssrcumoutflow_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncuminflow_mWQ (mm*basin):         ").c_str(), Allruncuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allruncumoutflow_mWQ (mm*basin):        ").c_str(), Allruncumoutflow_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' AllSdcuminflow (mm*basin):              ").c_str(), AllSdcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' AllSdcuminflow_mWQ (mm*basin):          ").c_str(), AllSdcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allrechrcuminflow (mm*basin):           ").c_str(), Allrechrcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' Allrechrcuminflow_mWQ (mm*basin):       ").c_str(), Allrechrcuminflow_mWQ);
        LogDebug(" ");
        LogMessage(string("'" + Name + " (WQ_Netroute_M_D)' AllTotal              (mm*basin):       ").c_str(), AllTotal);
        LogDebug(" ");
      } // for Sub */

    LogDebug(" ");

    if (variation == VARIATION_1)
        delete[] Clark_hruDelay_mWQ;

    if (variation == VARIATION_ORG)
        delete[] hruDelay_mWQ;

    delete[] ssrDelay_mWQ;
    delete[] runDelay_mWQ;
    delete[] gwDelay_mWQ;

    delete ssrDelay;
    delete runDelay;
    delete gwDelay;
}


void ClassWQ_Netroute_M_D::Reset_WQ(long hru, double* var, double** var_WQ_lay) {
    var[hru] = 0.0;
    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        var_WQ_lay[Sub][hru] = 0.0;
    }
}

void ClassWQ_Netroute_M_D::Set_WQ(const long hru, double* var, double* var_conc, double Amount, double amount_conc) {

    var[hru] = Amount;
    if (Amount > 0.0)
        var_conc[hru] = amount_conc;
    else
        var_conc[hru] = 0.0;
}

void ClassWQ_Netroute_M_D::copy_array(double* from, double* to) {
    for (hh = 0; chkStruct(); ++hh)
        to[hh] = from[hh];
}

void ClassWQ_Netroute_M_D::restore_hru(double* from, double* to, long hh) {
    to[hh] = from[hh];
}

void ClassWQ_Netroute_M_D::Restore(long hh) {

    restore_hru(gwoutflow_0, gwoutflow, hh);
    restore_hru(outflow_0, outflow, hh);
}

void ClassWQ_Netroute_M_D::Save() {

    copy_array(gwoutflow, gwoutflow_0);
    copy_array(outflow, outflow_0);
}

ClassWQ_Netroute_M_D* ClassWQ_Netroute_M_D::klone(string name) const {
    return new ClassWQ_Netroute_M_D(name);
}

double ClassWQ_Netroute_M_D::Function1(double* I, long hh) {
    return runDelay->ChangeLag(I, hh);
}

double ClassWQ_Netroute_M_D::Function2(double* X, long hh) {
    return runDelay->ChangeStorage(X, hh);
}