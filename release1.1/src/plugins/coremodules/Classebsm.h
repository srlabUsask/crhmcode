//created by Manishankar Mondal

#include "ClassModule.h"


class Classebsm : public ClassModule {
public:

Classebsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , Qnsn_Var, , "){};

// declared observation variables
const double *Qnsn;
const double *QnD;

// declared variables
double *snowmeltD;
double *cumsnowmelt;
double *LW_ebsm;
double *u_ebsm;
double *Qmelt;
double *Qn_ebsm;
double *Qh_ebsm;
double *Qe_ebsm;
double *Qe_subl;
double *cumQe_subl;
double *Qp_ebsm;
double *Qnsn_Acc;

double *LWmax;
double *net_rainD;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *tfactor;
const double *nfactor;
const double *Use_QnD;

// variable inputs
double *SWE;
const double *tmean;
const double *tmax;
const double *tmin;
const double *umean;
const double *rhmean;
const double *net_rain;
const double *Albedo;
const double *sunact;
const double *QdroD;
const double *QdfoD;
const double *sunmax;
const double *Qnsn_Var;

const long  *meltflag;
const long  *delay_melt;
const long  *Qe_subl_from_SWE;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classebsm* klone(string name) const;
};