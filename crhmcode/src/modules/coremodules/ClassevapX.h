//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"


class ClassevapX : public ClassModule {
public:

ClassevapX(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet { NULL };
double *hru_cum_actet { NULL };
double *evap { NULL };
double *evap_D { NULL };
double *cum_evap { NULL };
double *Granger_D { NULL };
double *rc { NULL };

// local allocated arrays
double *Pa { NULL };

// declared parameters
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *Ht { NULL };
const double *hru_elev { NULL };
const double *F_Qg { NULL };
const double *Zwind { NULL };
const double *rcs { NULL };
const double *Htmax { NULL };
const double *LAImax { NULL };
const double *LAImin { NULL };
const double *s { NULL };
const double *PM_method { NULL };
const double *soil_Depth { NULL };

const long *soil_type { NULL };
const long *evap_type { NULL };
const long *inhibit_evap { NULL };

// variable inputs
const double *soil_moist { NULL };
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
const double *Qsi { NULL };
const double *RnObs { NULL };

// declared observation functions
//double *Qsi_mean;
double *Tsmean { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapX* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};