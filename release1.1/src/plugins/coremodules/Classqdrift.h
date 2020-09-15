//created by Manishankar Mondal

#include "ClassModule.h"

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt;

// declared observation variables
const double *p;

// input variables
const double *hru_p;

// declared variables
double *SWE;
double *driftmelt;
double *driftmeltDly;
double *cumdriftmelt;
double *cumdriftmeltDly;
double *driftmeltD;
double *snowmeltD;

// declared parameters
const long *Type;      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo;   // drain to HRU
const double *InitSWE;  // initial SWE
const double *length;   // length normal to creek
const double *meltstorage;  // delay parameter (days)
const double *meltLag;      // delay parameter (days)

// variable inputs
const double *Qm;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};