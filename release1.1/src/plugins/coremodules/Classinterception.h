//created by Manishankar Mondal

#include "ClassModule.h"


class Classinterception : public ClassModule {
public:

Classinterception(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
const double *Qsi;

// variable inputs
const double *hru_t;
const double *hru_snow;
const double *hru_rain;
const double *hru_u;
const double *hru_rh;

// declared variables
double *SI_Lo;
double *net_snow;
double *net_rain;
double *SI_Subl;
double *Cum_Subl;
double *Cum_net_snow;
double *v;

// declared parameters
const double *Sbar;
const double *LAI;
const double *k;
const double *velw;
const double *Ht;
const double *WidthJ;
const double *basin_area;
const double *hru_area;

// variable inputs

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classinterception* klone(string name) const;
};