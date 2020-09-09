//created by Manishankar Mondal

#include "ClassModule.h"

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt;

// declared observation variables
const float *p;

// input variables
const float *hru_p;

// declared variables
float *SWE;
float *driftmelt;
float *driftmeltDly;
float *cumdriftmelt;
float *cumdriftmeltDly;
float *driftmeltD;
float *snowmeltD;

// declared parameters
const long *Type;      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo;   // drain to HRU
const float *InitSWE;  // initial SWE
const float *length;   // length normal to creek
const float *meltstorage;  // delay parameter (days)
const float *meltLag;      // delay parameter (days)

// variable inputs
const float *Qm;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};