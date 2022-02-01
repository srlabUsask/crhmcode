//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassNO_pbsm : public ClassModule {
public:

ClassNO_pbsm(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
// declared variables
double *SWE{ NULL };
double *cumSno{ NULL };
double *snowdepth{ NULL };

// declared parameters
const double *basin_area{ NULL };
const double *hru_area{ NULL };
const long *inhibit_evap{ NULL };

// variable inputs
const double *net_snow{ NULL };
const long  *hru_newsnow{ NULL };

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNO_pbsm* klone(string name) const;
};
