//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt{0};

ClassObstoPar(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var{ NULL };

// declared observation variables
const double *Ht_obs{ NULL };      // interval data

// declared parameters
TStringList *obs_name{ NULL };
TStringList *par_name{ NULL };

double *Ht{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};