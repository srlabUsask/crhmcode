//created by Manishankar Mondal

#include "ClassModule.h"


class Classalbedoobs : public ClassModule {
public:

Classalbedoobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Albedo;

// declared observation variables
const float *Albedo_obs;      // interval data

// declared parameters
const float *Albedo_Value;

void decl(void);
void init(void);
void run(void);

Classalbedoobs* klone(string name) const;
};