//created by Manishankar Mondal

#include "ClassModule.h"

class ClasspbsmSnobal : public ClassModule {
public:

ClasspbsmSnobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
float hru_u_;

// declared variables
float *Subl;
float *Drift;     // HRU composite drift
float *SublH;
float *DriftH;
float *Drift_out; // HRU drift out
float *Drift_in;  // HRU drift in
float *cumSubl;
float *cumDrift;
float *cumDriftIn;
float *Prob;
float *snowdepth;
float *BasinSnowLoss;
float *cumBasinSnowLoss;
float *cumBasinSnowGain;
float *SnowAge;
long  *DrySnow;

// declared parameters
const float *fetch;
const float *Ht;
const float *distrib;
const float *basin_area;
const float *hru_area;
const float *A_S;
const float *N_S;
const float *u_D;
const float *Drift_offset;
const float *Drift_slope;
const float *Subl_offset;
const float *Subl_slope;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const float *hru_t;
const float *hru_ea;
const float *hru_u;
const float *hru_Uadjust;
const float *net_snow;

// put variable inputs
float *SWE; // actually m_s
float *z_s;
float *rho;

// local allocated arrays
float *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClasspbsmSnobal* klone(string name) const;

};