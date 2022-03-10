#include "Class_z_s_rho.h"
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
Class_z_s_rho * Class_z_s_rho :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Class_z_s_rho::klone(string name) const@@@Class_z_s_rho.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Class_z_s_rho::klone(string name) const@@@Class_z_s_rho.cpp>");
    return new Class_z_s_rho (name);
InstrumentLogger::instance()->log_instrument_log("</Class_z_s_rho::klone(string name) const@@@Class_z_s_rho.cpp>");
}
void Class_z_s_rho :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class_z_s_rho::decl(void)@@@Class_z_s_rho.cpp>");
    Description = "'Required when pbsmSnobal used with glacier and glacier_org. Replaces z_s and rho normally supplied by module SnobalCRHM to pbsmSnobal.'";
    declstatvar ("z_s", TDim :: NHRU, "total snowcover thickness", "(m)", & z_s);
    declstatvar ("rho", TDim :: NHRU, "average snowcover density", "(kg/m^3)", & rho);
    declgetvar ("*", "SWE", "(mm)", & SWE);
InstrumentLogger::instance()->log_instrument_log("</Class_z_s_rho::decl(void)@@@Class_z_s_rho.cpp>");
}
void Class_z_s_rho :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class_z_s_rho::init(void)@@@Class_z_s_rho.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; chkStruct (); ++ hh) {
        z_s [hh] = 0.0;
        rho [hh] = 218.0;
    }
InstrumentLogger::instance()->log_instrument_log("</Class_z_s_rho::init(void)@@@Class_z_s_rho.cpp>");
}
void Class_z_s_rho :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Class_z_s_rho::run(void)@@@Class_z_s_rho.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        z_s [hh] = Common :: DepthofSnow (SWE [hh]);
        if (z_s [hh] > 0.0)
        {
            rho [hh] = SWE [hh] / z_s [hh];
        }

        else
        {
            rho [hh] = 218.0;
        }

    }
InstrumentLogger::instance()->log_instrument_log("</Class_z_s_rho::run(void)@@@Class_z_s_rho.cpp>");
}