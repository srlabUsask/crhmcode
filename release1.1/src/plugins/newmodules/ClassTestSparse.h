//created by Manishankar Mondal

#include "ClassModule.h"

class ClassTestSparse : public ClassModule {
public:

ClassTestSparse(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N_up;
long ObsCnt_P_up;
long ObsCntMan_N_up;
long ObsCntMan_P_up;
long ObsCntRes_N_up;
long ObsCntRes_P_up;
long ObsCnt_N_down;
long ObsCnt_P_down;
long ObsCntMan_N_down;
long ObsCntMan_P_down;
long ObsCntRes_N_down;
long ObsCntRes_P_down;
long ObsCnt_fertperiod;
long ObsCnt_litterperiod;

// declared variables
float *Fert_N_Var;
float *Fert_P_Var;
float *Man_N_Var;
float *Man_P_Var;
float *Res_N_Var;
float *Res_P_Var;
float *Fert_period_Var;
float *Litter_period_Var;

// declared parameters

// put parameters

// declared observation variables
const float *Fert_N_up;
const float *Fert_P_up;
const float *Man_N_up;
const float *Man_P_up;
const float *Res_N_up;
const float *Res_P_up;
const float *Fert_N_down;
const float *Fert_P_down;
const float *Man_N_down;
const float *Man_P_down;
const float *Res_N_down;
const float *Res_P_down;
const float *Fert_period;
const float *Litter_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassTestSparse* klone(string name) const;
};