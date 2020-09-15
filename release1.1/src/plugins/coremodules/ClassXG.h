//created by Manishankar Mondal

#include "ClassModule.h"

class ClassXG : public ClassModule {
public:

long front_size;

ClassXG(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "hru_tsf, , ") {};

// constants

float ko;
float km;
float ka;
float ki;
float kw;

// declared variables
float *Zdf;
float *Zdt;
long *Th_low_lay;
long *Fz_low_lay;
float *Bfr;
float *Bth;
float *TrigAcc;
float *B;
long *TrigState;
float *pf;
float **pf_lay;
float *pt;
float **pt_lay;
float *ttc;
float **ttc_lay;
float *ftc;
float **ftc_lay;
float *SWE_tc;
float *SWE_density;
float *XG_moist_d;
float *XG_rechr_d;
float *XG_moist;
float *check_XG_moist;
float **XG_moist_lay;
float *XG_max;
float **XG_max_lay;
float *layer_h2o;
float **h2o_lay;
float *theta;
float **theta_lay;
float *rechr_fract;
float **rechr_fract_lay;
float *moist_fract;
float **moist_fract_lay;
float *default_fract;
float **default_fract_lay;
float *tc_composite;
float **tc_composite_lay;
float *tc_composite2;
float **tc_composite2_lay;

float *Zd_front;
float **Zd_front_array;
float *n_factor;
float *n_factor_T;
float *check_t;
float *t_trend;
long *ttc_contents;
long **ttc_contents_lay;
long *ftc_contents;
long **ftc_contents_lay;
long  *nfront;

// declared parameters
const float *SWE_k;
const float *soil_solid_km;
const float **soil_solid_km_lay;
const float *soil_solid_km_ki;
const float **soil_solid_km_ki_lay;
const float *soil_solid_km_kw;
const float **soil_solid_km_kw_lay;
const float *depths;
const float **depths_lay;
const float *por;
const float **por_lay;
const float *theta_default;
const float **theta_default_lay;
const float *Zdf_init;
const float *Zdt_init;
const float *Zpf_init;
const float *n_factor_a;
const float *n_factor_b;
const float *n_factor_c;
const float *Trigthrhld;
const long *N_Soil_layers;
const long *calc_coductivity;
const long *freeze_kw_ki_update;
const long *thaw_ki_kw_update;
const long *k_update;
const float *soil_moist_max;
const float *soil_rechr_max;
const float *theta_min;

// variable inputs
const float *hru_t;
const float *hru_tsf;
const float *SWE;
const float *soil_moist;
const float *soil_rechr;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void freeze(void);
void thaw(void);
void find_freeze_D(float df);
void find_thaw_D(float dt);
void push_front(float D);
float pop_front(void);
float last_front(void);
float Interpolated_ftc_lay(float Za, long lay);
float Interpolated_ttc_lay(float Za, long lay);
float SWE_to_rho(float SWE);
float get_ftc_lay(long lay);
float get_ttc_lay(long lay);

ClassXG* klone(string name) const;
};