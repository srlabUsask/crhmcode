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

long dayno{0};
long nstep{0};

ClassWQ_SoilBGC(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameter

const double *hru_area{ NULL }; //
const double *hru_GSL{ NULL }; // ground slope
const double *soil_rechr_max{ NULL };
const double *soil_moist_max{ NULL };

const long *ccmax1{ NULL }; // crop cover during summer
//const long *ccmax2; // crop cover during winter and all year for year round
const long *gcmax1{ NULL }; // ground cover during summer
//const long *gcmax2; // ground cover during winter and all year for year round

/*
const long *baredayno1; // spring ploughing
const long *baredayno2; // sow date/beginning of growing season
const long *baredayno3; // harvest
const long *baredayno4; // autumn ploughing
const long *baredayno5; // winter crops sowing date
*/

const double *erodibility{ NULL }; // (g/J)
const double *cohesion{ NULL }; // (kPa)
const double *closewater{ NULL }; // ()
const double *buffer{ NULL }; // ()
const double *soil_Depth{ NULL };

const double *klh{ NULL };    // transformation rate of labileC to refractoryC (d-1)
const double *klo{ NULL };    // degradation labileC (d-1)
const double *kho{ NULL };    // degradation refractoryC (d-1)
const double *kof{ NULL };    // transformation to labileC (d-1)
const double *koflim{ NULL }; // threshold for transformation to labileC (-)
const double *minc{ NULL };   // fraction mineralisation to DIC (-)
const double *soimf{ NULL };  // satuaration soilmoisture factor (-)
const double *soim{ NULL };   // rate soilmoisture factor (-)
const double *soimr{ NULL };  // rate soilmoisture factor (-)

const long *calcN{ NULL }; // Status of nitrogen simulation
const long *calcP{ NULL }; // Status of phosphorus simulation
const long *calcC{ NULL }; // Status of organic carbon simulation
const long *Inhibit_Soil_BGC{ NULL }; // Skip Hype

const double *fertNamount_up{ NULL };
const double *fertNamount_down{ NULL };
const double *fertPamount_up{ NULL };
const double *fertPamount_down{ NULL };
const double *manNamount_up{ NULL };
const double *manNamount_down{ NULL };
const double *manPamount_up{ NULL };
const double *manPamount_down{ NULL };
const double *resNamount_up{ NULL };
const double *resPamount_up{ NULL };
const double *resNamount_down{ NULL };
const double *resPamount_down{ NULL };
const double *resCamount{ NULL };
const double *resfast{ NULL };
//const double *resdown;
//const double *fertdown1;
//const double *fertdown2;
//const double *mandown1;
//const double *mandown2;

const double *fertday_up{ NULL };
const double *fertday_down{ NULL };
const double *manday_up{ NULL };
const double *manday_down{ NULL };
const double *resday_up{ NULL };
const double *resday_down{ NULL };

const double *fertperiod{ NULL };
const long *litterperiod{ NULL };

const double *manureinogNfrac{ NULL };
const double *manureinogPfrac{ NULL };
const double *fertandman_inogNfrac_NO3Nfrac{ NULL };
const double *fertandman_inogNfrac_NH4Nfrac{ NULL };


const double *wp{ NULL }; // water content at wilting point(mm)

const double **wp_lay{ NULL }; // [maxsoillayers]
//const double *pw; // water content: total porosity(mm)
//const double **pw_lay; // [maxsoillayers]
//const double *ep; // water content: effectiv porosity(mm)
//const double **ep_lay; // [maxsoillayers]
const double *plant_uptk_NO3N{ NULL }; //
const double **plant_uptk_NO3N_lay{ NULL }; // 
const double *plant_uptk_NH4N{ NULL }; //
const double **plant_uptk_NH4N_lay{ NULL }; // 
const double *plant_uptk_SRP{ NULL }; //
const double **plant_uptk_SRP_lay{ NULL }; //
const double *pardenN{ NULL }; // nitrification
const double *parminfN{ NULL }; //
const double *parnitrfN{ NULL };
const double *parminfP{ NULL }; //
const double *pardegrhN{ NULL }; //
const double *pardegrhP{ NULL }; //
const double *pardisfN{ NULL }; //
const double *pardisfP{ NULL }; //
const double *pardishN{ NULL }; //
const double *pardishP{ NULL }; // 

const double *refractoryNmass_init{ NULL };
const double **refractoryNmass_init_lay{ NULL };
const double *refractoryPmass_init{ NULL };
const double **refractoryPmass_init_lay{ NULL };
const double *refractoryCmass_init{ NULL };
const double **refractoryCmass_init_lay{ NULL };
const double *labileNmass_init{ NULL };
const double **labileNmass_init_lay{ NULL };
const double *labilePmass_init{ NULL };
const double **labilePmass_init_lay{ NULL };
const double *labileCmass_init{ NULL };
const double **labileCmass_init_lay{ NULL };
const double *conc_soil_rechr_init{ NULL };
const double **conc_soil_rechr_init_lay{ NULL };
const double *conc_soil_lower_init{ NULL };
const double **conc_soil_lower_init_lay{ NULL };
const double *surfsoil_massSolub_init{ NULL };
const double **surfsoil_massSolub_init_lay{ NULL };
const double *surfsoil_masslabileNmass_init{ NULL };
const double *surfsoil_masslabilePmass_init{ NULL };
const double *surfsoil_massrefractoryNmass_init{ NULL };
const double *surfsoil_massrefractoryPmass_init{ NULL };
// declared variables

double *wp_mm{ NULL }; // water content at wilting point(mm)
double **wp_mm_lay{ NULL }; // [maxsoillayers]
//double *pw_mm; // water content: total porosity(mm)
//double **pw_mm_lay; // [maxsoillayers]
//double *fc_mm; // water content at field capacity(mm)
//double **fc_mm_lay; // [maxsoillayers]
//double *ep_mm; // water content: effectiv porosity(mm)
//double **ep_mm_lay; // [maxsoillayers]

double *refractoryP{ NULL }; // refractoryP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryP_lay{ NULL }; //  (soillayer,class, subbasin)
double *refractoryN{ NULL }; // refractoryN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryN_lay{ NULL };
double *refractoryC{ NULL }; // refractoryC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **refractoryC_lay{ NULL };
double *labileN{ NULL };  // labileN pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileN_lay{ NULL };
double *labileP{ NULL };  // labileP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileP_lay{ NULL };
double *labileC{ NULL };  // labileC pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **labileC_lay{ NULL };
double *NO3_Npool{ NULL };  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **NO3_Npool_lay{ NULL };
double *NH4_Npool{ NULL };  // NO3-N pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **NH4_Npool_lay{ NULL };
double *DONpool{ NULL };  // DON pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **DONpool_lay{ NULL };
double *SRPpool{ NULL };  // SRP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **SRPpool_lay{ NULL };
double *DOPpool{ NULL };  // DOP pool pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L) *** from soilstate
double **DOPpool_lay{ NULL };

double *PPrelpool{ NULL }; // (Particulate P release from soil due to erosion (kg/km2=mg/m2) (kg/km2/mm=mg/L)
//double **PPrelpool_lay; // ()

//double *conc_soil_rechr;   // concentration of inorganic nitrogen *** from soilstate
//double **conc_soil_rechr_lay;
double *conc_soil_lower{ NULL };   // concentration of organic nitrogen *** from soilstate
double **conc_soil_lower_lay{ NULL };
//double *conc_soil_moist;   // concentration of soluble (reactive) phosphorus, i.e. phosphate *** from soilstate
//double **conc_soil_moist_lay;

double *surfsoil_solub_mWQ{ NULL };
double **surfsoil_solub_mWQ_lay{ NULL };
double *surfsoil_labileN_mWQ{ NULL };
double *surfsoil_labileP_mWQ{ NULL };
double *surfsoil_refractoryN_mWQ{ NULL };
double *surfsoil_refractoryP_mWQ{ NULL };

double *conc_i_pp{ NULL };   // concentration of particulate phosphorus *** from soilstate *** from soilstate

double *sources_plant{ NULL };
double **sources_plant_lay{ NULL };
double *src_mineral_fertman_surfsoil{ NULL };
double **src_mineral_fertman_surfsoil_lay{ NULL };
double *src_mineral_fertman_soilrechr{ NULL };
double **src_mineral_fertman_soilrechr_lay{ NULL };

double *sink{ NULL };
double **sink_lay{ NULL };  // sink of nutrients in this subroutine  (kg/km2
double *source{ NULL };  // load from fertilizer and plant residues (kg/timestep)
double **source_lay{ NULL };  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
double *denitrification{ NULL };  // load from fertilizer and plant residues (kg/timestep)
double **denitrification_lay{ NULL };  // sources(2,numsubstances) load from fertilizer and plant residues (kg/timestep)
double *denitrification_surfsoil{ NULL };
double *Temp{ NULL };  // layer soil temperatures
double **Temp_lay{ NULL };  //

double *water{ NULL };  // soil moisture *** from soilstate
double **water_lay{ NULL };  // layer oil moisture
double *watermax{ NULL };  // soil moisture max *** from soilstate
double **watermax_lay{ NULL };  // layer oil moisture max
double *partP{ NULL };  // partP pool in soil (kg/km2=mg/m2) (kg/km2/mm=mg/L *** from soilstate
double **partP_lay{ NULL };
double *plant_uptk_NO3N_mWQ{ NULL };  //
double **plant_uptk_NO3N_mWQ_lay{ NULL };
double *plant_uptk_NH4N_mWQ{ NULL };  //
double **plant_uptk_NH4N_mWQ_lay{ NULL };
double *plant_uptk_SRP_mWQ{ NULL };  //
double **plant_uptk_SRP_mWQ_lay{ NULL };

double *fracminP{ NULL }; // part of eroded P in mineral form
double *cropuptake{ NULL }; // of i_no3n

// variable inputs

const double *snowmelt_int{ NULL };
const double *SWE{ NULL };
const double *net_rain{ NULL };
const double *runoff{ NULL };
const double *soil_runoff{ NULL };
double *soil_runoff_cWQ{ NULL };
double **soil_runoff_cWQ_lay{ NULL };
const double *hru_t{ NULL }; // has to be converted to soil temperatures. How?

// variable put inputs

double *SWE_conc{ NULL };
double **SWE_conc_lay{ NULL };
const double *soil_moist{ NULL };
const double *soil_lower{ NULL };
double *soil_lower_conc{ NULL };
double **soil_lower_conc_lay{ NULL };
const double *soil_rechr{ NULL };
double *conc_soil_rechr{ NULL };
double **conc_soil_rechr_lay{ NULL };

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





