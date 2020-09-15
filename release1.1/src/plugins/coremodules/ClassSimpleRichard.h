//created by Manishankar Mondal

#include "ClassModule.h"

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