//created by Manishankar Mondal

#include "ClassModule.h"

class Classbrushintcp : public ClassModule {
public:

Classbrushintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared variables
double *net_rain;
double *cum_net_rain;
double *net_snow;
double *net_p;
double *Load;
double *Thru;
double *cumThru;
double *brushsubl;
double *spherecoeff;
double *cumbrushsubl;
double *intcp_evap;

// declared parameters
const double *basin_area;   // [ONE]
const double *hru_area;
const double *Ht;
const double *Zref;
const double *Zcan;
const double *brushAtten;
const double *Sbar;
const double *LAI;
const double *WidthJ;
const double *Tunload;

// variable inputs
const double *hru_t;
const double *hru_tmean;
const double *hru_rh;
const double *hru_u;
const double *hru_p;
const double *hru_rain;
const double *hru_snow;

// variable inputs/outputs
double *cumSubl;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classbrushintcp* klone(string name) const;

};