//created by Manishankar Mondal

#include "ClassModule.h"

class ClassSimpleRichard : public ClassModule {

    public:

    ClassSimpleRichard(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables

    const float *Qsi;  // Downward shortwave radiation (W/m2)
    const float *Qli;  // Downward longwave radiation (W/m2)
    const float *snow; // Snowfall (kg/m2/s)
    const float *t;    // Air temperature (°K)
    const float *u;    // Wind speed (m/s)
    const float *rh;   // Relative humidity (%)

// declared variables

    float *SWE;       // (kg/m2)
    float *alb;       // Snow albedo
    float *snowmelt;  // (kg/m2)
    float *meltclark; // (kg/m2)
    float *sursubl;   // (kg/m2)
    float *T0;   // Surface temperature (°K)

    float *LE;   // Latent heat flux (W/m^2)
    float *H;    // Sensible heat flux (W/m^2)
    float *Hsm;  // Snowmelt heat flux (W/m^2)
    float *LWn;  // Net longwave radiation (W/m^2)
    float *SWn;  // Net shortwave radiation (W/m^2)

// declared parameters

    const float *a1;   // Albedo decay time constant for cold snow (s)
    const float *a2;   // Albedo decay time constant for melting snow (s)
    const float *amin; // Minimum albedo for aged snow
    const float *amax; // Maximum albedo for fresh snow
    const float *smin; // Minimum snowfall to refresh snow albedo (mm)
    const float *Ht;   // Roughness length
    const float *Zref;   // Reference height
    const float *Pa;   // Average surface pressure (KPa)
    const float *Kstorage; // [nhru]
    const float *Lag;      // [nhru]
    const float *Z0snow;   // snow roughness length (m)

// variable inputs

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good);

    ClassSimpleRichard* klone(string name) const;

    void EXCH(long hh, float Q1, float U1, float &CH);

    void ALBEDO(long hh);

    void SURF(long hh, float Q1, float U1);

// local class

    ClassClark *Delays;

    float dt;
};