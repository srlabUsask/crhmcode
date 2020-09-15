//created by Manishankar Mondal

#include "ClassModule.h"

class Classqmelt : public ClassModule {
public:

Classqmelt(string Name = "Qmelt", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
float *Qm;      // MJ/m2/Int
float *Qg;      // MJ/m2/Int
float *cum_Qm;  // MJ/m2
float *cum_Qg;  // MJ/m2
float *QmD;     // MJ/m2
float *QgD;     // MJ/m2

// declared parameters
const float *TIa0Mn;
const float *TIa1Mn;
const float *TIs0Mn;
const float *TIs1Mn;

// declared observations
const float *t;      // °C
const float *ts;     // °C
float *tmean;  // °C
float *tpos;   // °C
float *tsmean; // °C
float *tspos;  // °C

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};