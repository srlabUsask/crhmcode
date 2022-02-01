//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt{0};

ClassObstoPar(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var{ NULL };

// declared observation variables
const double *Ht_obs{ NULL };      // interval data

// declared parameters
std::vector<std::string> * obs_name{ NULL };
std::vector<std::string> * par_name{ NULL };

double *Ht{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};
