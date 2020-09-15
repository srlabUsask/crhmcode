//created by Manishankar Mondal

#include "ClassModule.h"

class ClasspbsmSnobal : public ClassModule {
public:

ClasspbsmSnobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
double hru_u_;

// declared variables
double *Subl;
double *Drift;     // HRU composite drift
double *SublH;
double *DriftH;
double *Drift_out; // HRU drift out
double *Drift_in;  // HRU drift in
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *Prob;
double *snowdepth;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *SnowAge;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *N_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_ea;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;

// put variable inputs
double *SWE; // actually m_s
double *z_s;
double *rho;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClasspbsmSnobal* klone(string name) const;

};