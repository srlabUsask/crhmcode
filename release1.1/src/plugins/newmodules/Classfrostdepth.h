//created by Manishankar Mondal

#include "ClassModule.h"

class Classfrostdepth : public ClassModule {
public:

Classfrostdepth(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                        k_lay(NULL),
                                        L_lay(NULL),
                                        c_lay(NULL),
                                        Lacc(NULL),
                                        Cacc(NULL),
                                        Kacc(NULL) {};
// declared variables
float *Findex;   // freezing index (days * frost °C)
long *Tfreeze;   // duration of freezing period in days
float *frostdepth;

// declared parameters
const float *Ta;        // mean annual air temperature
const float *d;         // depth of layer  m
const float **d_lay;    // depth of layer  m
const float *por;       // porosity m3/m3
const float **por_lay;  // porosity m3/m3
const float *theta;       // theta m3/m3  theta/porosity
const float **theta_lay;  // theta m3/m3
const long  *soil_type;
const long  **soil_type_lay;
const float *hru_lat;

// variable inputs
const float *hru_tmean;  // daily average temperature (°C)
const float *SWE;
const float *snowdepth;

// local allocated arrays
float **k_lay;    // J/(m.K.s)
float **L_lay;    // MJ/m3
float **c_lay;    // MJ/(m3 K)
float *Lacc; // effective value
float *Cacc; // effective value
float *Kacc; // effective value

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrostdepth* klone(string name) const;
};