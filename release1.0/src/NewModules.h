// 11/28/19
//---------------------------------------------------------------------------

#ifndef OurModulesH
#define OurModulesH
//---------------------------------------------------------------------------

//#include "ClassModule.h"
#include "ClassModule.h"
//#include "WQ_CRHM.h"
//#include "WQ_Soil_NPCcycling.h"
#include <stack>
#include <queue>

using namespace std;

extern "C" void  MoveModulesToGlobal(string DLLName = "CRHM");

double DepthofSnow(double SWE);
double SWEfromDepth(double Snow_Depth);
void ProbabilityThresholdNew(double SWE, double t, double Uten_Prob, double & Probability, double & Threshold, long Snow, double & SnowAge, long & DrySnow);
void Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH);
void Pbsm (double E_StubHt, double Uthr, double & DriftH, double & SublH,
           double t, double u, double rh, double Fetch, long N_S, double A_S);

class Classshared : public ClassModule {
public:

Classshared(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);

Classshared* klone(string name) const;
};

class ClassNOP : public ClassModule {
public:

ClassNOP(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

// declared variables

void decl(void);
void init(void);
void finish(bool good);

ClassNOP* klone(string name) const;
};

class Classbasin : public ClassModule {
public:

Classbasin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const double *Meyer_B;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;
TStringList *RapidAdvance_to;
TStringList *Loop_to;
TStringList *StateVars_to_Update;
TStringList *TraceVars;

//declared variables
long *run_ID;

void decl(void);
void init(void);

Classbasin* klone(string name) const;
};

class Classglobal : public ClassModule {
public:

Classglobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QdroD;
double *QdroDext;
double *QdfoD;
double *Qdro;
double *Qdfo;
double *Qdflat;
double *QdflatD;
double *QdflatE;
double *SolAng;
double *SunMax;
double *cosxs;
double *cosxsflat;
double *pQdro;
double **pQdro_FREQ;
double *pQdfo;
double **pQdfo_FREQ;
double *pQdflat;
double **pQdflat_FREQ;
double *pQdflatE;
double **pQdflatE_FREQ;
double *pSol;
double **pSol_FREQ;
double *pCosxs;
double **pCosxs_FREQ;
double *pCosxs0;
double **pCosxs0_FREQ;

// declared parameters
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;
const double *Time_Offset;

//const long  *Extra;

// variable inputs

void air_mass (const double czen, double &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};

class Classobs : public ClassModule {
public:

Classobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Exist;
long Exist2;

// declared observation variables
const double *p;      // interval data
const double *ppt;    // daily data
const double *t;
double **tday_intvls;
const double *rh;
double **rhday_intvls;
const double *ea;
double **eaday_intvls;
const double *u;
const double *t_max;
const double *t_min;
const double *obs_snow;
const double *obs_rain;

// declared observation functions
double *tmean;
double *tmin;
double *tmax;
double *umean;
double *pptD;
//double *p;      // interval data
double *NotUsed;

// declared variables
double *hru_t;
double *hru_rh;
double *hru_ea;
double *hru_estar;
double *hru_u;
double *hru_p;
// double *hru_icebulb;
double *Pa;
double *DTnow;
long  *DTindx;
double *hru_rain;
double *cumhru_rain;
double *hru_snow;
double *cumhru_snow;
double *cumhru_snow_meas;
double *hru_tmax;
double *hru_tmin;
double *hru_tmean;
double *hru_eamean;
double *hru_umean;
double *hru_rhmean;

double *t_obs;
double **t_obs_lay;

long  *hru_newsnow;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *tmax_allrain;
const double *tmax_allsnow;
const double *lapse_rate;
const double *precip_elev_adj;
const double *hru_elev;
const double *ClimChng_t;
const double *ClimChng_precip;
const long  *catchadjust;
const long  *ppt_daily_distrib;
const long  *snow_rain_determination;
const long  *HRU_OBS;
const long  **HRU_OBS_Tables;
const double *obs_elev;
const double  **obs_elev_Tables;
const long  *ElevChng_flag;
const long  *ClimChng_flag;

// variable inputs

void decl(void);
void init(void);
void run(void);
void pre_run(void);
void Harder(void);
void finish(bool good);

Classobs* klone(string name) const;
};

class Classintcp : public ClassModule {
public:

Classintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *net_rain;
double *cumnet_rain;
double *cumnet_snow;
double *net_snow;
double *net_p;
double *intcp_evap;

// declared parameters
const double *basin_area;
const double *hru_area;

// variable inputs
const double *hru_rain;
const double *hru_snow;
const double *hru_p;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classintcp* klone(string name) const;
};

class Classpbsm : public ClassModule {
public:

Classpbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust") {};

double hru_u_;

// declared variables

double *SWE;
double *Subl;
double *Drift;
double *SublH;
double *DriftH;
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *cumSno;
double *Prob;
double *snowdepth;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *SnowAge;
double *SWE_Init;
double *rain_on_snow;
double *cumrain_on_snow;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const double *N_S;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;
const double *net_rain;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm* klone(string name) const;
};

class ClassNO_pbsm : public ClassModule {
public:

ClassNO_pbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
// declared variables
double *SWE;
double *cumSno;
double *snowdepth;

// declared parameters
const double *basin_area;
const double *hru_area;
const long *inhibit_evap;

// variable inputs
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassNO_pbsm* klone(string name) const;
};

class Classtsurface : public ClassModule {
public:

Classtsurface(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_tsf;
double *hru_tsf_D;
double *hru_tsf_acc;
double *n_factor;
double *n_factor_T;
double *Zdt_last;
double *SWE_tc;
double *SWE_density;
double *hru_t_D;
double *hru_T_s_D;
double *hru_t_acc;
double *hru_T_s_acc;

// put inputs
double *Zdt; // not used as put. Allows Classtsurface to load before ClassXG

// declared parameters
const double *W_a; // Williams
const double *W_b;
const double *W_c;
const double *W_d;

const double *n_factor_a; // Woo
const double *n_factor_b;
const double *n_factor_c;

// variable inputs
const double *SWE;
const double *hru_t;
const double *netD;
const double *z_s;
const double *rho;
const double *T_s;
const double *G;
const double *tmin;
const double *snowdepth;
const double *xx;

void decl(void);
void init(void);
void run(void);

Classtsurface* klone(string name) const;
};

class Classalbedo : public ClassModule {
public:

Classalbedo(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo;
double *net_snowD;  // daily value sum(newsnow)
long *meltflag;
long *winter;
long  *newsnowcnt;

// declared parameters
const double *Albedo_bare;
const double *Albedo_snow;
const double *hru_lat;

// variable inputs
const double *hru_tmax;
const double *hru_tmin;
const double *QdroD;
const double *SWE;
const double *net_snow;
const long  *hru_newsnow;

void decl(void);
void init(void);
void run(void);

Classalbedo* klone(string name) const;
};

class Classnetall : public ClassModule {
public:

Classnetall(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *t;
const double *ea;
const double **tday_intvls;
const double **eaday_intvls;
const double *NotUsed;

// declared variables
double *net;
double *Rn; // net converted to mm
double *netD;
double *RnD; // netD converted to mm
double *RnD_POS;
double *cum_net;

// declared parameters

// variable inputs
const double *hru_t;
const double *hru_ea;
const double *Albedo;
const double *hru_SunAct;
const double *SunMax;
const double *Qdro;
const double *Qdfo;
const double *pQdro;
const double *pQdfo;
const double **pQdro_FREQ;
const double **pQdfo_FREQ;

void decl(void);
void init(void);
void run(void);

Classnetall* klone(string name) const;
};

class Classebsm : public ClassModule {
public:

Classebsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , Qnsn_Var, , "){};

// declared observation variables
const double *Qnsn;
const double *QnD;

// declared variables
double *snowmeltD;
double *cumsnowmelt;
double *LW_ebsm;
double *u_ebsm;
double *Qmelt;
double *Qn_ebsm;
double *Qh_ebsm;
double *Qe_ebsm;
double *Qe_subl;
double *cumQe_subl;
double *Qp_ebsm;
double *Qnsn_Acc;

double *LWmax;
double *net_rainD;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *tfactor;
const double *nfactor;
const double *Use_QnD;

// variable inputs
double *SWE;
const double *tmean;
const double *tmax;
const double *tmin;
const double *umean;
const double *rhmean;
const double *net_rain;
const double *Albedo;
const double *sunact;
const double *QdroD;
const double *QdfoD;
const double *sunmax;
const double *Qnsn_Var;

const long  *meltflag;
const long  *delay_melt;
const long  *Qe_subl_from_SWE;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classebsm* klone(string name) const;
};

class ClassTs : public ClassModule {

    public:

    ClassTs(string Name, string Version = "Radiation", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "QliVt_Var, ") {};

// declared observations
    double *Ts;

// declared observation variables

    const double *hru_u;

    const double *hru_t;

    const double *hru_rh;

    const double *Qli;

    const double *QliVt_Var;

// declared variables

   double *hru_Ts;

   double *Pa;

   double *q;

   double *ra;

   double *Qli_;

// declared parameters

   const double *Ht;

   const double *Zref;

   const double *Zwind;

   const double *hru_elev;

   const double *Z0snow; // snow roughness length (m)

// variable inputs


    void decl(void);
    void init(void);
    void run(void);

ClassTs* klone(string name) const;
};

class ClassNeedle : public ClassModule {

    public:

    ClassNeedle(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

    double Qli_;

    double Qsi_;

// declared observations

    double *Ts;

    double *Qnsn;

    double *Qsisn;

    double *Qlisn;

    double *Qlosn;

// declared observation variables

    const double *Qsi;

    const double *Qli;

    const double *QsiA_Var;

    const double *QsiS_Var;

    const double *QliVt_Var;

// declared variables

   double *Pa;

   double *k;

   double *Tauc;

   double *ra;

   double *Qnsn_Var;

// declared parameters

   const double *LAI;

   const double *Ht;

   const double *Zwind;

   const double *Zref;

   const double *hru_elev;

   const double *Z0snow; // snow roughness length (m)


// variable inputs

    const double *beta;

    const double *SWE;

    const double *Albedo;

    const double *hru_t;

    const double *hru_u;

    const double *hru_ea;

    const double *hru_rh;


    void decl(void);

    void init(void);

    void run(void);

ClassNeedle* klone(string name) const;
};

class ClassSimpleRichard : public ClassModule {

    public:

    ClassSimpleRichard(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables

    const double *Qsi;  // Downward shortwave radiation (W/m2)
    const double *Qli;  // Downward longwave radiation (W/m2)
    const double *snow; // Snowfall (kg/m2/s)
    const double *t;    // Air temperature (°K)
    const double *u;    // Wind speed (m/s)
    const double *rh;   // Relative humidity (%)

// declared variables

    double *SWE;       // (kg/m2)
    double *alb;       // Snow albedo
    double *snowmelt;  // (kg/m2)
    double *meltclark; // (kg/m2)
    double *sursubl;   // (kg/m2)
    double *T0;   // Surface temperature (°K)

    double *LE;   // Latent heat flux (W/m^2)
    double *H;    // Sensible heat flux (W/m^2)
    double *Hsm;  // Snowmelt heat flux (W/m^2)
    double *LWn;  // Net longwave radiation (W/m^2)
    double *SWn;  // Net shortwave radiation (W/m^2)

// declared parameters

    const double *a1;   // Albedo decay time constant for cold snow (s)
    const double *a2;   // Albedo decay time constant for melting snow (s)
    const double *amin; // Minimum albedo for aged snow
    const double *amax; // Maximum albedo for fresh snow
    const double *smin; // Minimum snowfall to refresh snow albedo (mm)
    const double *Ht;   // Roughness length
    const double *Zref;   // Reference height
    const double *Pa;   // Average surface pressure (KPa)
    const double *Kstorage; // [nhru]
    const double *Lag;      // [nhru]
    const double *Z0snow;   // snow roughness length (m)

// variable inputs

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good);

    ClassSimpleRichard* klone(string name) const;

    void EXCH(long hh, double Q1, double U1, double &CH);

    void ALBEDO(long hh);

    void SURF(long hh, double Q1, double U1);

// local class

    ClassClark *Delays;

    double dt;
};

class Classevap : public ClassModule {
public:

Classevap(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *hru_evap_PT;
double *evapD;
double *cum_evap;
double *evapGrangerD;
double *G;
double *D;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *hru_elev;
const double *F_Qg;
const double *rs;
const double *Zwind;

const long *evap_type;
const long *inhibit_evap;
const long *inhibit_evap_User;

// variable inputs
const double *Rn;
const double *RnD;
const double *RnD_POS;
const double *hru_t;
const double *hru_u;
const double *hru_ea;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};

class ClassevapD : public ClassModule {
public:

ClassevapD(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evapD;
double *cum_evap;
double *G;
double *D;

// local allocated arrays
double *Pa;


// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *hru_elev;
const double *F_Qg;

const long *evap_type;
const long *inhibit_evap;

// variable inputs
const double *RnD;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;

// variable puts

// declared observations variable

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};

class Classsbsm : public ClassModule {
public:

Classsbsm(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001), // setting PeerRank =1
                                  hru_basin(NULL) {};
double dt;

// declared variables
double *SWE;
double *wet_snow;
double *Subl;
double *Drift;
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *cumSno;
double *Prob;
double *snow_age;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *snowdepth;

// declared parameters
const double *basin_area;
const double *hru_area;
const double *Ht;
const double *zr;
const double *distrib;
const double *fetch;
const long *inhibit_evap;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classsbsm* klone(string name) const;

double transport(void);
double sublimation(void);
double scale(void);
void  prob(void);
};

class Classcrack : public ClassModule {
public:

Classcrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *snowinfil;
double *cumsnowinfil;
double *infil;
double *cuminfil;
double *meltrunoff;
double *cummeltrunoff;
double *runoff;
double *cumrunoff;
double *RainOnSnow;
double *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *fallstat;
const double *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;

// variable inputs
const double *hru_tmax;
const double *snowmelt;
const double *SWE;
const double *net_rain;

// local allocated arrays
double **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcrack* klone(string name) const;
};

class ClassKevin : public ClassModule {
public:

ClassKevin(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   SWEpeak(NULL),
                                   SWElast(NULL) {};
// declared observation variables

// declared variables
double *albedo;
double *sca;
double *snowmelt;
double *snowmeltD;
double *cumsnowmelt;
double *netLong;
double *netShort;
long  *winter;
long  *SnowStat;

// declared parameters
const double *Asnow1;
const double *Asnow2;
const double *Asoil;
const double *cv;
const double *tfactor;
const double *nfactor;
const double *meltthresh;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;

// variable inputs
double *SWE;
const double *hru_t;
const double *hru_tmean;
const double *hru_eamean;
const double *hru_Qn;
const double *hru_SunAct;
const double *Qdro;
const double *Qdfo;
const double *SunMax;

// local allocated arrays
double   *SWEpeak;
double   *SWElast;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassKevin* klone(string name) const;
};

class ClassGreencrack : public ClassModule {
public:

ClassGreencrack(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *infil;
double *cuminfil;
double *meltrunoff;
double *cummeltrunoff;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
long  *crackstat;
long  *crackon;
double *RainOnSnow;
double *RainOnSnowA;

// local variables
double *k;
double *F0;
double *f0;
double *F1;
double *f1;
double *dthbot;
double *psidthbot;
long  *timer;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *fallstat;
const double *Major;      // threshold for major melt event(default is 5 mm/day)
const double *soil_moist_max;
const double *soil_moist_init;
const long  *soil_type;
const long  *PriorInfiltration;

// variable inputs
const double *hru_tmax;
const double *snowmelt;
const double *SWE;
const double *net_rain;
double *soil_moist; // changed tp PUT

// class allocated
double garain;      // precipitation/int
double intensity;   // precipitation/int converted to mm/h
double pond;        // mm

// class allocated arrays
double **Xinfil; // [3] [nhru]

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreencrack* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};

class Classfrostdepth : public ClassModule {
public:

Classfrostdepth(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                        k_lay(NULL),
                                        L_lay(NULL),
                                        c_lay(NULL),
                                        Lacc(NULL),
                                        Cacc(NULL),
                                        Kacc(NULL) {};
// declared variables
double *Findex;   // freezing index (days * frost °C)
long *Tfreeze;   // duration of freezing period in days
double *frostdepth;

// declared parameters
const double *Ta;        // mean annual air temperature
const double *d;         // depth of layer  m
const double **d_lay;    // depth of layer  m
const double *por;       // porosity m3/m3
const double **por_lay;  // porosity m3/m3
const double *theta;       // theta m3/m3  theta/porosity
const double **theta_lay;  // theta m3/m3
const long  *soil_type;
const long  **soil_type_lay;
const double *hru_lat;

// variable inputs
const double *hru_tmean;  // daily average temperature (°C)
const double *SWE;
const double *snowdepth;

// local allocated arrays
double **k_lay;    // J/(m.K.s)
double **L_lay;    // MJ/m3
double **c_lay;    // MJ/(m3 K)
double *Lacc; // effective value
double *Cacc; // effective value
double *Kacc; // effective value

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classfrostdepth* klone(string name) const;
};

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

class ClassNetroute : public ClassModule {
public:

ClassNetroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *outflow_diverted; // [nhru]
double *cumoutflow_diverted; // [nhru]
double *cumoutflow;    // [nhru]
double *gwinflow;        // [nhru]
double *gwoutflow_diverted; // [nhru]
double *gwcumoutflow_diverted; // [nhru]
double *HRU_cumbasinflow; // [nhru]

double *ssrinflow;        // [nhru]
double *ssrcuminflow;     // [nhru]
double *ssroutflow;       // [nhru]
double *ssrcumoutflow;    // [nhru]

double *runinflow;        // [nhru]
double *runcuminflow;     // [nhru]
double *runoutflow;       // [nhru]
double *runcumoutflow;    // [nhru]

double *gwoutflow;       // [nhru]
double *gwcuminflow;    // [nhru]
double *gwcumoutflow;    // [nhru]

double *basinflow;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_gw_Buf;     // buffered

double *cum_to_Sd;         // [nhru]
double *cum_to_soil_rechr; // [nhru]
double *cum_preferential_flow_to_gw;

ClassClark *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const double *Kstorage;         // [nhru]
const double *Lag;              // [nhru]
const double *ssrKstorage;      // [nhru]
const double *ssrLag;           // [nhru]
const double *runKstorage;      // [nhru]
const double *runLag;           // [nhru]
const double *gwKstorage;      // [nhru]
const double *gwLag;           // [nhru]

const double *basin_area;        // [BASIN]
const double *hru_area;          // [nhru]
const long  *whereto;           // [nhru]
const long  *order;             // [nhru]
const long  *gwwhereto;             // [nhru]
const double *Sdmax;             // [nhru]
const double *soil_rechr_max;    // [nhru]

const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *preferential_flow; // [nhru]

// variable inputs
const double *soil_gw;   // [nhru]
const double *soil_ssr;    // [nhru]
const double *soil_runoff; // [nhru]

// variable puts
double *Sd;
double *soil_moist;
double *soil_rechr;
double *redirected_residual;
double *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute* klone(string name) const;
};

class Classinterception : public ClassModule {
public:

Classinterception(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observations
const double *Qsi;

// variable inputs
const double *hru_t;
const double *hru_snow;
const double *hru_rain;
const double *hru_u;
const double *hru_rh;

// declared variables
double *SI_Lo;
double *net_snow;
double *net_rain;
double *SI_Subl;
double *Cum_Subl;
double *Cum_net_snow;
double *v;

// declared parameters
const double *Sbar;
const double *LAI;
const double *k;
const double *velw;
const double *Ht;
const double *WidthJ;
const double *basin_area;
const double *hru_area;

// variable inputs

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classinterception* klone(string name) const;
};

class ClassGreenAmpt : public ClassModule {
public:

ClassGreenAmpt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};
// declared variables
double *infil;
double *cuminfil;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
double *meltrunoff;
double *cummeltrunoff;

// local variables
double *k;
double *F0;
double *f0;
double *F1;
double *f1;
double *dthbot;
double *psidthbot;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *soil_moist_max;
const double *soil_moist_init;
const long  *soil_type;

// variable inputs
const double *net_rain;
const double *snowmelt;
double *soil_moist; // changed to PUT

// class allocated
double garain;      // precipitation/int
double intensity;   // precipitation/int converted to mm/h
double pond;        // mm

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassGreenAmpt* klone(string name) const;

void infiltrate(void);
void ponding(void);
void startponding(void);
void howmuch(double F0, double dt);

double calcf1(double F, double psidth);
};

class Classalbedoparam : public ClassModule {
public:

Classalbedoparam(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo;

// declared parameters
const double *Albedo_Value;

void decl(void);
void init(void);
void run(void);

Classalbedoparam* klone(string name) const;
};

class Classalbedoobs : public ClassModule {
public:

Classalbedoobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Albedo;

// declared observation variables
const double *Albedo_obs;      // interval data

// declared parameters
const double *Albedo_Value;

void decl(void);
void init(void);
void run(void);

Classalbedoobs* klone(string name) const;
};

class ClassHtobs : public ClassModule {
public:

ClassHtobs(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var;

// declared observation variables
const double *Ht_obs;      // interval data

// declared parameters
//const double *Ht;
double *Ht;

void decl(void);
void init(void);
void run(void);

ClassHtobs* klone(string name) const;
};

class TSTEP_REC{ // time step information
  public:

#define	DATA_TSTEP	   0
#define	NORMAL_TSTEP	   1
#define	MEDIUM_TSTEP	   2
#define	SMALL_TSTEP	   3

// default for normal run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_NORMAL_THRESHOLD  60.0

// default for medium run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_MEDIUM_THRESHOLD  10.0

// default for small run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_SMALL_THRESHOLD  1.0


  int level;	    // timestep's level

  long time_step;   // length of timestep (seconds)

  int intervals;    // # of these timestep that are in the previous-level's timestep (not used for level 0: data tstep)

  double threshold;  // mass threshold for a layer to use this timestep (not used for level 0: data tstep)

  TSTEP_REC() : level(0), time_step(24*3600/Global::Freq), intervals(1), threshold(0.0) {};

};

class  INPUT_REC{ // climate-data input records
  public:

  double S_n;	// net solar radiation (W/m^2)
  double I_lw;	// incoming longwave (thermal) rad (W/m^2)
  double T_a;	// air temp (C)
  double e_a;	// vapor pressure (Pa)
  double u;	// wind speed (m/sec)
  double T_g;	// soil temp at depth z_g (C)
  double F_g;	// soil flux at depth z_g (W/m^2)
};

class  PRECIP_REC{ // precip-data input records
  public:

  double	  m_pp;		// total precipitation mass (kg/m^2)
  double	  m_rain;	// mass of rain in precip   (kg/m^2)
  double	  m_snow;	// mass of snow in precip   (kg/m^2)
  double	  m_drift;	// mass of snow drift       (kg/m^2)
  double	  m_subl;	// mass of snow drift       (kg/m^2)
  double	  z_snow;	// depth of snow in precip  (m)
};

class ClassSnobalBase : public ClassModule {

    public:

    ClassSnobalBase(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables

//   snowpack information

    long*   layer_count;    // number of layers in snowcover: 0, 1, or 2
    double*  z_s;            // total snowcover thickness (m)
    double*  z_s_0;          // active layer depth (m)
    double*  z_s_l;          // lower layer depth (m)
    double*  rho;            // average snowcover density (kg/m^3)
    double*  m_s;            // snowcover's specific mass (kg/m^2). Init by init_snow.
    double*  m_s_0;          // active layer specific mass (kg/m^2). Init by init_snow.
    double*  m_s_l;          // lower layer specific mass (kg/m^2). Init by init_snow.
    double*  T_s;            // average snowcover temp (K). Init by init_snow
    double*  T_s_0;          // active snow layer temp (K)
    double*  T_s_l;          // lower layer temp (C)
    double*  cc_s;           // snowcover's cold content (J/m^2). Init by init_snow.
    double*  cc_s_0;         // active layer cold content (J/m^2). Init by init_snow.
    double*  cc_s_l;         // lower layer cold content (J/m^2). Init by init_snow.
    double*  h2o_sat;        // % of liquid H2O saturation (relative water content, i.e., ratio of water in snowcover
//                                 to water that snowcover could hold at saturation)
    double*  h2o_vol;        // liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless).init_snow
    double*  h2o;            // liquid h2o content as specific mass(kg/m^2)
    double*  h2o_max;        // max liquid h2o content as specific mass(kg/m^2)
    double*  h2o_total;      // total liquid h2o: includes h2o in snowcover, melt, and rainfall (kg/m^2)

//   energy balance info for current timestep

    double  *R_n;            // net allwave radiation (W/m^2)
    double  *H;              // sensible heat xfr (W/m^2)
    double  *L_v_E;          // latent heat xfr (W/m^2)
    double  *G;              // heat xfr by conduction & diffusion from soil to snowcover (W/m^2)
    double  *G_0;            // heat xfr by conduction & diffusion from soil or lower layer to active layer (W/m^2)
    double  *M;              // advected heat from precip (W/m^2)
    double  *delta_Q;        // change in snowcover's energy (W/m^2)
    double  *delta_Q_0;      // change in active layer's energy (W/m^2)

//   mass balance vars for current timestep

    double  *melt_direct_int;       // specific melt (kg/m^2 or m)
    double  *sum;       // specific melt (kg/m^2 or m)
    double  *SWE_change;       // interval change in SWE
    double  *E_int;	    // mass flux by evap into air from active layer (kg/m^2/s)
    double  *E_s_int;	    // mass of evap into air & soil from snowcover (kg/m^2)
    double  *snowmelt_int;   // predicted specific runoff (m/sec)
    double  *snowmeltD;      // daily predicted specific runoff (m/sec)
    double  *snowmeltD_acc;      // daily predicted specific runoff accumulator (m/sec)

//   mass balance vars for variable timestep

    double  *melt;        // specific melt (kg/m^2 or m)
    double  *E;		 // mass flux by evap into air from active layer (kg/m^2/s)
    double  *E_s;	 // mass of evap into air & soil from snowcover (kg/m^2)
    double  *ro_predict;  // predicted specific runoff (m/sec)

    double  *E_s_0;        // mass of evaporation to air (kg/m^2)
    double  *E_s_l;        // mass of evaporation to soil (kg/m^2)
    double  *E_l;	  // mass flux by evap/cond to soil (kg/m^2/s)

    double  *E_s_0_int;        // mass of evaporation to air (kg/m^2)
    double  *E_s_l_int;        // mass of evaporation to soil (kg/m^2)
    double  *E_l_int;	  // mass flux by evap/cond to soil (kg/m^2/s)

//   precipitation info adjusted for current run timestep

    double  *m_precip;	// specific mass of total precip (kg/m^2)
    double  *m_rain;	// specific mass of rain in precip (kg/m^2)
    double  *m_snow;	// specific mass in snow in precip (kg/m^2)
    double  *m_drift;	// specific mass in snow drift (kg/m^2)
    double  *m_subl;	// specific mass in snow sublimation (kg/m^2)
    double  *rho_snow;   // density of snowfall (kg/m^3)
    double  *T_pp;       // precip temp (K)
    double  *z_snow;	// depth of snow in precip (m)

//   precipitation info for the current DATA timestep

    long   *precip_now;	// precipitation occur for current timestep?
    double  *T_rain;	// rain's temp (K)
    double  *T_snow;	// snowfall's temp (K)
    double  *h2o_sat_snow; // snowfall's % of liquid H2O saturation

//   local climate-data values for the current run timestep
    double  *S_n;      // net solar radiation (W/m^2)
    double  *I_lw;     // incoming longwave (thermal) rad (W/m^2)
    double  *T_a;      // air temp (K)
    double  *e_a;      // vapor pressure (Pa)
    double  *u;        // wind speed (m/sec)
    double  *T_g;      // soil temp at depth z_g (C)
    double  *F_g;      // soil flux at depth z_g (W/m^2)

    long *isothermal; // melting?
    long *snowcover;  // snow on gnd at start of current timestep?
    long  *stop_no_snow;       //

//   local variables
    double  *P_a;            // air pressure (Pa)
    double  *m_precip_cum;   //
    double  *m_rain_cum;     //
    double  *m_snow_cum;     //
    double  *m_drift_cum;    //
    double  *m_subl_cum;    //
    double  *E_s_cum;        //
    double  *cumsnowmelt;    //
    double  *melt_direct_cum;       //
    double  *Fault;       //

// debug variables
/*    double *Length;
    double **Length_array;
    double *Ustar;
    double **Ustar_array;
    double *e;
    double **e_array;
    double *h;
    double **h_array;
    long *ier;
    long **ier_array;
    long  *ArrayCnt; */

// declared parameters

//   measurement heights/depths

    const double *hru_elev;    // HRU elevation
    const double *basin_area;  // [BASIN]
    const double *hru_area;
    const double *KT_sand; // thermal conductivity of wet sand

    const long *relative_hts; // true if measurements heights, z_T and z_u, are relative to snow surface
                              // false if they are absolute heights above the ground
    const double  *T_g_or_G_flux;    // soil temp or ground flux option
    const double *z_g;         // depth of soil temp meas (m)
    const double *z_u;         // height of wind measurement (m)
    const double *z_T;         // height of air temp & vapor pressure measurement (m)
    const double *z_0;         // roughness length
    const double *max_z_s_0;   // maximum active layer thickness (m)
    const double *max_h2o_vol; // max liquid h2o content as volume ratio: V_water/(V_snow - V_ice) (unitless)

//    void decl(void);

  void init(void);

//    void run(void);

  void finish(bool good); // delete local storage used

  void init_snow(void);

  void _calc_layers(void);

  void _layer_mass(void);

  double _cold_content(double	temp, double	mass); // temperature of layer specific mass of layer

  void do_data_tstep(void);

  int _divide_tstep(TSTEP_REC *tstep); // record of timestep to be divided

  int _below_thold(double threshold);	 // current timestep's threshold for a layer's mass

  int _do_tstep(TSTEP_REC *tstep); // timestep's record

  int _e_bal(void);

  void _net_rad(void);

  int _h_le(void);

  double g_soil(
  double	rho,	// snow layer's density (kg/m^3)
  double	tsno,	// snow layer's temperature (K)
  double	tg,	// soil temperature (K)
  double	ds,	// snow layer's thickness (m)
  double	dg,	// dpeth of soil temperature measurement (m)
  double	pa);	// air pressure (Pa)

  double g_snow(
  double	rho1,	// upper snow layer's density (kg/m^3)
  double	rho2,	// lower  "     "        "    (kg/m^3)
  double	ts1,	// upper snow layer's temperature (K)
  double	ts2,	// lower  "     "         "       (K)
  double	ds1,	// upper snow layer's thickness (m)
  double	ds2,	// lower  "     "         "     (m)
  double	pa);	// air pressure (Pa)

  void _advec(void);

  void _mass_bal(void);

  void _time_compact(void);

  void _precip(void);

  void _snowmelt(void);

  void _drift(void);

  void _new_density(void);

  void _adj_snow(double delta_z_s, double delta_m_s); // change in snowcover's depth change is snowcover's mass

  void _evap_cond(void);

  void _h2o_compact(void);

  void _adj_layers(void);

  void _runoff(void);

  double new_tsno(double spm, double t0, double ccon);

  double heat_stor(double cp, double spm, double tdif);

  double sati(double tk);

  double ssxfr(double  k1, double  k2, double  t1, double  t2, double  d1, double  d2);

  double efcon(double k, double t, double p);

  int hle1(double press, double ta, double ts, double za, double ea, double es, double zq, double u, double zu,
                   double z0, double &h, double &le, double &e);

// time step information

  TSTEP_REC  **tstep_info; 	// array of info for each timestep [nhru] [4]:
                                //           0 : data timestep
                                //           1 : normal run timestep
                                //           2 : medium  "     "
                                //           3 : small   "     "

  long *time_step;     // length current timestep (sec)
  long *current_time;  // start time of current time step (sec)

// climate-data input records

  INPUT_REC  *input_rec1;	// input data for start of data timestep [nhru]
  INPUT_REC  *input_rec2;	//   "     "   "  end   "   "      "     [nhru]

  INPUT_REC **input_deltas;	// deltas for climate-input parameters
                                //  over each timestep [nhru] [4]

  PRECIP_REC **precip_info;	// array of precip info adjusted for
                                //  each timestep [nhru] [4]

  int **computed;		// array of flags for each timestep;
                                //  true if computed values for input
                                //   deltas and precip arrays [nhru] [4]
};

class ClassSnobalX : public ClassSnobalBase {

    public:

    ClassSnobalX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalX* klone(string name) const;

// variable climate-data inputs

    const double  *S_n_X;      // net solar radiation (W/m^2)
    const double  *I_lw_X;     // incoming longwave (thermal) rad (W/m^2)
    const double  *T_a_X;      // air temp (C)
    const double  *e_a_X;      // vapor pressure (Pa)
    const double  *u_X;        // wind speed (m/sec)
    const double  *T_g_X;      // soil temp at depth z_g (C)
    const double  *F_g_X;      // soil flux at depth z_g ()

// variable precipitation inputs

    const double  *m_precip_X;	// specific mass of total precip     (kg/m^2)
    const double  *m_rain_X;	// specific mass of rain in precip   (kg/m^2)
    const double  *m_snow_X;	// specific mass in snow in precip   (kg/m^2)
    const double  *m_drift_X;	// specific mass in snow drift       (kg/m^2)
    const double  *m_subl_X;	// specific mass of snow sublimation (kg/m^2)
    const double  *rho_snow_X;   // density of snowfall               (kg/m^3)
    const double  *T_pp_X;       // precip temp (C)


    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};

class ClasspbsmSnobal : public ClassModule {
public:

ClasspbsmSnobal(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
double hru_u_;

// declared variables
double *Subl;
double *Drift;     // HRU composite drift
double *SublH;
double *DriftH;
double *Drift_out; // HRU drift out
double *Drift_in;  // HRU drift in
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *Prob;
double *snowdepth;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *SnowAge;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *distrib;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *N_S;
const double *u_D;
const double *Drift_offset;
const double *Drift_slope;
const double *Subl_offset;
const double *Subl_slope;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;

// variable inputs
const double *hru_t;
const double *hru_ea;
const double *hru_u;
const double *hru_Uadjust;
const double *net_snow;

// put variable inputs
double *SWE; // actually m_s
double *z_s;
double *rho;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClasspbsmSnobal* klone(string name) const;

};

class ClassalbedoRichard : public ClassModule {
public:

ClassalbedoRichard(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// local class

    double dt;

// declared variables
double *Albedo;

// put variables:

// get variables:

 const double *net_snow;
 const double *SWE;

const double *T0;

// declared parameters
  const double *Albedo_Bare;
  const double *Albedo_Snow;
  const double *a1;       // Albedo decay time constant for cold snow (s)
  const double *a2;       // Albedo decay time constant for melting snow (s)
  const double *amin;     // Minimum albedo for aged snow
  const double *amax;     // Maximum albedo for fresh snow
  const double *smin;     // Minimum snowfall to refresh snow albedo (mm)

void decl(void);
void init(void);
void run(void);

ClassalbedoRichard* klone(string name) const;
};

class ClassalbedoBaker : public ClassModule {
public:

ClassalbedoBaker(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo;
  double *Ab_t;

// get variables:


 const double *net_snow;
 const double *SWE;

// put variables:

// declared parameters
  const double *Albedo_Bare;
  const double *Albedo_Snow;
  const double *refresh;

void decl(void);
void init(void);
void run(void);

ClassalbedoBaker* klone(string name) const;
};

class ClassHMSA : public ClassModule {
public:

ClassHMSA(string Name = "HMSA", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " hru_t, "){};

double Soil_Temp;

long MaxFrontCnt;
long Liqcnt;
long Totcnt;

// declared observation variables
const double *Tsurf_obs;
const double *LiqWat;
const double *TotMoist;

// variable inputs
const double *Tsurf_var;
const double *hru_t;

//const double *theta;

// declared variables
double *Cum_Thaw;
double *Cum_Frozen;
double *Lamda_b;
double *Frozen_D;
double *Thaw_D;
double *Last_Tsurf;

double *C_K0;
double *Total_Moisture;
double **Total_Moisture_lay;
double *Cum_d;
double **Cum_d_lay;
long *Frozen_ID;
long **Frozen_ID_lay;
double *FrntDepth;
double **FrntDepth_array;
double *ThawCum;
double **ThawCum_array;
double *FreezeCum;
double **FreezeCum_array;
long *FrntDepthType;
long **FrntDepthType_array;
long *FrontCnt;

// local
double *Tsurface;

// declared parameters
const double *Alpha_T;
const double *Alpha_F;
const double *d_lay;
const double *BulkDensityLayer;
const double *InitThaw_D;
const double *InitFrozen_D;
const double *D_Top;
const double *TMPB_W;
const double **TMPB_W_NDEF;
const long *Alpha_ID;
const long *Soil_ID;
const long **Soil_ID_lay;

const double *Soil_Depths;
const double **Soil_depths_lay; // [nn][hh]
const double *Organic;
const double **Organic_lay; // [nn][hh]
const double *Porosity;
const double **Porosity_lay; // [nn][hh
const double *BulkDensity;
const double **BulkDensity_lay; // [nn][hh]
double *f;
double *Soil_Ice;
double **Soil_Ice_lay;
double *Soil_Water;
double **Soil_Water_lay;

const long *Soil_Layers;
const long *Method_ID;

void decl(void);
void init(void);
void run(void);
void Get_Heat_Param_Soil(double Soil_temp, long nn);
void Get_Heat_Chad(long nn);

ClassHMSA* klone(string name) const;
};

class Classwalmsley_wind : public ClassModule {
public:
Classwalmsley_wind(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_Uadjust;
double *hru_Uchange;
double *WR;

// declared parameters
const double *Zwind;
const double *Ax;
const double *Bx;
const double *L;
const double *Walmsley_Ht;

// varaible inputs
const double *hru_u;

void decl(void);
void init(void);
void run(void);

Classwalmsley_wind* klone(string name) const;
};

class ClassNetroute_M : public ClassModule {
public:

ClassNetroute_M(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *outflow_diverted; // [nhru]
double *cumoutflow_diverted; // [nhru]
double *cumoutflow;    // [nhru]
double *gwinflow;        // [nhru]

double *ssrinflow;        // [nhru]
double *ssrcuminflow;     // [nhru]
double *ssroutflow;       // [nhru]
double *ssrcumoutflow;    // [nhru]
double *HRU_cumbasinflow; // [nhru]

double *runinflow;        // [nhru]
double *runcuminflow;     // [nhru]
double *runoutflow;       // [nhru]
double *runcumoutflow;    // [nhru]

double *gwoutflow;       // [nhru]
double *gwoutflow_diverted; // [nhru]
double *gwcuminflow;     // [nhru]
double *gwcumoutflow;    // [nhru]
double *gwcumoutflow_diverted; // [nhru]

double *basinflow;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_gw_Buf;     // buffered

double *cum_to_Sd;         // [nhru]
double *cum_to_soil_rechr; // [nhru]

double *Ktravel;         // [nhru] Muskingum
double *cum_preferential_flow_to_gw;

ClassMuskingum *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const double *route_n;         // [nhru]
const double *route_R;         // [nhru]
const double *route_S0;        // [nhru]
const double *route_L;         // [nhru]
const double *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const double *Lag;              // [nhru]
const double *ssrKstorage;      // [nhru]
const double *ssrLag;           // [nhru]
const double *runKstorage;      // [nhru]
const double *runLag;           // [nhru]
const double *gwKstorage;       // [nhru]
const double *gwLag;            // [nhru]

const double *basin_area;        // [BASIN]
const double *hru_area;          // [nhru]
const long  *whereto;           // [nhru]
const long  *gwwhereto;         // [nhru]
const long  *order;             // [nhru]
const double *Sdmax;             // [nhru]
const double *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *preferential_flow; // [nhru]

// variable inputs
const double *soil_gw;     // [nhru]
const double *soil_ssr;    // [nhru]
const double *soil_runoff; // [nhru]

// variable puts
double *Sd;
double *soil_moist;
double *soil_rechr;
double *redirected_residual;
double *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute_M* klone(string name) const;
};

class ClassREWroute2 : public ClassModule {
public:

ClassREWroute2(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt;
long gwCnt;

// declared variables
double *rew;
double *gwrew;

double **inflow_All;
double **gw_All;

double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *cumoutflow;    // [nhru]

double *gwinflow;        // [nhru]
double *cumgwinflow;     // [nhru]
double *gwoutflow;       // [nhru]
double *cumgwoutflow;    // [nhru]

double *flow;     // [BASIN] all HRUs
double *flow_s;   // [BASIN] all HRUs
double *cumflow;  // [BASIN] all HRUs

double *gwflow;     // [BASIN] all HRUs
double *gwflow_s;   // [BASIN] all HRUs
double *cumgwflow;  // [BASIN] all HRUs

double *WS_Ktravel_var;         // [nhru]
double *WS_gwKtravel_var;         // [nhru]

double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;

ClassMuskingum *inflowDelay;
ClassMuskingum *gwDelay;

ClassClark *Clark_inflowDelay;
ClassClark *Clark_gwDelay;

// declared parameters

const double *WS_route_n;         // [nhru]
const double *WS_route_R;         // [nhru]
const double *WS_route_S0;        // [nhru]
const double *WS_route_L;         // [nhru]
const long  *WS_Channel_shp;      // [nhru]

const double *WS_Lag;             // [nhru]
const double *WS_route_X_M;       // [nhru]
const long  *WS_whereto;         // [nhru]
const long  *WS_order;           // [nhru]

const double *WS_gwLag;           // [nhru]
const double *WS_gwroute_X_M;     // [nhru]
const long  *WS_gwwhereto;       // [nhru]
const long  *WS_gworder;         // [nhru]

const double *WS_Kstorage;     // [nhru]
const double *WS_gwKstorage;   // [nhru]

const double *WS_channel_slope;
const double *WS_side_slope;
const double *WS_culvert_diam;
const double *WS_culvert_water_Dmax;
const double *WS_number_culverts;

const long *WS_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute2* klone(string name) const;
};


double Farouki_a(double fract_por);

class ClassLongVt : public ClassModule {
public:

ClassLongVt(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , QsiD_Var, ") {};

// declared observation variables
  const double *Qsi;
  const double *QsiD;
  const double *Qli;

// declared observation functions
  double *QsiDavg;

// declared observations
  double *Qli_out;

// declared variables
  double *Qli_Var;
  double *QliVt_Var;
  double *tau;

// declared parameters
  const double *Vt;

//  const double *epsilon_clear;
  const double *epsilon_s;

// variable inputs
  const double *hru_t;
  const double *hru_ea;
  const double *hru_rh;
  const double *QdroDext;
  const double *QsiD_Var;

void decl(void);
void init(void);
void run(void);

ClassLongVt* klone(string name) const;
};

class Classpbsm_M : public ClassModule {
public:

Classpbsm_M(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, " hru_u, hru_Uadjust, hru_u, hru_Uadjust"), // setting PeerRank
                                  hru_basin(NULL) {};
// declared variables
double *SWE;
double *Subl;
double *Drift;
double *cumSubl;
double *cumDrift;
double *cumDriftIn;
double *cumSno;
double *Prob;
double *snowdepth;
double *BasinSnowLoss;
double *cumBasinSnowLoss;
double *cumBasinSnowGain;
double *SnowAge;
double *this_distrib;
double *Results;
double **Results_lay;
double *Q_leeslope;
double *Q_valley;
long  *DrySnow;

// declared parameters
const double *fetch;
const double *Ht;
const double *hru_Ht;
const double *distrib;
const double **distrib_hru;
const double *basin_area;
const double *hru_area;
const double *A_S;
const double *N_S;
const double *Zwind;
const double *hru_GSL;
const double *Beta_M;
const long *inhibit_evap;
const long *inhibit_bs;
const long *inhibit_subl;
const long *eq_prof;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_u;
const double *net_snow;
const long  *hru_newsnow;

// local allocated arrays
double *hru_basin;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classpbsm_M* klone(string name) const;
void Sum(double TQsalt, double TQsusp, double SBsum, double SBsalt, double & DriftH, double & SublH);
void Pbsm(double E_StubHt, double Uthr, double & DriftH, double & SublH, double t, double u, double rh, double Fetch,
            long N_S, double A_S, double GSL, double height, double Beta_M, double & Qdist_leeslope, double & Qdist_valley);
};

class ClassNetroute_D : public ClassModule {
public:

ClassNetroute_D(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
double *inflow;           // [nhru]
double *cuminflow;        // [nhru]
double *outflow;          // [nhru]
double *outflow_diverted; // [nhru]
double *cumoutflow_diverted; // [nhru]
double *cumoutflow;       // [nhru]
double *cumscaling_boost; // [nhru]
double *gwinflow;         // [nhru]
double *gwoutflow_diverted; // [nhru]
double *gwcumoutflow_diverted; // [nhru]
double *HRU_cumbasinflow; // [nhru]

double *ssrinflow;        // [nhru]
double *ssrcuminflow;     // [nhru]
double *ssroutflow;       // [nhru]
double *ssrcumoutflow;    // [nhru]

double *runinflow;        // [nhru]
double *runcuminflow;     // [nhru]
double *runoutflow;       // [nhru]
double *runcumoutflow;    // [nhru]

double *gwoutflow;       // [nhru]
double *gwcuminflow;    // [nhru]
double *gwcumoutflow;    // [nhru]

double *basinflow;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_gw_Buf;     // buffered

double *cum_to_Sd;         // [nhru]
double *cum_to_soil_rechr; // [nhru]

double *distrib_sum;
double *cum_preferential_flow_to_gw;

ClassClark *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const double *Kstorage;         // [nhru]
const double *Lag;              // [nhru]
const double *ssrKstorage;      // [nhru]
const double *ssrLag;           // [nhru]
const double *runKstorage;      // [nhru]
const double *runLag;           // [nhru]
const double *gwKstorage;       // [nhru]
const double *gwLag;            // [nhru]
const long  *gwwhereto;        // [nhru]

const double *basin_area;        // [BASIN]
const double *hru_area;          // [nhru]
const double *distrib;
const double **distrib_hru;
const double *distrib_Basin;
const double *Sdmax;             // [nhru]
const double *soil_rechr_max;    // [nhru]
const long  *Sd_ByPass;         // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *order; // [nhru]
const long  *preferential_flow; // [nhru]

const double *scaling_factor;    // temporary modification

// variable inputs
const double *soil_gw;   // [nhru]
const double *soil_ssr;    // [nhru]
const double *soil_runoff; // [nhru]

// variable puts
double *Sd;
double *soil_moist;
double *soil_rechr;
double *redirected_residual;
double *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute_D* klone(string name) const;
};

class ClassNetroute_M_D : public ClassModule {
public:

ClassNetroute_M_D(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long meltrunoffDiv;
long soil_ssrDiv;
long soil_runoffDiv;
long soil_gwDiv;

// declared variables
double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *outflow_diverted;    // [nhru]
double *cumoutflow_diverted; // [nhru]
double *cumoutflow;    // [nhru]
double *cumscaling_boost;    // [nhru]
double *gwinflow;         // [nhru]
double *gwoutflow_diverted; // [nhru]
double *gwcumoutflow_diverted; // [nhru]
double *HRU_cumbasinflow; // [nhru]

double *ssrinflow;        // [nhru]
double *ssrcuminflow;     // [nhru]
double *ssroutflow;       // [nhru]
double *ssrcumoutflow;    // [nhru]

double *runinflow;        // [nhru]
double *runcuminflow;     // [nhru]
double *runoutflow;       // [nhru]
double *runcumoutflow;    // [nhru]

double *gwoutflow;       // [nhru]
double *gwcuminflow;    // [nhru]
double *gwcumoutflow;    // [nhru]

double *basinflow;     // [BASIN] all HRUs
double *basinflow_s;   // [BASIN] all HRUs
double *cumbasinflow;  // [BASIN] all HRUs
double *basingw;       // [BASIN} all HRUs
double *basingw_s;     // [BASIN} all HRUs
double *cumbasingw;    // [BASIN} all HRUs

double *soil_ssr_Buf;    // buffered
double *soil_runoff_Buf; // buffered
double *soil_gw_Buf;     // buffered

double *cum_to_Sd;         // [nhru]
double *cum_to_soil_rechr; // [nhru]

double *Ktravel;         // [nhru] Muskingum

double *distrib_sum;
double *cum_preferential_flow_to_gw;

ClassMuskingum *hruDelay;
ClassClark *ssrDelay;
ClassClark *runDelay;
ClassClark *gwDelay;

// declared parameters
const double *route_n;         // [nhru]
const double *route_R;         // [nhru]
const double *route_S0;        // [nhru]
const double *route_L;         // [nhru]
const double *route_X_M;       // [nhru]
const long  *route_Cshp;      // [nhru]

const double *Lag;             // [nhru]
const double *ssrKstorage;     // [nhru]
const double *ssrLag;          // [nhru]
const double *runKstorage;     // [nhru]
const double *runLag;          // [nhru]
const double *gwKstorage;      // [nhru]
const double *gwLag;           // [nhru]
const long  *gwwhereto;       // [nhru]

const double *basin_area;      // [BASIN]
const double *hru_area;        // [nhru]
const double *distrib;
const double *distrib_Basin;
const double **distrib_hru;
const double *Sdmax;           // [nhru]
const double *soil_rechr_max;  // [nhru]
const long  *Sd_ByPass;       // [nhru]
const long  *soil_rechr_ByPass; // [nhru]
const long  *order;
const long  *preferential_flow; // [nhru]

const double *scaling_factor;    // temporary modification

// variable inputs
const double *soil_gw;   // [nhru]
const double *soil_ssr;    // [nhru]
const double *soil_runoff; // [nhru]

// variable puts
double *Sd;
double *soil_moist;
double *soil_rechr;
double *redirected_residual;
double *gw;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);
virtual double Function1(double *I, long hh);
virtual double Function2(double *X, long hh);

ClassNetroute_M_D* klone(string name) const;
};

class ClassSetSoil : public ClassModule {
public:

ClassSetSoil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared parameters

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_lat;
const double *hru_elev;
const double *hru_GSL;
const double *hru_ASL;
const long *RUN_ID;
const long *RUN_START;
const long *RUN_END;

const double *soil_Depth;
const double *soil_Depth_rechr;
const double *Vol_h2o_content;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;

const long *soil_type;
const long *soiltype_rechr;

TStringList *basin_name;
TStringList *INIT_STATE;
TStringList *hru_names;
TStringList *RapidAdvance_to;
TStringList *Loop_to;
TStringList *StateVars_to_Update;
TStringList *TraceVars;

// declared variables
//long *run_ID;

// variable inputs

void decl(void);
void init(void);

ClassSetSoil* klone(string name) const;
};

class ClassVolumetric : public ClassModule {
public:

ClassVolumetric(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "soil_gw") {}; // setting PeerVar. Cannot be "STATE" var

// declared parameters
const double *soil_Depth;
double *fallstat;
const double *Si;
const double *Si_correction;
const double *soil_moist_max;
const long *soil_type;
const long *set_fallstat;
//const long *fallstat_Si;

// declared variables
double *Volumetric;
double *fallstat_V;
double *Si_V;

// variable inputs
const double *soil_moist;

void decl(void);
void init(void);
void run(void);

ClassVolumetric* klone(string name) const;
};

class ClassAnnan : public ClassModule {
public:

  double QsiDT, TauAT;

  ClassAnnan(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
//const double *SunAct;

// declared variables
double *hru_SunAct;
double *QsiA_Var;
double *QsiD_Var;
double *QsiS_Var;

// declared parameters
const double *krs;
const double *hru_elev;

// declared observations
double *QsiA;
double *QsiD;
double *QsiS;

// variable inputs
const double *QdflatE;
const double *QdflatD;
const double *QdroDext;
const double *Qdro;
const double *Qdfo;
const double *QdfoD;
const double *SunMax;
const double *hru_tmax;
const double *hru_tmin;

void decl(void);
void init(void);
void run(void);

ClassAnnan* klone(string name) const;
};

class Classcalcsun : public ClassModule {
public:

Classcalcsun(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , , , QsiD_Var") {};

// declared observation variables
const double *Qsi;
const double *QsiD_Obs;
const double *SunAct;

// declared observation functions
double *Qsitot;

// declared variables
double *hru_SunAct;

// declared parameters

// variable inputs
const double *QdflatD;
const double *QdfoD;
const double *SunMax;
const double *QsiD_Var;

void decl(void);
void init(void);
void run(void);

Classcalcsun* klone(string name) const;
};

class ClassObstoPar : public ClassModule {
public:

long Ht_obsCnt;

ClassObstoPar(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Ht_var;

// declared observation variables
const double *Ht_obs;      // interval data

// declared parameters
TStringList *obs_name;
TStringList *par_name;

double *Ht;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassObstoPar* klone(string name) const;
};

class ClassPrairieInfil : public ClassModule {
public:

ClassPrairieInfil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                   Xinfil(NULL),
                                   timer(NULL) {};
// declared variables
double *snowinfil;
double *cumsnowinfil;
double *infil;
double *cuminfil;
double *meltrunoff;
double *cummeltrunoff;
double *runoff;
double *cumrunoff;
double *RainOnSnow;
double *RainOnSnowA;
long  *crackstat;
long  *crackon;

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const double *fallstat;
const double *Major;      // threshold for major melt event(default is 5 mm/day)
const long  *PriorInfiltration;
const long  *texture;
const long  *groundcover;

// variable inputs
const double *hru_tmax;
const double *snowmelt;
const double *SWE;
const double *net_rain;

// local allocated arrays
double **Xinfil; // [3] [nhru]
long *timer;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassPrairieInfil* klone(string name) const;
};

class ClassCRHMCanopy:public ClassModule {

public:

ClassCRHMCanopy(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_, Qli_;

// observation variables

const double *Qsi;
const double *Qli;

// declared observation variables

double *Ts;
double *Qnsn;
double *Qsisn;
double *Qlisn;
double *Qlosn;

// put variables

double *SWE;

// declared variables

double *drip_Cpy;
double *thrufall_Cpy;
double *netRain_Cpy;
double *direct_rain;
double *rain_load;
double *Snow_load;
double *direct_snow;
double *SUnload;
double *SUnload_H2O;
double *Qnsn_Var;

double *net_rain;
double *cum_net_rain;
double *net_snow;
double *cum_net_snow;
double *net_p;
double *intcp_evap;
double *cum_intcp_evap;
double *Subl_Cpy;
double *cum_Subl_Cpy;           
double *cum_SUnload;
double *cum_SUnload_H2O;

double *Cc;
double *k;
double *Tauc;
double *Pa;
double *ra;
double *u_FHt;
double *Pevap;
double *Qsisn_Var;
double *Qlisn_Var;

// variable inputs

const double *hru_t;
const double *hru_u;
const double *hru_rh;
const double *hru_ea;
const double *Albedo;

const double *hru_snow;
const double *hru_rain;
const double *hru_evap;

const double *SolAng;

const double *QsiS_Var;
const double *QsiA_Var;
const double *QliVt_Var;

// declared parameters:

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_elev;
const double *Ht;
const double *LAI;
const double *Sbar;
const double *Z0snow;
const double *Zref;
const double *Zwind;
const double *Zvent;
const double *unload_t;
const double *unload_t_water;
const double *B_canopy;
const double *Alpha_c;

const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/°C
double gamma(double Pa, double t); // Psychrometric constant (kPa/°C)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg °C))

ClassCRHMCanopy* klone(string name) const;

};

class ClassPSPnew : public ClassModule {
public:

ClassPSPnew(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared observation variables
const double *TsnowG;
const double *Lnot;

// declared variables
double *Qsubl;
double *Load;
double *Thru;
double *TCanSnow;
double *Tbiomass;

// declared parameters
const double *Sbar;
const double *LAI;
const double *Zcan;
const double *Zref;
const double *Ht;
const double *Biomass;
const double *k;
const double *HeightH;
const double *WidthJ;
const long *InitN;

// variable inputs
const double *RHref;
const double *Qn;
const double *QsIn;
const double *QsOut;
const double *hru_u;
const double *hru_p;
const double *TAref;
const double *SolarAng;

// local allocated arrays
double *T0CanSnow;
double *T0biomass;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

class ClassPSPnew* klone(string name) const;

};

class Classbrushintcp : public ClassModule {
public:

Classbrushintcp(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000) {};

// declared variables
double *net_rain;
double *cum_net_rain;
double *net_snow;
double *net_p;
double *Load;
double *Thru;
double *cumThru;
double *brushsubl;
double *spherecoeff;
double *cumbrushsubl;
double *intcp_evap;

// declared parameters
const double *basin_area;   // [ONE]
const double *hru_area;
const double *Ht;
const double *Zref;
const double *Zcan;
const double *brushAtten;
const double *Sbar;
const double *LAI;
const double *WidthJ;
const double *Tunload;

// variable inputs
const double *hru_t;
const double *hru_tmean;
const double *hru_rh;
const double *hru_u;
const double *hru_p;
const double *hru_rain;
const double *hru_snow;

// variable inputs/outputs
double *cumSubl;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classbrushintcp* klone(string name) const;

};

class ClassAyers : public ClassModule {
public:

ClassAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *infil;
double *cuminfil;
double *runoff;
double *cumrunoff;
double *snowinfil;
double *cumsnowinfil;
double *meltrunoff;
double *cummeltrunoff;
double *melt_int; // interval melt - from snowmelD

// declared parameters
const double *basin_area; // [BASIN]
const double *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const double *net_rain;
const double *snowmeltD;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassAyers* klone(string name) const;
};

class ClassSnobalCRHM : public ClassSnobalBase {

    public:

    ClassSnobalCRHM(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalCRHM* klone(string name) const;

    double Qsi_;
    double Qli_;

// Observations

    const double *Qsi; // incoming solar radiation (W/m^2)
    const double *Qli; // incoming longwave (thermal) rad (W/m^2) long
    const double *T_g_Obs; // ground temperature at depth
    const double *F_g_Obs; // ground flux at depth

// variable climate-data inputs

    const double  *T_a_X;      // air temp (C) hru_t
    const double  *T_pp_X;       // precip temp (C) hru_t
    const double  *e_a_X;      // vapor pressure (Pa) hru_ea
    const double  *u_X;        // wind speed (m/sec)  hru_u
    const double  *Albedo;     // albedo ()
    const double  *Qsisn_Var;  // short wave at snow surface
    const double  *QsiS_Var;  // short wave at snow surface from Slope_Qsi
    const double  *Qlisn_Var;  // long wave at snow surface - through canopy
    const double  *QliVt_Var;  // long wave at snow surface - no canopy

// variable precipitation inputs

    const double  *m_precip_X;	// specific mass of total precip     (kg/m^2) net_p
    const double  *m_snow_X;	// specific mass in snow in precip   (kg/m^2) net_snow
    const double  *m_drift_X;	// specific mass in snow drift       (kg/m^2) Drift
    const double  *m_subl_X;	// specific mass of snow sublimation (kg/m^2) Subl

// put variable precipitation inputs

    double  *m_rain_X;	// specific mass of rain in precip   (kg/m^2) net_rain

// parameters

    const double  *rho_snow_X;       // density of snowfall               (kg/m^3)
    const double  *T_g_X;            // soil temp at depth z_g (C)
    const double  *F_g_X;            // soil flux at depth z_g (C)
    const long   *rain_soil_snow;  //
    double *snow_store; // accumulates snow till > 1+mm

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};

class ClassSlope_Qsi : public ClassModule {
public:

ClassSlope_Qsi(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QsiS_Var;
double *QsiD_Var;

// declared observations variable
const double *Qsi;

// declared observations
double *QsiS;
double *QsiD;
double *QsiD_Obs;

// variable inputs
const double *Qdro;
const double *Qdfo;
const double *Qdflat;

void decl(void);
void init(void);
void run(void);

ClassSlope_Qsi* klone(string name) const;
};

class ClassfrozenAyers : public ClassModule {
public:

ClassfrozenAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
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
double *cumsnowinfil_0;  // cumulative frozen infiltration at beginning of frozen cycle
double *cummeltrunoff; // cumulative frozen melt runoff
double *runoff;        // cumulative runoff
double *cumrunoff;     // cumulative melt runoff
double *t0_Acc;        // infiltration opportunity time accumulation
double *t0_Var;        // infiltration opportunity time used
double *INF;           //
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
const long  *texture;
const long  *groundcover;

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

ClassfrozenAyers* klone(string name) const;
};

class ClassSoil : public ClassModule {
public:

ClassSoil(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// declared observation variables

// declared variables
long *current_getstep;
double *Sd;
double *gw;
double *soil_rechr;
double *soil_moist;
double *soil_gw;
double *Sd_gw;
double *gw_flow;
double *soil_ssr;
double *rechr_ssr;
double *soil_runoff;
double *cum_soil_ssr;
double *cum_rechr_ssr;
double *cum_soil_runoff;
double *cum_runoff_to_Sd;
double *cum_redirected_residual;
double *soil_gw_D;
double *soil_ssr_D;
double *gw_flow_D;
double *soil_runoff_D;
double *HK_V;
double *HK_A;
double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;
double *redirected_residual;
double *infil_act;
double *cum_infil_act;
double *infil_act_D;

double *soil_runoff_stream;
double *weir_outflow;
double *weir_outflow_m3s;
double *weir_water_A;
double *weir_water_V;
double *weir_water_h;
double *weir_evap;
double *cum_weir_over_m3;
double *weir_crest_volume;
double *stream;
double *stream_to_Sd;
double *cum_stream;
double *stream_Grp_in;
double *stream_Grp_loss;
double *cum_stream_Grp_loss;

// local variables
double *cum_soil_gw;
double *cum_Sd_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *cum_Sd_evap;
double *soil_moist_Init;
double *soil_rechr_Init;
double *Sd_Init;
double *gw_Init;
double *SWE_Init;

double *snowinfil_buf;
double *runoff_buf;
double *meltrunoff_buf;
double *hru_evap_buf;

// declared parameters
const double *Sdmax;
const double *Sdinit;
const double *gw_max;
const double *gw_init;
const double *gw_K;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;
const double *soil_gw_K;
const double *rechr_ssr_K;
const double *lower_ssr_K;
const double *Sd_ssr_K;
const double *Sd_gw_K;
const double *channel_slope;
const double *side_slope;
const double *culvert_diam;
const double *culvert_water_Dmax;
const double *number_culverts;

const double *weir_crest;
const double *weir_coefficient;
const double *weir_mult;
const double *weir_b;
const double *lake_mult;
const double *lake_power;
const double *lake_p;
const double *lake_S;
const double *runoff_stream;
const double *stream_runoff;
const double *stream_Sd;
const double *Wetlands_scaling_factor;    // temporary modification

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;
const double *SD;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoil* klone(string name) const;
};

class Classevap_Resist : public ClassModule {
public:

Classevap_Resist(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QsiS_Var, QsiA_Var") {};

double Qsi_;
long QsiCnt;
long TsCnt;
long RnObsCnt;
bool BeforeCorrectionRCS;

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *evapD;
double *cum_evap;
double *rc;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *Htmax;
const double *Zwind;
const double *hru_elev;
const double *F_Qg;
const double *rcs;
const double *LAImax;
const double *LAImin;
const double *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const double *s;
const long *PM_method;

// variable inputs
const double *Rn;
const double *RnD;
const double *RnD_POS;
const double *hru_t;
const double *hru_u;
const double *hru_ea;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;
const double *soil_moist;
const double *QsiS_Var;
const double *QsiA_Var;

// declared observations variable
const double *Qsi;
const double *Ts;
const double *RnObs;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classevap_Resist* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};

class ClassevapD_Resist : public ClassModule {
public:

ClassevapD_Resist(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt;
long TsCnt;

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evapD;
double *cum_evap;
double *rc;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *Htmax;
const double *Zwind;
const double *hru_elev;
const double *F_Qg;
const double *rcs;
const double *LAImax;
const double *LAImin;
const double *soil_Depth;

const long *evap_type;
const long *inhibit_evap;
const long *soil_type;
const double *s;
const long *PM_method;

// variable inputs
const double *RnD;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;
const double *soil_moist;

// declared observations variable
const double *Qsi;
const double *Ts;

// declared observation functions
double *Qsi_mean;
double *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD_Resist* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};

class ClassShutWall : public ClassModule {
public:

ClassShutWall(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;
double z0;
double d;
double n;


// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *evapD;
double *cum_evap;
double *Cc;
double *Cs;
double *Ra;
double *Rc;
double *Rs;
double *ETc;
double *ETs;
double *raa;
double *rca;
double *rcs;
double *rsa;
double *rss;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *rs;
const double *hru_elev;
const double *Cr;
const double *LAI;
const double *Ht;
const double *Zwind;
const double *w;
const double *rst;
const double *z0g;
const double *gammab;

const long *inhibit_evap;

// declared observations
const double *hru_u;
const double *hru_t;
const double *hru_ea;
const double *Qn;
const double *Qg;

// variable inputs

// local allocated arrays
double *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWall* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
};

class ClassShutWallD : public ClassModule {
public:

ClassShutWallD(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evapD;
double *cum_evap;
double *Cc;
double *Cs;
double *Ra;
double *Rc;
double *Rs;
double *ETc;
double *ETs;
double *raa;
double *rca;
double *rcs;
double *rsa;
double *rss;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *rs;
const double *hru_elev;
const double *Cr;
const double *LAI;
const double *Ht;
const double *Zwind;
const double *w;
const double *rst;
const double *z0g;
const double *gammab;

const long *inhibit_evap;

// declared observations
const double *hru_umean;
const double *hru_tmean;
const double *hru_eamean;
const double *Qn;
const double *Qg;

// declared observation functions
double *Qnmean;
double *Qgmean;

// variable inputs

// local allocated arrays
double *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWallD* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
};

class ClassIceBulb : public ClassModule {
public:

ClassIceBulb(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_icebulb;
double *hru_rainI;
double *cumhru_rainI;
double *hru_snowI;
double *cumhru_snowI;
double *cumhru_pI;
double *Pa;

// variable inputs
const double *hru_t;
const double *hru_rh;
const double *hru_p;

// declared parameters
const double *hru_elev;
const double *tmaxI_allrain;
const double *tmaxI_allsnow;

void decl(void);
void init(void);
void run(void);

ClassIceBulb* klone(string name) const;
};

class Classlake : public ClassModule {
public:

Classlake(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  int DaysMonth;
  long ThisMonth;
  bool DoMean;
  bool Ahead;
  long  N_intervals;
  long itime[6];

// declared variables
  double *hru_evap;
  double *hru_cum_evap;
  double *hru_actet;
  double *hru_cum_actet;
  double *lake_evap_month;
  double *hru_t_Mmean;
  double *hru_rh_Mmean;
  double *hru_u_Mmean;
  double *hru_t_acc;
  double *hru_rh_acc;
  double *hru_u_acc;
  double *Vw;
  double *Va;
  long  *start_open_day;
  long  *end_open_day;

// get variables:
  const double *hru_t;
  const double *hru_rh;
  const double *hru_u;

// put variables:

// declared parameters
  const double *Meyer_C;
  const double *Meyer_B;
  const double **Meyer_B_def;
  const double *hru_area;
  const double *basin_area;
  const double *hru_lat;
  const double *hru_elev;

  const long *start_open_water;
  const long *end_open_water;

void decl(void);
void init(void);
void run(void);
void add(void);
void process(void);
void finish(bool good);

Classlake* klone(string name) const;
};

class ClassalbedoWinstral : public ClassModule {
public:

ClassalbedoWinstral(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Albedo;
  double *irdalb;
  double *vdalb;
//  double *balbx;
  double *Ab_t;

// get variables:

  const double *net_snow;
  const double *SWE;

// put variables:

// declared parameters
  const double *maxdecay;
  const double *power;
  const double *decay_period;
  const double *refresh;
  const double *Albedo_Bare;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassalbedoWinstral* klone(string name) const;
};

class ClassK_Estimate : public ClassModule {
public:

ClassK_Estimate(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double *Ht_var;
  double *v_L_upper;
  double *v_L_lower;
  double *v_V_sd;
  double *v_V_soil;
  double *v_L_gw;
  double *rechr_ssr_K_V;
  double *lower_ssr_K_V;
  double *Sd_ssr_K_V;
  double *Sd_gw_K_V;
  double *soil_gw_K_V;
  double *gw_K_V;
  double *Dts_organic_runoff_K_V;
  double *Dts_snow_runoff_K_V;
  double *Ks_snow;
  double *v_L_organic;
  double *v_L_snow;

// declared observation variables

// declared parameters
  const double *Ks_lower;
  const double *Ks_upper;
  const double *Ks_gw;
  const double *hru_GSL;
//  const double *porosity;
  const double *PSD;
  const double *soil_rechr_max;
  const double *soil_moist_max;
//  const double *gw_max;

  const long *inhibit_evap;

// declared parameters
  const double *d_g;
  const double *Ks_organic;
  const double *PSD_org;
  const double *S_I;
  const long  *Inhibit_K_set;

// put parameters

  double *rechr_ssr_K;
  double *lower_ssr_K;
  double *Sd_ssr_K;
  double *Sd_gw_K;
  double *soil_gw_K;
  double *gw_K;
  double *Dts_organic_runoff_K;
  double *Dts_snow_runoff_K;

// put variables:

double *soil_rechr;
double *soil_moist;
double *gw;

// get variables:

const double *Dts;
const double *Dts_max;
const double *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassK_Estimate* klone(string name) const;
};

class ClassevapX : public ClassModule {
public:

ClassevapX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *evap_D;
double *cum_evap;
double *Granger_D;
double *rc;

// local allocated arrays
double *Pa;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *Ht;
const double *hru_elev;
const double *F_Qg;
const double *Zwind;
const double *rcs;
const double *Htmax;
const double *LAImax;
const double *LAImin;
const double *s;
const double *PM_method;
const double *soil_Depth;

const long *soil_type;
const long *evap_type;
const long *inhibit_evap;

// variable inputs
const double *soil_moist;
const double *Rn;
const double *RnD;
const double *RnD_POS;
const double *hru_t;
const double *hru_u;
const double *hru_ea;
const double *hru_tmean;
const double *hru_umean;
const double *hru_eamean;

// declared observations variable
const double *Qsi;
const double *RnObs;

// declared observation functions
//double *Qsi_mean;
double *Tsmean;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapX* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};

class Class3D_param : public ClassModule {
public:

Class3D_param(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Var_3D;

// declared parameters
const double *Param_3D;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Class3D_param* klone(string name) const;
};

class ClassMeltRunoff_Lag : public ClassModule {
public:

ClassMeltRunoff_Lag(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
double *In_Lagstorage;
long *Tf;

// get variables:
const double *snowmelt_int;

// put variables
double *runLag;

// declared parameters
const double *hru_area;
const long  *inhibit_MeltRunoff_Lag;

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Lag* klone(string name) const;
};

class ClassMeltRunoff_Kstorage : public ClassModule {
public:

ClassMeltRunoff_Kstorage(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
double *Ksat;
double *Meltrunoff_K;
double *In_storage;

// get variables:
const double *rho;

// put variables
double *runKstorage;

// declared parameters
const double *d_g;
const double *hru_GSL;
const double *runLag;
const double *route_L;
const long  *inhibit_evap;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassMeltRunoff_Kstorage* klone(string name) const;
};

class ClassREWroute : public ClassModule {
public:

ClassREWroute(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt;
long gwCnt;

// declared variables
double *rew;
double *gwrew;

double **inflow_All;
double **gw_All;

double *inflow;        // [nhru]
double *cuminflow;     // [nhru]
double *outflow;       // [nhru]
double *cumoutflow;    // [nhru]

double *gwinflow;        // [nhru]
double *cumgwinflow;     // [nhru]
double *gwoutflow;       // [nhru]
double *cumgwoutflow;    // [nhru]

double *flow;     // [BASIN] all HRUs
double *flow_s;   // [BASIN] all HRUs
double *cumflow;  // [BASIN] all HRUs

double *gwflow;     // [BASIN] all HRUs
double *gwflow_s;   // [BASIN] all HRUs
double *cumgwflow;  // [BASIN] all HRUs

double *WS_Ktravel_var;         // [nhru]
double *WS_gwKtravel_var;         // [nhru]

double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_water_O;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;

ClassMuskingum *inflowDelay;
ClassMuskingum *gwDelay;

ClassClark *Clark_inflowDelay;
ClassClark *Clark_gwDelay;

// declared parameters

const double *WS_route_n;         // [nhru]
const double *WS_route_R;         // [nhru]
const double *WS_route_S0;        // [nhru]
const double *WS_route_L;         // [nhru]
const long  *WS_Channel_shp;      // [nhru]

const double *WS_Lag;             // [nhru]
const double *WS_route_X_M;       // [nhru]
const long  *WS_whereto;         // [nhru]
const long  *WS_order;           // [nhru]

const double *WS_gwLag;           // [nhru]
const double *WS_gwroute_X_M;     // [nhru]
const long  *WS_gwwhereto;       // [nhru]
const long  *WS_gworder;         // [nhru]

const double *WS_Kstorage;     // [nhru]
const double *WS_gwKstorage;   // [nhru]

const double *WS_channel_slope;
const double *WS_side_slope;
const double *WS_culvert_diam;
const double *WS_culvert_water_Dmax;
const double *WS_number_culverts;

const long *WS_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute* klone(string name) const;
};

class ClassXG : public ClassModule {
public:

long front_size;

ClassXG(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "hru_tsf, , ") {};

// constants

double ko;
double km;
double ka;
double ki;
double kw;

// declared variables
double *Zdf;
double *Zdt;
long *Th_low_lay;
long *Fz_low_lay;
double *Bfr;
double *Bth;
double *TrigAcc;
double *B;
long *TrigState;
double *pf;
double **pf_lay;
double *pt;
double **pt_lay;
double *ttc;
double **ttc_lay;
double *ftc;
double **ftc_lay;
double *SWE_tc;
double *SWE_density;
double *XG_moist_d;
double *XG_rechr_d;
double *XG_moist;
double *check_XG_moist;
double **XG_moist_lay;
double *XG_max;
double **XG_max_lay;
double *layer_h2o;
double **h2o_lay;
double *theta;
double **theta_lay;
double *rechr_fract;
double **rechr_fract_lay;
double *moist_fract;
double **moist_fract_lay;
double *default_fract;
double **default_fract_lay;
double *tc_composite;
double **tc_composite_lay;
double *tc_composite2;
double **tc_composite2_lay;

double *Zd_front;
double **Zd_front_array;
double *n_factor;
double *n_factor_T;
double *check_t;
double *t_trend;
long *ttc_contents;
long **ttc_contents_lay;
long *ftc_contents;
long **ftc_contents_lay;
long  *nfront;

// declared parameters
const double *SWE_k;
const double *soil_solid_km;
const double **soil_solid_km_lay;
const double *soil_solid_km_ki;
const double **soil_solid_km_ki_lay;
const double *soil_solid_km_kw;
const double **soil_solid_km_kw_lay;
const double *depths;
const double **depths_lay;
const double *por;
const double **por_lay;
const double *theta_default;
const double **theta_default_lay;
const double *Zdf_init;
const double *Zdt_init;
const double *Zpf_init;
const double *n_factor_a;
const double *n_factor_b;
const double *n_factor_c;
const double *Trigthrhld;
const long *N_Soil_layers;
const long *calc_coductivity;
const long *freeze_kw_ki_update;
const long *thaw_ki_kw_update;
const long *k_update;
const double *soil_moist_max;
const double *soil_rechr_max;
const double *theta_min;

// variable inputs
const double *hru_t;
const double *hru_tsf;
const double *SWE;
const double *soil_moist;
const double *soil_rechr;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void freeze(void);
void thaw(void);
void find_freeze_D(double df);
void find_thaw_D(double dt);
void push_front(double D);
double pop_front(void);
double last_front(void);
double Interpolated_ftc_lay(double Za, long lay);
double Interpolated_ttc_lay(double Za, long lay);
double SWE_to_rho(double SWE);
double get_ftc_lay(long lay);
double get_ttc_lay(long lay);

ClassXG* klone(string name) const;
};

class Classcontribution : public ClassModule {
public:

Classcontribution(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long soil_runoffDiv;

// declared variables
double *contrib_area;
double *pre_contrib_area;
double *connected;
long  *N_connected;
long  *connectedTo;
double *Results;
double **Results_lay;
double *distrib_sum;
const double *distrib_Basin;
double *soil_runoff_Buf; // buffered

// declared parameters
const double *basin_area;
const double *hru_area;
const double *Sdmax;
const double *distrib;
const double **distrib_hru;

// variable inputs
const double *soil_runoff;
const double *Sd;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classcontribution* klone(string name) const;
};

class ClassSoilX : public ClassModule {
public:

ClassSoilX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;
long depths_size; // handles recharge and lower layers

// declared observation variables

// declared variables
double *Sd;
double *gw;
double *soil_rechr;
double *soil_moist;
double *soil_gw;
double *gw_flow;
double *soil_ssr;
double *rechr_ssr;
double *soil_runoff;
double *cum_soil_ssr;
double *cum_rechr_ssr;
double *cum_soil_runoff;
double *cum_runoff_to_Sd;
double *cum_redirected_residual;
double *soil_gw_D;
double *soil_ssr_D;
double *gw_flow_D;
double *soil_runoff_D;
double *HK_V;
double *HK_A;
double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;
double *redirected_residual;
double *infil_act;
double *cum_infil_act;
double *infil_act_D;

// local variables
double *cum_soil_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *soil_moist_Init;
double *soil_rechr_Init;
double *Sd_Init;
double *gw_Init;
double *SWE_Init;
double *Dts_runoff_K; // from Dts_snow_runoff_K or Dts_organic_runoff_K

double *snowinfil_buf;
double *runoff_buf;
double *meltrunoff_buf;
double *hru_evap_buf;

double *thaw_layers;
double **thaw_layers_lay;
double *depth_layers;
double **depth_layers_lay;
double *thaw_all;

// declared parameters
const double *Sdmax;
const double *Sdinit;
const double *gw_max;
const double *gw_init;
const double *gw_K;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;
const double *soil_gw_K;
const double *rechr_ssr_K;
const double *lower_ssr_K;
const double *Sd_ssr_K;
const double *Sd_gw_K;
const double *channel_slope;
const double *side_slope;
const double *culvert_diam;
const double *culvert_water_Dmax;
const double *number_culverts;
const double *porosity_upper;
const double *porosity_lower;
const double *evap_from_runoff;
const double *Dts_snow_max;
const double *Dts_organic_max;
const double *Dts_snow_init;
const double *Dts_snow_runoff_K;
const double *Dts_organic_runoff_K;
const double *Dts_organic_init;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *NO_Freeze;
const long *inhibit_evap;

// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;
const double *Zdt;
const double *Zdf;
const double *Zd_front;
const double **Zd_front_array;

double *Dts;
double *Dts_max;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilX* klone(string name) const;
};

class ClassMod_Exec : public ClassModule {
public:

ClassMod_Exec(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

  //HINSTANCE DLL;
  long Imodules;
  string S_Vars;
  string S_Pars;
  long Vars_Cnt;
  long Pars_Cnt;

  typedef  long LoadModuleTypeInit(const char *Grp, long GrpNo, long hru_cnt, const char *S_Vars, long VarsNo, double **V, const char *V_Pars, long ParsNo, double **P);
  typedef  long LoadModuleTypeStep(double DTnow); // time step. Zero at end of run.

  LoadModuleTypeInit *LoadUserInit;
  LoadModuleTypeStep *LoadUserStep;

// Lingage arrays

  double **VarArray;
  double **ParArray;

// declared variables
double *Dummy;
double *Dummy2;
long *statusInit;
long *statusStep;

// declared parameters
TStringList *DLL_name;
TStringList *chg_Pars;
TStringList *trk_Vars;
const long *Borland_Dll;

// variable inputs

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassMod_Exec* klone(string name) const;
};


class ClassFlowInSnow : public ClassModule {
public:

ClassFlowInSnow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// index to module to be called
ClassModule* Netroute_module; // used to call preser for simple projects

// declared variables
double *Ksat_snow;
double *K_snow;
double *u_down;
double *K_down;
double *K_slope;
double *Meltrunoff_K;
double *In_storage;
double *runKstorage_var;

// get variables:
const double *rho;
const double *h2o_sat;
const double *T_s_l;
const double *z_s;

// put variables
double  *runKstorage;

// declared parameters
const double *S_I;
const double *d_g;
const double *t_inhibit_flow;
const double *runKstorage_winter;
const double *runKstorage_summer;
const double *Sr;
const double  *hru_GSL;
const double  *route_L;
const long  *inhibit_MeltRunoff_Kstorage;

void decl(void);
void init(void);
void run(void);

ClassFlowInSnow* klone(string name) const;
};

class ClassSoilDS : public ClassModule {
public:

ClassSoilDS(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv;
long meltrunoffDiv;
long runoffDiv;
long evapDiv;

// declared observation variables

// declared variables
double *Sd;
double *gw;
double *soil_rechr;
double *soil_moist;
double *soil_gw;
double *gw_flow;
double *soil_ssr;
double *rechr_ssr;
double *soil_runoff;
double *cum_soil_ssr;
double *cum_rechr_ssr;
double *cum_soil_runoff;
double *cum_runoff_to_Sd;
double *cum_redirected_residual;
double *soil_gw_D;
double *soil_ssr_D;
double *gw_flow_D;
double *soil_runoff_D;
double *HK_V;
double *HK_A;
double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_over_Q;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;
double *redirected_residual;
double *infil_act;
double *cum_infil_act;
double *infil_act_D;
double *Dts;
double *Dts_max;

// local variables
double *cum_soil_gw;
double *cum_gw_flow;
double *cum_hru_condense;
double *soil_moist_Init;
double *soil_rechr_Init;
double *Sd_Init;
double *gw_Init;
double *SWE_Init;
double *Dts_runoff_K;

double *snowinfil_buf;
double *runoff_buf;
double *meltrunoff_buf;
double *hru_evap_buf;

// declared parameters
const double *Sdmax;
const double *Sdinit;
const double *gw_max;
const double *gw_init;
const double *gw_K;
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *soil_rechr_max;
const double *soil_rechr_init;
const double *soil_moist_max;
const double *soil_moist_init;
const double *soil_gw_K;
const double *rechr_ssr_K;
const double *lower_ssr_K;
const double *Sd_ssr_K;
const double *Sd_gw_K;
const double *channel_slope;
const double *side_slope;
const double *culvert_diam;
const double *culvert_water_Dmax;
const double *number_culverts;
const double *Dts_snow_max;
const double *Dts_organic_max;
const double *Dts_snow_init;
const double *Dts_snow_runoff_K;
const double *Dts_organic_runoff_K;
const double *Dts_organic_init;
const long *soil_withdrawal;
const long **soil_withdrawal_Tables;

const long *culvert_type;
const long *cov_type;
const long *transp_limited;
const long *soil_ssr_runoff;
const long *inhibit_evap;

// variable inputs
const double *infil;
const double *snowinfil;
const double *meltrunoff; // frozen melt runoff
const double *runoff;     // liquid runoff
const double *hru_evap;

// variable put inputs
double *hru_actet;      // [nhru]
double *hru_cum_actet;


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilDS* klone(string name) const;
};

class Classalbedoobs2 : public ClassModule {
public:

Classalbedoobs2(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables
const double *Albedo_obs;      // interval data

// declared variables
double *Albedo;
double *net_snowD;  // daily value sum(newsnow)
long *meltflag;
long *winter;
long  *newsnowcnt;

// declared parameters
const double *Albedo_bare;
const double *Albedo_snow;
const double *hru_lat;

// variable inputs
const double *hru_tmax;
const double *hru_tmin;
const double *QdroD;
const double *SWE;
const double *net_snow;
const long  *hru_newsnow;

void decl(void);
void init(void);
void run(void);

void albedo(long jday, double Qnc);

Classalbedoobs2* klone(string name) const;
};

class Classwinter_meltflag : public ClassModule {
public:

Classwinter_meltflag(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
long *meltflag;
long *winter;

// declared parameters
const double *hru_lat;

// variable inputs
const double *hru_tmax;
const double *hru_tmin;
const double *QdroD;
const double *SWE;
const long  *hru_newsnow;
const double *Albedo;

void decl(void);
void init(void);
void run(void);

Classwinter_meltflag* klone(string name) const;
};

class Class_z_s_rho : public ClassModule {
public:

Class_z_s_rho(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
  double*  z_s;            // total snowcover thickness (m)
  double*  rho;            // average snowcover density (kg/m^3)

// variable inputs
const double *SWE;

void decl(void);
void init(void);
void run(void);

Class_z_s_rho* klone(string name) const;
};

class Classqmelt : public ClassModule {
public:

Classqmelt(string Name = "Qmelt", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

// declared variables
double *Qm;      // MJ/m2/Int
double *Qg;      // MJ/m2/Int
double *cum_Qm;  // MJ/m2
double *cum_Qg;  // MJ/m2
double *QmD;     // MJ/m2
double *QgD;     // MJ/m2

// declared parameters
const double *TIa0Mn;
const double *TIa1Mn;
const double *TIs0Mn;
const double *TIs1Mn;

// declared observations
const double *t;      // °C
const double *ts;     // °C
double *tmean;  // °C
double *tpos;   // °C
double *tsmean; // °C
double *tspos;  // °C

void decl(void);
void init(void);
void run(void);

Classqmelt* klone(string name) const;
};

class Classquinton : public ClassModule {
public:

Classquinton(string Name = "Quinton", string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl){};

ClassClark *Delayrunoff;
ClassClark *Delayflow;

// declared observation variables
const double *p;

// input variables
const double *Qg;        // MJ/m2
const double *driftmelt; // melt depth from upstream drift
const double *hru_p;

// declared parameters
const long *Type;           // NOTUSED, DRIFT or HUMMOCK
//const long *k_range;        // normal, high or low
const long *DrainTo;        // drain to HRU
const double *slope;         // (m/m)
const double *length;        // length normal to creek
const double *Kbtm;         // bottom hydraulic conductivity (m/d)
const double *Ktop;         // bottom hydraulic conductivity (m/d)
const double *ztrn;         // transition depth (m)
const double *Residual;      // Organic non-drainable porosity ()
const double **Residual_lay; // Organic non-drainable porosity ()
const double *n_const;       // Van Genutchen constant
const double **n_const_lay;  // Van Genutchen constant
const double *a_const;       // Van Genutchen constant
const double **a_const_lay;  // Van Genutchen constant
const double *Drained;       // depth of surface drained organic material (m)
const double *FrozenTo;      // initial depth of frost table (m)
const double *runoffstorage; // runoff parameter ()
const double *runoffLag;     // runoff parameter ()
const double *flowstorage;   // flow parameter ()
const double *flowLag;       // flow parameter ()

const double *d;             // depth of layer  (m)
const double **d_lay;        // depth of layer  (m)
const double *Pors;          // filler only gives first value
const double **Pors_def;     // array of all values
const long  *soil_type;
const long  **soil_type_lay;
const double *tinit;         // initial layer temperature (°C)
const double **tinit_lay;    // initial layer temperature (°C)

// declared variables
double *Depth;          // hydraulic conductivity (m/day)
double *k;              // hydraulic conductivity (m/day)
double *d_surface;      // debug
double *watertable;     // water table depth (m)
double *dmelt;          // melt depth (m)
double *flowin;         // flowin depth (m/m2)
double *flowinm3;       // flowin depth (m3)
double *cumflowin;      // cumulative flowin depth (m)
double *runoff;         // runoff ((m/m2)/int)
double *runoffDly;      // runoff ((m/m2)/int)
double *runoffm3Dly;    // runoff (m3/int)
double *cumrunoff;      // cumulative runoff (m)
double *flow;           // total flow (m/int)
double *flowDly;        // total flow (m/int)
double *flowm3Dly;      // total flow (m3/int)
double *cumflow;        // cumulative total flow from all layers(m3/s)
double *loss;           // total loss (m/int)
double *transit;        // transit time through HRU (hr)
double *theta;          // soil moisture (m3/m3)
double **theta_lay;     // soil moisture (m3/m3)
double *layerwater;      // thawed water depth in layer (m)
double **layerwater_lay; // thawed water depth in layer (m)
double *capillary;      // locked thawed water depth in layer (m)
double **capillary_lay; // locked thawed water depth in layer (m)
double *tension;        // capillary tension (m)
double **tension_lay;   // capillary tension (m)
double *wDrained;       // working depth of surface drained organic material (m)

double *Cvis;         // frozen/saturated
double **Cvis_lay;    // heat capacity (J/m3/K)

double *Cvisa;       // frozen/unsaturated
double **Cvisa_lay;  // heat capacity (J/m3/K)

double *Cvws;        // unfrozen/saturated
double **Cvws_lay;   // heat capacity (J/m3/K)

double *Cvwsa;       // unfrozen/unsaturated
double **Cvwsa_lay;  // heat capacity (J/m3/K)

double *lamis;       // frozen/saturated
double **lamis_lay;  // thermal conductivity (W/m/K)

double *lamws;       // unfrozen/saturated
double **lamws_lay;  // thermal conductivity (W/m/K)

double *lamwsa;      // unfrozen/unsaturated
double **lamwsa_lay; // thermal conductivity (W/m/K)

double *tlayer;         // layer temperature (°C)
double **tlayer_lay;    // layer temperature (°C)

// local constants

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classquinton* klone(string name) const;
};

double Farouki_a(double fract_por);

class Classqdrift : public ClassModule {
public:

Classqdrift(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

ClassClark *Delaymelt;

// declared observation variables
const double *p;

// input variables
const double *hru_p;

// declared variables
double *SWE;
double *driftmelt;
double *driftmeltDly;
double *cumdriftmelt;
double *cumdriftmeltDly;
double *driftmeltD;
double *snowmeltD;

// declared parameters
const long *Type;      // NOTUSED, DRIFT or HUMMOCK
const long *DrainTo;   // drain to HRU
const double *InitSWE;  // initial SWE
const double *length;   // length normal to creek
const double *meltstorage;  // delay parameter (days)
const double *meltLag;      // delay parameter (days)

// variable inputs
const double *Qm;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classqdrift* klone(string name) const;
};

class ClassXGAyers : public ClassModule {
public:

ClassXGAyers(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};

// declared observation variables

// declared variables
double *infil;         // unfrozen infiltration
double *cuminfil;      // cumulative unfrozen infiltration
double *snowinfil;     // frozen infiltration
double *cumsnowinfil;  // cumulative frozen infiltration
double *meltrunoff;      // [nhru]
double *cummeltrunoff; // cumulative frozen melt runoff
double *runoff;        // cumulative runoff
double *cumrunoff;     // cumulative melt runoff

// variable put

// local variables
long *infiltype;

// declared parameters
const double *basin_area;  // [BASIN]
const double *hru_area;
const long  *texture;
const long  *groundcover;

// variable inputs
const double *snowmeltD;   // (mm/day)
const double *net_rain;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassXGAyers* klone(string name) const;
};

class ClassCRHMCanopyClearing:public ClassModule {

public:

ClassCRHMCanopyClearing(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 2000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_, Qli_;

// observation variables

const double *Qsi;
const double *Qli;

// declared observation variables

double *Ts;
double *Qnsn;
double *Qsisn;
double *Qlisn;
double *Qlosn;

// put variables

double *SWE;

// declared variables

double *drip_Cpy;
double *thrufall_Cpy;
double *netRain_Cpy;
double *direct_rain;
double *rain_load;
double *Snow_load;
double *direct_snow;
double *SUnload;
double *SUnload_H2O;
double *Qnsn_Var;
double *Qsisn_Var;
double *Qlisn_Var;

double *net_rain;
double *cum_net_rain;
double *net_snow;
double *cum_net_snow;
double *net_p;
double *intcp_evap;
double *cum_intcp_evap;
double *Subl_Cpy;
double *cum_Subl_Cpy;
double *cum_SUnload;
double *cum_SUnload_H2O;

double *Cc;
double *k;
double *Tauc;
double *Pa;
double *ra;
double *u_FHt;
double *Pevap;

// variable inputs

const double *hru_t;
const double *hru_u;
const double *hru_rh;
const double *hru_ea;
const double *Albedo;

const double *hru_snow;
const double *hru_rain;
const double *hru_evap;

const double *SolAng;

const double *QsiS_Var;
const double *QsiA_Var;
const double *QliVt_Var;

// declared parameters:

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_elev;
const double *Ht;
const double *LAI;
const double *Sbar;
const double *Z0snow;
const double *Zref;
const double *Zwind;
const double *Zvent;
const double *unload_t;
const double *unload_t_water;
const double *Alpha_c;
const double *B_canopy;

const long *CanopyClearing;
const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/°C
double gamma(double Pa, double t); // Psychrometric constant (kPa/°C)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg °C))

ClassCRHMCanopyClearing* klone(string name) const;

};

class ClassCRHMCanopyClearingGap:public ClassModule {

public:

ClassCRHMCanopyClearingGap(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

double Qsi_, Qli_;

// observation variables

const double *Qsi;
const double *Qli;

// declared observation variables

double *Ts;
double *Qnsn;
double *Qsisn;
double *Qlisn;
double *Qlosn;

// put variables

double *SWE;

// declared variables

double *drip_Cpy;
double *thrufall_Cpy;
double *netRain_Cpy;
double *direct_rain;
double *rain_load;
double *Snow_load;
double *direct_snow;
double *SUnload;
double *SUnload_H2O;
double *Qnsn_Var;
double *Qsisn_Var;
double *Qlisn_Var;

double *net_rain;
double *cum_net_rain;
double *net_snow;
double *cum_net_snow;
double *net_p;
double *intcp_evap;
double *cum_intcp_evap;
double *Subl_Cpy;
double *cum_Subl_Cpy;
double *cum_SUnload;
double *cum_SUnload_H2O;

double *Cc;
double *k;
double *Tauc;
double *Pa;
double *ra;
double *u_FHt;
double *Pevap;

// variable inputs

const double *hru_t;
const double *hru_u;
const double *hru_rh;
const double *hru_ea;
const double *Albedo;

const double *hru_snow;
const double *hru_rain;
const double *hru_evap;

const double *SolAng;
const double *cosxs;
const double *cosxsflat;
const double *Qdfo;

const double *QsiS_Var;
const double *QsiA_Var;
const double *QliVt_Var;

// declared parameters:

const double *basin_area;   // [BASIN]
const double *hru_area;
const double *hru_elev;
const double *Ht;
const double *LAI;
const double *Sbar;
const double *Z0snow;
const double *Zref;
const double *Zwind;
const double *Zvent;
const double *unload_t;
const double *unload_t_water;
const double *Surrounding_Ht;
const double *Gap_diameter;
const double *Alpha_c;
const double *B_canopy;

const long *CanopyClearing;
const long *inhibit_evap;


void decl(void);
void init(void);
void run(void);
void finish(bool good);

double delta(double t); // Slope of sat vap p vs t, kPa/°C
double gamma(double Pa, double t); // Psychrometric constant (kPa/°C)
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double lambda(double t); // Latent heat of vaporization (mJ/(kg °C))

ClassCRHMCanopyClearingGap* klone(string name) const;
};

class ClassGrow_Crop : public ClassModule {
public:

ClassGrow_Crop(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *Crop_Ht;

// declared parameters
const double *Ht;
const double *Crop_Grow_Rate;
const double *JCrop_Start;
const double *JCrop_Mature;
const double *JCrop_Harvest;
const double *Init_Crop_Ht;

// variable inputs

void decl(void);
void init(void);
void run(void);

ClassGrow_Crop* klone(string name) const;
};

class ClassREWroute_stream : public ClassModule {
public:

ClassREWroute_stream(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long instreamflowCnt;
long gwCnt;

// declared variables
double *rew;

double **instreamflow_All;
double **instreamflow_Grp_out_All;

double *instreamflow;        // [nhru]
double *cuminstreamflow;     // [nhru]
double *outstreamflow;       // [nhru]
double *cumoutstreamflow;    // [nhru]

double *streamflow;     // [BASIN] all HRUs
double *streamflow_s;   // [BASIN] all HRUs
double *cumstreamflow;  // [BASIN] all HRUs

double *WS_stream_Ktravel_var;         // [nhru]

double *culvert_Q;
double *culvert_water_H;
double *culvert_water_A;
double *culvert_water_V;
double *culvert_water_O;
double *culvert_evap;
double *cum_culvert;
double *cum_culvert_over;
double *HD;

ClassMuskingum *instreamflowDelay;

ClassClark *Clark_instreamflowDelay;

// declared parameters

const double *WS_stream_route_n;         // [nhru]
const double *WS_stream_route_R;         // [nhru]
const double *WS_stream_route_S0;        // [nhru]
const double *WS_stream_route_L;         // [nhru]
const long  *WS_stream_Channel_shp;      // [nhru]

const double *WS_stream_Lag;             // [nhru]
const double *WS_stream_route_X_M;       // [nhru]
const long  *WS_stream_whereto_Grp;     // [nhru]
const long  *WS_stream_wherefrom_HRU;   // [nhru]
const long  *WS_stream_whereto_HRU;     // [nhru]
const long  *WS_stream_order;           // [nhru]

const double *WS_stream_Kstorage;     // [nhru]

const double *WS_stream_channel_slope;
const double *WS_stream_side_slope;
const double *WS_stream_culvert_diam;
const double *WS_stream_culvert_water_Dmax;
const double *WS_stream_number_culverts;

const long *WS_stream_culvert_type;

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

ClassREWroute_stream* klone(string name) const;
};

class ClassICEflow : public ClassModule {
public:

ClassICEflow(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1001, "") {};

// declared variables
double *Ux;
double *Ub;
double *Utot;
double *Ice_in;
double *Ice_out;
double *cumIce_in;
double *cumIce_out;
double *cumulative_net_rain;

// declared parameters
const double *distrib;
const double *radius_glacier;
const double *Arrhenius_const;
const double *slip_c;
const double *slip_m;
const double *slip_sf;
const double *slip_fs;
const double **distrib_hru;
const double *basin_area;   // [BASIN]
const double *hru_area; // [nhru]
const double *test_option; // [nhru]
const long  *SWE_to_firn_Julian;
const long  *order; // [nhru]
const long *Disable_ICEflow; // [nhru]
const long  *channel_option; // [nhru]
const double *basal_option; // [nhru]

// variable get inputs
const double *firn;
const double *net_rain;
const double *hru_GSL;

// variable get/put inputs
double *ice;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassICEflow* klone(string name) const;
};

class Classglacier : public ClassModule {
public:

Classglacier(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " ,snowmeltD"){};

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
const double *glacier_Albedo_obs;

ClassClark *SWEDelay;
ClassClark *firnDelay;
ClassClark *iceDelay;

// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

Classglacier* klone(string name) const;
double DepthofSnow(double SWE);
};

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

class ClassSWEslope : public ClassModule {
public:

ClassSWEslope(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "glacier_h2o, snowmeltD") {};

// declared variables
double *SWE_in;
double *SWE_out;
double *cumSWE_in;
double *cumSWE_out;
double *Hd;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area; // [nhru]
const double *hru_GSL;    // [nhru]
const double *use_rho;    // [nhru]
const double *snow_density;    // [nhru]
const double *Hd_min;    // [nhru]
const long *order; // [nhru]
const double *distrib_SWEslope;
const double **distrib_hru;
const long *Disable_SWEslope; // [nhru]

// variable put inputs
double *SWE;

// variable inputs 
const double *rho;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSWEslope* klone(string name) const;
};

class ClassTestSparse : public ClassModule {
public:

ClassTestSparse(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long ObsCnt_N_up;
long ObsCnt_P_up;
long ObsCntMan_N_up;
long ObsCntMan_P_up;
long ObsCntRes_N_up;
long ObsCntRes_P_up;
long ObsCnt_N_down;
long ObsCnt_P_down;
long ObsCntMan_N_down;
long ObsCntMan_P_down;
long ObsCntRes_N_down;
long ObsCntRes_P_down;
long ObsCnt_fertperiod;
long ObsCnt_litterperiod;

// declared variables
double *Fert_N_Var;
double *Fert_P_Var;
double *Man_N_Var;
double *Man_P_Var;
double *Res_N_Var;
double *Res_P_Var;
double *Fert_period_Var;
double *Litter_period_Var;

// declared parameters

// put parameters

// declared observation variables
const double *Fert_N_up;
const double *Fert_P_up;
const double *Man_N_up;
const double *Man_P_up;
const double *Res_N_up;
const double *Res_P_up;
const double *Fert_N_down;
const double *Fert_P_down;
const double *Man_N_down;
const double *Man_P_down;
const double *Res_N_down;
const double *Res_P_down;
const double *Fert_period;
const double *Litter_period;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassTestSparse* klone(string name) const;
};
#endif
