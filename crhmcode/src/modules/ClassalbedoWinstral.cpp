#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "ClassalbedoWinstral.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
ClassalbedoWinstral * ClassalbedoWinstral :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoWinstral::klone(string name) const@@@ClassalbedoWinstral.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::klone(string name) const@@@ClassalbedoWinstral.cpp>");
    return new ClassalbedoWinstral (name);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::klone(string name) const@@@ClassalbedoWinstral.cpp>");
}
void ClassalbedoWinstral :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoWinstral::decl(void)@@@ClassalbedoWinstral.cpp>");
    Description = "'Incomplete code to calculate snowcover albedo from a method proposed by Winstral.'";
    declstatvar ("Albedo", TDim :: NHRU, "Albedo", "()", & Albedo);
    declstatdiag ("Ab_t", TDim :: NHRU, "steps since albedo refresh", "()", & Ab_t);
    decllocal ("irdalb", TDim :: NHRU, "ir_diffuse decay", "()", & irdalb);
    decllocal ("vddalb", TDim :: NHRU, "visible_diffuse decay", "()", & vdalb);
    decldiagparam ("maxdecay", TDim :: NHRU, "[0.25]", "0.1", "0.5", "maximum decay", "()", & maxdecay);
    decldiagparam ("power", TDim :: NHRU, "[1.4]", "-2.0", "2.0", "power function", "()", & power);
    decldiagparam ("decay_period", TDim :: NHRU, "[5000]", "100", "20000", "time over albedo decays", "()", & decay_period);
    decldiagparam ("refresh", TDim :: NHRU, "[1.0]", "0.5", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", & refresh);
    decldiagparam ("Albedo_Bare", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", & Albedo_Bare);
    declgetvar ("*", "SWE", "(mm)", & SWE);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::decl(void)@@@ClassalbedoWinstral.cpp>");
}
void ClassalbedoWinstral :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoWinstral::init(void)@@@ClassalbedoWinstral.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Ab_t [hh] = 0;
        irdalb [hh] = 0.24;
        vdalb [hh] = 0.02;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::init(void)@@@ClassalbedoWinstral.cpp>");
}
void ClassalbedoWinstral :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoWinstral::run(void)@@@ClassalbedoWinstral.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (SWE [hh] > refresh [hh])
        {
            if (net_snow [hh] >= refresh [hh])
            {
                Ab_t [hh] = 0;
            }

            else
            {
                Ab_t [hh] = Ab_t [hh] + 24.0 / Global :: Freq;
            }

            irdalb [hh] = 0.24 + pow (Ab_t [hh] / decay_period [hh], power [hh]) * maxdecay [hh];
            vdalb [hh] = 0.02 + pow (Ab_t [hh] / decay_period [hh], power [hh]) * maxdecay [hh];
            Albedo [hh] = (1.0 - vdalb [hh]) * 0.48 + (1.0 - irdalb [hh]) * 0.52;
        }

        else
        {
            Albedo [hh] = Albedo_Bare [hh];
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::run(void)@@@ClassalbedoWinstral.cpp>");
}
void ClassalbedoWinstral :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassalbedoWinstral::finish(bool good)@@@ClassalbedoWinstral.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        string s = "'" + Name + " (albedo_Winstral)' ";
        LogMessage (hh, s.c_str ());
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassalbedoWinstral::finish(bool good)@@@ClassalbedoWinstral.cpp>");
}