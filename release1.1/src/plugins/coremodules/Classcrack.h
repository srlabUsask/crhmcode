//created by Manishankar Mondal

#include "ClassModule.h"

class Classcrack : public ClassModule {
public:

Classcrack(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *snowinfil { NULL };
double *cumsnowinfil { NULL };
double *infil { NULL };
double *cuminfil { NULL };
double *meltrunoff { NULL };
double *cummeltrunoff { NULL };
double *runoff { NULL };
double *cumrunoff { NULL };
double *RainOnSnow { NULL };
double *RainOnSnowA { NULL };
long  *crackstat { NULL };
long  *crackon { NULL };

// declared parameters
const double *basin_area { NULL }; // [BASIN]
const double *hru_area { NULL };
const double *fallstat { NULL };
const double *Major { NULL };      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration { NULL };

// variable inputs
const double *hru_tmax { NULL };
const double *snowmelt { NULL };
const double *SWE { NULL };
const double *net_rain { NULL };

// local allocated arrays
double **Xinfil { NULL }; // [3] [nhru]
long *timer { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};