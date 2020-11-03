//created by Manishankar Mondal

#include "ClassModule.h"


class ClassKevin : public ClassModule {
public:

ClassKevin(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                   SWEpeak(NULL),
                                   SWElast(NULL) {};
// declared observation variables

// declared variables
double *albedo{ NULL };
double *sca{ NULL };
double *snowmelt{ NULL };
double *snowmeltD{ NULL };
double *cumsnowmelt{ NULL };
double *netLong{ NULL };
double *netShort{ NULL };
long  *winter{ NULL };
long  *SnowStat{ NULL };

// declared parameters
const double *Asnow1{ NULL };
const double *Asnow2{ NULL };
const double *Asoil{ NULL };
const double *cv{ NULL };
const double *tfactor{ NULL };
const double *nfactor{ NULL };
const double *meltthresh{ NULL };
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *hru_lat{ NULL };

// variable inputs
double *SWE{ NULL };
const double *hru_t{ NULL };
const double *hru_tmean{ NULL };
const double *hru_eamean{ NULL };
const double *hru_Qn{ NULL };
const double *hru_SunAct{ NULL };
const double *Qdro{ NULL };
const double *Qdfo{ NULL };
const double *SunMax{ NULL };

// local allocated arrays
double   *SWEpeak{ NULL };
double   *SWElast{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassKevin* klone(string name) const;
};