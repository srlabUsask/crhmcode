//created by Manishankar Mondal

#include "ClassModule.h"



class Classglobal : public ClassModule {
public:

Classglobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QdroD{ NULL };
double *QdroDext{ NULL };
double *QdfoD{ NULL };
double *Qdro{ NULL };
double *Qdfo{ NULL };
double *Qdflat{ NULL };
double *QdflatD{ NULL };
double *QdflatE{ NULL };
double *SolAng{ NULL };
double *SunMax{ NULL };
double *cosxs{ NULL };
double *cosxsflat{ NULL };
double *pQdro{ NULL };
double **pQdro_FREQ{ NULL };
double *pQdfo{ NULL };
double **pQdfo_FREQ{ NULL };
double *pQdflat{ NULL };
double **pQdflat_FREQ{ NULL };
double *pQdflatE{ NULL };
double **pQdflatE_FREQ{ NULL };
double *pSol{ NULL };
double **pSol_FREQ{ NULL };
double *pCosxs{ NULL };
double **pCosxs_FREQ{ NULL };
double *pCosxs0{ NULL };
double **pCosxs0_FREQ{ NULL };

// declared parameters
const double *hru_lat{ NULL };
const double *hru_elev{ NULL };
const double *hru_GSL{ NULL };
const double *hru_ASL{ NULL };
const double *Time_Offset{ NULL };

//const long  *Extra;

// variable inputs

void air_mass (const double czen, double &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};