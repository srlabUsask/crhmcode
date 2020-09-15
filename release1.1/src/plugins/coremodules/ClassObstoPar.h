//created by Manishankar Mondal

#include "ClassModule.h"

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt;

ClassObstoPar(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Ht_var;

// declared observation variables
const float *Ht_obs;      // interval data

// declared parameters
TStringList *obs_name;
TStringList *par_name;

float *Ht;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};