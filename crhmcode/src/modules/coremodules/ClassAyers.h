//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *infil { NULL };
double *cuminfil { NULL };
double *runoff { NULL };
double *cumrunoff { NULL };
double *snowinfil { NULL };
double *cumsnowinfil { NULL };
double *meltrunoff { NULL };
double *cummeltrunoff { NULL };
double *melt_int { NULL }; // interval melt - from snowmelD

// declared parameters
const double *basin_area { NULL }; // [BASIN]
const double *hru_area { NULL };
const long  *texture { NULL };
const long  *groundcover { NULL };

// variable inputs
const double *net_rain { NULL };
const double *snowmeltD { NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};