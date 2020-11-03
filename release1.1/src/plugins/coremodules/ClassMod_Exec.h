//created by Manishankar Mondal

#include "ClassModule.h"

class ClassMod_Exec : public ClassModule {
public:

ClassMod_Exec(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

  //HINSTANCE DLL;
  long Imodules {0};
  string S_Vars;
  string S_Pars;
  long Vars_Cnt {0};
  long Pars_Cnt {0};

  typedef  long LoadModuleTypeInit(const char *Grp, long GrpNo, long hru_cnt, const char *S_Vars, long VarsNo, double **V, const char *V_Pars, long ParsNo, double **P);
  typedef  long LoadModuleTypeStep(double DTnow); // time step. Zero at end of run.

  LoadModuleTypeInit *LoadUserInit{ NULL };
  LoadModuleTypeStep *LoadUserStep{ NULL };

// Lingage arrays

  double **VarArray{ NULL };
  double **ParArray{ NULL };

// declared variables
double *Dummy{ NULL };
double *Dummy2{ NULL };
long *statusInit{ NULL };
long *statusStep{ NULL };

// declared parameters
TStringList *DLL_name{ NULL };
TStringList *chg_Pars{ NULL };
TStringList *trk_Vars{ NULL };
const long *Borland_Dll{ NULL };

// variable inputs

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassMod_Exec* klone(string name) const;
};