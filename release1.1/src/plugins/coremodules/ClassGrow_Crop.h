//created by Manishankar Mondal

#include "ClassModule.h"

class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
float *Crop_Ht;

// declared parameters
const float *Ht;
const float *Crop_Grow_Rate;
const float *JCrop_Start;
const float *JCrop_Mature;
const float *JCrop_Harvest;
const float *Init_Crop_Ht;

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};