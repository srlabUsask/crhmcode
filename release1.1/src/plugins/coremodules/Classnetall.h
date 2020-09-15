//created by Manishankar Mondal

#include "ClassModule.h"


class Classnetall : public ClassModule {
public:

Classnetall(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const float *t;
const float *ea;
const float **tday_intvls;
const float **eaday_intvls;
const float *NotUsed;

// declared variables
float *net;
float *Rn; // net converted to mm
float *netD;
float *RnD; // netD converted to mm
float *RnD_POS;
float *cum_net;

// declared parameters

// variable inputs
const float *hru_t;
const float *hru_ea;
const float *Albedo;
const float *hru_SunAct;
const float *SunMax;
const float *Qdro;
const float *Qdfo;
const float *pQdro;
const float *pQdfo;
const float **pQdro_FREQ;
const float **pQdfo_FREQ;

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};