//created by Manishankar Mondal

#include "ClassModule.h"

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
const float *TsnowG;
const float *Lnot;

// declared variables
float *Qsubl;
float *Load;
float *Thru;
float *TCanSnow;
float *Tbiomass;

// declared parameters
const float *Sbar;
const float *LAI;
const float *Zcan;
const float *Zref;
const float *Ht;
const float *Biomass;
const float *k;
const float *HeightH;
const float *WidthJ;
const long *InitN;

// variable inputs
const float *RHref;
const float *Qn;
const float *QsIn;
const float *QsOut;
const float *hru_u;
const float *hru_p;
const float *TAref;
const float *SolarAng;

// local allocated arrays
float *T0CanSnow;
float *T0biomass;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};