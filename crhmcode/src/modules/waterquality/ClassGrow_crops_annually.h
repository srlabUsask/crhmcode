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

#ifndef CLASSGROW_CROPS_ANNUALLY
#define CLASSGROW_CROPS_ANNUALLY

#include "WQ_CRHM.h"


class ClassGrow_crops_annually : public ClassModule {
public:

	ClassGrow_crops_annually(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	long ObsCnt_N_up{ 0 };
	long ObsCnt_P_up{ 0 };
	long ObsCntMan_N_up{ 0 };
	long ObsCntMan_P_up{ 0 };
	long ObsCntRes_N_up{ 0 };
	long ObsCntRes_P_up{ 0 };
	long ObsCnt_N_down{ 0 };
	long ObsCnt_P_down{ 0 };
	long ObsCntMan_N_down{ 0 };
	long ObsCntMan_P_down{ 0 };
	long ObsCntRes_N_down{ 0 };
	long ObsCntRes_P_down{ 0 };
	long ObsCnt_fertperiod{ 0 };
	long ObsCnt_litterperiod{ 0 };

	// declared variables
	double* Fert_N_amount_up{ NULL };
	double* Fert_P_amount_up{ NULL };
	double* Man_N_amount_up{ NULL };
	double* Man_P_amount_up{ NULL };
	double* Fert_N_amount_down{ NULL };
	double* Fert_P_amount_down{ NULL };
	double* Man_N_amount_down{ NULL };
	double* Man_P_amount_down{ NULL };
	double* Res_N_amount_up{ NULL };
	double* Res_P_amount_up{ NULL };
	double* Res_N_amount_down{ NULL };
	double* Res_P_amount_down{ NULL };
	//double *Fertday;
	//double *Manday;
	//double *Resday_up;
	double* Fertperiod{ NULL };
	double* Litterperiod{ NULL };
	long* LockOut{ NULL };

	//long  *SecondDown_fert;
	//long  *SecondDown_man;

	// declared parameters
	const long* Ag_YearStart{ NULL };
	const long* disable_manfertres{ NULL };

	// put parameters
	const double* Htmax{ NULL };
	const double* Init_Crop_Ht_1{ NULL };
	const double* Crop_Grow_Rate_1{ NULL };
	const double* JCrop_Start_1{ NULL };
	const double* JCrop_Harvest_1{ NULL };
	const double* Crop_Htmax_1{ NULL };
	const double* Init_Crop_Ht_2{ NULL };
	const double* Crop_Grow_Rate_2{ NULL };
	const double* JCrop_Start_2{ NULL };
	const double* JCrop_Harvest_2{ NULL };
	const double* Crop_Htmax_2{ NULL };

	double* Ht{ NULL };
	double* fertNamount_up{ NULL };
	double* fertPamount_up{ NULL };
	double* fertNamount_down{ NULL };
	double* fertPamount_down{ NULL };
	double* manNamount_up{ NULL };
	double* manPamount_up{ NULL };
	double* manNamount_down{ NULL };
	double* manPamount_down{ NULL };
	double* resNamount_up{ NULL };
	double* resPamount_up{ NULL };
	double* resNamount_down{ NULL };
	double* resPamount_down{ NULL };

	double* manday_up{ NULL };
	double* manday_down{ NULL };
	double* fertday_up{ NULL };
	double* fertday_down{ NULL };
	double* resday_up{ NULL };
	double* resday_down{ NULL };
	long* fertperiod{ NULL };
	long* litterperiod{ NULL };

	// declared observation variables
	const double* Fert_N_up{ NULL };
	const double* Fert_P_up{ NULL };
	const double* Man_N_up{ NULL };
	const double* Man_P_up{ NULL };
	const double* Res_N_up{ NULL };
	const double* Res_P_up{ NULL };
	const double* Fert_N_down{ NULL };
	const double* Fert_P_down{ NULL };
	const double* Man_N_down{ NULL };
	const double* Man_P_down{ NULL };
	const double* Res_N_down{ NULL };
	const double* Res_P_down{ NULL };
	const long* Fert_period{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);
	bool Good_Dates(const double* date);

	ClassGrow_crops_annually* klone(string name) const;
};


#endif // !CLASSGROW_CROPS_ANNUALLY
