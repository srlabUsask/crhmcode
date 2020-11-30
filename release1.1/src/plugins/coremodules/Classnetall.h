//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"


class Classnetall : public ClassModule {
public:

Classnetall(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *t{ NULL };
const double *ea{ NULL };
const double **tday_intvls{ NULL };
const double **eaday_intvls{ NULL };
const double *NotUsed{ NULL };

// declared variables
double *net{ NULL };
double *Rn{ NULL }; // net converted to mm
double *netD{ NULL };
double *RnD{ NULL }; // netD converted to mm
double *RnD_POS{ NULL };
double *cum_net{ NULL };

// declared parameters

// variable inputs
const double *hru_t{ NULL };
const double *hru_ea{ NULL };
const double *Albedo{ NULL };
const double *hru_SunAct{ NULL };
const double *SunMax{ NULL };
const double *Qdro{ NULL };
const double *Qdfo{ NULL };
const double *pQdro{ NULL };
const double *pQdfo{ NULL };
const double **pQdro_FREQ{ NULL };
const double **pQdfo_FREQ{ NULL };

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};