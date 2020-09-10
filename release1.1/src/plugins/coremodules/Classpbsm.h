//created by Manishankar Mondal

#include "ClassModule.h"

class Classpbsm : public ClassModule {
public:

Classpbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

float hru_u_;

// declared variables

float *SWE;
float *Subl;
float *Drift;
float *SublH;
float *DriftH;
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *cumSno;
float *Prob;
float *snowdepth;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *SnowAge;
float *SWE_Init;
float *rain_on_snow;
float *cumrain_on_snow;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *u_D;
const float *Drift_offset;
const float *Drift_slope;
const float *Subl_offset;
const float *Subl_slope;
const float *N_S;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;
const float *net_rain;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm* klone(string name) const;
};