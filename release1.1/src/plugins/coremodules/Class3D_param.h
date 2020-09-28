//created by Manishankar Mondal

#include "ClassModule.h"

class Class3D_param : public ClassModule {
public:

Class3D_param(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double* Var_3D {NULL};

// declared parameters
const double* Param_3D {NULL};

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Class3D_param* klone(string name) const;
};