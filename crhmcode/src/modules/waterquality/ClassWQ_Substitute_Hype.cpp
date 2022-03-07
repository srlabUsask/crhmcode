#include "ClassWQ_Substitute_Hype.h"
#include "../../core/InstrumentLogger.h"

ClassWQ_Substitute_Hype * ClassWQ_Substitute_Hype :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Substitute_Hype::klone(string name) const@@@ClassWQ_Substitute_Hype.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::klone(string name) const@@@ClassWQ_Substitute_Hype.cpp>");
    return new ClassWQ_Substitute_Hype (name);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::klone(string name) const@@@ClassWQ_Substitute_Hype.cpp>");
}
void ClassWQ_Substitute_Hype :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Substitute_Hype::decl(void)@@@ClassWQ_Substitute_Hype.cpp>");
    Description = "'Provides necessary Hype variables conc_soil_rechr, conc_soil_lower and conc_soil_moist to run other WQ modules to run without proper Hype module.'";
    declstatvar ("conc_soil_rechr", TDim :: NDEFN, "concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", & conc_soil_rechr, & conc_soil_rechr_lay, numsubstances);
    declstatvar ("conc_soil_lower", TDim :: NDEFN, "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", & conc_soil_lower, & conc_soil_lower_lay, numsubstances);
    declstatvar ("conc_soil_moist", TDim :: NDEFN, "concentration of soluble (reactive) phosphorus, i.e. phosphate in soil moisture per land-soil", "(mg/l)", & conc_soil_moist, & conc_soil_moist_lay, numsubstances);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::decl(void)@@@ClassWQ_Substitute_Hype.cpp>");
}
void ClassWQ_Substitute_Hype :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Substitute_Hype::init(void)@@@ClassWQ_Substitute_Hype.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        for (long Sub = 0; Sub < numsubstances; ++ Sub) {
            conc_soil_rechr_lay [Sub] [hh] = 0.0;
            conc_soil_lower_lay [Sub] [hh] = 0.0;
            conc_soil_moist_lay [Sub] [hh] = 0.0;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::init(void)@@@ClassWQ_Substitute_Hype.cpp>");
}
void ClassWQ_Substitute_Hype :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Substitute_Hype::run(void)@@@ClassWQ_Substitute_Hype.cpp>");
    long step = getstep ();
    long nstep = step % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::run(void)@@@ClassWQ_Substitute_Hype.cpp>");
}
void ClassWQ_Substitute_Hype :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Substitute_Hype::finish(bool good)@@@ClassWQ_Substitute_Hype.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogDebug (" ");
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Substitute_Hype::finish(bool good)@@@ClassWQ_Substitute_Hype.cpp>");
}