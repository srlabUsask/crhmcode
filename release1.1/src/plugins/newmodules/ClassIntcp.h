//created by Manishankar Mondal

#include "ClassModule.h"

class Classintcp : public ClassModule {
public:

Classintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *net_rain;
float *cumnet_rain;
float *cumnet_snow;
float *net_snow;
float *net_p;
float *intcp_evap;

// declared parameters
const float *basin_area;
const float *hru_area;

// variable inputs
const float *hru_rain;
const float *hru_snow;
const float *hru_p;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classintcp* klone(string name) const;
};