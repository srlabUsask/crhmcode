//created by Manishankar Mondal

#include "ClassModule.h"


class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};
// declared variables
double *infil;
double *cuminfil;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
double *meltrunoff;
double *cummeltrunoff;

// local variables
double *k;
double *F0;
double *f0;
double *F1;
double *f1;
double *dthbot;
double *psidthbot;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *soil_moist_max;
const double *soil_moist_init;
const long  *soil_type;

// variable inputs
const double *net_rain;
const double *snowmelt;
double *soil_moist; // changed to PUT

// class allocated
double garain;      // precipitation/int
double intensity;   // precipitation/int converted to mm/h
double pond;        // mm

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