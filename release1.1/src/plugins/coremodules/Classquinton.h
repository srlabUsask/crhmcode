//created by Manishankar Mondal

#include "ClassModule.h"

class Classquinton : public ClassModule {
public:

Classquinton(string Name = "Quinton", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

ClassClark *Delayrunoff;
ClassClark *Delayflow;

// declared observation variables
const double *p;

// input variables
const double *Qg;        // MJ/m2
const double *driftmelt; // melt depth from upstream drift
const double *hru_p;

// declared parameters
const long *Type;           // NOTUSED, DRIFT or HUMMOCK
//const long *k_range;        // normal, high or low
const long *DrainTo;        // drain to HRU
const double *slope;         // (m/m)
const double *length;        // length normal to creek
const double *Kbtm;         // bottom hydraulic conductivity (m/d)
const double *Ktop;         // bottom hydraulic conductivity (m/d)
const double *ztrn;         // transition depth (m)
const double *Residual;      // Organic non-drainable porosity ()
const double **Residual_lay; // Organic non-drainable porosity ()
const double *n_const;       // Van Genutchen constant
const double **n_const_lay;  // Van Genutchen constant
const double *a_const;       // Van Genutchen constant
const double **a_const_lay;  // Van Genutchen constant
const double *Drained;       // depth of surface drained organic material (m)
const double *FrozenTo;      // initial depth of frost table (m)
const double *runoffstorage; // runoff parameter ()
const double *runoffLag;     // runoff parameter ()
const double *flowstorage;   // flow parameter ()
const double *flowLag;       // flow parameter ()

const double *d;             // depth of layer  (m)
const double **d_lay;        // depth of layer  (m)
const double *Pors;          // filler only gives first value
const double **Pors_def;     // array of all values
const long  *soil_type;
const long  **soil_type_lay;
const double *tinit;         // initial layer temperature (°C)
const double **tinit_lay;    // initial layer temperature (°C)

// declared variables
double *Depth;          // hydraulic conductivity (m/day)
double *k;              // hydraulic conductivity (m/day)
double *d_surface;      // debug
double *watertable;     // water table depth (m)
double *dmelt;          // melt depth (m)
double *flowin;         // flowin depth (m/m2)
double *flowinm3;       // flowin depth (m3)
double *cumflowin;      // cumulative flowin depth (m)
double *runoff;         // runoff ((m/m2)/int)
double *runoffDly;      // runoff ((m/m2)/int)
double *runoffm3Dly;    // runoff (m3/int)
double *cumrunoff;      // cumulative runoff (m)
double *flow;           // total flow (m/int)
double *flowDly;        // total flow (m/int)
double *flowm3Dly;      // total flow (m3/int)
double *cumflow;        // cumulative total flow from all layers(m3/s)
double *loss;           // total loss (m/int)
double *transit;        // transit time through HRU (hr)
double *theta;          // soil moisture (m3/m3)
double **theta_lay;     // soil moisture (m3/m3)
double *layerwater;      // thawed water depth in layer (m)
double **layerwater_lay; // thawed water depth in layer (m)
double *capillary;      // locked thawed water depth in layer (m)
double **capillary_lay; // locked thawed water depth in layer (m)
double *tension;        // capillary tension (m)
double **tension_lay;   // capillary tension (m)
double *wDrained;       // working depth of surface drained organic material (m)

double *Cvis;         // frozen/saturated
double **Cvis_lay;    // heat capacity (J/m3/K)

double *Cvisa;       // frozen/unsaturated
double **Cvisa_lay;  // heat capacity (J/m3/K)

double *Cvws;        // unfrozen/saturated
double **Cvws_lay;   // heat capacity (J/m3/K)

double *Cvwsa;       // unfrozen/unsaturated
double **Cvwsa_lay;  // heat capacity (J/m3/K)

double *lamis;       // frozen/saturated
double **lamis_lay;  // thermal conductivity (W/m/K)

double *lamws;       // unfrozen/saturated
double **lamws_lay;  // thermal conductivity (W/m/K)

double *lamwsa;      // unfrozen/unsaturated
double **lamwsa_lay; // thermal conductivity (W/m/K)

double *tlayer;         // layer temperature (°C)
double **tlayer_lay;    // layer temperature (°C)

// local constants

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classquinton* klone(string name) const;
};