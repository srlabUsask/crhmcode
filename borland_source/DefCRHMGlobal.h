// 09/29/16
//---------------------------------------------------------------------------

#ifndef DEFCRHMGlobalH
#define DEFCRHMGlobalH
//---------------------------------------------------------------------------

#include "GlobalCommon.h"
#include "Common.h"

using namespace std;

class __declspec(dllimport) Global {
public:

  static bool Global::NaNcheck;
  static bool Global::LOGVARLOAD;

  static long GroupCntTrk;
  static long StructCntTrk;

  static long Freq;

  static long DTindx;
  static long DTmin;
  static long DTmax;
  static long IndxMin;
  static long IndxMax;

  static long maxobs;
  static long maxlay;
  static long maxhru;

  static long nobs;
  static long nlay;
  static long nhru;

  static long CRHMStatus;
  static long CurrentModuleRun;
  static long CRHMControlSaveCnt;

  static BitSet RunUpBitSet;
  static BitSet ModuleBitSet;

  static double Interval;
  static double DTstart;
  static double DTend;

  static TDateTime DTnow;

  static TDateTime RapidAdvanceTo;
  static TDateTime LoopTo;
  static long LoopCnt;
  static long LoopCntDown;

  static CRHM::TBuild BuildFlag;
  static CRHM::TIMEFORMAT TimeFormat;

  static MapVar MapVars;
  static MapVar MapVarsGet;
  static MapVar MapVarsPut;
  static MapVar MapObsGet;
  static MapPar MapPars;
  static MapPar SharedMapPars;

  static Mapstr Mapgetvar;
  static Mapstr Mapputvar;
  static Mapstr Mapreadvar;
  static Mapstr Mapdeclvar;
  static Mapstr Mapdeclpar;
  static Mapstr Mapdeclobs;
  static Mapstr Mapdeclstat; // state variable list
  static Mapstr2 MapAKA;

  static TStringList *AllModulesList;   // modules defined in CRHM
  static TStringList *OurModulesList;   // modules defined in current model
  static TStringList *MacroModulesList; // custom modules defined in current model
  static TStringList *AllModelsList;    // models defined in CRHM
  static TStringList *ModelModulesList; // modules used in above models in CommaText
  static TStringList *OurHelpList;      // help files defined in current modules
  static TStringList *PendingDLLModuleList; // modules defined in current DLL
  static TStringList *ReportList;           //
  static TStringList *DeclRootList;         //
  static TStringList *OldModuleName;        // used to upgrade module names
  static TStringList *NewModuleName;        // used to upgrade module names

  static HWND crhmMain;
  static HWND crhmLog;

  static float  * lapse_rate; // used for array observations adjustments
  static float  * ppt_adj; // used for array observations adjustments
  static float  * hru_elev; // used for array observations adjustments
//  static float  * obs_elev; // used for array observations adjustments

  static float  * Warming_t; // used for climate warming
  static float  * Warming_p; // used for climate warming
  static long   * RH_VP_flag; // used for elevation change. -> 0 maintain rh, 1 -> maintain ea
  static long   * RH_VP_flag2; // used for climate warming. -> 0 maintain rh, 1 -> maintain ea
  static long     RH_EA_obs; // 0 -> rh obs, 1 -> ea obs
  static long    OBS_AS_IS; // 0 -> process obs, 1 -> no processing
  static long    Global::WQ_prj; // true -> processing WQ modules

  static float  ** OBS_ELEV; // used for array observations adjustments
  static long   ** HRU_OBS; // used for array observations
  static long   ** HRU_OBS_DIRECT; // used for array observations
  static float  ** obs_t; // used for array observations adjustments
  static float  ** obs_ea; // used for array observations adjustments
  static float  ** obs_rh; // used for array observations adjustments
  static float  ** obs_t_obs; // used for array observations adjustments

  static TObject *thisVar;
  };

#endif
