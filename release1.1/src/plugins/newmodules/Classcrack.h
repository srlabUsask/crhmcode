//created by Manishankar Mondal

#include "ClassModule.h"

class Classcrack : public ClassModule {
public:

Classcrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
float *snowinfil;
float *cumsnowinfil;
float *infil;
float *cuminfil;
float *meltrunoff;
float *cummeltrunoff;
float *runoff;
float *cumrunoff;
float *RainOnSnow;
float *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const float *fallstat;
const float *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;

// variable inputs
const float *hru_tmax;
const float *snowmelt;
const float *SWE;
const float *net_rain;

// local allocated arrays
float **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};