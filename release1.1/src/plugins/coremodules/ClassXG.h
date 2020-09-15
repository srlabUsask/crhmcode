//created by Manishankar Mondal

#include "ClassModule.h"

class ClassXG : public ClassModule {
public:

long front_size;

ClassXG(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "hru_tsf, , ") {};

// constants

double ko;
double km;
double ka;
double ki;
double kw;

// declared variables
double *Zdf;
double *Zdt;
long *Th_low_lay;
long *Fz_low_lay;
double *Bfr;
double *Bth;
double *TrigAcc;
double *B;
long *TrigState;
double *pf;
double **pf_lay;
double *pt;
double **pt_lay;
double *ttc;
double **ttc_lay;
double *ftc;
double **ftc_lay;
double *SWE_tc;
double *SWE_density;
double *XG_moist_d;
double *XG_rechr_d;
double *XG_moist;
double *check_XG_moist;
double **XG_moist_lay;
double *XG_max;
double **XG_max_lay;
double *layer_h2o;
double **h2o_lay;
double *theta;
double **theta_lay;
double *rechr_fract;
double **rechr_fract_lay;
double *moist_fract;
double **moist_fract_lay;
double *default_fract;
double **default_fract_lay;
double *tc_composite;
double **tc_composite_lay;
double *tc_composite2;
double **tc_composite2_lay;

double *Zd_front;
double **Zd_front_array;
double *n_factor;
double *n_factor_T;
double *check_t;
double *t_trend;
long *ttc_contents;
long **ttc_contents_lay;
long *ftc_contents;
long **ftc_contents_lay;
long  *nfront;

// declared parameters
const double *SWE_k;
const double *soil_solid_km;
const double **soil_solid_km_lay;
const double *soil_solid_km_ki;
const double **soil_solid_km_ki_lay;
const double *soil_solid_km_kw;
const double **soil_solid_km_kw_lay;
const double *depths;
const double **depths_lay;
const double *por;
const double **por_lay;
const double *theta_default;
const double **theta_default_lay;
const double *Zdf_init;
const double *Zdt_init;
const double *Zpf_init;
const double *n_factor_a;
const double *n_factor_b;
const double *n_factor_c;
const double *Trigthrhld;
const long *N_Soil_layers;
const long *calc_coductivity;
const long *freeze_kw_ki_update;
const long *thaw_ki_kw_update;
const long *k_update;
const double *soil_moist_max;
const double *soil_rechr_max;
const double *theta_min;

// variable inputs
const double *hru_t;
const double *hru_tsf;
const double *SWE;
const double *soil_moist;
const double *soil_rechr;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void freeze(void);
void thaw(void);
void find_freeze_D(double df);
void find_thaw_D(double dt);
void push_front(double D);
double pop_front(void);
double last_front(void);
double Interpolated_ftc_lay(double Za, long lay);
double Interpolated_ttc_lay(double Za, long lay);
double SWE_to_rho(double SWE);
double get_ftc_lay(long lay);
double get_ttc_lay(long lay);

ClassXG* klone(string name) const;
};