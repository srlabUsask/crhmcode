//created by Manishankar Mondal

#include "ClassModule.h"

class Classglacier_debris : public ClassModule {
public:

Classglacier_debris(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " ,snowmeltD"){};

long ObsCnt_Albedo;

// declared observation variables
const double *Qnsn;
const double *QnD;

// declared variables
double *SWEmelt;         // SWE snowmelt
double *SWEmelt_delayed; // SWE snowmelt delayed
double *cumSWEmelt;      // cumulative SWE snowmelt (same as snowmeltD_org}
double *firnmelt;         // firn snowmelt
double *firnmelt_delayed; // firn snowmelt delayed
double *cumfirnmelt;      // cumulative firn snowmelt runoff
double *icemelt;         // ice melt
double *icemelt_delayed; // ice melt delayed
double *cumicemelt;      // cumulative ice melt runoff
double *cumnet_rain_glacier; // cumulative net_rain + firn and ice melt
double *cumsnowmeltD_glacier; // cumulative snowmeltD + firn and ice melt

double *glacier_Albedo;
double *glacier_h2o;
double *glacier_Surf;
double *firn;
double *firn_depth;
double *firn_init;
double *firn_h;
double **firn_h_array;
double *firn_yr;
double **firn_yr_array;
double *firn_dens;
double **firn_dens_array;
double *SWE_2firn;
double *cumSWE_2firn;
double *SWE_2firn_dens;
double *firn_2ice;
double *cumfirn_2ice;
double *firn_2ice_dens;

double *Qmelt;
double *Xmelt_int;
double *Xmelt_acc;
double *Xmelt_V5;
double *cumQmelt;
double *ice;
double *Qn_ebsm;
double *Qh_ebsm;
double *Qe_ebsm;
double *Qp_ebsm;
double *Qnsn_Acc;

double *Gnet_rainD;
double *net_rain_org;
double *cumnet_rain_org;
double *SWE;
double *topo_elev;
double *glacier_depth;
double *rho_snow;
long *nfirn;
long *GlacierMode; // 0 - glacier, 1 - tongue

// declared put variable
double *Pa;
double *net_rain;
double *Albedo;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *tfactor;
const double *nfactor;
const double *Use_QnD;
const double *firn_Albedo;
const double *ice_init;
const double *ice_Albedo;
const double *ice_dens;
const double *TKMA;
const double *SWEAA;
const double *SWEstorage;
const double *SWELag;
const double *firnstorage;
const double *firnLag;
const double *icestorage;
const double *iceLag;
const double *topo_elev_init;

const double *firn_h_init;
const double **firn_h_array_init;
const double *firn_dens_init;
const double **firn_dens_array_init;
const long  *Elev_Adj_glacier_surf;
const long  *delay_melt;
const long  *SWE_to_firn_Julian;
const long  *inhibit_evap;
const long  *inhibit_firnmelt;
const long  *inhibit_icemelt;
const long  *Densification;
const double *Densification_550;
const double *Densification_above_550;

const double* debris_h; // not variation 4
const double* T_threshold; // not variation 4
const double* lagT1; // not variation 4
const double* lagT2; // not variation 4
const double* lagT3; // not variation 4
const double* lagT4; // not variation 4
const double* lagSW1; // not variation 4
const double* lagSW2; // not variation 4
const double* lagSW3; // not variation 4
const double* lagSW4; // not variation 4
const double* lagSW5; // not variation 4
const double* lagSW6; // not variation 4

// declared variables

double* lagTB;  // not variation 4
double* lagT;  // not variation 4
double* lagSW; // not variation 4
double* Gmelt_energy; // not variation 4
double* den_air; // not variation 4
double* K_kat; // not variation 4
double* Cp_water; // not variation 4

// declared put parameters
double *hru_elev;
double *snowmeltD;

// variable inputs
const double *tmean;
const double *tmax;
const double *tmin;
const double *umean;
const double *rhmean;
const double *sunact;
const double *QdroD;
const double *QdfoD;
const double *sunmax;
const double *Qnsn_Var;
const double *Xmelt;
const double *hru_t; // variation 5
const double *T_rain; // variation 5
const double *hru_ea; // variation 5
const double *glacier_Albedo_obs;

ClassClark *SWEDelay;
ClassClark *firnDelay;
ClassClark *iceDelay;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier_debris* klone(string name) const;
double DepthofSnow(double SWE);
};