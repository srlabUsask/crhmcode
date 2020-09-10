//created by Manishankar Mondal

#include "ClassModule.h"

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *hru_Uadjust;
float *hru_Uchange;
float *WR;

// declared parameters
const float *Zwind;
const float *Ax;
const float *Bx;
const float *L;
const float *Walmsley_Ht;

// varaible inputs
const float *hru_u;

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};