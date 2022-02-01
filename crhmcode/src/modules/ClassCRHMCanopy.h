//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassCRHMCanopy:public ClassModule {

public:

ClassCRHMCanopy(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 2000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_ { 0.0 }, Qli_ { 0.0 };

// observation variables

const double *Qsi { NULL };
const double *Qli { NULL };

// declared observation variables

double *Ts { NULL };
double *Qnsn { NULL };
double *Qsisn { NULL };
double *Qlisn { NULL };
double *Qlosn { NULL };

// put variables

double *SWE { NULL };

// declared variables

double *drip_Cpy { NULL };
double *thrufall_Cpy { NULL };
double *netRain_Cpy { NULL };
double *direct_rain { NULL };
double *rain_load { NULL };
double *Snow_load { NULL };
double *direct_snow { NULL };
double *SUnload { NULL };
double *SUnload_H2O { NULL };
double *Qnsn_Var { NULL };

double *net_rain { NULL };
double *cum_net_rain { NULL };
double *net_snow { NULL };
double *cum_net_snow { NULL };
double *net_p { NULL };
double *intcp_evap { NULL };
double *cum_intcp_evap { NULL };
double *Subl_Cpy { NULL };
double *cum_Subl_Cpy { NULL };
double *cum_SUnload { NULL };
double *cum_SUnload_H2O { NULL };

double *Cc { NULL };
double *k { NULL };
double *Tauc { NULL };
double *Pa { NULL };
double *ra { NULL };
double *u_FHt { NULL };
double *Pevap { NULL };
double *Qsisn_Var { NULL };
double *Qlisn_Var { NULL };

// variable inputs

const double *hru_t { NULL };
const double *hru_u { NULL };
const double *hru_rh { NULL };
const double *hru_ea { NULL };
const double *Albedo { NULL };

const double *hru_snow { NULL };
const double *hru_rain { NULL };
const double *hru_evap { NULL };

const double *SolAng { NULL };

const double *QsiS_Var { NULL };
const double *QsiA_Var { NULL };
const double *QliVt_Var { NULL };

// declared parameters:

const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *hru_elev { NULL };
const double *Ht { NULL };
const double *LAI { NULL };
const double *Sbar { NULL };
const double *Z0snow { NULL };
const double *Zref { NULL };
const double *Zwind { NULL };
const double *Zvent { NULL };
const double *unload_t { NULL };
const double *unload_t_water { NULL };
const double *B_canopy { NULL };
const double *Alpha_c { NULL };

const long *inhibit_evap { NULL };


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
double gamma(double Pa, double t); // Psychrometric constant (kPa/DEGREE_CELSIUS)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg DEGREE_CELSIUS))

ClassCRHMCanopy* klone(string name) const;

};
