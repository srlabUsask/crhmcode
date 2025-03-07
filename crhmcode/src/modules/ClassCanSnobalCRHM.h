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

#include "ClassCanSnobalBase.h"

class ClassCanSnobalCRHM : public ClassCanSnobalBase {

    public:

    ClassCanSnobalCRHM(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassCanSnobalBase(Name, Version, Lvl) {};

    ClassCanSnobalCRHM* klone(string name) const;

    double Qsi_{0.0};
    double Qli_{0.0};

// Observations

    const double *Qsi{ NULL }; // incoming solar radiation (W/m^2)
    const double *Qli{ NULL }; // incoming longwave (thermal) rad (W/m^2) long
    const double *obs_snow_load { NULL };

// variable climate-data inputs

    const double  *T_a_X{ NULL };      // air temp (C) hru_t
    const double  *T_pp_X{ NULL };       // precip temp (C) hru_t
    const double  *e_a_X{ NULL };      // vapor pressure (Pa) hru_ea
    const double  *u_X{ NULL };        // wind speed (m/sec)  hru_u
    const double *Qsw_in_veg{ NULL }; // downwelling shortwave radiation to the canopy (W m^-2)
    const double *Qlw_out_atm{ NULL }; // downwelling longwave radiation from the atmosphere plus terrain (W m^-2)

// variable precipitation inputs

    const double  *new_snow{ NULL };	// specific mass in snow in precip   (kg/m^2) net_snow
    const double  *new_rain{ NULL };	// specific mass in rain in precip   (kg/m^2) net_rain

// parameters

    const double  *rho_snow_X{ NULL };       // density of snowfall               (kg/m^3)

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};