#include "Classqdrift.h"
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
Classqdrift * Classqdrift :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classqdrift::klone(string name) const@@@Classqdrift.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classqdrift::klone(string name) const@@@Classqdrift.cpp>");
    return new Classqdrift (name);
InstrumentLogger::instance()->log_instrument_log("</Classqdrift::klone(string name) const@@@Classqdrift.cpp>");
}
void Classqdrift :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classqdrift::decl(void)@@@Classqdrift.cpp>");
    Description = "'Generates the drift melt from hummock-covered hillslopes in the Arctic tundra. CRHM compatible.' \
                 'using using observation \"p\" original version. ' \
                 'using using variable \"hru_p\" to be CRHM compatible. '";
    Global :: OBS_AS_IS = 1;
    declvar ("SWE", TDim :: NHRU, "mean snow water equivalent over HRU", "(mm)", & SWE);
    decllocal ("driftmeltOrg", TDim :: NHRU, "snow melt without delay", "(m^3/int)", & driftmelt);
    declvar ("driftmelt", TDim :: NHRU, "snow melt with delay", "(m^3/int)", & driftmeltDly);
    decllocal ("cumdriftmeltOrg", TDim :: NHRU, "cumulative snow melt", "(km^3)", & cumdriftmelt);
    declvar ("driftmeltD", TDim :: NHRU, "daily snow melt with delay", "(m^3/d)", & driftmeltD);
    declvar ("snowmeltD", TDim :: NHRU, "daily snow melt with delay", "(m^3/d)", & snowmeltD);
    declvar ("cumdriftmelt", TDim :: NHRU, "cumulative snow melt with delay", "(m^3)", & cumdriftmeltDly);
    declparam ("DrainTo", TDim :: NHRU, "[0]", "0", "20", " drift drain to hru, 0=NOWHERE, otherwise HRU# (1->MAXHRU)", "()", & DrainTo);
    declparam ("InitSWE", TDim :: NHRU, "[0.0]", "0", "1E3", "initial mean snow water equivalent", "(mm)", & InitSWE);
    declparam ("length", TDim :: NHRU, "[1]", "1", "1E4", "length normal to creek", "(m)", & length);
    declparam ("meltstorage", TDim :: NHRU, "[0]", "0", "20", "melt Storage", "(d)", & meltstorage);
    declparam ("meltLag", TDim :: NHRU, "[0]", "0", "48", "melt delay", "(h)", & meltLag);
    declgetvar ("*", "Qm", "(MJ/m^2*int)", & Qm);
    variation_set = VARIATION_0;
    declreadobs ("p", TDim :: NOBS, "precipitation", "(mm/int)", & p, true);
    declparam ("Type", TDim :: NHRU, "[NOTUSED]", "0", "2", "hru land type, 0=NOTUSED/1=DRIFT/2=HUMMOCK", "()", & Type);
    variation_set = VARIATION_1;
    declgetvar ("*", "hru_p", "(mm/int)", & hru_p);
    variation_set = VARIATION_ORG;
InstrumentLogger::instance()->log_instrument_log("</Classqdrift::decl(void)@@@Classqdrift.cpp>");
}
void Classqdrift :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classqdrift::init(void)@@@Classqdrift.cpp>");
    nhru = getdim (TDim :: NHRU);
    Delaymelt = new ClassClark (driftmelt, driftmeltDly, meltstorage, meltLag, nhru);
    for (int hh = 0; hh < nhru; ++ hh) {
        driftmelt [hh] = 0.0;
        cumdriftmelt [hh] = 0.0;
        driftmeltDly [hh] = 0.0;
        driftmeltD [hh] = 0.0;
        snowmeltD [hh] = 0.0;
        cumdriftmeltDly [hh] = 0.0;
        SWE [hh] = InitSWE [hh];
        if (hh == 0)
        {
            LogDebugT ("Initial");
        }

        if (variation == VARIATION_0 && Type [hh] != DRIFT)
        {
            continue;
        }

        double c = 0.0;
        if (SWE [hh] > 0.0)
        {
            c = length [hh] * InitSWE [hh] / 1E3;
        }

        LogMessageA (hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length [hh]);
    }
InstrumentLogger::instance()->log_instrument_log("</Classqdrift::init(void)@@@Classqdrift.cpp>");
}
void Classqdrift :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classqdrift::run(void)@@@Classqdrift.cpp>");
    for (int hh = 0; hh < nhru; ++ hh) {
        if ((getstep () % Global :: Freq) == 1)
        {
            driftmeltD [hh] = 0.0;
        }

        if (variation == VARIATION_0 && Type [hh] != DRIFT)
        {
            continue;
        }

        driftmelt [hh] = 0.0;
        if (SWE [hh] > 0.0)
        {
            if (Qm [hh] > 0.0)
            {
                double melt = Qm [hh] / 334.4 * 1E3;
                if (melt > SWE [hh])
                {
                    melt = SWE [hh];
                    SWE [hh] = 0.0;
                }

                else
                {
                    SWE [hh] -= melt;
                }

                double lastcumdriftmelt = cumdriftmelt [hh];
                cumdriftmelt [hh] = length [hh] * InitSWE [hh] * (1.0 - sqr (SWE [hh] / InitSWE [hh]));
                driftmelt [hh] = (cumdriftmelt [hh] - lastcumdriftmelt) / 1E3;
            }

        }

        if (variation == VARIATION_ORG)
        {
            if (p != NULL)
            {
                driftmelt [hh] += (p [0] * length [hh]);
            }

        }

        else
        if (variation == VARIATION_1)
        {
            driftmelt [hh] += (hru_p [0] * length [hh]);
        }

    }
    Delaymelt -> DoClark ();
    for (hh = 0; hh < nhru; ++ hh) {
        if (variation == VARIATION_ORG && Type [hh] != DRIFT)
        {
            continue;
        }

        cumdriftmeltDly [hh] += driftmeltDly [hh];
        driftmeltD [hh] += driftmeltDly [hh];
        snowmeltD [hh] = driftmeltD [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</Classqdrift::run(void)@@@Classqdrift.cpp>");
}
void Classqdrift :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<Classqdrift::finish(bool good)@@@Classqdrift.cpp>");
    for (hh = 0; hh < nhru; ++ hh) {
        if (hh == 0)
        {
            LogDebugT ("Final");
        }

        if (variation == VARIATION_ORG && Type [hh] != DRIFT)
        {
            continue;
        }

        double c = 0.0;
        if (SWE [hh] > 0.0)
        {
            c = length [hh] * InitSWE [hh] * sqr (SWE [hh] / InitSWE [hh]) / 1E3;
        }

        LogMessageA (hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length [hh]);
        LogMessageA (hh, "(Drift  ) - water storage (m^3) (m/m^2): ", Delaymelt -> Left (hh), length [hh]);
        LogDebug (" ");
    }
    delete Delaymelt;
InstrumentLogger::instance()->log_instrument_log("</Classqdrift::finish(bool good)@@@Classqdrift.cpp>");
}