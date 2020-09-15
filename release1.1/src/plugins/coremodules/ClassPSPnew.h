//created by Manishankar Mondal

#include "ClassModule.h"

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
const double *TsnowG;
const double *Lnot;

// declared variables
double *Qsubl;
double *Load;
double *Thru;
double *TCanSnow;
double *Tbiomass;

// declared parameters
const double *Sbar;
const double *LAI;
const double *Zcan;
const double *Zref;
const double *Ht;
const double *Biomass;
const double *k;
const double *HeightH;
const double *WidthJ;
const long *InitN;

// variable inputs
const double *RHref;
const double *Qn;
const double *QsIn;
const double *QsOut;
const double *hru_u;
const double *hru_p;
const double *TAref;
const double *SolarAng;

// local allocated arrays
double *T0CanSnow;
double *T0biomass;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};