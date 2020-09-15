//created by Manishankar Mondal

#include "ClassModule.h"

class Classsbsm : public ClassModule {
public:

Classsbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
double dt;

// declared variables
double *SWE;
double *wet_snow;
double *Subl;
double *Drift;
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *cumSno;
double *Prob;
double *snow_age;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *snowdepth;

// declared parameters
const double *basin_area;
const double *hru_area;
const double *Ht;
const double *zr;
const double *distrib;
const double *fetch;
const long *inhibit_evap;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classsbsm* klone(string name) const;

double transport(void);
double sublimation(void);
double scale(void);
void  prob(void);
};