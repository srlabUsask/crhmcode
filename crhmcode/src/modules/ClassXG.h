//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassXG : public ClassModule {
public:

long front_size{0};

ClassXG(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, "hru_tsf, , ") {};

// constants

double ko{0.0};
double km{0.0};
double ka{0.0};
double ki{0.0};
double kw{0.0};

// declared variables
double *Zdf{ NULL };
double *Zdt{ NULL };
long *Th_low_lay{ NULL };
long *Fz_low_lay{ NULL };
double *Bfr{ NULL };
double *Bth{ NULL };
double *TrigAcc{ NULL };
double *B{ NULL };
long *TrigState{ NULL };
double *pf{ NULL };
double **pf_lay{ NULL };
double *pt{ NULL };
double **pt_lay{ NULL };
double *ttc{ NULL };
double **ttc_lay{ NULL };
double *ftc{ NULL };
double **ftc_lay{ NULL };
double *SWE_tc{ NULL };
double *SWE_density{ NULL };
double *XG_moist_d{ NULL };
double *XG_rechr_d{ NULL };
double *XG_moist{ NULL };
double *check_XG_moist{ NULL };
double **XG_moist_lay{ NULL };
double *XG_max{ NULL };
double **XG_max_lay{ NULL };
double *layer_h2o{ NULL };
double **h2o_lay{ NULL };
double *theta{ NULL };
double **theta_lay{ NULL };
double *rechr_fract{ NULL };
double **rechr_fract_lay{ NULL };
double *moist_fract{ NULL };
double **moist_fract_lay{ NULL };
double *default_fract{ NULL };
double **default_fract_lay{ NULL };
double *tc_composite{ NULL };
double **tc_composite_lay{ NULL };
double *tc_composite2{ NULL };
double **tc_composite2_lay{ NULL };

double *Zd_front{ NULL };
double **Zd_front_array{ NULL };
double *n_factor{ NULL };
double *n_factor_T{ NULL };
double *check_t{ NULL };
double *t_trend{ NULL };
long *ttc_contents{ NULL };
long **ttc_contents_lay{ NULL };
long *ftc_contents{ NULL };
long **ftc_contents_lay{ NULL };
long  *nfront{ NULL };

// declared parameters
const double *SWE_k{ NULL };
const double *soil_solid_km{ NULL };
const double **soil_solid_km_lay{ NULL };
const double *soil_solid_km_ki{ NULL };
const double **soil_solid_km_ki_lay{ NULL };
const double *soil_solid_km_kw{ NULL };
const double **soil_solid_km_kw_lay{ NULL };
const double *depths{ NULL };
const double **depths_lay{ NULL };
const double *por{ NULL };
const double **por_lay{ NULL };
const double *theta_default{ NULL };
const double **theta_default_lay{ NULL };
const double *Zdf_init{ NULL };
const double *Zdt_init{ NULL };
const double *Zpf_init{ NULL };
const double *n_factor_a{ NULL };
const double *n_factor_b{ NULL };
const double *n_factor_c{ NULL };
const double *Trigthrhld{ NULL };
const long *N_Soil_layers{ NULL };
const long *calc_coductivity{ NULL };
const long *freeze_kw_ki_update{ NULL };
const long *thaw_ki_kw_update{ NULL };
const long *k_update{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_rechr_max{ NULL };
const double *theta_min{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_tsf{ NULL };
const double *SWE{ NULL };
const double *soil_moist{ NULL };
const double *soil_rechr{ NULL };

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