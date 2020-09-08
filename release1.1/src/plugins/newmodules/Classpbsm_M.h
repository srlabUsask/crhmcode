//created by Manishankar Mondal

#include "ClassModule.h"

class Classpbsm_M : public ClassModule {
public:

Classpbsm_M(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
// declared variables
float *SWE;
float *Subl;
float *Drift;
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
float *this_distrib;
float *Results;
float **Results_lay;
float *Q_leeslope;
float *Q_valley;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *hru_Ht;
const float *distrib;
const float **distrib_hru;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *N_S;
const float *Zwind;
const float *hru_GSL;
const float *Beta_M;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;
const long *eq_prof;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_u;
const float *net_snow;
const long  *hru_newsnow;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm_M* klone(string name) const;
void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH);
void Pbsm(float E_StubHt, float Uthr, float & DriftH, float & SublH, float t, float u, float rh, float Fetch,
            long N_S, float A_S, float GSL, float height, float Beta_M, float & Qdist_leeslope, float & Qdist_valley);
};