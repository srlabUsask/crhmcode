#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classwalmsley_wind.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classwalmsley_wind * Classwalmsley_wind :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classwalmsley_wind::klone(string name) const@@@Classwalmsley_wind.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classwalmsley_wind::klone(string name) const@@@Classwalmsley_wind.cpp>");
    return new Classwalmsley_wind (name);
InstrumentLogger::instance()->log_instrument_log("</Classwalmsley_wind::klone(string name) const@@@Classwalmsley_wind.cpp>");
}
void Classwalmsley_wind :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwalmsley_wind::decl(void)@@@Classwalmsley_wind.cpp>");
    Description = "'A parametric version of the wind flow model (Mason and Sykes (1979)).'";
    declvar ("hru_Uadjust", TDim :: NHRU, "adjusted wind speed due to topography", "(m/s)", & hru_Uadjust);
    declvar ("hru_Uchange", TDim :: NHRU, "amount of change in wind speed due to topography", "(m/s)", & hru_Uchange);
    decldiag ("WR", TDim :: NHRU, "wind ratio between adjusted wind speed and reference wind speed", "()", & WR);
    declparam ("Zwind", TDim :: NHRU, "[10.0]", "0.0", "100.0", "wind instrument height", "(m)", & Zwind);
    declparam ("A", TDim :: NHRU, "0.0", "0.0", "4.4", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 2.5 = 2D escarpments, 3.0 = 2D hills, 3.5 = 2D rolling terrain, 4.0 = 3D hills, 4.4 = 3D rolling terrain", "()", & Ax);
    declparam ("B", TDim :: NHRU, "0.0", "0.0", "2.0", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 0.8 = 2D escarpments, 1.1 = 3D rolling terrain, 1.55 = 2D rolling terrain, 1.6 = 3D hills, 2.0 = 2D hills", "()", & Bx);
    declparam ("L", TDim :: NHRU, "[1000.0]", "40.0", "1.0E6f", "upwind length at half height", "(m)", & L);
    declparam ("Walmsley_Ht", TDim :: NHRU, "[0]", "-1000.0", "1000.0", "Walmsley height", "(m)", & Walmsley_Ht);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
InstrumentLogger::instance()->log_instrument_log("</Classwalmsley_wind::decl(void)@@@Classwalmsley_wind.cpp>");
}
void Classwalmsley_wind :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwalmsley_wind::init(void)@@@Classwalmsley_wind.cpp>");
    nhru = getdim (TDim :: NHRU);
InstrumentLogger::instance()->log_instrument_log("</Classwalmsley_wind::init(void)@@@Classwalmsley_wind.cpp>");
}
void Classwalmsley_wind :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classwalmsley_wind::run(void)@@@Classwalmsley_wind.cpp>");
    for (int hh = 0; hh < nhru; ++ hh) {
        double Smax = Bx [hh] * Walmsley_Ht [hh] / L [hh];
        double S = Smax * exp (- Ax [hh] * Zwind [hh] / L [hh]);
        hru_Uchange [hh] = S * hru_u [hh];
        hru_Uadjust [hh] = hru_Uchange [hh] + hru_u [hh];
        WR [hh] = hru_Uadjust [hh] / hru_u [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classwalmsley_wind::run(void)@@@Classwalmsley_wind.cpp>");
}