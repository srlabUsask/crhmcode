//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class Classevap : public ClassModule {
public:

Classevap(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet { NULL };
double *hru_cum_actet { NULL };
double *evap { NULL };
double *hru_evap_PT { NULL };
double *evapD { NULL };
double *cum_evap { NULL };
double *evapGrangerD { NULL };
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
const double *rs { NULL };
const double *Zwind { NULL };

const long *evap_type { NULL };
const long *inhibit_evap { NULL };
const long *inhibit_evap_User { NULL };

// variable inputs
const double *Rn { NULL };
const double *RnD { NULL };
const double *RnD_POS { NULL };
const double *hru_t { NULL };
const double *hru_u { NULL };
const double *hru_ea { NULL };
const double *hru_tmean { NULL };
const double *hru_umean { NULL };
const double *hru_eamean { NULL };

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};