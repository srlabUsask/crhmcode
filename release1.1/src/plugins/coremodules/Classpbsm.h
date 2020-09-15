//created by Manishankar Mondal

#include "ClassModule.h"

class Classpbsm : public ClassModule {
public:

Classpbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

double hru_u_;

// declared variables

double *SWE;
double *Subl;
double *Drift;
double *SublH;
double *DriftH;
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *cumSno;
double *Prob;
double *snowdepth;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *SnowAge;
double *SWE_Init;
double *rain_on_snow;
double *cumrain_on_snow;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const double *N_S;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;
const double *net_rain;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm* klone(string name) const;
};