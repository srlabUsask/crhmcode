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
//created by Peter Lawford

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassRotate_Crop.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"

using namespace CRHM;

ClassRotate_Crop* ClassRotate_Crop::klone(string name) const{
  return new ClassRotate_Crop(name);
}

void ClassRotate_Crop::decl(void) {

  Description = "'Grows crop height from initial to maturiy.'";

  declparam("apply_rotation", TDim::NHRU, "[0]", "0", "10", "What amount to apply rotation to this HRU, 0 for not in rotation", "()", &apply_rotation);

  declparam("soil_moist_max", TDim::NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
        "Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);
    declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
        "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
        "and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

  declputvar("*", "soil_moist", "(mm)", &soil_moist);
  declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

}

void ClassRotate_Crop::init(void) {
  n_slots_in_rotation = 0;
  n_hrus_in_rotation = 0;
  for(hh = 0; chkStruct(); ++hh) {
    if (apply_rotation[hh] > 0) {  
      n_slots_in_rotation += apply_rotation[hh];
      n_hrus_in_rotation++;
    }
  }
  // It's not allowed to have only one HRU in a rotation
  assert( (n_hrus_in_rotation != 1) && "It's not allowed to have only one HRU in a rotation");
}

void ClassRotate_Crop::run(void) {

  long nstep = getstep() % Global::Freq;
  long JULIAN;

  if ((n_slots_in_rotation > 0) && (nstep == 0)) { // end of day
    JULIAN = julian("now");
    if (JULIAN == 1) {

// Calculate the average fractional water content for HRUs in rotation
      double sum_fractional_water_content_moist = 0.0;
      double sum_fractional_water_content_rechr = 0.0;
      for(hh = 0; chkStruct(); ++hh) {
        if (apply_rotation[hh]) {
          sum_fractional_water_content_moist += soil_moist[hh] / soil_moist_max[hh];
          sum_fractional_water_content_rechr += soil_rechr[hh] / soil_rechr_max[hh];
        }
      }
      double avg_fractional_water_content_moist = sum_fractional_water_content_moist / n_slots_in_rotation;
      double avg_fractional_water_content_rechr = sum_fractional_water_content_rechr / n_slots_in_rotation;

// Transfer soil moisture out of the HRU if the fractional water content is above the average for HRUs in rotation
      for(hh = 0; chkStruct(hh); ++hh) {
        if (apply_rotation[hh]) {
          double fractional_water_content_moist = soil_moist[hh] / soil_moist_max[hh];
          double fractional_water_content_rechr = soil_moist[hh] / soil_moist_max[hh];

          // divide by 3 to remove a maximum of 1/3 the excess water content in each of 3 years
          // Technically this would be an exponential decay since next year the excess content will be lower
          double excess_moist = soil_moist_max[hh]*(
                      fractional_water_content_moist - avg_fractional_water_content_moist) / 3;
          double excess_rechr = soil_rechr_max[hh]*(
                      fractional_water_content_rechr - avg_fractional_water_content_rechr) / 3;

          if (excess_moist > 0) {
            for(long jj = 0; chkStruct(jj); ++jj) {
              if ( (hh != jj) && (apply_rotation[jj] > 0)) {
                soil_moist[jj] += excess_moist * apply_rotation[jj] / (n_slots_in_rotation - apply_rotation[hh]);
              }
            }
            soil_moist[hh] -= excess_moist;
          }

          if (excess_rechr > 0) {
            for(long jj = 0; chkStruct(jj); ++jj) {
              if ( (hh != jj) && (apply_rotation[jj] > 0)) {
                soil_rechr[jj] += excess_rechr * apply_rotation[jj] / (n_slots_in_rotation - apply_rotation[hh]);
              }
            }
            soil_rechr[hh] -= excess_rechr;
          }

        }
      }
    }
  }
}
