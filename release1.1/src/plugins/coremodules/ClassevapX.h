//created by Manishankar Mondal

#include "ClassModule.h"

class ClassevapX : public ClassModule {
public:

ClassevapX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evap;
float *evap_D;
float *cum_evap;
float *Granger_D;
float *rc;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *hru_elev;
const float *F_Qg;
const float *Zwind;
const float *rcs;
const float *Htmax;
const float *LAImax;
const float *LAImin;
const float *s;
const float *PM_method;
const float *soil_Depth;

const long *soil_type;
const long *evap_type;
const long *inhibit_evap;

// variable inputs
const float *soil_moist;
const float *Rn;
const float *RnD;
const float *RnD_POS;
const float *hru_t;
const float *hru_u;
const float *hru_ea;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;

// declared observations variable
const float *Qsi;
const float *RnObs;

// declared observation functions
//float *Qsi_mean;
float *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapX* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/°C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};