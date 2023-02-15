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
#pragma once

#ifndef CLASSWQ_GEN_MASS_VAR_SOIL
#define CLASSWQ_GEN_MASS_VAR_SOIL

#include "WQ_CRHM.h"



class ClassWQ_Gen_Mass_Var_Soil : public ClassModule {
public:

	ClassWQ_Gen_Mass_Var_Soil(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared parameters

	double* soil_moist_change_mWQ{ NULL };
	double** soil_moist_change_mWQ_lay{ NULL };

	double* soil_top_change_mWQ{ NULL };
	double** soil_top_change_mWQ_lay{ NULL };
	double* soil_top_mWQ_last{ NULL };
	double** soil_top_mWQ_lay_last{ NULL };

	double* soil_bottom_change_mWQ{ NULL };
	double** soil_bottom_change_mWQ_lay{ NULL };
	double* soil_bottom_mWQ_last{ NULL };
	double** soil_bottom_mWQ_lay_last{ NULL };

	double* soil_ssr_change_mWQ{ NULL };
	double** soil_ssr_change_mWQ_lay{ NULL };
	double* soil_ssr_mWQ_last{ NULL };
	double** soil_ssr_mWQ_lay_last{ NULL };

	double* Sd_change_mWQ{ NULL };
	double** Sd_change_mWQ_lay{ NULL };
	double* Sd_mWQ_last{ NULL };
	double** Sd_mWQ_lay_last{ NULL };

	double* gw_change_mWQ{ NULL };
	double** gw_change_mWQ_lay{ NULL };
	double* gw_mWQ_last{ NULL };
	double** gw_mWQ_lay_last{ NULL };

	double* soil_gw_change_mWQ{ NULL };
	double** soil_gw_change_mWQ_lay{ NULL };
	double* soil_gw_mWQ_last{ NULL };
	double** soil_gw_mWQ_lay_last{ NULL };

	double* gw_flow_change_mWQ{ NULL };
	double** gw_flow_change_mWQ_lay{ NULL };
	double* gw_flow_mWQ_last{ NULL };
	double** gw_flow_mWQ_lay_last{ NULL };

	double* infil_act_change_mWQ{ NULL };
	double** infil_act_change_mWQ_lay{ NULL };
	double* infil_act_mWQ_last{ NULL };
	double** infil_act_mWQ_lay_last{ NULL };

	double* redirected_residual_change_mWQ{ NULL };
	double** redirected_residual_change_mWQ_lay{ NULL };
	double* redirected_residual_mWQ_last{ NULL };
	double** redirected_residual_mWQ_lay_last{ NULL };

	double* soil_runoff_change_mWQ{ NULL };
	double** soil_runoff_change_mWQ_lay{ NULL };
	double* soil_runoff_mWQ_last{ NULL };
	double** soil_runoff_mWQ_lay_last{ NULL };

	// variable get inputs
	const double* soil_rechr{ NULL };
	const double* soil_lower{ NULL };
	const double* soil_moist{ NULL };
	const double* soil_ssr{ NULL };
	const double* Sd{ NULL };
	const double* gw{ NULL };
	const double* soil_gw{ NULL };
	const double* gw_flow{ NULL };
	const double* infil_act{ NULL };
	const double* redirected_residual{ NULL };
	const double* soil_runoff{ NULL };

	const double* conc_soil_rechr{ NULL };
	const double** conc_soil_rechr_lay{ NULL };
	const double* conc_soil_lower{ NULL };
	const double** conc_soil_lower_lay{ NULL };
	const double* soil_ssr_conc{ NULL };
	const double** soil_ssr_conc_lay{ NULL };
	const double* Sd_conc{ NULL };
	const double** Sd_conc_lay{ NULL };
	const double* gw_conc{ NULL };
	const double** gw_conc_lay{ NULL };
	const double* soil_gw_conc{ NULL };
	const double** soil_gw_conc_lay{ NULL };
	const double* gw_flow_conc{ NULL };
	const double** gw_flow_conc_lay{ NULL };
	const double* infil_act_conc{ NULL };
	const double** infil_act_conc_lay{ NULL };
	const double* redirected_residual_conc{ NULL };
	const double** redirected_residual_conc_lay{ NULL };
	const double* soil_runoff_cWQ{ NULL };
	const double** soil_runoff_cWQ_lay{ NULL };

	//declared variables
	long* run_ID{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_Gen_Mass_Var_Soil* klone(string name) const;
};


#endif // !CLASSWQ_GEN_MASS_VAR_SOIL
