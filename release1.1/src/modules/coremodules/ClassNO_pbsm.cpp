//created by Manishankar Mondal

#include "ClassNO_pbsm.h"
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


ClassNO_pbsm* ClassNO_pbsm::klone(string name) const {
    return new ClassNO_pbsm(name);
}

void ClassNO_pbsm::decl(void) {

    Description = "'Substitute for pbsm when there is no transport and sublimation.  Alternatve is \"pbsm\" with parameter \"inhibit_bs\" = 1.'";

    declstatvar("SWE", TDim::NHRU, "snow water equivalent", "(mm)", &SWE);

    declstatdiag("cumSno", TDim::NHRU, "cumulative snow", "(mm)", &cumSno);

    declvar("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);


    /* parameters */

    declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

    declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

    decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);
    
    decldiagparam("SWEmin_inhibit_evap", TDim::NHRU, "[0.0]", "0.0", "10.0", "SWE threshold to inhibit evaporation, SWE > SWEmin_inhibit_evap: inhibit_evap = 1 -> inhibit evap", "()", &SWEmin_inhibit_evap); // modification on 24Feb2021

    declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
    
    declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClassNO_pbsm::init(void) {

    nhru = getdim(TDim::NHRU);

    hru_basin = new double[nhru];

    for (hh = 0; hh < nhru; ++hh) {
        SWE[hh] = 0.0;
        cumSno[hh] = 0.0;
        hru_basin[hh] = hru_area[hh] / basin_area[0];
        snowdepth[hh] = 0.0;
    }
}

void ClassNO_pbsm::run(void) {

    for (hh = 0; chkStruct(); ++hh) {

        if (net_snow[hh] > 0.0) {
            SWE[hh] = SWE[hh] + net_snow[hh];
            cumSno[hh] = cumSno[hh] + net_snow[hh];
        }

        if (SWE[hh] > SWEmin_inhibit_evap[hh]) { // modification on 24Feb2021: add SWEmin_inhibit_evap parameter
            const_cast<long*> (inhibit_evap)[hh] = 1;
            snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
        }
        else {
            const_cast<long*> (inhibit_evap)[hh] = 0;
            snowdepth[hh] = 0;
        }
    }
}

void ClassNO_pbsm::finish(bool good) {

    for (hh = 0; chkStruct(); ++hh) {
        LogMessageA(hh, string("'" + Name + " (NO_pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
    }
    LogDebug(" ");
}
