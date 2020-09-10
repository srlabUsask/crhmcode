//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMod_Exec : public ClassModule {
public:

ClassMod_Exec(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  //HINSTANCE DLL;
  long Imodules;
  string S_Vars;
  string S_Pars;
  long Vars_Cnt;
  long Pars_Cnt;

  typedef  long LoadModuleTypeInit(const char *Grp, long GrpNo, long hru_cnt, const char *S_Vars, long VarsNo, float **V, const char *V_Pars, long ParsNo, float **P);
  typedef  long LoadModuleTypeStep(double DTnow); // time step. Zero at end of run.

  LoadModuleTypeInit *LoadUserInit;
  LoadModuleTypeStep *LoadUserStep;

// Lingage arrays

  float **VarArray;
  float **ParArray;

// declared variables
float *Dummy;
float *Dummy2;
long *statusInit;
long *statusStep;

// declared parameters
TStringList *DLL_name;
TStringList *chg_Pars;
TStringList *trk_Vars;
const long *Borland_Dll;

// variable inputs

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassMod_Exec* klone(string name) const;
};