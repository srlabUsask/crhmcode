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

const double *hru_area; //
const double *hru_GSL; // ground slope
const double *soil_rechr_max;
const double *soil_moist_max;

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

const double *erodibility; // (g/J)
const double *cohesion; // (kPa)
const double *closewater; // ()
const double *buffer; // ()
const double *soil_Depth;

const double *klh;    // transformation rate of labileC to refractoryC (d-1)
const double *klo;    // degradation labileC (d-1)
const double *kho;    // degradation refractoryC (d-1)
const double *kof;    // transformation to labileC (d-1)
const double *koflim; // threshold for transformation to labileC (-)
const double *minc;   // fraction mineralisation to DIC (-)
const double *soimf;  // satuaration soilmoisture factor (-)
const double *soim;   // rate soilmoisture factor (-)
const double *soimr;  // rate soilmoisture factor (-)

const long *calcN; // Status of nitrogen simulation
const long *calcP; // Status of phosphorus simulation
const long *calcC; // Status of organic carbon simulation
const long *Inhibit_Soil_BGC; // Skip Hype

const double *fertNamount_up;
const double *fertNamount_down;
const double *fertPamount_up;
const double *fertPamount_down;
const double *manNamount_up;
const double *manNamount_down;
const double *manPamount_up;
const double *manPamount_down;
const double *resNamount_up;
const double *resPamount_up;
const double *resNamount_down;
const double *resPamount_down;
const double *resCamount;
const double *resfast;
//const double *resdown;
//const double *fertdown1;
//const double *fertdown2;
//const double *mandown1;
//const double *mandown2;

const double *fertday_up;
const double *fertday_down;
const double *manday_up;
const double *manday_down;
const double *resday_up;
const double *resday_down;

const double *fertperiod;
const long *litterperiod;

const double *manureinogNfrac;
const double *manureinogPfrac;
const double *fertandman_inogNfrac_NO3Nfrac;
const double *fertandman_inogNfrac_NH4Nfrac;


const double *wp; // water content at wilting point(mm)

const double **wp_lay; // [maxsoillayers]
//const double *pw; // water content: total porosity(mm)
//const double **pw_lay; // [maxsoillayers]
//const double *ep; // water content: effectiv porosity(mm)
//const double **ep_lay; // [maxsoillayers]
const double *plant_uptk_NO3N; //
const double **plant_uptk_NO3N_lay; // 
const double *plant_uptk_NH4N; //
const double **plant_uptk_NH4N_lay; // 
const double *plant_uptk_SRP; //
const double **plant_uptk_SRP_lay; //
const double *pardenN; // nitrification
const double *parminfN; //
const double *parnitrfN;
const double *parminfP; //
const double *pardegrhN; //
const double *pardegrhP; //
const double *pardisfN; //
const double *pardisfP; //
const double *pardishN; //
const double *pardishP; // 

const double *refractoryNmass_init;
const double **refractoryNmass_init_lay;
const double *refractoryPmass_init;
const double **refractoryPmass_init_lay;
const double *refractoryCmass_init;
const double **refractoryCmass_init_lay;
const double *labileNmass_init;
const double **labileNmass_init_lay;
const double *labilePmass_init;
const double **labilePmass_init_lay;
const double *labileCmass_init;
const double **labileCmass_init_lay;
const double *conc_soil_rechr_init;
const double **conc_soil_rechr_init_lay;
const double *conc_soil_lower_init;
const double **conc_soil_lower_init_lay;
const double *surfsoil_massSolub_init;
const double **surfsoil_massSolub_init_lay;
const double *surfsoil_masslabileNmass_init;
const double *surfsoil_masslabilePmass_init;
const double *surfsoil_massrefractoryNmass_init;
const double *surfsoil_massrefractoryPmass_init;
// declared variables

double *wp_mm; // water content at wilting point(mm)
double **wp_mm_lay; // [maxsoillayers]
//double *pw_mm; // water content: total porosity(mm)
//double **pw_mm_lay; // [maxsoillayers]
//double *fc_mm; // water content at field capacity(mm)
//double **fc_mm_lay; // [maxsoillayers]
//double *ep_mm; // water content: effectiv porosity(mm)
//double **ep_mm_lay; // [maxsoillayers]

double *refractoryP; // refractoryP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryP_lay; //  (soillayer,class, subbasin)
double *refractoryN; // refractoryN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryN_lay;
double *refractoryC; // refractoryC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryC_lay;
double *labileN;  // labileN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileN_lay;
double *labileP;  // labileP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileP_lay;
double *labileC;  // labileC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileC_lay;
double *NO3_Npool;  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **NO3_Npool_lay;
double *NH4_Npool;  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **NH4_Npool_lay;
double *DONpool;  // DON pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **DONpool_lay;
double *SRPpool;  // SRP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **SRPpool_lay;
double *DOPpool;  // DOP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **DOPpool_lay;

double *PPrelpool; // (Particulate P release from soil due to erosion (kg/km2=mg/m2) (kg/km2/mm=mg/L)
//double **PPrelpool_lay; // ()

//double *conc_soil_rechr;   // concentration of inorganic nitrogen *** from soilstate
//double **conc_soil_rechr_lay;
double *conc_soil_lower;   // concentration of organic nitrogen *** from soilstate
double **conc_soil_lower_lay;
//double *conc_soil_moist;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
//double **conc_soil_moist_lay;

double *surfsoil_solub_mWQ;
double **surfsoil_solub_mWQ_lay;
double *surfsoil_labileN_mWQ;
double *surfsoil_labileP_mWQ;
double *surfsoil_refractoryN_mWQ;
double *surfsoil_refractoryP_mWQ;

double *conc_i_pp;   // concentration of particulate phosphorus *** from soilstate *** from soilstate

double *sources_plant;
double **sources_plant_lay;
double *src_mineral_fertman_surfsoil;
double **src_mineral_fertman_surfsoil_lay; 
double *src_mineral_fertman_soilrechr;
double **src_mineral_fertman_soilrechr_lay;

double *sink;
double **sink_lay;  // sink of nutrients in this subroutine  (kg/km2
double *source;  // load from fertilizer and plant residues (kg/timestep)
double **source_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
double *denitrification;  // load from fertilizer and plant residues (kg/timestep)
double **denitrification_lay;  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
double *denitrification_surfsoil;
double *Temp;  // layer soil temperatures
double **Temp_lay;  //

double *water;  // soil moisture *** from soilstate
double **water_lay;  // layer oil moisture
double *watermax;  // soil moisture max *** from soilstate
double **watermax_lay;  // layer oil moisture max
double *partP;  // partP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L *** from soilstate
double **partP_lay;
double *plant_uptk_NO3N_mWQ;  //
double **plant_uptk_NO3N_mWQ_lay;
double *plant_uptk_NH4N_mWQ;  //
double **plant_uptk_NH4N_mWQ_lay;
double *plant_uptk_SRP_mWQ;  //
double **plant_uptk_SRP_mWQ_lay;

double *fracminP; // part of eroded P in mineral form
double *cropuptake; // of i_no3n

// variable inputs

const double *snowmelt_int;
const double *SWE;
const double *net_rain;
const double *runoff;
const double *soil_runoff;
double *soil_runoff_cWQ;
double **soil_runoff_cWQ_lay; 
const double *hru_t; // has to be converted to soil temperatures. How?

// variable put inputs

double *SWE_conc;
double **SWE_conc_lay;
const double *soil_moist;
const double *soil_lower;
double *soil_lower_conc;
double **soil_lower_conc_lay;
const double *soil_rechr;
double *conc_soil_rechr;
double **conc_soil_rechr_lay;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassWQ_SoilBGC* klone(string name) const;

// soil_np_processes.f

      void soil_np_processes();

      void soil_pool_transformations(); // requires soil temperature

      void  plant_uptake(double **conc_soil_rechr_lay, double **conc_soil_lower_lay, double **sink_lay);

      void  nutrient_inputs();

      void soil_denitrification(const long soil_layer);

      double tempfactor(double temperature);

      double moisturefactor(double sm, double wp, double satact, double thetapow, double thetalow, double thetaupp); // temporary creation

      void add_source_to_water(const double vol, long n, double conc, double source);

      void add_source_to_water(const double vol, const long n, double *conc, const double source);

      void new_concentration(const double pool, const double vol, double *conc); // return by reference


      void retention_pool(long n, long hh, double **pool, double *sink);

      void retention_pool(long n, double *pool, double *sink);

      void retention_pool(double &pool, double &sink);

      void production_pool(long n, double pool, const double source); // used

      void production_pool(long n, long hh, double **pool, const double source[][2]); // used

      void production_pool(long n, long hh, double **pool, const double *source); // used

      void production_pool(long n, double *pool, const double source);

      void soil_carbon_processes();

      void soil_carbon_pool_transformations();

      double exponential_moisturefactor(const double sm, const double pw, const double limpar, const double exp);

      double halfsatconcfactor(const double conc, const double par);

      double SUM(double XX[maxsoillayers][2], long part); // two dimensional arrays

      double SUM(double *XX); // one dimensional arrays
      
      void runoff_pp_by_erosion();

      void calculate_erosion(double& erodedP);

      void calculate_transport(double erodingflow, double& erodedP);   // calculate amount of PP transported in fast flow paths  (kg/km2)

};

#endif





