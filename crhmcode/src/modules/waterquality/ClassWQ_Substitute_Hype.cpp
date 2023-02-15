/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
#include "ClassWQ_Substitute_Hype.h"


ClassWQ_Substitute_Hype* ClassWQ_Substitute_Hype::klone(string name) const {
    return new ClassWQ_Substitute_Hype(name);
}

void ClassWQ_Substitute_Hype::decl(void) {

    Description = "'Provides necessary Hype variables conc_soil_rechr, conc_soil_lower and conc_soil_moist to run other WQ modules to run without proper Hype module.'";

    declstatvar("conc_soil_rechr", TDim::NDEFN, "concentration of inorganic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay, numsubstances); //

    declstatvar("conc_soil_lower", TDim::NDEFN, "concentration of organic nitrogen in soil moisture per land-soil", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay, numsubstances);

    declstatvar("conc_soil_moist", TDim::NDEFN, "concentration of soluble (reactive) phosphorus, i.e. phosphate in soil moisture per land-soil", "(mg/l)", &conc_soil_moist, &conc_soil_moist_lay, numsubstances);

}

void ClassWQ_Substitute_Hype::init(void) {

    nhru = getdim(TDim::NHRU);
    for (hh = 0; hh < nhru; ++hh) {
        for (long Sub = 0; Sub < numsubstances; ++Sub) {
            conc_soil_rechr_lay[Sub][hh] = 0.0;
            conc_soil_lower_lay[Sub][hh] = 0.0;
            conc_soil_moist_lay[Sub][hh] = 0.0;
        }
    }
}

void ClassWQ_Substitute_Hype::run(void) {

    long step = getstep();
    long nstep = step % Global::Freq;

    for (hh = 0; chkStruct(); ++hh) {
    }
}

void ClassWQ_Substitute_Hype::finish(bool good) {

    for (hh = 0; chkStruct(); ++hh) {
        //    LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
        LogDebug(" ");
    }
    LogDebug(" ");
}