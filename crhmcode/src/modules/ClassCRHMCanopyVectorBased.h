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

#include "../core/ClassModule.h"

class ClassCRHMCanopyVectorBased:public ClassModule {

public:

ClassCRHMCanopyVectorBased(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_{ 0.0 }, Qli_ {0.0};

// observation variables

const double *Qsi { NULL };
const double *Qli { NULL };

// declared observation variables

double *Ts { NULL };
double *Qnsn { NULL };
double *Qsisn { NULL };
double *Qlisn { NULL };
double *Qlosn { NULL };

// put variables

double *SWE { NULL };

// declared variables

double *drip_Cpy { NULL };
double *thrufall_Cpy { NULL };
double *netRain_Cpy { NULL };
double *direct_rain { NULL };
double *rain_load { NULL };
double *Snow_load { NULL };
double *direct_snow { NULL };
double *SUnload { NULL };
double *SUnload_H2O { NULL };
double *Qnsn_Var { NULL };
double *Qsisn_Var { NULL };
double *Qlisn_Var { NULL };

double *net_rain { NULL };
double *cum_net_rain { NULL };
double *net_snow { NULL };
double *cum_net_snow { NULL };
double *net_p { NULL };
double *intcp_evap { NULL };
double *cum_intcp_evap { NULL };
double *pot_subl_cpy { NULL };
double *Subl_Cpy { NULL };
double *cum_Subl_Cpy { NULL };
double *cum_SUnload { NULL };
double *cum_SUnload_H2O { NULL };

double *Cc { NULL };
double *k { NULL };
double *Tauc { NULL };
double *Pa { NULL };
double *ra { NULL };
double *u_FHt { NULL };
double *u_1_third_Ht { NULL };
double *Pevap { NULL };

// variable inputs

const double *hru_t { NULL };
const double *hru_u { NULL };
const double *hru_rh { NULL };
const double *hru_ea { NULL };
const double *Albedo { NULL };

const double *hru_snow { NULL };
const double *hru_rain { NULL };
const double *hru_evap { NULL };

const double *SolAng { NULL };
const double *cosxs { NULL };
const double *cosxsflat { NULL };
const double *Qdfo { NULL };

const double *QsiS_Var { NULL };
const double *QsiA_Var { NULL };
const double *QliVt_Var { NULL };

// declared parameters:

const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *hru_elev { NULL };
const double *Ht { NULL };
const double *LAI { NULL };
const double *Lmax { NULL };
const double *alpha { NULL };
const double *Z0snow { NULL };
const double *Zref { NULL };
const double *Zwind { NULL };
const double *Zvent { NULL };
const double *unload_t { NULL };
const double *unload_t_water { NULL };
const double *Surrounding_Ht { NULL };
const double *Gap_diameter { NULL };
const double *Alpha_c { NULL };
const double *B_canopy { NULL };

const long *CanopyClearing { NULL };
const long *inhibit_evap { NULL };


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
double gamma(double Pa, double t); // Psychrometric constant (kPa/DEGREE_CELSIUS)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg DEGREE_CELSIUS))

ClassCRHMCanopyVectorBased* klone(string name) const;
};
