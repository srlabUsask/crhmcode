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
double *Fert_N_Var;
double *Fert_P_Var;
double *Man_N_Var;
double *Man_P_Var;
double *Res_N_Var;
double *Res_P_Var;
double *Fert_period_Var;
double *Litter_period_Var;

// declared parameters

// put parameters

// declared observation variables
const double *Fert_N_up;
const double *Fert_P_up;
const double *Man_N_up;
const double *Man_P_up;
const double *Res_N_up;
const double *Res_P_up;
const double *Fert_N_down;
const double *Fert_P_down;
const double *Man_N_down;
const double *Man_P_down;
const double *Res_N_down;
const double *Res_P_down;
const double *Fert_period;
const double *Litter_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassTestSparse* klone(string name) const;
};