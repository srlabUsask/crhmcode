//created by Manishankar Mondal

#include "ClassModule.h"

class Classcrack : public ClassModule {
public:

Classcrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *snowinfil;
double *cumsnowinfil;
double *infil;
double *cuminfil;
double *meltrunoff;
double *cummeltrunoff;
double *runoff;
double *cumrunoff;
double *RainOnSnow;
double *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *fallstat;
const double *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;

// variable inputs
const double *hru_tmax;
const double *snowmelt;
const double *SWE;
const double *net_rain;

// local allocated arrays
double **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};