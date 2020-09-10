//created by Manishankar Mondal

#include "ClassModule.h"

class Classquinton : public ClassModule {
public:

Classquinton(string Name = "Quinton", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

ClassClark *Delayrunoff;
ClassClark *Delayflow;

// declared observation variables
const float *p;

// input variables
const float *Qg;        // MJ/m2
const float *driftmelt; // melt depth from upstream drift
const float *hru_p;

// declared parameters
const long *Type;           // NOTUSED, DRIFT or HUMMOCK
//const long *k_range;        // normal, high or low
const long *DrainTo;        // drain to HRU
const float *slope;         // (m/m)
const float *length;        // length normal to creek
const float *Kbtm;         // bottom hydraulic conductivity (m/d)
const float *Ktop;         // bottom hydraulic conductivity (m/d)
const float *ztrn;         // transition depth (m)
const float *Residual;      // Organic non-drainable porosity ()
const float **Residual_lay; // Organic non-drainable porosity ()
const float *n_const;       // Van Genutchen constant
const float **n_const_lay;  // Van Genutchen constant
const float *a_const;       // Van Genutchen constant
const float **a_const_lay;  // Van Genutchen constant
const float *Drained;       // depth of surface drained organic material (m)
const float *FrozenTo;      // initial depth of frost table (m)
const float *runoffstorage; // runoff parameter ()
const float *runoffLag;     // runoff parameter ()
const float *flowstorage;   // flow parameter ()
const float *flowLag;       // flow parameter ()

const float *d;             // depth of layer  (m)
const float **d_lay;        // depth of layer  (m)
const float *Pors;          // filler only gives first value
const float **Pors_def;     // array of all values
const long  *soil_type;
const long  **soil_type_lay;
const float *tinit;         // initial layer temperature (°C)
const float **tinit_lay;    // initial layer temperature (°C)

// declared variables
float *Depth;          // hydraulic conductivity (m/day)
float *k;              // hydraulic conductivity (m/day)
float *d_surface;      // debug
float *watertable;     // water table depth (m)
float *dmelt;          // melt depth (m)
float *flowin;         // flowin depth (m/m2)
float *flowinm3;       // flowin depth (m3)
float *cumflowin;      // cumulative flowin depth (m)
float *runoff;         // runoff ((m/m2)/int)
float *runoffDly;      // runoff ((m/m2)/int)
float *runoffm3Dly;    // runoff (m3/int)
float *cumrunoff;      // cumulative runoff (m)
float *flow;           // total flow (m/int)
float *flowDly;        // total flow (m/int)
float *flowm3Dly;      // total flow (m3/int)
float *cumflow;        // cumulative total flow from all layers(m3/s)
float *loss;           // total loss (m/int)
float *transit;        // transit time through HRU (hr)
float *theta;          // soil moisture (m3/m3)
float **theta_lay;     // soil moisture (m3/m3)
float *layerwater;      // thawed water depth in layer (m)
float **layerwater_lay; // thawed water depth in layer (m)
float *capillary;      // locked thawed water depth in layer (m)
float **capillary_lay; // locked thawed water depth in layer (m)
float *tension;        // capillary tension (m)
float **tension_lay;   // capillary tension (m)
float *wDrained;       // working depth of surface drained organic material (m)

float *Cvis;         // frozen/saturated
float **Cvis_lay;    // heat capacity (J/m3/K)

float *Cvisa;       // frozen/unsaturated
float **Cvisa_lay;  // heat capacity (J/m3/K)

float *Cvws;        // unfrozen/saturated
float **Cvws_lay;   // heat capacity (J/m3/K)

float *Cvwsa;       // unfrozen/unsaturated
float **Cvwsa_lay;  // heat capacity (J/m3/K)

float *lamis;       // frozen/saturated
float **lamis_lay;  // thermal conductivity (W/m/K)

float *lamws;       // unfrozen/saturated
float **lamws_lay;  // thermal conductivity (W/m/K)

float *lamwsa;      // unfrozen/unsaturated
float **lamwsa_lay; // thermal conductivity (W/m/K)

float *tlayer;         // layer temperature (°C)
float **tlayer_lay;    // layer temperature (°C)

// local constants

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classquinton* klone(string name) const;
};