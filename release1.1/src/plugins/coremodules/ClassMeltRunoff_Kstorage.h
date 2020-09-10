//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMeltRunoff_Kstorage : public ClassModule {
public:

ClassMeltRunoff_Kstorage(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
float *Ksat;
float *Meltrunoff_K;
float *In_storage;

// get variables:
const float *rho;

// put variables
float *runKstorage;

// declared parameters
const float *d_g;
const float *hru_GSL;
const float *runLag;
const float *route_L;
const long  *inhibit_evap;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Kstorage* klone(string name) const;
};