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

class Classpbsm : public ClassModule {
public:

Classpbsm(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

double hru_u_{0.0};

// declared variables

double *SWE{ NULL };
double *Subl{ NULL };
double *Drift{ NULL };
double *SublH{ NULL };
double *DriftH{ NULL };
double *cumSubl{ NULL };
double *cumDrift{ NULL };
double *cumDriftIn{ NULL };
double *cumSno{ NULL };
double *Prob{ NULL };
double *snowdepth{ NULL };
double *BasinSnowLoss{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowGain{ NULL };
double *SnowAge{ NULL };
double *SWE_Init{ NULL };
double *rain_on_snow{ NULL };
double *cumrain_on_snow{ NULL };
long  *DrySnow{ NULL };

// declared parameters
const double *fetch{ NULL };
const double *Ht{ NULL };
const double *distrib{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *A_S{ NULL };
const double *u_D{ NULL };
const double *Drift_offset{ NULL };
const double *Drift_slope{ NULL };
const double *Subl_offset{ NULL };
const double *Subl_slope{ NULL };
const long *N_S{ NULL }; // N_S represents the number of plant stalks for a given square meter of ground.
const long *inhibit_evap{ NULL };
const long *inhibit_bs{ NULL };
const long *inhibit_subl{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_rh{ NULL };
const double *hru_u{ NULL };
const double *hru_Uadjust{ NULL };
const double *net_snow{ NULL };
const double *net_rain{ NULL };
const long  *hru_newsnow{ NULL };

// local allocated arrays
double *hru_basin{ NULL };


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm* klone(string name) const;
};
