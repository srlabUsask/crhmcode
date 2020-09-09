//created by Manishankar Mondal

#include "ClassModule.h"

class ClassXGAyers : public ClassModule {
public:

ClassXGAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};

// declared observation variables

// declared variables
float *infil;         // unfrozen infiltration
float *cuminfil;      // cumulative unfrozen infiltration
float *snowinfil;     // frozen infiltration
float *cumsnowinfil;  // cumulative frozen infiltration
float *meltrunoff;      // [nhru]
float *cummeltrunoff; // cumulative frozen melt runoff
float *runoff;        // cumulative runoff
float *cumrunoff;     // cumulative melt runoff

// variable put

// local variables
long *infiltype;

// declared parameters
const float *basin_area;  // [BASIN]
const float *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const float *snowmeltD;   // (mm/day)
const float *net_rain;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassXGAyers* klone(string name) const;
};