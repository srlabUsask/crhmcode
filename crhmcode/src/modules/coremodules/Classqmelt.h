//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class Classqmelt : public ClassModule {
public:

Classqmelt(string Name = "Qmelt", string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
double *Qm{ NULL };      // MJ/m2/Int
double *Qg{ NULL };      // MJ/m2/Int
double *cum_Qm{ NULL };  // MJ/m2
double *cum_Qg{ NULL };  // MJ/m2
double *QmD{ NULL };     // MJ/m2
double *QgD{ NULL };     // MJ/m2

// declared parameters
const double *TIa0Mn{ NULL };
const double *TIa1Mn{ NULL };
const double *TIs0Mn{ NULL };
const double *TIs1Mn{ NULL };

// declared observations
const double *t{ NULL };      // DEGREE_CELSIUS
const double *ts{ NULL };     // DEGREE_CELSIUS
double *tmean{ NULL };  // DEGREE_CELSIUS
double *tpos{ NULL };   // DEGREE_CELSIUS
double *tsmean{ NULL }; // DEGREE_CELSIUS
double *tspos{ NULL };  // DEGREE_CELSIUS

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};