#include "ClassSoilPrairie.h"


ClassSoilPrairie* ClassSoilPrairie::klone(string name) const {
    return new ClassSoilPrairie(name);
}

void ClassSoilPrairie::decl(void) {

    Description = "'Handles soil moisture throughout the year.' \
                 'Parametric contibuting fraction model with Pond,'";

    if (Global::nlay < 2) {
        Global::nlay = 2;
        Global::maxlay = 2;
    }

    declvar("redirected_residual", TDim::NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

    declstatdiag("cum_redirected_residual", TDim::NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

    declvar("direct_rain", TDim::NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

    declstatvar("Sd", TDim::NHRU, "Depression storage.", "(mm)", &Sd);

    declstatvar("gw", TDim::NHRU, "ground water storage.", "(mm)", &gw);

    declstatvar("soil_rechr", TDim::NHRU, "moisture content of soil recharge zone, ie, the"//
        "portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

    declstatvar("soil_moist", TDim::NHRU, "moisture content of soil profile to the depth"//
        "of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

    decllocal("cum_hru_condense", TDim::NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

    declvar("soil_gw", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

    declvar("soil_gw_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

    declvar("gw_flow", TDim::NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

    declvar("gw_flow_D", TDim::NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

    declvar("infil_act", TDim::NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

    declvar("cum_infil_act", TDim::NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

    declvar("infil_act_D", TDim::NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

    declstatdiag("cum_gw_flow", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

    declvar("soil_ssr", TDim::NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

    declvar("rechr_ssr", TDim::NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

    declstatdiag("cum_soil_ssr", TDim::NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

    declstatdiag("cum_rechr_ssr", TDim::NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

    declvar("soil_ssr_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

    declvar("soil_runoff", TDim::NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

    declstatdiag("cum_soil_runoff", TDim::NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

    declvar("soil_runoff_D", TDim::NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

    declvar("Pond_water_frac", TDim::NHRU, "fraction of the maximum possible Sd HRU fraction that is under water.", "()", &Pond_water_frac);

    declvar("Small_Ponds_water_frac", TDim::NHRU, "fraction of the maximum possible Small_Ponds HRU fraction that is under water.", "()", &Small_Ponds_water_frac);

    decldiag("cum_runoff_to_Sd", TDim::NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

    decldiag("cum_soil_gw", TDim::NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);

    declvar("Sd_water_frac", TDim::NHRU, "fraction of the maximum possible Sd HRU fraction that is under water.", "()", &Sd_water_frac);

    declvar("Pond_water_frac", TDim::NHRU, "Fraction of the wetlands contributing water.", "()", &Pond_water_frac);

    declvar("Small_Ponds_water_frac", TDim::NHRU, "Small Ponds contrib fraction", "()", &Small_Ponds_water_frac);

    declvar("wetlands_evap", TDim::NHRU, "Depth of water evaporating from wetlands using Priestley-Taylor.", "(mm/int)", &wetlands_evap);

    declvar("Pond_evap", TDim::NHRU, "pond evaporation.", "(mm)", &Pond_evap);

    declvar("Pond_area", TDim::NHRU, "pond surface area.", "(mm^2)", &Pond_area);

    declvar("Pond_volume", TDim::NHRU, "pond volume.", "(mm^3)", &Pond_volume);

    declvar("Pond_s", TDim::NHRU, "link between the shape of the basin and A-h relation. p = 2 corresponds to a paraboloid basin and p = 10 a flat bottom.", "(mm^3)", &Pond_s);

    declvar("Pond_h", TDim::NHRU, "pond depth.", "(mm)", &Pond_h);

    declvar("Pond_hmax", TDim::NHRU, "pond maximum depth ", "(m)", &Pond_hmax);

    declvar("runoff_to_Pond", TDim::NHRU, "runoff to pond", "(mm)", &runoff_to_Pond);

    declvar("Small_Ponds_runoff_to_Pond", TDim::NHRU, "Small pond runoff to pond", "(mm)", &Small_Ponds_runoff_to_Pond);

    declvar("Small_Ponds_evap", TDim::NHRU, "Small pond evaporation.", "(mm)", &Small_Ponds_evap);

    declvar("Small_Ponds_area", TDim::NHRU, "pond surface area.", "(mm^2)", &Small_Ponds_area);

    declstatvar("Small_Ponds_Sd", TDim::NHRU, "Small Ponds depression storage.", "(mm)", &Small_Ponds_Sd);

    declvar("runoff_to_Small_Ponds", TDim::NHRU, "runoff to small ponds", "(mm)", &runoff_to_Small_Ponds);


    decllocal("snowinfil_buf", TDim::NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

    decllocal("runoff_buf", TDim::NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

    decllocal("meltrunoff_buf", TDim::NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

    decllocal("hru_evap_buf", TDim::NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

    decllocal("soil_moist_Init", TDim::NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

    decllocal("soil_rechr_Init", TDim::NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

    decllocal("Sd_Init", TDim::NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

    decllocal("gw_Init", TDim::NHRU, "initial ground water storage.", "(mm)", &gw_Init);


    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

    declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

    declparam("Sdinit", TDim::NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

    declparam("Small_Ponds_Sdmax", TDim::NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Small_Ponds_Sdmax);

    declparam("Small_Ponds_Sdinit", TDim::NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Small_Ponds_Sdinit);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

    declparam("soil_rechr_init", TDim::NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
        "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

    declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

    declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "5000.0",
        "Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

    declparam("Small_Ponds_area_max", TDim::NHRU, "3", "1e-6", "1e+09", "small pond maximum area.", "(km^2)", &Small_Ponds_area_max);

    declparam("Pond_area_max", TDim::NHRU, "3", "1e-6", "1e+09", "pond maximum area.", "(km^2)", &Pond_area_max);

    declparam("soil_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
        "that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

    declparam("gw_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

    declparam("gw_init", TDim::NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

    declparam("gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

    declparam("rechr_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

    declparam("lower_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

    declparam("Sd_ssr_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

    declparam("Sd_gw_K", TDim::NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

    declparam("Sd_water_frac_max", TDim::NHRU, "[0.24]", "0.0", "1.0", "Maximum fraction of the HRU area that can be water.", "()", &Sd_water_frac_max);

    declparam("evap_threshold", TDim::NHRU, "[10]", "0.0", "20.0", "Threshold evaporation necessary for setting the contribution fraction to zero.", "(mm)", &evap_threshold);

    declparam("soil_withdrawal", TDim::NDEFN, "[3]", "1", "4",
        "Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
        &soil_withdrawal, &soil_withdrawal_Tables, 2);

    declparam("cov_type", TDim::NHRU,
        "[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
        "0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

    declparam("transp_limited", TDim::NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

    declparam("soil_ssr_runoff", TDim::NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit.", "()", &inhibit_evap);

    declparam("Sd_normal", TDim::NHRU, "[0]", "0", "1", "inhibit pond handling of depressional storage", "()", &Sd_normal);

    declparam("Pond_contrib_frac", TDim::NHRU, "[0.0]", "0", "1", "Pond contrib fraction of basin", "()", &Pond_contrib_frac);

    declparam("Pond_p", TDim::NHRU, "[2]", ".1", "10", "link between the shape of the basin and A-h relation. p = 2 corresponds to a paraboloid basin and p = 10 a flat bottom", "()", &Pond_p);

    declparam("Pond_C1", TDim::NHRU, "[-0.254337]", "-1.0", "10", "coefficient 1 to calculate pond area from Sd/Sdmax", "()", &Pond_C1);

    declparam("Pond_C2", TDim::NHRU, "[1.22233]", "0.1", "10", "coefficient 2 to calculate pond area from Sd/Sdmax", "()", &Pond_C2);

    declparam("Pond_C3", TDim::NHRU, "[0.0261854]", "0.1", "10", "coefficient 3 to calculate pond area from Sd/Sdmax", "()", &Pond_C3);

    declparam("Small_Ponds_contrib_frac", TDim::NHRU, "[0.0]", "0", "1", "Small_Ponds contrib fraction of basin", "()", &Small_Ponds_contrib_frac);

    declparam("Small_Ponds_p", TDim::NHRU, "[2]", ".1", "10", "link between the shape of the basin and A-h relation. p = 2 corresponds to a paraboloid basin and p = 10 a flat bottom", "()", &Small_Ponds_p);

    declparam("Small_Ponds_C1", TDim::NHRU, "[-0.254337]", "-1.0", "10", "coefficient 1 to calculate small pond area from Sd/Sdmax", "()", &Small_Ponds_C1);

    declparam("Small_Ponds_C2", TDim::NHRU, "[1.22233]", "0.1", "10", "coefficient 2 to calculate small area from Sd/Sdmax", "()", &Small_Ponds_C2);

    declparam("Small_Ponds_C3", TDim::NHRU, "[0.0261854]", "0.1", "10", "coefficient 3 to calculate small area from Sd/Sdmax", "()", &Small_Ponds_C3);




    declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

    declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


    evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

    declgetvar("*", "hru_evap_PT", "(mm/int)", &hru_evap_PT);


    declgetvar("*", "infil", "(mm/int)", &infil);

    snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

    runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

    meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);
}

void ClassSoilPrairie::init(void) {

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

        Sd[hh] = Sdinit[hh];

        gw[hh] = gw_init[hh];

        hru_cum_actet[hh] = 0.0;
        cum_hru_condense[hh] = 0.0;
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
        cum_gw_flow[hh] = 0.0;

        cum_runoff_to_Sd[hh] = 0.0;
        cum_redirected_residual[hh] = 0.0;

        Pond_area[hh] = 0.0;
        Pond_evap[hh] = 0.0;
        Pond_h[hh] = 0.0;
        Pond_s[hh] = 0.0;
        Small_Ponds_area[hh] = 0.0;
        Small_Ponds_evap[hh] = 0.0;
        Small_Ponds_runoff_to_Pond[hh] = 0.0;
        Small_Ponds_Sd[hh] = Small_Ponds_Sdinit[hh];

        if (Sdmax[hh] > 0.0 && soil_moist_max[hh] > 0.0) { // Not all water
            calc_h_and_S(Sdmax[hh], Pond_area_max[hh], Pond_p[hh], Pond_h[hh], Pond_s[hh]);
            Pond_hmax[hh] = Pond_h[hh];
            Pond_calc_h_A(Pond_s[hh], Pond_p[hh], Sdmax[hh], Pond_h[hh], Pond_area[hh]);
        }

        if (Sdmax[hh] > 0.0 && soil_moist_max[hh] > 0.0) {
            if (Sdmax[hh] > 0.0)
                Pond_water_frac[hh] = Sd[hh] / Sdmax[hh];
            else
                Pond_water_frac[hh] = 0.0;

            if (Small_Ponds_Sdmax[hh] > 0.0)
                Small_Ponds_water_frac[hh] = Small_Ponds_Sd[hh] / Small_Ponds_Sdmax[hh];
            else
                Small_Ponds_water_frac[hh] = 0.0;
        }
    } // for hh
}

void ClassSoilPrairie::run(void) {

    double soil_lower, excs, condense;
    double et;

    long nstep = getstep();

    if (nstep == 1)
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
            soil_runoff_D[hh] = 0.0;
            soil_ssr_D[hh] = 0.0;
            soil_gw_D[hh] = 0.0;
            gw_flow_D[hh] = 0.0;
            infil_act_D[hh] = 0.0;
        }

        hru_actet[hh] = 0.0;
        infil_act[hh] = 0.0;
        soil_gw[hh] = 0.0;
        soil_ssr[hh] = 0.0;
        rechr_ssr[hh] = 0.0;
        wetlands_evap[hh] = 0.0;

        if (hru_evap_buf[hh] < 0.0) {
            condense = -hru_evap_buf[hh];
            cum_hru_condense[hh] += condense;
            hru_evap_buf[hh] = 0.0;
        }
        else
            condense = 0.0;

        // do direct precipitation on water

        //******Add infiltration to soil and compute excess

        if (soil_moist_max[hh] > 0.0) {
            soil_lower = soil_moist[hh] - soil_rechr[hh];

            double potential = infil[hh] + snowinfil_buf[hh] + condense;

            soil_rechr[hh] = soil_rechr[hh] + potential;

            if (soil_rechr[hh] > soil_rechr_max[hh]) {
                excs = soil_rechr[hh] - soil_rechr_max[hh];
                soil_rechr[hh] = soil_rechr_max[hh];
                soil_lower = soil_lower + excs;
            }

            soil_moist[hh] = soil_lower + soil_rechr[hh];

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
                if (soil_rechr_max[hh] > 0.0)
                    rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;

                if (rechr_ssr[hh] > soil_rechr[hh])
                    rechr_ssr[hh] = soil_rechr[hh];

                soil_rechr[hh] -= rechr_ssr[hh];
                if (soil_rechr[hh] < 0.0)
                    soil_rechr[hh] = 0.0;

                soil_moist[hh] -= rechr_ssr[hh];
                soil_ssr[hh] = rechr_ssr[hh];
                cum_rechr_ssr[hh] += rechr_ssr[hh];
            }

            double s2gw_k = soil_gw_K[hh] / Global::Freq;

            //  Handle excess to gw

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
                soil_ssr[hh] += excs;
                excs = 0.0;
            }
        }
        else { // soil_moist_max <= 0.0, i.e. Pond
            excs = infil[hh] + snowinfil_buf[hh] + condense;
        }

        runoff_to_Pond[hh] = 0.0; // (mm)
        runoff_to_Small_Ponds[hh] = 0.0; // (mm)
        Small_Ponds_runoff_to_Pond[hh] = 0.0; // (mm)
        Small_Ponds_evap[hh] = 0.0; // (mm)
        Pond_evap[hh] = 0.0; // (mm)

        soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs; // + (redirected_residual[hh] / hru_area[hh]);

    // use variable contributing areas for wetland HRUs

        if (soil_runoff[hh] > 0.0 || redirected_residual[hh] > 0.0) {

            if (Sd_normal[hh] == 0 && soil_runoff[hh] > 0.0) {

                // Handle the small ponds

                runoff_to_Small_Ponds[hh] = soil_runoff[hh] * Small_Ponds_contrib_frac[hh];
                runoff_to_Pond[hh] = soil_runoff[hh] * Pond_contrib_frac[hh];
                soil_runoff[hh] -= (runoff_to_Pond[hh] + runoff_to_Small_Ponds[hh]);

                if (Small_Ponds_Sd[hh] + runoff_to_Small_Ponds[hh] > Small_Ponds_Sdmax[hh]) {
                    runoff_to_Pond[hh] += (Small_Ponds_Sd[hh] + runoff_to_Small_Ponds[hh] - Small_Ponds_Sdmax[hh]);
                }
                else
                    Small_Ponds_Sd[hh] += runoff_to_Small_Ponds[hh];

                Small_Ponds_Sd[hh] += runoff_to_Small_Ponds[hh];

                Small_Ponds_runoff_to_Pond[hh] = Small_Ponds_runoff_frac(Small_Ponds_Sd[hh] / Small_Ponds_Sdmax[hh], hh) * Small_Ponds_Sd[hh];

                runoff_to_Pond[hh] += Small_Ponds_runoff_to_Pond[hh];

                Small_Ponds_Sd[hh] -= Small_Ponds_runoff_to_Pond[hh];

                // Handle the large pond

                if (redirected_residual[hh] + runoff_to_Pond[hh] > 0.0) {
                    if (Sd[hh] + runoff_to_Pond[hh] + redirected_residual[hh] > Sdmax[hh]) {
                        soil_runoff[hh] += (Sd[hh] + runoff_to_Pond[hh] + redirected_residual[hh] - Sdmax[hh]);
                    }
                    else
                        Sd[hh] += runoff_to_Pond[hh] + redirected_residual[hh];

                    redirected_residual[hh] = 0.0;

                    Pond_calc_h_A(Sd[hh], Pond_s[hh], Pond_p[hh], Pond_h[hh], Pond_area[hh]);

                }
            }
            else { // do not use small/large pond
                soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + (redirected_residual[hh] / hru_area[hh]);
                redirected_residual[hh] = 0.0;
            }
        }
        else { // handle Pond evaporation

            if (Small_Ponds_Sd[hh] > 0.0) {
                Small_Ponds_water_frac[hh] = Small_Ponds_area_frac(Small_Ponds_Sd[hh] / Small_Ponds_Sdmax[hh], hh);
                Small_Ponds_evap[hh] = Small_Ponds_water_frac[hh] * hru_evap_PT[hh];
                if (Small_Ponds_evap[hh] > Small_Ponds_Sd[hh])
                    Small_Ponds_evap[hh] = Small_Ponds_Sd[hh];

                wetlands_evap[hh] = Small_Ponds_evap[hh];

                Small_Ponds_water_frac[hh] = Small_Ponds_area_frac(Small_Ponds_Sd[hh] / Small_Ponds_Sdmax[hh], hh);

                Small_Ponds_Sd[hh] -= Small_Ponds_evap[hh];
            }

            if (Sd[hh] > 0.0) {
                Pond_water_frac[hh] = Pond_area_frac(Sd[hh] / Sdmax[hh], hh);
                Pond_evap[hh] = Pond_water_frac[hh] * hru_evap_PT[hh];
                if (Pond_evap[hh] > Sd[hh])
                    Pond_evap[hh] = Sd[hh];


                wetlands_evap[hh] += Pond_evap[hh];

                Sd[hh] -= Pond_evap[hh];
            }
        }

        cum_redirected_residual[hh] += (redirected_residual[hh] / hru_area[hh]);
        redirected_residual[hh] = 0;
        soil_runoff_D[hh] += soil_runoff[hh];
        cum_soil_runoff[hh] += soil_runoff[hh];
        cum_runoff_to_Sd[hh] += runoff_to_Pond[hh];

        if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
            double Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
            if (Sd2gw_k > Sd[hh])
                Sd2gw_k = Sd[hh];
            soil_gw[hh] += Sd2gw_k;
            Sd[hh] -= Sd2gw_k;
            if (Sd[hh] < 0.0)
                Sd[hh] = 0.0;
        }

        soil_gw_D[hh] += soil_gw[hh];
        cum_soil_gw[hh] += soil_gw[hh];

        gw[hh] += soil_gw[hh];
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
            double Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq;
            if (Sd2ssr_k >= Sd[hh])
                Sd2ssr_k = Sd[hh];
            soil_ssr[hh] += Sd2ssr_k;
            Sd[hh] -= Sd2ssr_k;
            if (Sd[hh] < 0.0)
                Sd[hh] = 0.0;
        }

        double s2ssr_k = lower_ssr_K[hh] / Global::Freq;
        if (s2ssr_k > 0.0) {
            double avail = soil_moist[hh] - soil_rechr[hh];
            if (s2ssr_k >= avail)
                s2ssr_k = avail;
            soil_moist[hh] -= s2ssr_k;
            soil_ssr[hh] += s2ssr_k;
        }

        cum_soil_ssr[hh] += soil_ssr[hh];
        soil_ssr_D[hh] += soil_ssr[hh];

        //   ***Compute actual evapotranspiration

        double avail_evap = hru_evap_buf[hh] * (1.0 - (Pond_water_frac[hh] + Small_Ponds_water_frac[hh])); // N.B. Pond and Small_Ponds handled earlier with "wetlands_evap" variable.

        if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

            double pctl, pctr, etl, etr;
            //double ets; varible is unreferenced commenting out for now - jhs507

            if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
                pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
            else
                pctl = 0.0;

            if (soil_rechr_max[hh] > 0.0)
                pctr = soil_rechr[hh] / soil_rechr_max[hh];
            else
                pctr = 0.0;
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

        } // soil_moist[hh] > 0.0  wetlands_evap

        if (wetlands_evap[hh] > 0.0) //  Pond and Small_Ponds evaporation
            hru_actet[hh] = wetlands_evap[hh]; // evaporate all

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
    } // for
}

void ClassSoilPrairie::finish(bool good) {

    double Allcum_soil_runoff = 0.0;
    double Allcum_soil_ssr = 0.0;
    double Allcum_rechr_ssr = 0.0;
    double Allcum_soil_gw = 0.0;
    double Allcum_gw_flow = 0.0;
    double Allcum_infil_act = 0.0;
    double Allcum_soil_moist_change = 0.0;
    double Allcum_Sd_change = 0.0;
    double Allcum_gw_change = 0.0;

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
        LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
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
    } // hh

    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
    LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
    LogDebug(" ");
}

double ClassSoilPrairie::Pond_area_frac(const double area_frac, const long hh) {

    // calculates maximum water area fraction from water volume fraction using simple scaling curve

    double ZZ = Pond_C1[hh] * sqr(area_frac) + Pond_C2[hh] * area_frac + Pond_C3[hh]; // area_frac

    if (ZZ < 0.0)
        ZZ = 0.0;
    else if (ZZ > 1.0)
        ZZ = 1.0;

    return ZZ;
}

double ClassSoilPrairie::Small_Ponds_area_frac(const double area_frac, const long hh) {

    // calculates maximum water area fraction from water volume fraction using simple scaling curve

    double ZZ = Small_Ponds_C1[hh] * sqr(area_frac) + Small_Ponds_C2[hh] * area_frac + Small_Ponds_C3[hh]; // area_frac

    if (ZZ < 0.0)
        ZZ = 0.0;
    else if (ZZ > 1.0)
        ZZ = 1.0;

    return ZZ;
}

double ClassSoilPrairie::Small_Ponds_runoff_frac(const double Sd_Sdmax, const long hh) {

    // calculates maximum water area fraction from water volume fraction using simple scaling curve

    double ZZ = Sd_Sdmax; // area_frac

    if (ZZ < 0.0)
        ZZ = 0.0;
    else if (ZZ > 1.0)
        ZZ = 1.0;

    return ZZ;
}

void ClassSoilPrairie::Pond_calc_h_A(const double volume, const double s, const double p, double& h, double& area) {

    // calculate current depth & area from s, p, maxarea and desired volume

    h = pow((volume * (1.0 + 2.0 / p) / s), (1.0 / (1.0 + 2.0 / p)));

    area = s * pow(h, 2.0 / p);

} // end  Pond_calc_h_A

void ClassSoilPrairie::calc_h_and_S(const double maxvolume, const double maxarea, const double pval, double& S, double& h) {

    const double maxerror = 0.000001;
    const double  maxiterations = 100;

    double est_area, area_error;
    long iterations;
    long done;
    // does iterative calculations to find h and S
    h = 1.0;
    done = false;
    iterations = 0;
    while (!done) {
        S = maxarea / pow(h, (2.0 / pval));
        h = pow(maxvolume * (1.0 + 2.0 / pval) / S, 1.0 / (1.0 + 2.0 / pval));
        est_area = S * pow(h, (2.0 / pval));
        area_error = fabs(est_area - maxarea) / maxarea;

        if ((area_error < maxerror) || (iterations > maxiterations))
            done = true;
        else
            iterations = iterations + 1;
    }
} // calc_h_and_S