//created by Manishankar Mondal

#include "ClassModule.h"

class ClassIceBulb : public ClassModule {
public:

ClassIceBulb(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_icebulb{ NULL };
double *hru_rainI{ NULL };
double *cumhru_rainI{ NULL };
double *hru_snowI{ NULL };
double *cumhru_snowI{ NULL };
double *cumhru_pI{ NULL };
double *Pa{ NULL };

// variable inputs
const double *hru_t{ NULL };
const double *hru_rh{ NULL };
const double *hru_p{ NULL };

// declared parameters
const double *hru_elev{ NULL };
const double *tmaxI_allrain{ NULL };
const double *tmaxI_allsnow{ NULL };

void decl(void);
void init(void);
void run(void);

ClassIceBulb* klone(string name) const;
};