//created by Manishankar Mondal

#include "ClassModule.h"

class ClassCRHMCanopyClearing:public ClassModule {

public:

ClassCRHMCanopyClearing(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

float Qsi_, Qli_;

// observation variables

const float *Qsi;
const float *Qli;

// declared observation variables

float *Ts;
float *Qnsn;
float *Qsisn;
float *Qlisn;
float *Qlosn;

// put variables

float *SWE;

// declared variables

float *drip_Cpy;
float *thrufall_Cpy;
float *netRain_Cpy;
float *direct_rain;
float *rain_load;
float *Snow_load;
float *direct_snow;
float *SUnload;
float *SUnload_H2O;
float *Qnsn_Var;
float *Qsisn_Var;
float *Qlisn_Var;

float *net_rain;
float *cum_net_rain;
float *net_snow;
float *cum_net_snow;
float *net_p;
float *intcp_evap;
float *cum_intcp_evap;
float *Subl_Cpy;
float *cum_Subl_Cpy;
float *cum_SUnload;
float *cum_SUnload_H2O;

float *Cc;
float *k;
float *Tauc;
float *Pa;
float *ra;
float *u_FHt;
float *Pevap;

// variable inputs

const float *hru_t;
const float *hru_u;
const float *hru_rh;
const float *hru_ea;
const float *Albedo;

const float *hru_snow;
const float *hru_rain;
const float *hru_evap;

const float *SolAng;

const float *QsiS_Var;
const float *QsiA_Var;
const float *QliVt_Var;

// declared parameters:

const float *basin_area;   // [BASIN]
const float *hru_area;
const float *hru_elev;
const float *Ht;
const float *LAI;
const float *Sbar;
const float *Z0snow;
const float *Zref;
const float *Zwind;
const float *Zvent;
const float *unload_t;
const float *unload_t_water;
const float *Alpha_c;
const float *B_canopy;

const long *CanopyClearing;
const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(float t); // Slope of sat vap p vs t, kPa/°C
double gamma(float Pa, float t); // Psychrometric constant (kPa/°C)
float RHOa(float t, float ea, float Pa); // atmospheric density (kg/m^3)
float lambda(float t); // Latent heat of vaporization (mJ/(kg °C))

ClassCRHMCanopyClearing* klone(string name) const;

};