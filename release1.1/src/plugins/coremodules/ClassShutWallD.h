//created by Manishankar Mondal

#include "ClassModule.h"

class ClassShutWallD : public ClassModule {
public:

ClassShutWallD(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
float *Cc;
float *Cs;
float *Ra;
float *Rc;
float *Rs;
float *ETc;
float *ETs;
float *raa;
float *rca;
float *rcs;
float *rsa;
float *rss;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *rs;
const float *hru_elev;
const float *Cr;
const float *LAI;
const float *Ht;
const float *Zwind;
const float *w;
const float *rst;
const float *z0g;
const float *gammab;

const long *inhibit_evap;

// declared observations
const float *hru_umean;
const float *hru_tmean;
const float *hru_eamean;
const float *Qn;
const float *Qg;

// declared observation functions
float *Qnmean;
float *Qgmean;

// variable inputs

// local allocated arrays
float *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWallD* klone(string name) const;

float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/°C
};