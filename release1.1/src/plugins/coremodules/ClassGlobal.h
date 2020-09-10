//created by Manishankar Mondal

#include "ClassModule.h"



class Classglobal : public ClassModule {
public:

Classglobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *QdroD;
float *QdroDext;
float *QdfoD;
float *Qdro;
float *Qdfo;
float *Qdflat;
float *QdflatD;
float *QdflatE;
float *SolAng;
float *SunMax;
float *cosxs;
float *cosxsflat;
float *pQdro;
float **pQdro_FREQ;
float *pQdfo;
float **pQdfo_FREQ;
float *pQdflat;
float **pQdflat_FREQ;
float *pQdflatE;
float **pQdflatE_FREQ;
float *pSol;
float **pSol_FREQ;
float *pCosxs;
float **pCosxs_FREQ;
float *pCosxs0;
float **pCosxs0_FREQ;

// declared parameters
const float *hru_lat;
const float *hru_elev;
const float *hru_GSL;
const float *hru_ASL;
const float *Time_Offset;

//const long  *Extra;

// variable inputs

void air_mass (const float czen, float &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};