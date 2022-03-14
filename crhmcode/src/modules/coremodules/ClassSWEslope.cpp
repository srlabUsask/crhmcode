#include "ClassSWEslope.h"
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
ClassSWEslope * ClassSWEslope :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassSWEslope::klone(string name) const@@@ClassSWEslope.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::klone(string name) const@@@ClassSWEslope.cpp>");
    return new ClassSWEslope (name);
InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::klone(string name) const@@@ClassSWEslope.cpp>");
}
void ClassSWEslope :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSWEslope::decl(void)@@@ClassSWEslope.cpp>");
    Description = "'calculates SWE slope transport (Bernhardt & Schulz, 2010).' \
                 'Standard version for use with the glacier module,' \
                 'Standard version for use without the glacier module. Identical code but links to snowmeltD.'";
    variation_max = VARIATION_1;
    declvar ("SWE_out", TDim :: NHRU, "outgoing snow slide transport SWE", "(mm/int)", & SWE_out);
    declvar ("SWE_in", TDim :: NHRU, "incoming snow slide transport SWE", "(mm/int)", & SWE_in);
    declstatdiag ("cumSWE_in", TDim :: NHRU, "incoming cumulative Slide transport SWE from other HRU", "(mm)", & cumSWE_in);
    declstatdiag ("cumSWE_out", TDim :: NHRU, "outgoing cumulative Slide transport SWE to other HRU", "(mm)", & cumSWE_out);
    declvar ("Hd", TDim :: NHRU, "SWE holding depth of snow", "(mm)", & Hd);
    declparam ("hru_GSL", TDim :: NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string (DEGREE_CELSIUS) + ")", & hru_GSL);
    declparam ("order", TDim :: NHRU, "[1,2,3,4,5!]", "1", "1000", "sequence of HRUs for slide routing ", "()", & order);
    declparam ("Disable_SWEslope", TDim :: NHRU, "[0]", "0", "1", "set to 1 to disable module", "()", & Disable_SWEslope);
    declparam ("Hd_min", TDim :: NHRU, "[50.0]", "0", "750", "minimum SWE holding depth", "(mm)", & Hd_min);
    declparam ("use_rho", TDim :: NHRU, "[1]", "0", "1", "0: user defined snow density, 1: use rho from Snobal", "()", & use_rho);
    declparam ("snow_density", TDim :: NHRU, "[100]", "50", "750", "density of snow", "(kg/m^3)", & snow_density);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("distrib_SWEslope", TDim :: NDEFN, "[0.0]", "0.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs. Source HRU can include itself in the re-distribution", "()", & distrib_SWEslope, & distrib_hru, nhru);
    declputvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "rho", "(kg/m^3)", & rho);
InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::decl(void)@@@ClassSWEslope.cpp>");
}
void ClassSWEslope :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSWEslope::init(void)@@@ClassSWEslope.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        SWE_in [hh] = 0.0;
        SWE_out [hh] = 0.0;
        cumSWE_in [hh] = 0.0;
        cumSWE_out [hh] = 0.0;
        Hd [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::init(void)@@@ClassSWEslope.cpp>");
}
void ClassSWEslope :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSWEslope::run(void)@@@ClassSWEslope.cpp>");
    for (long hh = 0; chkStruct (hh); ++ hh) {
        SWE_in [hh] = 0.0;
        SWE_out [hh] = 0.0;
        Hd [hh] = 0.0;
    }
    for (long hhh = 0; chkStruct (hhh); ++ hhh) {
        if (Disable_SWEslope [hhh])
        {
            continue;
        }

        hh = order [hhh] - 1;
        if (hru_GSL [hh] > 25.0)
        {
            double den_snow;
            if (use_rho [hh])
            {
                den_snow = rho [hh];
            }

            else
            {
                den_snow = snow_density [hh];
            }

            Hd [hh] = 3178.4 * pow (hru_GSL [hh], - 1.998) * den_snow;
            if (Hd [hh] > Hd_min [hh] && SWE [hh] > Hd [hh])
            {
                double Used, total = 0.0;
                double Amount = SWE [hh];
                for (long To = 0; chkStruct (To); ++ To)
                    total += distrib_hru [hh] [To];
                if (total == 0 || total <= distrib_hru [hh] [hh])
                {
                    break;
                }

                for (long To = 0; chkStruct (To); ++ To) {
                    if (hh != To && Amount > 0.0 && distrib_hru [hh] [To] > 0.0)
                    {
                        Used = Amount * distrib_hru [hh] [To] / total;
                        SWE_out [hh] = Used;
                        cumSWE_out [hh] += Used;
                        SWE [hh] -= Used;
                        Used = Used * hru_area [hh] / hru_area [To];
                        SWE [To] += Used;
                        SWE_in [To] = Used;
                        cumSWE_in [To] += Used;
                    }

                }
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::run(void)@@@ClassSWEslope.cpp>");
}
void ClassSWEslope :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassSWEslope::finish(bool good)@@@ClassSWEslope.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (SWESlope)' cumSWE_in (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSWE_in [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (SWESlope)' cumSWE_out (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSWE_out [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassSWEslope::finish(bool good)@@@ClassSWEslope.cpp>");
}