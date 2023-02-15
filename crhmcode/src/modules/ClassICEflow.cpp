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

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassICEflow.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassICEflow* ClassICEflow::klone(string name) const{
  return new ClassICEflow(name);
}

void ClassICEflow::decl(void) {

  Description = "'Simulates ICE flow dynamic.'";

  declvar("Ice_out", TDim::NHRU, "outgoing iceflow transport", "(mm/int)", &Ice_out);

  declvar("Ice_in", TDim::NHRU, "incoming iceflow transport", "(mm/int)", &Ice_in);

  declvar("Ux", TDim::NHRU, "plastic flow due to its own weight. Can be channel flow or slab flow(shallow iceflow).", "(m)", &Ux);

  declvar("Ub", TDim::NHRU, "velocity due to basal slip", "(m)", &Ub);

  declvar("Utot", TDim::NHRU, "sum of plastic deformation and basal slip", "(m)", &Utot);

  declvar("cumulative_net_rain", TDim::NHRU, "cumulative meltwater and rain", "(m/yr)", &cumulative_net_rain);

  decldiag("cumIce_in", TDim::NHRU, "incoming cumulative Slip transport ice from other HRU", "(mm)", &cumIce_in);

  decldiag("cumIce_out", TDim::NHRU, "outgoing cumulative Slip transport ice to other HRU", "(mm)", &cumIce_out);

/* parameters */

  declparam("order", TDim::NHRU, "[1,2,3,4,5!]", "1","1000", "sequence of HRUs for iceflow distribution", "()", &order);

  declparam("Disable_ICEflow", TDim::NHRU, "[0]", "0","1", "set to 1 to disable module", "()", &Disable_ICEflow);

  declparam("distrib_iceflow", TDim::NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs", "()", &distrib, &distrib_hru, nhru);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  declparam("hru_GSL", TDim::NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);

  declparam("SWE_to_firn_Julian", TDim::NHRU, "[274]", "0", "366", "convert any SWE to firn on Julian day. 0 - inhibit transfer", "()", &SWE_to_firn_Julian);

  declparam("test_option", TDim::NHRU, "[-1]", "-1", "100", "negative - disable testing option, >= 0 sets Utot to value of test option.", "(mm)", &test_option);

  declparam("channel_option", TDim::NHRU, "[0]", "0", "1", "0 - channel flow, 1 - slab flow.", "()", &channel_option);

  declparam("basal_option", TDim::NHRU, "[1]", "1", "2", "1 - u_basal option 1, 2 - u_basal option 2", "()", &basal_option);

  declparam("radius_glacier", TDim::NHRU, "[1000]", "100", "10000", "radius of glacier", "(m)", &radius_glacier);

  declparam("Arrhenius_const", TDim::NHRU, "[2.935E-17]", "1E-30", "1E-2", "Arrhenius constant", "(1/Pa*yr)", &Arrhenius_const); // Cuffey and Paterson (2010)

  declparam("slip_sf", TDim::NHRU, "[0.5]", "0.0", "2.0", "shape factor for the shear stress in channel flow", "()", &slip_sf); // Nye J.F. (1965). The flow of a glacier in a channel of rectangular, elliptic, or parabolic cross-section. Journal of Glaciology. Vol 5, 661-690.

  declparam("slip_m", TDim::NHRU, "[3.0]", "0.0", "3.0", "exponent constant for basal slip", "()", &slip_m); // Generally 2 to 3 (Oerlemans, 2001)

  declparam("slip_c", TDim::NHRU, "[0.1]", "0.0", "1.0", "constant for physical characteristics of the bed", "()", &slip_c);

  declparam("slip_fs", TDim::NHRU, "[1.8E-12]", "1E-25", "1.0", "sliding parameter from Budd et al. (1979) for basal option 2", "(Pa^-3*m^2*yr)", &slip_fs); // fs = 5.7e-20*(365.2422*24*3600) Oerlemans J. (2001). Glaciers and Climate Change. A.A. Balkema Publishers, Lisse.


  declputvar("*", "ice", "(mm)", &ice); // water equivalent of ice
  declgetvar("*", "firn", "(mm)", &firn); // water equivalent of firn
  declgetvar("*", "net_rain", "(mm)", &net_rain); // meltwater and rain
}

void ClassICEflow::init(void) {

  nhru = getdim(TDim::NHRU);

  for (hh = 0; hh < nhru; ++hh){
    Ice_in[hh] = 0.0;
    Ice_out[hh] = 0.0;
    cumIce_in[hh] = 0.0;
    cumIce_out[hh] = 0.0;
    Ux[hh] = 0.0;
    Ub[hh] = 0.0;
    Utot[hh] = 0.0;
    cumulative_net_rain[hh] = 0.0;
  }
}

void ClassICEflow::run(void) {

  const double ice_dens = 917;
  const double g = 9.81;
  const double n_Glen = 3;  // Glen's flow parameter
  const double alpha = M_PI/180.0;  // degrees to radians
  const double water_dens = 1000;  // kg/m^3

  long nstep = getstep()% Global::Freq;

  for (long hh = 0; chkStruct(hh); ++hh)
    cumulative_net_rain[hh] += net_rain[hh]; // from glacier module. It includes melt and rain

  if(nstep == 0 || Global::Freq == 1){ // end of every day

    for (long hhh = 0; chkStruct(hhh); ++hhh) {

      hh = order[hhh] - 1; // do HRUs in the desired sequence

      if(Disable_ICEflow[hh])
        continue;

      long Julian = julian("now"); // same as "decday"
      if(SWE_to_firn_Julian[hh] == Julian){
        if(hh == 0)
          for (long mm = 0; chkStruct(mm); ++mm)
            Ice_in[mm] = 0.0;


        Ice_out[hh] = 0.0;
        Ux[hh] = 0.0;
        Ub[hh] = 0.0;
        Utot[hh] = 0.0;

        if(test_option[hh] >= 0.0) // use user value for ice flow
          Utot[hh] = test_option[hh];
        else{
          double ICE = ice[hh] + firn[hh];
          if(channel_option[hh] == 0) // channel flow
            Ux[hh] = 2*Arrhenius_const[hh]*pow(slip_sf[hh]*ice_dens*g*sin(hru_GSL[hh]*alpha), n_Glen)*pow(radius_glacier[hh], n_Glen+1)/(n_Glen+2);
          else // by default slab flow
            Ux[hh] = 2*Arrhenius_const[hh]*pow(ice_dens*g*sin(hru_GSL[hh]*alpha), n_Glen)*pow(ICE/ice_dens, n_Glen+1)/(n_Glen+2);

	        double ice_thickness = ICE/ice_dens; //ICE is in mm water equivalent, and ice_dens is in kg/m3, therefore, ice_thickness is in m
          double Iw = ice_dens*g*ice_thickness;
          double tau_b = slip_sf[hh]*ice_dens*g*ice_thickness*sin(hru_GSL[hh]*alpha);

          if(basal_option[hh] == 1){
            double Pw = water_dens*g*cumulative_net_rain[hh]/1000.0; // (mm) > (m)
            Ub[hh] = slip_c[hh]*pow(tau_b, slip_m[hh])/(Iw - Pw);
          }
          else{ // by default option 2
            Ub[hh] = slip_fs[hh]*pow(tau_b, slip_m[hh])/ice_thickness;
          }

          Utot[hh] = Ux[hh] + Ub[hh];
        }

        if(Utot[hh] > 0.0){ // distribute flow

          for(long To = 0; chkStruct(To); ++To) { // distribute ice outflow of HRU

            if(hh != To && Utot[hh] > 0.0 && distrib_hru[hh][To] > 0.0){
              double Amount = Utot[hh]*distrib_hru[hh][To];
              Ice_out[hh] = Amount;
              cumIce_out[hh] += Amount;
              ice[hh] -= Amount;

              Amount = Amount*hru_area[hh]/hru_area[To]; // adjust to area of destination HRU
              ice[To] += Amount;
              Ice_in[To] = Amount;
              cumIce_in[To] += Amount;
            }
          }
        } // end of moving
        cumulative_net_rain[hh] = 0.0; // reset at end of season
      } // end of Julian date
    } // end for hhh(hh)
  } // end of day
}

void ClassICEflow::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (ICESlope)' ice        (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (ICESlope)' cumIce_in  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumIce_in[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (ICESlope)' cumIce_out (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumIce_out[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }
}
