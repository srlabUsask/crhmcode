//created by Manishankar Mondal

#include "ClassModule.h"

class ClassIceBulb : public ClassModule {
public:

ClassIceBulb(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_icebulb;
double *hru_rainI;
double *cumhru_rainI;
double *hru_snowI;
double *cumhru_snowI;
double *cumhru_pI;
double *Pa;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_p;

// declared parameters
const double *hru_elev;
const double *tmaxI_allrain;
const double *tmaxI_allsnow;

void decl(void);
void init(void);
void run(void);

ClassIceBulb* klone(string name) const;
};