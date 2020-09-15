//created by Manishankar Mondal

#include "ClassModule.h"

class ClassevapD_Resist : public ClassModule {
public:

ClassevapD_Resist(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt;
long TsCnt;

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evapD;
double *cum_evap;
double *rc;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *Htmax;
const double *Zwind;
const double *hru_elev;
const double *F_Qg;
const double *rcs;
const double *LAImax;
const double *LAImin;
const double *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const double *s;
const long *PM_method;

// variable inputs
const double *RnD;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;
const double *soil_moist;

// declared observations variable
const double *Qsi;
const double *Ts;

// declared observation functions
double *Qsi_mean;
double *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD_Resist* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};