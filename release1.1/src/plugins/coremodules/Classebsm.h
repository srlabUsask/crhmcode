//created by Manishankar Mondal

#include "ClassModule.h"


class Classebsm : public ClassModule {
public:

Classebsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , Qnsn_Var, , "){};

// declared observation variables
const float *Qnsn;
const float *QnD;

// declared variables
float *snowmeltD;
float *cumsnowmelt;
float *LW_ebsm;
float *u_ebsm;
float *Qmelt;
float *Qn_ebsm;
float *Qh_ebsm;
float *Qe_ebsm;
float *Qe_subl;
float *cumQe_subl;
float *Qp_ebsm;
float *Qnsn_Acc;

float *LWmax;
float *net_rainD;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tfactor;
const float *nfactor;
const float *Use_QnD;

// variable inputs
float *SWE;
const float *tmean;
const float *tmax;
const float *tmin;
const float *umean;
const float *rhmean;
const float *net_rain;
const float *Albedo;
const float *sunact;
const float *QdroD;
const float *QdfoD;
const float *sunmax;
const float *Qnsn_Var;

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