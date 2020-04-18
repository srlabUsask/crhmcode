// 01/23/18
//---------------------------------------------------------------------------

#ifndef Hype_lakeH
#define Hype_lakeH
//---------------------------------------------------------------------------

#include "Hype_routines.h"

using namespace std;

class ClassWQ_Lake : public ClassWQ_Hype {
public:

	ClassWQ_Lake(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassWQ_Hype(Name, Version, Lvl) {};

	// declared parameters

	const float *hru_area; //
	const float *hru_GSL; // ground slope
	const float *denpar;
	const float *cohesion;      // (kPa)
	const float *erodibility;   // (g/J)
	const float *sedpppar;   // (g/J)
	const float *limonpar;   // (g/J)
	const float *limpppar;   // (g/J)
	const float *prodPpar;   // (g/J)
	const float *closewater;
	const float *buffer;
	const float *prodNpar;
	const float *lake_depth;
	const float *pppar;
	const float *sppar;
	const long *calcN; // Status of nitrogen simulation
	const long *calcP; // Status of phosphorus simulation
	const long *sedonpar;
	const long *sedocpar;
	const long *laketype; // Lake or river type (1=local, 2=main/outlet
	const long *conductN; // Status of nitrogen simulation
	const long *conductP; // Status of phosphorus simulation

	const float *thickness; // thickness of soil layers
	const float **thickness_lay; // thickness of soil layers [maxsoillayers]
	const float *fc; // water content at field capacity
	const float **fc_lay; // thickness of soil layers [maxsoillayers]
	const float *ep; // water content: effectiv porosity
	const float **ep_lay; // water content: effectiv porosity [maxsoillayers]
	const float *wp; // water content at wilting point (mm)
	const float **wp_lay; // [maxsoillayers]

						  // declared variables

						  //float **water_lay;  //
	long **source_lay; // source of soil water nutrients through mineralizatio [numsubstances]
	float *sink;
	float **sink_lay;  // sink of nutrients in this subroutine  (kg/km2
	float **SRP_conc_lay;
	float **poolPP_lay;
	float *PPrelpool;  // pool of delayed PP in runoff (mg/m2)
	float **PPrelpool_lay;

	float *slowwater;   // concentration of soil moisture per land-soil
	float *temp_l; // temperature (laketype,subbasin)
	float *temp10_l;   // 10-day mean lake temperature (laketype,subbasin)
	float *temp20_l;   // 20-day mean lake temperature (laketype,subbasin)
	float *TPmean_l;   // 365-day mean Total Phosphorus concentration of lake (laketype,subbasin)
	float *concslow;   // concentration of soil moisture per land-soil
	float **concslow_lay;

	// variable put input
	float *conc_top;   // concentration of inorganic nitrogen *** from soilstate
	float **conc_top_lay;
	float *conc_bottom;   // concentration of organic nitrogen *** from soilstate
	float **conc_bottom_lay;
	float *conc_below;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
	float **conc_below_lay;

	// parameter inputs
	const float *soil_moist_max;

	// variable inputs
	const float *water;  // water stage of lake (mm) (laketype,subbasin)
	const float *SWE;
	const float *net_rain;
	const float *runoff;
	const float *hru_t;
	const float *soil_moist;
	const float *SRP_conc;   // concentration of soil moisture per land-soil
	const float *poolPP;   // concentration of soil moisture per land-soil
	const float *sources;  // load from fertilizer and plant residues (kg/timestep)
	const float **sources_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_Lake* klone(string name) const;

	void np_processes_in_lake(const long laketype, const float area, const float denpar, const long prodNpar, const float prodPpar, const long sedonpar, const float sedpppar,
		const float limonpar, const float limpppar); // OK

	void denitrification_water(const long laketype, const float area, const float denpar); // OK

	void production_mineralisation(const long laketype, const float area, const float prodNpar, const float prodPpar, const float limpppar,
		const float depth = 0.0); // OK

	void sedimentation_lake(const long laketype, const float area, const float sedonpar, const float sedpppar, const float limonpar, const float limpppar); // OK

	void sedimentation_lake(const long laketype, const float sedonpar, const float sedpppar, const float limonpar, const float limpppar); // OK

	void calculate_lake_tpmean(const long laketype); // OK

	void internal_lake_load(const long laketype, const float area); // OK

	void ClassWQ_Lake::oc_processes_in_lake(const long watertype, const long area, const long prodpar, const long limpppar, const long sedocpar);

	void oc_production_mineralisation(const float area, float prodpar, float limpppar, float water, float conc, float watertemp,
		float waterTPmean, float temp10, float temp20, float depth); // OK
	void ClassWQ_Lake::oc_sedimentation(const float area, const float sedocpar);
};

#endif