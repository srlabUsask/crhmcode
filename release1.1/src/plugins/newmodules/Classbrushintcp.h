//created by Manishankar Mondal

#include "ClassModule.h"

class Classbrushintcp : public ClassModule {
public:

Classbrushintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared variables
float *net_rain;
float *cum_net_rain;
float *net_snow;
float *net_p;
float *Load;
float *Thru;
float *cumThru;
float *brushsubl;
float *spherecoeff;
float *cumbrushsubl;
float *intcp_evap;

// declared parameters
const float *basin_area;   // [ONE]
const float *hru_area;
const float *Ht;
const float *Zref;
const float *Zcan;
const float *brushAtten;
const float *Sbar;
const float *LAI;
const float *WidthJ;
const float *Tunload;

// variable inputs
const float *hru_t;
const float *hru_tmean;
const float *hru_rh;
const float *hru_u;
const float *hru_p;
const float *hru_rain;
const float *hru_snow;

// variable inputs/outputs
float *cumSubl;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classbrushintcp* klone(string name) const;

};