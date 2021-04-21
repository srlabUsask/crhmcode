#include "ClassWQ_Netroute.h"


ClassWQ_Netroute* ClassWQ_Netroute::klone(string name) const {
    return new ClassWQ_Netroute(name);
}

void ClassWQ_Netroute::decl(void) {

    // kg/km2 = (mg/l)*mm = mg/m2

    Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'\
                    'uses Clark,' \
                    'uses Muskingum.'";

    declvar("inflow", TDim::NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

    declvar("inflow_mWQ", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg/l * mm*km^2/int)", &inflow_mWQ, &inflow_mWQ_lay, numsubstances);

    declstatvar("cuminflow", TDim::NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

    declstatvar("cuminflow_mWQ", TDim::NDEFN, "cumulative mass of solute inflow from other HRUs", "(mg/l * mm*km^2/int)", &cuminflow_mWQ, &cuminflow_mWQ_lay, numsubstances);

    declvar("outflow", TDim::NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

    declvar("outflow_mWQ", TDim::NDEFN, "Substance mass: HRU outflow", "(mg/l * mm*km^2/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);

    declvar("outflow_cWQ", TDim::NDEFN, "Substance concentration: HRU outflow", "(mg/l)", &outflow_cWQ, &outflow_cWQ_lay, numsubstances);

    declstatvar("cumoutflow", TDim::NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

    declstatvar("cumoutflow_mWQ", TDim::NDEFN, "cumulative mass of solute HRU outflow", "(mg/l * mm*km^2/int)", &cumoutflow_mWQ, &cumoutflow_mWQ_lay, numsubstances);

    declvar("outflow_diverted", TDim::NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

    declvar("outflow_diverted_conc", TDim::NDEFN, "Concentration: HRU outflow diverted to another HRU", "(mg/l)", &outflow_diverted_conc, &outflow_diverted_conc_lay, numsubstances);

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

    declvar("basinflow_conc", TDim::NDEF, "basin surface and sub-surface outflow", "(mg/l)", &basinflow_conc, &basinflow_conc_lay, numsubstances);

    decldiag("basinflow_s", TDim::BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

    declvar("cumbasinflow", TDim::BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

    declvar("cumbasinflow_mWQ", TDim::NDEF, "cumulative mass of solute basin surface and sub-surface outflow", "(mg/l * mm*km^2/int)", &cumbasinflow_mWQ, &cumbasinflow_mWQ_lay, numsubstances);

    declvar("basingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

    declvar("basingw_conc", TDim::NDEF, "cumulative basin groundwater outflow", "(m^3/int)", &basingw_conc, &basingw_conc_lay, numsubstances);

    decldiag("basingw_s", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

    declstatvar("cumbasingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

    declvar("cumbasingw_mWQ", TDim::NDEF, "cumulative mass of solute basin groundwater outflow", "(mg/l * mm*km^2/int)", &cumbasingw_mWQ, &cumbasingw_mWQ_lay, numsubstances);


    decllocal("soil_ssr_Buf", TDim::NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

    declvar("soil_ssr_Buf_conc", TDim::NDEFN, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf_conc, &soil_ssr_Buf_conc_lay, numsubstances);

    decllocal("soil_runoff_Buf", TDim::NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

    declvar("soil_runoff_Buf_conc", TDim::NDEFN, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf_conc, &soil_runoff_Buf_conc_lay, numsubstances);

    decllocal("soil_gw_Buf", TDim::NHRU, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf);

    declvar("soil_gw_Buf_conc", TDim::NDEFN, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf_conc, &soil_gw_Buf_conc_lay, numsubstances);


    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

    declparam("Lag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", &Lag);

    declparam("ssrKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

    declparam("ssrLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

    declparam("runKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

    declparam("runLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

    declparam("gwKstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

    declparam("gwLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

    declparam("order", TDim::NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

    declparam("whereto", TDim::NHRU, "[0]", "0", "1000", "send to; 0 - basin outflow, or HRU input", "()", &whereto);

    declparam("gwwhereto", TDim::NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

    declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

    declparam("Sd_ByPass", TDim::NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

    declparam("soil_rechr_ByPass", TDim::NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);

    declparam("preferential_flow", TDim::NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


    soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

    soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

    soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

    declgetvar("*", "soil_gw_conc", "(mg)", &soil_gw_conc, &soil_gw_conc_lay);

    declgetvar("*", "soil_ssr_conc", "(mg)", &soil_ssr_conc, &soil_ssr_conc_lay);

    declgetvar("*", "soil_runoff_cWQ", "(mg)", &soil_runoff_cWQ, &soil_runoff_cWQ_lay);


    declputvar("*", "Sd", "(mm)", &Sd);

    declputvar("*", "Sd_conc", "(mg)", &Sd_conc, &Sd_conc_lay);

    declputvar("*", "soil_moist", "(mm)", &soil_moist);

    declputvar("*", "soil_moist_conc", "(mg/l)", &soil_moist_conc, &soil_moist_conc_lay);

    declputvar("*", "soil_lower", "(mm)", &soil_lower);

    declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

    declputvar("*", "redirected_residual", "(mg)", &redirected_residual);

    declputvar("*", "redirected_residual_conc", "(mm*km^2/int)", &redirected_residual_conc, &redirected_residual_conc_lay);

    declputvar("*", "cum_redirected_residual", "(mg)", &cum_redirected_residual);

    declputvar("*", "cum_redirected_residual_mWQ", "(mg/l * mm*km^2/int)", &cum_redirected_residual_mWQ, &cum_redirected_residual_mWQ_lay);

    declputvar("*", "gw", "(mm)", &gw);

    declputvar("*", "gw_conc", "(mg/l)", &gw_conc, &gw_conc_lay);

    declputvar("*", "conc_soil_rechr", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay);

    declputvar("*", "conc_soil_lower", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay);


    decllocal("gwoutflow_0", TDim::NHRU, "", "", &gwoutflow_0);

    decllocal("outflow_0", TDim::NHRU, "", "", &outflow_0);


    variation_set = VARIATION_1;

    decllocal("Ktravel", TDim::NHRU, "travel time", "(d)", &Ktravel);

    declparam("route_n", TDim::NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &route_n);

    declparam("route_R", TDim::NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "(m)", &route_R);

    declparam("route_S0", TDim::NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &route_S0);

    declparam("route_L", TDim::NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

    declparam("route_X_M", TDim::NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &route_X_M);

    declparam("Channel_shp", TDim::NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);


    variation_set = VARIATION_0;

    declparam("Kstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", &Kstorage);

    variation_set = VARIATION_ORG;
}

void ClassWQ_Netroute::init(void) {

    nhru = getdim(TDim::NHRU);

    try {
        ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
        runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
        gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

        ssrDelay_mWQ = new ClassClark * [numsubstances];
        runDelay_mWQ = new ClassClark * [numsubstances];
        gwDelay_mWQ = new ClassClark * [numsubstances];

        for (long Sub = 0; Sub < numsubstances; ++Sub) {
            ssrDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], ssrKstorage, ssrLag, nhru);
            runDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], runKstorage, runLag, nhru);
            gwDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], gwKstorage, gwLag, nhru);
        }

        if (variation == VARIATION_ORG) {
            Clark_hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);
            Clark_hruDelay_mWQ = new ClassClark * [numsubstances];

            for (long Sub = 0; Sub < numsubstances; ++Sub)
                Clark_hruDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Kstorage, Lag, nhru);
        }
        else if (variation == VARIATION_1) {
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
        } // VARIATION_1
    } // try
    catch (std::bad_alloc) {
        CRHMException Except("Could not allocate in module CRACK.", TExcept::TERMINATE);
        LogError(Except);
        throw Except;
    }

    if (soil_ssrDiv > 1) {
        string S = "Netroute:  \"soil_ssr\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (soil_runoffDiv > 1) {
        string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    if (soil_gwDiv > 1) {
        string S = "Netroute:  \"gw_flow\". Converting to mm/int";
        CRHMException TExcept(S.c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    Reset_WQ(0, basinflow, basinflow_conc_lay);
    Reset_WQ(0, cumbasinflow, cumbasinflow_mWQ_lay);
    Reset_WQ(0, basingw, basingw_conc_lay);
    Reset_WQ(0, cumbasingw, cumbasingw_mWQ_lay);

    basinflow_s[0] = 0.0;
    basingw_s[0] = 0.0;

    for (long Sub = 0; Sub < numsubstances; ++Sub) {

        if (variation == VARIATION_ORG)
            Clark_hruDelay_mWQ[Sub] = new ClassClark(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Kstorage, Lag, nhru);
        else // ClassMuskingum
            hruDelay_mWQ[Sub] = new ClassMuskingum(inflow_mWQ_lay[Sub], outflow_mWQ_lay[Sub], Ktravel, route_X_M, Lag, nhru);

        ssrDelay_mWQ[Sub] = new ClassClark(ssrinflow_mWQ_lay[Sub], ssroutflow_mWQ_lay[Sub], ssrKstorage, ssrLag, nhru, -1);
        runDelay_mWQ[Sub] = new ClassClark(runinflow_mWQ_lay[Sub], runoutflow_mWQ_lay[Sub], runKstorage, runLag, nhru, -1);
        gwDelay_mWQ[Sub] = new ClassClark(gwinflow_mWQ_lay[Sub], gwoutflow_mWQ_lay[Sub], gwKstorage, gwLag, nhru, -1);
    } // for Sub

    for (hh = 0; hh < nhru; ++hh) {
        Reset_WQ(hh, inflow, inflow_mWQ_lay);
        Reset_WQ(hh, cuminflow, cuminflow_mWQ_lay);

        Reset_WQ(hh, outflow, outflow_mWQ_lay);
        Reset_WQ(hh, cumoutflow, cumoutflow_mWQ_lay);

        Reset_WQ(hh, gwinflow, gwinflow_mWQ_lay); ;
        Reset_WQ(hh, gwcuminflow, gwcuminflow_mWQ_lay); ;

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

void ClassWQ_Netroute::run(void) {

    long step = getstep();
    long nstep = step % Global::Freq;

    double gw_Amount = 0.0;
    double gw_Amount_mWQ = 0.0;

    double Amount = 0.0;
    double Amount_mWQ = 0.0;

    Reset_WQ(0, basinflow, basinflow_conc_lay);
    Reset_WQ(0, basingw, basingw_conc_lay);

    for (long hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.

        Reset_WQ(hh, outflow_diverted, outflow_diverted_conc_lay);
        Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc_lay);

        for (long Sub = 0; Sub < numsubstances; ++Sub) {

            if (soil_gwDiv == 1) { // interval value
                soil_gw_Buf[hh] = soil_gw[hh];
                soil_gw_Buf_conc_lay[Sub][hh] = soil_gw_conc_lay[Sub][hh];
            }
            if (soil_ssrDiv == 1) { // interval value
                soil_ssr_Buf[hh] = soil_ssr[hh];
                soil_ssr_Buf_conc_lay[Sub][hh] = soil_ssr_conc_lay[Sub][hh];
            }

            if (soil_runoffDiv == 1) { // interval value
                soil_runoff_Buf[hh] = soil_runoff[hh];
                soil_runoff_Buf_conc_lay[Sub][hh] = soil_runoff_cWQ_lay[Sub][hh];
            }
        } // for Sub
    } // for hh

    for (long Sub = 0; Sub < numsubstances; ++Sub) {

        if (Sub == 0) // saves all HRUs, non WQ variables the first time
            Save();

        for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

            for (hh = 0; chkStruct(hh); ++hh)
                if (order[hh] - 1 == jj)
                    break;

            if (Sub != 0)
                Restore(hh);

            // FROM GW (starts here...)  

            gw_Amount = 0.0;
            gw_Amount_mWQ = 0.0;

            Amount = 0.0;
            Amount_mWQ = 0.0;

            gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];
            gwinflow_mWQ_lay[Sub][hh] = soil_gw_conc_lay[Sub][hh] * gwinflow[hh];

            gwoutflow_diverted[hh] = 0.0;
            gwoutflow_diverted_conc_lay[Sub][hh] = 0.0;

            for (long hhh = 0; chkStruct(hhh); ++hhh) {
                if (gwoutflow[hhh] > 0.0) {
                    gwoutflow_diverted[hhh] = gwoutflow[hhh]; // gwoutflow_diverted[hh] = gwoutflow[hhh];

                    gw_Amount = gwoutflow[hhh] / hru_area[hh]; // units (mm*km^2/int)
                    gw_Amount_mWQ = gwoutflow_mWQ_lay[Sub][hhh] / hru_area[hh]; // units (mm*km^2/int)
                    gwoutflow[hh] = 0.0;

                    gwcumoutflow_diverted[hhh] += gw_Amount;
                    gwcumoutflow_diverted_mWQ_lay[Sub][hhh] += gw_Amount_mWQ;

                    if (abs(gwwhereto[hhh]) <= nhru) {
                        if (gwwhereto[hhh] > 0) { // direct to HRU surface
                            double free = soil_rechr_max[hh] - soil_rechr[hh];
                            //double free_mWQ = Amount_mWQ*free/gw_Amount;

                            if (free > 0.0 && !soil_rechr_ByPass[hh]) {
                                if (free > gw_Amount) { // units (mm*km^2/int)

                                    conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + gw_Amount_mWQ;
                                    conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + gw_Amount);

                                    soil_moist_conc_lay[Sub][hh] = soil_moist_conc_lay[Sub][hh] * soil_moist[hh] + gw_Amount_mWQ;
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
                                    double free_WQ_2rechr = gw_Amount_mWQ * free / gw_Amount;
                                    gw_Amount_mWQ = gw_Amount_mWQ * (gw_Amount - free) / gw_Amount;
                                    gw_Amount = (gw_Amount - free);

                                    conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + free_WQ_2rechr;
                                    conc_soil_rechr_lay[Sub][hh] /= soil_rechr_max[hh];

                                    soil_moist_conc_lay[Sub][hh] = soil_moist_conc_lay[Sub][hh] * soil_moist[hh] + free_WQ_2rechr;
                                    soil_moist_conc_lay[Sub][hh] /= (soil_moist[hh] + free);

                                    cum_to_soil_rechr_mWQ_lay[Sub][hh] += free_WQ_2rechr;

                                    if (Sub == numsubstances - 1) {
                                        soil_rechr[hh] = soil_rechr_max[hh];
                                        soil_moist[hh] = soil_moist[hh] + free;
                                        cum_to_soil_rechr[hh] += free;
                                    }
                                }
                            }

                            free = Sdmax[hh] - Sd[hh];
                            //free_mWQ = Amount_mWQ*free/gw_Amount;

                            if (free > 0.0 && !Sd_ByPass[hh] && gw_Amount > 0.0) {
                                if (free > gw_Amount) { // units (mm*km^2/int)
                                    if ((Sd[hh] + gw_Amount) > minFlow_WQ)
                                    {
                                        Sd_conc_lay[Sub][hh] /= (Sd[hh] + gw_Amount);
                                    }
                                    else 
                                    {
                                        Sd_conc_lay[Sub][hh] = 0.0f;
                                    }
                                        
                                    cum_to_Sd_mWQ_lay[Sub][hh] += gw_Amount_mWQ;

                                    if (Sub == numsubstances - 1) {
                                        Sd[hh] += gw_Amount;
                                        cum_to_Sd[hh] += gw_Amount;
                                    }

                                    gw_Amount = 0.0;
                                    gw_Amount_mWQ = 0.0;
                                }
                                else {
                                    double free_mWQ_2Sd = gw_Amount_mWQ * free / gw_Amount;
                                    gw_Amount_mWQ = gw_Amount_mWQ * (gw_Amount - free) / gw_Amount;

                                    Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + free_mWQ_2Sd;
                                    Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] / Sdmax[hh];

                                    cum_to_Sd_mWQ_lay[Sub][hh] += free_mWQ_2Sd;

                                    if (Sub == numsubstances - 1) {
                                        gw_Amount = (gw_Amount - free); // this is inside the substances-loop, so its useless because it is overwritten for every substance right after the substances-loop starts                    Sd[hh] = Sdmax[hh];
                                        cum_to_Sd[hh] += free;
                                    }
                                }
                            }
                        } // hh > 0
                        else if (gwwhereto[hh] == 0) { // move to basin gw
                            cumbasingw_mWQ_lay[Sub][0] += gw_Amount_mWQ;

                            if ((basingw[0] + gw_Amount) > 0.0) {
                                basingw_conc_lay[Sub][0] = basingw_conc_lay[Sub][0] * basingw[0] + gw_Amount_mWQ * 1000;
                                basingw_conc_lay[Sub][0] /= (basingw[0] + gw_Amount * 1000);
                            }
                            else {
                                basingw_conc_lay[Sub][0] = 0.0;
                            }

                            gwcumoutflow_mWQ_lay[Sub][hh] += gw_Amount_mWQ;

                            if (Sub == numsubstances - 1) {
                                basingw[0] += gw_Amount * 1000; // (m3) end of every day
                                cumbasingw[0] += basingw[0];
                                gwcumoutflow[hh] += gw_Amount;
                            }

                            gw_Amount = 0.0;
                            gw_Amount_mWQ = 0.0;
                        }
                        else { // hh < 0
                            gw_conc_lay[Sub][hh] = gw_conc_lay[Sub][hh] * gw[hh] + gw_Amount_mWQ * gw_Amount;
                            gw_conc_lay[Sub][hh] /= (gw[hh] + gw_Amount);

                            if (Sub == numsubstances - 1)
                                gw[hh] += gw_Amount;

                            gw_Amount = 0.0;
                            gw_Amount_mWQ = 0.0;
                        }
                    }
                    else { // > nHRU move to basinflow
                        cumbasinflow_mWQ_lay[Sub][0] += gw_Amount_mWQ;

                        basinflow_conc_lay[Sub][0] = basinflow_conc_lay[Sub][0] * basinflow[0] + gw_Amount_mWQ * 1000;

                        if ((basinflow[0] + gw_Amount) > 0.0)
                            basinflow_conc_lay[Sub][hh] /= (basinflow[0] + gw_Amount * 1000);
                        else
                            basinflow_conc_lay[Sub][hh] = 0.0;

                        gwcumoutflow_mWQ_lay[Sub][hh] += gw_Amount_mWQ;

                        if (Sub == numsubstances - 1) {
                            HRU_cumbasinflow[hh] += gw_Amount;
                            basinflow[0] += gw_Amount * hru_area[hh] * 1000; // (m3)
                            cumbasinflow[0] += basinflow[0];
                            cumoutflow[hh] += gw_Amount * hru_area[hh];
                        }

                        gw_Amount = 0.0;
                        gw_Amount_mWQ = 0.0;
                    } // > nHRU move to basinflow
                } // gwoutflow > 0.0
            } // for hhh


            // FROM RUNOFF and SSDRUNOFF ....(starts here)

            runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh];
            ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh];

            runinflow_mWQ_lay[Sub][hh] = soil_runoff_Buf_conc_lay[Sub][hh] * runinflow[hh];
            runcuminflow_mWQ_lay[Sub][hh] += runinflow_mWQ_lay[Sub][hh];
            runcumoutflow_mWQ_lay[Sub][hh] += runoutflow_mWQ_lay[Sub][hh];

            ssrinflow_mWQ_lay[Sub][hh] = soil_ssr_Buf_conc_lay[Sub][hh] * soil_ssr_Buf[hh] * hru_area[hh];
            ssrcuminflow_mWQ_lay[Sub][hh] += ssrinflow_mWQ_lay[Sub][hh];
            ssrcumoutflow_mWQ_lay[Sub][hh] += ssroutflow_mWQ_lay[Sub][hh];

            inflow[hh] = runoutflow[hh] + ssroutflow[hh]; // + gw_Amount; // add this HRU runoff and subsurface flow
            inflow_mWQ_lay[Sub][hh] = runoutflow_mWQ_lay[Sub][hh] + ssroutflow_mWQ_lay[Sub][hh]; // + Amount_mWQ; // add this HRU runoff and subsurface flow

            if (Sub == numsubstances - 1) {
                gwcuminflow[hh] += gwinflow[hh];
                runcuminflow[hh] += runinflow[hh];
                runcumoutflow[hh] += runoutflow[hh];
                ssrcuminflow[hh] += ssrinflow[hh];
                ssrcumoutflow[hh] += ssroutflow[hh];
                cuminflow[hh] += inflow[hh];
                cumoutflow[hh] += inflow[hh];
            }

            for (long hhh = 0; chkStruct(hhh); ++hhh) {

                Amount = 0.0;
                Amount_mWQ = 0.0;
                if ((whereto[hhh] - 1 == hh || whereto[hhh] == 0) && outflow[hhh] > 0.0) {
                    Amount = outflow[hhh] / hru_area[hh]; // outflow (mm*km^2/int)
                    Amount_mWQ = outflow_mWQ_lay[Sub][hhh] / hru_area[hh];
                    outflow[hhh] = 0.0;

                    if (Amount > minFlow_WQ)
                    {
                        outflow_diverted_conc_lay[Sub][hhh] += Amount_mWQ / Amount;
                    }
                    else
                    {
                        outflow_diverted_conc_lay[Sub][hhh] = 0.0f;
                    }
                        

                    if (Sub == numsubstances - 1)
                        outflow_diverted[hhh] += Amount;

                    if (whereto[hhh] - 1 == hh) {
                        if (preferential_flow[hhh]) {
                            gw_conc_lay[Sub][hh] = gw_conc_lay[Sub][hh] * gw[hh] + Amount_mWQ;
                            gw_conc_lay[Sub][hh] /= (gw[hh] + Amount);

                            if (Sub == numsubstances - 1) {
                                gw[hh] += Amount;
                                cum_preferential_flow_to_gw[hh] += Amount;
                            }

                            Amount = 0.0;
                            Amount_mWQ = 0.0;
                            break;
                        }
                        else {
                            if (!soil_rechr_ByPass[hh]) {
                                if (soil_rechr[hh] + Amount >= soil_rechr_max[hh]) { // units (mm*km^2/int)
                                    double Excess = soil_rechr[hh] + Amount - soil_rechr_max[hh];
                                    double Free = Amount - Excess;

                                    conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + Amount_mWQ * Free / (Amount);
                                    conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + Free);

                                    soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + Amount_mWQ * Free / Amount) / (soil_lower[hh] + soil_rechr[hh] + Free); // present mQW

                                    if (Sub == numsubstances - 1) {
                                        soil_rechr[hh] += Free;
                                        soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];
                                    }
                                    Amount_mWQ = Amount_mWQ * Excess / Amount;
                                    Amount = Excess;

                                }
                                else {
                                    if (soil_rechr[hh] + Amount > 0.0) {
                                        conc_soil_rechr_lay[Sub][hh] = conc_soil_rechr_lay[Sub][hh] * soil_rechr[hh] + Amount_mWQ;
                                        conc_soil_rechr_lay[Sub][hh] /= (soil_rechr[hh] + Amount);
                                    }
                                    else {
                                        conc_soil_rechr_lay[Sub][hh] = 0.0;
                                    }

                                    soil_moist_conc_lay[Sub][hh] = (conc_soil_lower_lay[Sub][hh] * soil_lower[hh] + conc_soil_rechr_lay[Sub][hh] * (soil_rechr[hh] + Amount_mWQ)) / (soil_lower[hh] + soil_rechr[hh] + Amount); // amount used

                                    if (Sub == numsubstances - 1) {
                                        soil_rechr[hh] = soil_rechr[hh] + Amount;
                                        soil_moist[hh] = soil_lower[hh] + soil_rechr[hh];
                                    }

                                    Amount = 0.0;
                                    Amount_mWQ = 0.0;
                                } // else
                            } // if !soil_rechr_ByPass
                            else if (!Sd_ByPass[hh] && Amount > 0.0) {
                                if (Sd[hh] + Amount >= Sdmax[hh]) { // units (mm*km^2/int)
                                    double Excess = Sd[hh] + Amount - Sdmax[hh];
                                    double Free = Amount - Excess;

                                    if ((Sd[hh] + Free) > minFlow_WQ) 
                                    {
                                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + Amount_mWQ * Free / Amount;
                                        Sd_conc_lay[Sub][hh] /= (Sd[hh] + Free);
                                    }

                                    if (Amount > minFlow_WQ) 
                                    {
                                        cum_to_Sd_mWQ_lay[Sub][hh] += Amount_mWQ * Free / Amount;
                                    }

                                        

                                    if (Sub == numsubstances - 1) {
                                        Sd[hh] += Free;
                                        cum_to_Sd[hh] += Amount;
                                    }

                                    Amount_mWQ = Sd_conc_lay[Sub][hh] * Excess;
                                    Amount = Excess;
                                }
                                else {
                                    if (Sd[hh] + Amount > 0.0) {
                                        Sd_conc_lay[Sub][hh] = Sd_conc_lay[Sub][hh] * Sd[hh] + Amount_mWQ;
                                        Sd_conc_lay[Sub][hh] /= (Sd[hh] + Amount);
                                    }
                                    else {
                                        Sd_conc_lay[Sub][hh] = 0.0;
                                    }

                                    if (Sub == numsubstances - 1) {
                                        Sd[hh] = Sd[hh] + Amount;
                                        cum_to_Sd[hh] += Amount;
                                    }

                                    Amount = 0.0;
                                    Amount_mWQ = 0.0;
                                } // else
                            } // if !Sd_ByPass
                        }

                        if ((redirected_residual[hh] + Amount * hru_area[hh]) > minFlow_WQ) { // handle excess
                            redirected_residual_conc_lay[Sub][hh] = redirected_residual_conc_lay[Sub][hh] * redirected_residual[hh] + Amount_mWQ * hru_area[hh];
                            redirected_residual_conc_lay[Sub][hh] /= (redirected_residual[hh] + Amount * hru_area[hh]);

                            if (Sub == numsubstances - 1)
                                redirected_residual[hh] += Amount * hru_area[hh];

                            Amount = 0.0;
                            Amount_mWQ = 0.0;
                            outflow[hhh] = 0.0;
                        }
                    } // whereto == hh
                    else if (whereto[hhh] == 0 && Amount > 0.0) { // move to basinflow
          //            outflow_diverted_conc_lay[Sub][hhh] += Amount_mWQ/Amount;

                        cumbasinflow_mWQ_lay[Sub][0] += Amount_mWQ;

                        basinflow_conc_lay[Sub][0] = basinflow_conc_lay[Sub][0] * basinflow[0] + Amount_mWQ * 1000;
                        if ((basinflow[0] + Amount * 1000) > minFlow_WQ)
                        {
                            basinflow_conc_lay[Sub][0] /= (basinflow[0] + Amount * 1000);
                        }
                        else 
                        {
                            basinflow_conc_lay[Sub][0] = 0;
                        }
                            


                        if (Sub == numsubstances - 1) {
                            basinflow[0] = Amount * 1000;
                            cumbasinflow[0] += basinflow[0];
                            cumoutflow[hh] += Amount * hru_area[hh];
                            outflow_diverted[hhh] += Amount;
                        }

                        Amount = 0.0;
                        Amount_mWQ = 0.0;
                    } // whereto == 0
                } // outflow > 0
            } // for hhh - distribution
        } // for jj accessing hh
    } // for Sub

    if (nstep == 0) { // end of every day
        if (soil_ssrDiv > 1) // daily value - ready for next day
            soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

        if (soil_runoffDiv > 1) // daily value - ready for next day
            soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

        if (soil_gwDiv > 1) // daily value - ready for next day
            soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
    } // end if

    if (variation == VARIATION_ORG) {
        Clark_hruDelay->DoClark(); // need to update for later HRUs
        for (long Sub = 0; Sub < numsubstances; ++Sub)
            Clark_hruDelay_mWQ[Sub]->DoClark(); // need to update for later HRUs
    }
    else if (variation == VARIATION_1) {
        hruDelay->DoMuskingum(); // need to update for later HRUs
        for (long Sub = 0; Sub < numsubstances; ++Sub)
            hruDelay_mWQ[Sub]->DoMuskingum(); // need to update for later HRUs
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

void ClassWQ_Netroute::finish(bool good) {


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

    string S = string("H2O");
    LogDebug(S.c_str());
    LogMessage(" ");

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        if (variation == VARIATION_ORG)
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), Clark_hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
        else
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow_diverted       (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");

        Total = cumoutflow[hh] + gwcumoutflow[hh] - cumbasinflow[hh] - cum_to_Sd[hh] - cum_to_soil_rechr[hh] - gwcumoutflow[hh]
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
    } // hh

    LogMessage(string("'" + Name + " (WQ_Netroute)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
    LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);

    LogMessage(string("'" + Name + " (WQ_Netroute)' Total (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total);
    LogDebug(" ");

    for (long Sub = 0; Sub < numsubstances; ++Sub) {

        string S = string("Substance# ") + to_string(Sub + 1);
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

        for (hh = 0; chkStruct(); ++hh) {
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cuminflow_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow_mWQ              (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cumoutflow_diverted_mWQ     (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            if (variation == VARIATION_ORG)
                LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), Clark_hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
            else
                LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcuminflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrcumoutflow_mWQ           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcuminflow_mWQ         (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runoffcumoutflow_mWQ        (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcuminflow_mWQ             (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow_diverted       (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwcumoutflow_diverted_mWQ   (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_Sd_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_to_soil_rechr_mWQ       (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' cum_redirected_residual_mWQ (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual_mWQ[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
            LogMessageA(hh, string("'" + Name + " (WQ_Netroute)' HRU_cumbasinflow_mwq        (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow_mWQ_lay[Sub][hh] / hru_area[hh], hru_area[hh], basin_area[0]);
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
        } // for hh

        LogMessage(string("'" + Name + " (WQ_Netroute)' cumbasinflow(m^3):           ").c_str(), cumbasinflow[0]);
        LogMessage(string("'" + Name + " (WQ_Netroute)' cumbasinflow_mWQ_lay(mg):    ").c_str(), cumbasinflow_mWQ_lay[Sub][0]);
        LogMessage(string("'" + Name + " (WQ_Netroute)' cumbasingw(m^3):             ").c_str(), cumbasingw[0]);
        LogMessage(string("'" + Name + " (WQ_Netroute)' cumbasingw_mWQ_lay(mg):      ").c_str(), cumbasingw_mWQ_lay[Sub][0]);
        LogMessage(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcuminflow_mWQ (mm*basin):          ").c_str(), Allgwcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflow_mWQ (mm*basin):         ").c_str(), Allgwcumoutflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allgwcumoutflowdiverted_mWQ (mm*basin): ").c_str(), Allgwcumoutflowdiverted_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcuminflow_mWQ (mm*basin):            ").c_str(), Allcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflow (mm*basin):               ").c_str(), Allcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allcumoutflowdiverted_mWQ (mm*basin):   ").c_str(), Allcumoutflowdiverted_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcuminflow_mWQ (mm*basin):         ").c_str(), Allssrcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allssrcumoutflow_mWQ (mm*basin):        ").c_str(), Allssrcumoutflow_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncuminflow_mWQ (mm*basin):         ").c_str(), Allruncuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allruncumoutflow_mWQ (mm*basin):        ").c_str(), Allruncumoutflow_mWQ);
        LogDebug(" ");

        LogMessage(string("'" + Name + " (WQ_Netroute)' AllSdcuminflow (mm*basin):              ").c_str(), AllSdcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' AllSdcuminflow_mWQ (mm*basin):          ").c_str(), AllSdcuminflow_mWQ);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allrechrcuminflow (mm*basin):           ").c_str(), Allrechrcuminflow);
        LogMessage(string("'" + Name + " (WQ_Netroute)' Allrechrcuminflow_mWQ (mm*basin):       ").c_str(), Allrechrcuminflow_mWQ);
        LogDebug(" ");
        LogMessage(string("'" + Name + " (WQ_Netroute)' AllTotal              (mm*basin):       ").c_str(), AllTotal);
        LogDebug(" ");
    } // for Sub

    LogDebug(" ");

    if (variation == VARIATION_ORG)
        delete[] Clark_hruDelay_mWQ;

    if (variation == VARIATION_1)
        delete[] hruDelay_mWQ;

    delete[] ssrDelay_mWQ;
    delete[] runDelay_mWQ;
    delete[] gwDelay_mWQ;

    delete ssrDelay;
    delete runDelay;
    delete gwDelay;
}


double ClassWQ_Netroute::Function1(double* I, long hh) {
    return runDelay->ChangeLag(I, hh);
}

double ClassWQ_Netroute::Function2(double* X, long hh) {
    return runDelay->ChangeStorage(X, hh);
}

void ClassWQ_Netroute::Reset_WQ(long hru, double* var, double** var_cWQ_lay) {
    var[hru] = 0.0;
    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        var_cWQ_lay[Sub][hru] = 0.0;
    }
}

void ClassWQ_Netroute::Set_WQ(const long hru, double* var, double* var_conc, double Amount, double amount_conc) {

    var[hru] = Amount;
    if (Amount > 0.0)
        var_conc[hru] = amount_conc;
    else
        var_conc[hru] = 0.0;
}

void ClassWQ_Netroute::copy_array(double* from, double* to) {
    for (hh = 0; chkStruct(); ++hh)
        to[hh] = from[hh];
}

void ClassWQ_Netroute::restore_hru(double* from, double* to, long hh) {
    to[hh] = from[hh];
}

void ClassWQ_Netroute::Restore(long hh) {

    restore_hru(gwoutflow_0, gwoutflow, hh);
    restore_hru(outflow_0, outflow, hh);
}

void ClassWQ_Netroute::Save() {

    copy_array(gwoutflow, gwoutflow_0);
    copy_array(outflow, outflow_0);
}