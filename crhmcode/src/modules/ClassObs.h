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
//created by Manishankar

#include "../core/ClassModule.h"

class Classobs : public ClassModule {
public:

Classobs(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long Exist{0};
long Exist2{0};

// declared observation variables
const double *p{ NULL };      // interval data
const double *ppt{ NULL };    // daily data
const double *t{ NULL };
double **tday_intvls{ NULL };
const double *rh{ NULL };
double **rhday_intvls{ NULL };
const double *ea{ NULL };
double **eaday_intvls{ NULL };
const double *u{ NULL };
const double *t_max{ NULL };
const double *t_min{ NULL };
const double *obs_snow{ NULL };
const double *obs_rain{ NULL };

// declared observation functions
double *tmean{ NULL };
double *tmin{ NULL };
double *tmax{ NULL };
double *umean{ NULL };
double *pptD{ NULL };
//double *p;      // interval data
double *NotUsed{ NULL };

// declared variables
double *hru_t{ NULL };
double *hru_rh{ NULL };
double *hru_ea{ NULL };
double *hru_estar{ NULL };
double *hru_u{ NULL };
double *hru_p{ NULL };
// double *hru_icebulb;
double *Pa{ NULL };
double *DTnow{ NULL };
long  *DTindx{ NULL };
double *hru_rain{ NULL };
double *cumhru_rain{ NULL };
double *hru_snow{ NULL };
double *cumhru_snow{ NULL };
double *cumhru_snow_meas{ NULL };
double *hru_tmax{ NULL };
double *hru_tmin{ NULL };
double *hru_tmean{ NULL };
double *hru_eamean{ NULL };
double *hru_umean{ NULL };
double *hru_rhmean{ NULL };

double *t_obs{ NULL };
double **t_obs_lay{ NULL };

long  *hru_newsnow{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *tmax_allrain{ NULL };
const double *tmax_allsnow{ NULL };
const double *lapse_rate{ NULL };
const double *precip_elev_adj{ NULL };
const double *hru_elev{ NULL };
const double *ClimChng_t{ NULL };
const double *ClimChng_precip{ NULL };
const long  *catchadjust{ NULL };
const long  *ppt_daily_distrib{ NULL };
const long  *snow_rain_determination{ NULL };
const long  *HRU_OBS{ NULL };
const long  **HRU_OBS_Tables{ NULL };
const double *obs_elev{ NULL };
const double  **obs_elev_Tables{ NULL };
const long  *ElevChng_flag{ NULL };
const long  *ClimChng_flag{ NULL };

// variable inputs

void decl(void);
void init(void);
void run(void);
void pre_run(void);
void Harder(void);
void finish(bool good);

Classobs* klone(string name) const;
};
