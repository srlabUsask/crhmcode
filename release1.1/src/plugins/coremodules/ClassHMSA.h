//created by Manishankar Mondal

#include "ClassModule.h"

class ClassHMSA : public ClassModule {
public:

ClassHMSA(string Name = "HMSA", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " hru_t, "){};

double Soil_Temp;

long MaxFrontCnt;
long Liqcnt;
long Totcnt;

// declared observation variables
const double *Tsurf_obs;
const double *LiqWat;
const double *TotMoist;

// variable inputs
const double *Tsurf_var;
const double *hru_t;

//const double *theta;

// declared variables
double *Cum_Thaw;
double *Cum_Frozen;
double *Lamda_b;
double *Frozen_D;
double *Thaw_D;
double *Last_Tsurf;

double *C_K0;
double *Total_Moisture;
double **Total_Moisture_lay;
double *Cum_d;
double **Cum_d_lay;
long *Frozen_ID;
long **Frozen_ID_lay;
double *FrntDepth;
double **FrntDepth_array;
double *ThawCum;
double **ThawCum_array;
double *FreezeCum;
double **FreezeCum_array;
long *FrntDepthType;
long **FrntDepthType_array;
long *FrontCnt;

// local
double *Tsurface;

// declared parameters
const double *Alpha_T;
const double *Alpha_F;
const double *d_lay;
const double *BulkDensityLayer;
const double *InitThaw_D;
const double *InitFrozen_D;
const double *D_Top;
const double *TMPB_W;
const double **TMPB_W_NDEF;
const long *Alpha_ID;
const long *Soil_ID;
const long **Soil_ID_lay;

const double *Soil_Depths;
const double **Soil_depths_lay; // [nn][hh]
const double *Organic;
const double **Organic_lay; // [nn][hh]
const double *Porosity;
const double **Porosity_lay; // [nn][hh
const double *BulkDensity;
const double **BulkDensity_lay; // [nn][hh]
double *f;
double *Soil_Ice;
double **Soil_Ice_lay;
double *Soil_Water;
double **Soil_Water_lay;

const long *Soil_Layers;
const long *Method_ID;

void decl(void);
void init(void);
void run(void);
void Get_Heat_Param_Soil(double Soil_temp, long nn);
void Get_Heat_Chad(long nn);

ClassHMSA* klone(string name) const;
};