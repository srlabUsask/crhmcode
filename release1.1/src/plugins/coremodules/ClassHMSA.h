//created by Manishankar Mondal

#include "ClassModule.h"

class ClassHMSA : public ClassModule {
public:

ClassHMSA(string Name = "HMSA", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " hru_t, "){};

float Soil_Temp;

long MaxFrontCnt;
long Liqcnt;
long Totcnt;

// declared observation variables
const float *Tsurf_obs;
const float *LiqWat;
const float *TotMoist;

// variable inputs
const float *Tsurf_var;
const float *hru_t;

//const float *theta;

// declared variables
float *Cum_Thaw;
float *Cum_Frozen;
float *Lamda_b;
float *Frozen_D;
float *Thaw_D;
float *Last_Tsurf;

float *C_K0;
float *Total_Moisture;
float **Total_Moisture_lay;
float *Cum_d;
float **Cum_d_lay;
long *Frozen_ID;
long **Frozen_ID_lay;
float *FrntDepth;
float **FrntDepth_array;
float *ThawCum;
float **ThawCum_array;
float *FreezeCum;
float **FreezeCum_array;
long *FrntDepthType;
long **FrntDepthType_array;
long *FrontCnt;

// local
float *Tsurface;

// declared parameters
const float *Alpha_T;
const float *Alpha_F;
const float *d_lay;
const float *BulkDensityLayer;
const float *InitThaw_D;
const float *InitFrozen_D;
const float *D_Top;
const float *TMPB_W;
const float **TMPB_W_NDEF;
const long *Alpha_ID;
const long *Soil_ID;
const long **Soil_ID_lay;

const float *Soil_Depths;
const float **Soil_depths_lay; // [nn][hh]
const float *Organic;
const float **Organic_lay; // [nn][hh]
const float *Porosity;
const float **Porosity_lay; // [nn][hh
const float *BulkDensity;
const float **BulkDensity_lay; // [nn][hh]
float *f;
float *Soil_Ice;
float **Soil_Ice_lay;
float *Soil_Water;
float **Soil_Water_lay;

const long *Soil_Layers;
const long *Method_ID;

void decl(void);
void init(void);
void run(void);
void Get_Heat_Param_Soil(float Soil_temp, long nn);
void Get_Heat_Chad(long nn);

ClassHMSA* klone(string name) const;
};