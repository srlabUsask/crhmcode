//created by Manishankar Mondal

#include "ClassModule.h"

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *infil;
double *cuminfil;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
double *meltrunoff;
double *cummeltrunoff;
double *melt_int; // interval melt - from snowmelD

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const double *net_rain;
const double *snowmeltD;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};