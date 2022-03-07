#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassICEflow.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassICEflow * ClassICEflow :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassICEflow::klone(string name) const@@@ClassICEflow.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::klone(string name) const@@@ClassICEflow.cpp>");
    return new ClassICEflow (name);
InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::klone(string name) const@@@ClassICEflow.cpp>");
}
void ClassICEflow :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassICEflow::decl(void)@@@ClassICEflow.cpp>");
    Description = "'Simulates ICE flow dynamic.'";
    declvar ("Ice_out", TDim :: NHRU, "outgoing iceflow transport", "(mm/int)", & Ice_out);
    declvar ("Ice_in", TDim :: NHRU, "incoming iceflow transport", "(mm/int)", & Ice_in);
    declvar ("Ux", TDim :: NHRU, "plastic flow due to its own weight. Can be channel flow or slab flow(shallow iceflow).", "(m)", & Ux);
    declvar ("Ub", TDim :: NHRU, "velocity due to basal slip", "(m)", & Ub);
    declvar ("Utot", TDim :: NHRU, "sum of plastic deformation and basal slip", "(m)", & Utot);
    declvar ("cumulative_net_rain", TDim :: NHRU, "cumulative meltwater and rain", "(m/yr)", & cumulative_net_rain);
    decldiag ("cumIce_in", TDim :: NHRU, "incoming cumulative Slip transport ice from other HRU", "(mm)", & cumIce_in);
    decldiag ("cumIce_out", TDim :: NHRU, "outgoing cumulative Slip transport ice to other HRU", "(mm)", & cumIce_out);
    declparam ("order", TDim :: NHRU, "[1,2,3,4,5!]", "1", "1000", "sequence of HRUs for iceflow distribution", "()", & order);
    declparam ("Disable_ICEflow", TDim :: NHRU, "[0]", "0", "1", "set to 1 to disable module", "()", & Disable_ICEflow);
    declparam ("distrib_iceflow", TDim :: NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs", "()", & distrib, & distrib_hru, nhru);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("hru_GSL", TDim :: NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string (DEGREE) + ")", & hru_GSL);
    declparam ("SWE_to_firn_Julian", TDim :: NHRU, "[274]", "0", "366", "convert any SWE to firn on Julian day. 0 - inhibit transfer", "()", & SWE_to_firn_Julian);
    declparam ("test_option", TDim :: NHRU, "[-1]", "-1", "100", "negative - disable testing option, >= 0 sets Utot to value of test option.", "(mm)", & test_option);
    declparam ("channel_option", TDim :: NHRU, "[0]", "0", "1", "0 - channel flow, 1 - slab flow.", "()", & channel_option);
    declparam ("basal_option", TDim :: NHRU, "[1]", "1", "2", "1 - u_basal option 1, 2 - u_basal option 2", "()", & basal_option);
    declparam ("radius_glacier", TDim :: NHRU, "[1000]", "100", "10000", "radius of glacier", "(m)", & radius_glacier);
    declparam ("Arrhenius_const", TDim :: NHRU, "[2.935E-17]", "1E-30", "1E-2", "Arrhenius constant", "(1/Pa*yr)", & Arrhenius_const);
    declparam ("slip_sf", TDim :: NHRU, "[0.5]", "0.0", "2.0", "shape factor for the shear stress in channel flow", "()", & slip_sf);
    declparam ("slip_m", TDim :: NHRU, "[3.0]", "0.0", "3.0", "exponent constant for basal slip", "()", & slip_m);
    declparam ("slip_c", TDim :: NHRU, "[0.1]", "0.0", "1.0", "constant for physical characteristics of the bed", "()", & slip_c);
    declparam ("slip_fs", TDim :: NHRU, "[1.8E-12]", "1E-25", "1.0", "sliding parameter from Budd et al. (1979) for basal option 2", "(Pa^-3*m^2*yr)", & slip_fs);
    declputvar ("*", "ice", "(mm)", & ice);
    declgetvar ("*", "firn", "(mm)", & firn);
    declgetvar ("*", "net_rain", "(mm)", & net_rain);
InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::decl(void)@@@ClassICEflow.cpp>");
}
void ClassICEflow :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassICEflow::init(void)@@@ClassICEflow.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Ice_in [hh] = 0.0;
        Ice_out [hh] = 0.0;
        cumIce_in [hh] = 0.0;
        cumIce_out [hh] = 0.0;
        Ux [hh] = 0.0;
        Ub [hh] = 0.0;
        Utot [hh] = 0.0;
        cumulative_net_rain [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::init(void)@@@ClassICEflow.cpp>");
}
void ClassICEflow :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassICEflow::run(void)@@@ClassICEflow.cpp>");
    const double ice_dens = 917;
    const double g = 9.81;
    const double n_Glen = 3;
    const double alpha = M_PI / 180.0;
    const double water_dens = 1000;
    long nstep = getstep () % Global :: Freq;
    for (long hh = 0; chkStruct (hh); ++ hh)
        cumulative_net_rain [hh] += net_rain [hh];
    if (nstep == 0 || Global :: Freq == 1)
    {
        for (long hhh = 0; chkStruct (hhh); ++ hhh) {
            hh = order [hhh] - 1;
            if (Disable_ICEflow [hh])
            {
                continue;
            }

            long Julian = julian ("now");
            if (SWE_to_firn_Julian [hh] == Julian)
            {
                if (hh == 0)
                {
                    for (long mm = 0; chkStruct (mm); ++ mm)
                        Ice_in [mm] = 0.0;
                }

                Ice_out [hh] = 0.0;
                Ux [hh] = 0.0;
                Ub [hh] = 0.0;
                Utot [hh] = 0.0;
                if (test_option [hh] >= 0.0)
                {
                    Utot [hh] = test_option [hh];
                }

                else
                {
                    double ICE = ice [hh] + firn [hh];
                    if (channel_option [hh] == 0)
                    {
                        Ux [hh] = 2 * Arrhenius_const [hh] * pow (slip_sf [hh] * ice_dens * g * sin (hru_GSL [hh] * alpha), n_Glen) * pow (radius_glacier [hh], n_Glen + 1) / (n_Glen + 2);
                    }

                    else
                    {
                        Ux [hh] = 2 * Arrhenius_const [hh] * pow (ice_dens * g * sin (hru_GSL [hh] * alpha), n_Glen) * pow (ICE / ice_dens, n_Glen + 1) / (n_Glen + 2);
                    }

                    double ice_thickness = ICE / ice_dens;
                    double Iw = ice_dens * g * ice_thickness;
                    double tau_b = slip_sf [hh] * ice_dens * g * ice_thickness * sin (hru_GSL [hh] * alpha);
                    if (basal_option [hh] == 1)
                    {
                        double Pw = water_dens * g * cumulative_net_rain [hh] / 1000.0;
                        Ub [hh] = slip_c [hh] * pow (tau_b, slip_m [hh]) / (Iw - Pw);
                    }

                    else
                    {
                        Ub [hh] = slip_fs [hh] * pow (tau_b, slip_m [hh]) / ice_thickness;
                    }

                    Utot [hh] = Ux [hh] + Ub [hh];
                }

                if (Utot [hh] > 0.0)
                {
                    for (long To = 0; chkStruct (To); ++ To) {
                        if (hh != To && Utot [hh] > 0.0 && distrib_hru [hh] [To] > 0.0)
                        {
                            double Amount = Utot [hh] * distrib_hru [hh] [To];
                            Ice_out [hh] = Amount;
                            cumIce_out [hh] += Amount;
                            ice [hh] -= Amount;
                            Amount = Amount * hru_area [hh] / hru_area [To];
                            ice [To] += Amount;
                            Ice_in [To] = Amount;
                            cumIce_in [To] += Amount;
                        }

                    }
                }

                cumulative_net_rain [hh] = 0.0;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::run(void)@@@ClassICEflow.cpp>");
}
void ClassICEflow :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassICEflow::finish(bool good)@@@ClassICEflow.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (ICESlope)' ice        (mm) (mm*hru) (mm*hru/basin): ").c_str (), ice [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (ICESlope)' cumIce_in  (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumIce_in [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (ICESlope)' cumIce_out (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumIce_out [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassICEflow::finish(bool good)@@@ClassICEflow.cpp>");
}