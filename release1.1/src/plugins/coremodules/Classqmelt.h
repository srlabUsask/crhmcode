//created by Manishankar Mondal

#include "ClassModule.h"

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
const double *t{ NULL };      // °C
const double *ts{ NULL };     // °C
double *tmean{ NULL };  // °C
double *tpos{ NULL };   // °C
double *tsmean{ NULL }; // °C
double *tspos{ NULL };  // °C

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};