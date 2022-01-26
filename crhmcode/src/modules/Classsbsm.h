//created by Manishankar Mondal

#include "../core/ClassModule.h"

class Classsbsm : public ClassModule {
public:

Classsbsm(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
double dt{0.0};

// declared variables
double *SWE{ NULL };
double *wet_snow{ NULL };
double *Subl{ NULL };
double *Drift{ NULL };
double *cumSubl{ NULL };
double *cumDrift{ NULL };
double *cumDriftIn{ NULL };
double *cumSno{ NULL };
double *Prob{ NULL };
double *snow_age{ NULL };
double *BasinSnowLoss{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowGain{ NULL };
double *snowdepth{ NULL };

// declared parameters
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *Ht{ NULL };
const double *zr{ NULL };
const double *distrib{ NULL };
const double *fetch{ NULL };
const long *inhibit_evap{ NULL };
const long *inhibit_subl{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_rh{ NULL };
const double *hru_u{ NULL };
const double *net_snow{ NULL };
const long  *hru_newsnow{ NULL };

// local allocated arrays
double *hru_basin{ NULL };


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
