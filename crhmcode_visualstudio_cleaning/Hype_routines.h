// 04/19/18
//---------------------------------------------------------------------------
#ifndef Hype_routinesH
#define Hype_routinesH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 5
#define maxsoillayers2 2
#define maxsoillayers 3

using namespace std;




const float thetalow = 0.1;                     // Low(?) moisture coefficient (thetalow)
const float thetaupp = 0.5;                     // high(?) moisture coefficient (thetaupp)
const float bulkdensity = 1300;
//const float soilcoh = 1.0; // soilpar(float m_soilcoh, long isoil);
const float sreroexp = 0.0; // genpar(float m_sreroexp); surface runoff erosion exponent
const float filtPbuf = 1.0; // landpar(float m_filtPbuf, long iluse);
const float filtPother = 1.0; // landpar(float m_filtPbuf, long iluse);
const float filtPinner = 1.0; // landpar(float m_filtPbuf, long iluse);
const float pprelmax = 1.0; // landpar(float m_filtPbuf, long iluse);
const float pprelexp = 1.0; // genpar(float m_filtPbuf, long iluse);
const float Kfr = 1.0; // model parameter freundlich
const float Nfr = 1.0; // model parameter freundlichmodel parameter freundlich
const float Kadsdes = 1.0; // model parameter freundlich, adsorption or desportion rate (1/d)

const float halfsatTPwater = 0.05;    // half stauration concentration, production in water (mg P/L)
const float maxprodwater = 0.5;     // maximum part of IN/SRP pool that can be used for production per timestep
const float maxdegradwater = 0.5;     // maximum part of ON/PP/OC pool that can be degraded per timestep
const float NPratio = 1.0 / 7.2; // ratio for production/mineralisation in water
const float NCratio = 5.7;     // NC ratio for production/mineralisation in water (värde från BIOLA)
const float maxdenitriwater = 999; // USE HYPEVARIABLES, ONLY
const float halfsatINwater = 999; //USE HYPEVARIABLES, ONLY

const float soilerod = 1.0;
const float satact = 1.0;
const float thetapow = 1.0;
const float smfdenitlim = 0.1; // limitation parameter of moisturefactor (mm) (smfdenitlim)
const float smfdenitpow = 1.0; // exponent of moisturefactor (smfdenitpow)
const float halfsatINsoil = 1.0;
const float ldprodpp = 1.0;
const float ldprodsp = 1.0;

const long i_in = 0; // inorganic nitrogen
const long i_on = 1; // organic nitrogen
const long i_sp = 2; // soluble (reactive) phosphorus, i.e. phosphate
const long i_pp = 3; // particulate phosphorus
const long i_oc = 4; // (dissolved) organic carbon





class ClassWQ_Hype : public ClassModule {
public:

	long dayno;
	long nstep;

	ClassWQ_Hype(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

	// declared parameter

	const float *hru_area; //
	const float *hru_GSL; // ground slope
	const float *soil_rechr_max;
	const float *soil_moist_max;

	const long *ccmax1; // crop cover during summer
	const long *ccmax2; // crop cover during winter and all year for year round
	const long *gcmax1; // ground cover during summer
	const long *gcmax2; // ground cover during winter and all year for year round

	const long *baredayno1; // spring ploughing
	const long *baredayno2; // sow date/beginning of growing season
	const long *baredayno3; // harvest
	const long *baredayno4; // autumn ploughing
	const long *baredayno5; // winter crops sowing date

	const float *klh;    // transformation rate of fastC to humusC (d-1)
	const float *klo;    // degradation fastC (d-1)
	const float *kho;    // degradation humusC (d-1)
	const float *kof;    // transformation to fastC (d-1)
	const float *koflim; // threshold for transformation to fastC (-)
	const float *minc;   // fraction mineralisation to DIC (-)
	const float *soimf;  // satuaration soilmoisture factor (-)
	const float *soim;   // rate soilmoisture factor (-)
	const float *soimr;  // rate soilmoisture factor (-)

	const long *calcN; // Status of nitrogen simulation
	const long *calcP; // Status of phosphorus simulation
	const long *calcC; // Status of organic carbon simulation

	const long *conductN; // Status of nitrogen simulation
	const long *conductP; // Status of phosphorus simulation

	const float *fertNamount1;
	const float *fertNamount2;
	const float *fertPamount1;
	const float *fertPamount2;
	const float *manNamount1;
	const float *manNamount2;
	const float *manPamount1;
	const float *manPamount2;
	const float *resNamount;
	const float *resPamount;
	const float *resCamount;
	const float *resfast;
	const float *resdown;
	const float *fertdown1;
	const float *fertdown2;
	const float *mandown1;
	const float *mandown2;

	const long *fertday1;
	const long *fertday2;
	const long *manday1;
	const long *manday2;
	const long *resdayno;
	const long *fertperiod;
	const long *litterperiod;

	const float *closewater;
	const float *buffer;
	const float *part;
	const float *inorgpart;
	const float *fastpart;

	const float *wp; // water content at wilting point (mm)
	const float **wp_lay; // [maxsoillayers]
	const float *pw; // water content: total porosity (mm)
	const float **pw_lay; // [maxsoillayers]
	const float *fc; // water content at field capacity
	const float **fc_lay; // [maxsoillayers]
	const float *ep; // water content: effectiv porosity
	const float **ep_lay; // [maxsoillayers]
	const float *N_uptake; //
	const float **N_uptake_lay; // 
	const float *P_uptake; //
	const float **P_uptake_lay; //
	const float *denpar;
	const float *cohesion;      // (kPa)
	const float *erodibility;   // (g/J)
	const float *parminfN; // nitrification
	const float *parminfP; // nitrification
	const float *pardegrhN; // nitrification
	const float *pardegrhP; // nitrification
	const float *pardisfN; // nitrification
	const float *pardisfP; // nitrification
	const float *pardishN; // nitrification
	const float *pardishP; // nitrification

	const float *humusN_init;
	const float **humusN_init_lay;
	const float *humusP_init;
	const float **humusP_init_lay;
	const float *humusC_init;
	const float **humusC_init_lay;
	const float *fastN_init;
	const float **fastN_init_lay;
	const float *fastP_init;
	const float **fastP_init_lay;
	const float *fastC_init;
	const float **fastC_init_lay;

	// declared variables

	float *humusP; // humusP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **humusP_lay; //  (soillayer,class, subbasin)
	float *humusN; // humusN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **humusN_lay;
	float *humusC; // humusC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **humusC_lay;
	float *fastN;  // fastN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **fastN_lay;
	float *fastP;  // fastP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **fastP_lay;
	float *fastC;  // fastC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
	float **fastC_lay;

	float *conc_top;   // concentration of inorganic nitrogen *** from soilstate
	float **conc_top_lay;
	float *conc_bottom;   // concentration of organic nitrogen *** from soilstate
	float **conc_bottom_lay;
	float *conc_below;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
	float **conc_below_lay;
	float *conc_i_pp;   // concentration of particulate phosphorus *** from soilstate *** from soilstate

	float *sources_plant;
	float **sources_plant_lay;
	float *sources_fertilizer;
	float **sources_fertilizer_lay;

	float *sink;
	float **sink_lay;  // sink of nutrients in this subroutine  (kg/km2
	float *source;  // load from fertilizer and plant residues (kg/timestep)
	float **source_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
	float *denitrification;  // load from fertilizer and plant residues (kg/timestep)
	float **denitrification_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
	float *temp; //
	float **temp_lay;  //

	float *water;  // soil moisture *** from soilstate
	float **water_lay;  // layer oil moisture
	float *thickness; // thickness of soil layers
	float **thickness_lay; // [maxsoillayers]
	float *partP;  // partP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L *** from soilstate
	float **partP_lay;

	float *PPrelpool;  // pool of delayed PP in runoff (mg/m2) *** from soilstate
	float **PPrelpool_lay;
	float *erodedP; // eroded phosphorus (kg/km2)
	float *fracminP; // part of eroded P in mineral form
	float *csurface; // total runoff (surfacerunoff, tilerunoff, soilrunoff layer 1-3)
	float *totflow; // total runoff (surfacerunoff, tilerunoff, soilrunoff layer 1-3)
	float *nitrification; // nitrification
	float *cropuptake; // of i_in

					   // variable inputs

	const float *SWE;
	const float *net_rain;
	const float *runoff;
	const float *hru_t;
	const float *soil_moist;
	const float *soil_rechr;
	const float *soil_rechr_to_Hype_D_mWQ;
	const float *soil_lower_to_Hype_D_mWQ;

	void decl(void);
	void init(void);
	void run(void);
	void finish(bool good);

	ClassWQ_Hype* klone(string name) const;

	float tempfactor(float temp);

	static float moisturefactor(float sm, float wp, float sum, float thickm, float satact, float thetapow, float thetalow, float thetaupp); // temporary creation

	void balance_spsoil(const float kfr, const float nfr, const float kadsdes);

	// PoolPP and SRP_Conc called by reference.
	void freundlich(long lin, float *PoolPP, float *SRP_Conc, const float Vol, const float LayerThick, const float Kfr, const float Nfr, const float Kadsdes);

	// runoff_pp_by_erosion.f

	void runoff_pp_by_erosion(const float prec, float surfacerunoff,
		float totflow, float csurface, float **csoil_top_lay, float **csoil_bottom_lay); // !!! fix - call commented out

	void calculate_erosion(const float prec, const float thickness_lay, float surfacerunoff, float erodedP, const float cohesion,
		const float erodibility, const float snow, const float sreroexp, float **partP_lay, float **humusP_lay, float fracminP);

	void calculate_transport(const float erodingflow, float erodedP);   // calculate amount of PP transported in fast flow paths  (kg/km2);

																		// soil_np_processes.f

	void soil_np_processes(const long calcN, const long calcP, const float calcC, const float area, const float **fc_lay, const float **ep_lay,
		const float **N_uptake_lay, const float **P_uptake_lay, float **thickness_lay, const long fertperiod,
		const long litterperiod, float **source_lay, float *nitrification,
		float **denitrification_lay, float *cropuptake, float **sources_top_lay, float **sources_bottom_lay,
		const float pardisfN, const float pardisfP, const float pardishN, const float pardishP, const float parminfN,
		const float parminfP, const float pardegrhN, const float denpar, const float pardegrhP);

	void soil_pool_transformations(const long calcN, long long calcP, const float **wp, const float **fc,
		const float **ep, float **thickness_lay, float **source_lay,
		const float pardisfN, const float pardisfP, const float pardishN, const float pardishP,
		const float minfNpar, const float minfPpar, const float degrhNpar, const float degrhPpar); // requires soil temperature

	void  plant_uptake(const long calcN, const long calcP, const float **N_uptake_lay, const float **P_uptake_lay, const float **wp_lay,
		float **thickness_lay, float **soil_lay,
		float **csoil_top_lay, float **csoil_bottom_lay, float **sink_lay);

	void  crop_sources(const long calcN, const long calcP, const float calcC, const long fertperiod, const long litterperiod, const float area,
		float **thickness_lay, float **sources_top_lay, float **sources_bottom_lay);

	void soil_denitrification(const float maxwc, const float denpar, const float *soil_moist, const float stemp,
		float **csoil_top_lay, float **sink_lay);

	void add_source_to_water(const float vol, long n, float conc, float source);

	void add_source_to_water(const float vol, const long n, float *conc, const float source);

	void new_concentration(const float pool, float vol, float conc);

	void new_concentration(const float pool, const float vol, float *conc); // return by reference

	void new_concentration(const float pool, const float vol, float **conc); // special to handle dimension reversal

	void retention_pool(const long n, float **pool, float *sink, long CRHM_array = -1);

	void retention_pool(const long n, float *pool, float *sink);

	void production_pool(const long n, float *pool, const float source); // return by reference

	void production_pool(const long n, float *pool, const float *source);

	void production_pool(const long n, float **pool, const float *source, long CRHM_array = -1);

	void production_pool(const long n, float **pool, const float source[][numsubstances], long Application = -1);

	void soil_carbon_processes(const float calcC, const float **wp_lay, const float **fc_lay, const float **ep_lay, const float **pw_lay, float **thickness_lay,
		const float klh, const float klo, const float kho, const float kof, const float koflim,
		const float minc, const float soimf, const float soimr);

	void soil_carbon_pool_transformations(const float Calc, const float **wp, const float **fc, const float **pw, float **thickness_lay,
		const float klh, const float klo, const float kho, const float kof, const float koflim,
		const float minc, const float soimf, const float soimr);

	float tempfactor2(const float temp);

	static float exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp);

	static float halfsatconcfactor(const float conc, const float par);

	float static SUM(float XX[][numsubstances], long Substance);

	float static SUM(float *XX);
};

inline int CalculateDaysInYear(unsigned short year) {
	int days;
	bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (!leapyear)
		days = 365;
	else
		days = 366;
	return days;
};

#endif