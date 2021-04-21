#include "ClassGlacier_debris_cover.h"

ClassGlacier_debris_cover* ClassGlacier_debris_cover::klone(string name) const {
    return new ClassGlacier_debris_cover(name);
}

void ClassGlacier_debris_cover::decl(void) {

    long step = getstep();
    long nstep = step % Global::Freq;

    declvar("lagT", TDim::NHRU, "lagged temperature.", "(" + string(DEGREE_CELSIUS) + ")", &lagT);

    declvar("lagSW", TDim::NHRU, "lagged shortwave radiation.", "(W/m^2)", &lagSW);

    declvar("Xmelt", TDim::NHRU, "Experimental Firn and Ice melt at daily timestepe.", "(mm/d)", &Xmelt);

    declvar("Xmelt_int", TDim::NHRU, "Experimental Firn and Ice melt at interval timestep.", "(mm/int)", &Xmelt_int);

    declvar("Xmelt_acc", TDim::NHRU, "Experimental Firn and Ice melt daily accumulator.", "(mm)", &Xmelt_acc);


    declparam("debris_h", TDim::NHRU, "[0.0]", "0", "10", "debris thickness.", "(m)", &debris_h);

    declparam("T_threshold", TDim::NHRU, "[1.0]", "-30", "30", "threshold temperature for melt to occur.", "(" + string(DEGREE_CELSIUS) + ")", &T_threshold);

    declreadobs("lagT1", TDim::NHRU, "lagged temperature 1", "(" + string(DEGREE_CELSIUS) + ")", &lagT1, HRU_OBS_Q, true);
    declreadobs("lagT2", TDim::NHRU, "lagged temperature 2", "(" + string(DEGREE_CELSIUS) + ")", &lagT2, HRU_OBS_Q, true);
    declreadobs("lagT3", TDim::NHRU, "lagged temperature 3", "(" + string(DEGREE_CELSIUS) + ")", &lagT3, HRU_OBS_Q, true);
    declreadobs("lagT4", TDim::NHRU, "lagged temperature 4", "(" + string(DEGREE_CELSIUS) + ")", &lagT4, HRU_OBS_Q, true);

    declreadobs("lagSW1", TDim::NHRU, "lagged shortwave radiation 1", "(W/m^2)", &lagSW1, HRU_OBS_Q, true);
    declreadobs("lagSW2", TDim::NHRU, "lagged shortwave radiation 2", "(W/m^2)", &lagSW2, HRU_OBS_Q, true);
    declreadobs("lagSW3", TDim::NHRU, "lagged shortwave radiation 3", "(W/m^2)", &lagSW3, HRU_OBS_Q, true);
    declreadobs("lagSW4", TDim::NHRU, "lagged shortwave radiation 4", "(W/m^2)", &lagSW4, HRU_OBS_Q, true);
    declreadobs("lagSW5", TDim::NHRU, "lagged shortwave radiation 5", "(W/m^2)", &lagSW5, HRU_OBS_Q, true);
    declreadobs("lagSW6", TDim::NHRU, "lagged shortwave radiation 6", "(W/m^2)", &lagSW6, HRU_OBS_Q, true);

    declgetvar("*", "Albedo", "()", &Albedo);
    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
    declgetvar("*", "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var);
}

void ClassGlacier_debris_cover::init(void) {
    for (hh = 0; hh < nhru; ++hh) {
        lagT[hh] = 0.0;
        lagSW[hh] = 0.0;
        Xmelt[hh] = 0.0;
        Xmelt_int[hh] = 0.0;
        Xmelt_acc[hh] = 0.0;
    }
}

void ClassGlacier_debris_cover::run(void) {

    double TF = 0.0;
    double SRF = 0.0;

    long nstep = getstep();
    nstep = nstep % Global::Freq;

    for (hh = 0; hh < nhru; ++hh) {
        if (debris_h[hh] > 0.0) {
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
            else if (debris_h[hh] > 0.4) {
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