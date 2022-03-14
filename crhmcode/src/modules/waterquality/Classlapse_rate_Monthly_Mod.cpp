#include "Classlapse_rate_Monthly_Mod.h"
#include "../../core/InstrumentLogger.h"

Classlapse_rate_Monthly_Mod * Classlapse_rate_Monthly_Mod :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<Classlapse_rate_Monthly_Mod::klone(string name) const@@@Classlapse_rate_Monthly_Mod.cpp>");

InstrumentLogger::instance()->log_instrument_log("</Classlapse_rate_Monthly_Mod::klone(string name) const@@@Classlapse_rate_Monthly_Mod.cpp>");
    return new Classlapse_rate_Monthly_Mod (name);
InstrumentLogger::instance()->log_instrument_log("</Classlapse_rate_Monthly_Mod::klone(string name) const@@@Classlapse_rate_Monthly_Mod.cpp>");
}
void Classlapse_rate_Monthly_Mod :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classlapse_rate_Monthly_Mod::decl(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
    declvar ("lapse_rate_Mthly", TDim :: NHRU, "temperature lapse rate Mthly.", "(" + string (DEGREE_CELSIUS) + "/100m)", & lapse_rate_Mthly);
    declvar ("lapse_rate", TDim :: NHRU, "temperature lapse rate.", "(" + string (DEGREE_CELSIUS) + "/100m)", & lapse_rate);
InstrumentLogger::instance()->log_instrument_log("</Classlapse_rate_Monthly_Mod::decl(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
}
void Classlapse_rate_Monthly_Mod :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classlapse_rate_Monthly_Mod::init(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
    for (hh = 0; hh < nhru; ++ hh) {
        lapse_rate [hh] = 0.0;
        lapse_rate_Mthly [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</Classlapse_rate_Monthly_Mod::init(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
}
void Classlapse_rate_Monthly_Mod :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<Classlapse_rate_Monthly_Mod::run(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
    long step = getstep ();
    long nstep = step % Global :: Freq;
    long JULIAN = julian ("now");
    if (nstep == 0)
    {
        for (hh = 0; hh < nhru; ++ hh) {
            if (JULIAN >= 274 && JULIAN < 305)
            {
                lapse_rate [hh] = 0.81;
            }

            else
            if (JULIAN >= 305 && JULIAN < 335)
            {
                lapse_rate [hh] = 0.83;
            }

            else
            if (JULIAN >= 335 && JULIAN < 365)
            {
                lapse_rate [hh] = 0.73;
            }

            else
            if (JULIAN >= 1 && JULIAN < 32)
            {
                lapse_rate [hh] = 0.66;
            }

            else
            if (JULIAN >= 32 && JULIAN < 60)
            {
                lapse_rate [hh] = 0.72;
            }

            else
            if (JULIAN >= 60 && JULIAN < 91)
            {
                lapse_rate [hh] = 0.8;
            }

            else
            if (JULIAN >= 91 && JULIAN < 121)
            {
                lapse_rate [hh] = 0.85;
            }

            else
            if (JULIAN >= 121 && JULIAN < 152)
            {
                lapse_rate [hh] = 0.8;
            }

            else
            if (JULIAN >= 152 && JULIAN < 182)
            {
                lapse_rate [hh] = 0.78;
            }

            else
            if (JULIAN >= 182 && JULIAN < 213)
            {
                lapse_rate [hh] = 0.6;
            }

            else
            if (JULIAN >= 213 && JULIAN < 244)
            {
                lapse_rate [hh] = 0.57;
            }

            else
            if (JULIAN >= 244 && JULIAN < 274)
            {
                lapse_rate [hh] = 0.76;
            }

            lapse_rate_Mthly [hh] = lapse_rate [hh];
        }
    }

InstrumentLogger::instance()->log_instrument_log("</Classlapse_rate_Monthly_Mod::run(void)@@@Classlapse_rate_Monthly_Mod.cpp>");
}