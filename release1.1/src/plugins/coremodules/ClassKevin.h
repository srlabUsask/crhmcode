//created by Manishankar Mondal

#include "ClassModule.h"


class ClassKevin : public ClassModule {
public:

ClassKevin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   SWEpeak(NULL),
                                   SWElast(NULL) {};
// declared observation variables

// declared variables
float *albedo;
float *sca;
float *snowmelt;
float *snowmeltD;
float *cumsnowmelt;
float *netLong;
float *netShort;
long  *winter;
long  *SnowStat;

// declared parameters
const float *Asnow1;
const float *Asnow2;
const float *Asoil;
const float *cv;
const float *tfactor;
const float *nfactor;
const float *meltthresh;
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_lat;

// variable inputs
float *SWE;
const float *hru_t;
const float *hru_tmean;
const float *hru_eamean;
const float *hru_Qn;
const float *hru_SunAct;
const float *Qdro;
const float *Qdfo;
const float *SunMax;

// local allocated arrays
float   *SWEpeak;
float   *SWElast;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassKevin* klone(string name) const;
};