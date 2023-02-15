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

#ifndef CLASSWQ_PBSMSNOBAL
#define CLASSWQ_PBSMSNOBAL

#include "WQ_CRHM.h"


class ClassWQ_pbsmSnobal : public ClassModule {
public:

	ClassWQ_pbsmSnobal(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

	double hru_u_{ 0.0 };

	// declared variables

	double* SWE_max{ NULL };
	double* SWE_conc{ NULL };
	double** SWE_conc_lay{ NULL };
	double* Subl{ NULL };
	double* Subl_conc{ NULL };
	double** Subl_conc_lay{ NULL };
	double* Drift{ NULL };
	double* Drift_in{ NULL };
	double* Drift_in_conc{ NULL };
	double** Drift_in_conc_lay{ NULL };
	double* Drift_out{ NULL };       // HRU composite drift
	double* Drift_out_conc{ NULL };  // HRU composite drift
	double** Drift_out_conc_lay{ NULL };  // HRU composite drift
	double* cumSubl{ NULL };
	double* cumSubl_mWQ{ NULL };
	double** cumSubl_mWQ_lay{ NULL };
	double* cumDriftOut{ NULL };
	double* cumDriftOut_mWQ{ NULL };
	double** cumDriftOut_mWQ_lay{ NULL };
	double* cumDrift{ NULL };
	double* cumDriftIn{ NULL };
	double* cumDriftIn_mWQ{ NULL };
	double** cumDriftIn_mWQ_lay{ NULL };
	double* cumSno{ NULL };
	double* cumSno_mWQ{ NULL };
	double** cumSno_mWQ_lay{ NULL };
	double* snowdepth{ NULL };
	double* BasinSnowLoss{ NULL };
	double* BasinSnowLoss_mWQ{ NULL };
	double** BasinSnowLoss_mWQ_lay{ NULL };
	double* BasinSnowGain{ NULL };
	double* BasinSnowGain_mWQ{ NULL };
	double** BasinSnowGain_mWQ_lay{ NULL };
	double* cumBasinSnowLoss{ NULL };
	double* cumBasinSnowLoss_mWQ{ NULL };
	double** cumBasinSnowLoss_mWQ_lay{ NULL };
	double* cumBasinSnowGain{ NULL };
	double* cumBasinSnowGain_mWQ{ NULL };
	double** cumBasinSnowGain_mWQ_lay{ NULL };
	double* SublH{ NULL };
	double* DriftH{ NULL };
	double* Prob{ NULL };
	double* SnowAge{ NULL };
	double* SWE_Init{ NULL };
	long* DrySnow{ NULL };

	// declared parameters
	const double* fetch{ NULL };
	const double* Ht{ NULL };
	const double* distrib{ NULL };
	const double* basin_area{ NULL };
	const double* hru_area{ NULL };
	const double* A_S{ NULL };
	const double* u_D{ NULL };
	const double* Drift_offset{ NULL };
	const double* Drift_slope{ NULL };
	const double* Subl_offset{ NULL };
	const double* Subl_slope{ NULL };
	const long* N_S{ NULL };
	const double* rain_conc{ NULL };
	const double** rain_conc_lay{ NULL };
	const double* snow_conc{ NULL };
	const double** snow_conc_lay{ NULL };
	const double* atmos_mWQ{ NULL };
	const double** atmos_mWQ_lay{ NULL };
	const long* inhibit_evap{ NULL };
	const long* inhibit_bs{ NULL };
	const long* inhibit_subl{ NULL };

	// put variable inputs
	double* SWE{ NULL }; // actually m_s

	// variable inputs
	const double* z_s{ NULL };
	const double* rho{ NULL };
	const double* hru_t{ NULL };
	const double* hru_u{ NULL };
	const double* hru_Uadjust{ NULL };
	const double* net_snow{ NULL };
	const long* hru_newsnow{ NULL };
	const double* hru_ea{ NULL };

	// local allocated arrays

	double* BasinSnowGain_0{ NULL };
	double* cumBasinSnowGain_0{ NULL };
	double* BasinSnowLoss_0{ NULL };
	double* cumBasinSnowLoss_0{ NULL };

	double* hru_basin{ NULL };
	double* SWE_0{ NULL };
	double* SWE_Init_0{ NULL };
	double* z_s_0{ NULL };
	double* rho_0{ NULL };

	double* Drift_out_0{ NULL };
	double* Drift_in_0{ NULL };
	double* cumDriftIn_0{ NULL };
	double* cumDriftOut_0{ NULL };
	double* cumSubl_0{ NULL };
	double* Subl_0{ NULL };
	double* cumSno_0{ NULL };
	double* SnowAge_0{ NULL };
	long* DrySnow_0{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Reset_WQ(long hru, double* var, double** var_WQ_lay);
	void Save();
	void Restore(const long hh);
	void copy_array(double* from, double* to);
	void copy_array(long* from, long* to);
	void copy_basin(double* from, double* to);
	void restore_hru(double* from, double* to, const long hh);
	void restore_hru(long* from, long* to, const long hh);

	ClassWQ_pbsmSnobal* klone(string name) const;
};


#endif // !CLASSWQ_PBSMSNOBAL
