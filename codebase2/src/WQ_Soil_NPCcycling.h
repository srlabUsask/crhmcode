// 11/20/19
//---------------------------------------------------------------------------
#ifndef WQ_Soil_NPCcyclingH
#define WQ_Soil_NPCcyclingH
//---------------------------------------------------------------------------

#include "ClassModule.h"

#define numsubstances 7
#define maxsoillayers 2
#define inorg 0 // where 0 - refractoryNpart (Humus)
#define fast 1  // where 1 - fastpart (labile)

using namespace std;

class ClassWQ_SoilBGC : public ClassModule {
public:

long dayno;
long nstep;

ClassWQ_SoilBGC(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameter

const float *hru_area; //
const float *hru_GSL; // ground slope
const float *soil_rechr_max;
const float *soil_moist_max;

const long *ccmax1; // crop cover during summer
//const long *ccmax2; // crop cover during winter and all year for year round
const long *gcmax1; // ground cover during summer
//const long *gcmax2; // ground cover during winter and all year for year round

/*
const long *baredayno1; // spring ploughing
const long *baredayno2; // sow date/beginning of growing season
const long *baredayno3; // harvest
const long *baredayno4; // autumn ploughing
const long *baredayno5; // winter crops sowing date
*/

const float *erodibility; // (g/J)
const float *cohesion; // (kPa)
const float *closewater; // ()
const float *buffer; // ()
const float *soil_Depth;

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
const long *Inhibit_Soil_BGC; // Skip Hype

const float *fertNamount_up;
const float *fertNamount_down;
const float *fertPamount_up;
const float *fertPamount_down;
const float *manNamount_up;
const float *manNamount_down;
const float *manPamount_up;
const float *manPamount_down;
const float *resNamount_up;
const float *resPamount_up;
const float *resNamount_down;
const float *resPamount_down;
const float *resCamount;
const float *resfast;
//const float *resdown;
//const float *fertdown1;
//const float *fertdown2;
//const float *mandown1;
//const float *mandown2;

const float *fertday_up;
const float *fertday_down;
const float *manday_up;
const float *manday_down;
const float *resday_up;
const float *resday_down;

const float *fertperiod;
const long *litterperiod;

const float *manureinogNfrac;
const float *manureinogPfrac;
const float *fertandman_inogNfrac_NO3Nfrac;
const float *fertandman_inogNfrac_NH4Nfrac;


const float *wp; // water content at wilting point(mm)

const float **wp_lay; // [maxsoillayers]
//const float *pw; // water content: total porosity(mm)
//const float **pw_lay; // [maxsoillayers]
//const float *ep; // water content: effectiv porosity(mm)
//const float **ep_lay; // [maxsoillayers]
const float *plant_uptk_NO3N; //
const float **plant_uptk_NO3N_lay; // 
const float *plant_uptk_NH4N; //
const float **plant_uptk_NH4N_lay; // 
const float *plant_uptk_SRP; //
const float **plant_uptk_SRP_lay; //
const float *pardenN; // nitrification
const float *parminfN; //
const float *parnitrfN;
const float *parminfP; //
const float *pardegrhN; //
const float *pardegrhP; //
const float *pardisfN; //
const float *pardisfP; //
const float *pardishN; //
const float *pardishP; // 

const float *refractoryNmass_init;
const float **refractoryNmass_init_lay;
const float *refractoryPmass_init;
const float **refractoryPmass_init_lay;
const float *refractoryCmass_init;
const float **refractoryCmass_init_lay;
const float *labileNmass_init;
const float **labileNmass_init_lay;
const float *labilePmass_init;
const float **labilePmass_init_lay;
const float *labileCmass_init;
const float **labileCmass_init_lay;
const float *conc_soil_rechr_init;
const float **conc_soil_rechr_init_lay;
const float *conc_soil_lower_init;
const float **conc_soil_lower_init_lay;
const float *surfsoil_massSolub_init;
const float **surfsoil_massSolub_init_lay;
const float *surfsoil_masslabileNmass_init;
const float *surfsoil_masslabilePmass_init;
const float *surfsoil_massrefractoryNmass_init;
const float *surfsoil_massrefractoryPmass_init;
// declared variables

float *wp_mm; // water content at wilting point(mm)
float **wp_mm_lay; // [maxsoillayers]
//float *pw_mm; // water content: total porosity(mm)
//float **pw_mm_lay; // [maxsoillayers]
//float *fc_mm; // water content at field capacity(mm)
//float **fc_mm_lay; // [maxsoillayers]
//float *ep_mm; // water content: effectiv porosity(mm)
//float **ep_mm_lay; // [maxsoillayers]

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
float *NO3_Npool;  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **NO3_Npool_lay;
float *NH4_Npool;  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **NH4_Npool_lay;
float *DONpool;  // DON pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **DONpool_lay;
float *SRPpool;  // SRP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **SRPpool_lay;
float *DOPpool;  // DOP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
float **DOPpool_lay;

float *PPrelpool; // (Particulate P release from soil due to erosion (kg/km2=mg/m2) (kg/km2/mm=mg/L)
//float **PPrelpool_lay; // ()

//float *conc_soil_rechr;   // concentration of inorganic nitrogen *** from soilstate
//float **conc_soil_rechr_lay;
float *conc_soil_lower;   // concentration of organic nitrogen *** from soilstate
float **conc_soil_lower_lay;
//float *conc_soil_moist;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
//float **conc_soil_moist_lay;

float *surfsoil_solub_mWQ;
float **surfsoil_solub_mWQ_lay;
float *surfsoil_labileN_mWQ;
float *surfsoil_labileP_mWQ;
float *surfsoil_refractoryN_mWQ;
float *surfsoil_refractoryP_mWQ;

float *conc_i_pp;   // concentration of particulate phosphorus *** from soilstate *** from soilstate

float *sources_plant;
float **sources_plant_lay;
float *src_mineral_fertman_surfsoil;
float **src_mineral_fertman_surfsoil_lay; 
float *src_mineral_fertman_soilrechr;
float **src_mineral_fertman_soilrechr_lay;

float *sink;
float **sink_lay;  // sink of nutrients in this subroutine  (kg/km2
float *source;  // load from fertilizer and plant residues (kg/timestep)
float **source_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
float *denitrification;  // load from fertilizer and plant residues (kg/timestep)
float **denitrification_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
float *denitrification_surfsoil;
float *Temp;  // layer soil temperatures
float **Temp_lay;  //

float *water;  // soil moisture *** from soilstate
float **water_lay;  // layer oil moisture
float *watermax;  // soil moisture max *** from soilstate
float **watermax_lay;  // layer oil moisture max
float *partP;  // partP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L *** from soilstate
float **partP_lay;
float *plant_uptk_NO3N_mWQ;  //
float **plant_uptk_NO3N_mWQ_lay;
float *plant_uptk_NH4N_mWQ;  //
float **plant_uptk_NH4N_mWQ_lay;
float *plant_uptk_SRP_mWQ;  //
float **plant_uptk_SRP_mWQ_lay;

float *fracminP; // part of eroded P in mineral form
float *cropuptake; // of i_no3n

// variable inputs

const float *snowmelt_int;
const float *SWE;
const float *net_rain;
const float *runoff;
const float *soil_runoff;
float *soil_runoff_cWQ;
float **soil_runoff_cWQ_lay; 
const float *hru_t; // has to be converted to soil temperatures. How?

// variable put inputs

float *SWE_conc;
float **SWE_conc_lay;
const float *soil_moist;
const float *soil_lower;
float *soil_lower_conc;
float **soil_lower_conc_lay;
const float *soil_rechr;
float *conc_soil_rechr;
float **conc_soil_rechr_lay;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_SoilBGC* klone(string name) const;

// soil_np_processes.f

      void soil_np_processes();

      void soil_pool_transformations(); // requires soil temperature

      void  plant_uptake(float **conc_soil_rechr_lay, float **conc_soil_lower_lay, float **sink_lay);

      void  nutrient_inputs();

      void soil_denitrification(const long soil_layer);

      float tempfactor(float temperature);

      float moisturefactor(float sm, float wp, float satact, float thetapow, float thetalow, float thetaupp); // temporary creation

      void add_source_to_water(const float vol, long n, float conc, float source);

      void add_source_to_water(const float vol, const long n, float *conc, const float source);

      void new_concentration(const float pool, const float vol, float *conc); // return by reference


      void retention_pool(long n, long hh, float **pool, float *sink);

      void retention_pool(long n, float *pool, float *sink);

      void retention_pool(float &pool, float &sink);

      void production_pool(long n, float pool, const float source); // used

      void production_pool(long n, long hh, float **pool, const float source[][2]); // used

      void production_pool(long n, long hh, float **pool, const float *source); // used

      void production_pool(long n, float *pool, const float source);

      void soil_carbon_processes();

      void soil_carbon_pool_transformations();

      float exponential_moisturefactor(const float sm, const float pw, const float limpar, const float exp);

      float halfsatconcfactor(const float conc, const float par);

      float SUM(float XX[maxsoillayers][2], long part); // two dimensional arrays

      float SUM(float *XX); // one dimensional arrays
      
      void runoff_pp_by_erosion();

      void calculate_erosion(float& erodedP);

      void calculate_transport(float erodingflow, float& erodedP);   // calculate amount of PP transported in fast flow paths  (kg/km2)

};

#endif





