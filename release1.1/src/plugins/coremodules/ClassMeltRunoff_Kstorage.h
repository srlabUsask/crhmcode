//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMeltRunoff_Kstorage : public ClassModule {
public:

ClassMeltRunoff_Kstorage(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
double *Ksat;
double *Meltrunoff_K;
double *In_storage;

// get variables:
const double *rho;

// put variables
double *runKstorage;

// declared parameters
const double *d_g;
const double *hru_GSL;
const double *runLag;
const double *route_L;
const long  *inhibit_evap;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Kstorage* klone(string name) const;
};