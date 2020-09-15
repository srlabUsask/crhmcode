//created by Manishankar Mondal

#include "ClassModule.h"

class ClassXGAyers : public ClassModule {
public:

ClassXGAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};

// declared observation variables

// declared variables
double *infil;         // unfrozen infiltration
double *cuminfil;      // cumulative unfrozen infiltration
double *snowinfil;     // frozen infiltration
double *cumsnowinfil;  // cumulative frozen infiltration
double *meltrunoff;      // [nhru]
double *cummeltrunoff; // cumulative frozen melt runoff
double *runoff;        // cumulative runoff
double *cumrunoff;     // cumulative melt runoff

// variable put

// local variables
long *infiltype;

// declared parameters
const double *basin_area;  // [BASIN]
const double *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const double *snowmeltD;   // (mm/day)
const double *net_rain;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassXGAyers* klone(string name) const;
};