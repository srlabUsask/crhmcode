#include "ClassWQ_pbsmSnobal.h"


ClassWQ_pbsmSnobal* ClassWQ_pbsmSnobal::klone(string name) const {
    return new ClassWQ_pbsmSnobal(name);
}

void ClassWQ_pbsmSnobal::decl(void) {

    Description = "'Special \"pbsm\" module compatible with \"snobal\".' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

    variation_set = VARIATION_0 + VARIATION_2;

    declgetvar("*", "hru_u", "(m/s)", &hru_u);


    variation_set = VARIATION_1 + VARIATION_3;

    declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


    variation_set = VARIATION_2 + VARIATION_3;

    declparam("u_D", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

    declparam("Drift_offset", TDim::NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

    declparam("Drift_slope", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

    declparam("Subl_offset", TDim::NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

    declparam("Subl_slope", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


    variation_set = VARIATION_ORG;

    declstatvar("SWE_max", TDim::NHRU, "snow water equivalent seasonal maximum", "(mm)", &SWE_max);

    declvar("SWE_conc", TDim::NDEFN, "snow water equivalent", "(mg/l)", &SWE_conc, &SWE_conc_lay, numsubstances);

    declvar("Subl", TDim::NHRU, "interval sublimation", "(mm/int)", &Subl);

    declvar("Subl_conc", TDim::NDEFN, "interval sublimation", "(mm/int)", &Subl_conc, &Subl_conc_lay, numsubstances);

    declvar("cumDriftOut", TDim::NHRU, "cumulative transport from HRU", "(mm)", &cumDriftOut);

    declvar("cumDriftOut_mWQ", TDim::NDEFN, "mass solute from HRU", "(mg/l * mm*km^2/int)", &cumDriftOut_mWQ, &cumDriftOut_mWQ_lay, numsubstances);

    declvar("Drift_out", TDim::NHRU, "interval transport out of HRU", "(mm/int)", &Drift_out);

    declvar("Drift_out_conc", TDim::NDEFN, "interval transport out of HRU", "(mg/l)", &Drift_out_conc, &Drift_out_conc_lay, numsubstances);

    declvar("hru_subl", TDim::NHRU, "interval sublimation", "(mm/int)", &Subl);

    declvar("hru_drift", TDim::NHRU, "interval composite transport", "(mm/int)", &Drift);

    declvar("Drift_in", TDim::NHRU, "interval transport into HRU", "(mm/int)", &Drift_in);

    declvar("Drift_in_conc", TDim::NDEFN, "interval transport into HRU", "(mg/l)", &Drift_in_conc, &Drift_in_conc_lay, numsubstances);

    decldiag("DriftH", TDim::NHRU, "interval transport", "(mm/int)", &DriftH);

    decldiag("SublH", TDim::NHRU, "interval sublimation", "(mm/int)", &SublH);

    decldiag("BasinSnowLoss", TDim::BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

    decldiag("BasinSnowLoss_mWQ", TDim::NDEF, "transport out of basin", "(mg/l * mm*km^2/int)", &BasinSnowLoss_mWQ, &BasinSnowLoss_mWQ_lay, numsubstances);

    decldiag("BasinSnowGain", TDim::BASIN, "cumulative transport to basin estimated from HRU 1", "(mm/int)", &BasinSnowGain);

    decldiag("BasinSnowGain_mWQ", TDim::NDEF, "cumulative transport to basin estimated from HRU 1", "(mg/l * mm*km^2/int)", &BasinSnowGain_mWQ, &BasinSnowGain_mWQ_lay, numsubstances);

    declvar("BasinSnowLoss", TDim::BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

    declvar("cumSubl", TDim::NHRU, "cumulative sublimation", "(mm)", &cumSubl);

    declvar("cumSubl_mWQ", TDim::NDEFN, "cumulative sublimation solute", "(mg/l * mm*km^2/int)", &cumSubl_mWQ, &cumSubl_mWQ_lay, numsubstances);

    declvar("cumDrift", TDim::NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

    declvar("cumBasinSnowLoss", TDim::BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

    declvar("cumBasinSnowLoss_mWQ", TDim::NDEF, "cumulative mass of solute transport out of basin", "(mg/l * mm*km^2/int)", &cumBasinSnowLoss_mWQ, &cumBasinSnowLoss_mWQ_lay, numsubstances);

    declvar("cumBasinSnowGain", TDim::BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

    declvar("cumBasinSnowGain_mWQ", TDim::NDEF, "cumulative mass of solute transport to basin estimated from HRU 1", "(mg/l * mm*km^2/int)", &cumBasinSnowGain_mWQ, &cumBasinSnowGain_mWQ_lay, numsubstances);

    declvar("cumDriftIn", TDim::NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

    declvar("cumDriftIn_mWQ", TDim::NDEFN, "cumulative mass of solute transport to HRU", "(mg/l * mm*km^2/int)", &cumDriftIn_mWQ, &cumDriftIn_mWQ_lay, numsubstances);

    decllocal("hru_basin", TDim::NHRU, "conversion factor", "()", &hru_basin);

    decldiag("DrySnow", TDim::NHRU, "DrySnow", "()", &DrySnow);

    declvar("SnowAge", TDim::NHRU, "SnowAge", "()", &SnowAge);

    declvar("cumSno", TDim::NHRU, "cumulative snow", "(mm)", &cumSno);

    declvar("cumSno_mWQ", TDim::NDEFN, "cumulative mass of solute snow", "(mg/l * mm*km^2/int)", &cumSno_mWQ, &cumSno_mWQ_lay, numsubstances);

    decldiag("Prob", TDim::NHRU, "Probability", "()", &Prob);

    decldiag("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

    decllocal("SWE_Init", TDim::NHRU, "initial SWE", "(mm)", &SWE_Init);

    // parameters

    declparam("fetch", TDim::NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

    declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

    declparam("distrib", TDim::NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

    declparam("N_S", TDim::NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

    declparam("A_S", TDim::NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

    declparam("inhibit_bs", TDim::NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

    declparam("inhibit_subl", TDim::NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

    declparam("rain_conc", TDim::NDEFN, "0", "0", "1000", "rain solute concentration", "(mg/l)", &rain_conc, &rain_conc_lay, numsubstances);

    declparam("snow_conc", TDim::NDEFN, "0", "0", "1000", "snow solute concentration", "(mg/l)", &snow_conc, &snow_conc_lay, numsubstances);

    declparam("atmos_mWQ", TDim::NDEFN, "0", "0", "10", "total basin area", "(mg/int??)", &atmos_mWQ, &atmos_mWQ_lay, numsubstances);


    decllocal("DrySnow_0", TDim::NHRU, "", "", &DrySnow_0);

    decllocal("SnowAge_0", TDim::NHRU, "", "", &SnowAge_0);

    decllocal("BasinSnowGain_0", TDim::NHRU, "", "", &BasinSnowGain_0);

    decllocal("cumBasinSnowGain_0", TDim::NHRU, "", "", &cumBasinSnowGain_0);

    decllocal("BasinSnowLoss_0", TDim::NHRU, "", "", &BasinSnowLoss_0);

    decllocal("cumBasinSnowLoss_0", TDim::NHRU, "", "", &cumBasinSnowLoss_0);

    decllocal("Subl_0", TDim::NHRU, "", "", &Subl_0);

    decllocal("Subl_0", TDim::NHRU, "", "", &Subl_0);

    decllocal("cumSubl_0", TDim::NHRU, "", "", &cumSubl_0);

    decllocal("Drift_in_0", TDim::NHRU, "", "", &Drift_in_0);

    decllocal("cumDriftIn_0", TDim::NHRU, "", "", &cumDriftIn_0);

    decllocal("Drift_out_0", TDim::NHRU, "", "", &Drift_out_0);

    decllocal("cumDriftOut_0", TDim::NHRU, "", "", &cumDriftOut_0);

    decllocal("SWE_0", TDim::NHRU, "", "", &SWE_0);

    decllocal("SWE_Init_0", TDim::NHRU, "", "", &SWE_Init_0);

    decllocal("cumSno_0", TDim::NHRU, "", "", &cumSno_0);

    declputvar("*", "SWE", "(kg/m^2)", &SWE);
    declgetvar("*", "z_s", "(m)", &z_s);
    declgetvar("*", "rho", "(kg/m^3)", &rho);

    declgetvar("*", "hru_t", "(°C)", &hru_t);
    declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
    declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
    declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClassWQ_pbsmSnobal::init(void) {

    nhru = getdim(TDim::NHRU);

    Reset_WQ(0, cumBasinSnowLoss, cumBasinSnowLoss_mWQ_lay);
    Reset_WQ(0, cumBasinSnowGain, cumBasinSnowGain_mWQ_lay);
    Reset_WQ(0, BasinSnowLoss, BasinSnowLoss_mWQ_lay);
    Reset_WQ(0, BasinSnowGain, BasinSnowGain_mWQ_lay);

    for (hh = 0; hh < nhru; ++hh) {

        Reset_WQ(hh, Drift_in, Drift_in_conc_lay);
        Reset_WQ(hh, Drift_out, Drift_out_conc_lay);
        Reset_WQ(hh, cumDriftOut, cumDriftOut_mWQ_lay);
        Reset_WQ(hh, cumDriftIn, cumDriftIn_mWQ_lay);
        Reset_WQ(hh, cumSno, cumSno_mWQ_lay);
        Reset_WQ(hh, cumSubl, cumSubl_mWQ_lay);

        for (long Sub = 0; Sub < numsubstances; ++Sub)
            SWE_conc_lay[Sub][hh];


        SnowAge[hh] = 0.0;
        DrySnow[hh] = 0;
        snowdepth[hh] = 0.0;
        DriftH[hh] = 0.0;
        SublH[hh] = 0.0;
        Prob[hh] = 0.0;
        hru_basin[hh] = hru_area[hh] / basin_area[0];

        if ((hh > 0) && (Ht[hh] < Ht[hh - 1]) && distrib[hh - 1] > 0) {
            CRHMException TExcept(string("'" + Name + " (pbsmSnobal)' vegetation heights not in ascending order.").c_str(), TExcept::WARNING);
            LogError(TExcept);
        }
    }
}

void ClassWQ_pbsmSnobal::run(void) {

    double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
    double SumDrift, SumDrift_mWQ, total, transport, transport_mWQ;

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        if (getstep() == 1)
            for (hh = 0; chkStruct(); ++hh)
                SWE_Init[hh] = SWE[hh];

        if (Sub == 0) // saves all HRUs
            Save();

        for (hh = 0; chkStruct(); ++hh) {

            if (Sub != 0)
                Restore(hh);

            if (variation == VARIATION_ORG || variation == VARIATION_2)
                hru_u_ = hru_u[hh];
            else
                hru_u_ = hru_Uadjust[hh];

            if (variation == VARIATION_2 || variation == VARIATION_3)
                hru_u_ = u_D[hh] * hru_u_;

            Reset_WQ(hh, Drift_in, Drift_in_conc_lay);
            Reset_WQ(hh, Drift_out, Drift_out_conc_lay);
            Reset_WQ(hh, Subl, Subl_conc_lay);

            Drift[hh] = 0.0;
            DriftH[hh] = 0.0;
            SublH[hh] = 0.0;
            Prob[hh] = 0.0;

            if (SWE[hh] > 0.0)
                SWE_conc_lay[Sub][hh] = ((SWE[hh] - net_snow[hh]) * SWE_conc_lay[Sub][hh] + snow_conc_lay[Sub][hh] * net_snow[hh] + atmos_mWQ_lay[Sub][hh]) / SWE[hh]; // netsnow already added in Snobal
            else
                SWE_conc_lay[Sub][hh] = 0.0;

            if (SWE[hh] > 0.0 && !inhibit_bs[hh]) {

                E_StubHt = Ht[hh] - z_s[hh];                      // depths(m)
                if (E_StubHt < 0.0001) E_StubHt = 0.0001;

                Ustar = 0.02264 * pow(hru_u_, 1.295f);            // Eq. 6.2 rev.,  Ustar over fallow

                if (E_StubHt > 0.01) {
                    Znod = (sqr(Ustar) / 163.3f) + 0.5 * N_S[hh] * E_StubHt * A_S[hh]; // Eq. 29, Snowcover Book
                    Lambda = N_S[hh] * A_S[hh] * E_StubHt;                      // Raupach Eq. 1

                    Ustn = Ustar * sqrt((PBSM_constants::Beta * Lambda) / (1.0 + PBSM_constants::Beta * Lambda));

                    Uten_Prob = (log(10.0 / Znod)) / PBSM_constants::KARMAN * sqrt(Ustar - Ustn);
                }
                else
                {
                    Uten_Prob = hru_u_;
                } // end if

                bool newsnow = net_snow[hh]; // attributed with snow_conc_lay

                ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, newsnow, SnowAge[hh], DrySnow[hh]);  // (mm)

                if (Prob[hh] > 0.001) {
                    Ut = Ut * 0.8;

                    double RH = hru_ea[hh] / Common::estar(hru_t[hh]); // Snobal uses Pascals

                    Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, RH, fetch[hh], N_S[hh], A_S[hh]);

                    if (variation == VARIATION_2 || variation == VARIATION_3) {
                        DriftH[hh] = Drift_offset[hh] + DriftH[hh] * Drift_slope[hh];
                        SublH[hh] = Subl_offset[hh] + SublH[hh] * Subl_slope[hh];
                    }

                    Drift_out[hh] = DriftH[hh] * Prob[hh] / fetch[hh];
                    Drift_out_conc_lay[Sub][hh] = SWE_conc_lay[Sub][hh];

                    if (!inhibit_subl[hh]) {
                        Subl[hh] = SublH[hh] * Prob[hh];
                        // assume WQ evaporates slso
                    }

                    // handle insufficient snow pack

                    if (Drift_out[hh] + Subl[hh] > SWE[hh]) {
                        if (Drift_out[hh] >= SWE[hh]) {
                            Drift_out[hh] = SWE[hh];
                            Subl[hh] = 0.0;
                        }
                        else {
                            Subl[hh] = SWE[hh] - Drift_out[hh];
                            // assume WQ evaporates slso
                        }
                    }
                    cumDriftOut_mWQ_lay[Sub][hh] += Drift_out_conc_lay[Sub][hh] * Drift_out[hh];
                    cumDriftOut[hh] += Drift_out[hh];
                    cumSubl[hh] += Subl[hh];
                    cumSubl_mWQ_lay[Sub][hh] += Subl[hh]; // stays behind or sublimates
                }
            } // end if
        } // end for (hh)

   // distribute drift

        if (distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
            double Drft = Drift_out[0] * distrib[0];
            SWE_conc_lay[Sub][0] = SWE_conc_lay[Sub][0] * SWE[0] + Drift_out_conc_lay[Sub][0] * Drft;
            SWE[0] += Drft;
            SWE_conc_lay[Sub][0] /= SWE[0];
            cumDriftIn[0] += Drft;
            cumDriftIn_mWQ_lay[Sub][0] += Drift_out_conc_lay[Sub][0] * Drft;
            cumBasinSnowGain[0] += Drft * hru_basin[0];  // **** hru_basin = hru_area/basin_area ****
        }

        BasinSnowLoss[0] = 0.0;
        long LastN = 0;

        if (!inhibit_bs[0] && nhru == 1) {
            BasinSnowLoss[0] = Drift_out[0];
            BasinSnowLoss_mWQ_lay[Sub][0] += Drift_out_conc_lay[Sub][0] * Drift_out[0];
            cumBasinSnowLoss[0] += BasinSnowLoss[0];
            cumBasinSnowLoss_mWQ_lay[Sub][0] += BasinSnowLoss_mWQ_lay[Sub][0];
        }

        for (long nn = LastN; chkStruct(nn); ++nn) {
            if (distrib[nn] >= 0.0 && nn + 1 < nhru) // skip till last HRU or -ve distribution
                continue;

            SumDrift = 0.0; SumDrift_mWQ = 0.0;
            for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) { // sum drift over range
                SumDrift += Drift_out[hhh] * hru_basin[hhh];
                SumDrift_mWQ += Drift_out[hhh] * hru_basin[hhh] * Drift_out_conc_lay[Sub][hhh];
            }

            if (SumDrift > 0.0) { // drift has occurred!
                for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {

                    if (Ht[hh] > z_s[hh])
                        SWE_max[hh] = SWE[hh] + rho[hh] * (Ht[hh] - z_s[hh]); // not filled
                    else
                        SWE_max[hh] = SWE[hh]; // filled or over filled. Wait for snow transport

                    if (SWE_max[hh] <= 0.0)
                        SWE_max[hh] = Ht[hh];

                    if (hh == nn) { // handle last HRU
                        if (distrib[nn] > 0) {
                            double In = SumDrift / hru_basin[hh]; // remaining drift
                            if (SWE_max[hh] > SWE[hh] + In) { // fill snowpack, remainder leaves basin
                                Drift_in[hh] = In; // can handle all
                                Drift_in_conc_lay[Sub][hh] = SumDrift_mWQ / hru_basin[hh] / In;
                                cumDriftIn[hh] += Drift_in[hh];
                                cumDriftIn_mWQ_lay[Sub][hh] += SumDrift_mWQ / hru_basin[hh];
                                transport = 0.0;
                                transport_mWQ = 0.0;
                            }
                            else if (SWE_max[hh] > SWE[hh]) { // cannot handle all
                                Drift_in[hh] = SWE_max[hh] - SWE[hh];
                                double used = Drift_in[hh] / In;
                                Drift_in_conc_lay[Sub][hh] = SumDrift_mWQ * used / Drift_in[hh];
                                cumDriftIn[hh] += Drift_in[hh];
                                cumDriftIn_mWQ_lay[Sub][hh] += SumDrift_mWQ * used;
                                transport -= (In - (SWE_max[hh] - SWE[hh])) * hru_basin[hh];
                                transport_mWQ -= SumDrift_mWQ * (1.0 - used) * hru_basin[hh];
                            }
                            else { // zero or -ve - happens during melt??
                                transport = SumDrift;
                                transport_mWQ = SumDrift_mWQ;
                            }
                        }
                        else if (distrib[nn] < 0) { // all drift deposited
                            double In = SumDrift / hru_basin[hh]; // remaining drift
                            Drift_in[hh] = SumDrift / hru_basin[hh]; // can handle all
                            Drift_in_conc_lay[Sub][hh] = SumDrift_mWQ / hru_basin[hh] / In;
                            cumDriftIn[hh] += Drift_in[hh];
                            cumDriftIn_mWQ_lay[Sub][hh] += SumDrift_mWQ / hru_basin[hh];
                            transport = 0.0;
                            transport_mWQ = 0.0;
                        }
                        else { // distrib[nn] == 0 -> all excess drift leaves basin
                            transport = SumDrift;
                            transport_mWQ = SumDrift_mWQ;
                        }

                        BasinSnowLoss[0] += (transport + Drift_out[hh] * hru_basin[hh]);
                        BasinSnowLoss_mWQ_lay[Sub][0] += (transport_mWQ + Drift_out_conc_lay[Sub][hh] * Drift_out[hh] * hru_basin[hh]);
                        cumBasinSnowLoss[0] += BasinSnowLoss[0];
                        cumBasinSnowLoss_mWQ_lay[Sub][0] += BasinSnowLoss_mWQ_lay[Sub][0];
                    }
                    else if (SWE_max[hh] > SWE[hh] && distrib[hh] > 0.0) {
                        // handle intermediate HRUs with available storage and distrib > 0
                        total = 0.0;
                        for (long jj = hh; chkStruct(jj, nn + 1); ++jj) // calculate denominator
                            total += fabs(distrib[jj]);
                        // determine contribution and scale
                        transport = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];
                        transport_mWQ = SumDrift_mWQ * fabs(distrib[hh]) / total / hru_basin[hh];
                        if (SWE_max[hh] > SWE[hh] + transport) { // sufficient capacity
                            Drift_in[hh] += transport;
                        }
                        else if (SWE_max[hh] > SWE[hh]) {
                            transport = SWE_max[hh] - SWE[hh];  // insufficient capacity
                            Drift_in[hh] += transport;
                        }
                        else {
                            transport = 0.0;
                            transport_mWQ = 0.0;
                        }

                        SumDrift -= transport * hru_basin[hh]; // remove drift used from total available
                        SumDrift_mWQ -= transport_mWQ * hru_basin[hh]; // remove drift used from total available
                        cumDriftIn[hh] += transport;
                        cumDriftIn_mWQ_lay[Sub][hh] += transport_mWQ;
                    } // end if
                } // end for (hh)
                LastN = nn + 1;
            } // end if
        } // end for (nn)

        for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation
            Drift[hh] = Drift_in[hh] - Drift_out[hh];
            if (SWE[hh] > 0.0) {
                const_cast<long*> (inhibit_evap)[hh] = 1;
                snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
            }
            else {
                const_cast<long*> (inhibit_evap)[hh] = 0;
                snowdepth[hh] = 0.0;
            }
        } // end for (hh)
    } // end for (Sub)
}

void ClassWQ_pbsmSnobal::finish(bool good) {

    if (!good) return;

    double AllcumSubl = 0.0;
    double AllcumCover = cumBasinSnowGain[0] - cumBasinSnowLoss[0];
    long Sub = 0;

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumDriftOut(mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftOut[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh] + cumDriftIn[hh] - cumDriftOut[hh] - cumSubl[hh], hru_area[hh], basin_area[0], "*** SWE just before melt");
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' SWE_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh] - SWE_Init[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");

        AllcumSubl += cumSubl[hh] * hru_area[hh];
        AllcumCover += (cumSno[hh] + cumDriftIn[hh] - cumDriftOut[hh] - cumSubl[hh]) * hru_area[hh];
        LogDebug(" ");

        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumSno_mWQ     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumDriftOut_mWQ(mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftOut_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
        LogMessageA(hh, string("'" + Name + " (WQ_pbsmSnobal)' cumDriftIn_mWQ (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn_mWQ_lay[Sub][hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }

    LogMessage(string("'" + Name + " (WQ_pbsmSnobal)' AllcumSubl  (mm*basin): ").c_str(), AllcumSubl, "*** cumulative sum of all HRUs cumSubl");
    LogMessage(string("'" + Name + " (WQ_pbsmSnobal)' AllcumCover (mm*basin): ").c_str(), AllcumCover, "*** SWE just before melt cumulative sum of all HRUs cumCover");

    LogDebug(" ");
    LogMessage("'WQ_pbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
    LogMessage("'WQ_pbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);

    LogDebug(" ");
    LogMessage("'WQ_pbsm' cumBasinSnowLoss_mWQ (substance) (mm): ", cumBasinSnowLoss_mWQ_lay[Sub][0]);
    LogMessage("'WQ_pbsm' cumBasinSnowGain_mWQ (substance) (mm): ", cumBasinSnowGain_mWQ_lay[Sub][0]);
    LogDebug(" ");
}

void ClassWQ_pbsmSnobal::Reset_WQ(long hru, double* var, double** var_WQ_lay) {
    var[hru] = 0.0;
    for (long Sub = 0; Sub < numsubstances; ++Sub)
        var_WQ_lay[Sub][hru] = 0.0;
}

void ClassWQ_pbsmSnobal::copy_array(double* from, double* to) {
    for (hh = 0; chkStruct(); ++hh)
        to[hh] = from[hh];
}

void ClassWQ_pbsmSnobal::copy_array(long* from, long* to) {
    for (hh = 0; chkStruct(); ++hh)
        to[hh] = from[hh];
}

void ClassWQ_pbsmSnobal::copy_basin(double* from, double* to) {
    to[0] = from[0];
}

void ClassWQ_pbsmSnobal::restore_hru(double* from, double* to, long hh) {
    to[hh] = from[hh];
}

void ClassWQ_pbsmSnobal::restore_hru(long* from, long* to, long hh) {
    to[hh] = from[hh];
}

void ClassWQ_pbsmSnobal::Restore(long hh) {

    restore_hru(DrySnow_0, DrySnow, hh);
    restore_hru(SnowAge_0, SnowAge, hh);

    restore_hru(BasinSnowGain_0, BasinSnowGain, hh);
    restore_hru(cumBasinSnowGain_0, cumBasinSnowGain, hh);
    restore_hru(BasinSnowLoss_0, BasinSnowLoss, hh);
    restore_hru(cumBasinSnowLoss_0, cumBasinSnowLoss, hh);

    restore_hru(SWE_0, SWE, hh);
    restore_hru(SWE_Init_0, SWE_Init, hh);
    restore_hru(cumSno_0, cumSno, hh);
    restore_hru(Drift_in_0, Drift_in, hh);
    restore_hru(cumDriftIn_0, cumDriftIn, hh);
    restore_hru(Drift_out_0, Drift_out, hh); // not used in run
    restore_hru(cumDriftOut_0, cumDriftOut, hh);
    restore_hru(Subl_0, Subl, hh);
    restore_hru(cumSubl_0, cumSubl, hh);
}

void ClassWQ_pbsmSnobal::Save() {

    copy_array(DrySnow, DrySnow_0);
    copy_array(SnowAge, SnowAge_0);

    copy_basin(BasinSnowGain, BasinSnowGain_0);
    copy_basin(cumBasinSnowGain, cumBasinSnowGain_0);
    copy_basin(BasinSnowLoss, BasinSnowLoss_0);
    copy_basin(cumBasinSnowLoss, cumBasinSnowLoss_0);

    copy_array(SWE, SWE_0);
    copy_array(SWE_Init, SWE_Init_0);
    copy_array(cumSno, cumSno_0);
    copy_array(Drift_in, Drift_in_0);
    copy_array(cumDriftIn, cumDriftIn_0);
    copy_array(Drift_out, Drift_out_0);
    copy_array(cumDriftOut, cumDriftOut_0);
    copy_array(Subl, Subl_0);
    copy_array(cumSubl, cumSubl_0);
}