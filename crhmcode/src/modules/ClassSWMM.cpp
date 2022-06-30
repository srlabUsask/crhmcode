//created by Peter Lawford

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include <dlfcn.h>

#include "ClassSWMM.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassSWMM* ClassSWMM::klone(string name) const{
  return new ClassSWMM(name);
}

void ClassSWMM::decl(void) {

  Description = "'Calls SWMM to handle the routing of surface runoff from RBs (representative basins).'";

// Maybe TDim::ONE is bettern than TDIM::BASIN
//  swmm_config = declparam("swmm_config", TDim::BASIN, "Basin", "SWMM configuration file name", swmm_config);
//  swmm_report = declparam("swmm_report", TDim::BASIN, "Basin", "SWMM report file name", swmm_report);

  swmm_config_filename = decldiagparam("swmm_config", TDim::ONE, "' ', ' ', ' '",
                "Filename for SWMM configuration", swmm_config_filename);
  swmm_report_filename = decldiagparam("swmm_report", TDim::ONE, "' ', ' ', ' '",
                "Filename for SWMM output report", swmm_report_filename);

  inflowCnt = declgrpvar("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", &rew, &inflow_All);
  //gwCnt     = declgrpvar("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", &gwrew, &gw_All);
  inflow_mWQCnt = declgrpvar("WS_ALL_inflow_mWQ", "basinflow_mWQ", "query variable = 'basinflow_mWQ'", "(mg/l)", &rew_mWQ, &inflow_mWQ_All);

  declvar("WS_outflow", TDim::NHRU, "outflow of each RB", "(m^3/int)", &outflow);
  declvar("WS_outflow_mWQ", TDim::NDEFN, "Concentration: outflow of each RB", "(kg/int)", &outflow_mWQ, &outflow_mWQ_lay, numsubstances);

//  declparam("injection_nodes", TDim::NHRU, "[0]", "0","1000", "SWMM nodes to inject into", "()", &injection_nodes);
//  declparam("collection_nodes", TDim::NHRU, "[0]", "0","1000", "SWMM nodes to collect from", "()", &collection_nodes);

  injection_node_names  = declparam("injection_nodes", TDim::NHRU, "''", "injection node names", injection_node_names);
  collection_node_names = declparam("injection_nodes", TDim::NHRU, "''", "collection node names", collection_node_names);


}

void ClassSWMM::init(void) {

  if(nhru < inflowCnt) {
    CRHMException Except("Module REW route # of HRUs must be >= # of groups." , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  void *plugin = dlopen(library_filename, RTLD_NOW);
  if (!plugin)
  {
    string S = string("Cannot load ") + library_filename + 
              string(" : ") + dlerror();
    CRHMException Except(S.c_str() , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  _mapLibraryFunctions(plugin);

  if (swmm_config_filename->at(0).length() == 0) {
    CRHMException Except("(SWMM) Config file not specified" , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  if (swmm_report_filename->at(0).length() == 0) {
    CRHMException Except("(SWMM) Report file not specified" , TExcept::TERMINATE);
    LogError(Except);
    throw Except;
  }

  swmm_open(swmm_config_filename->at(0).c_str(),
            swmm_report_filename->at(0).c_str(),
            "");  // binary output filename is empty string, so no file created

  assert(inflowCnt == injection_node_names->size());
  assert(inflowCnt == collection_node_names->size());

  /*
   * Map SWMM node names to CRHM 'HRU's 
   */

  int n_swmm_nodes = swmm_getCount(swmm_NODE);

  int bufsz = 32;
  char buf[bufsz];

  injection_nodes = new int[inflowCnt];
  collection_nodes = new int[inflowCnt];

  for (int i=0; i<inflowCnt; i++) {
    if (injection_node_names->at(i).length() > 0) {
      bool matched = false;
      for (int j=0; j<n_swmm_nodes; j++) {
        swmm_getName(swmm_NODE, j, buf, bufsz);
        if ( strcmp(injection_node_names->at(i).c_str(), buf) == 0 ) {
          injection_nodes[i] = j;
          matched = true;
        }
      }

      if (!matched) {
        string S = string("Unmatched SWMM node name: ")+injection_node_names->at(i);
        CRHMException Except(S, TExcept::TERMINATE);
        LogError(Except);
        throw Except;
      }

    } else {
      injection_nodes[i] = -1;
    }    

    if (collection_node_names->at(i).length() > 0) {
      bool matched = false;
      for (int j=0; j<n_swmm_nodes; j++) {
        swmm_getName(swmm_NODE, j, buf, bufsz);
        if ( strcmp(collection_node_names->at(i).c_str(), buf) == 0) {
          collection_nodes[i] = j;
          matched = true;
        }
      }

      if (!matched) {
        string S = string("Unmatched SWMM node name: ")+collection_node_names->at(i);
        CRHMException Except(S, TExcept::TERMINATE);
        LogError(Except);
        throw Except;
      }
    } else {
      collection_nodes[i] = -1;
    }    
  }

// If using water quality, ensure that pollutants are defined in SWMM
  
  if ( (outflow_mWQ == NULL) || (outflow_mWQ_lay == NULL)) {
    calculate_wq = false;
    if (swmm_getCount(swmm_POLLUT) < 1) {
      string S = string("Pollutants were defined in SWMM config file, but no CRHM WQ modules were specified");
      CRHMException Except(S, TExcept::TERMINATE);
      LogError(Except);
      throw Except;
    }
  } else {
    if (swmm_getCount(swmm_POLLUT) < 1) {
      string S = string("No pollutants defined in SWMM config file, WQ results will not be correct");
      CRHMException Except(S, TExcept::WARNING);
      LogError(Except);
      throw Except;
      calculate_wq = false;
    } else {
      calculate_wq = true;
    }
  }

  // printf("Nodes: %d\n",swmm_getCount(swmm_NODE));
  // printf("Links: %d\n",swmm_getCount(swmm_LINK));

  // int bufsz = 32;
  // char buf[bufsz];
  // swmm_getName(swmm_NODE, 0, buf, bufsz);
  // printf("Node0: %s\n",buf);


  /*
   * Start up the SWMM model
   */

  swmm_start(true);
  swmm_elapsedTime = 0.0;



  // flow[0] = 0.0;
  // flow_s[0] = 0.0;
  // cumflow[0] = 0.0;

  // gwflow[0] = 0.0;
  // gwflow_s[0] = 0.0;
  // cumgwflow[0] = 0.0;

  for(hh = 0; hh < nhru; ++hh) {
  //   inflow[hh] = 0.0;
  //   cuminflow[hh] = 0.0;
    outflow[hh] = 0.0;
  //   cumoutflow[hh] = 0.0;
  //   gwinflow[hh] = 0.0;
  //   cumgwinflow[hh] = 0.0;
  //   gwoutflow[hh] = 0.0;
  //   cumgwoutflow[hh] = 0.0;
  }
}



void ClassSWMM::run(void) {

// Global::Interval is the length of each timestep in days
// elapsedTime (days)
  double crhm_elapsedTime = getstep() * Global::Interval;

// repeat until the time matches to CRHM time
  double prev_time = 0;
  do {

// inject flow values from CRHM into SWMM
    for(hh = 0; hh < nhru; ++hh){
      if (injection_nodes[hh] >= 0) {
        swmm_setValue(swmm_NODE_LATFLOW, injection_nodes[hh],
                    inflow_All[hh][0]*Global::Freq/86400.0);
        if (calculate_wq)
          swmm_setGroupValue(swmm_NODE_POLLUTANTMASS, 
                    injection_nodes[hh], 0, 7.0);
      }
    }


// Step the SWMM model
    prev_time = swmm_elapsedTime;
    int ErrorCode = swmm_step(&swmm_elapsedTime);
    if (ErrorCode != 0) {
      swmm_end();
      swmm_report();

      printf("SWMM error during timestep: err %d\n", ErrorCode);
      string S = "SWMM error during timestep";
      CRHMException Except(S , TExcept::TERMINATE);
      LogError(Except);
      throw Except;
    }

    if (prev_time >= swmm_elapsedTime) {
      printf("SWMM time stuck: err %d\n", ErrorCode);
      break;
    }

  } while (crhm_elapsedTime > swmm_elapsedTime);

// Collect the output flow data from SWMM back into CRHM 
  for(hh = 0; hh < nhru; ++hh) {
    if (collection_nodes[hh] >= 0) {

      outflow[hh] = swmm_getValue(swmm_NODE_INFLOW,collection_nodes[hh]) *
                        86400.0/Global::Freq;
      if (calculate_wq)
        outflow_mWQ_lay[0][hh] = swmm_getGroupValue(swmm_NODE_POLLUTANTMASS,
                        collection_nodes[hh], 0) * 86400.0/Global::Freq;
//        gwoutflow[hh] = swmm_getValue(swmm_NODE_LATFLOW, collection_nodes[hh]-1);
    }
  }


}



void ClassSWMM::finish(bool good) {
  // for(hh = 0; hh < inflowCnt; ++hh) {
  //   LogMessageA(hh, string("'" + Name + " (REW_route)' cuminflow          (m^3) (m^3): ").c_str(), cuminflow[hh], 1.0);
  //   LogMessageA(hh, string("'" + Name + " (REW_route)' cumoutflow         (m^3) (m^3): ").c_str(), cumoutflow[hh], 1.0);
  //   if(variation == VARIATION_ORG)
  //     LogMessageA(hh, string("'" + Name + " (REW_route)' inflowDelay_in_storage (m^3) (m^3): ").c_str(), inflowDelay->Left(hh), 1.0);
  //   else
  //     LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str(), Clark_inflowDelay->Left(hh), 1.0);

  //   LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwinflow  (m^3) (m^3): ").c_str(), cumgwinflow[hh], 1.0);
  //   LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwoutflow (m^3) (m^3): ").c_str(), cumgwoutflow[hh], 1.0);
  //   if(variation == VARIATION_ORG)
  //     LogMessageA(hh, string("'" + Name + " (REW_route)' gwDelay_in_storage (m^3) (m^3): ").c_str(), gwDelay->Left(hh), 1.0);
  //   else
  //     LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str(), Clark_gwDelay->Left(hh), 1.0);

  //   LogDebug(" ");
  // }

  // LogMessage(string("'" + Name + " (REW_route)' cumflow (m^3): ").c_str(), cumflow[0]);
  // LogMessage(string("'" + Name + " (REW_route)' cumgwflow (m^3): ").c_str(), cumgwflow[0]);
  // LogDebug(" ");

  swmm_end();
  swmm_report();
  swmm_close();

  delete injection_nodes;
  delete collection_nodes;

}


void ClassSWMM::_mapLibraryFunctions(void *plugin) {
  *(void**)(&swmm_run) = dlsym(plugin, "swmm_run");
  *(void**)(&swmm_open) = dlsym(plugin, "swmm_open");
  *(void**)(&swmm_start) = dlsym(plugin, "swmm_start");
  *(void**)(&swmm_step) = dlsym(plugin, "swmm_step");
  *(void**)(&swmm_end) = dlsym(plugin, "swmm_end");
  *(void**)(&swmm_report) = dlsym(plugin, "swmm_report");
  *(void**)(&swmm_close) = dlsym(plugin, "swmm_close");
  *(void**)(&swmm_getCount) = dlsym(plugin, "swmm_getCount");
  *(void**)(&swmm_getName) = dlsym(plugin, "swmm_getName");
  *(void**)(&swmm_getIndex) = dlsym(plugin, "swmm_getIndex");
  *(void**)(&swmm_getValue) = dlsym(plugin, "swmm_getValue");
  *(void**)(&swmm_setValue) = dlsym(plugin, "swmm_setValue");
  *(void**)(&swmm_setGroupValue) = dlsym(plugin, "swmm_setGroupValue");
  *(void**)(&swmm_getGroupValue) = dlsym(plugin, "swmm_getGroupValue");

  if ( (!swmm_run) || (!swmm_open) || (!swmm_start) || (!swmm_step)
           || (!swmm_end) || (!swmm_report) || (!swmm_close) || (!swmm_getCount)
            || (!swmm_getName)|| (!swmm_getIndex)|| (!swmm_getValue)
            || (!swmm_setValue) || (!swmm_setGroupValue) || (!swmm_getGroupValue ) ) {
      /* no such symbol */
      string S = string("'" + Name + " (SWMM) Error ") +
                  string(dlerror()) +
                  string("in HRU ") + to_string(hh+1);

      CRHMException Except(S.c_str() , TExcept::TERMINATE);
      LogError(Except);
      dlclose(plugin);
      throw Except;
  }
}