//created by Manishankar Mondal

#include "ClassModule.h"


class Classalbedoobs : public ClassModule {
public:

Classalbedoobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo { NULL };

// declared observation variables
const double *Albedo_obs { NULL };      // interval data

// declared parameters
const double *Albedo_Value { NULL };

void decl(void);
void init(void);
void run(void);

Classalbedoobs* klone(string name) const;
};