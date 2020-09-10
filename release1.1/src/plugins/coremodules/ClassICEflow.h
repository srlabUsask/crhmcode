//created by Manishankar Mondal

#include "ClassModule.h"

class ClassICEflow : public ClassModule {
public:

ClassICEflow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "") {};

// declared variables
float *Ux;
float *Ub;
float *Utot;
float *Ice_in;
float *Ice_out;
float *cumIce_in;
float *cumIce_out;
float *cumulative_net_rain;

// declared parameters
const float *distrib;
const float *radius_glacier;
const float *Arrhenius_const;
const float *slip_c;
const float *slip_m;
const float *slip_sf;
const float *slip_fs;
const float **distrib_hru;
const float *basin_area;   // [BASIN]
const float *hru_area; // [nhru]
const float *test_option; // [nhru]
const long  *SWE_to_firn_Julian;
const long  *order; // [nhru]
const long *Disable_ICEflow; // [nhru]
const long  *channel_option; // [nhru]
const float *basal_option; // [nhru]

// variable get inputs
const float *firn;
const float *net_rain;
const float *hru_GSL;

// variable get/put inputs
float *ice;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassICEflow* klone(string name) const;
};