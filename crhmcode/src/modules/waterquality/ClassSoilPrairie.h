#pragma once

#ifndef CLASSSOILPRARIE
#define CLASSSOILPRARIE

#include "WQ_CRHM.h"


class ClassSoilPrairie : public ClassModule {
public:

	ClassSoilPrairie(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	long snowinfilDiv{ 0 };
	long meltrunoffDiv{ 0 };
	long runoffDiv{ 0 };
	long evapDiv{ 0 };

	// allocated storage
	double** current_area{ NULL }; // [NumSloughs] [nhru]
	double** current_depth{ NULL }; // [NumSloughs] [nhru]
	double** current_volume{ NULL }; // [NumSloughs] [nhru]
	double** S_values{ NULL }; // [NumSloughs] [nhru]
	double** h_values{ NULL }; // [NumSloughs] [nhru]
	double** wetland_drainage{ NULL }; // [NumSloughs] [nhru]


	// declared observation variables

	// declared variables
	double* gw{ NULL };
	double* soil_rechr{ NULL };
	double* soil_moist{ NULL };
	double* soil_gw{ NULL };
	double* gw_flow{ NULL };
	double* soil_ssr{ NULL };
	double* rechr_ssr{ NULL };
	double* soil_runoff{ NULL };
	double* cum_soil_ssr{ NULL };
	double* cum_rechr_ssr{ NULL };
	double* cum_soil_runoff{ NULL };
	double* cum_runoff_to_Sd{ NULL };
	double* cum_redirected_residual{ NULL };
	double* soil_gw_D{ NULL };
	double* soil_ssr_D{ NULL };
	double* gw_flow_D{ NULL };
	double* soil_runoff_D{ NULL };
	double* HK_V{ NULL };
	double* HK_A{ NULL };
	double* HD{ NULL };
	double* redirected_residual{ NULL };
	double* infil_act{ NULL };
	double* cum_infil_act{ NULL };
	double* infil_act_D{ NULL };
	double* Sd_water_frac{ NULL };
	double* contrib_frac{ NULL };
	double* wetlands_evap{ NULL };
	double* total_evap{ NULL };
	double* direct_rain{ NULL };

	double* Pond_water_frac{ NULL }; // Sd[hh]/Sdmax[hh]
	double* Pond_evap{ NULL };
	double* Pond_area{ NULL };
	double* Pond_volume{ NULL };
	double* Pond_h{ NULL };
	double* Pond_hmax{ NULL };
	double* Pond_s{ NULL };
	double* Sd{ NULL };
	double* runoff_to_Pond{ NULL };

	double* Small_Ponds_water_frac{ NULL }; // Small_Ponds_Sd[hh]/Small_Ponds_Sdmax[hh]
	double* Small_Ponds_evap{ NULL };
	double* Small_Ponds_area{ NULL };
	double* Small_Ponds_Sd{ NULL };
	double* runoff_to_Small_Ponds{ NULL };
	double* Small_Ponds_runoff_to_Pond{ NULL };

	// local variables
	double* cum_soil_gw{ NULL };
	double* cum_gw_flow{ NULL };
	double* cum_hru_condense{ NULL };
	double* soil_moist_Init{ NULL };
	double* soil_rechr_Init{ NULL };
	double* Sd_Init{ NULL };
	double* gw_Init{ NULL };
	double* SWE_Init{ NULL };

	double* snowinfil_buf{ NULL };
	double* runoff_buf{ NULL };
	double* meltrunoff_buf{ NULL };
	double* hru_evap_buf{ NULL };

	// declared parameters
	const double* Sdmax{ NULL };
	const double* Sdinit{ NULL };
	const double* gw_max{ NULL };
	const double* gw_init{ NULL };
	const double* gw_K{ NULL };
	const double* basin_area{ NULL };   // [BASIN]
	const double* hru_area{ NULL };
	const double* soil_rechr_max{ NULL };
	const double* soil_rechr_init{ NULL };
	const double* soil_moist_max{ NULL };
	const double* soil_moist_init{ NULL };
	const double* soil_gw_K{ NULL };
	const double* rechr_ssr_K{ NULL };
	const double* lower_ssr_K{ NULL };
	const double* Sd_ssr_K{ NULL };
	const double* Sd_gw_K{ NULL };
	const double* Sd_water_frac_max{ NULL };
	const double* evap_threshold{ NULL };
	const long* soil_withdrawal{ NULL };
	const long** soil_withdrawal_Tables{ NULL };

	const long* cov_type{ NULL };
	const long* transp_limited{ NULL };
	const long* soil_ssr_runoff{ NULL };
	const long* inhibit_evap{ NULL };
	const long* Sd_normal{ NULL };

	const double* Pond_p{ NULL };
	const double* Pond_C1{ NULL };
	const double* Pond_C2{ NULL };
	const double* Pond_C3{ NULL };
	const double* Pond_contrib_frac{ NULL }; // Pond fraction of basin
	const double* Pond_area_max{ NULL };

	const double* Small_Ponds_Sdmax{ NULL };
	const double* Small_Ponds_Sdinit{ NULL };
	const double* Small_Ponds_p{ NULL };
	const double* Small_Ponds_C1{ NULL };
	const double* Small_Ponds_C2{ NULL };
	const double* Small_Ponds_C3{ NULL };
	const double* Small_Ponds_contrib_frac{ NULL }; // Small Ponds fraction of basin
	const double* Small_Ponds_area_max{ NULL };



	// variable inputs
	const double* infil{ NULL };
	const double* snowinfil{ NULL };
	const double* meltrunoff{ NULL }; // frozen melt runoff
	const double* runoff{ NULL };     // liquid runoff
	const double* hru_evap{ NULL };
	const double* hru_evap_PT{ NULL };

	// variable put inputs
	double* hru_actet{ NULL };      // [nhru]
	double* hru_cum_actet{ NULL };


	// local allocated arrays

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassSoilPrairie* klone(string name) const;

	double area_frac(const double area_frac);
	void Pond_calc_h_A(const double s, const double p, const double volume, double& h, double& area);
	void calc_h_and_S(const double maxvolume, const double maxarea, const double pval, double& S, double& h);
	double Pond_area_frac(const double vol_frac, const long hh);
	double Small_Ponds_area_frac(const double vol_frac, const long hh);
	double Small_Ponds_runoff_frac(const double Sd_Sdmax, const long hh);
};


#endif // !CLASSSOILPRARIE
