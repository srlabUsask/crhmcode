/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include "../core/ClassModule.h"

class Classlake : public ClassModule {
public:

Classlake(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

  int DaysMonth {0};
  long ThisMonth {0};
  bool DoMean{ false };
  bool Ahead { false };
  long  N_intervals {0};
  long itime[6] {0,0,0,0,0,0};

// declared variables
  double *hru_evap{ NULL };
  double *hru_cum_evap{ NULL };
  // double *hru_actet{ NULL }; // modified Aug 2, 2022, hru_actet not calculated in lake_evap
  // double *hru_cum_actet{ NULL }; // modified Aug 2, 2022, hru_actet not calculated in lake_evap
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
