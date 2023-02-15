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

class ClassSnobalCRHM : public ClassSnobalBase {

    public:

    ClassSnobalCRHM(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalCRHM* klone(string name) const;

    double Qsi_{0.0};
    double Qli_{0.0};

// Observations

    const double *Qsi{ NULL }; // incoming solar radiation (W/m^2)
    const double *Qli{ NULL }; // incoming longwave (thermal) rad (W/m^2) long
    const double *T_g_Obs{ NULL }; // ground temperature at depth
    const double *F_g_Obs{ NULL }; // ground flux at depth

// variable climate-data inputs

    const double  *T_a_X{ NULL };      // air temp (C) hru_t
    const double  *T_pp_X{ NULL };       // precip temp (C) hru_t
    const double  *e_a_X{ NULL };      // vapor pressure (Pa) hru_ea
    const double  *u_X{ NULL };        // wind speed (m/sec)  hru_u
    const double  *Albedo{ NULL };     // albedo ()
    const double  *Qsisn_Var{ NULL };  // short wave at snow surface
    const double  *QsiS_Var{ NULL };  // short wave at snow surface from Slope_Qsi
    const double  *Qlisn_Var{ NULL };  // long wave at snow surface - through canopy
    const double  *QliVt_Var{ NULL };  // long wave at snow surface - no canopy

// variable precipitation inputs

    const double  *m_precip_X{ NULL };	// specific mass of total precip     (kg/m^2) net_p
    const double  *m_snow_X{ NULL };	// specific mass in snow in precip   (kg/m^2) net_snow
    const double  *m_drift_X{ NULL };	// specific mass in snow drift       (kg/m^2) Drift
    const double  *m_subl_X{ NULL };	// specific mass of snow sublimation (kg/m^2) Subl

// put variable precipitation inputs

    double  *m_rain_X{ NULL };	// specific mass of rain in precip   (kg/m^2) net_rain

// parameters

    const double  *rho_snow_X{ NULL };       // density of snowfall               (kg/m^3)
    const double  *T_g_X{ NULL };            // soil temp at depth z_g (C)
    const double  *F_g_X{ NULL };            // soil flux at depth z_g (C)
    const long   *rain_soil_snow{ NULL };  //
    const double  *lw_reduction{ NULL };            // soil flux at depth z_g (C)
    double *snow_store{ NULL }; // accumulates snow till > 1+mm

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};