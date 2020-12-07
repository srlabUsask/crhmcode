//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class Classevap_Resist : public ClassModule {
public:

Classevap_Resist(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QsiS_Var, QsiA_Var") {};

double Qsi_ {0.0};
long QsiCnt {0};
long TsCnt {0};
long RnObsCnt {0};
bool BeforeCorrectionRCS {false};

// declared variables
double *hru_actet { NULL };
double *hru_cum_actet { NULL };
double *evap { NULL };
double *evapD { NULL };
double *cum_evap { NULL };
double *rc { NULL };

// local allocated arrays
double *Pa { NULL };

// declared parameters
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *Ht { NULL };
const double *Htmax { NULL };
const double *Zwind { NULL };
const double *hru_elev { NULL };
const double *F_Qg { NULL };
const double *rcs { NULL };
const double *LAImax { NULL };
const double *LAImin { NULL };
const double *soil_Depth { NULL };

const long *evap_type { NULL };
const long *inhibit_evap { NULL };
const long *soil_type { NULL };
const double *s { NULL };
const long *PM_method { NULL };

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
const double *soil_moist { NULL };
const double *QsiS_Var { NULL };
const double *QsiA_Var { NULL };

// declared observations variable
const double *Qsi { NULL };
const double *Ts { NULL };
const double *RnObs { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap_Resist* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};