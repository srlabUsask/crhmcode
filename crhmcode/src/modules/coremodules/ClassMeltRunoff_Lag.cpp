#include "ClassMeltRunoff_Lag.h"
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
ClassMeltRunoff_Lag * ClassMeltRunoff_Lag :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassMeltRunoff_Lag::klone(string name) const@@@ClassMeltRunoff_Lag.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassMeltRunoff_Lag::klone(string name) const@@@ClassMeltRunoff_Lag.cpp>");
    return new ClassMeltRunoff_Lag (name);
InstrumentLogger::instance()->log_instrument_log("</ClassMeltRunoff_Lag::klone(string name) const@@@ClassMeltRunoff_Lag.cpp>");
}
void ClassMeltRunoff_Lag :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMeltRunoff_Lag::decl(void)@@@ClassMeltRunoff_Lag.cpp>");
    Description = "'Calculates Melt Runoff.'";
    declvar ("Tf", TDim :: NHRU, "time lag after water percolated snowcover", "()", & Tf);
    decldiag ("In_Lagstorage", TDim :: NHRU, "melt runoff in Lag storage at the beginning of interval!", "(mm)", & In_Lagstorage);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("inhibit_MeltRunoff_Lag", TDim :: NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Lag correction, 1 -> inhibit", "()", & inhibit_MeltRunoff_Lag);
    declputparam ("*", "runLag", "(h)", & runLag);
    declgetvar ("*", "snowmelt_int", "(mm)", & snowmelt_int);
InstrumentLogger::instance()->log_instrument_log("</ClassMeltRunoff_Lag::decl(void)@@@ClassMeltRunoff_Lag.cpp>");
}
void ClassMeltRunoff_Lag :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMeltRunoff_Lag::init(void)@@@ClassMeltRunoff_Lag.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; chkStruct (); ++ hh) {
        Tf [hh] = 0.0;
        In_Lagstorage [hh] = 0.0;
    }
    Netroute_module = (ClassModule *) FindModule_from_parameter ("*", "runKstorage");
InstrumentLogger::instance()->log_instrument_log("</ClassMeltRunoff_Lag::init(void)@@@ClassMeltRunoff_Lag.cpp>");
}
void ClassMeltRunoff_Lag :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassMeltRunoff_Lag::run(void)@@@ClassMeltRunoff_Lag.cpp>");
    for (hh = 0; chkStruct (); ++ hh)
        if (! inhibit_MeltRunoff_Lag [hh])
        {
            if (snowmelt_int [hh] > 0.0)
            {
                Tf [hh] = 250.0 * pow (hru_area [hh], 0.17) * pow (snowmelt_int [hh], - 0.5) / 60.0;
            }

            if (snowmelt_int [hh] <= 0.0)
            {
                Tf [hh] = 0.0;
            }

            In_Lagstorage [hh] = Netroute_module -> Function1 (Tf, hh);
        }

InstrumentLogger::instance()->log_instrument_log("</ClassMeltRunoff_Lag::run(void)@@@ClassMeltRunoff_Lag.cpp>");
}