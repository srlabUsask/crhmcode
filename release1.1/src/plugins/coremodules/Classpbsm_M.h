//created by Manishankar Mondal

#include "ClassModule.h"

class Classpbsm_M : public ClassModule {
public:

Classpbsm_M(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
// declared variables
double *SWE{ NULL };
double *Subl{ NULL };
double *Drift{ NULL };
double *cumSubl{ NULL };
double *cumDrift{ NULL };
double *cumDriftIn{ NULL };
double *cumSno{ NULL };
double *Prob{ NULL };
double *snowdepth{ NULL };
double *BasinSnowLoss{ NULL };
double *cumBasinSnowLoss{ NULL };
double *cumBasinSnowGain{ NULL };
double *SnowAge{ NULL };
double *this_distrib{ NULL };
double *Results{ NULL };
double **Results_lay{ NULL };
double *Q_leeslope{ NULL };
double *Q_valley{ NULL };
long  *DrySnow{ NULL };

// declared parameters
const double *fetch{ NULL };
const double *Ht{ NULL };
const double *hru_Ht{ NULL };
const double *distrib{ NULL };
const double **distrib_hru{ NULL };
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const double *A_S{ NULL };
const double *N_S{ NULL };
const double *Zwind{ NULL };
const double *hru_GSL{ NULL };
const double *Beta_M{ NULL };
const long *inhibit_evap{ NULL };
const long *inhibit_bs{ NULL };
const long *inhibit_subl{ NULL };
const long *eq_prof{ NULL };

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

Classpbsm_M* klone(string name) const;
void Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH);
void Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch,
            long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley);
};