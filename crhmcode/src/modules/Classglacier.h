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

class Classglacier : public ClassModule {
public:

Classglacier(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " ,snowmeltD"){};

long ObsCnt_Albedo{ 0 };

// declared observation variables
const double* Qnsn{ NULL };
const double* QnD{ NULL };


double* SWEmelt{ NULL };         // SWE snowmelt
double* SWEmelt_delayed{ NULL }; // SWE snowmelt delayed
double* cumSWEmelt{ NULL };      // cumulative SWE snowmelt (same as snowmeltD_org}
double* firnmelt{ NULL };         // firn snowmelt
double* firnmelt_delayed{ NULL }; // firn snowmelt delayed
double* cumfirnmelt{ NULL };      // cumulative firn snowmelt runoff
double* icemelt{ NULL };         // ice melt
double* icemelt_delayed{ NULL }; // ice melt delayed
double* cumicemelt{ NULL };      // cumulative ice melt runoff
double* cumnet_rain_glacier{ NULL }; // cumulative net_rain + firn and ice melt
double* cumsnowmeltD_glacier{ NULL }; // cumulative snowmeltD + firn and ice melt

double* glacier_Albedo{ NULL };
double* glacier_h2o{ NULL };
double* glacier_Surf{ NULL };
double* firn{ NULL };
double* firn_depth{ NULL };
double* firn_init{ NULL };
double* firn_h{ NULL };
double** firn_h_array{ NULL };
double* firn_yr{ NULL };
double** firn_yr_array{ NULL };
double* firn_dens{ NULL };
double** firn_dens_array{ NULL };
double* SWE_2firn{ NULL };
double* cumSWE_2firn{ NULL };
double* SWE_2firn_dens{ NULL };
double* firn_2ice{ NULL };
double* cumfirn_2ice{ NULL };
double* firn_2ice_dens{ NULL };

double* Qmelt{ NULL };
double* cumQmelt{ NULL };
double* ice{ NULL };
double* Qn_ebsm{ NULL };
double* Qh_ebsm{ NULL };
double* Qe_ebsm{ NULL };
double* Qp_ebsm{ NULL };
double* Qnsn_Acc{ NULL };

double* Gnet_rainD{ NULL };
double* net_rain_org{ NULL };
double* cumnet_rain_org{ NULL };
double* SWE{ NULL };
double* topo_elev{ NULL };
double* glacier_depth{ NULL };
double* rho_snow{ NULL };
long* nfirn{ NULL };
long* GlacierMode{ NULL }; // 0 - glacier, 1 - tongue

double* lagT_delayed{ NULL }; // lagged temperature, 22 Apr 2022 added
double** lagT_delayed_lay{ NULL }; // lagged temperature, 22 Apr 2022 added
double* lagSW_delayed{ NULL }; // lagged shortwave radiation, 22 Apr 2022 added
double** lagSW_delayed_lay{ NULL }; // lagged shortwave radiation, 22 Apr 2022 added
long* lagT{ NULL }; // debris-cover melt
long* lagSW{ NULL }; // debris-cover melt
double* TF{ NULL }; // debris-cover melt
double* SRF{ NULL }; // debris-cover melt
double* Xdebris_melt_hrly{ NULL }; // debris-cover melt
double* Xdebris_melt_acc{ NULL }; // debris-cover melt
double* lagT_used{ NULL }; // debris-cover melt, added 2 July 2020
double* lagSW_used{ NULL }; // debris-cover melt, added 2 July 2020
double* den_air{ NULL }; // katabatic parameterization
double* K_kat{ NULL }; // katabatic parameterization
double* Cp_water{ NULL }; // katabatic parameterization
double* Xmelt_int{ NULL }; // katabatic parameterization
double* Xmelt_acc{ NULL }; // katabatic parameterization
double* Qn_kata{ NULL }; // katabatic parameterization
double* Qh_kata{ NULL }; // katabatic parameterization
double* Qe_kata{ NULL }; // katabatic parameterization
double* Qp_kata{ NULL }; // katabatic parameterization
double* Qmelt_kata{ NULL }; // katabatic parameterization

// declared put variable
double* Pa{ NULL };
double* net_rain{ NULL };
double* Albedo{ NULL };
double* snowmeltD{ NULL };

// declared parameters
const double* basin_area{ NULL };   // [BASIN]
const double* hru_area{ NULL };
const double* tfactor{ NULL };
const double* nfactor{ NULL };
const double* Use_QnD{ NULL };
const double* firn_Albedo{ NULL };
const double* ice_init{ NULL };
const double* ice_Albedo{ NULL };
const double* ice_dens{ NULL };
const double* TKMA{ NULL };
const double* SWEAA{ NULL };
const double* SWEstorage{ NULL };
const double* SWELag{ NULL };
const double* firnstorage{ NULL };
const double* firnLag{ NULL };
const double* icestorage{ NULL };
const double* iceLag{ NULL };
const double* topo_elev_init{ NULL };

const double* firn_h_init{ NULL };
const double** firn_h_array_init{ NULL };
const double* firn_dens_init{ NULL };
const double** firn_dens_array_init{ NULL };
const long* Elev_Adj_glacier_surf{ NULL };
const long* delay_melt{ NULL };
const long* SWE_to_firn_Julian{ NULL };
const long* inhibit_evap{ NULL };
const long* inhibit_firnmelt{ NULL };
const long* inhibit_icemelt{ NULL };
const long* Densification{ NULL };
const double* Densification_550{ NULL };
const double* Densification_above_550{ NULL };

const double* debris_h{ NULL }; // debris-cover melt
const double* T_threshold{ NULL }; // debris-cover melt
const long* use_debris{ NULL }; // debris-cover melt
const double* katabatic_lapse_rate{ NULL }; // katabatic parameterization

// declared put parameters
double* hru_elev{ NULL };
//float *snowmeltD; // changed 17 June 2020

// variable inputs
const double* tmean{ NULL };
const double* tmax{ NULL };
const double* tmin{ NULL };
const double* umean{ NULL };
const double* rhmean{ NULL };
const double* sunact{ NULL };
const double* QdroD{ NULL };
const double* QdfoD{ NULL };
const double* sunmax{ NULL };
const double* Qnsn_Var{ NULL };
const double* Xmelt{ NULL };
const double* glacier_Albedo_obs{ NULL };
const double* Qsisn_Var{ NULL }; // debris-cover melt
const double* T_rain{ NULL }; // katabatic parameterization
const double* hru_t{ NULL }; // katabatic parameterization
const double* hru_ea{ NULL }; // katabatic parameterization

ClassClark* SWEDelay{ NULL };
ClassClark* firnDelay{ NULL };
ClassClark* iceDelay{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier* klone(string name) const;
double DepthofSnow(double SWE);
};
