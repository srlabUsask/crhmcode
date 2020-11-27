//created by Manishankar Mondal

#include "ClassModule.h"

class Classglacier_debris : public ClassModule {
public:

Classglacier_debris(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " ,snowmeltD"){};

long ObsCnt_Albedo {0};

// declared observation variables
const double *Qnsn{ NULL };
const double *QnD{ NULL };

// declared variables
double *SWEmelt{ NULL };         // SWE snowmelt
double *SWEmelt_delayed{ NULL }; // SWE snowmelt delayed
double *cumSWEmelt{ NULL };      // cumulative SWE snowmelt (same as snowmeltD_org}
double *firnmelt{ NULL };         // firn snowmelt
double *firnmelt_delayed{ NULL }; // firn snowmelt delayed
double *cumfirnmelt{ NULL };      // cumulative firn snowmelt runoff
double *icemelt{ NULL };         // ice melt
double *icemelt_delayed{ NULL }; // ice melt delayed
double *cumicemelt{ NULL };      // cumulative ice melt runoff
double *cumnet_rain_glacier{ NULL }; // cumulative net_rain + firn and ice melt
double *cumsnowmeltD_glacier{ NULL }; // cumulative snowmeltD + firn and ice melt

double *glacier_Albedo{ NULL };
double *glacier_h2o{ NULL };
double *glacier_Surf{ NULL };
double *firn{ NULL };
double *firn_depth{ NULL };
double *firn_init{ NULL };
double *firn_h{ NULL };
double **firn_h_array{ NULL };
double *firn_yr{ NULL };
double **firn_yr_array{ NULL };
double *firn_dens{ NULL };
double **firn_dens_array{ NULL };
double *SWE_2firn{ NULL };
double *cumSWE_2firn{ NULL };
double *SWE_2firn_dens{ NULL };
double *firn_2ice{ NULL };
double *cumfirn_2ice{ NULL };
double *firn_2ice_dens{ NULL };

double *Qmelt{ NULL };
double *Xmelt_int{ NULL };
double *Xmelt_acc{ NULL };
double *Xmelt_V5{ NULL };
double *cumQmelt{ NULL };
double *ice{ NULL };
double *Qn_ebsm{ NULL };
double *Qh_ebsm{ NULL };
double *Qe_ebsm{ NULL };
double *Qp_ebsm{ NULL };
double *Qnsn_Acc{ NULL };

double *Gnet_rainD{ NULL };
double *net_rain_org{ NULL };
double *cumnet_rain_org{ NULL };
double *SWE{ NULL };
double *topo_elev{ NULL };
double *glacier_depth{ NULL };
double *rho_snow{ NULL };
long *nfirn{ NULL };
long *GlacierMode{ NULL }; // 0 - glacier, 1 - tongue

// declared put variable
double *Pa{ NULL };
double *net_rain{ NULL };
double *Albedo{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *tfactor{ NULL };
const double *nfactor{ NULL };
const double *Use_QnD{ NULL };
const double *firn_Albedo{ NULL };
const double *ice_init{ NULL };
const double *ice_Albedo{ NULL };
const double *ice_dens{ NULL };
const double *TKMA{ NULL };
const double *SWEAA{ NULL };
const double *SWEstorage{ NULL };
const double *SWELag{ NULL };
const double *firnstorage{ NULL };
const double *firnLag{ NULL };
const double *icestorage{ NULL };
const double *iceLag{ NULL };
const double *topo_elev_init{ NULL };

const double *firn_h_init{ NULL };
const double **firn_h_array_init{ NULL };
const double *firn_dens_init{ NULL };
const double **firn_dens_array_init{ NULL };
const long  *Elev_Adj_glacier_surf{ NULL };
const long  *delay_melt{ NULL };
const long  *SWE_to_firn_Julian{ NULL };
const long  *inhibit_evap{ NULL };
const long  *inhibit_firnmelt{ NULL };
const long  *inhibit_icemelt{ NULL };
const long  *Densification{ NULL };
const double *Densification_550{ NULL };
const double *Densification_above_550{ NULL };

const double* debris_h{ NULL }; // not variation 4
const double* T_threshold{ NULL }; // not variation 4
const double* lagT1{ NULL }; // not variation 4
const double* lagT2{ NULL }; // not variation 4
const double* lagT3{ NULL }; // not variation 4
const double* lagT4{ NULL }; // not variation 4
const double* lagSW1{ NULL }; // not variation 4
const double* lagSW2{ NULL }; // not variation 4
const double* lagSW3{ NULL }; // not variation 4
const double* lagSW4{ NULL }; // not variation 4
const double* lagSW5{ NULL }; // not variation 4
const double* lagSW6{ NULL }; // not variation 4

// declared variables

double* lagTB{ NULL };  // not variation 4
double* lagT{ NULL };  // not variation 4
double* lagSW{ NULL }; // not variation 4
double* Gmelt_energy{ NULL }; // not variation 4
double* den_air{ NULL }; // not variation 4
double* K_kat{ NULL }; // not variation 4
double* Cp_water{ NULL }; // not variation 4

// declared put parameters
double *hru_elev{ NULL };
double *snowmeltD{ NULL };

// variable inputs
const double *tmean{ NULL };
const double *tmax{ NULL };
const double *tmin{ NULL };
const double *umean{ NULL };
const double *rhmean{ NULL };
const double *sunact{ NULL };
const double *QdroD{ NULL };
const double *QdfoD{ NULL };
const double *sunmax{ NULL };
const double *Qnsn_Var{ NULL };
const double *Xmelt{ NULL };
const double *hru_t{ NULL }; // variation 5
const double *T_rain{ NULL }; // variation 5
const double *hru_ea{ NULL }; // variation 5
const double *glacier_Albedo_obs{ NULL };

ClassClark *SWEDelay{ NULL };
ClassClark *firnDelay{ NULL };
ClassClark *iceDelay{ NULL };

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier_debris* klone(string name) const;
double DepthofSnow(double SWE);
};