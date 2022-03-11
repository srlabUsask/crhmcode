//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassShutWall : public ClassModule {
public:

ClassShutWall(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt{0};
long Qg_Cnt{0};
double z0{0.0};
double d{0.0};
double n{0.0};


// declared variables
double* hru_actet{NULL};
double *hru_cum_actet{ NULL };
double *evap{ NULL };
double *evapD{ NULL };
double *cum_evap{ NULL };
double *Cc{ NULL };
double *Cs{ NULL };
double *Ra{ NULL };
double *Rc{ NULL };
double *Rs{ NULL };
double *ETc{ NULL };
double *ETs{ NULL };
double *raa{ NULL };
double *rca{ NULL };
double *rcs{ NULL };
double *rsa{ NULL };
double *rss{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *rs{ NULL };
const double *hru_elev{ NULL };
const double *Cr{ NULL };
const double *LAI{ NULL };
const double *Ht{ NULL };
const double *Zwind{ NULL };
const double *w{ NULL };
const double *rst{ NULL };
const double *z0g{ NULL };
const double *gammab{ NULL };

const long *inhibit_evap{ NULL };

// declared observations
const double *hru_u{ NULL };
const double *hru_t{ NULL };
const double *hru_ea{ NULL };
const double *Qn{ NULL };
const double *Qg{ NULL };

// variable inputs

// local allocated arrays
double *Pa{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWall* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
};