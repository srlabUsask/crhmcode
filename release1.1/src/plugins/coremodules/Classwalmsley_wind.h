//created by Manishankar Mondal

#include "ClassModule.h"

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_Uadjust;
double *hru_Uchange;
double *WR;

// declared parameters
const double *Zwind;
const double *Ax;
const double *Bx;
const double *L;
const double *Walmsley_Ht;

// varaible inputs
const double *hru_u;

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};