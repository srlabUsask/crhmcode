//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNO_pbsm : public ClassModule {
public:

ClassNO_pbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
// declared variables
double *SWE;
double *cumSno;
double *snowdepth;

// declared parameters
const double *basin_area;
const double *hru_area;
const long *inhibit_evap;

// variable inputs
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNO_pbsm* klone(string name) const;
};