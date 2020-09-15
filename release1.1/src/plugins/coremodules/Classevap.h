//created by Manishankar Mondal

#include "ClassModule.h"

class Classevap : public ClassModule {
public:

Classevap(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *hru_evap_PT;
double *evapD;
double *cum_evap;
double *evapGrangerD;
double *G;
double *D;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *hru_elev;
const double *F_Qg;
const double *rs;
const double *Zwind;

const long *evap_type;
const long *inhibit_evap;
const long *inhibit_evap_User;

// variable inputs
const double *Rn;
const double *RnD;
const double *RnD_POS;
const double *hru_t;
const double *hru_u;
const double *hru_ea;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};