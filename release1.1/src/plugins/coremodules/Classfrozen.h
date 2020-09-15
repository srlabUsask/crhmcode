//created by Manishankar Mondal

#include "ClassModule.h"


class Classfrozen : public ClassModule {
public:

Classfrozen(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};
bool SetOpportunityTime;
bool Update_infil;

// declared observation variables
const double *t0_inhibit;   // (mm/day)

// declared variables
double *infil;         // unfrozen infiltration
double *cuminfil;      // cumulative unfrozen infiltration
double *snowinfil;     // frozen infiltration
double *cumsnowinfil;  // cumulative frozen infiltration
double *cummeltrunoff; // cumulative frozen melt runoff
double *runoff;        // cumulative runoff
double *cumrunoff;     // cumulative melt runoff
double *t0_Acc;        // infiltration opportunity time accumulation
double *t0_Var;        // infiltration opportunity value used in calculation
double *INF;
double *SWEPk;           //
double *snowmeltD_last; //
long  *Julian_window; // currently in Julian window.
long  *Julian_lockout;    // Julian window end date.

// variable put
const double *soil_moist;    //
double *meltrunoff;      // [nhru]

// local variables
long *infiltype;

// declared parameters
const double *basin_area;  // [BASIN]
const double *hru_area;
const double *S0;          // surface saturation (mm3/mm3)
const double *Si;          // initial average soil saturation (mm3/mm3)
const double *C;           // coefficient
const double *hru_tsoil;   // soil temperature(°K) of 0-40cm soil layer at start of infiltration
const double *t_ice_lens;   // overnight minimum to cause ice lens after major melt
const double *t0;          // infiltration opportunity time. Set at end of calibration run.
const double *soil_moist_max; // common to smbal to control maximum inflitration.
const long  *t0_Julian;    // Julian date when t0 is primed. '0' value - never reset.

// variable inputs
const double *snowmeltD;   // (mm/day)
const double *SWE;         // (mm)
const double *frostdepth;
const double *net_rain;
const double *hru_tmin;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrozen* klone(string name) const;
};