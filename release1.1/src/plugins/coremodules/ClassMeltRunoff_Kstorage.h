//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMeltRunoff_Kstorage : public ClassModule {
public:

ClassMeltRunoff_Kstorage(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module { NULL }; // used to call preser for simple projects

// declared variables
double *Ksat{ NULL };
double *Meltrunoff_K{ NULL };
double *In_storage{ NULL };

// get variables:
const double *rho{ NULL };

// put variables
double *runKstorage{ NULL };

// declared parameters
const double *d_g{ NULL };
const double *hru_GSL{ NULL };
const double *runLag{ NULL };
const double *route_L{ NULL };
const long  *inhibit_evap{ NULL };
const long  *inhibit_MeltRunoff_Kstorage{ NULL };

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Kstorage* klone(string name) const;
};