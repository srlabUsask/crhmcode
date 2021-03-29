//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassSimpleRichard : public ClassModule {

    public:

    ClassSimpleRichard(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared observation variables

    const double *Qsi{ NULL };  // Downward shortwave radiation (W/m2)
    const double *Qli{ NULL };  // Downward longwave radiation (W/m2)
    const double *snow{ NULL }; // Snowfall (kg/m2/s)
    const double *t{ NULL };    // Air temperature (K)
    const double *u{ NULL };    // Wind speed (m/s)
    const double *rh{ NULL };   // Relative humidity (%)

// declared variables

    double *SWE{ NULL };       // (kg/m2)
    double *alb{ NULL };       // Snow albedo
    double *snowmelt{ NULL };  // (kg/m2)
    double *meltclark{ NULL }; // (kg/m2)
    double *sursubl{ NULL };   // (kg/m2)
    double *T0{ NULL };   // Surface temperature (K)

    double *LE{ NULL };   // Latent heat flux (W/m^2)
    double *H{ NULL };    // Sensible heat flux (W/m^2)
    double *Hsm{ NULL };  // Snowmelt heat flux (W/m^2)
    double *LWn{ NULL };  // Net longwave radiation (W/m^2)
    double *SWn{ NULL };  // Net shortwave radiation (W/m^2)

// declared parameters

    const double *a1{ NULL };   // Albedo decay time constant for cold snow (s)
    const double *a2{ NULL };   // Albedo decay time constant for melting snow (s)
    const double *amin{ NULL }; // Minimum albedo for aged snow
    const double *amax{ NULL }; // Maximum albedo for fresh snow
    const double *smin{ NULL }; // Minimum snowfall to refresh snow albedo (mm)
    const double *Ht{ NULL };   // Roughness length
    const double *Zref{ NULL };   // Reference height
    const double *Pa{ NULL };   // Average surface pressure (KPa)
    const double *Kstorage{ NULL }; // [nhru]
    const double *Lag{ NULL };      // [nhru]
    const double *Z0snow{ NULL };   // snow roughness length (m)

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

    ClassClark *Delays{ NULL };

    double dt{0.0};
};