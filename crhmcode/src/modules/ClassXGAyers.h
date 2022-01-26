//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassXGAyers : public ClassModule {
public:

ClassXGAyers(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};

// declared observation variables

// declared variables
double *infil{ NULL };         // unfrozen infiltration
double *cuminfil{ NULL };      // cumulative unfrozen infiltration
double *snowinfil{ NULL };     // frozen infiltration
double *cumsnowinfil{ NULL };  // cumulative frozen infiltration
double *meltrunoff{ NULL };      // [nhru]
double *cummeltrunoff{ NULL }; // cumulative frozen melt runoff
double *runoff{ NULL };        // cumulative runoff
double *cumrunoff{ NULL };     // cumulative melt runoff

// variable put

// local variables
long *infiltype{ NULL };

// declared parameters
const double *basin_area{ NULL };  // [BASIN]
const double *hru_area{ NULL };
const long  *texture{ NULL };
const long  *groundcover{ NULL };

// variable inputs
const double *snowmeltD{ NULL };   // (mm/day)
const double *net_rain{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassXGAyers* klone(string name) const;
};
