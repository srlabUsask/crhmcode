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
#include "ClassWQ_mass_conc.h"


ClassWQ_mass_conc* ClassWQ_mass_conc::klone(string name) const {
    return new ClassWQ_mass_conc(name);
}

void ClassWQ_mass_conc::decl(void) {

    Description = "'converts _mWQ to concentrations'";

    declvar("inflow_conc", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg)", &inflow_conc, &inflow_conc_lay, numsubstances);
    declvar("outflow_conc", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg)", &outflow_conc, &outflow_conc_lay, numsubstances);
    declvar("runflow_conc", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg)", &runoutflow_conc, &runoutflow_conc_lay, numsubstances);
    declvar("ssrflow_conc", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg)", &ssroutflow_conc, &ssroutflow_conc_lay, numsubstances);
    declvar("gwoutflow_conc", TDim::NDEFN, "Mass: inflow from other HRUs", "(mg)", &gwoutflow_conc, &gwoutflow_conc_lay, numsubstances);


    declgetvar("*", "inflow", "(mm/int)", &inflow);
    declgetvar("*", "inflow_mWQ", "(mg)", &inflow_mWQ, &inflow_mWQ_lay);
    declgetvar("*", "outflow", "(mm/int)", &outflow);
    declgetvar("*", "outflow_mWQ", "(mg)", &outflow_mWQ, &outflow_mWQ_lay);
    declgetvar("*", "outflow_cWQ", "(mg/l)", &outflow_cWQ, &outflow_cWQ_lay);
    declgetvar("*", "runoutflow", "(mm/int)", &runoutflow);
    declgetvar("*", "runoutflow_mWQ", "(mg)", &runoutflow_mWQ, &runoutflow_mWQ_lay);
    declgetvar("*", "ssroutflow", "(mm/int)", &ssroutflow);
    declgetvar("*", "ssroutflow_mWQ", "(mg)", &ssroutflow_mWQ, &ssroutflow_mWQ_lay);
    declgetvar("*", "gwoutflow", "(mm/int)", &gwoutflow);
    declgetvar("*", "gwoutflow_mWQ", "(mg)", &gwoutflow_mWQ, &gwoutflow_mWQ_lay);

}

void ClassWQ_mass_conc::init(void) {

    nhru = getdim(TDim::NHRU);
    Reset_WQ(inflow_conc_lay);
    Reset_WQ(outflow_conc_lay);
    Reset_WQ(runoutflow_conc_lay);
    Reset_WQ(ssroutflow_conc_lay);
    Reset_WQ(gwoutflow_conc_lay);
}

void ClassWQ_mass_conc::run(void) {

    mass_to_conc(inflow, inflow_mWQ_lay, inflow_conc_lay);
    mass_to_conc(outflow, outflow_mWQ_lay, outflow_conc_lay);
    mass_to_conc(runoutflow, runoutflow_mWQ_lay, runoutflow_conc_lay);
    mass_to_conc(ssroutflow, ssroutflow_mWQ_lay, ssroutflow_conc_lay);
    mass_to_conc(gwoutflow, gwoutflow_mWQ_lay, gwoutflow_conc_lay);
}

void ClassWQ_mass_conc::mass_to_conc(const double* var, const double** var_mWQ, double** var_conc) {

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        for (long hh = 0; hh < nhru; ++hh) {
            if (var[hh] <= 0.0)
                var_conc[Sub][hh] = 0.0;
            else
                var_conc[Sub][hh] = var_mWQ[Sub][hh] / var[hh];
        }
    }
}

void ClassWQ_mass_conc::Reset_WQ(double** var_lay) {
    for (long hh = 0; hh < nhru; ++hh) {
        for (long Sub = 0; Sub < numsubstances; ++Sub)
            var_lay[Sub][hh] = 0.0;
    }
}