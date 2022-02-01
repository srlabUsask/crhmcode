//created by Manishankar Mondal

#include "../core/ClassModule.h"

class ClassHtobs : public ClassModule {
public:

ClassHtobs(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var{ NULL };

// declared observation variables
const double *Ht_obs{ NULL };      // interval data

// declared parameters
//const double *Ht;
double *Ht{ NULL };

void decl(void);
void init(void);
void run(void);

ClassHtobs* klone(string name) const;
};
