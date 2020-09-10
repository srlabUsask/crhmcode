//created by Manishankar Mondal

#include "ClassModule.h"

class Classlake : public ClassModule {
public:

Classlake(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  int DaysMonth;
  long ThisMonth;
  bool DoMean;
  bool Ahead;
  long  N_intervals;
  long itime[6];

// declared variables
  float *hru_evap;
  float *hru_cum_evap;
  float *hru_actet;
  float *hru_cum_actet;
  float *lake_evap_month;
  float *hru_t_Mmean;
  float *hru_rh_Mmean;
  float *hru_u_Mmean;
  float *hru_t_acc;
  float *hru_rh_acc;
  float *hru_u_acc;
  float *Vw;
  float *Va;
  long  *start_open_day;
  long  *end_open_day;

// get variables:
  const float *hru_t;
  const float *hru_rh;
  const float *hru_u;

// put variables:

// declared parameters
  const float *Meyer_C;
  const float *Meyer_B;
  const float **Meyer_B_def;
  const float *hru_area;
  const float *basin_area;
  const float *hru_lat;
  const float *hru_elev;

  const long *start_open_water;
  const long *end_open_water;

void decl(void);
void init(void);
void run(void);
void add(void);
void process(void);
void finish(bool good);

Classlake* klone(string name) const;
};