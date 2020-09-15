//created by Manishankar Mondal

#include "ClassModule.h"

class ClassICEflow : public ClassModule {
public:

ClassICEflow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "") {};

// declared variables
double *Ux;
double *Ub;
double *Utot;
double *Ice_in;
double *Ice_out;
double *cumIce_in;
double *cumIce_out;
double *cumulative_net_rain;

// declared parameters
const double *distrib;
const double *radius_glacier;
const double *Arrhenius_const;
const double *slip_c;
const double *slip_m;
const double *slip_sf;
const double *slip_fs;
const double **distrib_hru;
const double *basin_area;   // [BASIN]
const double *hru_area; // [nhru]
const double *test_option; // [nhru]
const long  *SWE_to_firn_Julian;
const long  *order; // [nhru]
const long *Disable_ICEflow; // [nhru]
const long  *channel_option; // [nhru]
const double *basal_option; // [nhru]

// variable get inputs
const double *firn;
const double *net_rain;
const double *hru_GSL;

// variable get/put inputs
double *ice;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassICEflow* klone(string name) const;
};