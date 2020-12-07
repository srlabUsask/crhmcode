//created by Manishankar Mondal

#include "Classebsm.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM/ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;



Classebsm* Classebsm::klone(string name) const{
  return new Classebsm(name);
}

void Classebsm::decl(void) {

  Description = "'Energy-budget snowmelt model for the Canadian Prairies', \
                 'ebsm using Brunt et al', \
                 'ebsm using input variable Qnsn_Var (W/m^2*int) from CanopyClearing etc.', \
                 'ebsm using input observation Qnsn (W/m^2*int)', \
                 'ebsm using input observation QnD (MJ/m^2*d)'";

  variation_set = VARIATION_ORG;

  declvar("snowmeltD", TDim::NHRU, "daily snowmelt", "(mm/d)", &snowmeltD);

  declvar("cumsnowmelt", TDim::NHRU, "cumulative melt", "(mm)", &cumsnowmelt);

  declstatvar("LW_ebsm", TDim::NHRU, "liquid water in snowpack", "(mm)", &LW_ebsm, NULL, 1, false, TVISIBLE::PRIVATE);

  declstatvar("u_ebsm", TDim::NHRU, "snowpack energy deficit", "(MJ)", &u_ebsm, NULL, 1, false, TVISIBLE::PRIVATE);

  declvar("Qmelt", TDim::NHRU, "Qmelt = Qn+Qh+Qe+Qp", "(MJ/d)", &Qmelt);

  declvar("Qn_ebsm", TDim::NHRU, "net radiation", "(MJ/d)", &Qn_ebsm);

  declvar("Qh_ebsm", TDim::NHRU, "sensible heat", "(MJ/d)", &Qh_ebsm);

  declvar("Qe_ebsm", TDim::NHRU, "latent heat", "(MJ/d)", &Qe_ebsm);

  declvar("Qe_subl", TDim::NHRU, "latent heat sublimation", "(mm/d)", &Qe_subl);

  declvar("cumQe_subl", TDim::NHRU, "cumulative latent heat sublimation", "(mm)", &cumQe_subl);

  declvar("Qp_ebsm", TDim::NHRU, "input from rainfall", "(MJ/d)", &Qp_ebsm);


  decldiag("LWmax", TDim::NHRU, "maximum liquid water in snowpack", "(mm)", &LWmax);

  declvar("net_rainD", TDim::NHRU, "daily net rain", "(mm/d)", &net_rainD);


  decldiagparam("delay_melt", TDim::NHRU, "[0]", "0","366", "inhibit melt until this Julian date. Default incorrect for the Southern Hemisphere", "()", &delay_melt);

  decldiagparam("Qe_subl_from_SWE", TDim::NHRU, "[0]", "0", "1", "0 - add to 'Qmelt' (original version), 1 - take Qe_subl from SWE ", "()", &Qe_subl_from_SWE);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);


  declgetvar("*", "SunMax", "(h)",       &sunmax);
  declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
  declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
  declgetvar("*", "hru_tmean", "(°C)",  &tmean);
  declgetvar("*", "hru_tmax", "(°C)",   &tmax);
  declgetvar("*", "hru_tmin", "(°C)",   &tmin);
  declgetvar("*", "hru_umean", "(m/s)",  &umean);
  declgetvar("*", "hru_rhmean", "(%)", &rhmean);
  declgetvar("*", "hru_SunAct", "(h)", &sunact);
  declgetvar("*", "meltflag", "()",   &meltflag);
  declgetvar("*", "Albedo", "()",     &Albedo);
  declputvar("*", "SWE", "(mm)",        &SWE);
  declgetvar("*", "net_rain", "(mm/int)", &net_rain);


  variation_set = VARIATION_0;

  decldiagparam("tfactor", TDim::NHRU, "[0.0]", "0.0","10.0", "degree day melt factor", "(mm/d*°C)", &tfactor);

  decldiagparam("nfactor", TDim::NHRU, "[0.0]", "0.0","10.0", "net radiation factor (typical value 3.0(mm*m^2/MJ))", "(mm*m^2/MJ)", &nfactor);

  decldiagparam("Use_QnD", TDim::NHRU, "[0]", "0","1", "1 - Use QnD if available", "()", &Use_QnD);


  variation_set = VARIATION_0 + VARIATION_3;

  declreadobs("QnD", TDim::NHRU, "net radiation", "(MJ/m^2*d)", &QnD, HRU_OBS_Q, true); // must check for NULL


  variation_set = VARIATION_1 + VARIATION_2;

  declstatvar("Qnsn_Acc", TDim::NHRU, "accumulator for Qnsn_Var/Qnsn", "(W/m^2)", &Qnsn_Acc); // daily value


  variation_set = VARIATION_1;

  declgetvar("*",  "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var); // interval value

  variation_set = VARIATION_2;


  declreadobs("Qnsn", TDim::NHRU, "net radiation", "(W/m^2*int)", &Qnsn, HRU_OBS_Q);

  variation_set = VARIATION_ORG;
}

void Classebsm::init(void) {

  nhru = getdim(TDim::NHRU);

  for(hh = 0; hh < nhru; ++hh) {
    snowmeltD[hh] = 0.0;
    cumsnowmelt[hh] = 0.0;
    LW_ebsm[hh] = 0.0;
    u_ebsm[hh] = 0.0;
    Qmelt[hh] = 0.0;
    Qn_ebsm[hh] = 0.0;
    Qh_ebsm[hh] = 0.0;
    Qe_ebsm[hh] = 0.0;
    Qe_subl[hh] = 0.0;
    cumQe_subl[hh] = 0.0;
    Qp_ebsm[hh] = 0.0;

    if(variation == VARIATION_ORG)
      if(nfactor[hh] != 0.0 && QnD == NULL){
        CRHMException TExcept("ebsm: nfactor > 0.0 with observation 'QnD' not defined!", TExcept::TERMINATE);
        LogError(TExcept);
      }
  }
}

void Classebsm::run(void) {

      double umin, ref, melt;

      long  nstep = getstep()%Global::Freq;

      for(hh = 0; chkStruct(); ++hh){
        if(nstep == 1 || Global::Freq == 1){ // beginning of every day
          net_rainD[hh] = net_rain[hh];
          if(variation == VARIATION_1)
            Qnsn_Acc[hh] = Qnsn_Var[hh];
          else if(variation == VARIATION_2)
            Qnsn_Acc[hh] = Qnsn[hh];
        }
        else{
          net_rainD[hh] += net_rain[hh];
          if(variation == VARIATION_1)
            Qnsn_Acc[hh] += Qnsn_Var[hh];
          else if(variation == VARIATION_2)
            Qnsn_Acc[hh] += Qnsn[hh];
        }
      }

      if(nstep == 0 || Global::Freq == 1){ // end of every day

        for(hh = 0; chkStruct(); ++hh) {

          snowmeltD[hh] = 0.0;
          Qmelt[hh] = 0.0;
          Qn_ebsm[hh] = 0.0;
          Qh_ebsm[hh] = 0.0;
          Qe_ebsm[hh] = 0.0;
          Qe_subl[hh] = 0.0;
          Qp_ebsm[hh] = 0.0;

          if(SWE[hh] <= 0.0) { // bare ground
            LW_ebsm[hh] = 0.0;
            u_ebsm[hh] = 0.0;
          }
          else if(variation == VARIATION_ORG && (tfactor[hh] > 0.0 || nfactor[hh] > 0.0) && meltflag[hh] == 1) {
            if(delay_melt[hh] <= julian("now")) {

              if(QnD){ // observation available (MJ/m^2*d)
                if(QnD[hh] > 0.0)
                  Qn_ebsm[hh] = QnD[hh]*nfactor[hh];
              }

              Qh_ebsm[hh] = tmax[hh]*tfactor[hh];

              Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh];
              snowmeltD[hh] = Qmelt[hh];
              if (snowmeltD[hh] <= 0.0)
                snowmeltD[hh] = 0.0;
              else {
                if(SWE[hh] > snowmeltD[hh])
                  SWE[hh] = SWE[hh] - snowmeltD[hh];
                else {
                  snowmeltD[hh] = SWE[hh];
                  SWE[hh] = 0.0;
                }
                cumsnowmelt[hh] = cumsnowmelt[hh] + snowmeltD[hh];
              }
            }
          }
          else if(meltflag[hh] == 1 && delay_melt[hh] <= julian("now")) {
            double eamean = Common::estar(tmean[hh])*rhmean[hh]/100.0;\
            switch (variation) {

              case VARIATION_ORG :
                if(QnD != NULL && Use_QnD[hh]){ // observation available (MJ/m^2*d)
                  if(QnD[hh] > 0.0)
                    Qn_ebsm[hh] = QnD[hh];
                }
                else
                  Qn_ebsm[hh] = -0.53+0.47*(QdroD[hh] + QdfoD[hh])*(0.52+0.52*sunact[hh]/sunmax[hh])*(1.0-Albedo[hh]);

                break;
              case VARIATION_1 :
                Qn_ebsm[hh] = Qnsn_Acc[hh]*0.0864/Global::Freq; // convert to (MJ/m^2*d)
              break;
              case VARIATION_2 :
                Qn_ebsm[hh] = Qnsn_Acc[hh]*0.0864/Global::Freq; // convert to (MJ/m^2*d)
              break;
              case VARIATION_3 :
                Qn_ebsm[hh] = QnD[hh]; // already in (MJ/m^2*d)
              break;
            } // switch

            Qh_ebsm[hh] = -0.92+0.076*umean[hh]+0.19*tmax[hh];
            Qe_ebsm[hh] = 0.08*(0.18+0.098*umean[hh])*(6.11-eamean*10.0);

            Qe_subl[hh] = Qe_ebsm[hh]/2.83; // Lv = 2.83 mJ/Kg

            if(Qe_subl_from_SWE[hh]){
              if(Qe_subl[hh] > SWE[hh])
                Qe_subl[hh] = SWE[hh];
              cumQe_subl[hh] += Qe_subl[hh];
              SWE[hh] = SWE[hh] - Qe_subl[hh];
            }

            if(net_rainD[hh] > 0.0)
              Qp_ebsm[hh] = net_rainD[hh]*tmean[hh]*4.2/1000.0;
            else
              Qp_ebsm[hh] = 0.0;

            if(Qe_subl_from_SWE[hh])
              Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qp_ebsm[hh]; // Qe_ebsm already taken from SWE
            else
              Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qe_ebsm[hh] + Qp_ebsm[hh];

            u_ebsm[hh] = u_ebsm[hh] + Qmelt[hh];

            LWmax[hh] = SWE[hh]*0.05;

            double t_minus = tmin[hh];
            if(t_minus > 0.0)
              t_minus = 0.0;

            umin = SWE[hh]*(2.115+0.00779*t_minus)*t_minus/1000.0;

            if(umin > u_ebsm[hh])
              u_ebsm[hh] = umin;

            if(u_ebsm[hh] > 0.0) {
              melt = u_ebsm[hh]/316.8*1000.0; // thermal quality B=0.95. 316.8 = 333.5*0.95 (kJ/kg)
              if(melt + LW_ebsm[hh] > LWmax[hh]) {
                snowmeltD[hh] = melt - (LWmax[hh] - LW_ebsm[hh]);
                if(snowmeltD[hh] > SWE[hh]) {
                  snowmeltD[hh] = SWE[hh] + LW_ebsm[hh];
                  SWE[hh] = 0.0;
                  LW_ebsm[hh] = 0.0;
                }
                else if(SWE[hh] > melt){
                  SWE[hh] = SWE[hh] - melt;
                  LW_ebsm[hh] = LWmax[hh];
                }
                else {
                  snowmeltD[hh] = SWE[hh] + LW_ebsm[hh];
                  SWE[hh] = 0.0;
                  LW_ebsm[hh] = 0.0;
                }
                cumsnowmelt[hh] = cumsnowmelt[hh] + snowmeltD[hh];
              }
              else { // melt retained in snowpack
                LW_ebsm[hh] = LW_ebsm[hh] + melt;
                SWE[hh] = SWE[hh] - melt;
                snowmeltD[hh] = 0.0;
              }
              u_ebsm[hh] = 0.0;
            }
            else { // no melt - convert liquid water to ice - reduce u_ebsm accordingly
              Qmelt[hh] = 0.0;
              snowmeltD[hh] = 0.0;

              if(u_ebsm[hh] < 0.0){
                ref = -u_ebsm[hh]/333.5*1000.0;
                if(LW_ebsm[hh] > ref) {
                  u_ebsm[hh] = 0.0;
                  SWE[hh] = SWE[hh] + ref;
                  LW_ebsm[hh] = LW_ebsm[hh] - ref;
                }
                else {
                  u_ebsm[hh] = u_ebsm[hh] + LW_ebsm[hh]*333.5/1000.0;
                  SWE[hh] = SWE[hh] + LW_ebsm[hh];
                  LW_ebsm[hh] = 0.0;
                }
              }
            } // no melt
          } // if
          else { // meltflag[hh] == 0. TB addition 02/02/06
            if(tmin[hh] < 0.0)
              u_ebsm[hh] = SWE[hh]*(2.115+0.00779*tmin[hh])*tmin[hh]/1000.0;
            if(LW_ebsm[hh] > 0.0){
              u_ebsm[hh] = u_ebsm[hh] + LW_ebsm[hh]*333.5/1000.0;
              SWE[hh] = SWE[hh] + LW_ebsm[hh];
            }
            LW_ebsm[hh] = 0.0;
          }
        } // end for HRUs
      } // end if (end of day)
}

void Classebsm::finish(bool good) {

  if(!good) return;

  double Allcumsnowmelt = 0.0;

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (ebsm)' cumQe_subl   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumQe_subl[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (ebsm)' cumsnowmelt   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmelt[hh], hru_area[hh], basin_area[0]);

    Allcumsnowmelt += cumsnowmelt[hh]*hru_area[hh];
  }
  LogDebug(" ");
  LogMessage(string("'" + Name + " (ebsm)' Allcumsnowmelt (mm*basin): ").c_str(), Allcumsnowmelt);
  LogDebug(" ");
}