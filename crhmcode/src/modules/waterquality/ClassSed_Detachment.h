// 11/20/19
//---------------------------------------------------------------------------
#ifndef Sed_Detachment
#define Sed_Detachment
//---------------------------------------------------------------------------

#include "../../core/ClassModule.h"
#include "WQ_CRHM.h"

using namespace std;


class ClassSed_Detachment : public ClassModule {
    public:

    long dayno{0};

    ClassSed_Detachment(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

    ClassSed_Detachment* klone(string name) const;

    void decl(void);
    void init(void);
    void run(void);
    void finish(bool good);

    void runoff_sed_by_erosion();
    void calculate_erosion(double& erodedSed);
    void calculate_transport(const double flow, double& erodedSed);

    double *conc_soil_rechr{ NULL };
    double **conc_soil_rechr_lay{ NULL };
    double *conc_soil_lower{ NULL };   // concentration of sediment (always zero)
    double **conc_soil_lower_lay{ NULL };

    const double *runoff{ NULL };
    const double *scf{ NULL };

    const double *soil_runoff{ NULL };
    double *soil_runoff_cWQ{ NULL };
    double **soil_runoff_cWQ_lay{ NULL };

    const double *snowmelt_int{ NULL };
    const double *snowmeltD{ NULL };
    const double *net_rain{ NULL };

    double *sedrelpool{ NULL }; // (Particulate P release from soil due to erosion (kg/km2=mg/m2) (kg/km2/mm=mg/L)

/*******************
 * PARAMETERS
 *******************/
    const double *sedrelmax{ NULL }; // (mm)
    const double *sedrelexp{ NULL }; // ()
    const double *sreroexp{ NULL }; // ()
    const double *erodibility{ NULL }; // (g/J)
    const double *cohesion{ NULL }; // (kPa)

};

#endif
