#include "Classalbedoobs.h"
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
Classalbedoobs * Classalbedoobs :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs::klone(string name) const@@@Classalbedoobs.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs::klone(string name) const@@@Classalbedoobs.cpp>");
    return new Classalbedoobs (name);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs::klone(string name) const@@@Classalbedoobs.cpp>");
}
void Classalbedoobs :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs::decl(void)@@@Classalbedoobs.cpp>");
    Description = "'Every interval sets the variable \"Albedo\" to the value of the observation \"Albedo_obs\".'";
    declvar ("Albedo", TDim :: NHRU, "Albedo", "()", & Albedo);
    decldiagparam ("Albedo_Value", TDim :: NHRU, "[0.17]", "0.0", "1.0", "Albedo", "()", & Albedo_Value);
    declreadobs ("Albedo_obs", TDim :: NHRU, "albedo observation", "()", & Albedo_obs, HRU_OBS_Q, true);
InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs::decl(void)@@@Classalbedoobs.cpp>");
}
void Classalbedoobs :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs::init(void)@@@Classalbedoobs.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Albedo [hh] = Albedo_Value [hh];
    }
    if (Albedo_obs == NULL)
    {
        CRHMException TExcept ("\"albedo_obs\". No observation albedo data!  Using constant parameter value instead.", TExcept :: WARNING);
        LogError (TExcept);
    }

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs::init(void)@@@Classalbedoobs.cpp>");
}
void Classalbedoobs :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classalbedoobs::run(void)@@@Classalbedoobs.cpp>");
    if (Albedo_obs != NULL)
    {
        for (hh = 0; chkStruct (); ++ hh)
            Albedo [hh] = Albedo_obs [hh];
    }

InstrumentLogger::instance()->log_instrument_log("</Classalbedoobs::run(void)@@@Classalbedoobs.cpp>");
}