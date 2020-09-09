//created by Manishankar Mondal

#include "ClassModule.h"

class ClassIceBulb : public ClassModule {
public:

ClassIceBulb(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_icebulb;
float *hru_rainI;
float *cumhru_rainI;
float *hru_snowI;
float *cumhru_snowI;
float *cumhru_pI;
float *Pa;

// variable inputs
const float *hru_t;
const float *hru_rh;
const float *hru_p;

// declared parameters
const float *hru_elev;
const float *tmaxI_allrain;
const float *tmaxI_allsnow;

void decl(void);
void init(void);
void run(void);

ClassIceBulb* klone(string name) const;
};