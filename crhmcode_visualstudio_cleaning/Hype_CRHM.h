// 02/13/18
//---------------------------------------------------------------------------
#ifndef Hype_CRHMH
#define Hype_CRHMH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 5
#define maxsoillayers2 2
#define maxsoillayers 3

using namespace std;

class ClassWQ_Soil : public ClassModule {
public:

	ClassWQ_Soil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

	long snowinfilDiv;
	long meltrunoffDiv;
	long runoffDiv;
	long evapDiv;

	// declared observation variables

	// declared variables
	float *Sd;
	float *Sd_conc;
	float **Sd_conc_lay;
	float *gw;
	float *gw_conc;
	float **gw_conc_lay;
	float *solute_deposit;
	float *cumsolute_deposit;
	float *soil_rechr;
	float *soil_rechr_conc;
	float **soil_rechr_conc_lay;
	float *soil_moist;
	float *soil_moist_conc;
	float **soil_moist_conc_lay;
	float *soil_lower;
	float *soil_lower_conc;
	float **soil_lower_conc_lay;
	float *soil_gw;
	float *soil_gw_conc;
	float **soil_gw_conc_lay;
	float *gw_flow;
	float *gw_flow_conc;
	float **gw_flow_conc_lay;
	float *soil_ssr;
	float *soil_ssr_conc;
	float **soil_ssr_conc_lay;
	float *rechr_ssr;
	float *rechr_ssr_conc;
	float **rechr_ssr_conc_lay;
	float *soil_rechr_to_Hype_conc;
	float *soil_rechr_to_Hype_Acc_mWQ;
	float *soil_rechr_to_Hype_D_mWQ;
	float *soil_lower_to_Hype_mWQ;
	float *soil_lower_to_Hype_Acc_mWQ;
	float *soil_lower_to_Hype_D_mWQ;
	float *soil_runoff;
	float *soil_runoff_conc;
	float *cum_soil_ssr;
	float *cum_soil_ssr_mWQ;
	float **cum_soil_ssr_mWQ_lay;
	float *cum_rechr_ssr;
	float *cum_Sd_ssr;
	float *cum_Sd_gw;
	float *cum_lower_ssr;
	float *cum_rechr_ssr_mWQ;
	float **cum_rechr_ssr_mWQ_lay;
	float *cum_soil_runoff;
	float *cum_soil_runoff_mWQ;
	float **cum_soil_runoff_mWQ_lay;
	float *cum_runoff_to_ssr;
	float *cum_runoff_to_Sd;
	float *cum_runoff_to_Sd_mWQ;
	float **cum_runoff_to_Sd_mWQ_lay;
	float *cum_redirected_residual;
	float *cum_redirected_residual_mWQ;
	float *soil_gw_D;
	float *soil_ssr_D;
	float *gw_flow_D;
	float *soil_runoff_D;
	float *HK_V;
	float *HK_A;
	float *culvert_Q;
	float *culvert_water_H;
	float *culvert_water_A;
	float *culvert_water_V;
	float *culvert_over_Q;
	float *culvert_evap;
	float *cum_culvert;
	float *cum_culvert_over;
	float *HD;
	float *redirected_residual;
	float *redirected_residual_conc;
	float **redirected_residual_conc_lay;
	float *infil_act;
	float *infil_act_conc;
	float **infil_act_conc_lay;
	float *cum_infil_act;
	float *cum_infil_act_mWQ;
	float *infil_act_D;

	// local variables
	float *cum_soil_gw;
	float *cum_soil_gw_mWQ;
	float *cum_gw_flow;
	float *cum_gw_flow_mWQ;
	float *cum_hru_condense;
	float *cum_Sd_evap;
	float *soil_moist_Init;
	float *soil_lower_Init;
	float *soil_rechr_Init;
	float *Sd_Init;
	float *gw_Init;
	float *soil_moist_conc_Init;
	float *soil_lower_conc_Init;
	float *soil_rechr_conc_Init;
	float *Sd_conc_Init;
	float *gw_conc_Init;

	float *snowinfil_buf;
	float *runoff_buf;
	float *meltrunoff_buf;
	float *hru_evap_buf;

	// declared parameters
	const float *Sdmax;
	const float *Sd_init;
	const float *Sd_conc_init;
	const float **Sd_conc_init_lay;
	const float *gw_max;
	const float *gw_init;
	const float *gw_conc_init;
	const float **gw_conc_init_lay;
	const float *gw_K;
	const float *basin_area;   // [BASIN]
	const float *hru_area;
	const float *soil_rechr_max;
	const float *soil_rechr_init;
	const float *soil_rechr_conc_init;
	const float **soil_rechr_conc_init_lay;
	const float *soil_moist_max;
	const float *soil_moist_init;
	const float *soil_moist_conc_init;
	const float **soil_moist_conc_init_lay;
	const float *soil_gw_K;
	const float *rechr_ssr_K;
	const float *lower_ssr_K;
	const float *Sd_ssr_K;
	const float *Sd_gw_K;
	const float *c_rain_N_cWQ;
	const float *Atmos_N_mWQ;
	const float *channel_slope;
	const float *side_slope;
	const float *culvert_diam;
	const float *culvert_water_Dmax;
	const float *number_culverts;
	const long *soil_withdrawal;
	const long **soil_withdrawal_Tables;

	const long *culvert_type;
	const long *cov_type;
	const long *transp_limited;
	const long *soil_ssr_runoff;
	const long *inhibit_evap;

	const long *calcN; // Status of nitrogen simulation
	const long *calcP; // Status of phosphorus simulation
	const long *calcC; // Status of organic carbon simulation


					   // variable inputs
	const float *infil;
	const float *snowinfil;
	const float *meltrunoff; // frozen melt runoff
	const float *runoff;     // liquid runoff
	const float *hru_evap;
	const float *SWE_conc;
	const float *conc_top;
	const float **conc_top_lay;
	const float *conc_bottom;
	const float **conc_bottom_lay;
	const float *conc_below;
	const float **conc_below_lay;

	// variable put inputs
	float *hru_actet;
	float *hru_cum_actet;


	// local allocated arrays

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Add_WQ(const long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
	void Add_WQ(const long hru, float *var, float *var_cWQ, float *var2, float *var2_cWQ, float *var3, float *var3_cWQ);
	void Sub_WQ(const long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
	void Sub_WQ(const long hru, float *var, float *var_cWQ, float *var2, float *var2_cWQ, float *var3, float *var3_cWQ);
	void Set_WQ(const long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
	void Reset_WQ(const long hru, float *var, float *var_cWQ);

	ClassWQ_Soil* klone(string name) const;
};

class ClassWQ_Netroute : public ClassModule {
public:

	ClassWQ_Netroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

	long meltrunoffDiv;
	long soil_ssrDiv;
	long soil_runoffDiv;
	long soil_gwDiv;

	// declared variables
	float *inflow;
	float *inflow_conc;
	float *cuminflow;
	float *cuminflow_mWQ;
	float *outflow;
	float *outflow_conc;
	float *outflow_diverted;
	float *outflow_diverted_conc;
	float *cumoutflow_diverted;
	float *cumoutflow_diverted_mWQ;
	float *cumoutflow;
	float *cumoutflow_mWQ;
	float *gwinflow;
	float *gwinflow_conc;
	float *gwoutflow_diverted;
	float *gwoutflow_diverted_conc;
	float *gwcumoutflow_diverted;
	float *gwcumoutflow_diverted_mWQ;
	float *HRU_cumbasinflow;
	float *HRU_cumbasinflow_conc;

	float *ssrinflow;
	float *ssrinflow_conc;
	float *ssrcuminflow;
	float *ssrcuminflow_mWQ;
	float *ssroutflow;
	float *ssroutflow_conc;
	float *ssrcumoutflow;
	float *ssrcumoutflow_mWQ;

	float *runinflow;
	float *runinflow_conc;
	float *runcuminflow;
	float *runcuminflow_mWQ;
	float *runoutflow;
	float *runoutflow_conc;
	float *runcumoutflow;
	float *runcumoutflow_mWQ;

	float *gwoutflow;
	float *gwoutflow_conc;
	float *gwcuminflow;
	float *gwcuminflow_mWQ;
	float *gwcumoutflow;
	float *gwcumoutflow_mWQ;

	float *basinflow;     // [BASIN] all HRUs
	float *basinflow_conc;     // [BASIN] all HRUs
	float *basinflow_s;   // [BASIN] all HRUs
	float *cumbasinflow;  // [BASIN] all HRUs
	float *cumbasinflow_mWQ;  // [BASIN] all HRUs
	float *basingw;       // [BASIN} all HRUs
	float *basingw_conc;       // [BASIN} all HRUs
	float *basingw_s;     // [BASIN} all HRUs
	float *cumbasingw;    // [BASIN} all HRUs
	float *cumbasingw_mWQ;    // [BASIN} all HRUs

	float *soil_ssr_Buf;    // buffered
	float *soil_runoff_Buf; // buffered
	float *meltrunoff_Buf;  // buffered
	float *soil_gw_Buf;     // buffered

	float *cum_to_Sd;
	float *cum_to_Sd_mWQ;
	float *cum_to_soil_rechr;
	float *cum_to_soil_rechr_mWQ;

	ClassClark *hruDelay;
	ClassClark *ssrDelay;
	ClassClark *runDelay;
	ClassClark *gwDelay;

	ClassClark *hruDelay_cWQ;
	ClassClark *ssrDelay_cWQ;
	ClassClark *runDelay_cWQ;
	ClassClark *gwDelay_cWQ;

	// declared parameters
	const float *Kstorage;
	const float *Lag;
	const float *ssrKstorage;
	const float *ssrLag;
	const float *runKstorage;
	const float *runLag;
	const float *gwKstorage;
	const float *gwLag;

	const float *basin_area;        // [BASIN]
	const float *hru_area;
	const long  *whereto;
	const long  *order;
	const long  *gwwhereto;
	const float *Sdmax;
	const float *soil_rechr_max;
	const long  *Sd_ByPass;
	const long  *soil_rechr_ByPass;

	// variable inputs
	const float *soil_gw;
	const float *soil_gw_conc;
	const float *soil_ssr;
	const float *soil_ssr_gw_mWQ;
	const float *soil_runoff;
	const float *soil_runoff_gw_mWQ;
	const float *soil_ssr_conc;
	const float *soil_runoff_conc;

	// variable puts
	float *Sd;
	float *Sd_conc;
	float *soil_moist;
	float *soil_moist_conc;
	float *soil_lower;
	float *soil_lower_conc;
	float *soil_rechr;
	float *soil_rechr_conc;
	float *redirected_residual;
	float *redirected_residual_conc;
	float *cum_redirected_residual;
	float *cum_redirected_residual_mWQ;
	float *gw;
	float *gw_conc;

	// local allocated arrays

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Add_WQ(long hru, float *var, float *var_conc, float amount, float amount_conc);
	void Sub_WQ(long hru, float *var, float *var_conc, float *var2, float *var2_conc, float *var3, float *var3_conc);
	void Set_WQ(long hru, float *var, float *var_conc, float amount_conc, float amount);
	void Reset_WQ(long hru, float *var, float *var_conc);

	virtual float Function1(float *I, long hh);
	virtual float Function2(float *X, long hh);

	ClassWQ_Netroute* klone(string name) const;
};

class ClassWQ_ion : public ClassModule {
public:

	ClassWQ_ion(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared variables
	float *SWE_prev;
	float *layer_h2o;
	float **h2o_lay;
	float *layer_Csnow;
	float **Csnow_layers;
	float *layer_Csnow_prev;
	float **Csnow_layers_prev;
	long *ni_cur;
	long *ni_prev;

	// declared parameters
	const float *dz;
	const float *Dz;
	const float *Uz;
	const float *N_snow_layers;

	// variable inputs
	const float *SWE;
	const float *snowmelt_int_mWQ;

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void adjust_layers(void);
	void calc_layers(void);

	ClassWQ_ion* klone(string name) const;
};

class ClassWQ_pbsm : public ClassModule {
public:

	ClassWQ_pbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

	float hru_u_;

	// declared variables

	float *SWE;
	float *SWE_conc;
	float *Subl;
	float *Drift_in;
	float *Drift_in_cWQ;
	float *Drift_out;       // HRU composite drift
	float *Drift_out_cWQ;  // HRU composite drift
	float *SublH;
	float *DriftH;
	float *cumSubl;
	float *cumDrift;
	float *cumDriftIn;
	float *cumSno;
	float *cumDrift_mWQ;
	float *cumDriftIn_mWQ;
	float *cumSno_mWQ;
	float *Prob;
	float *snowdepth;
	float *BasinSnowLoss;
	float *BasinSnowGain;
	float *cumBasinSnowLoss;
	float *cumBasinSnowGain;
	float *cumBasinSnowLoss_mWQ;
	float *cumBasinSnowGain_mWQ;
	float *SnowAge;
	float *SWE_Init;
	long  *DrySnow;

	// declared parameters
	const float *fetch;
	const float *Ht;
	const float *distrib;
	const float *basin_area;
	const float *hru_area;
	const float *A_S;
	const float *u_D;
	const float *Drift_offset;
	const float *Drift_slope;
	const float *Subl_offset;
	const float *Subl_slope;
	const float *N_S;
	const float *c_snow_N_cWQ;
	const float *Atmos_N_mWQ;
	const long *inhibit_evap;
	const long *inhibit_bs;
	const long *inhibit_subl;

	// variable inputs
	const float *hru_t;
	const float *hru_rh;
	const float *hru_u;
	const float *hru_Uadjust;
	const float *net_snow;
	const long  *hru_newsnow;

	// local allocated arrays
	float *hru_basin;


	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	void Add_to_Drift_in_cWQ(long hru, float transport, float transport_WQ);
	void Add_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
	void Sub_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ);
	void Reset_WQ(long hru, float *var, float *var_cWQ);

	ClassWQ_pbsm* klone(string name) const;
};

#endif





