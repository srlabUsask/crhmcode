#include <algorithm>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "ClassalbedoBaker.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassalbedoBaker * ClassalbedoBaker :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoBaker::klone(string name) const@@@ClassalbedoBaker.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassalbedoBaker::klone(string name) const@@@ClassalbedoBaker.cpp>");
    return new ClassalbedoBaker (name);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoBaker::klone(string name) const@@@ClassalbedoBaker.cpp>");
}
void ClassalbedoBaker :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoBaker::decl(void)@@@ClassalbedoBaker.cpp>");
    Description = "'Calculates snowcover albedo from a method proposed by Baker.'";
    declstatvar ("Albedo", TDim :: NHRU, "Albedo", "()", & Albedo);
    decllocal ("Ab_t", TDim :: NHRU, "timesteps since albedo refresh", "()", & Ab_t);
    decldiagparam ("Albedo_Snow", TDim :: NHRU, "[0.85]", "0.0", "1.0", "Initial albedo for snow cover", "()", & Albedo_Snow);
    decldiagparam ("Albedo_Bare", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", & Albedo_Bare);
    decldiagparam ("refresh", TDim :: NHRU, "[3.0]", "0.0", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", & refresh);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoBaker::decl(void)@@@ClassalbedoBaker.cpp>");
}
void ClassalbedoBaker :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoBaker::init(void)@@@ClassalbedoBaker.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        if (SWE [hh] > 1.0)
        {
            Albedo [hh] = Albedo_Snow [hh];
        }

        else
        {
            Albedo [hh] = Albedo_Bare [hh];
        }

        Ab_t [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoBaker::init(void)@@@ClassalbedoBaker.cpp>");
}
void ClassalbedoBaker :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoBaker::run(void)@@@ClassalbedoBaker.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (SWE [hh] > 1.0)
        {
            if (net_snow [hh] >= refresh [hh])
            {
                Ab_t [hh] = 0;
            }

            else
            {
                Ab_t [hh] = Ab_t [hh] + 1;
            }

            Albedo [hh] = 0.9 - 0.0473 * pow (Ab_t [hh] / Global :: Freq, 0.1f);
            if (Albedo [hh] < Albedo_Bare [hh] || SWE [hh] <= 1.0)
            {
                Albedo [hh] = Albedo_Bare [hh];
            }

        }

        else
        {
            Albedo [hh] = Albedo_Bare [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoBaker::run(void)@@@ClassalbedoBaker.cpp>");
}