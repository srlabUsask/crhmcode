/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include "../core/ClassModule.h"

class Classquinton : public ClassModule {
public:

Classquinton(string Name = "Quinton", string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl){};

ClassClark *Delayrunoff{ NULL };
ClassClark *Delayflow{ NULL };

// declared observation variables
const double *p{ NULL };

// input variables
const double *Qg{ NULL };        // MJ/m2
const double *driftmelt{ NULL }; // melt depth from upstream drift
const double *hru_p{ NULL };

// declared parameters
const long *Type{ NULL };           // NOTUSED, DRIFT or HUMMOCK
//const long *k_range;        // normal, high or low
const long *DrainTo{ NULL };        // drain to HRU
const double *slope{ NULL };         // (m/m)
const double *length{ NULL };        // length normal to creek
const double *Kbtm{ NULL };         // bottom hydraulic conductivity (m/d)
const double *Ktop{ NULL };         // bottom hydraulic conductivity (m/d)
const double *ztrn{ NULL };         // transition depth (m)
const double *Residual{ NULL };      // Organic non-drainable porosity ()
const double **Residual_lay{ NULL }; // Organic non-drainable porosity ()
const double *n_const{ NULL };       // Van Genutchen constant
const double **n_const_lay{ NULL };  // Van Genutchen constant
const double *a_const{ NULL };       // Van Genutchen constant
const double **a_const_lay{ NULL };  // Van Genutchen constant
const double *Drained{ NULL };       // depth of surface drained organic material (m)
const double *FrozenTo{ NULL };      // initial depth of frost table (m)
const double *runoffstorage{ NULL }; // runoff parameter ()
const double *runoffLag{ NULL };     // runoff parameter ()
const double *flowstorage{ NULL };   // flow parameter ()
const double *flowLag{ NULL };       // flow parameter ()

const double *d{ NULL };             // depth of layer  (m)
const double **d_lay{ NULL };        // depth of layer  (m)
const double *Pors{ NULL };          // filler only gives first value
const double **Pors_def{ NULL };     // array of all values
const long  *soil_type{ NULL };
const long  **soil_type_lay{ NULL };
const double *tinit{ NULL };         // initial layer temperature (DEGREE_CELSIUS)
const double **tinit_lay{ NULL };    // initial layer temperature (DEGREE_CELSIUS)

// declared variables
double *Depth{ NULL };          // hydraulic conductivity (m/day)
double *k{ NULL };              // hydraulic conductivity (m/day)
double *d_surface{ NULL };      // debug
double *watertable{ NULL };     // water table depth (m)
double *dmelt{ NULL };          // melt depth (m)
double *flowin{ NULL };         // flowin depth (m/m2)
double *flowinm3{ NULL };       // flowin depth (m3)
double *cumflowin{ NULL };      // cumulative flowin depth (m)
double *runoff{ NULL };         // runoff ((m/m2)/int)
double *runoffDly{ NULL };      // runoff ((m/m2)/int)
double *runoffm3Dly{ NULL };    // runoff (m3/int)
double *cumrunoff{ NULL };      // cumulative runoff (m)
double *flow{ NULL };           // total flow (m/int)
double *flowDly{ NULL };        // total flow (m/int)
double *flowm3Dly{ NULL };      // total flow (m3/int)
double *cumflow{ NULL };        // cumulative total flow from all layers(m3/s)
double *loss{ NULL };           // total loss (m/int)
double *transit{ NULL };        // transit time through HRU (hr)
double *theta{ NULL };          // soil moisture (m3/m3)
double **theta_lay{ NULL };     // soil moisture (m3/m3)
double *layerwater{ NULL };      // thawed water depth in layer (m)
double **layerwater_lay{ NULL }; // thawed water depth in layer (m)
double *capillary{ NULL };      // locked thawed water depth in layer (m)
double **capillary_lay{ NULL }; // locked thawed water depth in layer (m)
double *tension{ NULL };        // capillary tension (m)
double **tension_lay{ NULL };   // capillary tension (m)
double *wDrained{ NULL };       // working depth of surface drained organic material (m)

double *Cvis{ NULL };         // frozen/saturated
double **Cvis_lay{ NULL };    // heat capacity (J/m3/K)

double *Cvisa{ NULL };       // frozen/unsaturated
double **Cvisa_lay{ NULL };  // heat capacity (J/m3/K)

double *Cvws{ NULL };        // unfrozen/saturated
double **Cvws_lay{ NULL };   // heat capacity (J/m3/K)

double *Cvwsa{ NULL };       // unfrozen/unsaturated
double **Cvwsa_lay{ NULL };  // heat capacity (J/m3/K)

double *lamis{ NULL };       // frozen/saturated
double **lamis_lay{ NULL };  // thermal conductivity (W/m/K)

double *lamws{ NULL };       // unfrozen/saturated
double **lamws_lay{ NULL };  // thermal conductivity (W/m/K)

double *lamwsa{ NULL };      // unfrozen/unsaturated
double **lamwsa_lay{ NULL }; // thermal conductivity (W/m/K)

double *tlayer{ NULL };         // layer temperature (DEGREE_CELSIUS)
double **tlayer_lay{ NULL };    // layer temperature (DEGREE_CELSIUS)

// local constants

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classquinton* klone(string name) const;
};
