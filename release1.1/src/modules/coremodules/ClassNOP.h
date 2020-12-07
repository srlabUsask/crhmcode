//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassNOP : public ClassModule {
public:

ClassNOP(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);
void finish(bool good);

ClassNOP* klone(string name) const;
};