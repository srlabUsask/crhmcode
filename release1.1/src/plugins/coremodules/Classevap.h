//created by Manishankar Mondal

#include "ClassModule.h"

class Classevap : public ClassModule {
public:

Classevap(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evap;
float *hru_evap_PT;
float *evapD;
float *cum_evap;
float *evapGrangerD;
float *G;
float *D;

// local allocated arrays
float *Pa;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *Ht;
const float *hru_elev;
const float *F_Qg;
const float *rs;
const float *Zwind;

const long *evap_type;
const long *inhibit_evap;
const long *inhibit_evap_User;

// variable inputs
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

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/°C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};