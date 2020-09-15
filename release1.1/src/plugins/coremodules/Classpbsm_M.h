//created by Manishankar Mondal

#include "ClassModule.h"

class Classpbsm_M : public ClassModule {
public:

Classpbsm_M(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
// declared variables
double *SWE;
double *Subl;
double *Drift;
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
double *this_distrib;
double *Results;
double **Results_lay;
double *Q_leeslope;
double *Q_valley;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *hru_Ht;
const double *distrib;
const double **distrib_hru;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *N_S;
const double *Zwind;
const double *hru_GSL;
const double *Beta_M;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;
const long *eq_prof;

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

Classpbsm_M* klone(string name) const;
void Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH);
void Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch,
            long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley);
};