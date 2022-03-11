//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassHMSA : public ClassModule {
public:

ClassHMSA(string Name = "HMSA", string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " hru_t, "){};

double Soil_Temp{0.0};

long MaxFrontCnt{0};
long Liqcnt{0};
long Totcnt{0};

// declared observation variables
const double *Tsurf_obs{ NULL };
const double *LiqWat{ NULL };
const double *TotMoist{ NULL };

// variable inputs
const double *Tsurf_var{ NULL };
const double *hru_t{ NULL };

//const double *theta;

// declared variables
double *Cum_Thaw{ NULL };
double *Cum_Frozen{ NULL };
double *Lamda_b{ NULL };
double *Frozen_D{ NULL };
double *Thaw_D{ NULL };
double *Last_Tsurf{ NULL };

double *C_K0{ NULL };
double *Total_Moisture{ NULL };
double **Total_Moisture_lay{ NULL };
double *Cum_d{ NULL };
double **Cum_d_lay{ NULL };
long *Frozen_ID{ NULL };
long **Frozen_ID_lay{ NULL };
double *FrntDepth{ NULL };
double **FrntDepth_array{ NULL };
double *ThawCum{ NULL };
double **ThawCum_array{ NULL };
double *FreezeCum{ NULL };
double **FreezeCum_array{ NULL };
long *FrntDepthType{ NULL };
long **FrntDepthType_array{ NULL };
long *FrontCnt{ NULL };

// local
double *Tsurface{ NULL };

// declared parameters
const double *Alpha_T{ NULL };
const double *Alpha_F{ NULL };
const double *d_lay{ NULL };
const double *BulkDensityLayer{ NULL };
const double *InitThaw_D{ NULL };
const double *InitFrozen_D{ NULL };
const double *D_Top{ NULL };
const double *TMPB_W{ NULL };
const double **TMPB_W_NDEF{ NULL };
const long *Alpha_ID{ NULL };
const long *Soil_ID{ NULL };
const long **Soil_ID_lay{ NULL };

const double *Soil_Depths{ NULL };
const double **Soil_depths_lay{ NULL }; // [nn][hh]
const double *Organic{ NULL };
const double **Organic_lay{ NULL }; // [nn][hh]
const double *Porosity{ NULL };
const double **Porosity_lay{ NULL }; // [nn][hh
const double *BulkDensity{ NULL };
const double **BulkDensity_lay{ NULL }; // [nn][hh]
double *f{ NULL };
double *Soil_Ice{ NULL };
double **Soil_Ice_lay{ NULL };
double *Soil_Water{ NULL };
double **Soil_Water_lay{ NULL };

const long *Soil_Layers{ NULL };
const long *Method_ID{ NULL };

void decl(void);
void init(void);
void run(void);
void Get_Heat_Param_Soil(double Soil_temp, long nn);
void Get_Heat_Chad(long nn);

ClassHMSA* klone(string name) const;
};