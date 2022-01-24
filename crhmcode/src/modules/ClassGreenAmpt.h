//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"


class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};
// declared variables
double *infil{ NULL };
double *cuminfil{ NULL };
double *runoff{ NULL };
double *cumrunoff{ NULL };
double *snowinfil{ NULL };
double *cumsnowinfil{ NULL };
double *meltrunoff{ NULL };
double *cummeltrunoff{ NULL };

// local variables
double *k{ NULL };
double *F0{ NULL };
double *f0{ NULL };
double *F1{ NULL };
double *f1{ NULL };
double *dthbot{ NULL };
double *psidthbot{ NULL };

// declared parameters
const double *basin_area{ NULL }; // [BASIN]
const double *hru_area{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const long  *soil_type{ NULL };

// variable inputs
const double *net_rain{ NULL };
const double *snowmelt{ NULL };
double *soil_moist{ NULL }; // changed to PUT

// class allocated
double garain {0.0};      // precipitation/int
double intensity {0.0};   // precipitation/int converted to mm/h
double pond {0.0};        // mm

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreenAmpt* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};