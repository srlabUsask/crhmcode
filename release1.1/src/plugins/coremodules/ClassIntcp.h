//created by Manishankar Mondal

#include "ClassModule.h"

class Classintcp : public ClassModule {
public:

Classintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *net_rain;
double *cumnet_rain;
double *cumnet_snow;
double *net_snow;
double *net_p;
double *intcp_evap;

// declared parameters
const double *basin_area;
const double *hru_area;

// variable inputs
const double *hru_rain;
const double *hru_snow;
const double *hru_p;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classintcp* klone(string name) const;
};