//created by Manishankar Mondal

#include "ClassModule.h"

class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Crop_Ht;

// declared parameters
const double *Ht;
const double *Crop_Grow_Rate;
const double *JCrop_Start;
const double *JCrop_Mature;
const double *JCrop_Harvest;
const double *Init_Crop_Ht;

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};