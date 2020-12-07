//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassevapD : public ClassModule {
public:

ClassevapD(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet { NULL };
double *hru_cum_actet { NULL };
double *evapD { NULL };
double *cum_evap { NULL };
double *G { NULL };
double *D { NULL };

// local allocated arrays
double *Pa { NULL };


// declared parameters
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *Ht { NULL };
const double *hru_elev { NULL };
const double *F_Qg { NULL };

const long *evap_type { NULL };
const long *inhibit_evap { NULL };

// variable inputs
const double *RnD { NULL };
const double *hru_tmean { NULL };
const double *hru_umean { NULL };
const double *hru_eamean { NULL };

// variable puts

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};