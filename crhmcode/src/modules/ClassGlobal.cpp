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

#include "ClassGlobal.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"

using namespace CRHM;


Classglobal* Classglobal::klone(string name) const{
  return new Classglobal(name);
}

void Classglobal::decl(void) {

  Description = "'Calculate theoretical short_wave radiation using method proposed by Garnier and Ohmura (1970).'";

  declvar("QdroD", TDim::NHRU, "daily clear-sky direct", "(MJ/m^2*d)", &QdroD);

  declvar("QdroDext", TDim::NHRU, "daily ExtraTerrestrial direct", "(MJ/m^2*d)", &QdroDext);

  declvar("QdfoD", TDim::NHRU, "daily average clear-sky diffuse", "(MJ/m^2*d)", &QdfoD);

  declvar("Qdro", TDim::NHRU, "clear-sky direct", "(W/m^2)", &Qdro);

  declvar("Qdfo", TDim::NHRU, "clear-sky diffuse", "(W/m^2)", &Qdfo);

  declvar("Qdflat", TDim::NHRU, "clear-sky 'Qdro + Qdfo' on horizontal surface", "(W/m^2)", &Qdflat);

  declvar("QdflatE", TDim::NHRU, "'Qdro' on horizontal surface, no atmosheric attenuation", "(W/m^2)", &QdflatE);

  declvar("QdflatD", TDim::NHRU, "daily clear-sky Qdro (with diffuse) on horizontal surface", "(MJ/m^2*d)", &QdflatD);

  declvar("SolAng", TDim::NHRU, "Solar Angle", "(r)", &SolAng);

  declvar("SunMax", TDim::NHRU, "maximum sunshine hours", "(h)", &SunMax);

  declvar("cosxs", TDim::NHRU, "cosine of the angle of incidence on the slope", "()", &cosxs);

  declvar("cosxsflat", TDim::NHRU, "cosine of the angle of incidence on the horizontal", "()", &cosxsflat);

  declvar("pQdro", TDim::NFREQ, "clear-sky direct", "(MJ/m^2*int)", &pQdro, &pQdro_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pQdfo", TDim::NFREQ, "clear-sky diffuse", "(MJ/m^2*int)", &pQdfo, &pQdfo_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pQdflat", TDim::NFREQ, "Qdro + Qdfo on horizontal surface", "(MJ/m^2*int)", &pQdflat, &pQdflat_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pQdflatE", TDim::NFREQ, "Qdro on horizontal surface with no atmospheric attenuation", "(MJ/m^2*int)", &pQdflatE, &pQdflatE_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pSol", TDim::NFREQ, "Solar Angle", "(r)", &pSol, &pSol_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pCosxs", TDim::NFREQ, "Cos(x^s)", "(r)", &pCosxs, &pCosxs_FREQ, 0, true, false, TVISIBLE::PRIVATE);

  declvar("pCosxs0", TDim::NFREQ, "Cos(x^s) on the horizontal", "(r)", &pCosxs0, &pCosxs0_FREQ, 0, true, false, TVISIBLE::PRIVATE);


// parameters

  declparam("hru_lat", TDim::NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(" + string(DEGREE) + ")", &hru_lat);

  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  declparam("hru_GSL", TDim::NHRU, "0.0", "-90.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(" + string(DEGREE) + ")", &hru_GSL);

  declparam("hru_ASL", TDim::NHRU, "0.0", "-360.0", "360.0","aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(" + string(DEGREE) + ")", &hru_ASL);

  declparam("Time_Offset", TDim::NHRU, "0.0", "-12.0", "12.0","solar time offset from local time", "(h)", &Time_Offset);

}

void Classglobal::init(void) {

  nhru = getdim(TDim::NHRU);

  int Integer = CalcFreq/Global::Freq;

  int Remainder = CalcFreq%Global::Freq;

  if(Remainder != 0 || Integer < 1){
    CRHMException TExcept("\"288/(first observation frequency)\" must be an integer > one!", TExcept::TERMINATE);
    LogError(TExcept);
  }

}


// void Classglobal::air_mass (const double czen, double &oam){

//   double diff;

//   double Z = acos(czen);

void Classglobal::air_mass (const double czen_in, double &oam_out){  // performance improvement (PRL)

  // double diff;
  // double Z = acos(czen);

  float czen = czen_in;
  float diff;
  float Z = acos(czen);

  float oam = fabs(1.0f/(czen + 0.50572f*pow(96.07995f-Z, -1.6364f)));       // oam by cosecant approx.

  if(oam < 2.9) {                         // zenith < 70 deg
    oam_out = oam;
    return;
  }
  else if(oam < 16.38) {                 // zenith < 86.5 deg
    diff = pow(10.0f, 2.247f*log10(oam) - 2.104f);
    oam = oam - diff;
    oam_out = oam;
    return;
  }
  else if(oam <= 114.6){                 // zenith < 89.5 deg
	diff = pow(10.0f, 1.576f*log10(oam) - 1.279f);
    oam = oam - diff;
    oam_out = oam;
    return;
  }

  oam = 30.0;                             // computed oam >114.6
  oam_out = oam;
}

void Classglobal::run(void) {

/*   calculate daily incoming short wave radiation

     calculate direct and diffuse solar radiation on a slope in mj/m^2*d
          for a surface at given slope and azimuth
          for any given day and transmissivity
          account cloud cover empirically

      written by Pat Landine
                 Division of Hydrology
                 University of Sask.

            ref. B.J. Garnier and Atsuma Ohmura
                 A method of calculating the direct shortwave
                 radiation income of slopes
                 Jour. of Applied Meteorology vol.7 1968

      incident shortwave radiation

         id = (sol/rad_vec**2)*integral{(trans**oam)*cos(x^s)*dh}

              sol      = solar constant
              rad_vec  = radius vector of the earth'S orbit
              trans    = mean transmissivity of the atmosphere
              oam      = optical air mass
              cos(x^s) = cosine of the angle of incidence  of the
                         sun'S rays on the slope (x is a unit normal
                         vector pointing away from the surface and
                         s is the unit vector expressing the sun'S
                         position.
              h        = hour angle measured from solar noon.
                         (15 deg./hour or pi/12 rad/hour)

                integration is performed as an addition of a series of
                MINS_int minute intervals

       diffuse clear sky radiation

           Qdfo = 0.5*[(1 - aw - ao)*it - id]*(cos(gslope/2))**2

              aw     = radiation absorbed by water vapour (assumed = 7%
              aw     = radiation absorbed by ozone (assumed = 2%)
              gslope = gradient of slope

              it = (sol/rad_vec**2)*integral{czen*dh}

                 czen = cosine of the sun'S zenith angle

       cloud cover adjustment

           ig = (id + Qdfo)

       variable description

           aslope = azimuth of the slope
           dec    = declination of the sun above or below the equator
           day = day of the calendar year

      use phys_constants
*/

  long Period, Day;

  double Trans, Dec, Rad_vec, Sol, Clat, Slat, Cdec, Sdec, Hr_Ang;
  double Czen, t1, t2, x, y, z, Oam;
  double cosxsL, cosxs0, t10, t20;
  double It, Id, diffuse, Sum_Id, Sum_Diff, Sum_Sol, Sum_cosxs, Sum_cosxs0, Sum_Ext, Sum_Flatd, Sum_Flatf;

  Period = (getstep()-1)%Global::Freq;

  if(Period == 0 || getstep() == 1){

    for (hh = 0; hh < nhru; ++hh) {

      Day = julian("now");
      if(Global::Freq <= 1) --Day;  // if daily 00:00 is the next day

      Trans = 0.818;

      Dec = sin(((long long)Day - 81ll) * DEGtoRAD365) * 0.40928;     // Declination

      Rad_vec = .01676*cos(M_PI-0.017262*((long long)Day-3ll))+1.0;   // radius vector
      Sol = 0.0819/(Rad_vec*Rad_vec);                    // solar constant  mj/m**2*min or 117.936 mj/m**2*day

// calculate sines and cosines

      Clat = cos(hru_lat[hh]*DEGtoRAD);
      Slat = sin(hru_lat[hh]*DEGtoRAD);
      Cdec = cos(Dec);
      Sdec = sin(Dec);

// set constants and initial values

      SunMax[hh] = 0.0;                 // no. of sunshine hours in 10ths.
      QdroD[hh] = 0.0;
      QdroDext[hh] = 0.0;
      QdfoD[hh] = 0.0;
      QdflatD[hh] = 0.0;
      Sum_Id = 0.0;
      Sum_Diff = 0.0;
      Sum_Sol = 0.0;
      Sum_cosxs = 0.0;
      Sum_cosxs0 = 0.0;
      Sum_Ext = 0.0;
      Sum_Flatd = 0.0;
      Sum_Flatf = 0.0;

/*     cos(x^s) = [(Slat * cos(Hr_Ang) * (-cos(ASL) * sin(GSL))
                    - sin(Hr_Ang) * (sin(ASL) * sin(GSL))
                    + (Clat * cos(Hr_Ang)) * cos(GSL)] * Cdec
                    + [Clat * (cos(ASL) * sin(GSL))
                    + Slat * cos(GSL)] * Sdec */

      x = -cos(hru_ASL[hh]*DEGtoRAD) * sin(hru_GSL[hh]*DEGtoRAD);
      y = sin(hru_ASL[hh]*DEGtoRAD) * sin(hru_GSL[hh]*DEGtoRAD);   //  compute constant
      z = cos(hru_GSL[hh]*DEGtoRAD);                               //  components of cos(x^s)
      t1 = (x*Slat + z*Clat)* Cdec;
      t2 = (-x*Clat + z*Slat)* Sdec;

      t10 = Clat* Cdec;
      t20 = Slat* Sdec;

      Hr_Ang = -M_PI*(1.0 + Time_Offset[hh]/12.0);

      for(long jj = 0; jj < CalcFreq; ++jj, Hr_Ang+=RADxxMIN){ // CalcFreq periods/day

        Czen = Cdec*Clat*cos(Hr_Ang) + Sdec*Slat;  // cos of zenith angle
        diffuse = 0.0;

        if(Czen > 0.0) {
          Sum_Sol = Sum_Sol + M_PI/2.0f - acos(Czen);

          SunMax[hh] = SunMax[hh] + MINS_int; // sum sunshine minutes
          It = MINS_int*Sol*Czen;           // extra-ter. rad for MINS_int minute interval

          cosxs0 = t10*cos(Hr_Ang);
          cosxs0 = cosxs0 + t20;
// horzontal
          if(cosxs0 > 0.0){      // not in shadow
            Sum_cosxs0 += cosxs0;

            air_mass (Czen, Oam); // get optical air mass
	    Oam = Oam*pow((288.0f-0.0065f*hru_elev[hh])/288.0f, 5.256f);  // correction

            Id = MINS_int*Sol*cosxs0; // direct rad. for MINS_int minute interval
            Sum_Ext += Id;

            Id = Id*pow(Trans, Oam); // direct rad. for MINS_int minute interval

// List (1968) diffuse = 0.5((1-aw-ac)Qa - Id) where
// aw = radiation absorbed by water vapour (7%)
// ac = radiation absorbed by ozone (2%)

            diffuse = 0.5f*(0.91f*It-Id);      // Diffuse radiation on horizontal
            Sum_Flatf += diffuse;
            Sum_Flatd += Id;
          }

          cosxsL = -y*sin(Hr_Ang)*Cdec + t1*cos(Hr_Ang);
          cosxsL = cosxsL + t2;

          if(cosxsL > 0.0) {       // slope not in shadow
            Sum_cosxs += cosxsL;

            air_mass (Czen, Oam); // get optical air mass
            Oam = Oam*pow((288.0f-0.0065f*hru_elev[hh])/288.0f, 5.256f);  // correction

            Id = MINS_int*Sol*cosxsL;     // direct rad. for MINS_int minute interval
            Id = Id*pow(Trans, Oam);

            Sum_Id += Id;
          }

          diffuse = diffuse*sqr(cos(hru_GSL[hh]/2.0 * DEGtoRAD)); // on slope

          Sum_Diff += diffuse;

        } // end if

        if (!((jj+1) % (CalcFreq/Global::Freq))) {

          int kk = jj/(CalcFreq/Global::Freq);
          pQdro_FREQ[kk][hh] = Sum_Id;     // direct radiation
          pQdfo_FREQ[kk][hh] = Sum_Diff;   // diffuse radiation
          pQdflat_FREQ[kk][hh] = (Sum_Flatd + Sum_Flatf); // level direct + diffuse radiation
          pQdflatE_FREQ[kk][hh] = Sum_Ext; // level direct no atmospheric attenuation
          pSol_FREQ[kk][hh] = Sum_Sol/(CalcFreq/Global::Freq);  // solar angle
          pCosxs_FREQ[kk][hh] = Sum_cosxs/(CalcFreq/Global::Freq);  // solar angle
          pCosxs0_FREQ[kk][hh] = Sum_cosxs0/(CalcFreq/Global::Freq);  // solar angle

          QdroD[hh]    += Sum_Id;   // direct radiation
          QdroDext[hh] += Sum_Ext;  // ExtraTerrestrial radiation
          QdfoD[hh]    += Sum_Diff; // diffuse radiation
          QdflatD[hh]  += Sum_Flatd + Sum_Flatf; // level direct

          Sum_Id = 0.0;
          Sum_Diff = 0.0;
          Sum_Sol = 0.0;
          Sum_cosxs = 0.0;
          Sum_cosxs0 = 0.0;
          Sum_Ext = 0.0;
          Sum_Flatd = 0.0;
          Sum_Flatf = 0.0;
        }

      } // end for
      SunMax[hh] = SunMax[hh]/60.0;        // convert to hours*10

      Hr_Ang = 0.0;
    } // end for hh
  } // end if - Entire day calculated

  for (hh = 0; hh < nhru; ++hh) {
    Qdro[hh] =    pQdro_FREQ[Period][hh]*1E6/86400*Global::Freq; // MJ/m^2.int to W/m^2
    Qdfo[hh] =    pQdfo_FREQ[Period][hh]*1E6/86400*Global::Freq; // MJ/m^2.int to W/m^2
    Qdflat[hh] =  pQdflat_FREQ[Period][hh]*1E6/86400*Global::Freq; // MJ/m^2.int to W/m^2
    QdflatE[hh] = pQdflatE_FREQ[Period][hh]*1E6/86400*Global::Freq; // MJ/m^2.int to W/m^2
    SolAng[hh] =  pSol_FREQ[Period][hh];
    cosxs[hh] =   pCosxs_FREQ[Period][hh];
    cosxsflat[hh] =   pCosxs0_FREQ[Period][hh];
  } // end if
}
