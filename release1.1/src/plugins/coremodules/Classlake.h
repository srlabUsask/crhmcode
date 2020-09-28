//created by Manishankar Mondal

#include "ClassModule.h"

class Classlake : public ClassModule {
public:

Classlake(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  int DaysMonth {0};
  long ThisMonth {0};
  bool DoMean{ false };
  bool Ahead { false };
  long  N_intervals {0};
  long itime[6] {0,0,0,0,0,0};

// declared variables
  double *hru_evap{ NULL };
  double *hru_cum_evap{ NULL };
  double *hru_actet{ NULL };
  double *hru_cum_actet{ NULL };
  double *lake_evap_month{ NULL };
  double *hru_t_Mmean{ NULL };
  double *hru_rh_Mmean{ NULL };
  double *hru_u_Mmean{ NULL };
  double *hru_t_acc{ NULL };
  double *hru_rh_acc{ NULL };
  double *hru_u_acc{ NULL };
  double *Vw{ NULL };
  double *Va{ NULL };
  long  *start_open_day{ NULL };
  long  *end_open_day{ NULL };

// get variables:
  const double *hru_t{ NULL };
  const double *hru_rh{ NULL };
  const double *hru_u{ NULL };

// put variables:

// declared parameters
  const double *Meyer_C{ NULL };
  const double *Meyer_B{ NULL };
  const double **Meyer_B_def{ NULL };
  const double *hru_area{ NULL };
  const double *basin_area{ NULL };
  const double *hru_lat{ NULL };
  const double *hru_elev{ NULL };

  const long *start_open_water{ NULL };
  const long *end_open_water{ NULL };

void decl(void);
void init(void);
void run(void);
void add(void);
void process(void);
void finish(bool good);

Classlake* klone(string name) const;
};