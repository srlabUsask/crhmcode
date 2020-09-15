//created by Manishankar Mondal

#include "ClassModule.h"

class Classqmelt : public ClassModule {
public:

Classqmelt(string Name = "Qmelt", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
double *Qm;      // MJ/m2/Int
double *Qg;      // MJ/m2/Int
double *cum_Qm;  // MJ/m2
double *cum_Qg;  // MJ/m2
double *QmD;     // MJ/m2
double *QgD;     // MJ/m2

// declared parameters
const double *TIa0Mn;
const double *TIa1Mn;
const double *TIs0Mn;
const double *TIs1Mn;

// declared observations
const double *t;      // °C
const double *ts;     // °C
double *tmean;  // °C
double *tpos;   // °C
double *tsmean; // °C
double *tspos;  // °C

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};