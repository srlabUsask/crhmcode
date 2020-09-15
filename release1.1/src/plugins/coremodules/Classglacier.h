//created by Manishankar Mondal

#include "ClassModule.h"

class Classglacier : public ClassModule {
public:

Classglacier(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " ,snowmeltD"){};

long ObsCnt_Albedo;

// declared observation variables
const float *Qnsn;
const float *QnD;

// declared variables
float *SWEmelt;         // SWE snowmelt
float *SWEmelt_delayed; // SWE snowmelt delayed
float *cumSWEmelt;      // cumulative SWE snowmelt (same as snowmeltD_org}
float *firnmelt;         // firn snowmelt
float *firnmelt_delayed; // firn snowmelt delayed
float *cumfirnmelt;      // cumulative firn snowmelt runoff
float *icemelt;         // ice melt
float *icemelt_delayed; // ice melt delayed
float *cumicemelt;      // cumulative ice melt runoff
float *cumnet_rain_glacier; // cumulative net_rain + firn and ice melt
float *cumsnowmeltD_glacier; // cumulative snowmeltD + firn and ice melt

float *glacier_Albedo;
float *glacier_h2o;
float *glacier_Surf;
float *firn;
float *firn_depth;
float *firn_init;
float *firn_h;
float **firn_h_array;
float *firn_yr;
float **firn_yr_array;
float *firn_dens;
float **firn_dens_array;
float *SWE_2firn;
float *cumSWE_2firn;
float *SWE_2firn_dens;
float *firn_2ice;
float *cumfirn_2ice;
float *firn_2ice_dens;

float *Qmelt;
float *cumQmelt;
float *ice;
float *Qn_ebsm;
float *Qh_ebsm;
float *Qe_ebsm;
float *Qp_ebsm;
float *Qnsn_Acc;

float *Gnet_rainD;
float *net_rain_org;
float *cumnet_rain_org;
float *SWE;
float *topo_elev;
float *glacier_depth;
float *rho_snow;
long *nfirn;
long *GlacierMode; // 0 - glacier, 1 - tongue

// declared put variable
float *Pa;
float *net_rain;
float *Albedo;

// declared parameters
const float *basin_area;   // [BASIN]
const float *hru_area;
const float *tfactor;
const float *nfactor;
const float *Use_QnD;
const float *firn_Albedo;
const float *ice_init;
const float *ice_Albedo;
const float *ice_dens;
const float *TKMA;
const float *SWEAA;
const float *SWEstorage;
const float *SWELag;
const float *firnstorage;
const float *firnLag;
const float *icestorage;
const float *iceLag;
const float *topo_elev_init;

const float *firn_h_init;
const float **firn_h_array_init;
const float *firn_dens_init;
const float **firn_dens_array_init;
const long  *Elev_Adj_glacier_surf;
const long  *delay_melt;
const long  *SWE_to_firn_Julian;
const long  *inhibit_evap;
const long  *inhibit_firnmelt;
const long  *inhibit_icemelt; 
const long  *Densification;
const float *Densification_550;
const float *Densification_above_550;

// declared put parameters
float *hru_elev;
float *snowmeltD;

// variable inputs
const float *tmean;
const float *tmax;
const float *tmin;
const float *umean;
const float *rhmean;
const float *sunact;
const float *QdroD;
const float *QdfoD;
const float *sunmax;
const float *Qnsn_Var;
const float *Xmelt;
const float *glacier_Albedo_obs;

ClassClark *SWEDelay;
ClassClark *firnDelay;
ClassClark *iceDelay;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier* klone(string name) const;
float DepthofSnow(float SWE);
};