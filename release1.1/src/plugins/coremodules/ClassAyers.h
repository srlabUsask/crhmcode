//created by Manishankar Mondal

#include "ClassModule.h"

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *infil;
float *cuminfil;
float *runoff;
float *cumrunoff;
float *snowinfil;
float *cumsnowinfil;
float *meltrunoff;
float *cummeltrunoff;
float *melt_int; // interval melt - from snowmelD

// declared parameters
const float *basin_area; // [BASIN]
const float *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const float *net_rain;
const float *snowmeltD;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};