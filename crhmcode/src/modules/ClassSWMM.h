//created by Peter Lawford

#include "../core/ClassModule.h"

/********************************************
 * Taken from swmm5.h
 */

typedef enum {
    swmm_GAGE     = 0,
    swmm_SUBCATCH = 1,
    swmm_NODE     = 2,
    swmm_LINK     = 3,
    swmm_SYSTEM   = 100
} swmm_Object;

typedef enum {
    swmm_NODE_TYPE     = 300,
    swmm_NODE_ELEV     = 301,
    swmm_NODE_MAXDEPTH = 302,
    swmm_NODE_DEPTH    = 303,
    swmm_NODE_HEAD     = 304,
    swmm_NODE_VOLUME   = 305,
    swmm_NODE_LATFLOW  = 306,
    swmm_NODE_INFLOW   = 307,
    swmm_NODE_OVERFLOW = 308,
    swmm_NODE_RPTFLAG  = 309
} swmm_NodeProperty;

/*********************************************/


class ClassSWMM : public ClassModule {
public:

ClassSWMM(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt{0};
// long gwCnt{0};

// declared variables
double *rew{ NULL };
// double *gwrew{ NULL };

double **inflow_All{ NULL };
// double **gw_All{ NULL };

// double *inflow{ NULL };        // [nhru]
// double *cuminflow{ NULL };     // [nhru]
double *outflow{ NULL };       // [nhru]
// double *cumoutflow{ NULL };    // [nhru]

// double *gwinflow{ NULL };        // [nhru]
// double *cumgwinflow{ NULL };     // [nhru]
// double *gwoutflow{ NULL };       // [nhru]
// double *cumgwoutflow{ NULL };    // [nhru]

// double *flow{ NULL };     // [BASIN] all HRUs
// double *flow_s{ NULL };   // [BASIN] all HRUs
// double *cumflow{ NULL };  // [BASIN] all HRUs

// double *gwflow{ NULL };     // [BASIN] all HRUs
// double *gwflow_s{ NULL };   // [BASIN] all HRUs
// double *cumgwflow{ NULL };  // [BASIN] all HRUs


const char * library_filename = "./libswmm5.so";
double swmm_elapsedTime;

// declared parameters

std::vector<std::string> * swmm_config_filename { NULL };
std::vector<std::string> * swmm_report_filename { NULL };


// const long  *injection_nodes{ NULL };           // [nhru]
// const long  *collection_nodes{ NULL };           // [nhru]

std::vector<std::string> * injection_node_names { NULL };
std::vector<std::string> * collection_node_names { NULL };

int *injection_nodes;
int *collection_nodes;

/*
 * SWMM (EPA version) API
 * N.B. The OVA version of SWMM is currently missing some functinality
 */

int    (* swmm_run)(const char *f1, const char *f2, const char *f3);
int    (* swmm_open)(const char *f1, const char *f2, const char *f3);
int    (* swmm_start)(int saveFlag);
int    (* swmm_step)(double *elapsedTime);
// int    DLLEXPORT swmm_stride(int strideStep, double *elapsedTime);
int    (* swmm_end)(void);
int    (* swmm_report)(void);
int    (* swmm_close)(void);

int    (* swmm_getCount)(int objType);
void   (* swmm_getName)(int objType, int index, char *name, int size);
int    (* swmm_getIndex)(int objType, const char *name);
double (* swmm_getValue)(int property, int index);
void   (* swmm_setValue)(int property, int index,  double value);



void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassSWMM* klone(string name) const;

private:
    void _mapLibraryFunctions(void *plugin);

};
