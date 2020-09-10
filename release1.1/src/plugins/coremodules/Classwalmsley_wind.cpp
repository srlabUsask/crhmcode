//created by Manishankar Mondal

#include "Classwalmsley_wind.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

Classwalmsley_wind* Classwalmsley_wind::klone(string name) const{
  return new Classwalmsley_wind(name);
}

void Classwalmsley_wind::decl(void) {

  Description = "'A parametric version of the wind flow model (Mason and Sykes (1979)).'";

  declvar("hru_Uadjust", NHRU, "adjusted wind speed due to topography", "(m/s)", &hru_Uadjust);

  declvar("hru_Uchange", NHRU, "amount of change in wind speed due to topography", "(m/s)", &hru_Uchange);

  decldiag("WR", NHRU, "wind ratio between adjusted wind speed and reference wind speed", "()", &WR);

  declparam("Zwind", NHRU, "[10.0]", "0.0", "100.0", "wind instrument height", "(m)", &Zwind);

  declparam("A", NHRU, "0.0", "0.0", "4.4", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 2.5 = 2D escarpments, 3.0 = 2D hills, 3.5 = 2D rolling terrain, 4.0 = 3D hills, 4.4 = 3D rolling terrain",
            "()", &Ax);

  declparam("B", NHRU, "0.0", "0.0", "2.0", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 0.8 = 2D escarpments, 1.1 = 3D rolling terrain, 1.55 = 2D rolling terrain, 1.6 = 3D hills, 2.0 = 2D hills",
            "()", &Bx);

  declparam("L", NHRU, "[1000.0]", "40.0", "1.0E6f", "upwind length at half height", "(m)", &L);

  declparam("Walmsley_Ht", NHRU, "[0]", "-1000.0", "1000.0", "Walmsley height", "(m)", &Walmsley_Ht);

  declgetvar("*",     "hru_u", "(m/s)", &hru_u);

}

void Classwalmsley_wind::init(void) {
  nhru = getdim(NHRU);
}

void Classwalmsley_wind::run(void) {

/*Walmsley, Talor and Salmon's simple guidelines for estimating wind speed variations
due to topographic features*/

  for (int hh = 0; hh < nhru; ++hh) {
    double Smax = Bx[hh] * Walmsley_Ht[hh] / L[hh]; // maximum decay of fractional speed-up ratio
    double S = Smax * exp(-Ax[hh]*Zwind[hh]/L[hh]); // the decay of fractional speed-up ratio

    hru_Uchange[hh] = S * hru_u[hh];
    hru_Uadjust[hh] = hru_Uchange[hh] + hru_u[hh];
    WR[hh] = hru_Uadjust[hh] / hru_u[hh];
  }

}