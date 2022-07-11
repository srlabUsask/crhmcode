//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassGreencrack2 : public ClassModule {
public:

ClassGreencrack2(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *snowinfil{ NULL };
double *cumsnowinfil{ NULL };
double *infil{ NULL };
double *cuminfil{ NULL };
double *meltrunoff{ NULL };
double *cummeltrunoff{ NULL };
double *runoff{ NULL };
double *cumrunoff{ NULL };
double *RainOnSnow{ NULL };
double *RainOnSnowA{ NULL };
long  *crackstat{ NULL };
long  *crackon{ NULL };

// declared parameters
const double *basin_area{ NULL }; // [BASIN]
const double *hru_area{ NULL };
const double *fallstat{ NULL };
const double *Major{ NULL };      // threshold for major melt event(default is 5 mm/day)
const long* infDays{ NULL }; // maximum number of days of snowmelt infiltration to frozen soil
const double *maxinfil_prm{ NULL };
const long  *PriorInfiltration{ NULL };
const long  *texture{ NULL };
const long  *groundcover{ NULL };
const long  *soil_type{ NULL };

// declared parameters (Green-ampt related)
const double *psi_fixup{ NULL };
const double *ksat_fixup{ NULL };
const long *ga_rechr{ NULL };

// variable inputs
const double *hru_tmax{ NULL };
const double *snowmelt{ NULL };
const double *snowmeltD{ NULL };
const double *SWE{ NULL };
const double *net_rain{ NULL };

// local variables (Green-ampt related)
double *k{ NULL };
double *F0{ NULL };
double *f0{ NULL };
double *F1{ NULL };
double *f1{ NULL };
double *dthbot{ NULL };
double *psidthbot{ NULL };

const double *soil_rechr_max{ NULL };
const double *soil_rechr_init{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
double *soil_rechr{ NULL }; // changed tp PUT
double *soil_moist{ NULL }; // changed tp PUT


// local allocated arrays
double **Xinfil{ NULL }; // [3] [nhru]
long *timer{ NULL };

// temporaries (Green-Ampt related)
double garain {0.0};      // precipitation/int
double intensity  {0.0};    // precipitation/int converted to mm/h
double pond{ 0.0 };        // mm


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack2* klone(string name) const;

private:
void applyCrack(double RainOnSnow_int);
void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);

};
