//created by Manishankar Mondal

#include "ClassModule.h"

class ClassevapD_Resist : public ClassModule {
public:

ClassevapD_Resist(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt;
long TsCnt;

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
float *rc;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *Htmax;
const float *Zwind;
const float *hru_elev;
const float *F_Qg;
const float *rcs;
const float *LAImax;
const float *LAImin;
const float *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const float *s;
const long *PM_method;

// variable inputs
const float *RnD;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;
const float *soil_moist;

// declared observations variable
const float *Qsi;
const float *Ts;

// declared observation functions
float *Qsi_mean;
float *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD_Resist* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/°C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};