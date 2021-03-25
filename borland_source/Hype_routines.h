// 05/07/19
//---------------------------------------------------------------------------
#ifndef Hype_routinesH
#define Hype_routinesH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 5
#define maxsoillayers 3
#define maxsoillayers2 2
#define inorg 0 // where 0 - refractoryNpart
#define fast 1  // where 1 - fastpart

using namespace std;

class ClassWQ_Hype : public ClassModule {
public:

long dayno;
long nstep;

ClassWQ_Hype(string Name, String Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

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

const float *klh;    // transformation rate of labileC to refractoryC (d-1)
const float *klo;    // degradation labileC (d-1)
const float *kho;    // degradation refractoryC (d-1)
const float *kof;    // transformation to labileC (d-1)
const float *koflim; // threshold for transformation to labileC (-)
const float *minc;   // fraction mineralisation to DIC (-)
const float *soimf;  // satuaration soilmoisture factor (-)
const float *soim;   // rate soilmoisture factor (-)
const float *soimr;  // rate soilmoisture factor (-)

const long *calcN; // Status of nitrogen simulation
const long *calcP; // Status of phosphorus simulation
const long *calcC; // Status of organic carbon simulation
const long *Inhibit_Hype; // Skip Hype

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

const float *fertday1;
const float *fertday2;
const float *manday1;
const float *manday2;
const float *resdayno;

const float *fertperiod;
const long *litterperiod;

const float *part;
const float *manureNpart;
const float *manureNfastpart;

const float *wp; // water content at wilting point(mm)
const float **wp_lay; // [maxsoillayers]
const float *pw; // water content: total porosity(mm)
const float **pw_lay; // [maxsoillayers]
const float *fc; // water content at field capacity(mm)
const float **fc_lay; // [maxsoillayers]
const float *ep; // water content: effectiv porosity(mm)
const float **ep_lay; // [maxsoillayers]
const float *N_uptake; //
const float **N_uptake_lay; // 
const float *P_uptake; //
const float **P_uptake_lay; //
const float *pardenN; // nitrification
const float *parminfN; //
const float *parminfP; //
const float *pardegrhN; //
const float *pardegrhP; //
const float *pardisfN; //
const float *pardisfP; //
const float *pardishN; //
const float *pardishP; // 

const float *refractoryN_init;
const float **refractoryN_init_lay;
const float *refractoryP_init;
const float **refractoryP_init_lay;
const float *refractoryC_init;
const float **refractoryC_init_lay;
const float *labileN_init;
const float **labileN_init_lay;
const float *labileP_init;
const float **labileP_init_lay;
const float *labileC_init;
const float **labileC_init_lay;
const float *conc_top_init;
const float **conc_top_init_lay;
const float *conc_bottom_init;
const float **conc_bottom_init_lay;

// declared variables

float *refractoryP; // refractoryP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **refractoryP_lay; //  (soillayer,class, subbasin)
float *refractoryN; // refractoryN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **refractoryN_lay;
float *refractoryC; // refractoryC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **refractoryC_lay;
float *labileN;  // labileN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **labileN_lay;
float *labileP;  // labileP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **labileP_lay;
float *labileC;  // labileC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **labileC_lay;
float *DINpool;  // inorgN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **DINpool_lay;
float *DONpool;  // DON pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **DONpool_lay;
float *SRPpool;  // SRP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **SRPpool_lay;
float *DOPpool;  // DOP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **DOPpool_lay;

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
float *Temp;  // layer soil temperatures
float **Temp_lay;  //

float *water;  // soil moisture *** from soilstate
float **water_lay;  // layer oil moisture
float *thickness; // thickness of soil layers
float **thickness_lay; // [maxsoillayers]
float *partP;  // partP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L *** from soilstate
float **partP_lay;
float *uptakeN;  //
float **uptakeN_lay;
float *uptakeP;  //
float **uptakeP_lay;

float *fracminP; // part of eroded P in mineral form
float *nitrification; // nitrification
float *cropuptake; // of i_in

// variable inputs

const float *SWE;
const float *net_rain;
const float *runoff;
const float *hru_t; // has to be converted to soil temperatures. How?

// variable put inputs

const float *soil_moist;
const float *soil_lower;
float *soil_lower_conc;
float **soil_lower_conc_lay;
const float *soil_rechr;
float *soil_rechr_conc;
float **soil_rechr_conc_lay;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_Hype* klone(string name) const;

// soil_np_processes.f

      void soil_np_processes();

      void soil_pool_transformations(); // requires soil temperature

      void  plant_uptake(float **soil_lay, float **csoil_top_lay, float **csoil_bottom_lay, float **sink_lay);

      void  crop_sources();

      void soil_denitrification(const float maxwc, float **csoil_lay);

      float tempfactor(float temperature);

      float moisturefactor(float sm, float wp, float sum, float thickm, float satact, float thetapow, float thetalow, float thetaupp); // temporary creation

      void add_source_to_water(const float vol, long n, float conc, float source);

      void add_source_to_water(const float vol, const long n, float *conc, const float source);

      void new_concentration(const float pool, const float vol, float *conc); // return by reference

      void retention_pool(float **pool, float *sink, long maxlayers = 2);

      void retention_pool(float *pool, float *sink, long maxlayers = 2);

      void retention_pool(float **pool, long hh, float *sink, long maxlayers = 2);

      void production_pool(float *pool, const float source);

      void production_pool(float pool, const float source);

      void production_pool(float *pool, const float *source, long maxlayers = 2);

      void production_pool(float **pool, long hh, const float *source, long maxlayers = 2);

      void production_pool(float **pool, const float *source, long maxlayers = 2);

      void production_pool(float **pool, const float source[][2], long Application = 0);

      void soil_carbon_processes();

      void soil_carbon_pool_transformations();

      float tempfactor2(const float temperature);

      float exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp);

      float halfsatconcfactor(const float conc, const float par);

      float SUM(float XX[maxsoillayers][2], long Substance);

      float SUM(float *XX);
};

#endif





