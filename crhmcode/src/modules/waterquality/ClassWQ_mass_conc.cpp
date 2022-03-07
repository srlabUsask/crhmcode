#include "ClassWQ_mass_conc.h"
#include "../../core/InstrumentLogger.h"

ClassWQ_mass_conc * ClassWQ_mass_conc :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::klone(string name) const@@@ClassWQ_mass_conc.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::klone(string name) const@@@ClassWQ_mass_conc.cpp>");
    return new ClassWQ_mass_conc (name);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::klone(string name) const@@@ClassWQ_mass_conc.cpp>");
}
void ClassWQ_mass_conc :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::decl(void)@@@ClassWQ_mass_conc.cpp>");
    Description = "'converts _mWQ to concentrations'";
    declvar ("inflow_conc", TDim :: NDEFN, "Mass: inflow from other HRUs", "(mg)", & inflow_conc, & inflow_conc_lay, numsubstances);
    declvar ("outflow_conc", TDim :: NDEFN, "Mass: inflow from other HRUs", "(mg)", & outflow_conc, & outflow_conc_lay, numsubstances);
    declvar ("runflow_conc", TDim :: NDEFN, "Mass: inflow from other HRUs", "(mg)", & runoutflow_conc, & runoutflow_conc_lay, numsubstances);
    declvar ("ssrflow_conc", TDim :: NDEFN, "Mass: inflow from other HRUs", "(mg)", & ssroutflow_conc, & ssroutflow_conc_lay, numsubstances);
    declvar ("gwoutflow_conc", TDim :: NDEFN, "Mass: inflow from other HRUs", "(mg)", & gwoutflow_conc, & gwoutflow_conc_lay, numsubstances);
    declgetvar ("*", "inflow", "(mm/int)", & inflow);
    declgetvar ("*", "inflow_mWQ", "(mg)", & inflow_mWQ, & inflow_mWQ_lay);
    declgetvar ("*", "outflow", "(mm/int)", & outflow);
    declgetvar ("*", "outflow_mWQ", "(mg)", & outflow_mWQ, & outflow_mWQ_lay);
    declgetvar ("*", "outflow_cWQ", "(mg/l)", & outflow_cWQ, & outflow_cWQ_lay);
    declgetvar ("*", "runoutflow", "(mm/int)", & runoutflow);
    declgetvar ("*", "runoutflow_mWQ", "(mg)", & runoutflow_mWQ, & runoutflow_mWQ_lay);
    declgetvar ("*", "ssroutflow", "(mm/int)", & ssroutflow);
    declgetvar ("*", "ssroutflow_mWQ", "(mg)", & ssroutflow_mWQ, & ssroutflow_mWQ_lay);
    declgetvar ("*", "gwoutflow", "(mm/int)", & gwoutflow);
    declgetvar ("*", "gwoutflow_mWQ", "(mg)", & gwoutflow_mWQ, & gwoutflow_mWQ_lay);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::decl(void)@@@ClassWQ_mass_conc.cpp>");
}
void ClassWQ_mass_conc :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::init(void)@@@ClassWQ_mass_conc.cpp>");
    nhru = getdim (TDim :: NHRU);
    Reset_WQ (inflow_conc_lay);
    Reset_WQ (outflow_conc_lay);
    Reset_WQ (runoutflow_conc_lay);
    Reset_WQ (ssroutflow_conc_lay);
    Reset_WQ (gwoutflow_conc_lay);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::init(void)@@@ClassWQ_mass_conc.cpp>");
}
void ClassWQ_mass_conc :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::run(void)@@@ClassWQ_mass_conc.cpp>");
    mass_to_conc (inflow, inflow_mWQ_lay, inflow_conc_lay);
    mass_to_conc (outflow, outflow_mWQ_lay, outflow_conc_lay);
    mass_to_conc (runoutflow, runoutflow_mWQ_lay, runoutflow_conc_lay);
    mass_to_conc (ssroutflow, ssroutflow_mWQ_lay, ssroutflow_conc_lay);
    mass_to_conc (gwoutflow, gwoutflow_mWQ_lay, gwoutflow_conc_lay);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::run(void)@@@ClassWQ_mass_conc.cpp>");
}
void ClassWQ_mass_conc :: mass_to_conc (const double * var, const double ** var_mWQ, double ** var_conc)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::mass_to_conc(const double * var, const double ** var_mWQ, double ** var_conc)@@@ClassWQ_mass_conc.cpp>");
    for (long Sub = 0; Sub < numsubstances; ++ Sub) {
        for (long hh = 0; hh < nhru; ++ hh) {
            if (var [hh] <= 0.0)
            {
                var_conc [Sub] [hh] = 0.0;
            }

            else
            {
                var_conc [Sub] [hh] = var_mWQ [Sub] [hh] / var [hh];
            }

        }
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::mass_to_conc(const double * var, const double ** var_mWQ, double ** var_conc)@@@ClassWQ_mass_conc.cpp>");
}
void ClassWQ_mass_conc :: Reset_WQ (double ** var_lay)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_mass_conc::Reset_WQ(double ** var_lay)@@@ClassWQ_mass_conc.cpp>");
    for (long hh = 0; hh < nhru; ++ hh) {
        for (long Sub = 0; Sub < numsubstances; ++ Sub)
            var_lay [Sub] [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_mass_conc::Reset_WQ(double ** var_lay)@@@ClassWQ_mass_conc.cpp>");
}