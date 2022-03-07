#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classquinton.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classquinton * Classquinton :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classquinton::klone(string name) const@@@Classquinton.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classquinton::klone(string name) const@@@Classquinton.cpp>");
    return new Classquinton (name);
InstrumentLogger::instance()->log_instrument_log("</Classquinton::klone(string name) const@@@Classquinton.cpp>");
}
void Classquinton :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classquinton::decl(void)@@@Classquinton.cpp>");
    Description = "'Handles the subsurface drainage from hummock-covered hillslopes in the Arctic tundra. CRHM compatible.' \
                 'using using observation \"p\" original version. ' \
                 'using using variable \"hru_p\" to be CRHM compatible. '";
    Global :: OBS_AS_IS = 1;
    declvar ("Depth", TDim :: NHRU, "water depth above the frost table.", "(m)", & Depth);
    declvar ("theta", TDim :: NLAY, "volumetric soil moisture.", "(m^3/m^3)", & theta, & theta_lay);
    declvar ("layerwater", TDim :: NLAY, "depth of drainable liquid water in layer.", "(m)", & layerwater, & layerwater_lay);
    declvar ("capillary", TDim :: NLAY, "depth of capillary liquid water in layer.", "(m)", & capillary, & capillary_lay);
    declvar ("tension", TDim :: NLAY, "tension in layer.", "(m)", & tension, & tension_lay);
    declvar ("dmelt", TDim :: NHRU, "frost table depth from surface.", "(m)", & dmelt);
    declvar ("k", TDim :: NHRU, "hydraulic conductivity.", "(m/d)", & k);
    declvar ("d_surface", TDim :: NHRU, "water depth used to calculate horizontal hydraulic conductivity.", "(m)", & d_surface);
    declvar ("watertable", TDim :: NHRU, "depth of the water table surface from the ground surface.", "(m)", & watertable);
    declvar ("flowin", TDim :: NHRU, "flow into HRU depth (water only).", "(m/m^2*int)", & flowin);
    declvar ("flowinm3", TDim :: NHRU, "flow into HRU depth.", "(m^3/int)", & flowinm3);
    declvar ("cumflowin", TDim :: NHRU, "cumulative flow into HRU depth (water only).", "(m/m^2)", & cumflowin);
    declvar ("loss", TDim :: NHRU, "water loss from all layers (water only).", "(m/m^2*int)", & loss);
    declvar ("transit", TDim :: NHRU, "transit time through HRU.", "(d)", & transit);
    decllocal ("runoffI", TDim :: NHRU, "runoff from HRU no delay.", "(m/m^2*int)", & runoff);
    declvar ("runoff", TDim :: NHRU, "runoff from HRU delayed (water only).", "(m/m^2*int)", & runoffDly);
    declvar ("runoffm3", TDim :: NHRU, "runoff from HRU delayed.", "(m^3/int)", & runoffm3Dly);
    declvar ("cumrunoff", TDim :: NHRU, "cumulative runoff from HRU delayed.", "(m/m^2)", & cumrunoff);
    decllocal ("flowI", TDim :: NHRU, "flow from all layers no delay.", "(m/m^2*int)", & flow);
    declvar ("flow", TDim :: NHRU, "flow from all layers delayed (water only).", "(m/m^2*int)", & flowDly);
    declvar ("flowm3", TDim :: NHRU, "flow from all layers delayed.", "(m^3/int)", & flowm3Dly);
    declvar ("cumflow", TDim :: NHRU, "cumulative flow from all layers delayed (water only).", "(m/m^2)", & cumflow);
    declvar ("Cvis", TDim :: NLAY, "Heat capacity sat/frozen.", "(J/m^3*K)", & Cvis, & Cvis_lay);
    declvar ("Cvisa", TDim :: NLAY, "Heat capacity unsat/frozen.", "(J/m^3*K)", & Cvisa, & Cvisa_lay);
    declvar ("Cvws", TDim :: NLAY, "Heat capacity sat/unfrozen.", "(J/m^3*K)", & Cvws, & Cvws_lay);
    declvar ("Cvwsa", TDim :: NLAY, "Heat capacity unsat/unfrozen.", "(J/m^3*K)", & Cvwsa, & Cvwsa_lay);
    declvar ("lamis", TDim :: NLAY, "Thermal conductivity sat/frozen.", "(W/m*K)", & lamis, & lamis_lay);
    declvar ("lamws", TDim :: NLAY, "Thermal conductivity sat/unfrozen.", "(W/m*K)", & lamws, & lamws_lay);
    declvar ("lamwsa", TDim :: NLAY, "Thermal conductivity unsat/unfrozen.", "(W/m*K)", & lamwsa, & lamwsa_lay);
    declvar ("wDrained", TDim :: NHRU, "depth of drained frozen organic material from surface.", "(m)", & wDrained);
    decllocal ("tlayer", TDim :: NLAY, "layer temperature.", "(" + string (DEGREE_CELSIUS) + ")", & tlayer, & tlayer_lay);
    declparam ("Type", TDim :: NHRU, "drift, [HUMMOCK]", "0", "2", "hru land type, 0=NOTUSED/1=DRIFT/2=HUMMOCK.", "()", & Type);
    declparam ("DrainTo", TDim :: NHRU, "[0]", "0", "20", " drift drains to hru, 0=NOWHERE, otherwise HRU# (1->MAXHRU).", "()", & DrainTo);
    declparam ("soil_type", TDim :: NLAY, "[0, 1, 2]", "0", "4", "HRU soil type: 0 = loam1, 1 = loam2, 2 = loam3, 3 = sand, 4 = clay.", "()", & soil_type, & soil_type_lay);
    declparam ("Pors", TDim :: NDEF, "0.96, 0.9, 0.87, 0.43, 0.43", "0.0", "1.0", "porosity at layer depths.", "(m^3/m^3)", & Pors, & Pors_def, CLAY + 1);
    declparam ("d", TDim :: NLAY, "[0.15] , [0.1], [0.1] ,[0.1]", "0.0", "100.0", "layer depth.", "(m)", & d, & d_lay);
    declparam ("tinit", TDim :: NLAY, "[-8.0] , [-8.0], [-8.0] ,[-8.0]", "-40.0", "10.0", "initial layer temperature.", "(" + string (DEGREE_CELSIUS) + ")", & tinit, & tinit_lay);
    declparam ("slope", TDim :: NHRU, "[0.01]", "0.0", "1.0", "slope.", "(m/m)", & slope);
    declparam ("length", TDim :: NHRU, "[1]", "1", "1E4", "length normal to creek", "(m)", & length);
    declparam ("K_btm", TDim :: NHRU, "[1.4]", "0.6", "2.5", "horizontal bottom hydraulic conductivity.", "(m/d)", & Kbtm);
    declparam ("K_top", TDim :: NHRU, "[360]", "30", "1200", "horizontal top hydraulic conductivity.", "(m/d)", & Ktop);
    declparam ("z_trn", TDim :: NHRU, "[0.15]", "0.12", "0.18", "hydraulic conductivity transition depth.", "(m)", & ztrn);
    declparam ("Residual", TDim :: NLAY, "[0.5], [0.8], [0.8]", "0.0", "1.0", "Organic non-drainable porosity.", "(m^3/m^3)", & Residual, & Residual_lay);
    declparam ("n", TDim :: NLAY, "[2], [1.6], [1.6]", "0.0", "10.0", "empirical constant.", "()", & n_const, & n_const_lay);
    declparam ("a", TDim :: NLAY, "[25], [15], [15]", "0.0", "50.0", "empirical constant for alpha.", "()", & a_const, & a_const_lay);
    declparam ("Drained", TDim :: NHRU, "[0.0]", "0.0", "1.0", "depth of saturated organic material(ice or water).", "(m)", & Drained);
    declparam ("FrozenTo", TDim :: NHRU, "[0.0]", "0.0", "1.0", "initial depth of frost table.", "(m)", & FrozenTo);
    declparam ("runoffstorage", TDim :: NHRU, "[0]", "0", "20", "runoff Storage.", "(d)", & runoffstorage);
    declparam ("runoffLag", TDim :: NHRU, "[0]", "0", "48", "runoff delay.", "(h)", & runoffLag);
    declparam ("flowstorage", TDim :: NHRU, "[0]", "0", "20", "flow Storage.", "(d)", & flowstorage);
    declparam ("flowLag", TDim :: NHRU, "[0]", "-1", "192", "flow delay.", "(h)", & flowLag);
    declgetvar ("*", "Qg", "(MJ/m^2*d)", & Qg);
    declgetvar ("Qdrift", "driftmelt", "(mm/int)", & driftmelt);
    variation_set = VARIATION_0;
    declreadobs ("p", TDim :: NOBS, "precipitation", "(mm/int)", & p, true);
    variation_set = VARIATION_1;
    declgetvar ("*", "hru_p", "(mm/int)", & hru_p);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</Classquinton::decl(void)@@@Classquinton.cpp>");
}
void Classquinton :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classquinton::init(void)@@@Classquinton.cpp>");
    nlay = getdim (TDim :: NLAY);
    Delayrunoff = new ClassClark (runoff, runoffDly, runoffstorage, runoffLag, nhru);
    Delayflow = new ClassClark (flow, flowDly, flowstorage, flowLag, nhru);
    for (int nn = 0; nn <= CLAY; ++ nn)
        if (Pors_def [nn] [0] > 0.0)
        {
            const_cast < double * > (por_s) [nn] = Pors_def [nn] [0];
        }

    for (hh = 0; chkStruct (); ++ hh) {
        Depth [hh] = 0.0;
        flowin [hh] = 0.0;
        cumflowin [hh] = 0.0;
        flow [hh] = 0.0;
        flowDly [hh] = 0.0;
        cumflow [hh] = 0.0;
        runoff [hh] = 0.0;
        runoffDly [hh] = 0.0;
        cumrunoff [hh] = 0.0;
        loss [hh] = 0.0;
        k [hh] = 0.0;
        d_surface [hh] = 0.0;
        watertable [hh] = 0.0;
        transit [hh] = 0.0;
        dmelt [hh] = FrozenTo [hh];
        double DrainD = Drained [hh];
        bool AsWater = FrozenTo [hh] > Drained [hh];
        if (! AsWater)
        {
            wDrained [hh] = Drained [hh];
        }

        else
        {
            wDrained [hh] = 0.0;
        }

        double d_cum = 0.0;
        for (int nn = 0; nn < nlay; ++ nn) {
            if (Residual_lay [nn] [hh] >= por_s [soil_type_lay [nn] [hh]] && Type [hh] == HUMMOCK)
            {
                string S = "residual cannot be greater or equal to the layer porosity in HRU " + to_string (hh + 1) + ", layer " + to_string (nn + 1);
                CRHMException TExcept (S.c_str (), TExcept :: TERMINATE);
                LogError (TExcept);
            }

            theta_lay [nn] [hh] = 0.0;
            layerwater_lay [nn] [hh] = 0.0;
            capillary_lay [nn] [hh] = 0.0;
            tension_lay [nn] [hh] = 0.0;
            if (AsWater)
            {
                if (Drained [hh] <= d_cum + d_lay [nn] [hh] && Drained [hh] > d_cum)
                {
                    if (FrozenTo [hh] >= d_cum + d_lay [nn] [hh])
                    {
                        capillary_lay [nn] [hh] = (d_cum + d_lay [nn] [hh] - Drained [hh]);
                    }

                    else
                    if (FrozenTo [hh] < d_cum + d_lay [nn] [hh])
                    {
                        capillary_lay [nn] [hh] = (FrozenTo [hh] - Drained [hh]);
                    }

                    Depth [hh] = FrozenTo [hh] - Drained [hh];
                    d_surface [hh] = FrozenTo [hh] - Depth [hh] / 2.0;
                    watertable [hh] = FrozenTo [hh] - Depth [hh];
                }

                else
                if (Drained [hh] < d_cum && FrozenTo [hh] > d_cum)
                {
                    if (FrozenTo [hh] >= d_cum + d_lay [nn] [hh])
                    {
                        capillary_lay [nn] [hh] += d_lay [nn] [hh];
                    }

                    else
                    {
                        capillary_lay [nn] [hh] += FrozenTo [hh] - d_cum;
                    }

                }

            }

            d_cum += d_lay [nn] [hh];
            tlayer_lay [nn] [hh] = tinit_lay [nn] [hh];
            Cvis_lay [nn] [hh] = 0.0;
            Cvisa_lay [nn] [hh] = 0.0;
            Cvws_lay [nn] [hh] = 0.0;
            Cvwsa_lay [nn] [hh] = 0.0;
            lamis_lay [nn] [hh] = 0.0;
            lamws_lay [nn] [hh] = 0.0;
            lamwsa_lay [nn] [hh] = 0.0;
        }
        if (Type [hh] != HUMMOCK)
        {
            continue;
        }

        double c = 0.0;
        d_cum = 0.0;
        double Top;
        double Bot;
        DrainD = Drained [hh];
        for (int nn = 0; nn < nlay; ++ nn) {
            d_cum += d_lay [nn] [hh];
            Top = 0.0;
            Bot = 0.0;
            if (DrainD >= d_cum)
            {
                Top = d_lay [nn] [hh];
            }

            else
            if (DrainD <= (d_cum - d_lay [nn] [hh]))
            {
                Bot = d_lay [nn] [hh];
            }

            else
            {
                Bot = d_cum - DrainD;
                Top = d_lay [nn] [hh] - Bot;
            }

            c += Top * Residual_lay [nn] [hh];
            c += Bot * por_s [soil_type_lay [nn] [hh]];
        }
        LogMessageA (hh, "(Hummock) - water content (m^3) (m/m^2): ", c * length [hh], length [hh]);
    }
InstrumentLogger::instance()->log_instrument_log("</Classquinton::init(void)@@@Classquinton.cpp>");
}
void Classquinton :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classquinton::run(void)@@@Classquinton.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (Type [hh] != HUMMOCK)
        {
            continue;
        }

        for (int nn = 0; nn < nlay; ++ nn) {
            Cvis_lay [nn] [hh] = Cv_i * por_s [soil_type_lay [nn] [hh]] + Cv_s [soil_type_lay [nn] [hh]] * (1.0 - por_s [soil_type_lay [nn] [hh]]);
            Cvisa_lay [nn] [hh] = Cv_i * Residual_lay [nn] [hh] + Cv_s [soil_type_lay [nn] [hh]] * (1.0 - por_s [soil_type_lay [nn] [hh]]) + Cv_a * (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
            Cvws_lay [nn] [hh] = Cv_w * por_s [soil_type_lay [nn] [hh]] + Cv_s [soil_type_lay [nn] [hh]] * (1.0 - por_s [soil_type_lay [nn] [hh]]);
            Cvwsa_lay [nn] [hh] = Cv_w * Residual_lay [nn] [hh] + Cv_s [soil_type_lay [nn] [hh]] * (1.0 - por_s [soil_type_lay [nn] [hh]]) + Cv_a * (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
            double Xs = 1.0 - por_s [soil_type_lay [nn] [hh]];
            double Xw = por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh];
            double Xa = 1.0 - Xs - Xw;
            double n = por_s [soil_type_lay [nn] [hh]];
            double ga;
            if (Xw >= 0.09)
            {
                ga = 0.333 - Xa / n * (0.333 - 0.035);
            }

            else
            {
                ga = 0.013 + 0.944 * Xw;
            }

            double gc = 1.0 - 2.0 * ga;
            double Fs = 1.0 / 3.0 * (2.0 / (1 + (ks_s [soil_type_lay [nn] [hh]] / lam_w - 1.0) * 0.125) + (1.0 / ((1 + (ks_s [soil_type_lay [nn] [hh]] / lam_w - 1.0) * 0.75))));
            double Fa = 1.0 / 3.0 * (2.0 / (1 + (lam_a / lam_w - 1.0) * ga) + (1.0 / ((1 + (lam_a / lam_w - 1.0) * gc))));
            double a = Farouki_a (por_s [soil_type_lay [nn] [hh]]);
            lamis_lay [nn] [hh] = lam_i * a * a + lam_s [soil_type_lay [nn] [hh]] * sqr (1.0 - a) + lam_s [soil_type_lay [nn] [hh]] * lam_i * (2 * a - 2 * sqr (a)) / (lam_s [soil_type_lay [nn] [hh]] * a + lam_i * (1.0 - a));
            lamws_lay [nn] [hh] = lam_w * a * a + lam_s [soil_type_lay [nn] [hh]] * sqr (1.0 - a) + lam_s [soil_type_lay [nn] [hh]] * lam_w * (2 * a - 2 * sqr (a)) / (lam_s [soil_type_lay [nn] [hh]] * a + lam_w * (1.0 - a));
            lamwsa_lay [nn] [hh] = (Xw * lam_w + Fa * Xa * lam_a + Fs * Xs * lam_s [soil_type_lay [nn] [hh]]) / (Xw + Fa * Xa + Fs * Xs);
        }
        double d_cum = 0.0;
        double Top;
        double Bot;
        double DrainD = wDrained [hh];
        if (Qg [hh] > 0.0)
        {
            double Energy = Qg [hh] * 1.0E6;
            for (int nn = 0; nn < nlay; ++ nn) {
                d_cum += d_lay [nn] [hh];
                if (dmelt [hh] >= d_cum)
                {
                    continue;
                }

                Top = 0.0;
                Bot = 0.0;
                if (DrainD - d_cum >= 0.0)
                {
                    Top = d_lay [nn] [hh];
                }

                else
                if (DrainD - (d_cum - d_lay [nn] [hh]) <= 0.0)
                {
                    Bot = d_lay [nn] [hh];
                }

                else
                {
                    Top = DrainD - (d_cum - d_lay [nn] [hh]);
                    Bot = d_cum - DrainD;
                }

                if (Top > 0.0 && dmelt [hh] < d_cum - Bot)
                {
                    double d = Energy / (- tlayer_lay [nn] [hh] * Cvisa_lay [nn] [hh] + Hf * 1e3 * Residual_lay [nn] [hh]);
                    if ((d + dmelt [hh]) > d_cum)
                    {
                        double dif = d_cum - dmelt [hh];
                        double used = (- tlayer_lay [nn] [hh] * Cvisa_lay [nn] [hh] + Hf * 1e3 * Residual_lay [nn] [hh]) * dif;
                        Energy -= used;
                        dmelt [hh] = d_cum;
                        capillary_lay [nn] [hh] += 0.0;
                        continue;
                    }

                    else
                    {
                        dmelt [hh] += d;
                        capillary_lay [nn] [hh] += 0.0;
                        break;
                    }

                }

                if (Bot > 0.0)
                {
                    double d = Energy / (- tlayer_lay [nn] [hh] * Cvis_lay [nn] [hh] + Hf * 1e3 * por_s [soil_type_lay [nn] [hh]]);
                    if ((d + dmelt [hh]) > d_cum)
                    {
                        double dif = d_cum - dmelt [hh];
                        double used = (- tlayer_lay [nn] [hh] * Cvis_lay [nn] [hh] + Hf * 1e3 * por_s [soil_type_lay [nn] [hh]]) * dif;
                        Energy -= used;
                        dmelt [hh] = d_cum;
                        capillary_lay [nn] [hh] += dif;
                    }

                    else
                    {
                        dmelt [hh] += d;
                        capillary_lay [nn] [hh] += d;
                        break;
                    }

                }

            }
        }

        if (wDrained [hh] > 0 && dmelt [hh] >= wDrained [hh])
        {
            wDrained [hh] = 0.0;
        }

        Depth [hh] = 0.0;
        flow [hh] = 0.0;
        d_cum = 0.0;
        for (int nn = 0; nn < nlay; ++ nn) {
            if (dmelt [hh] <= d_cum)
            {
                break;
            }

            d_cum += d_lay [nn] [hh];
            tension_lay [nn] [hh] = 0.0;
            if (n_const_lay [nn] [hh] > 0.001)
            {
                double m = 1.0 - 1.0 / n_const_lay [nn] [hh];
                double alph = a_const_lay [nn] [hh] * m - 1.0;
                double fieldtheta = (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]) * pow (2.0f, - m);
                double thawedthislayer = dmelt [hh] - (d_cum - d_lay [nn] [hh]);
                if (thawedthislayer > d_lay [nn] [hh])
                {
                    thawedthislayer = d_lay [nn] [hh];
                }

                if (capillary_lay [nn] [hh] / thawedthislayer > fieldtheta)
                {
                    double drain = (capillary_lay [nn] [hh] - thawedthislayer * fieldtheta);
                    if (drain > capillary_lay [nn] [hh])
                    {
                        drain = capillary_lay [nn] [hh];
                    }

                    layerwater_lay [nn] [hh] += drain;
                    capillary_lay [nn] [hh] -= drain;
                }

                if (capillary_lay [nn] [hh] > 0.0)
                {
                    double tension;
                    if (d_surface [hh] > d_cum)
                    {
                        tension = (d_surface [hh] - d_cum) + d_lay [nn] [hh];
                    }

                    else
                    if (d_surface [hh] > d_cum - d_lay [nn] [hh])
                    {
                        tension = (d_surface [hh] - (d_cum - d_lay [nn] [hh]));
                    }

                    else
                    {
                        tension = 0.0;
                    }

                    tension_lay [nn] [hh] = tension;
                    if (tension > 1.0 / alph)
                    {
                        double theta = (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]) * pow (1.0f + pow (alph * tension, n_const_lay [nn] [hh]), - m);
                        double excess = capillary_lay [nn] [hh] - theta * d_lay [nn] [hh] / por_s [soil_type_lay [nn] [hh]];
                        if (excess > 0.0)
                        {
                            if (excess >= capillary_lay [nn] [hh])
                            {
                                layerwater_lay [nn] [hh] += capillary_lay [nn] [hh];
                                capillary_lay [nn] [hh] = 0.0;
                            }

                            else
                            {
                                capillary_lay [nn] [hh] -= excess;
                                layerwater_lay [nn] [hh] += excess;
                            }

                        }

                    }

                }

                else
                {
                    layerwater_lay [nn] [hh] += capillary_lay [nn] [hh];
                    capillary_lay [nn] [hh] = 0.0;
                }

            }

            else
            {
                layerwater_lay [nn] [hh] += capillary_lay [nn] [hh];
                capillary_lay [nn] [hh] = 0.0;
            }

            Depth [hh] += layerwater_lay [nn] [hh];
        }
        d_surface [hh] = dmelt [hh] - Depth [hh] / 2.0;
        watertable [hh] = dmelt [hh] - Depth [hh];
        if (d_surface [hh] < 0.0)
        {
            d_surface [hh] = 0.001;
        }

        if (Depth [hh] > 0.0)
        {
            double Y = log (Kbtm [hh]) + (log (Ktop [hh]) - log (Kbtm [hh])) / (1.0f + pow (d_surface [hh] / ztrn [hh], 4.3f));
            double YY = exp (Y);
            k [hh] = exp (Y);
            double kd = k [hh];
            double lasttransit = transit [hh];
            transit [hh] = length [hh] * 24.0 / kd;
            if (lasttransit != transit [hh] && flowLag [hh] > 0.0)
            {
                Delayflow -> ChangeLag (transit, hh);
            }

            double Loss = kd / Global :: Freq * slope [hh] * Depth [hh];
            loss [hh] = Loss;
            for (int nn = 0; nn < nlay; ++ nn) {
                if (layerwater_lay [nn] [hh] > 0.0)
                {
                    double available = layerwater_lay [nn] [hh] * (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                    if (available > Loss)
                    {
                        layerwater_lay [nn] [hh] -= Loss / (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                        flow [hh] += Loss;
                        Loss = 0.0;
                        break;
                    }

                    else
                    {
                        flow [hh] += available;
                        Loss -= available;
                        layerwater_lay [nn] [hh] = 0.0;
                    }

                }

            }
        }

        flowin [hh] = 0.0;
        for (long hhh = 0; hhh < hh; ++ hhh) {
            if (DrainTo [hhh] - 1 == hh)
            {
                if (Type [hhh] == DRIFT)
                {
                    flowin [hh] += driftmelt [hhh] / length [hh];
                }

                else
                if (Type [hhh] == HUMMOCK)
                {
                    flowin [hh] += runoffDly [hhh] * length [hhh] / length [hh];
                    flowin [hh] += flowDly [hhh] * length [hhh] / length [hh];
                }

            }

        }
        if (variation == VARIATION_ORG)
        {
            if (p != NULL)
            {
                flowin [hh] += p [0];
            }

            else
            if (variation == VARIATION_1)
            {
                flowin [hh] += hru_p [0];
            }

        }

        double MINFLOAT = 0.00;
        if (flowin [hh] > MINFLOAT * 2)
        {
            cumflowin [hh] += flowin [hh];
        }

        flowinm3 [hh] = flowin [hh] * length [hh];
        d_cum = 0.0;
        if (flowin [hh] > 0.0)
        {
            double maxdepth;
            double frozmaxdepth;
            runoff [hh] = flowin [hh];
            for (int nn = 0; nn < nlay; ++ nn)
                d_cum += d_lay [nn] [hh];
            for (int nn = nlay - 1; nn >= 0; -- nn) {
                DrainD = wDrained [hh];
                maxdepth = 0.0;
                frozmaxdepth = 0.0;
                if (dmelt [hh] >= d_cum)
                {
                    maxdepth = d_lay [nn] [hh];
                    d_cum -= d_lay [nn] [hh];
                }

                else
                {
                    d_cum -= d_lay [nn] [hh];
                    if (dmelt [hh] <= d_cum)
                    {
                        if (DrainD <= d_cum)
                        {
                            continue;
                        }

                        frozmaxdepth = DrainD - max (dmelt [hh], d_cum);
                    }

                    else
                    {
                        maxdepth = dmelt [hh] - d_cum;
                        if (DrainD > dmelt [hh])
                        {
                            frozmaxdepth = DrainD - dmelt [hh];
                        }

                    }

                }

                if (frozmaxdepth > 1e-6)
                {
                    double froztopup = frozmaxdepth * (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                    if (runoff [hh] > froztopup)
                    {
                        capillary_lay [nn] [hh] += frozmaxdepth;
                        runoff [hh] -= froztopup;
                    }

                    else
                    {
                        frozmaxdepth = runoff [hh] / (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                        capillary_lay [nn] [hh] += frozmaxdepth;
                        runoff [hh] = 0.0;
                        break;
                    }

                }

                if (maxdepth > 1e-6)
                {
                    double topup = (maxdepth - (layerwater_lay [nn] [hh] + capillary_lay [nn] [hh])) * (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                    if (runoff [hh] > topup)
                    {
                        capillary_lay [nn] [hh] += topup / (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                        runoff [hh] -= topup;
                    }

                    else
                    {
                        capillary_lay [nn] [hh] += runoff [hh] / (por_s [soil_type_lay [nn] [hh]] - Residual_lay [nn] [hh]);
                        runoff [hh] = 0.0;
                        break;
                    }

                }

            }
        }

        else
        {
            runoff [hh] = 0.0;
        }

        d_cum = 0.0;
        DrainD = wDrained [hh];
        for (int nn = 0; nn < nlay; ++ nn) {
            d_cum += d_lay [nn] [hh];
            Top = 0.0;
            Bot = 0.0;
            if (DrainD > 0.0)
            {
                if (DrainD >= d_cum)
                {
                    theta_lay [nn] [hh] = Residual_lay [nn] [hh] * por_s [soil_type_lay [nn] [hh]];
                    continue;
                }

                else
                if (DrainD <= (d_cum - d_lay [nn] [hh]))
                {
                    theta_lay [nn] [hh] = por_s [soil_type_lay [nn] [hh]];
                    continue;
                }

                else
                {
                    Top = DrainD - (d_cum - d_lay [nn] [hh]);
                    Bot = d_cum - DrainD;
                }

            }

            else
            {
                if (dmelt [hh] <= d_cum - d_lay [nn] [hh])
                {
                    theta_lay [nn] [hh] = por_s [soil_type_lay [nn] [hh]];
                    continue;
                }

                else
                if (dmelt [hh] >= d_cum && (layerwater_lay [nn] [hh] + capillary_lay [nn] [hh]) <= 0)
                {
                    theta_lay [nn] [hh] = Residual_lay [nn] [hh];
                    continue;
                }

                else
                {
                    if (dmelt [hh] < d_cum)
                    {
                        Bot = d_cum - dmelt [hh];
                    }

                    Top = d_lay [nn] [hh] - Bot;
                }

            }

            theta_lay [nn] [hh] = ((Top * Residual_lay [nn] [hh] + Bot) * por_s [soil_type_lay [nn] [hh]] + capillary_lay [nn] [hh]) / d_lay [nn] [hh];
        }
        Delayflow -> DoClark (hh);
        Delayrunoff -> DoClark (hh);
    }
    for (hh = 0; chkStruct (); ++ hh) {
        if (Type [hh] != HUMMOCK)
        {
            continue;
        }

        cumrunoff [hh] += runoffDly [hh];
        cumflow [hh] += flowDly [hh];
        flowm3Dly [hh] = flowDly [hh] * length [hh];
        runoffm3Dly [hh] = runoffDly [hh] * length [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classquinton::run(void)@@@Classquinton.cpp>");
}
void Classquinton :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classquinton::finish(bool good)@@@Classquinton.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (Type [hh] != HUMMOCK)
        {
            continue;
        }

        double c = 0.0;
        double d_cum = 0.0;
        double Top, Bot;
        double DrainD = wDrained [hh];
        for (int nn = 0; nn < nlay; ++ nn) {
            d_cum += d_lay [nn] [hh];
            Top = 0.0;
            Bot = 0.0;
            if (DrainD > 0.0)
            {
                if (DrainD >= d_cum)
                {
                    Top = d_lay [nn] [hh];
                }

                else
                if (DrainD <= (d_cum - d_lay [nn] [hh]))
                {
                    Bot = d_lay [nn] [hh];
                }

                else
                {
                    Top = DrainD - (d_cum - d_lay [nn] [hh]);
                    Bot = d_cum - DrainD;
                }

            }

            else
            {
                if (dmelt [hh] >= d_cum && (layerwater_lay [nn] [hh] + capillary_lay [nn] [hh]) < 0.0)
                {
                    Top = d_lay [nn] [hh];
                }

                else
                if (dmelt [hh] <= d_cum - d_lay [nn] [hh])
                {
                    Bot = d_lay [nn] [hh];
                }

                else
                {
                    Bot = layerwater_lay [nn] [hh] + capillary_lay [nn] [hh];
                    if (dmelt [hh] < d_cum)
                    {
                        Bot += d_cum - dmelt [hh];
                    }

                    Top = d_lay [nn] [hh] - Bot;
                }

            }

            c += Top * Residual_lay [nn] [hh];
            c += Bot * por_s [soil_type_lay [nn] [hh]];
        }
        LogMessageA (hh, "(Hummock) - water content      (m^3) (m/m^2): ", c * length [hh], length [hh]);
        LogMessageA (hh, "(Hummock) - cumulative flowin  (m^3) (m/m^2): ", cumflowin [hh] * length [hh], length [hh]);
        LogMessageA (hh, "(Hummock) - cumulative flowout (m^3) (m/m^2): ", cumflow [hh] * length [hh], length [hh]);
        LogMessageA (hh, "(Hummock) - flowout in storage (m^3) (m/m^2): ", Delayflow -> Left (hh) * length [hh], length [hh]);
        LogMessageA (hh, "(Hummock) - cumulative runoff  (m^3) (m/m^2): ", cumrunoff [hh] * length [hh], length [hh]);
        LogMessageA (hh, "(Hummock) - runoff in storage  (m^3) (m/m^2): ", Delayrunoff -> Left (hh) * length [hh], length [hh]);
        LogDebug (" ");
    }
    delete Delayflow;
    delete Delayrunoff;
InstrumentLogger::instance()->log_instrument_log("</Classquinton::finish(bool good)@@@Classquinton.cpp>");
}