#include "ClassNO_pbsm.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"
#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include "../../core/InstrumentLogger.h"

using namespace CRHM;
ClassNO_pbsm * ClassNO_pbsm :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassNO_pbsm::klone(string name) const@@@ClassNO_pbsm.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::klone(string name) const@@@ClassNO_pbsm.cpp>");
    return new ClassNO_pbsm (name);
InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::klone(string name) const@@@ClassNO_pbsm.cpp>");
}
void ClassNO_pbsm :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNO_pbsm::decl(void)@@@ClassNO_pbsm.cpp>");
    Description = "'Substitute for pbsm when there is no transport and sublimation.  Alternatve is \"pbsm\" with parameter \"inhibit_bs\" = 1.'";
    declstatvar ("SWE", TDim :: NHRU, "snow water equivalent", "(mm)", & SWE);
    declstatdiag ("cumSno", TDim :: NHRU, "cumulative snow", "(mm)", & cumSno);
    declvar ("snowdepth", TDim :: NHRU, "depth of snow using Gray/Pomeroy", "(m)", & snowdepth);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    decldiagparam ("inhibit_evap", TDim :: NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", & inhibit_evap);
    declgetvar ("*", "hru_newsnow", "()", & hru_newsnow);
    declgetvar ("*", "net_snow", "(mm/int)", & net_snow);
InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::decl(void)@@@ClassNO_pbsm.cpp>");
}
void ClassNO_pbsm :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNO_pbsm::init(void)@@@ClassNO_pbsm.cpp>");
    nhru = getdim (TDim :: NHRU);
    hru_basin = new double [nhru];
    for (hh = 0; hh < nhru; ++ hh) {
        SWE [hh] = 0.0;
        cumSno [hh] = 0.0;
        hru_basin [hh] = hru_area [hh] / basin_area [0];
        snowdepth [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::init(void)@@@ClassNO_pbsm.cpp>");
}
void ClassNO_pbsm :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNO_pbsm::run(void)@@@ClassNO_pbsm.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        if (net_snow [hh] > 0.0)
        {
            SWE [hh] = SWE [hh] + net_snow [hh];
            cumSno [hh] = cumSno [hh] + net_snow [hh];
        }

        if (SWE [hh] > 0.0)
        {
            const_cast < long * > (inhibit_evap) [hh] = 1;
            snowdepth [hh] = Common :: DepthofSnow (SWE [hh]);
        }

        else
        {
            const_cast < long * > (inhibit_evap) [hh] = 0;
            snowdepth [hh] = 0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::run(void)@@@ClassNO_pbsm.cpp>");
}
void ClassNO_pbsm :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassNO_pbsm::finish(bool good)@@@ClassNO_pbsm.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (NO_pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumSno [hh], hru_area [hh], basin_area [0]);
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassNO_pbsm::finish(bool good)@@@ClassNO_pbsm.cpp>");
}