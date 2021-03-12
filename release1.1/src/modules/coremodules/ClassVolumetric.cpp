//created by Manishankar Mondal

#include "ClassVolumetric.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

ClassVolumetric* ClassVolumetric::klone(string name) const {
    return new ClassVolumetric(name);
}

void ClassVolumetric::decl(void) {

    Description = "'Converts soil moisture to volumetric equivalent and determines fall status.'";

    declvar("Volumetric", TDim::NHRU, "volumetric soil moisture", "()", &Volumetric);

    declvar("Volumetric_rechr", TDim::NHRU, "volumetric soil moisture in soil recharge zone", "()", &Volumetric_rechr); // 04/14/2020: adding option for updating Si or fallstat based on Volumetric moisture content in recharge layer

    declvar("fallstat_V", TDim::NHRU, "fallstat_V copy of parameter fallstat", "()", &fallstat_V);

    declvar("Si_V", TDim::NHRU, "Si_V copy of parameter Si", "()", &Si_V);

    declparam("soil_type", TDim::NHRU, "[4]", "0", "12",
        "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
        " 0 - 12", "()", &soil_type);

    declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0",
        "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone",
        "(mm)", &soil_moist_max);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        " Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//   // 04/14/2020
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

    declparam("soil_Depth", TDim::NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

    declparam("Si_correction", TDim::NHRU, "[0.0]", "0.0", "1.0", "Si correction number", "()", &Si_correction);

    declparam("set_fallstat", TDim::NHRU, "[305]", "0", "366", "set fallstat on this Julian date", "()", &set_fallstat);

    declparam("Volumetric_option", TDim::NHRU, "[1]", "0", "1", "option of setting Si or fallstat: 0 - based on Volumetric moisture content in entire soil column, 1 - based on Volumetric moisture content in soil recharge layer", "()", &Volumetric_option);  // 04/14/2020:

    declputparam("*", "Si", "(mm^3/mm^3)", &Si);

    declputparam("*", "fallstat", "(%)", &fallstat);

    declgetvar("*", "soil_moist", "(mm)", &soil_moist);

    declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);

}

void ClassVolumetric::init(void) {

    for (hh = 0; chkStruct(); ++hh)
        fallstat_V[hh] = 0.0;
}

void ClassVolumetric::run(void) {

    long nstep = getstep() % Global::Freq;
    long Julian = julian("now"); // same as "decday"

    for (hh = 0; chkStruct(); ++hh) {

        Volumetric[hh] = (soil_moist[hh] / soil_Depth[hh] + SetSoilproperties[soil_type[hh]][1]) / 1000.0;

        Volumetric_rechr[hh] = (soil_rechr[hh] / soil_rechr_max[hh] * SetSoilproperties[soil_type[hh]][3] + SetSoilproperties[soil_type[hh]][1]) / 1000.0;  // 04/14/2020

        if (nstep == 0 && set_fallstat[hh] == Julian || (getstep() == 1 && Julian > set_fallstat[hh])) {
            if (Si) {
                double X = 1.0;
                if (SetSoilproperties[soil_type[hh]][3] > 0.0) {
                    if (Volumetric_option[hh])  // 04/14/2020
                        X = Volumetric_rechr[hh] / SetSoilproperties[soil_type[hh]][3] * 1000.0;
                    else
                        X = Volumetric[hh] / SetSoilproperties[soil_type[hh]][3] * 1000.0;
                    X = X - Si_correction[hh];
                }

                if (X < 0.0) {
                    X = 0.0;
                }
                else if (X > 1.0) {
                    X = 1.0;
                }

                Si[hh] = X;
                Si_V[hh] = Si[hh];

            }

            if (fallstat[hh]) 
            {

                if (SetSoilproperties[soil_type[hh]][3] > 0.0)
                {
                    if (Volumetric_option[hh])  // 04/14/2020
                    {
                        fallstat[hh] = Volumetric_rechr[hh] / SetSoilproperties[soil_type[hh]][3] * 100000.0; // ie 100*1000
                    }                        
                    else
                    {
                        fallstat[hh] = Volumetric[hh] / SetSoilproperties[soil_type[hh]][3] * 100000.0; // ie 100*1000
                    }
                }
                else
                {
                    fallstat[hh] = 1.0;
                }

                fallstat_V[hh] = fallstat[hh];
            }
        }
    }
}

