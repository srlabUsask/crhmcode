#include "ClassTs.h"
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
ClassTs * ClassTs :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassTs::klone(string name) const@@@ClassTs.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassTs::klone(string name) const@@@ClassTs.cpp>");
    return new ClassTs (name);
InstrumentLogger::instance()->log_instrument_log("</ClassTs::klone(string name) const@@@ClassTs.cpp>");
}
void ClassTs :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassTs::decl(void)@@@ClassTs.cpp>");
    Description = "'Estimates snow surface temperature from HRU inputs.' \
                 'Tsnow using variable QliVt_Var (W/m^2),' \
                 'Tsnow using observation Qli (W/m^2).'";
    variation_set = VARIATION_ORG;
    declvar ("hru_Ts", TDim :: NHRU, "snow surface temperature", "(°C)", & hru_Ts);
    declobs ("Ts", TDim :: NHRU, "snow surface temperature", "(°C)", & Ts);
    decllocal ("Pa", TDim :: NHRU, "average surface pressure", "(kPa)", & Pa);
    decllocal ("ra", TDim :: NHRU, "", "(s/m)", & ra);
    decllocal ("Qli_", TDim :: NHRU, "", "(W/m^2)", & Qli_);
    declparam ("hru_elev", TDim :: NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", & hru_elev);
    declparam ("Z0snow", TDim :: NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", & Z0snow);
    decldiagparam ("Zref", TDim :: NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", & Zref);
    declparam ("Zwind", TDim :: NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", & Zwind);
    declgetvar ("*", "hru_t", "(°C)", & hru_t);
    declgetvar ("*", "hru_rh", "()", & hru_rh);
    declgetvar ("*", "hru_u", "(m/s)", & hru_u);
    variation_set = VARIATION_0;
    declgetvar ("*", "QliVt_Var", "(W/m^2)", & QliVt_Var);
    variation_set = VARIATION_1;
    declreadobs ("Qli", TDim :: NHRU, "incident long-wave for a flat horizon with vt = 0", "(W/m^2)", & Qli, HRU_OBS_Q);
InstrumentLogger::instance()->log_instrument_log("</ClassTs::decl(void)@@@ClassTs.cpp>");
}
void ClassTs :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassTs::init(void)@@@ClassTs.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        Pa [hh] = 101.3f * pow ((293.0f - 0.0065f * hru_elev [hh]) / 293.0f, 5.26f);
    }
InstrumentLogger::instance()->log_instrument_log("</ClassTs::init(void)@@@ClassTs.cpp>");
}
void ClassTs :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassTs::run(void)@@@ClassTs.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        switch (variation) {
        case VARIATION_ORG:
            Qli_ [hh] = QliVt_Var [hh];
            break;
        case VARIATION_1:
            Qli_ [hh] = Qli [hh];
            break;
        }
        double T1 = hru_t [hh] + CRHM_constants :: Tm;
        double rho = Pa [hh] * 1000 / (CRHM_constants :: Rgas * T1);
        double U1 = max < double > (hru_u [hh], 1.0e-3);
        ra [hh] = (log (Zref [hh] / Z0snow [hh]) * log (Zwind [hh] / Z0snow [hh])) / sqr (CRHM_constants :: kappa) / U1;
        double delta = 0.622 * CRHM_constants :: Ls * Common :: Qs (Pa [hh], T1) / (CRHM_constants :: Rgas * sqr (T1));
        double q = (hru_rh [hh] / 100) * Common :: Qs (Pa [hh], T1);
        Ts [hh] = T1 + (CRHM_constants :: emiss * (Qli_ [hh] - CRHM_constants :: sbc * pow (T1, 4.0f)) + CRHM_constants :: Ls * (q - Common :: Qs (Pa [hh], T1)) * rho / ra [hh]) / (4.0f * CRHM_constants :: emiss * CRHM_constants :: sbc * pow (T1, 3.0f) + (CRHM_constants :: Cp + CRHM_constants :: Ls * delta) * rho / ra [hh]);
        Ts [hh] -= CRHM_constants :: Tm;
        if (Ts [hh] > 0.0)
        {
            Ts [hh] = 0.0;
        }

        hru_Ts [hh] = Ts [hh];
    }
InstrumentLogger::instance()->log_instrument_log("</ClassTs::run(void)@@@ClassTs.cpp>");
}