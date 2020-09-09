//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNOP : public ClassModule {
public:

ClassNOP(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);
void finish(bool good);

ClassNOP* klone(string name) const;
};