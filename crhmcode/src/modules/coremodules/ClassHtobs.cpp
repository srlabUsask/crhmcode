#include "ClassHtobs.h"
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
ClassHtobs * ClassHtobs :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassHtobs::klone(string name) const@@@ClassHtobs.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassHtobs::klone(string name) const@@@ClassHtobs.cpp>");
    return new ClassHtobs (name);
InstrumentLogger::instance()->log_instrument_log("</ClassHtobs::klone(string name) const@@@ClassHtobs.cpp>");
}
void ClassHtobs :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassHtobs::decl(void)@@@ClassHtobs.cpp>");
    Description = "'Every interval sets the variable \"Ht_var\" to the value of the observation \"Ht_obs\".'";
    declvar ("Ht_var", TDim :: NHRU, "vegetation height", "(m)", & Ht_var);
    declputparam ("*", "Ht", "(m)", & Ht);
    declreadobs ("Ht_obs", TDim :: NHRU, "height observation", "(m)", & Ht_obs, HRU_OBS_misc, true);
InstrumentLogger::instance()->log_instrument_log("</ClassHtobs::decl(void)@@@ClassHtobs.cpp>");
}
void ClassHtobs :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassHtobs::init(void)@@@ClassHtobs.cpp>");
    nhru = getdim (TDim :: NHRU);
    if (Ht_obs == NULL)
    {
        CRHMException TExcept ("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", TExcept :: WARNING);
        LogError (TExcept);
    }

    for (hh = 0; hh < nhru; ++ hh) {
        Ht_var [hh] = Ht [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassHtobs::init(void)@@@ClassHtobs.cpp>");
}
void ClassHtobs :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassHtobs::run(void)@@@ClassHtobs.cpp>");
    if (Ht_obs != NULL)
    {
        for (hh = 0; chkStruct (); ++ hh) {
            double H = Ht_obs [hh];
            if (H < 0.001)
            {
                H = 0.001;
            }

            Ht [hh] = H;
            Ht_var [hh] = Ht [hh];
        }
    }

InstrumentLogger::instance()->log_instrument_log("</ClassHtobs::run(void)@@@ClassHtobs.cpp>");
}