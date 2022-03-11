//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Crop_Ht{ NULL };

// declared parameters
const double *Ht{ NULL };
const double *Crop_Grow_Rate{ NULL };
const double *JCrop_Start{ NULL };
const double *JCrop_Mature{ NULL };
const double *JCrop_Harvest{ NULL };
const double *Init_Crop_Ht{ NULL };

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};