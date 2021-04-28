#pragma once

#ifndef CLASSSOILPRARIE
#define CLASSSOILPRARIE

#include "WQ_CRHM.h"

class ClassSoilPrairie : public ClassModule {
public:

	ClassSoilPrairie(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	long snowinfilDiv{0};
	long meltrunoffDiv{0};
	long runoffDiv{0};
	long evapDiv{0};



	// allocated storage
	double** current_area{NULL}; // [NumSloughs] [nhru]
	double** current_depth{ NULL }; // [NumSloughs] [nhru]
	double** current_volume{ NULL }; // [NumSloughs] [nhru]
	double** S_values{ NULL }; // [NumSloughs] [nhru]
	double** h_values{ NULL }; // [NumSloughs] [nhru]
	double** wetland_drainage{ NULL }; // [NumSloughs] [nhru]


	// declared observation variables

	// declared variables
	double* Sd{ NULL };
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

	// local variables
	double* cum_soil_gw{ NULL };
	double* cum_gw_flow{ NULL };
	double* cum_hru_condense{ NULL };
	double* soil_moist_Init{ NULL };
	double* soil_rechr_Init{ NULL };
	double* Sd_Init{ NULL };
	double* gw_Init{ NULL };
	double* SWE_Init{ NULL };

	// local variables for variation 1
	double* total_basin_area{ NULL };
	double* final_area{ NULL };
	double* max_slough_area{ NULL };
	double* outflow_volume{ NULL };
	double* delta_vol{ NULL };
	double* final_vol{ NULL };
	double* max_slough_volume{ NULL };
	double* volfrac{ NULL };
	double* areafrac{ NULL };
	double* runofffrac{ NULL };
	double* PCM_runoff_multiplier{ NULL };
	double* total_slough_basin_area{ NULL };
	double* PCM_Sdmax{ NULL };
	double* total_slough_volume{ NULL };
	double* PCM_outflow{ NULL };

	// local variables for variation 2
	double* SPRE{ NULL };


	double* snowinfil_buf{ NULL };
	double* runoff_buf{ NULL };
	double* meltrunoff_buf{ NULL };
	double* hru_evap_buf{ NULL };
	double* hru_evap_PT_buf{ NULL };

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
	const double* contrib_frac_init{ NULL };
	const double* evap_threshold{ NULL };
	const long* soil_withdrawal{ NULL };
	const long** soil_withdrawal_Tables{ NULL };

	const long* cov_type{ NULL };
	const long* transp_limited{ NULL };
	const long* soil_ssr_runoff{ NULL };
	const long* inhibit_evap{ NULL };
	const long* Sd_normal{ NULL };

	// parameters for variation 1
	const double* max_water_frac{ NULL };
	const long* numSloughs{ NULL };
	const double* Max_V{ NULL };
	const double* Max_A{ NULL };
	const double* Init_V{ NULL };
	const long* Connect{ NULL };
	const double* p1{ NULL };
	const double* p2{ NULL };
	const double* maxPondArea_p1{ NULL };
	const double* minPondBasinArea{ NULL };
	const double* minPondArea{ NULL };
	const double* basinarea_c1{ NULL };
	const double* basinarea_c2{ NULL };
	const double** Max_V_N{ NULL };
	const double** Max_A_N{ NULL };
	const double** Init_V_N{ NULL };
	const double* vol_frac_pt1{ NULL };
	const double* vol_frac_pt2{ NULL };
	const double* contrib_frac_pt1{ NULL };
	const double* contrib_frac_pt2{ NULL };
	const long** Connect_N{ NULL };

	// parameters for variation 2
	const double* CMAX{ NULL };
	const double* CMIN{ NULL };
	const double* B{ NULL };


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

	double parametric_contrib_frac_subtract(void);
	double parametric_contrib_frac_add(const double contrib_frac_slice, const double delta_Sd);

	double parametric_Sd_add(const double applied_depth);
	double parametric_Sd_subtract(const double applied_depth);

	double parametric_area_frac(const double vol_frac);
	void calc_total_evap(const double actual_evap, const double precip);

	// functions for variation 1
	double PCM_area_frac(double maxarea, double volume, double S, double h);
	void PCM_calc_h_and_S(double maxvolume, double maxarea, double& S, double& h);
	double PCM_wetland_drainage_area(double maxarea);
	void PCM_evap(double evap);
	void PCM_set_Sd();
	void PCM_rain();
	void PCM_runoff();
	double PCM_route_excess();

	// functions for variation 2
	void PDMROF_add_subtract(double deltaSd);


	ClassSoilPrairie* klone(string name) const;
};


#endif // !CLASSSOILPRARIE
