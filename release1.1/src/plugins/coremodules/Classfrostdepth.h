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
double *Findex;   // freezing index (days * frost °C)
long *Tfreeze;   // duration of freezing period in days
double *frostdepth;

// declared parameters
const double *Ta;        // mean annual air temperature
const double *d;         // depth of layer  m
const double **d_lay;    // depth of layer  m
const double *por;       // porosity m3/m3
const double **por_lay;  // porosity m3/m3
const double *theta;       // theta m3/m3  theta/porosity
const double **theta_lay;  // theta m3/m3
const long  *soil_type;
const long  **soil_type_lay;
const double *hru_lat;

// variable inputs
const double *hru_tmean;  // daily average temperature (°C)
const double *SWE;
const double *snowdepth;

// local allocated arrays
double **k_lay;    // J/(m.K.s)
double **L_lay;    // MJ/m3
double **c_lay;    // MJ/(m3 K)
double *Lacc; // effective value
double *Cacc; // effective value
double *Kacc; // effective value

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrostdepth* klone(string name) const;
};