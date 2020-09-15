//created by Manishankar Mondal

#include "ClassModule.h"


class Classnetall : public ClassModule {
public:

Classnetall(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *t;
const double *ea;
const double **tday_intvls;
const double **eaday_intvls;
const double *NotUsed;

// declared variables
double *net;
double *Rn; // net converted to mm
double *netD;
double *RnD; // netD converted to mm
double *RnD_POS;
double *cum_net;

// declared parameters

// variable inputs
const double *hru_t;
const double *hru_ea;
const double *Albedo;
const double *hru_SunAct;
const double *SunMax;
const double *Qdro;
const double *Qdfo;
const double *pQdro;
const double *pQdfo;
const double **pQdro_FREQ;
const double **pQdfo_FREQ;

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};