#include "ClassVolumetric.h"
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
ClassVolumetric * ClassVolumetric :: klone (string name) const
{
InstrumentLogger::instance()->log_instrument_log("<ClassVolumetric::klone(string name) const@@@ClassVolumetric.cpp>");

InstrumentLogger::instance()->log_instrument_log("</ClassVolumetric::klone(string name) const@@@ClassVolumetric.cpp>");
    return new ClassVolumetric (name);
InstrumentLogger::instance()->log_instrument_log("</ClassVolumetric::klone(string name) const@@@ClassVolumetric.cpp>");
}
void ClassVolumetric :: decl (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVolumetric::decl(void)@@@ClassVolumetric.cpp>");
    Description = "'Converts soil moisture to volumetric equivalent and determines fall status.'";
    declvar ("Volumetric", TDim :: NHRU, "volumetric soil moisture", "()", & Volumetric);
    declvar ("fallstat_V", TDim :: NHRU, "fallstat_V copy of parameter fallstat", "()", & fallstat_V);
    declvar ("Si_V", TDim :: NHRU, "Si_V copy of parameter Si", "()", & Si_V);
    declparam ("soil_type", TDim :: NHRU, "[4]", "0", "12", "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement"
        " 0 - 12", "()", & soil_type);
    declparam ("soil_moist_max", TDim :: NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."
        "Soil profile is surface to bottom of rooting zone", "(mm)", & soil_moist_max);
    declparam ("soil_Depth", TDim :: NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", & soil_Depth);
    declparam ("Si_correction", TDim :: NHRU, "[0.0]", "0.0", "1.0", "Si correction number", "()", & Si_correction);
    declparam ("set_fallstat", TDim :: NHRU, "[305]", "0", "366", "set fallstat on this Julian date", "()", & set_fallstat);
    declparam ("Si", TDim :: NHRU, "[0.5]", "0.0", "1.0", "initial soil saturation (0 - 0.4m)", "(mm^3/mm^3)", & Si);
    declputparam ("*", "fallstat", "(%)", & fallstat);
    declgetvar ("*", "soil_moist", "(mm)", & soil_moist);
InstrumentLogger::instance()->log_instrument_log("</ClassVolumetric::decl(void)@@@ClassVolumetric.cpp>");
}
void ClassVolumetric :: init (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVolumetric::init(void)@@@ClassVolumetric.cpp>");
    for (hh = 0; chkStruct (); ++ hh)
        fallstat_V [hh] = 0.0;
InstrumentLogger::instance()->log_instrument_log("</ClassVolumetric::init(void)@@@ClassVolumetric.cpp>");
}
void ClassVolumetric :: run (void)
{
InstrumentLogger::instance()->log_instrument_log("<ClassVolumetric::run(void)@@@ClassVolumetric.cpp>");
    long nstep = getstep () % Global :: Freq;
    long Julian = julian ("now");
    for (hh = 0; chkStruct (); ++ hh) {
        Volumetric [hh] = (soil_moist [hh] / soil_Depth [hh] + SetSoilproperties [soil_type [hh]] [1]) / 1000.0;
        if (nstep == 0 && set_fallstat [hh] == Julian || (getstep () == 1 && Julian > set_fallstat [hh]))
        {
            if (Si)
            {
                double X = 1.0;
                if (SetSoilproperties [soil_type [hh]] [3] > 0.0)
                {
                    X = Volumetric [hh] / SetSoilproperties [soil_type [hh]] [3] * 1000.0;
                    X = X - Si_correction [hh];
                }

                if (X < 0.0)
                {
                    X = 0.0;
                }

                else
                if (X > 1.0)
                {
                    X = 1.0;
                    const_cast < double * > (Si) [hh] = X;
                    Si_V [hh] = Si [hh];
                }

            }

            if (fallstat [hh])
            {
                if (SetSoilproperties [soil_type [hh]] [3] > 0.0)
                {
                    fallstat [hh] = Volumetric [hh] / SetSoilproperties [soil_type [hh]] [3] * 100000.0;
                }

                else
                {
                    fallstat [hh] = 1.0;
                }

                fallstat_V [hh] = fallstat [hh];
            }

        }

    }
InstrumentLogger::instance()->log_instrument_log("</ClassVolumetric::run(void)@@@ClassVolumetric.cpp>");
}