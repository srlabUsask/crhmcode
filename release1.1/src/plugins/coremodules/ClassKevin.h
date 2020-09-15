//created by Manishankar Mondal

#include "ClassModule.h"


class ClassKevin : public ClassModule {
public:

ClassKevin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   SWEpeak(NULL),
                                   SWElast(NULL) {};
// declared observation variables

// declared variables
double *albedo;
double *sca;
double *snowmelt;
double *snowmeltD;
double *cumsnowmelt;
double *netLong;
double *netShort;
long  *winter;
long  *SnowStat;

// declared parameters
const double *Asnow1;
const double *Asnow2;
const double *Asoil;
const double *cv;
const double *tfactor;
const double *nfactor;
const double *meltthresh;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;

// variable inputs
double *SWE;
const double *hru_t;
const double *hru_tmean;
const double *hru_eamean;
const double *hru_Qn;
const double *hru_SunAct;
const double *Qdro;
const double *Qdfo;
const double *SunMax;

// local allocated arrays
double   *SWEpeak;
double   *SWElast;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassKevin* klone(string name) const;
};