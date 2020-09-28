//created by Manishankar Mondal

#include "ClassModule.h"

class Classintcp : public ClassModule {
public:

Classintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *net_rain{ NULL };
double *cumnet_rain{ NULL };
double *cumnet_snow{ NULL };
double *net_snow{ NULL };
double *net_p{ NULL };
double *intcp_evap{ NULL };

// declared parameters
const double *basin_area{ NULL };
const double *hru_area{ NULL };

// variable inputs
const double *hru_rain{ NULL };
const double *hru_snow{ NULL };
const double *hru_p{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classintcp* klone(string name) const;
};