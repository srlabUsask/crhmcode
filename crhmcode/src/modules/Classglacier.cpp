//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "Classglacier.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

Classglacier* Classglacier::klone(string name) const {
    return new Classglacier(name);
}

void Classglacier::decl(void) {

    Description = "'Energy-budget glacier model', \
                 'glacier using Brunt et al', \
                 'glacier using input variable Qnsn_Var (W/m^2*int) from CanopyClearing etc.', \
                 'glacier using input observation Qnsn (W/m^2*int)', \
                 'glacier using input observation QnD (MJ/m^2*d)', \
                 'glacier using input variable Xmelt ()'";

    variation_set = VARIATION_ORG;

    declvar("SWEmelt", TDim::NHRU, "daily SWE snowmelt", "(mm/d)", &SWEmelt);

    declvar("SWEmelt_delayed", TDim::NHRU, "daily SWE snowmelt delayed", "(mm/d)", &SWEmelt_delayed);

    declstatdiag("cumSWEmelt", TDim::NHRU, "cumulative SWE snowmelt", "(mm)", &cumSWEmelt);

    declvar("firnmelt", TDim::NHRU, "daily firn melt", "(mm/d)", &firnmelt);

    declvar("firnmelt_delayed", TDim::NHRU, "daily firn melt delayed", "(mm/d)", &firnmelt_delayed);

    declstatdiag("cumfirnmelt", TDim::NHRU, "cumulative firn melt", "(mm)", &cumfirnmelt);

    declvar("icemelt", TDim::NHRU, "daily ice melt", "(mm/d)", &icemelt);

    declvar("icemelt_delayed", TDim::NHRU, "daily ice melt delayed", "(mm/d)", &icemelt_delayed);

    declstatdiag("cumicemelt", TDim::NHRU, "cumulative ice melt", "(mm)", &cumicemelt);

    declstatvar("firn_dens", TDim::NDEFN, "densities of firn layers", "(kg/m^3)", &firn_dens, &firn_dens_array, Global::nlay);

    declstatvar("firn_h", TDim::NDEFN, "depths of firn layers", "(m)", &firn_h, &firn_h_array, Global::nlay);

    declstatvar("firn_yr", TDim::NDEFN, "layer[1] - years to 'critical density' and layer[2, ...] age of firn", "(yr)", &firn_yr, &firn_yr_array, Global::nlay);

    decldiagparam("firn_dens_init", TDim::NDEFN, "[220.0]", "0.0", "1000.0", "initial densities of firn densification layers", "(kg/m^3)", &firn_dens_init, &firn_dens_array_init, Global::nlay);

    decldiagparam("firn_h_init", TDim::NDEFN, "[0.0]", "0.0", "100.0", "initial depths of firn densification layers", "(m)", &firn_h_init, &firn_h_array_init, Global::nlay);


    declstatvar("ice", TDim::NHRU, "water equivalent of ice", "(mm)", &ice);

    declstatvar("firn", TDim::NHRU, "water equivalent of all firn layers", "(mm)", &firn);

    declvar("glacier_Albedo", TDim::NHRU, "Albedo used by glacier. From an albedo module unless overwritten by an albedo observation", "()", &glacier_Albedo);

    declvar("glacier_h2o", TDim::NHRU, "water equivalent of SWE, firn layers and ice", "(mm)", &glacier_h2o);

    declvar("glacier_depth", TDim::NHRU, "depth of glacier", "(m)", &glacier_depth);

    declvar("glacier_Surf", TDim::NHRU, "surface elevation of glacier (SWE, firn layers, ice and optionally land elevation)", "(m)", &glacier_Surf);

    declstatvar("firn_depth", TDim::NHRU, "depth of all firn layers", "(m)", &firn_depth);

    declvar("firn_init", TDim::NHRU, "initial water equivalent of all firn layers", "(mm)", &firn_init);

    declstatvar("nfirn", TDim::NHRU, "num of layers used in firn consolidation array", "()", &nfirn);

    decllocal("topo_elev", TDim::NHRU, "topography elevations below glacier", "(m)", &topo_elev);

    decllocal("rho_snow", TDim::NHRU, "rho of snow moved to furn", "(kg/m^3)", &rho_snow);

    declvar("Gmelt", TDim::NHRU, "Qmelt = Qn+Qh+Qe+Qp/316.8*1000.0", "(mm/d)", &Qmelt);

    decllocal("cumGmelt", TDim::NHRU, "cumulative Qmelt = Qn+Qh+Qe+Qp/316.8*1000.0", "(mm)", &cumQmelt);

    decllocal("cumnet_rain_glacier", TDim::NHRU, "cumulative net_rain + firn and ice melt", "(mm)", &cumnet_rain_glacier);

    decllocal("cumsnowmeltD_glacier", TDim::NHRU, "cumulative snowmeltD + firn and ice melt", "(mm)", &cumsnowmeltD_glacier);

    decldiag("Gn_ebsm", TDim::NHRU, "net radiation", "(MJ/d)", &Qn_ebsm);

    decldiag("Gh_ebsm", TDim::NHRU, "sensible heat", "(MJ/d)", &Qh_ebsm);

    decldiag("Ge_ebsm", TDim::NHRU, "latent heat", "(MJ/d)", &Qe_ebsm);

    decldiag("Gp_ebsm", TDim::NHRU, "input from rainfall", "(MJ/d)", &Qp_ebsm);

    decldiag("GlacierMode", TDim::NHRU, "1 - glacier, 0 - tongue (no firn or ice", "()", &GlacierMode);


    decldiag("SWE_2firn", TDim::NHRU, "end of summer SWE transferred to firn", "(mm)", &SWE_2firn);

    decldiag("SWE_2firn_dens", TDim::NHRU, "end of summer density of SWE transferred to firn", "(kg/m^3)", &SWE_2firn_dens);

    declstatdiag("cumSWE_2firn", TDim::NHRU, "cumulative SWE added to firn", "(mm)", &cumSWE_2firn);

    decldiag("firn_2ice", TDim::NHRU, "end of summer firn transferred to ice", "(mm)", &firn_2ice);

    decldiag("firn_2ice_dens", TDim::NHRU, "end of summer density of firn transferred to ice.", "(kg/m^3)", &firn_2ice_dens);

    declstatdiag("cumfirn_2ice", TDim::NHRU, "cumulative firn added to ice", "(mm)", &cumfirn_2ice);

    declvar("Gnet_rainD", TDim::NHRU, "daily net rain calculated from net_rain", "(mm/d)", &Gnet_rainD);

    declvar("net_rain_org", TDim::NHRU, "value of 'net_rain' before addition of SWE, firn and ice melt", "(mm/int)", &net_rain_org);

    declvar("cumnet_rain_org", TDim::NHRU, "cumulative value of 'net_rain' before addition of SWE, firn and ice melt", "(mm)", &cumnet_rain_org);


    ObsCnt_Albedo = declreadobs("glacier_Albedo_obs", TDim::NHRU, "available Albedo observations", "()", &glacier_Albedo_obs, HRU_OBS_misc, true); // HRU_OBS_p_ppt HRU_OBS_misc HRU_OBS_Q HRU_OBS_u HRU_OBS_t_rh_ea


    decldiagparam("delay_melt", TDim::NHRU, "[0]", "0", "366", "inhibit melt until this Julian date. Default incorrect for the Southern Hemisphere", "()", &delay_melt);

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("ice_init", TDim::NHRU, "[1.0]", "0.0", "1.0E6", "Initial water equivalent of glacier ice", "(mm)", &ice_init);

    declparam("firn_Albedo", TDim::NHRU, "[187.0]", "0.2", "0.9", "Initial glacier firn albedo", "()", &firn_Albedo);

    declparam("ice_Albedo", TDim::NHRU, "[187.0]", "0.2", "0.9", "Initial glacier ice albedo", "()", &ice_Albedo);

    declparam("ice_dens", TDim::NHRU, "[1000.0]", "200.0", "1000.0", "density of glacier ice", "(kg/m^3)", &ice_dens);

    declparam("TKMA", TDim::NHRU, "[30]", "-50", "50", "Mean annual temperature of glacier", "(" + string(DEGREE_CELSIUS) + ")", &TKMA);

    declparam("SWEAA", TDim::NHRU, "[0.3]", "0.1", "10.0", "Mean annual accumulation of glacier SWE", "(m/yr)", &SWEAA);

    declparam("SWEstorage", TDim::NHRU, "[0.0]", "0.0", "200.0", "snowmelt storage constant", "(d)", &SWEstorage);

    declparam("SWELag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "snowmelt  lag delay", "(h)", &SWELag);

    declparam("topo_elev_init", TDim::NHRU, "[0]", "0", "1000", "elevation used to initialise 'topo_elev' when 'Elev_Adj_glacier_surf equals 0.0'", "(m)", &topo_elev_init);

    declparam("Elev_Adj_glacier_surf", TDim::NHRU, "[0]", "0", "1", " 0 - glacier_Surf (m) = glacier depth, 1 - glacier_Surf = glacier depth + land elevation", "()", &Elev_Adj_glacier_surf);

    declparam("firnstorage", TDim::NHRU, "[0.1]", "0.0", "200.0", "firn storage constant", "(d)", &firnstorage);

    declparam("firnLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "firn  lag delay", "(h)", &firnLag);

    declparam("icestorage", TDim::NHRU, "[0.1]", "0.0", "200.0", "ice melt storage constant", "(d)", &icestorage);

    declparam("iceLag", TDim::NHRU, "[0.0]", "0.0", "1.0E4.0", "ice melt lag delay", "(h)", &iceLag);

    declparam("SWE_to_firn_Julian", TDim::NHRU, "[244]", "0", "366", "convert any SWE to firn on Julian day. 0 - inhibit transfer", "()", &SWE_to_firn_Julian);

    declparam("Densification", TDim::NHRU, "[0]", "0", "1", ". Densification method: 0 - simple linear, 1 - original", "()", &Densification);

    declparam("Densification_550", TDim::NHRU, "[100]", "0", "1000", ". Densification increment < 550", "()", &Densification_550);

    declparam("Densification_above_550", TDim::NHRU, "[100]", "0", "1000", ". Densification increment >= 550", "()", &Densification_above_550);

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

    declparam("inhibit_firnmelt", TDim::NHRU, "[0]", "0", "1", "set to 1 to inhibit firn melt", "()", &inhibit_firnmelt);

    declparam("inhibit_icenmelt", TDim::NHRU, "[0]", "0", "1", "set to 1 to inhibit firn melt", "()", &inhibit_icemelt);

    declgetvar("*", "SunMax", "(h)", &sunmax);
    declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
    declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
    declgetvar("*", "hru_tmean", "(" + string(DEGREE_CELSIUS) + ")", &tmean);
    declgetvar("*", "hru_tmax", "(" + string(DEGREE_CELSIUS) + ")", &tmax);
    declgetvar("*", "hru_tmin", "(" + string(DEGREE_CELSIUS) + ")", &tmin);
    declgetvar("*", "hru_umean", "(m/s)", &umean);
    declgetvar("*", "hru_rhmean", "(%)", &rhmean);
    declgetvar("*", "hru_SunAct", "(h)", &sunact);
    declputvar("*", "SWE", "(mm)", &SWE);
    declputvar("*", "net_rain", "(mm/int)", &net_rain);
    declputvar("*", "snowmeltD", "(mm/d)", &snowmeltD);

    declputparam("*", "hru_elev", "(m)", &hru_elev);
    declputvar("*", "Pa", "(kPa)", &Pa);
    declputvar("*", "Albedo", "()", &Albedo);

    // debris-cover melt, Debris Enhanced Temperature-Index (DETI) model by Carenzo et al (2016), added on 16 June 2020
    declvar("lagT", TDim::NHRU, "lagged temperature accounting for the energy transfer through the debris layers", "(" + string(DEGREE_CELSIUS) + ")", &lagT);
    declvar("lagSW", TDim::NHRU, "lagged shortwave radiation accounting for the energy transfer through the debris layers", "(W/m^2)", &lagSW);
    declvar("TF", TDim::NHRU, "temperature factor for the energy transfer through the debris layers", "(mm h^-1 " + string(DEGREE_CELSIUS) + "^-1)", &TF);
    declvar("SRF", TDim::NHRU, "shortwave radiation factor for the energy transfer through the debris layers", "(m2 mm W^-1 h^-1 )", &SRF);
    declvar("Xdebris_melt_hrly", TDim::NHRU, "Experimental Firn and Ice melt under debris-cover at hourly timestep", "(mm/h)", &Xdebris_melt_hrly);
    declvar("Xdebris_melt_acc", TDim::NHRU, "Experimental Firn and Ice melt under debris-cover daily accumulator", "(mm/d)", &Xdebris_melt_acc);
    declvar("lagT_used", TDim::NHRU, "lagged air temperature used for debris delays otherwise zero.", "(" + string(DEGREE_CELSIUS) + ")", &lagT_used); // added 2 July 2020
    declvar("lagSW_used", TDim::NHRU, "lagged incoming shortwave radiation used for debris delays otherwise zero.", "(W/m^2)", &lagSW_used); // added 2 July 2020
    declparam("debris_h", TDim::NHRU, "[0.0]", "0.0", "10.0", "debris thickness", "(m)", &debris_h);
    declparam("T_threshold", TDim::NHRU, "[1.0]", "-30.0", "30.0", "threshold temperature above which melt is assumed to occur", "(" + string(DEGREE_CELSIUS) + ")", &T_threshold);
    declparam("use_debris", TDim::NHRU, "[0]", "0", "1", "0 - clean glacier melt, 1 - use debris-cover melt", "(" + string(DEGREE_CELSIUS) + ")", &use_debris);
    declgetvar("*", "Qsisn_Var", "(W/m^2*int)", &Qsisn_Var); // incident short-wave at surface, interval value
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);

    variation_set = VARIATION_0;

    decldiagparam("tfactor", TDim::NHRU, "[0.0]", "0.0", "10.0", "degree day melt factor", "(mm/d*" + string(DEGREE_CELSIUS) + ")", &tfactor);

    decldiagparam("nfactor", TDim::NHRU, "[0.0]", "0.0", "10.0", "net radiation factor (typical value 3.0(mm*m^2/MJ*d))", "(mm*m^2/MJ)", &nfactor);

    decldiagparam("Use_QnD", TDim::NHRU, "[0]", "0", "1", "1 - Use QnD if available", "()", &Use_QnD);


    variation_set = VARIATION_0 + VARIATION_3;

    declreadobs("QnD", TDim::NHRU, "net radiation", "(MJ/m^2*d)", &QnD, HRU_OBS_Q, true); // must check for NULL


    variation_set = VARIATION_1 + VARIATION_2;

    declstatvar("Qnsn_Acc", TDim::NHRU, "accumulator for Qnsn_Var/Qnsn", "(W/m^2)", &Qnsn_Acc); // daily value


    variation_set = VARIATION_1 + VARIATION_5; // katabatic parameterization, added on 15 June 2020;

    declgetvar("*", "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var); // interval value


    variation_set = VARIATION_2;

    declreadobs("Qnsn", TDim::NHRU, "net radiation", "(W/m^2*int)", &Qnsn, HRU_OBS_Q);

    variation_set = VARIATION_4;

    declgetvar("*", "Xmelt", "(mm/d)", &Xmelt); // interval value

    variation_set = VARIATION_5; // katabatic parameterization, added on 15 June 2020

    declvar("den_air", TDim::NHRU, "air density.", "(kg/m^-3)", &den_air);

    declvar("K_kat", TDim::NHRU, "katabatic bulk exchange coefficient.", "()", &K_kat);

    declvar("Cp_water", TDim::NHRU, "specific heat of water.", "(J/(kg*K))", &Cp_water);

    declvar("Xmelt_int", TDim::NHRU, "Experimental Firn and Ice melt at interval timestep", "(mm/int)", &Xmelt_int);

    declvar("Xmelt_acc", TDim::NHRU, "Experimental Firn and Ice melt daily accumulator", "(mm/d)", &Xmelt_acc);

    declvar("Qn_kata", TDim::NHRU, "net radiation", "(W/m^2)", &Qn_kata);

    declvar("Qh_kata", TDim::NHRU, "sensible heat flux using katabatic parameterization", "(W/m^2)", &Qh_kata);

    declvar("Qe_kata", TDim::NHRU, "latent heat flux using katabatic parameterization", "(W/m^2)", &Qe_kata);

    declvar("Qp_kata", TDim::NHRU, "advective flux from rainfall", "(W/m^2)", &Qp_kata);

    declvar("Qmelt_kata", TDim::NHRU, "Energy available for glacier melt", "(W/m^2)", &Qmelt_kata);

    declparam("katabatic_lapse_rate", TDim::NHRU, "[0.005]", "0", "2", "lapse rate for katabatic turbulent transfer calculation", "(" + string(DEGREE_CELSIUS) + "/100m)", &katabatic_lapse_rate);

    declgetvar("*", "T_rain", "("+string(DEGREE_CELSIUS)+")", &T_rain);

    declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

    variation_set = VARIATION_ORG;
}

void Classglacier::init(void) {

    nhru = getdim(TDim::NHRU);
    nlay = getdim(TDim::NLAY);

    if (nlay < 3) {
        string S = string("'") + Name + " (glacier)' project file nlay(number of layers) must be greater than 2";
        CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
        LogError(TExcept);
        throw TExcept;
    }

    if (ObsCnt_Albedo > -1) {
        CRHMException TExcept("Handling glacier albedo from 'glacier_Albedo_obs' observation input.", TExcept::WARNING);
        LogError(TExcept);
    }

    for (hh = 0; hh < nhru; ++hh) {

        ice[hh] = ice_init[hh]; // (mm)

        cumSWE_2firn[hh] = 0.0;
        cumfirn_2ice[hh] = 0.0;
        cumfirnmelt[hh] = 0.0;
        cumicemelt[hh] = 0.0;
        cumQmelt[hh] = 0.0;
        cumnet_rain_glacier[hh] = 0.0;
        cumsnowmeltD_glacier[hh] = 0.0;
        cumSWEmelt[hh] = 0.0;
        cumnet_rain_org[hh] = 0.0;
        rho_snow[hh] = 0.0;

        firn_init[hh] = 0.0;
        firn_depth[hh] = 0.0;
        SWE_2firn[hh] = 0.0;
        SWE_2firn_dens[hh] = 0.0;
        firn_2ice[hh] = 0.0;
        firn_2ice_dens[hh] = 0.0;
        firn[hh] = 0.0;
        nfirn[hh] = 0;
        GlacierMode[hh] = 1;
        glacier_h2o[hh] = 0.0;
        glacier_Albedo[hh] = 0.0;

        bool end_para = false;
        bool Warned = false;

        for (long ll = 0; ll < nlay; ++ll) {
            firn_yr_array[ll][hh] = 0.0;
            firn_h_array[ll][hh] = 0.0;
            firn_dens_array[ll][hh] = 0.0;

            if (firn_h_array_init[ll][hh] > 0.0) {
                if (end_para && !Warned) {
                    string S = string("'") + Name + " (glacier)' firn initialisation parameters not contiguous in hru = " + to_string(hh + 1).c_str();
                    CRHMException TExcept(S.c_str(), TExcept::WARNING);
                    LogError(TExcept);
                    Warned = true;
                }
                else if (!end_para)
                    ++nfirn[hh];

                firn_h_array[ll][hh] = firn_h_array_init[ll][hh] * 1000.0; // (m) to (mm)
                firn_dens_array[ll][hh] = firn_dens_array_init[ll][hh];
                firn_init[hh] += firn_h_array[ll][hh] * firn_dens_array[ll][hh] / 1000.0; // (mm)
                firn_depth[hh] += firn_h_array[ll][hh]; // (mm)

                firn[hh] += firn_h_array[ll][hh] * firn_dens_array[ll][hh] / 1000.0; // (mm)
            }
            else
                end_para = true;
        } // for nlay

        if (nfirn[hh] > nlay) { // nfirm always less than nlay
            string S = string("'") + Name + " (glacier)' global 'nlay'(" + to_string(nlay).c_str() + ") must be greater than number of firn layers (" + to_string(nfirn[hh]).c_str() + ") in hru = " + to_string(hh + 1).c_str();
            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
            LogError(TExcept);
        }

        if (Elev_Adj_glacier_surf[hh]) // add glacier depth(m) to physical depth
            topo_elev[hh] = hru_elev[hh] - (firn_depth[hh] / 1000.0 + ice[hh] / ice_dens[hh]); // m
        else
            topo_elev[hh] = topo_elev_init[hh];

        Qmelt[hh] = 0.0;
        Qn_ebsm[hh] = 0.0;
        Qh_ebsm[hh] = 0.0;
        Qe_ebsm[hh] = 0.0;
        Qp_ebsm[hh] = 0.0;

        lagT[hh] = 0.0;
        lagSW[hh] = 0.0;
        TF[hh] = 0.0;
        SRF[hh] = 0.0;
        Xdebris_melt_hrly[hh] = 0.0;
        Xdebris_melt_acc[hh] = 0.0;
        lagT_used[hh] = 0.0;
        lagSW_used[hh] = 0.0;

        if (variation == VARIATION_5) {
            den_air[hh] = 0.0;
            K_kat[hh] = 0.0;
            Cp_water[hh] = 0.0;
            Xmelt_int[hh] = 0.0;
            Xmelt_acc[hh] = 0.0;
            Qn_kata[hh] = 0.0;
            Qh_kata[hh] = 0.0;
            Qe_kata[hh] = 0.0;
            Qp_kata[hh] = 0.0;
            Qmelt_kata[hh] = 0.0;
        } // VARIATION_5

        if (variation == VARIATION_ORG) {
            if (nfactor[hh] != 0.0 && QnD == NULL) {
                CRHMException TExcept("ebsm: nfactor > 0.0 with observation 'QnD' not defined!", TExcept::TERMINATE);
                LogError(TExcept);
            }
        }
    } // for nhru

    SWEDelay = new ClassClark(SWEmelt, SWEmelt_delayed, SWEstorage, SWELag, nhru);
    firnDelay = new ClassClark(firnmelt, firnmelt_delayed, firnstorage, firnLag, nhru);
    iceDelay = new ClassClark(icemelt, icemelt_delayed, icestorage, iceLag, nhru);
}

void Classglacier::run(void) {

    long nstep;
    double rho;
    //double umin; variable is unreferenced commenting out for now - jhs507
    //double ref; variable is unreferenced commenting out for now - jhs507

    nstep = getstep();

    if (nstep == 1) { // must be here after 'hru_elev' parameter has been backed up
        for (hh = 0; hh < nhru; ++hh) {
            glacier_h2o[hh] = SWE[hh] + firn[hh] + ice[hh]; // water equivalent(mm)
            glacier_depth[hh] = (Common::DepthofSnow(SWE[hh]) + firn_depth[hh]) / 1000.0 + ice[hh] / ice_dens[hh]; // (m) thickness
            glacier_Surf[hh] = glacier_depth[hh] + topo_elev[hh]; // (m)

            Pa[hh] = 101.3f * pow((293.0f - 0.0065f * glacier_Surf[hh]) / 293.0f, 5.26f);  // (kPa)
        }
    }

    nstep = nstep % Global::Freq;

    for (hh = 0; chkStruct(); ++hh) {

        firn[hh] = 0.0;

        for (long nn = 0; nn < nfirn[hh]; ++nn)
            firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // (mm)

        if (firn[hh] <= 0.0 && ice[hh] <= 0.0) // treat as soil
            GlacierMode[hh] = 0;
        else {
            GlacierMode[hh] = 1;

            if (ObsCnt_Albedo >= hh) {
                if (glacier_Albedo_obs[hh] != xLimit && glacier_Albedo_obs[hh] != -9999)
                    glacier_Albedo[hh] = glacier_Albedo_obs[hh];
            }
            else {
                if (SWE[hh] <= 0.0 || ice_Albedo[hh] > Albedo[hh])
                    if (firn[hh] > 0.0)
                        glacier_Albedo[hh] = firn_Albedo[hh];
                    else
                        glacier_Albedo[hh] = ice_Albedo[hh]; // must be ice[hh] >= 0.0
            }
        }

        if (GlacierMode[hh] == 1 && SWE[hh] <= 0.0) // added on 25 June 2020
            Albedo[hh] = glacier_Albedo[hh];

        net_rain_org[hh] = net_rain[hh];
        cumnet_rain_org[hh] += net_rain[hh];

        if (nstep == 1 || Global::Freq == 1) { // beginning of every day
            Gnet_rainD[hh] = net_rain[hh];
            if (variation == VARIATION_1)
                Qnsn_Acc[hh] = Qnsn_Var[hh];
            else if (variation == VARIATION_2)
                Qnsn_Acc[hh] = Qnsn[hh];
        }
        else {
            Gnet_rainD[hh] += net_rain[hh];
            if (variation == VARIATION_1)
                Qnsn_Acc[hh] += Qnsn_Var[hh];
            else if (variation == VARIATION_2)
                Qnsn_Acc[hh] += Qnsn[hh];
        }

        float epsilon = 0.005f; // used for comparing floating numbers
        if (use_debris[hh] && debris_h[hh] > 0.0) { // debris-cover melt, Debris Enhanced Temperature-Index (DETI) model by Carenzo et al (2016), added on 16 June 2020
            if (fabs(debris_h[hh] - 0.05) < epsilon) {
                lagT[hh] = 0.0;
                lagSW[hh] = 0.0;
                TF[hh] = 0.0984;
                SRF[hh] = 0.0044;
            }
            else if (fabs(debris_h[hh] - 0.1) < epsilon) {
                lagT[hh] = 0.0;
                lagSW[hh] = 1.0;
                TF[hh] = 0.066;
                SRF[hh] = 0.0023;
            }
            else if (fabs(debris_h[hh] - 0.2) < epsilon) {
                lagT[hh] = 3.0;
                lagSW[hh] = 3.0;
                TF[hh] = 0.0456;
                SRF[hh] = 0.0009;
            }
            else if (fabs(debris_h[hh] - 0.23) < epsilon) {
                lagT[hh] = 3.0;
                lagSW[hh] = 4.0;
                TF[hh] = 0.0438;
                SRF[hh] = 0.0006;
            }
            else if (fabs(debris_h[hh] - 0.3) < epsilon) {
                lagT[hh] = 5.0;
                lagSW[hh] = 5.0;
                TF[hh] = 0.0392;
                SRF[hh] = 0.0002;
            }
            else if (fabs(debris_h[hh] - 0.4) < epsilon) {
                lagT[hh] = 7.0;
                lagSW[hh] = 7.0;
                TF[hh] = 0.0334;
                SRF[hh] = 0.0001;
            }
            else if (fabs(debris_h[hh] - 0.5) < epsilon) {
                lagT[hh] = 10.0;
                lagSW[hh] = 11.0;
                TF[hh] = 0.0265;
                SRF[hh] = 0.0;
            }

            if (nstep >= lagT[hh])
                lagT_used[hh] = hru_t[hh];

            if (nstep >= lagSW[hh])
                lagSW_used[hh] = Qsisn_Var[hh];

            if (hru_t[hh] > T_threshold[hh]) {
                Xdebris_melt_hrly[hh] = TF[hh] * lagT_used[hh] + SRF[hh] * (1 - glacier_Albedo[hh]) * lagSW_used[hh]; // modified 2 July 2020
                if (Xdebris_melt_hrly[hh] < 0.0)
                    Xdebris_melt_hrly[hh] = 0.0;
            }
            else
                Xdebris_melt_hrly[hh] = 0.0;

            if (nstep == 1)
                Xdebris_melt_acc[hh] = Xdebris_melt_hrly[hh];
            else
                Xdebris_melt_acc[hh] += Xdebris_melt_hrly[hh];
        } // debris-cover melt

        if (variation == VARIATION_5) { // katabatic parameterization
            const double Cp_air = 1006.0; // specific heat of air at constant pressure, J/kg K
            const double MOL_wt_ratio_h2o_to_air = 0.622; // molecular weight ratio of water to air, g
            const double Lv = 2.5E6; // latent heat of vaporization, J/kg
            const double Ts_glacier = 273.15; //surface temperature , K
            const double e_s = 0.6113; // surface water vapor pressure, kPa
            const double Pr = 5.0; // Prandlt constant
            const double Katabatic = 0.0004; // Katabatic constant
            const double g = 9.8; // gravity, m/s
            const double Cp_W0 = 4217.7; //specific heat of water, J/kg K
            const double rho_h2o = 1000.0; // density of water, kg/m^3

            Qn_kata[hh] = Qnsn_Var[hh];
            den_air[hh] = (Pa[hh] - hru_ea[hh]) * 1000 / (287.05 * (hru_t[hh] + 273.15)) + hru_ea[hh] * 1000 / (461.495 * (hru_t[hh] + 273.15));
            K_kat[hh] = Katabatic * ((hru_t[hh] + 273.15) - Ts_glacier) * pow(g / Ts_glacier * katabatic_lapse_rate[hh] * Pr, 0.5); // from Oerlemand and Grisogono (2002)
            Qh_kata[hh] = den_air[hh] * Cp_air * ((0.01 + K_kat[hh]) / 2) * ((hru_t[hh] + 273.15) - Ts_glacier); // katabatic parameterization from Oerlemand and Grisogono (2002)
            Qe_kata[hh] = (MOL_wt_ratio_h2o_to_air * den_air[hh] * Lv) / (Pa[hh] * 10.0) * ((0.01 + K_kat[hh]) / 2.0) * ((hru_ea[hh] - e_s) * 10.0); // katabatic parameterization from Oerlemand and Grisogono (2002)
            Cp_water[hh] = Cp_W0 - 2.55 * ((T_rain[hh] + 273.15) - FREEZE);
            Qp_kata[hh] = Cp_water[hh] * rho_h2o * net_rain_org[hh] / 1000.0 * ((T_rain[hh] + 273.15) - Ts_glacier) / (24.0 / Global::Freq * 3600.0); // advective flux from rainfall, use net_rain_org as net_rain is updated by glacier later (Hock, 2005)
            Qmelt_kata[hh] = Qn_kata[hh] + Qh_kata[hh] + Qe_kata[hh] + Qp_kata[hh]; // W/m^2
            Xmelt_int[hh] = Qmelt_kata[hh] / (rho_h2o * 316.825 * 1000.0) * 1000.0 * (24.0 / Global::Freq * 3600.0); // melt mass flux (mm/int), thermal quality B=0.95. 316.825 = 333.5*0.95 (kJ/kg),
            if (nstep == 1)
                Xmelt_acc[hh] = Xmelt_int[hh];
            else
                Xmelt_acc[hh] += Xmelt_int[hh];
        } // VARIATION_5
    } // for hh

    if (nstep == 0 || Global::Freq == 1) { // end of every day

        for (hh = 0; chkStruct(); ++hh) {

            Qmelt[hh] = 0.0;
            SWEmelt[hh] = snowmeltD[hh];
            cumSWEmelt[hh] += snowmeltD[hh];

            Qn_ebsm[hh] = 0.0;
            Qh_ebsm[hh] = 0.0;
            Qe_ebsm[hh] = 0.0;
            Qp_ebsm[hh] = 0.0;

            firnmelt[hh] = 0.0; // Has to be only once a daY
            icemelt[hh] = 0.0;

            // calculate SWE or firn

            if (SWE[hh] <= 0.0 && (firn[hh] > 0.0 || ice[hh] > 0.0)) {
                const_cast<long*> (inhibit_evap)[hh] = 1;

                if (variation == VARIATION_ORG && (tfactor[hh] > 0.0 || nfactor[hh] > 0.0)) {
                    if (delay_melt[hh] <= julian("now")) {

                        if (QnD) { // observation available (MJ/m^2*d)
                            if (QnD[hh] > 0.0)
                                Qn_ebsm[hh] = QnD[hh] * nfactor[hh]; // (mm/d)
                        }

                        Qh_ebsm[hh] = tmax[hh] * tfactor[hh]; // (mm/d)
                        Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh];

                        if (Qmelt[hh] <= 0.0)
                            Qmelt[hh] = 0.0;
                    }
                }
                else if (delay_melt[hh] <= julian("now")) {
                    double eamean = Common::estar(tmean[hh]) * rhmean[hh] / 100.0; \
                        switch (variation) {
                        case VARIATION_ORG:
                            if (QnD != NULL && Use_QnD[hh]) { // observation available (MJ/m^2*d)
                                if (QnD[hh] > 0.0)
                                    Qn_ebsm[hh] = QnD[hh];
                            }
                            else {
                                Qn_ebsm[hh] = -0.53 + 0.47 * (QdroD[hh] + QdfoD[hh]) * (0.52 + 0.52 * sunact[hh] / sunmax[hh]) * (1.0 - glacier_Albedo[hh]);
                            }
                            break;
                        case VARIATION_1:
                            Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
                            break;
                        case VARIATION_2:
                            Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
                            break;
                        case VARIATION_3:
                            Qn_ebsm[hh] = QnD[hh]; // already (MJ/m^2*d)
                            break;
                        } // switch

                    Qh_ebsm[hh] = -0.92 + 0.076 * umean[hh] + 0.19 * tmax[hh];
                    Qe_ebsm[hh] = 0.08 * (0.18 + 0.098 * umean[hh]) * (6.11 - eamean * 10.0);

                    if (Gnet_rainD[hh] > 0.0)
                        Qp_ebsm[hh] = Gnet_rainD[hh] * tmean[hh] * 4.2 / 1000.0;
                    else
                        Qp_ebsm[hh] = 0.0;

                    Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qe_ebsm[hh] + Qp_ebsm[hh];

                    Qmelt[hh] = Qmelt[hh] / 316.8 * 1000.0; // thermal quality B=0.95. 316.8 = 333.5*0.95 (kJ/kg), (mm/d)

                    if (variation == VARIATION_4)
                        Qmelt[hh] = Xmelt[hh];

                    if (variation == VARIATION_5) { // katabatic parameterization
                        Qmelt[hh] = Xmelt_acc[hh];
                        Xmelt_acc[hh] = 0.0;
                    }

                    if (use_debris[hh] && debris_h[hh] > 0.0) { // debris-cover melt
                        Qmelt[hh] = Xdebris_melt_acc[hh];
                        Xdebris_melt_acc[hh] = 0.0;
                    }

                    if (Qmelt[hh] <= 0.0)
                        Qmelt[hh] = 0.0;
                }
            } // no snow so melt firn or ice!

            if (firn[hh] > 0.0 || ice[hh] > 0.0) {

                if (nfirn[hh] > 0 && Qmelt[hh] > 0.0 && !inhibit_firnmelt[hh]) { // melt firn
                    double h2o;
                    while (nfirn[hh] > 0 && Qmelt[hh] > 0.0) {
                        h2o = firn_dens_array[0][hh] * firn_h_array[0][hh] / 1000.0;
                        if (Qmelt[hh] < h2o) { // melt some firn
                            firnmelt[hh] += Qmelt[hh];
                            cumQmelt[hh] += Qmelt[hh];
                            firn_h_array[0][hh] = (h2o - Qmelt[hh]) * 1000.0 / firn_dens_array[0][hh];
                            Qmelt[hh] = 0.0;
                        }
                        else { // All firn melts
                            firnmelt[hh] += h2o;
                            Qmelt[hh] -= h2o;
                            cumQmelt[hh] += h2o;
                            for (long nn = 0; nn < nfirn[hh] - 1; ++nn) { // move columns up
                                firn_dens_array[nn][hh] = firn_dens_array[nn + 1][hh];
                                firn_h_array[nn][hh] = firn_h_array[nn + 1][hh];
                            } // end for
                            --nfirn[hh];
                            firn_dens_array[nfirn[hh]][hh] = 0.0;
                            firn_h_array[nfirn[hh]][hh] = 0.0;
                            if (ice[hh] <= 0.0)
                                const_cast<long*> (inhibit_evap)[hh] = 0;
                        }
                        cumfirnmelt[hh] += firnmelt[hh];
                    } // end while

                    firn_depth[hh] = 0.0;
                    firn[hh] = 0.0;

                    for (long nn = 0; nn < nfirn[hh]; ++nn) {
                        firn_depth[hh] += firn_h_array[nn][hh];
                        firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // mm
                    }
                }  // if
        // handle ice
                else if (ice[hh] > 0.0 && Qmelt[hh] > 0.0 && !inhibit_icemelt[hh]) {
                    if (Qmelt[hh] >= ice[hh]) { // melt layer
                        icemelt[hh] = ice[hh];
                        Qmelt[hh] -= icemelt[hh];
                        cumQmelt[hh] += icemelt[hh];
                        ice[hh] = 0.0;
                        const_cast<long*> (inhibit_evap)[hh] = 0;
                    }
                    else { // melt some ice
                        ice[hh] -= Qmelt[hh];
                        cumQmelt[hh] += Qmelt[hh];
                        icemelt[hh] = Qmelt[hh];
                        Qmelt[hh] = 0.0;
                    }
                    cumicemelt[hh] += icemelt[hh];
                }

                // Update glacier at end of summer

                const double R = 8.314; // (J/(K.mol)
                const double RHOi = 917; // (kg/m3)

                long Julian = julian("now"); // same as "decday"
                if (SWE_to_firn_Julian[hh] == Julian) { // use fixed date - end of day    !!!!

                    double k0 = 11.0 * exp(-10160.0 / (R * (TKMA[hh] + CRHM_constants::Tm)));
                    double k1 = 575.0 * exp(-21400.0 / (R * (TKMA[hh] + CRHM_constants::Tm)));

                    // Check if bottom layer of firn becomes ice
                    if (nfirn[hh] && firn_dens_array[nfirn[hh] - 1][hh] >= 830.0) { // transfer
                        firn_2ice[hh] = firn_dens_array[nfirn[hh] - 1][hh] * firn_h_array[nfirn[hh] - 1][hh] / 1000.0; // ice (mm)
                        ice[hh] += firn_2ice[hh];
                        cumfirn_2ice[hh] = firn_2ice[hh];
                        firn_2ice_dens[hh] = firn_dens_array[nfirn[hh] - 1][hh];
                        firn_dens_array[nfirn[hh] - 1][hh] = 0.0;
                        firn_h_array[nfirn[hh] - 1][hh] = 0.0; // (mm)
                        --nfirn[hh];
                    }
                    else {
                        firn_2ice[hh] = 0.0;
                        firn_2ice_dens[hh] = 0.0;
                    }

                    // Add new SWE

                    if (SWE[hh] > 0.0) {
                        if (nfirn[hh] == nlay) { // combine last two entries
                            double mean_d = (firn_dens_array[nlay - 2][hh] + firn_dens_array[nlay - 1][hh]) / 2.0;
                            firn_h_array[nlay - 2][hh] = (firn_h_array[nlay - 2][hh] * firn_dens_array[nlay - 2][hh] + firn_h_array[nlay - 1][hh] * firn_dens_array[nlay - 1][hh]) / mean_d;
                            firn_dens_array[nlay - 2][hh] = mean_d;
                            --nfirn[hh]; // remove layer from SWE
                        }

                        for (long nn = nlay - 2; nn >= 0; --nn) { // move column down opening space
                            firn_dens_array[nn + 1][hh] = firn_dens_array[nn][hh];
                            firn_h_array[nn + 1][hh] = firn_h_array[nn][hh];
                        }

                        if (nfirn[hh] >= nlay) { // space available to allocate layer !!! check purpose/position !!!
                            string S = string("'") + Name + " (glacier)' too many firn fronts in hru = " + to_string(hh + 1).c_str();
                            CRHMException TExcept(S.c_str(), TExcept::TERMINATE);
                            LogError(TExcept);
                            throw TExcept;
                        }
                        ++nfirn[hh];

                        // solve for density from SWE using Bisection method

                        double h1 = 0.6, h2 = 8.00, e, h;
                        long iter_max = 0;
                        do {
                            h = (h1 + h2) / 2.0; // (m)
                            rho = (450.0 - 204.7 / h * (1.0 - exp(-h / 0.673))); // Pomeroy et al (1998)
                            e = rho * h - SWE[hh]; // original equation was cm
                            if (e < 0)
                                h1 += (h2 - h1) / 2.0;
                            else
                                h2 -= (h2 - h1) / 2.0;

                        } while (fabs(e) > 0.001 && h > 0.601 && ++iter_max < 100); // below 60cm the density is 250 kg/m3

                        firn_h_array[0][hh] = SWE[hh] * 1000.0 / rho;
                        firn_dens_array[0][hh] = rho;

                        firn_yr_array[0][hh] = 1.0 / (k0 * SWEAA[hh]) * log((RHOi - firn_dens_array[0][hh]) / (RHOi - 550));

                        SWE_2firn[hh] = SWE[hh];
                        cumSWE_2firn[hh] += SWE[hh];
                        SWE_2firn_dens[hh] = rho;
                        SWE[hh] = 0.0;
                    } // add SWE
                    else
                        rho = 249.0; // value for SWE = 0.1mm

            // Update firn layer densities

                    rho_snow[hh] = rho;
                    firn_depth[hh] = firn_h_array[0][hh]; // (mm)
                    firn[hh] = firn_dens_array[0][hh] * firn_h_array[0][hh] / 1000.0; // (mm)
                    if (nfirn[hh] > 0)
                        for (long nn = 1; nn < nfirn[hh]; ++nn) {
                            double old_firn = firn_dens_array[nn][hh] * firn_h_array[nn][hh] / 1000.0;

                            if (old_firn == 0.0) {
                                old_firn = (double)(long long)hh * 100ll + (long long)nn;
                                //              assert(0);
                                string D = StandardConverterUtility::GetDateTimeInString(Global::DTnow) + " Update firn layer densities (27549)";
                                string SS = D + "hh " + to_string(hh) + "old_firn: " + FloatToStrF(old_firn, TFloatFormat::ffFixed, 10, 4);
                                SS = SS + " firn_dens_array[nn][hh]: " + FloatToStrF(firn_dens_array[nn][hh], TFloatFormat::ffFixed, 10, 4)
                                    + " firn_h_array[nn][hh]: " + FloatToStrF(firn_h_array[nn][hh], TFloatFormat::ffFixed, 10, 4);
                                CRHMException TExcept(SS.c_str(), TExcept::WARNING);
                                LogError(TExcept);
                            }
                            double h550 = 1000.0 / (RHOi * k0) * (log(550.0 / (RHOi - 550.0)) - log(rho / (RHOi - rho))); // rho is current SWE density      Densification
                            if (Densification[hh] != 0) {
                                if (firn_dens_array[nn][hh] < 550.0) { // density < 550
                                    double Z0 = exp(RHOi * k0 * firn_depth[hh] / 10e6 + log(firn_dens_array[nn][hh] / (RHOi - firn_dens_array[nn][hh])));
                                    double New = RHOi * Z0 / (1.0 + Z0);
                                    if (New > firn_dens_array[nn][hh])
                                        firn_dens_array[nn][hh] = New;
                                    firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
                                    firn_yr_array[nn][hh] = 1.0 / (k0 * SWEAA[hh]) * log((RHOi - rho) / (RHOi - 550));
                                }
                                else { // density >= 550
                                    double Z1 = exp(RHOi * k1 * (firn_depth[hh] / 1000.0 - h550) / 1000.0 / sqrt(SWEAA[hh]) + log(550.0 / (RHOi - 550.0)));
                                    double New = RHOi * Z1 / (1.0 + Z1);
                                    if (firn_dens_array[nn][hh] > New)
                                        firn_dens_array[nn][hh] = New;
                                    firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
                                    double t550 = 1.0 / (k0 * SWEAA[hh]) * (log((RHOi - rho) / (RHOi - 550))); // units years
                                    firn_yr_array[nn][hh] = 1.0 / (k1 * sqrt(SWEAA[hh])) * log((RHOi - 550) / (RHOi - firn_dens_array[nn][hh])) + t550;
                                }
                            }
                            else {
                                firn_yr_array[nn][hh] = 0.0;
                                if (firn_dens_array[nn][hh] < 550.0) {
                                    firn_dens_array[nn][hh] += Densification_550[hh];
                                    firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
                                }
                                else {
                                    firn_dens_array[nn][hh] += Densification_above_550[hh];
                                    if (firn_dens_array[nn][hh] > 1000.0)
                                        firn_dens_array[nn][hh] = 1000.0;
                                    firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
                                }
                            }

                            firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
                            firn_depth[hh] += firn_h_array[nn][hh];

                            firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // (mm)
                        } // for nn
                } // end update SWE and firn
            } // update firn or ice!
        } // end for HRUs
    } // end if (end of day)

    SWEDelay->DoClark();
    firnDelay->DoClark();
    iceDelay->DoClark();

    for (hh = 0; chkStruct(); ++hh) {
        Pa[hh] = 101.3f * pow((293.0f - 0.0065f * glacier_Surf[hh]) / 293.0f, 5.26f);  // (kPa)

        if (GlacierMode[hh] == 1) { // ie glacier
            glacier_h2o[hh] = SWE[hh] + firn[hh] + ice[hh]; // water equivalent(mm)
            glacier_depth[hh] = (Common::DepthofSnow(SWE[hh]) + firn_depth[hh]) / 1000.0 + ice[hh] / ice_dens[hh]; // (m) thickness
            glacier_Surf[hh] = glacier_depth[hh] + topo_elev[hh]; // (m)

            net_rain[hh] += (firnmelt_delayed[hh] + icemelt_delayed[hh]) / Global::Freq;
        }
        cumnet_rain_glacier[hh] += net_rain[hh];
        cumsnowmeltD_glacier[hh] += snowmeltD[hh] / Global::Freq;
    } // end for HRUs
}

void Classglacier::finish(bool good) {

    double Glacier_All = 0.0;
    double SWE_All = 0.0;
    double firn_All = 0.0;
    double ice_All = 0.0;
    double firn_init_All = 0.0;
    double ice_init_All = 0.0;
    double firn_change_All = 0.0;
    double ice_change_All = 0.0;
    double cumfirnmelt_All = 0.0;
    double cumSWE_2firn_All = 0.0;
    double cumicemelt_All = 0.0;
    double cumfirn_2ice_All = 0.0;
    double cumnet_rain_glacier_All = 0.0;

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (glacier)' firn_init    (mm) (mm*hru) (mm*hru/basin): ").c_str(), firn_init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' firn_final   (mm) (mm*hru) (mm*hru/basin): ").c_str(), firn[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumfirnmelt  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumfirnmelt[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumSWE_2firn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_2firn[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' firn_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), (firn[hh] - firn_init[hh]), hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumicemelt   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumicemelt[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumfirn_2ice (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumfirn_2ice[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' ice_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice_init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' ice          (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' ice_change   (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh] - ice_init[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumnet_rain_org      (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain_org[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumnet_rain_glacier  (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain_glacier[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumSWEmelt_org       (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumSWEmelt[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (glacier)' cumsnowmeltD_glacier (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmeltD_glacier[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");

        Glacier_All += glacier_h2o[hh];
        SWE_All += SWE[hh];
        firn_All += firn[hh];
        ice_All += ice[hh];
        firn_init_All += firn_init[hh];
        ice_init_All += ice_init[hh];
        firn_change_All += firn[hh] - firn_init[hh];
        ice_change_All += ice_init[hh] - ice[hh];
        cumfirnmelt_All += cumfirnmelt[hh];
        cumSWE_2firn_All += cumSWE_2firn[hh];
        cumicemelt_All += cumicemelt[hh];
        cumfirn_2ice_All += cumfirn_2ice[hh];
        cumnet_rain_glacier_All += cumnet_rain_glacier[hh];
        LogDebug(" ");
    }

    LogMessage(string("'" + Name + " (glacier)' SWE_All               (mm*basin): ").c_str(), SWE_All, "      *** cumulative sum of all HRU SWE");
    LogMessage(string("'" + Name + " (glacier)' firn_All              (mm*basin): ").c_str(), firn_All, "      *** cumulative sum of all HRU firn");
    LogMessage(string("'" + Name + " (glacier)' ice_All               (mm*basin): ").c_str(), ice_All, "      *** cumulative sum of all HRU ice");
    LogMessage(string("'" + Name + " (glacier)' Glacier_All           (mm*basin): ").c_str(), Glacier_All, "      *** cumulative sum of all of above");
    LogDebug(" ");
    LogMessage(string("'" + Name + " (glacier)' firn_init_All         (mm*basin): ").c_str(), firn_init_All, "      *** cumulative sum of all HRU firn_init");
    LogMessage(string("'" + Name + " (glacier)' ice_init_All          (mm*basin): ").c_str(), ice_init_All, "      *** cumulative sum of all HRU ice_init");
    LogDebug(" ");
    LogMessage(string("'" + Name + " (glacier)' firn_change_All       (mm*basin): ").c_str(), firn_change_All, "      *** cumulative sum of all HRU firn change");
    LogMessage(string("'" + Name + " (glacier)' ice_change_All        (mm*basin): ").c_str(), ice_change_All, "      *** cumulative sum of all HRU ice change");
    LogDebug(" ");
    LogMessage(string("'" + Name + " (glacier)' cumfirnmelt_All       (mm*basin): ").c_str(), cumfirnmelt_All, "      *** cumulative sum of all HRU firnmelt");
    LogMessage(string("'" + Name + " (glacier)' cumSWE_2firn_All      (mm*basin): ").c_str(), cumSWE_2firn_All, "      *** cumulative sum of all HRU cumSWE_2firn");
    LogMessage(string("'" + Name + " (glacier)' cumfirn_2ice_All      (mm*basin): ").c_str(), cumfirn_2ice_All, "      *** cumulative sum of all HRU cumSWE_2firn");
    LogMessage(string("'" + Name + " (glacier)' cumicemelt_All        (mm*basin): ").c_str(), cumicemelt_All, "      *** cumulative sum of all HRU cumicemelt");
    LogMessage(string("'" + Name + " (glacier)' cumnet_rain_glacier_All (mm*basin): ").c_str(), cumnet_rain_glacier_All, "      *** cumulative sum of all HRU rain + firn and ice melt");
    LogDebug(" ");

    delete firnDelay;
    delete iceDelay;
}

double Classglacier::DepthofSnow(double SWE) { // (mm)

// Tabler et al. (1990b) Calculates Snow Depth(mm) from SWE(mm)
    double rho;

    if (SWE > 1.0) {
        rho = 522.0 - 204700 / SWE * (1.0 - exp(-SWE / 673.0)); // converted from original cm to mm
        return SWE / rho * 1000.0; // (mm)
    }
    else
        return 0.0;

} // DepthofSnow
