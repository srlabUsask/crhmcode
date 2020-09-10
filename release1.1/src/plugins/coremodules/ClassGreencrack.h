//created by Manishankar Mondal

#include "ClassModule.h"


class ClassGreencrack : public ClassModule {
public:

ClassGreencrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
float *infil;
float *cuminfil;
float *meltrunoff;
float *cummeltrunoff;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
long  *crackstat;
long  *crackon;
float *RainOnSnow;
float *RainOnSnowA;

// local variables
float *k;
float *F0;
float *f0;
float *F1;
float *f1;
float *dthbot;
float *psidthbot;
long  *timer;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *fallstat;
const float *Major;      // threshold for major melt event(default is 5 mm/day)
const float *soil_moist_max;
const float *soil_moist_init;
const long  *soil_type;
const long  *PriorInfiltration;

// variable inputs
const float *hru_tmax;
const float *snowmelt;
const float *SWE;
const float *net_rain;
float *soil_moist; // changed tp PUT

// class allocated
float garain;      // precipitation/int
float intensity;   // precipitation/int converted to mm/h
float pond;        // mm

// class allocated arrays
float **Xinfil; // [3] [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(float F0, float dt);

float calcf1(float F, float psidth);
};