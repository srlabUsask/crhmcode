//created by Manishankar Mondal

#include "ClassSnobalBase.h"

class ClassSnobalX : public ClassSnobalBase {

    public:

    ClassSnobalX(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalX* klone(string name) const;

// variable climate-data inputs

    const float  *S_n_X;      // net solar radiation (W/m^2)
    const float  *I_lw_X;     // incoming longwave (thermal) rad (W/m^2)
    const float  *T_a_X;      // air temp (C)
    const float  *e_a_X;      // vapor pressure (Pa)
    const float  *u_X;        // wind speed (m/sec)
    const float  *T_g_X;      // soil temp at depth z_g (C)
    const float  *F_g_X;      // soil flux at depth z_g ()

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2)
    const float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2)
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2)
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2)
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2)
    const float  *rho_snow_X;   // density of snowfall               (kg/m^3)
    const float  *T_pp_X;       // precip temp (C)


    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};