//created by Manishankar Mondal

#include "ClassModule.h"

class Classshared : public ClassModule {
public:

Classshared(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);

Classshared* klone(string name) const;
};