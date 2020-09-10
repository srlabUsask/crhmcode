//created by Manishankar Mondal

#include "ClassModule.h"

class Classsbsm : public ClassModule {
public:

Classsbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
float dt;

// declared variables
float *SWE;
float *wet_snow;
float *Subl;
float *Drift;
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *cumSno;
float *Prob;
float *snow_age;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *snowdepth;

// declared parameters
const float *basin_area;
const float *hru_area;
const float *Ht;
const float *zr;
const float *distrib;
const float *fetch;
const long *inhibit_evap;
const long *inhibit_subl;

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

Classsbsm* klone(string name) const;

float transport(void);
float sublimation(void);
float scale(void);
void  prob(void);
};