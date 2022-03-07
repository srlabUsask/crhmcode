#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassalbedoRichard.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassalbedoRichard * ClassalbedoRichard :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoRichard::klone(string name) const@@@ClassalbedoRichard.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassalbedoRichard::klone(string name) const@@@ClassalbedoRichard.cpp>");
    return new ClassalbedoRichard (name);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoRichard::klone(string name) const@@@ClassalbedoRichard.cpp>");
}
void ClassalbedoRichard :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoRichard::decl(void)@@@ClassalbedoRichard.cpp>");
    Description = "'Calculates snow cover albedo from a method proposed by R.Essery.'";
    declstatvar ("Albedo", TDim :: NHRU, "Albedo", "()", & Albedo);
    decldiagparam ("Albedo_Snow", TDim :: NHRU, "[0.85]", "0.0", "1.0", "Initial albedo for snow cover", "()", & Albedo_Snow);
    decldiagparam ("Albedo_Bare", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", & Albedo_Bare);
    decldiagparam ("a1", TDim :: NHRU, "[1.08e7]", "0.0", "1.0e8", "Albedo decay time constant for cold snow", "(s)", & a1);
    decldiagparam ("a2", TDim :: NHRU, "[7.2e5]", "0.0", "1.0e8", "Albedo decay time constant for melting snow", "(s)", & a2);
    decldiagparam ("amin", TDim :: NHRU, "[0.5]", "0.0", "1.0", "Minimum albedo for aged snow", "()", & amin);
    decldiagparam ("amax", TDim :: NHRU, "[0.84]", "0.0", "1.0", "Maximum albedo for fresh snow", "()", & amax);
    decldiagparam ("smin", TDim :: NHRU, "[10]", "0.0", "20", "Minimum snowfall to refresh snow albedo", "(mm/int)", & smin);
    declgetvar ("*", "hru_tmean", "(" + string (DEGREE_CELSIUS) + ")", & T0);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoRichard::decl(void)@@@ClassalbedoRichard.cpp>");
}
void ClassalbedoRichard :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoRichard::init(void)@@@ClassalbedoRichard.cpp>");
    dt = 3600 * 24 / Global :: Freq;
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh)
        if (SWE [hh] > 1.0)
        {
            Albedo [hh] = Albedo_Snow [hh];
        }

        else
        {
            Albedo [hh] = Albedo_Bare [hh];
        }

InstrumentLogger::instance()->log_instrument_log("</ClassalbedoRichard::init(void)@@@ClassalbedoRichard.cpp>");
}
void ClassalbedoRichard :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoRichard::run(void)@@@ClassalbedoRichard.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (SWE [hh] > 1.0)
        {
            if (T0 [hh] < 0)
            {
                Albedo [hh] = Albedo [hh] - dt / a1 [hh];
            }

            else
            {
                Albedo [hh] = (Albedo [hh] - amin [hh]) * exp (- dt / a2 [hh]) + amin [hh];
            }

            Albedo [hh] = Albedo [hh] + (amax [hh] - Albedo [hh]) * net_snow [hh] / smin [hh];
            if (Albedo [hh] < amin [hh])
            {
                Albedo [hh] = amin [hh];
            }

            if (Albedo [hh] > amax [hh])
            {
                Albedo [hh] = amax [hh];
            }

        }

        else
        {
            Albedo [hh] = Albedo_Bare [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoRichard::run(void)@@@ClassalbedoRichard.cpp>");
}