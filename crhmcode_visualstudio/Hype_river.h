// 01/23/18
//---------------------------------------------------------------------------

#ifndef Hype_riverH
#define Hype_riverH
//---------------------------------------------------------------------------

#include "Hype_routines.h"

using namespace std;

class ClassWQ_River : public ClassWQ_Hype {
public:

	ClassWQ_River(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassWQ_Hype(Name, Version, Lvl) {};

	// declared variables

	float *TPmean_r;   // 365-day mean Total Phosphorus concentration of lake (laketype,subbasin)
	float *temp_r;
	float *temp10_r;
	float *temp20_r;

	float *water_r;
	float **water_r_lay;  //
	float *Psed;

	// variable put input
	float *conc;
	float **conc_lay;

	// parameters
	const float *catchment_area; //
	const float *depth; //
	const float *transq; //
	const float *qbank; //
	const float *riverq; //
	const float *denpar;
	const float *denparl;
	const float *prodNpar;
	const float *prodPpar;
	const float *limpppar;
	const float *sedexppar;
	const float *prodpar;
	const float *limppar;
	const float *watertemp;
	const float *waterTPmean;
	const long *i_in; // inorganic nitrogen
	const long *i_on; // organic nitrogen
	const long *i_sp; // soluble (reactive) phosphorus, i.e. phosphate
	const long *i_pp; // particulate phosphorus
	const long *i_oc; // (dissolved) organic carbon
	const long *conductN; // Status of nitrogen simulation
	const long *conductP; // Status of phosphorus simulation
	const long *rivertype; // river type (local or main)
	const float *Psed_init;

	// parameter inputs
	const float *soil_moist_max;

	// variable inputs
	const float *hru_t;
	const float *soil_moist;
	const float *SRP_conc;   // concentration of soil moisture per land-soil
	const float **SRP_conc_lay;

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_River* klone(string name) const;

	void np_processes_in_river(const long rivertype, const float area, const float depth, const float transq, const float Qbank, const float denpar,
		const float denparl, const float prodNpar, const float prodPpar, const float sedexppar, const float limpppar); // OK

	void calculate_river_tpmean(const long itype); // OK

	void production_mineralisation(const long rivertype, const float area, const float prodNpar, const float prodPpar, const float limpppar,
		const float depth = 0.0); // OK

	void sedimentation_resuspension(const long rivertype, const float area, const float sedexppar, const float riverq, const float qbank, const float depth); // OKJ

	void denitrification_water(const long rivertype, const float area, const float denpar); // OK

	void oc_processes_in_river(const long rivertype, const float area, const float depth, const float prodpar, const float limpppar); // OK

	void oc_production_mineralisation(const float area, float prodpar, float limpppar, float water, float conc, float watertemp,
		float waterTPmean, float temp10, float temp20, float depth); // OK
};

class ClassWQ_REWroute : public ClassModule {
public:

	ClassWQ_REWroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

	long inflowCnt;
	long gwCnt;

	// declared variables
	float *rew;
	float *gwrew;

	float **inflow_All;
	float **gw_All;

	float *inflow;        // [nhru]
	float *cuminflow;     // [nhru]
	float *outflow;       // [nhru]
	float *cumoutflow;    // [nhru]

	float *gwinflow;        // [nhru]
	float *cumgwinflow;     // [nhru]
	float *gwoutflow;       // [nhru]
	float *cumgwoutflow;    // [nhru]

	float *flow;     // [BASIN] all HRUs
	float *flow_s;   // [BASIN] all HRUs
	float *cumflow;  // [BASIN] all HRUs

	float *gwflow;     // [BASIN] all HRUs
	float *gwflow_s;   // [BASIN] all HRUs
	float *cumgwflow;  // [BASIN] all HRUs

	float *WS_Ktravel_var;         // [nhru]
	float *WS_gwKtravel_var;         // [nhru]

	float *culvert_Q;
	float *culvert_water_H;
	float *culvert_water_A;
	float *culvert_water_V;
	float *culvert_water_O;
	float *culvert_evap;
	float *cum_culvert;
	float *cum_culvert_over;
	float *HD;

	ClassMuskingum *inflowDelay;
	ClassMuskingum *gwDelay;

	ClassClark *Clark_inflowDelay;
	ClassClark *Clark_gwDelay;

	// declared parameters

	const float *watershed_area;      // [watershed area (basin)]
	const float *RB_area;        // [RBs (nhru)]

	const float *WS_route_n;         // [nhru]
	const float *WS_route_R;         // [nhru]
	const float *WS_route_S0;        // [nhru]
	const float *WS_route_L;         // [nhru]
	const long  *WS_Channel_shp;      // [nhru]

	const float *WS_Lag;             // [nhru]
	const float *WS_route_X_M;       // [nhru]
	const long  *WS_whereto;         // [nhru]
	const long  *WS_order;           // [nhru]

	const float *WS_gwLag;           // [nhru]
	const float *WS_gwroute_X_M;     // [nhru]
	const long  *WS_gwwhereto;       // [nhru]
	const long  *WS_gworder;         // [nhru]

	const float *WS_Kstorage;     // [nhru]
	const float *WS_gwKstorage;   // [nhru]

	const float *WS_channel_slope;
	const float *WS_side_slope;
	const float *WS_culvert_diam;
	const float *WS_culvert_water_Dmax;
	const float *WS_number_culverts;

	const long *WS_culvert_type;

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);
	void Culvert(long hh);

	ClassWQ_REWroute* klone(string name) const;
};
#endif
