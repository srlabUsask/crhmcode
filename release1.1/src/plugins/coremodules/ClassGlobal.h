//created by Manishankar Mondal

#include "ClassModule.h"



class Classglobal : public ClassModule {
public:

Classglobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QdroD;
double *QdroDext;
double *QdfoD;
double *Qdro;
double *Qdfo;
double *Qdflat;
double *QdflatD;
double *QdflatE;
double *SolAng;
double *SunMax;
double *cosxs;
double *cosxsflat;
double *pQdro;
double **pQdro_FREQ;
double *pQdfo;
double **pQdfo_FREQ;
double *pQdflat;
double **pQdflat_FREQ;
double *pQdflatE;
double **pQdflatE_FREQ;
double *pSol;
double **pSol_FREQ;
double *pCosxs;
double **pCosxs_FREQ;
double *pCosxs0;
double **pCosxs0_FREQ;

// declared parameters
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;
const double *Time_Offset;

//const long  *Extra;

// variable inputs

void air_mass (const double czen, double &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};