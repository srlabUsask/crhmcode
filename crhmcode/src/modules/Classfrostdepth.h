//created by Manishankar Mondal

#include "../core/ClassModule.h"

class Classfrostdepth : public ClassModule {
public:

Classfrostdepth(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                        k_lay(NULL),
                                        L_lay(NULL),
                                        c_lay(NULL),
                                        Lacc(NULL),
                                        Cacc(NULL),
                                        Kacc(NULL) {};
// declared variables
double *Findex { NULL };   // freezing index (days * frost DEGREE_CELSIUS)
long *Tfreeze { NULL };   // duration of freezing period in days
double *frostdepth { NULL };

// declared parameters
const double *Ta { NULL };        // mean annual air temperature
const double *d { NULL };         // depth of layer  m
const double **d_lay { NULL };    // depth of layer  m
const double *por { NULL };       // porosity m3/m3
const double **por_lay { NULL };  // porosity m3/m3
const double *theta { NULL };       // theta m3/m3  theta/porosity
const double **theta_lay { NULL };  // theta m3/m3
const long  *soil_type { NULL };
const long  **soil_type_lay { NULL };
const double *hru_lat { NULL };

// variable inputs
const double *hru_tmean { NULL };  // daily average temperature (DEGREE_CELSIUS)
const double *SWE { NULL };
const double *snowdepth { NULL };

// local allocated arrays
double **k_lay { NULL };    // J/(m.K.s)
double **L_lay { NULL };    // MJ/m3
double **c_lay { NULL };    // MJ/(m3 K)
double *Lacc { NULL }; // effective value
double *Cacc { NULL }; // effective value
double *Kacc { NULL }; // effective value

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrostdepth* klone(string name) const;
};
