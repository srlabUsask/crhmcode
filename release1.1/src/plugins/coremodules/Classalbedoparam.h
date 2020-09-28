//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedoparam : public ClassModule {
public:

Classalbedoparam(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo { NULL };

// declared parameters
const double *Albedo_Value { NULL };

void decl(void);
void init(void);
void run(void);

Classalbedoparam* klone(string name) const;
};