//created by Manishankar

#include "ClassModule.h"

class Classobs : public ClassModule {
public:

Classobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Exist;
long Exist2;

// declared observation variables
const float *p;      // interval data
const float *ppt;    // daily data
const float *t;
float **tday_intvls;
const float *rh;
float **rhday_intvls;
const float *ea;
float **eaday_intvls;
const float *u;
const float *t_max;
const float *t_min;
const float *obs_snow;
const float *obs_rain;

// declared observation functions
float *tmean;
float *tmin;
float *tmax;
float *umean;
float *pptD;
//float *p;      // interval data
float *NotUsed;

// declared variables
float *hru_t;
float *hru_rh;
float *hru_ea;
float *hru_estar;
float *hru_u;
float *hru_p;
// float *hru_icebulb;
float *Pa;
float *DTnow;
long  *DTindx;
float *hru_rain;
float *cumhru_rain;
float *hru_snow;
float *cumhru_snow;
float *cumhru_snow_meas;
float *hru_tmax;
float *hru_tmin;
float *hru_tmean;
float *hru_eamean;
float *hru_umean;
float *hru_rhmean;

float *t_obs;
float **t_obs_lay;

long  *hru_newsnow;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tmax_allrain;
const float *tmax_allsnow;
const float *lapse_rate;
const float *precip_elev_adj;
const float *hru_elev;
const float *ClimChng_t;
const float *ClimChng_precip;
const long  *catchadjust;
const long  *ppt_daily_distrib;
const long  *snow_rain_determination;
const long  *HRU_OBS;
const long  **HRU_OBS_Tables;
const float *obs_elev;
const float  **obs_elev_Tables;
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