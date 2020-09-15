//created by Manishankar

#include "ClassModule.h"

class Classobs : public ClassModule {
public:

Classobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Exist;
long Exist2;

// declared observation variables
const double *p;      // interval data
const double *ppt;    // daily data
const double *t;
double **tday_intvls;
const double *rh;
double **rhday_intvls;
const double *ea;
double **eaday_intvls;
const double *u;
const double *t_max;
const double *t_min;
const double *obs_snow;
const double *obs_rain;

// declared observation functions
double *tmean;
double *tmin;
double *tmax;
double *umean;
double *pptD;
//double *p;      // interval data
double *NotUsed;

// declared variables
double *hru_t;
double *hru_rh;
double *hru_ea;
double *hru_estar;
double *hru_u;
double *hru_p;
// double *hru_icebulb;
double *Pa;
double *DTnow;
long  *DTindx;
double *hru_rain;
double *cumhru_rain;
double *hru_snow;
double *cumhru_snow;
double *cumhru_snow_meas;
double *hru_tmax;
double *hru_tmin;
double *hru_tmean;
double *hru_eamean;
double *hru_umean;
double *hru_rhmean;

double *t_obs;
double **t_obs_lay;

long  *hru_newsnow;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *tmax_allrain;
const double *tmax_allsnow;
const double *lapse_rate;
const double *precip_elev_adj;
const double *hru_elev;
const double *ClimChng_t;
const double *ClimChng_precip;
const long  *catchadjust;
const long  *ppt_daily_distrib;
const long  *snow_rain_determination;
const long  *HRU_OBS;
const long  **HRU_OBS_Tables;
const double *obs_elev;
const double  **obs_elev_Tables;
const long  *ElevChng_flag;
const long  *ClimChng_flag;

// variable inputs

void decl(void);
void init(void);
void run(void);
void pre_run(void);
void Harder(void);
void finish(bool good);

Classobs* klone(string name) const;
};