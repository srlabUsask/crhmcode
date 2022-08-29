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
//created by Manishankar Mondal

#include "ClassSnobalBase.h"

class ClassSnobalX : public ClassSnobalBase {

    public:

    ClassSnobalX(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalX* klone(string name) const;

// variable climate-data inputs

    const double  *S_n_X{ NULL };      // net solar radiation (W/m^2)
    const double  *I_lw_X{ NULL };     // incoming longwave (thermal) rad (W/m^2)
    const double  *T_a_X{ NULL };      // air temp (C)
    const double  *e_a_X{ NULL };      // vapor pressure (Pa)
    const double  *u_X{ NULL };        // wind speed (m/sec)
    const double  *T_g_X{ NULL };      // soil temp at depth z_g (C)
    const double  *F_g_X{ NULL };      // soil flux at depth z_g ()

// variable precipitation inputs

    const double  *m_precip_X{ NULL };	// specific mass of total precip     (kg/m^2)
    const double  *m_rain_X{ NULL };	// specific mass of rain in precip   (kg/m^2)
    const double  *m_snow_X{ NULL };	// specific mass in snow in precip   (kg/m^2)
    const double  *m_drift_X{ NULL };	// specific mass in snow drift       (kg/m^2)
    const double  *m_subl_X{ NULL };	// specific mass of snow sublimation (kg/m^2)
    const double  *rho_snow_X{ NULL };   // density of snowfall               (kg/m^3)
    const double  *T_pp_X{ NULL };       // precip temp (C)


    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};