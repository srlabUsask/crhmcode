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
  double *hru_evap;
  double *hru_cum_evap;
  double *hru_actet;
  double *hru_cum_actet;
  double *lake_evap_month;
  double *hru_t_Mmean;
  double *hru_rh_Mmean;
  double *hru_u_Mmean;
  double *hru_t_acc;
  double *hru_rh_acc;
  double *hru_u_acc;
  double *Vw;
  double *Va;
  long  *start_open_day;
  long  *end_open_day;

// get variables:
  const double *hru_t;
  const double *hru_rh;
  const double *hru_u;

// put variables:

// declared parameters
  const double *Meyer_C;
  const double *Meyer_B;
  const double **Meyer_B_def;
  const double *hru_area;
  const double *basin_area;
  const double *hru_lat;
  const double *hru_elev;

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