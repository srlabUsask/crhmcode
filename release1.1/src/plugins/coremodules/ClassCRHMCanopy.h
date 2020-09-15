//created by Manishankar Mondal

#include "ClassModule.h"

class ClassCRHMCanopy:public ClassModule {

public:

ClassCRHMCanopy(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_, Qli_;

// observation variables

const double *Qsi;
const double *Qli;

// declared observation variables

double *Ts;
double *Qnsn;
double *Qsisn;
double *Qlisn;
double *Qlosn;

// put variables

double *SWE;

// declared variables

double *drip_Cpy;
double *thrufall_Cpy;
double *netRain_Cpy;
double *direct_rain;
double *rain_load;
double *Snow_load;
double *direct_snow;
double *SUnload;
double *SUnload_H2O;
double *Qnsn_Var;

double *net_rain;
double *cum_net_rain;
double *net_snow;
double *cum_net_snow;
double *net_p;
double *intcp_evap;
double *cum_intcp_evap;
double *Subl_Cpy;
double *cum_Subl_Cpy;           
double *cum_SUnload;
double *cum_SUnload_H2O;

double *Cc;
double *k;
double *Tauc;
double *Pa;
double *ra;
double *u_FHt;
double *Pevap;
double *Qsisn_Var;
double *Qlisn_Var;

// variable inputs

const double *hru_t;
const double *hru_u;
const double *hru_rh;
const double *hru_ea;
const double *Albedo;

const double *hru_snow;
const double *hru_rain;
const double *hru_evap;

const double *SolAng;

const double *QsiS_Var;
const double *QsiA_Var;
const double *QliVt_Var;

// declared parameters:

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_elev;
const double *Ht;
const double *LAI;
const double *Sbar;
const double *Z0snow;
const double *Zref;
const double *Zwind;
const double *Zvent;
const double *unload_t;
const double *unload_t_water;
const double *B_canopy;
const double *Alpha_c;

const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/°C
double gamma(double Pa, double t); // Psychrometric constant (kPa/°C)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg °C))

ClassCRHMCanopy* klone(string name) const;

};