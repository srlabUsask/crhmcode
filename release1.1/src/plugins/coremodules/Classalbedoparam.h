//created by Manishankar Mondal

#include "ClassModule.h"

class Classalbedoparam : public ClassModule {
public:

Classalbedoparam(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Albedo;

// declared parameters
const float *Albedo_Value;

void decl(void);
void init(void);
void run(void);

Classalbedoparam* klone(string name) const;
};