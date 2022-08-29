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

#ifndef CLASSWQ_NETROUTE
#define CLASSWQ_NETROUTE

#include "WQ_CRHM.h"


class ClassWQ_Netroute : public ClassModule {
public:

	ClassWQ_Netroute(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	long meltrunoffDiv{ 0 };
	long soil_ssrDiv{ 0 };
	long soil_runoffDiv{ 0 };
	long soil_gwDiv{ 0 };
	//long Sub;

	// declared variables
	double* ssrinflow{ NULL };
	double* ssrinflow_mWQ{ NULL };
	double** ssrinflow_mWQ_lay{ NULL };
	double* ssrcuminflow{ NULL };
	double* ssrcuminflow_mWQ{ NULL };
	double** ssrcuminflow_mWQ_lay{ NULL };
	double* ssroutflow{ NULL };
	double* ssroutflow_mWQ{ NULL };
	double** ssroutflow_mWQ_lay{ NULL };
	double* ssrcumoutflow{ NULL };
	double* ssrcumoutflow_mWQ{ NULL };
	double** ssrcumoutflow_mWQ_lay{ NULL };

	double* runinflow{ NULL };
	double* runinflow_mWQ{ NULL };
	double** runinflow_mWQ_lay{ NULL };
	double* runcuminflow{ NULL };
	double* runcuminflow_mWQ{ NULL };
	double** runcuminflow_mWQ_lay{ NULL };
	double* runoutflow{ NULL };
	double* runoutflow_mWQ{ NULL };
	double** runoutflow_mWQ_lay{ NULL };
	double* runcumoutflow{ NULL };
	double* runcumoutflow_mWQ{ NULL };
	double** runcumoutflow_mWQ_lay{ NULL };

	double* inflow{ NULL };
	double* inflow_mWQ{ NULL };
	double** inflow_mWQ_lay{ NULL };
	double* cuminflow{ NULL };
	double* cuminflow_mWQ{ NULL };
	double** cuminflow_mWQ_lay{ NULL };
	double* outflow{ NULL };
	double* outflow_mWQ{ NULL };
	double** outflow_mWQ_lay{ NULL };
	double* outflow_cWQ{ NULL };
	double** outflow_cWQ_lay{ NULL };
	double* cumoutflow{ NULL };
	double* cumoutflow_mWQ{ NULL };
	double** cumoutflow_mWQ_lay{ NULL };
	double* outflow_diverted{ NULL };
	double* outflow_diverted_conc{ NULL };
	double** outflow_diverted_conc_lay{ NULL };
	double* cumoutflow_diverted{ NULL };
	double* cumoutflow_diverted_mWQ{ NULL };
	double** cumoutflow_diverted_mWQ_lay{ NULL };

	double* gwinflow{ NULL };
	double* gwinflow_mWQ{ NULL };
	double** gwinflow_mWQ_lay{ NULL };
	double* gwcuminflow{ NULL };
	double* gwcuminflow_mWQ{ NULL };
	double** gwcuminflow_mWQ_lay{ NULL };
	double* gwoutflow{ NULL };
	double* gwoutflow_mWQ{ NULL };
	double** gwoutflow_mWQ_lay{ NULL };
	double* gwcumoutflow{ NULL };
	double* gwcumoutflow_mWQ{ NULL };
	double** gwcumoutflow_mWQ_lay{ NULL };
	double* gwoutflow_diverted{ NULL };
	double* gwoutflow_diverted_conc{ NULL };
	double** gwoutflow_diverted_conc_lay{ NULL };
	double* gwcumoutflow_diverted{ NULL };
	double* gwcumoutflow_diverted_mWQ{ NULL };
	double** gwcumoutflow_diverted_mWQ_lay{ NULL };

	double* basinflow{ NULL };     // [BASIN] all HRUs
	double* basinflow_conc{ NULL };     // [BASIN] all HRUs
	double** basinflow_conc_lay{ NULL };     // [BASIN] all HRUs
	double* basinflow_s{ NULL };   // [BASIN] all HRUs
	double* cumbasinflow{ NULL };  // [BASIN] all HRUs
	double* cumbasinflow_mWQ{ NULL };  // [BASIN] all HRUs
	double** cumbasinflow_mWQ_lay{ NULL };  // [BASIN] all HRUs
	double* basingw{ NULL };       // [BASIN} all HRUs
	double* basingw_conc{ NULL };       // [BASIN} all HRUs
	double** basingw_conc_lay{ NULL };       // [BASIN} all HRUs
	double* basingw_s{ NULL };     // [BASIN} all HRUs
	double* cumbasingw{ NULL };    // [BASIN} all HRUs
	double* cumbasingw_mWQ{ NULL };    // [BASIN} all HRUs
	double** cumbasingw_mWQ_lay{ NULL };    // [BASIN} all HRUs

	double* soil_ssr_Buf{ NULL };    // buffered
	double* soil_ssr_Buf_conc{ NULL };    // buffered
	double** soil_ssr_Buf_conc_lay{ NULL };    // buffered
	double* soil_runoff_Buf{ NULL }; // buffered
	double* soil_runoff_Buf_conc{ NULL }; // buffered
	double** soil_runoff_Buf_conc_lay{ NULL }; // buffered
	double* soil_gw_Buf{ NULL };     // buffered
	double* soil_gw_Buf_conc{ NULL };     // buffered
	double** soil_gw_Buf_conc_lay{ NULL };     // buffered

	double* HRU_cumbasinflow{ NULL };
	double* HRU_cumbasinflow_mWQ{ NULL };
	double** HRU_cumbasinflow_mWQ_lay{ NULL };
	double* cum_to_Sd{ NULL };
	double* cum_to_Sd_mWQ{ NULL };
	double** cum_to_Sd_mWQ_lay{ NULL };
	double* cum_to_soil_rechr{ NULL };
	double* cum_to_soil_rechr_mWQ{ NULL };
	double** cum_to_soil_rechr_mWQ_lay{ NULL };
	double* Ktravel{ NULL };         // [nhru] Muskingum
	double* cum_preferential_flow_to_gw{ NULL };

	// local allocated arrays

	double* outflow_0{ NULL };
	double* gwoutflow_0{ NULL };
	//double *soil_gw_Buf_0;

	// declared parameters
	const double* route_n{ NULL };         // [nhru]
	const double* route_R{ NULL };         // [nhru]
	const double* route_S0{ NULL };        // [nhru]
	const double* route_L{ NULL };         // [nhru]
	const double* route_X_M{ NULL };       // [nhru]
	const long* route_Cshp{ NULL };      // [nhru]

	const double* Kstorage{ NULL };
	const double* Lag{ NULL };
	const double* ssrKstorage{ NULL };
	const double* ssrLag{ NULL };
	const double* runKstorage{ NULL };
	const double* runLag{ NULL };
	const double* gwKstorage{ NULL };
	const double* gwLag{ NULL };

	const double* basin_area{ NULL };        // [BASIN]
	const double* hru_area{ NULL };
	const long* whereto{ NULL };
	const long* order{ NULL };
	const long* gwwhereto{ NULL };
	const double* Sdmax{ NULL };
	const double* soil_rechr_max{ NULL };
	const long* preferential_flow{ NULL }; // [nhru]
	const long* Sd_ByPass{ NULL };
	const long* soil_rechr_ByPass{ NULL };

	// variable inputs

	const double* soil_gw{ NULL }; // N.B. gw_flow in original CRHM
	const double* soil_gw_conc{ NULL };
	const double** soil_gw_conc_lay{ NULL };
	const double* soil_ssr{ NULL };
	const double* soil_ssr_conc{ NULL };
	const double** soil_ssr_conc_lay{ NULL };
	const double* soil_runoff{ NULL };
	const double* soil_runoff_cWQ{ NULL };
	const double** soil_runoff_cWQ_lay{ NULL };

	// variable puts
	double* Sd{ NULL };
	double* Sd_conc{ NULL };
	double** Sd_conc_lay{ NULL };
	double* soil_moist{ NULL };
	double* soil_moist_conc{ NULL };
	double** soil_moist_conc_lay{ NULL };
	double* soil_lower{ NULL };
	double* soil_lower_conc{ NULL };
	double** soil_lower_conc_lay{ NULL };
	double* soil_rechr{ NULL };
	double* soil_rechr_conc{ NULL };
	double** soil_rechr_conc_lay{ NULL };
	double* redirected_residual{ NULL };
	double* redirected_residual_conc{ NULL };
	double** redirected_residual_conc_lay{ NULL };
	double* cum_redirected_residual{ NULL };
	double* cum_redirected_residual_mWQ{ NULL };
	double** cum_redirected_residual_mWQ_lay{ NULL };
	double* gw{ NULL };
	double* gw_conc{ NULL };
	double** gw_conc_lay{ NULL };
	double* conc_soil_rechr{ NULL };
	double** conc_soil_rechr_lay{ NULL };
	double* conc_soil_lower{ NULL };
	double** conc_soil_lower_lay{ NULL };
	double* conc_soil_moist{ NULL };
	double** conc_soil_moist_lay{ NULL };

	ClassMuskingum** hruDelay_mWQ{ NULL }; // [numsubstances] handled locally
	ClassClark** Clark_hruDelay_mWQ{ NULL };
	ClassClark** ssrDelay_mWQ{ NULL };
	ClassClark** runDelay_mWQ{ NULL };
	ClassClark** gwDelay_mWQ{ NULL };

	ClassMuskingum* hruDelay{ NULL };
	ClassClark* Clark_hruDelay{ NULL };
	ClassClark* ssrDelay{ NULL };
	ClassClark* runDelay{ NULL };
	ClassClark* gwDelay{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Set_WQ(long hru, double* var, double* var_conc, double amount_conc, double amount);
	void Reset_WQ(long hru, double* var, double** var_cWQ_lay);

	void Save();
	void Restore(const long hh);
	void copy_array(double* from, double* to);
	void restore_hru(double* from, double* to, const long hh);

	virtual double Function1(double* I, long hh);
	virtual double Function2(double* X, long hh);

	ClassWQ_Netroute* klone(string name) const;
};


#endif // !CLASSWQ_NETROUTE
