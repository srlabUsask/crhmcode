#include "ClassWQ_Gen_Mass_Var_Netroute.h"
#include "../../core/InstrumentLogger.h"

ClassWQ_Gen_Mass_Var_Netroute * ClassWQ_Gen_Mass_Var_Netroute :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Gen_Mass_Var_Netroute::klone(string name) const@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::klone(string name) const@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
    return new ClassWQ_Gen_Mass_Var_Netroute (name);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::klone(string name) const@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
}
void ClassWQ_Gen_Mass_Var_Netroute :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Gen_Mass_Var_Netroute::decl(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
    Description = "'Generates variable mWQ balances in Netroute*.'";
    declvar ("basinflow_change_mWQ", TDim :: NDEFN, "mass of solute basinflow change.", "(mg)", & basinflow_change_mWQ, & basinflow_change_mWQ_lay, numsubstances);
    declvar ("basingw_change_mWQ", TDim :: NDEFN, "mass of solute basingwflow change.", "(mg)", & basingw_change_mWQ, & basingw_change_mWQ_lay, numsubstances);
    declvar ("outflow_diverted_change_mWQ", TDim :: NDEFN, "mass of solute outflow_diverted change.", "(mg)", & outflow_diverted_change_mWQ, & outflow_diverted_change_mWQ_lay, numsubstances);
    declvar ("gwoutflow_diverted_change_mWQ", TDim :: NDEFN, "mass of solute outflow_diverted change.", "(mg)", & gwoutflow_diverted_change_mWQ, & gwoutflow_diverted_change_mWQ_lay, numsubstances);
    declvar ("basinflow_conc_last", TDim :: NDEFN, "last mass of solute basinflow.", "(mg)", & basinflow_mWQ_last, & basinflow_mWQ_lay_last, numsubstances);
    declvar ("basingw_conc_last", TDim :: NDEFN, "last mass of solute basin gw flow.", "(mg)", & basingw_mWQ_last, & basingw_mWQ_lay_last, numsubstances);
    declvar ("outflow_diverted_conc_last", TDim :: NDEFN, "last mass of solute outflow_diverted.", "(mg)", & outflow_diverted_mWQ_last, & outflow_diverted_mWQ_lay_last, numsubstances);
    declvar ("gwoutflow_diverted_conc_last", TDim :: NDEFN, "last mass of solute outflow_diverted.", "(mg)", & gwoutflow_diverted_mWQ_last, & gwoutflow_diverted_mWQ_lay_last, numsubstances);
    declputvar ("*", "basinflow", "(mm)", & basinflow);
    declputvar ("*", "basinflow_conc", "(mg/l)", & basinflow_conc, & basinflow_conc_lay);
    declputvar ("*", "basingw", "(mm)", & basingw);
    declputvar ("*", "basingw_conc", "(mg/l)", & basingw_conc, & basingw_conc_lay);
    declputvar ("*", "outflow_diverted", "(mm)", & outflow_diverted);
    declputvar ("*", "outflow_diverted_conc", "(mg/l)", & outflow_diverted_conc, & outflow_diverted_conc_lay);
    declputvar ("*", "gwoutflow_diverted", "(mm)", & gwoutflow_diverted);
    declputvar ("*", "gwoutflow_diverted_conc", "(mg/l)", & gwoutflow_diverted_conc, & gwoutflow_diverted_conc_lay);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::decl(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
}
void ClassWQ_Gen_Mass_Var_Netroute :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Gen_Mass_Var_Netroute::init(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (long Sub = 0; Sub < numsubstances; ++ Sub) {
        basinflow_change_mWQ_lay [Sub] [0] = 0.0;
        basinflow_mWQ_lay_last [Sub] [0] = 0.0;
        basingw_change_mWQ_lay [Sub] [0] = 0.0;
        basingw_mWQ_lay_last [Sub] [0] = 0.0;
        for (hh = 0; chkStruct (); ++ hh) {
            outflow_diverted_change_mWQ_lay [Sub] [hh] = 0.0;
            outflow_diverted_mWQ_lay_last [Sub] [hh] = outflow_diverted [hh] * outflow_diverted_conc_lay [Sub] [hh];
            gwoutflow_diverted_change_mWQ_lay [Sub] [hh] = 0.0;
            gwoutflow_diverted_mWQ_lay_last [Sub] [hh] = gwoutflow_diverted [hh] * gwoutflow_diverted_conc_lay [Sub] [hh];
        }
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::init(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
}
void ClassWQ_Gen_Mass_Var_Netroute :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Gen_Mass_Var_Netroute::run(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
    double temp;
    for (long Sub = 0; Sub < numsubstances; ++ Sub) {
        temp = basinflow [0] * basinflow_conc_lay [Sub] [0];
        basinflow_change_mWQ_lay [Sub] [0] = temp - basinflow_mWQ_lay_last [Sub] [0];
        basinflow_mWQ_lay_last [Sub] [0] = temp;
        temp = basingw [0] * basingw_conc_lay [Sub] [0];
        basingw_change_mWQ_lay [Sub] [0] = temp - basingw_mWQ_lay_last [Sub] [0];
        basingw_mWQ_lay_last [Sub] [0] = temp;
        for (hh = 0; chkStruct (); ++ hh) {
            temp = outflow_diverted [hh] * outflow_diverted_conc_lay [Sub] [hh];
            outflow_diverted_change_mWQ_lay [Sub] [hh] = temp - outflow_diverted_mWQ_lay_last [Sub] [hh];
            outflow_diverted_mWQ_lay_last [Sub] [hh] = temp;
            temp = gwoutflow_diverted_conc_lay [Sub] [hh];
            gwoutflow_diverted_change_mWQ_lay [Sub] [hh] = temp - gwoutflow_diverted_mWQ_lay_last [Sub] [hh];
            gwoutflow_diverted_mWQ_lay_last [Sub] [hh] = temp;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::run(void)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
}
void ClassWQ_Gen_Mass_Var_Netroute :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Gen_Mass_Var_Netroute::finish(bool good)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
    LogDebug ("**WQ_Gen_Mass_Var_Netroute**");
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Gen_Mass_Var_Netroute::finish(bool good)@@@ClassWQ_Gen_Mass_Var_Netroute.cpp>");
}