//created by Manishankar Mondal

#include "ClassModule.h"

class ClassevapD : public ClassModule {
public:

ClassevapD(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_actet;
float *hru_cum_actet;
float *evapD;
float *cum_evap;
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

const long *evap_type;
const long *inhibit_evap;

// variable inputs
const float *RnD;
const float *hru_tmean;
const float *hru_umean;
const float *hru_eamean;

// variable puts

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD* klone(string name) const;

double gamma(float Pa, float t);         // Psychrometric constant
float lambda(float t);                   // Latent heat of vaporization
double delta(float t);                   // Slope of sat vap p vs t, kPa/°C
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
double fdaily(float u, float Ht);        // Drying power f(u) - interval
};