//created by Manishankar Mondal

#include "ClassModule.h"


class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};
// declared variables
float *infil;
float *cuminfil;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
float *meltrunoff;
float *cummeltrunoff;

// local variables
float *k;
float *F0;
float *f0;
float *F1;
float *f1;
float *dthbot;
float *psidthbot;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *soil_moist_max;
const float *soil_moist_init;
const long  *soil_type;

// variable inputs
const float *net_rain;
const float *snowmelt;
float *soil_moist; // changed to PUT

// class allocated
float garain;      // precipitation/int
float intensity;   // precipitation/int converted to mm/h
float pond;        // mm

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreenAmpt* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(float F0, float dt);

float calcf1(float F, float psidth);
};