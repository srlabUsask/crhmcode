#include "ClassGlacier_melt_debris_cover_estimate_Mod.h"


ClassGlacier_melt_debris_cover_estimate_Mod* ClassGlacier_melt_debris_cover_estimate_Mod::klone(string name) const {
    return new ClassGlacier_melt_debris_cover_estimate_Mod(name);
}

void ClassGlacier_melt_debris_cover_estimate_Mod::decl(void) {

    long step = getstep();
    long nstep = step % Global::Freq;

    declvar("lagT", TDim::NHRU, "lagged temperature.", "(°C)", &lagT);

    declvar("lagSW", TDim::NHRU, "lagged shortwave radiation.", "(W/m^2)", &lagSW);

    declvar("Gmelt_energy", TDim::NHRU, "Energy available for glacier melt.", "(W/m^2)", &Gmelt_energy);

    declvar("den_air", TDim::NHRU, "air density.", "(kg/m^-3)", &den_air);

    declvar("K_kat", TDim::NHRU, "katabatic bulk exchange coefficient.", "()", &K_kat);

    declvar("Cp_water", TDim::NHRU, "specific heat of water.", "(J/(kg*K))", &Cp_water);

    declvar("Xmelt", TDim::NHRU, "Experimental Firn and Ice melt at daily timestepe.", "(mm/d)", &Xmelt);

    declvar("Xmelt_int", TDim::NHRU, "Experimental Firn and Ice melt at interval timestep.", "(mm/int)", &Xmelt_int);

    declvar("Xmelt_acc", TDim::NHRU, "Experimental Firn and Ice melt daily accumulator.", "(mm)", &Xmelt_acc);

    declvar("Xmelt_V5", TDim::NHRU, "Version 5 Firn and Ice melt daily variable.", "(mm)", &Xmelt_V5);



    declparam("debris_h", TDim::NHRU, "[0.0]", "0", "10", "debris thickness.", "(m)", &debris_h);

    declparam("T_threshold", TDim::NHRU, "[1.0]", "-30", "30", "threshold temperature for melt to occur.", "(°C)", &T_threshold);

    declreadobs("lagT1", TDim::NHRU, "lagged temperature 1", "(°C)", &lagT1, HRU_OBS_Q, true);
    declreadobs("lagT2", TDim::NHRU, "lagged temperature 2", "(°C)", &lagT2, HRU_OBS_Q, true);
    declreadobs("lagT3", TDim::NHRU, "lagged temperature 3", "(°C)", &lagT3, HRU_OBS_Q, true);
    declreadobs("lagT4", TDim::NHRU, "lagged temperature 4", "(°C)", &lagT4, HRU_OBS_Q, true);

    declreadobs("lagSW1", TDim::NHRU, "lagged shortwave radiation 1", "(W/m^2)", &lagSW1, HRU_OBS_Q, true);
    declreadobs("lagSW2", TDim::NHRU, "lagged shortwave radiation 2", "(W/m^2)", &lagSW2, HRU_OBS_Q, true);
    declreadobs("lagSW3", TDim::NHRU, "lagged shortwave radiation 3", "(W/m^2)", &lagSW3, HRU_OBS_Q, true);
    declreadobs("lagSW4", TDim::NHRU, "lagged shortwave radiation 4", "(W/m^2)", &lagSW4, HRU_OBS_Q, true);
    declreadobs("lagSW5", TDim::NHRU, "lagged shortwave radiation 5", "(W/m^2)", &lagSW5, HRU_OBS_Q, true);
    declreadobs("lagSW6", TDim::NHRU, "lagged shortwave radiation 6", "(W/m^2)", &lagSW6, HRU_OBS_Q, true);

    declgetvar("*", "Albedo", "()", &Albedo);
    declgetvar("*", "T_rain", "(°C)", &T_rain);
    declgetvar("*", "hru_t", "(°C)", &hru_t);
    declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
    declgetvar("*", "net_rain", "(mm/int)", &net_rain);
    declgetvar("*", "Pa", "(kPa)", &Pa);
    declgetvar("*", "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var);

    declputvar("*", "Gn_ebsm", "(W/m^2)", &Gn_ebsm);
    declputvar("*", "Gh_ebsm", "(W/m^2)", &Gh_ebsm);
    declputvar("*", "Ge_ebsm", "(W/m^2)", &Ge_ebsm);
    declputvar("*", "Gp_ebsm", "(W/m^2)", &Gp_ebsm);
}

void ClassGlacier_melt_debris_cover_estimate_Mod::init(void) {
    for (hh = 0; hh < nhru; ++hh) {
        lagT[hh] = 0.0;
        lagSW[hh] = 0.0;
        Gmelt_energy[hh] = 0.0;
        den_air[hh] = 0.0;
        Cp_water[hh] = 0.0;
        Xmelt[hh] = 0.0;
        Xmelt_int[hh] = 0.0;
        Xmelt_acc[hh] = 0.0;
    }
}

void ClassGlacier_melt_debris_cover_estimate_Mod::run(void) {
    const double Cp_air = 1006;
    const double MOL_wt_ratio_h2o_to_air = 0.622;
    const double Lv = 2.5e6;
    const double Ts_glacier = 273.15;
    const double e_s = 0.6113;
    const double Pr = 5;
    const double Katabatic = 0.0004;
    const double g = 9.8;
    const double FREEZE = 273.15;
    const double Cp_W0 = 4217.7;
    const double rho_h2o = 1000.0;
    const double B = 0.95;
    const double lapse_rate = 0.005;
    const double LH_fusion = 333.5;
    double TF = 0.0;
    double SRF = 0.0;

    long nstep = getstep();
    nstep = nstep % Global::Freq;

    for (hh = 0; hh < nhru; ++hh) {
        if (debris_h[hh] <= 0) {
            lagT[hh] = hru_t[hh];
            lagSW[hh] = Qnsn_Var[hh];
            TF = 0;
            SRF = 0;
            Gn_ebsm[hh] = Qnsn_Var[hh];
            den_air[hh] = (Pa[hh] - hru_ea[hh]) * 1000 / (287.05 * (hru_t[hh] + 273.15)) + hru_ea[hh] * 1000 / (461.495 * (hru_t[hh] + 273.15));
            K_kat[hh] = Katabatic * ((hru_t[hh] + 273.15) - Ts_glacier) * pow(g / Ts_glacier * lapse_rate * Pr, 0.5);
            Gh_ebsm[hh] = den_air[hh] * Cp_air * ((0.01 + K_kat[hh]) / 2) * ((hru_t[hh] + 273.15) - Ts_glacier);
            Ge_ebsm[hh] = (MOL_wt_ratio_h2o_to_air * den_air[hh] * Lv) / (Pa[hh] * 10) * ((0.01 + K_kat[hh]) / 2) * (hru_ea[hh] - e_s) * 0.1;
            Cp_water[hh] = Cp_W0 - 2.55 * ((T_rain[hh] + 273.15) - FREEZE);
            Gp_ebsm[hh] = Cp_water[hh] * rho_h2o * net_rain[hh] / 1000 * ((T_rain[hh] + 273.15) - Ts_glacier) / (24ll / (long long)Global::Freq * 3600ll);
            Gmelt_energy[hh] = Gn_ebsm[hh] + Gh_ebsm[hh] + Ge_ebsm[hh] + Gp_ebsm[hh];
            Xmelt_int[hh] = Gmelt_energy[hh] / (996.0 * 334000.0) * 1000.0 * 3600.0; // (996*334000) * 1000*3600;
            if (Xmelt_int[hh] < 0.0)
                Xmelt_int[hh] = 0.0;
        } // debris_h[hh] <= 0
        else { // debris_h[hh] > 0
            Xmelt_int[hh] = 0.0;
            if (debris_h[hh] <= 0.05) {
                lagT[hh] = hru_t[hh];
                lagSW[hh] = Qnsn_Var[hh];
                TF = 0.0984;
                SRF = 0.0044;
            }
            else if (debris_h[hh] <= 0.1) {
                lagT[hh] = hru_t[hh];
                lagSW[hh] = lagSW1[hh];
                TF = 0.066;
                SRF = 0.0023;
            }
            else if (debris_h[hh] <= 0.2) {
                lagT[hh] = lagT1[hh];
                lagSW[hh] = lagSW2[hh];
                TF = 0.0456;
                SRF = 0.0009;
            }
            else if (debris_h[hh] <= 0.23) {
                lagT[hh] = lagT1[hh];
                lagSW[hh] = lagSW3[hh];
                TF = 0.04338;
                SRF = 0.0006;
            }
            else if (debris_h[hh] <= 0.3) {
                lagT[hh] = lagT2[hh];
                lagSW[hh] = lagSW4[hh];
                TF = 0.0392;
                SRF = 0.0002;
            }
            else if (debris_h[hh] <= 0.4) {
                lagT[hh] = lagT3[hh];
                lagSW[hh] = lagSW5[hh];
                TF = 0.0334;
                SRF = 0.0001;
            }
            else {
                lagT[hh] = lagT4[hh];
                lagSW[hh] = lagSW6[hh];
                TF = 0.0265;
                SRF = 0;
            }
            if (hru_t[hh] > T_threshold[hh]) {
                Xmelt_int[hh] = TF * lagT[hh] + SRF * (1 - Albedo[hh]) * lagSW[hh];
                if (Xmelt_int[hh] <= 0.0)
                    Xmelt_int[hh] = 0.0;
            }
        } // debris_h[hh] > 0

        if (nstep == 1)
            Xmelt_acc[hh] = Xmelt_int[hh]; // start of every
        else
            Xmelt_acc[hh] += Xmelt_int[hh]; // every other interval

        if (nstep == 0 || Global::Freq == 1) { // end of every day
            Xmelt[hh] = Xmelt_acc[hh];
            Xmelt_acc[hh] = 0.0;
        } // end of every day
    } // for hh
} // run