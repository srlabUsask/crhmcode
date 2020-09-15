//created by Manishankar Mondal

#include "ClassModule.h"


class Classinterception : public ClassModule {
public:

Classinterception(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
const float *Qsi;

// variable inputs
const float *hru_t;
const float *hru_snow;
const float *hru_rain;
const float *hru_u;
const float *hru_rh;

// declared variables
float *SI_Lo;
float *net_snow;
float *net_rain;
float *SI_Subl;
float *Cum_Subl;
float *Cum_net_snow;
float *v;

// declared parameters
const float *Sbar;
const float *LAI;
const float *k;
const float *velw;
const float *Ht;
const float *WidthJ;
const float *basin_area;
const float *hru_area;

// variable inputs

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classinterception* klone(string name) const;
};