//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
const double *TsnowG{ NULL };
const double *Lnot{ NULL };

// declared variables
double *Qsubl{ NULL };
double *Load{ NULL };
double *Thru{ NULL };
double *TCanSnow{ NULL };
double *Tbiomass{ NULL };

// declared parameters
const double *Sbar{ NULL };
const double *LAI{ NULL };
const double *Zcan{ NULL };
const double *Zref{ NULL };
const double *Ht{ NULL };
const double *Biomass{ NULL };
const double *k{ NULL };
const double *HeightH{ NULL };
const double *WidthJ{ NULL };
const long *InitN{ NULL };

// variable inputs
const double *RHref{ NULL };
const double *Qn{ NULL };
const double *QsIn{ NULL };
const double *QsOut{ NULL };
const double *hru_u{ NULL };
const double *hru_p{ NULL };
const double *TAref{ NULL };
const double *SolarAng{ NULL };

// local allocated arrays
double *T0CanSnow{ NULL };
double *T0biomass{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};