//created by Manishankar Mondal

#include "ClassModule.h"

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt{ NULL };

// declared observation variables
const double *p{ NULL };

// input variables
const double *hru_p{ NULL };

// declared variables
double *SWE{ NULL };
double *driftmelt{ NULL };
double *driftmeltDly{ NULL };
double *cumdriftmelt{ NULL };
double *cumdriftmeltDly{ NULL };
double *driftmeltD{ NULL };
double *snowmeltD{ NULL };

// declared parameters
const long *Type{ NULL };      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo{ NULL };   // drain to HRU
const double *InitSWE{ NULL };  // initial SWE
const double *length{ NULL };   // length normal to creek
const double *meltstorage{ NULL };  // delay parameter (days)
const double *meltLag{ NULL };      // delay parameter (days)

// variable inputs
const double *Qm{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};