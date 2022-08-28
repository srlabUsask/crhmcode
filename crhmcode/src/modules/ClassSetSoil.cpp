//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassSetSoil.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassSetSoil* ClassSetSoil::klone(string name) const {
    return new ClassSetSoil(name);
}

void ClassSetSoil::decl(void) {

    Description = "'Initialises module \"soil\", soil moisture variables from \"Vol_h2o_content\" and depth parameters.'";

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string(DEGREE) + ")", &hru_lat);

    declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

    declparam("hru_GSL", TDim::NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);

    declparam("hru_ASL", TDim::NHRU, "0.0", "0.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(" + string(DEGREE) + ")", &hru_ASL);

    // parameters for setsoil

    declparam("soil_Depth_rechr", TDim::NHRU, "[0.25]", "0.0", "10.0", "depth of top soil layer", "(m)", &soil_Depth_rechr);

    declparam("soil_Depth", TDim::NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

    declparam("Vol_h2o_content", TDim::NHRU, "[0.5]", "0.01", "0.7", "initial volumetric water content", "()", &Vol_h2o_content);

    declparam("soil_type_rechr", TDim::NHRU, "[4]", "0", "12",
        "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
        " 0 - 12", "()", &soiltype_rechr);

    declparam("soil_type", TDim::NHRU, "[4]", "0", "12",
        "water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
        " 0 - 12", "()", &soil_type);

    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        " Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

    declparam("soil_rechr_init", TDim::NHRU, "[30.0]", "0.0", "250.0", " Initial value of available water for soil recharge zone (upper part of "//
        "soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

    declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0",
        "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone.",
        "(mm)", &soil_moist_max);

    declparam("soil_moist_init", TDim::NHRU, "[187.0]", "0.0", "2500.0",
        "Initial value of available water in soil profile.",
        "(mm)", &soil_moist_init);
}

void ClassSetSoil::init(void) {

    double totarea = 0;
    nhru = getdim(TDim::NHRU);

    for (hh = 0; chkStruct(); ++hh)
        totarea += hru_area[hh];

    if (fabs((totarea - basin_area[0]) / basin_area[0]) > 1e-3) {
        const_cast<double*>  (basin_area)[0] = totarea;
        CRHMException TExcept(string(string("Sum of HRU's area <> Basin area, Basin area made = ") + FloatToStrF(totarea, TFloatFormat::ffGeneral, 3, 0)).c_str(), TExcept::WARNING);
        LogError(TExcept);
    }

    for (hh = 0; chkStruct(); ++hh) {
        double Fract = (Vol_h2o_content[hh] * 1000 - SetSoilproperties[soiltype_rechr[hh]][1]) / SetSoilproperties[soiltype_rechr[hh]][0];
        if (Fract > 1.0)
            Fract = 1.0;
        if (Fract < 0.0)
            Fract = 0.0;

        const_cast<double*> (soil_rechr_init)[hh] = soil_Depth_rechr[hh] * Fract * SetSoilproperties[soiltype_rechr[hh]][0];

        const_cast<double*> (soil_rechr_max)[hh] = soil_Depth_rechr[hh] * SetSoilproperties[soiltype_rechr[hh]][0];

        double Fract2 = (Vol_h2o_content[hh] * 1000 - SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][0];
        if (Fract2 > 1.0)
            Fract2 = 1.0;
        if (Fract2 < 0.0)
            Fract2 = 0.0;

        const_cast<double*> (soil_moist_init)[hh] = soil_Depth[hh] * Fract2 * SetSoilproperties[soil_type[hh]][0];

        const_cast<double*> (soil_moist_max)[hh] = soil_Depth[hh] * SetSoilproperties[soil_type[hh]][0];

        if (soil_rechr_init[hh] > soil_moist_init[hh]) // handles approximations
            const_cast<double*> (soil_rechr_init)[hh] = soil_moist_init[hh];

        if (soil_rechr_max[hh] > soil_moist_max[hh]) // handles approximations
            const_cast<double*> (soil_rechr_max)[hh] = soil_moist_max[hh];
    }
}
