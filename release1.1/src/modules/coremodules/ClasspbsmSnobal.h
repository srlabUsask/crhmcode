//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClasspbsmSnobal : public ClassModule {
public:

ClasspbsmSnobal(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
double hru_u_{0.0};

// declared variables
double *Subl{ NULL };
double *Drift{ NULL };     // HRU composite drift
double *SublH{ NULL };
double *DriftH{ NULL };
double *Drift_out{ NULL }; // HRU drift out
double *Drift_in{ NULL };  // HRU drift in
double *cumSubl{ NULL };
double *cumDrift{ NULL };
double *cumDriftIn{ NULL };
double *Prob{ NULL };
double *snowdepth{ NULL };
double *BasinSnowLoss{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowGain{ NULL };
double *SnowAge{ NULL };
long  *DrySnow{ NULL };

// declared parameters
const double *fetch{ NULL };
const double *Ht{ NULL };
const double *distrib{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *A_S{ NULL };
const long *N_S{ NULL };
const double *u_D{ NULL };
const double *Drift_offset{ NULL };
const double *Drift_slope{ NULL };
const double *Subl_offset{ NULL };
const double *Subl_slope{ NULL };
const long *inhibit_evap{ NULL };
const double* SWEmin_inhibit_evap{ NULL }; // modification on 24Feb2021
const long *inhibit_bs{ NULL };
const long *inhibit_subl{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_ea{ NULL };
const double *hru_u{ NULL };
const double *hru_Uadjust{ NULL };
const double *net_snow{ NULL };

// put variable inputs
double *SWE{ NULL }; // actually m_s
double *z_s{ NULL };
double *rho{ NULL };

// local allocated arrays
double *hru_basin{ NULL };


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClasspbsmSnobal* klone(string name) const;

};