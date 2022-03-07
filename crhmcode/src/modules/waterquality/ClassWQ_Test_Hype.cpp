#include "ClassWQ_Test_Hype.h"
#include "../../core/InstrumentLogger.h"

ClassWQ_Test_Hype * ClassWQ_Test_Hype :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Test_Hype::klone(string name) const@@@ClassWQ_Test_Hype.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::klone(string name) const@@@ClassWQ_Test_Hype.cpp>");
    return new ClassWQ_Test_Hype (name);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::klone(string name) const@@@ClassWQ_Test_Hype.cpp>");
}
void ClassWQ_Test_Hype :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Test_Hype::decl(void)@@@ClassWQ_Test_Hype.cpp>");
    Description = "'Provides necessary inputs to test the operation of CRHM and Hype separately.'\
                 'Provides necessary inputs to test WQ_soil, WQ_Netroute and Hype.'\
                 'Provides necessary inputs to test Hype alone.'";
    variation_set = VARIATION_1;
    declvar ("soil_moist", TDim :: NHRU, "moisture content of soil of the HRU.", "(mm)", & soil_moist);
    declvar ("soil_rechr", TDim :: NHRU, "moisture content of soil recharge zone of the HRU.", "(mm)", & soil_rechr);
    declparam ("soil_moist_0", TDim :: NHRU, "[60]", "0", "1000", "initial soil moisture.", "()", & soil_moist_0);
    declparam ("soil_rechr_0", TDim :: NHRU, "[30]", "0", "1000", "initial soil recharge.", "()", & soil_rechr_0);
    declparam ("soil_moist_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile.", "(mm)", & soil_moist_max);
    declparam ("soil_rechr_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", & soil_rechr_max);
    variation_set = VARIATION_ORG;
    declvar ("infil", TDim :: NHRU, "infil", "(mm/int)", & infil);
    declvar ("snowinfil", TDim :: NHRU, "snowinfil", "(mm/int)", & snowinfil);
    declvar ("runoff", TDim :: NHRU, "runoff", "(mm/int)", & runoff);
    declvar ("meltrunoff", TDim :: NHRU, "meltrunoff", "(mm/int)", & meltrunoff);
    declvar ("hru_evap", TDim :: NHRU, "hru_evap", "(mm/int)", & hru_evap);
    declvar ("hru_cum_evap", TDim :: NHRU, "hru_cum_evap", "(mm)", & hru_cum_evap);
    declvar ("hru_cum_actet", TDim :: NHRU, "hru_cum_actet", "(mm)", & hru_cum_actet);
    declvar ("hru_actet", TDim :: NHRU, "hru_actet", "(mm/int)", & hru_actet);
    declvar ("net_rain", TDim :: NHRU, "net_rain", "(mm/int)", & net_rain);
    declvar ("SWE", TDim :: NHRU, "SWE", "(mm)", & SWE);
    declvar ("SWE_max", TDim :: NHRU, "maximum seasonal SWE", "(mm)", & SWE_max);
    declvar ("hru_t", TDim :: NHRU, "hru_t", "(mm/int)", & hru_t);
    declvar ("SWE_conc", TDim :: NDEFN, "SWE_conc", "(mg/l)", & SWE_conc, & SWE_conc_lay, numsubstances);
    declparam ("runoff_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "runoff_0", "(mm/int)", & runoff_0);
    declparam ("infil_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "infil_0", "(mm/int)", & infil_0);
    declparam ("snowinfil_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "snowinfil_0", "(mm/int)", & snowinfil_0);
    declparam ("runoff_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "runoff_0", "(mm/int)", & runoff_0);
    declparam ("meltrunoff_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "meltrunoff_0", "(mm/int)", & meltrunoff_0);
    declparam ("hru_evap_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "hru_evap_0", "(mm/int)", & hru_evap_0);
    declparam ("hru_actet_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "hru_actet_0", "(mm/int)", & hru_actet_0);
    declparam ("hru_cum_evap_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "hru_cum_evap_0", "(mm/int)", & hru_cum_evap_0);
    declparam ("hru_cum_actet_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "hru_cum_actet_0", "(mm/int)", & hru_cum_evap_0);
    declparam ("net_rain_0", TDim :: NHRU, "[0.0]", "0.0", "100.0", "net rain", "(mm/int)", & net_rain_0);
    declparam ("SWE_0", TDim :: NHRU, "[0.0]", "0.0", "500.0", "SWE", "(mm)", & SWE_0);
    declparam ("hru_t_0", TDim :: NHRU, "[20.0]", "-50.0", "100.0", "hru_t_0", "(mm/int)", & hru_t_0);
    declparam ("SWE_conc_0", TDim :: NDEFN, "[0.0]", "0.0", "100.0", "SWE_conc_0", "(mg/l)", & SWE_conc_0, & SWE_conc_lay_0, numsubstances);
    declparam ("Julian_start", TDim :: NHRU, "[30]", "0", "366", "enable input.", "()", & Julian_start);
    declparam ("Julian_end", TDim :: NHRU, "[30]", "0", "366", "disable input.", "()", & Julian_end);
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::decl(void)@@@ClassWQ_Test_Hype.cpp>");
}
void ClassWQ_Test_Hype :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Test_Hype::init(void)@@@ClassWQ_Test_Hype.cpp>");
    nhru = getdim (TDim :: NHRU);
    for (hh = 0; hh < nhru; ++ hh) {
        infil [hh] = 0.0;
        snowinfil [hh] = 0.0;
        runoff [hh] = 0.0;
        meltrunoff [hh] = 0.0;
        hru_evap [hh] = 0.0;
        hru_cum_evap [hh] = 0.0;
        hru_cum_actet [hh] = 0.0;
        hru_actet [hh] = 0.0;
        net_rain [hh] = 0.0;
        SWE [hh] = 0.0;
        SWE_max [hh] = 0.0;
        hru_t [hh] = 0.0;
        SWE_conc [hh] = 0.0;
        if (variation == VARIATION_1)
        {
            soil_moist [hh] = 0.0;
            soil_rechr [hh] = 0.0;
        }

        for (long Sub = 0; Sub < numsubstances; ++ Sub)
            SWE_conc_lay [Sub] [hh] = 0.0;
    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::init(void)@@@ClassWQ_Test_Hype.cpp>");
}
void ClassWQ_Test_Hype :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Test_Hype::run(void)@@@ClassWQ_Test_Hype.cpp>");
    long step = getstep ();
    long nstep = step % Global :: Freq;
    for (hh = 0; chkStruct (); ++ hh) {
        if (nstep == 1)
        {
            if (Julian_start [hh] <= julian ("now") && julian ("now") < Julian_end [hh])
            {
                infil [hh] = infil_0 [hh];
                snowinfil [hh] = snowinfil_0 [hh];
                runoff [hh] = runoff_0 [hh];
                meltrunoff [hh] = meltrunoff_0 [hh];
                hru_t [hh] = hru_t_0 [hh];
                SWE [hh] = SWE_0 [hh];
                SWE_max [hh] = SWE [hh];
                for (long Sub = 0; Sub < numsubstances; ++ Sub)
                    SWE_conc_lay [Sub] [hh] = SWE_conc_lay_0 [Sub] [hh];
                hru_evap [hh] = hru_evap_0 [hh];
                hru_actet [hh] = hru_actet_0 [hh];
                net_rain [hh] = net_rain_0 [hh];
                if (variation == VARIATION_1)
                {
                    soil_moist [hh] = soil_moist_0 [hh];
                    soil_rechr [hh] = soil_moist_0 [hh];
                }

            }

            else
            {
                infil [hh] = 0.0;
                snowinfil [hh] = 0.0;
                runoff [hh] = 0.0;
                meltrunoff [hh] = 0.0;
                hru_evap [hh] = 0.0;
                hru_cum_evap [hh] = 0.0;
                hru_cum_actet [hh] = 0.0;
                hru_actet [hh] = 0.0;
                net_rain [hh] = 0.0;
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::run(void)@@@ClassWQ_Test_Hype.cpp>");
}
void ClassWQ_Test_Hype :: finish (bool good)
{
InstrumentLogger::instance()->log_instrument_log("<ClassWQ_Test_Hype::finish(bool good)@@@ClassWQ_Test_Hype.cpp>");
    for (hh = 0; chkStruct (); ++ hh) {
        LogDebug (" ");
    }
    LogDebug (" ");
InstrumentLogger::instance()->log_instrument_log("</ClassWQ_Test_Hype::finish(bool good)@@@ClassWQ_Test_Hype.cpp>");
}