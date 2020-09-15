//created by Manishankar Mondal

#include "ClassModule.h"


class ClassGreencrack : public ClassModule {
public:

ClassGreencrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *infil;
double *cuminfil;
double *meltrunoff;
double *cummeltrunoff;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
long  *crackstat;
long  *crackon;
double *RainOnSnow;
double *RainOnSnowA;

// local variables
double *k;
double *F0;
double *f0;
double *F1;
double *f1;
double *dthbot;
double *psidthbot;
long  *timer;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *fallstat;
const double *Major;      // threshold for major melt event(default is 5 mm/day)
const double *soil_moist_max;
const double *soil_moist_init;
const long  *soil_type;
const long  *PriorInfiltration;

// variable inputs
const double *hru_tmax;
const double *snowmelt;
const double *SWE;
const double *net_rain;
double *soil_moist; // changed tp PUT

// class allocated
double garain;      // precipitation/int
double intensity;   // precipitation/int converted to mm/h
double pond;        // mm

// class allocated arrays
double **Xinfil; // [3] [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};