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
#include "Classlapse_rate_Monthly_Mod.h"


Classlapse_rate_Monthly_Mod* Classlapse_rate_Monthly_Mod::klone(string name) const {
    return new Classlapse_rate_Monthly_Mod(name);
}

void Classlapse_rate_Monthly_Mod::decl(void) {
    declvar("lapse_rate_Mthly", TDim::NHRU, "temperature lapse rate Mthly.", "(" + string(DEGREE_CELSIUS) + "/100m)", &lapse_rate_Mthly);
    declvar("lapse_rate", TDim::NHRU, "temperature lapse rate.", "(" + string(DEGREE_CELSIUS) + "/100m)", &lapse_rate);
    //  declparam("lapse_rate", NHRU, "[0.75]", "0", "2", "temperature lapse rate.", "("+string(DEGREE_CELSIUS)+"/100m)", &lapse_rate);
}

void Classlapse_rate_Monthly_Mod::init(void) {
    for (hh = 0; hh < nhru; ++hh) {
        lapse_rate[hh] = 0.0;
        lapse_rate_Mthly[hh] = 0.0;
    }
}

void Classlapse_rate_Monthly_Mod::run(void) {

    long step = getstep();
    long nstep = step % Global::Freq;
    long JULIAN = julian("now");

    if (nstep == 0) {  // end of day
        for (hh = 0; hh < nhru; ++hh) {
            if (JULIAN >= 274 && JULIAN < 305)
                lapse_rate[hh] = 0.81;
            else if (JULIAN >= 305 && JULIAN < 335)
                lapse_rate[hh] = 0.83;
            else if (JULIAN >= 335 && JULIAN < 365)
                lapse_rate[hh] = 0.73;
            else if (JULIAN >= 1 && JULIAN < 32)
                lapse_rate[hh] = 0.66;
            else if (JULIAN >= 32 && JULIAN < 60)
                lapse_rate[hh] = 0.72;
            else if (JULIAN >= 60 && JULIAN < 91)
                lapse_rate[hh] = 0.8;
            else if (JULIAN >= 91 && JULIAN < 121)
                lapse_rate[hh] = 0.85;
            else if (JULIAN >= 121 && JULIAN < 152)
                lapse_rate[hh] = 0.8;
            else if (JULIAN >= 152 && JULIAN < 182)
                lapse_rate[hh] = 0.78;
            else if (JULIAN >= 182 && JULIAN < 213)
                lapse_rate[hh] = 0.6;
            else if (JULIAN >= 213 && JULIAN < 244)
                lapse_rate[hh] = 0.57;
            else if (JULIAN >= 244 && JULIAN < 274)
                lapse_rate[hh] = 0.76;

            lapse_rate_Mthly[hh] = lapse_rate[hh];
        } // for hh
    } // end of day
} // run