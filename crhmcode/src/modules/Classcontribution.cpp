#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>
#include "Classcontribution.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"
#include "../core/InstrumentLogger.h"

using namespace CRHM;
Classcontribution * Classcontribution :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classcontribution::klone(string name) const@@@Classcontribution.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classcontribution::klone(string name) const@@@Classcontribution.cpp>");
    return new Classcontribution (name);
InstrumentLogger::instance()->log_instrument_log("</Classcontribution::klone(string name) const@@@Classcontribution.cpp>");
}
void Classcontribution :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcontribution::decl(void)@@@Classcontribution.cpp>");
    Description = "'calculates contributing area.'";
    declvar ("contrib_area", TDim :: NHRU, "contributing area", "(mm^2)", & contrib_area);
    declvar ("pre_contrib_area", TDim :: NHRU, "maximum contributing area of HRU before transfer", "(mm^2)", & pre_contrib_area);
    declvar ("connected", TDim :: NHRU, "connected HRUs", "()", & connected);
    declvar ("N_connected", TDim :: NHRU, "number of connected HRUs", "()", & N_connected);
    declvar ("connectedTo", TDim :: NHRU, "connected HRUs", "()", & connectedTo);
    declvar ("Results", TDim :: NDEFN, "calulated distributions", "()", & Results, & Results_lay, nhru);
    decllocal ("distrib_sum", TDim :: NHRU, "HRU distribution sum", "()", & distrib_sum);
    decllocal ("soil_runoff_Buf", TDim :: NHRU, "buffer rain runoff", "(mm/d)", & soil_runoff_Buf);
    declparam ("basin_area", TDim :: BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", & basin_area);
    declparam ("hru_area", TDim :: NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", & hru_area);
    declparam ("Sdmax", TDim :: NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", & Sdmax);
    declparam ("distrib_Route", TDim :: NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", & distrib, & distrib_hru, nhru);
    declparam ("distrib_Basin", TDim :: NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", & distrib_Basin);
    soil_runoffDiv = declgetvar ("*", "soil_runoff", "(mm/int)", & soil_runoff);
    declgetvar ("*", "Sd", "(mm)", & Sd);
InstrumentLogger::instance()->log_instrument_log("</Classcontribution::decl(void)@@@Classcontribution.cpp>");
}
void Classcontribution :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcontribution::init(void)@@@Classcontribution.cpp>");
    if (soil_runoffDiv > 1)
    {
        string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
        CRHMException TExcept (S.c_str (), TExcept :: WARNING);
        LogError (TExcept);
    }

    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        contrib_area [hh] = 0.0;
        pre_contrib_area [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</Classcontribution::init(void)@@@Classcontribution.cpp>");
}
void Classcontribution :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classcontribution::run(void)@@@Classcontribution.cpp>");
    long nstep = getstep () % Global :: Freq;
    if (getstep () == 1)
    {
        for (hh = 0; chkStruct (hh); ++ hh) {
            distrib_sum [hh] = 0.0;
            for (long hhh = 0; chkStruct (hhh); ++ hhh) {
                if (distrib_hru [hh] [hhh] < 0.0)
                {
                    const_cast < double ** > (distrib_hru) [hh] [hhh] = - distrib_hru [hh] [hhh] * hru_area [hh];
                }

                distrib_sum [hh] += distrib_hru [hh] [hhh];
            }
            if (distrib_sum [hh] <= 0 && distrib_Basin [hh] <= 0.0)
            {
                const_cast < double * > (distrib_Basin) [hh] = 1;
            }

            distrib_sum [hh] += distrib_Basin [hh];
        }
    }

    for (hh = 0; chkStruct (hh); ++ hh) {
        if (soil_runoffDiv == 1)
        {
            soil_runoff_Buf [hh] = soil_runoff [hh];
        }

        contrib_area [hh] = hru_area [hh];
        pre_contrib_area [hh] = 0.0;
        connected [hh] = 0.0;
        N_connected [hh] = 0;
        connectedTo [hh] = 0;
        for (long hhh = 0; chkStruct (hhh); ++ hhh)
            Results_lay [hhh] [hh] = 0.0;
    }
    for (hh = 0; chkStruct (hh); ++ hh) {
        for (long hhh = 0; chkStruct (hhh); ++ hhh) {
            if ((Sd [hh] >= Sdmax [hh] || soil_runoff_Buf [hh] > 0.0) && distrib_hru [hh] [hhh] > 0.0)
            {
                Results_lay [hhh] [hh] = distrib_hru [hh] [hhh] - 1;
                connected [hh] += distrib_hru [hh] [hhh];
                connectedTo [hh] = hhh;
            }

        }
    }
    for (long hh = 6; chkStruct (hh); ++ hh) {
        if (connected [hh])
        {
            pre_contrib_area [hh] = contrib_area [hh];
            contrib_area [connectedTo [hh]] += contrib_area [hh];
            contrib_area [hh] = 0.0;
            ++ N_connected [connectedTo [hh]];
            ++ N_connected [nhru - 1];
        }

    }
    double sum2 = 0;
    for (long hh = 6; chkStruct (hh); ++ hh) {
        sum2 += contrib_area [hh];
    }
    if (nstep == 0)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            if (soil_runoffDiv > 1)
            {
                soil_runoff_Buf [hh] = soil_runoff [hh] / soil_runoffDiv;
            }

        }
    }

InstrumentLogger::instance()->log_instrument_log("</Classcontribution::run(void)@@@Classcontribution.cpp>");
}
void Classcontribution :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classcontribution::finish(bool good)@@@Classcontribution.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogMessageA (hh, string ("'" + Name + " (intcp)'  contrib_area  (mm) (mm*hru) (mm*hru/basin): ").c_str (), contrib_area [hh], hru_area [hh], basin_area [0]);
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</Classcontribution::finish(bool good)@@@Classcontribution.cpp>");
}