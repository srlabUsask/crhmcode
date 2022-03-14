#include "ClassXGAyers.h"
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
ClassXGAyers * ClassXGAyers :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassXGAyers::klone(string name) const@@@ClassXGAyers.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::klone(string name) const@@@ClassXGAyers.cpp>");
    return new ClassXGAyers (name);
InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::klone(string name) const@@@ClassXGAyers.cpp>");
}
void ClassXGAyers :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXGAyers::decl(void)@@@ClassXGAyers.cpp>");
    Description = "'Snow melt handled by XG and and Ayers, .'";
    declvar ("infil", TDim :: NHRU, "Potential rain infiltration", "(mm/int)", & infil);
    declstatdiag ("cuminfil", TDim :: NHRU, "cumulative potential rain infiltration", "(mm)", & cuminfil);
    declvar ("snowinfil", TDim :: NHRU, "melt infiltration", "(mm/int)", & snowinfil);
    declstatvar ("cumsnowinfil", TDim :: NHRU, "cumulative melt infiltration", "(mm)", & cumsnowinfil);
    declvar ("meltrunoff", TDim :: NHRU, "melt runoff = 0.0", "(mm/int)", & meltrunoff);
    declstatdiag ("cummeltrunoff", TDim :: NHRU, "cumulative melt runoff = 0.0", "(mm)", & cummeltrunoff);
    declvar ("runoff", TDim :: NHRU, "rainfall runoff", "(mm/int)", & runoff);
    declstatdiag ("cumrunoff", TDim :: NHRU, "cumulative rainfall runoff", "(mm)", & cumrunoff);
    declparam ("texture", TDim :: NHRU, "[1]", "1", "4", "texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", & texture);
    declparam ("groundcover", TDim :: NHRU, "[1]", "1", "6", "groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", & groundcover);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declgetvar ("*", "snowmeltD", "(mm/d)", & snowmeltD);
    declgetvar ("*", "net_rain", "(mm/int)", & net_rain);
InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::decl(void)@@@ClassXGAyers.cpp>");
}
void ClassXGAyers :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXGAyers::init(void)@@@ClassXGAyers.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        infil [hh] = 0.0;
        runoff [hh] = 0.0;
        snowinfil [hh] = 0.0;
        meltrunoff [hh] = 0.0;
        cuminfil [hh] = 0.0;
        cumsnowinfil [hh] = 0.0;
        cummeltrunoff [hh] = 0.0;
        cumrunoff [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::init(void)@@@ClassXGAyers.cpp>");
}
void ClassXGAyers :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXGAyers::run(void)@@@ClassXGAyers.cpp>");
    long nstep = getstep () % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        infil [hh] = 0.0;
        runoff [hh] = 0.0;
        if (net_rain [hh] > 0.0)
        {
            double maxinfil = textureproperties [texture [hh] - 1] [groundcover [hh] - 1] * 24.0 / Global :: Freq;
            if (maxinfil > net_rain [hh])
            {
                infil [hh] = net_rain [hh];
            }

            else
            {
                infil [hh] = maxinfil;
                runoff [hh] = net_rain [hh] - maxinfil;
            }

            cuminfil [hh] += infil [hh];
            cumrunoff [hh] += runoff [hh];
        }

        snowinfil [hh] = 0.0;
        meltrunoff [hh] = snowmeltD [hh] / Global :: Freq;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::run(void)@@@ClassXGAyers.cpp>");
}
void ClassXGAyers :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassXGAyers::finish(bool good)@@@ClassXGAyers.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (frozenAyers)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumsnowinfil [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (frozenAyers)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str (), cummeltrunoff [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (frozenAyers)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str (), cuminfil [hh], hru_area [hh], basin_area [0]);
        LogMessageA (hh, string ("'" + Name + " (frozenAyers)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str (), cumrunoff [hh], hru_area [hh], basin_area [0]);
        LogDebug (" ");
    }
InstrumentLogger::instance()->log_instrument_log("</ClassXGAyers::finish(bool good)@@@ClassXGAyers.cpp>");
}