//created by Manishankar Mondal

#include "ClassModule.h"

class ClassfrozenAyers : public ClassModule {
public:

ClassfrozenAyers(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};
bool SetOpportunityTime {false};
bool Update_infil {false};

// declared observation variables
const double *t0_inhibit { NULL };   // (mm/day)

// declared variables
double *infil { NULL };         // unfrozen infiltration
double *cuminfil { NULL };      // cumulative unfrozen infiltration
double *snowinfil { NULL };     // frozen infiltration
double *cumsnowinfil { NULL };  // cumulative frozen infiltration
double *cumsnowinfil_0 { NULL };  // cumulative frozen infiltration at beginning of frozen cycle
double *cummeltrunoff { NULL }; // cumulative frozen melt runoff
double *runoff { NULL };        // cumulative runoff
double *cumrunoff { NULL };     // cumulative melt runoff
double *t0_Acc { NULL };        // infiltration opportunity time accumulation
double *t0_Var { NULL };        // infiltration opportunity time used
double *INF { NULL };           //
double *SWEPk { NULL };           //
double *snowmeltD_last { NULL }; //
long  *Julian_window { NULL }; // currently in Julian window.
long  *Julian_lockout { NULL };    // Julian window end date.

// variable put
const double *soil_moist { NULL };    //
double *meltrunoff { NULL };      // [nhru]

// local variables
long *infiltype { NULL };

// declared parameters
const double *basin_area { NULL };  // [BASIN]
const double *hru_area { NULL };
const double *S0 { NULL };          // surface saturation (mm3/mm3)
const double *Si { NULL };          // initial average soil saturation (mm3/mm3)
const double *C { NULL };           // coefficient
const double *hru_tsoil { NULL };   // soil temperature(°K) of 0-40cm soil layer at start of infiltration
const double *t_ice_lens { NULL };   // overnight minimum to cause ice lens after major melt
const double *t0 { NULL };          // infiltration opportunity time. Set at end of calibration run.
const double *soil_moist_max { NULL }; // common to smbal to control maximum inflitration.
const long  *t0_Julian { NULL };    // Julian date when t0 is primed. '0' value - never reset.
const long  *texture { NULL };
const long  *groundcover { NULL };

// variable inputs
const double *snowmeltD { NULL };   // (mm/day)
const double *SWE { NULL };         // (mm)
const double *frostdepth { NULL };
const double *net_rain { NULL };
const double *hru_tmin { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassfrozenAyers* klone(string name) const;
};