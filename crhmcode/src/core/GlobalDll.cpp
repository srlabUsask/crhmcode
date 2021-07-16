

// 12/19/16
//---------------------------------------------------------------------------
#include <stdio.h>
//#include <tchar.h>



#include "GlobalDll.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init) removed uneeded pragma - jhs507

using namespace std;

bool Global::NaNcheck;
bool Global::LOGVARLOAD;

long Global::GroupCntTrk;
long Global::StructCntTrk;

long Global::Freq;     // set by first observation file.

long Global::DTindx;  // current index during model run and observation display.  Set in main.
long Global::DTmin;   // minimum index during model run and observation display.  Set in main.
long Global::DTmax;   // maximum index during model run and observation display.  Set in main.
long Global::IndxMin; // minimum index of the first file.
long Global::IndxMax; // maximum index of the first file.

long Global::maxobs;
long Global::maxlay;
long Global::maxhru;

long Global::nobs;
long Global::nlay;
long Global::nhru;

long Global::CRHMStatus;  // module status; module control = 1 , main control = 2 and Finished = 4. Both inhibit output.
std::string Global::CurrentModuleRun;  //!< Currently executing module
long Global::CRHMControlSaveCnt; // NewModules input

BitSet Global::RunUpBitSet; // determines modules executed during looping.
std::set<std::string> * Global::ModuleBitSet; // determines modules executed during calculating ahead.

double Global::Interval; // set by first observation file.
double Global::DTstart;  // set by first observation file.  Integer.
double Global::DTend;    // set by first observation file.  Integer.

TDateTime Global::DTnow; // current time during model run and observation display.  Set in main.

TDateTime Global::RapidAdvanceTo; // Rapid advance to this date.
TDateTime Global::LoopTo; // Loop to this date.
long Global::LoopCnt;  // Loop this count
long Global::LoopCntDown;  // Loop this count

TBuild Global::BuildFlag;
TIMEFORMAT Global::TimeFormat;

MapVar Global::MapVars;     // DECL
MapVar Global::MapVarsGet;  // INIT
MapVar Global::MapVarsPut;  // INIT
MapVar Global::MapObsGet;   // INIT
MapPar Global::MapPars;     // DECL
MapPar Global::SharedMapPars; // DECL

Mapstr Global::Mapgetvar;   // build
Mapstr Global::Mapputvar;   // build
Mapstr Global::Mapreadvar;  // build
Mapstr Global::Mapdeclvar;  // build
Mapstr Global::Mapdeclpar;  // build
Mapstr Global::Mapdeclobs;  // build
Mapstr Global::Mapdeclstat; // build
Mapstr2 Global::MapAKA;

std::map<std::string, ClassModule * > * (Global::AllModulesList);
std::list<std::pair<std::string, ClassModule*>> * (Global::OurModulesList);
std::list<std::pair<std::string, unsigned short>> * (Global::OurModulesVariation);
std::vector<std::string> * (Global::MacroModulesList);
std::list<std::pair<std::string, int>> * (Global::AllModelsList);
std::list<std::pair<std::string, Administer* >> * (Global::ModelModulesList);

TStringList *(Global::OurHelpList);
TStringList *(Global::PendingDLLModuleList);
TStringList *(Global::ReportList);
TStringList *(Global::DeclRootList);
TStringList *(Global::OldModuleName);
TStringList *(Global::NewModuleName);

//HWND Global::crhmMain;
//HWND Global::crhmLog;

double  *Global::lapse_rate; // used for array observations adjustments
double  *Global::ppt_adj; // used for array observations adjustments
double  *Global::hru_elev; // used for array observations adjustments
long   **Global::HRU_OBS; // used for array observations

double  *Global::Warming_t; // used for climate warming
double  *Global::Warming_p; // used for climate warming
long   *Global::RH_VP_flag; // used for elevation change. -> 0 maintain rh, 1 -> maintain ea
long   *Global::RH_VP_flag2; // used for climate warming. -> 0 maintain rh, 1 -> maintain ea
long    Global::RH_EA_obs; // 0 -> rh obs, 1 -> ea obs
long    Global::OBS_AS_IS; // 0 -> process obs, 1 -> no processing
long    Global::WQ_prj; // true -> processing WQ modules

double  **Global::OBS_ELEV; // used for array observations adjustments
long   **Global::HRU_OBS_DIRECT; // used for array observations
double  **Global::obs_t; // used for array observations adjustments
double  **Global::obs_ea; // used for array observations adjustments
double  **Global::obs_rh; // used for array observations adjustments
double  **Global::obs_t_obs; // used for array observations adjustments

TObject *Global::thisVar;
