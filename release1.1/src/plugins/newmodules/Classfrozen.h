//created by Manishankar Mondal

#include "ClassModule.h"


class Classfrozen : public ClassModule {
public:

Classfrozen(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};
bool SetOpportunityTime;
bool Update_infil;

// declared observation variables
const float *t0_inhibit;   // (mm/day)

// declared variables
float *infil;         // unfrozen infiltration
float *cuminfil;      // cumulative unfrozen infiltration
float *snowinfil;     // frozen infiltration
float *cumsnowinfil;  // cumulative frozen infiltration
float *cummeltrunoff; // cumulative frozen melt runoff
float *runoff;        // cumulative runoff
float *cumrunoff;     // cumulative melt runoff
float *t0_Acc;        // infiltration opportunity time accumulation
float *t0_Var;        // infiltration opportunity value used in calculation
float *INF;
float *SWEPk;           //
float *snowmeltD_last; //
long  *Julian_window; // currently in Julian window.
long  *Julian_lockout;    // Julian window end date.

// variable put
const float *soil_moist;    //
float *meltrunoff;      // [nhru]

// local variables
long *infiltype;

// declared parameters
const float *basin_area;  // [BASIN]
const float *hru_area;
const float *S0;          // surface saturation (mm3/mm3)
const float *Si;          // initial average soil saturation (mm3/mm3)
const float *C;           // coefficient
const float *hru_tsoil;   // soil temperature(°K) of 0-40cm soil layer at start of infiltration
const float *t_ice_lens;   // overnight minimum to cause ice lens after major melt
const float *t0;          // infiltration opportunity time. Set at end of calibration run.
const float *soil_moist_max; // common to smbal to control maximum inflitration.
const long  *t0_Julian;    // Julian date when t0 is primed. '0' value - never reset.

// variable inputs
const float *snowmeltD;   // (mm/day)
const float *SWE;         // (mm)
const float *frostdepth;
const float *net_rain;
const float *hru_tmin;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrozen* klone(string name) const;
};