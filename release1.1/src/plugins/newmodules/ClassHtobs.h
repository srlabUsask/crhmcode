//created by Manishankar Mondal

#include "ClassModule.h"

class ClassHtobs : public ClassModule {
public:

ClassHtobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Ht_var;

// declared observation variables
const float *Ht_obs;      // interval data

// declared parameters
//const float *Ht;
float *Ht;

void decl(void);
void init(void);
void run(void);

ClassHtobs* klone(string name) const;
};