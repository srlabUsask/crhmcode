#pragma once

#ifndef CLASSWQ_SOIL
#define CLASSWQ_SOIL

#include "WQ_CRHM.h"

class ClassWQ_Soil : public ClassModule {
public:

	ClassWQ_Soil(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

	long snowinfilDiv{ 0 };
	long meltrunoffDiv{ 0 };
	long runoffDiv{ 0 };
	long evapDiv{ 0 };
	long Sub{ 0 };
	long FaultsAllowed{ 0 };

	// declared variables
	long* current_getstep{ NULL };
	double* scf{ NULL };
	double* Sd{ NULL };
	double* Sd_conc{ NULL };
	double** Sd_conc_lay{ NULL };
	double* gw{ NULL };
	double* gw_conc{ NULL };
	double** gw_conc_lay{ NULL };
	double* solute_deposit{ NULL };
	double* cum_solute_deposit{ NULL };
	double* soil_rechr{ NULL };
	double* soil_rechr_conc{ NULL };
	double** soil_rechr_conc_lay{ NULL };
	double* potential{ NULL };
	double* potential_mWQ{ NULL };
	double** potential_mWQ_lay{ NULL };
	double* direct_excs{ NULL };
	double* direct_excs_mWQ{ NULL };
	double** direct_excs_mWQ_lay{ NULL };
	double* soil_moist{ NULL };
	double* soil_moist_conc{ NULL };
	double** soil_moist_conc_lay{ NULL };
	double* soil_lower_max{ NULL };
	double* soil_lower{ NULL };
	double* soil_lower_conc{ NULL };
	double** soil_lower_conc_lay{ NULL };
	double* soil_gw{ NULL };
	double* soil_gw_conc{ NULL };
	double** soil_gw_conc_lay{ NULL };
	double* gw_flow{ NULL };
	double* gw_flow_conc{ NULL };
	double** gw_flow_conc_lay{ NULL };
	double* soil_ssr{ NULL };
	double* soil_ssr_conc{ NULL };
	double** soil_ssr_conc_lay{ NULL };
	double* rechr_ssr{ NULL };
	double* rechr_ssr_conc{ NULL };
	double** rechr_ssr_conc_lay{ NULL };
	double* soil_runoff{ NULL };
	double* soil_runoff_cWQ{ NULL };
	double** soil_runoff_cWQ_lay{ NULL };
	double* cum_soil_ssr{ NULL };
	double* cum_soil_ssr_mWQ{ NULL };
	double** cum_soil_ssr_mWQ_lay{ NULL };
	double* cum_rechr_ssr{ NULL };
	double* cum_Sd_ssr{ NULL };
	double* cum_Sd_gw{ NULL };
	double* cum_lower_ssr{ NULL };
	double* cum_rechr_ssr_mWQ{ NULL };
	double** cum_rechr_ssr_mWQ_lay{ NULL };
	double* cum_soil_runoff{ NULL };
	double* cum_soil_runoff_mWQ{ NULL };
	double** cum_soil_runoff_mWQ_lay{ NULL };
	double* cum_runoff_to_ssr{ NULL };
	double* cum_runoff_to_Sd{ NULL };
	double* cum_runoff_to_Sd_mWQ{ NULL };
	double** cum_runoff_to_Sd_mWQ_lay{ NULL };
	double* cum_redirected_residual{ NULL };
	double* cum_redirected_residual_mWQ{ NULL };
	double** cum_redirected_residual_mWQ_lay{ NULL };
	double* soil_gw_D{ NULL };
	double* soil_ssr_D{ NULL };
	double* gw_flow_D{ NULL };
	double* soil_runoff_D{ NULL };
	double* HK_V{ NULL };
	double* HK_A{ NULL };
	double* culvert_Q{ NULL };
	double* culvert_water_H{ NULL };
	double* culvert_water_A{ NULL };
	double* culvert_water_V{ NULL };
	double* culvert_over_Q{ NULL };
	double* culvert_evap{ NULL };
	double* cum_culvert{ NULL };
	double* cum_culvert_over{ NULL };
	double* HD{ NULL };
	double* redirected_residual{ NULL };
	double* redirected_residual_conc{ NULL };
	double** redirected_residual_conc_lay{ NULL };
	double* infil_act{ NULL };
	double* infil_act_conc{ NULL };
	double** infil_act_conc_lay{ NULL };
	double* cum_infil_act{ NULL };
	double* cum_infil_act_mWQ{ NULL };
	double** cum_infil_act_mWQ_lay{ NULL };
	double* infil_act_D{ NULL };
	double* tile_flow{ NULL };
	double* tile_flow_conc{ NULL };
	double** tile_flow_conc_lay{ NULL };
	double* Dequiv_depth{ NULL };
	double* x{ NULL };
	double* Dw{ NULL };

	// local variables
	double* cum_soil_gw{ NULL };
	double* cum_soil_gw_mWQ{ NULL };
	double** cum_soil_gw_mWQ_lay{ NULL };
	double* cum_gw_flow{ NULL };
	double* cum_gw_flow_mWQ{ NULL };
	double** cum_gw_flow_mWQ_lay{ NULL };
	double* cum_hru_condense{ NULL };
	double* cum_Sd_evap{ NULL };
	double* soil_moist_Init{ NULL };
	double** soil_moist_conc_Init_lay{ NULL };
	double* soil_bottom_Init{ NULL };
	double** soil_bottom_conc_Init_lay{ NULL };
	double* soil_rechr_Init{ NULL };
	double** soil_top_conc_Init_lay{ NULL };
	double* Sd_Init{ NULL };
	double* gw_Init{ NULL };
	double* soil_moist_conc_Init{ NULL };
	double* soil_bottom_conc_Init{ NULL };
	double* soil_top_conc_Init{ NULL };
	double* Sd_conc_Init{ NULL };
	double** Sd_conc_Init_lay{ NULL };
	double* gw_conc_Init{ NULL };
	double** gw_conc_Init_lay{ NULL };

	double* snowinfil_buf{ NULL };
	double* runoff_buf{ NULL };
	double* meltrunoff_buf{ NULL };
	double* hru_evap_buf{ NULL };

	// declared parameters

	const double* Sdmax{ NULL };
	const double* Sdinit{ NULL };
	const double* Sd_conc_init{ NULL };
	const double** Sd_conc_init_lay{ NULL };
	const double* gw_max{ NULL };
	const double* gw_init{ NULL };
	const double* gw_conc_init{ NULL };
	const double** gw_conc_init_lay{ NULL };
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
	const double* rain_conc{ NULL };
	const double** rain_conc_lay{ NULL };
	const double* atmos_mWQ{ NULL };
	const double** atmos_mWQ_lay{ NULL };
	const double* sr_mix_rate{ NULL };
	const double* parleach{ NULL };
	const double* channel_slope{ NULL };
	const double* CV_SWE{ NULL };
	const double* side_slope{ NULL };
	const double* culvert_diam{ NULL };
	const double* culvert_water_Dmax{ NULL };
	const double* number_culverts{ NULL };

	const double* Ka{ NULL };
	const double* Kb{ NULL };
	const double* Di{ NULL };
	const double* Dd{ NULL };
	const double* soil_poro_moist{ NULL };
	const double* L{ NULL };
	const double* r{ NULL };


	const long* soil_withdrawal{ NULL };
	const long** soil_withdrawal_Tables{ NULL };
	const long* culvert_type{ NULL };
	const long* cov_type{ NULL };
	const long* transp_limited{ NULL };
	const long* soil_ssr_runoff{ NULL };
	const long* inhibit_evap{ NULL };
	const long* calcN{ NULL }; // Status of nitrogen simulation
	const long* calcP{ NULL }; // Status of phosphorus simulation
	const long* calcC{ NULL }; // Status of organic carbon simulation


	// variable inputs
	const double* infil{ NULL };
	const double* snowinfil{ NULL };
	const double* meltrunoff{ NULL }; // frozen melt runoff
	const double* runoff{ NULL };     // liquid runoff
	const double* hru_evap{ NULL };
	const double* SWE{ NULL };
	const double* SWE_max{ NULL };
	const double* SWE_conc{ NULL };
	const double** SWE_conc_lay{ NULL };

	// variable put inputs
	double* conc_soil_rechr{ NULL };
	double** conc_soil_rechr_lay{ NULL };
	double* conc_soil_lower{ NULL };
	double** conc_soil_lower_lay{ NULL };
	double* conc_soil_moist{ NULL };
	double** conc_soil_moist_lay{ NULL };
	double* surfsoil_solub_mWQ{ NULL };
	double** surfsoil_solub_mWQ_lay{ NULL };

	// variable put inputs
	double* hru_actet{ NULL };
	double* hru_cum_actet{ NULL };

	// local allocated arrays

	double* redirected_residual_0{ NULL };
	double* Sd_0{ NULL };
	double* gw_0{ NULL };
	double* soil_rechr_0{ NULL };
	double* soil_moist_0{ NULL };
	double* soil_lower_0{ NULL };
	double* hru_evap_0{ NULL };
	double* gw_flow_0{ NULL };
	double* hru_actet_0{ NULL };
	double* hru_cum_actet_0{ NULL };
	double* cum_redirected_residual_0{ NULL };
	double* cum_hru_condense_0{ NULL };
	double* cum_Sd_evap_0{ NULL };
	double* cum_Sd_ssr_0{ NULL };
	double* cum_Sd_gw_0{ NULL };
	double* cum_lower_ssr_0{ NULL };
	double* cum_infil_act_0{ NULL };
	double* cum_gw_flow_0{ NULL };
	double* cum_soil_ssr_0{ NULL };
	double* cum_rechr_ssr_0{ NULL };
	double* cum_soil_runoff_0{ NULL };
	double* cum_runoff_to_Sd_0{ NULL };
	double* cum_runoff_to_ssr_0{ NULL };
	double* cum_soil_gw_0{ NULL };
	double* cum_solute_deposit_0{ NULL };

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Add_WQ(const long hru, double* var, double** var_cWQ, double* var2, double** var2_cWQ, double* var3, double** var3_cWQ);
	void Set_WQ(const long hru, double* var, double* var_cWQ, double amount, double amount_cWQ);
	void Reset_Basin_WQ(const long hru, double* var, double* var_cWQ);
	void Reset_WQ(const long hru, double* var, double* var_cWQ);
	void Reset_WQ(const long hru, double* var, double** var_cWQ_lay);

	void Save();
	void Restore(const long hh);
	void copy_array(double* from, double* to);
	void restore_hru(double* from, double* to, const long hh);

	double FunctX(const double x);
	void Sd_to_soil_mass(double Sdmass_2_soil);
	ClassWQ_Soil* klone(string name) const;
};


#endif // !CLASSWQ_SOIL
