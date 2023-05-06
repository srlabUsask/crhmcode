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

    constexpr double calc_rainsplash_energy(double intensity);
    double calculate_rainsplash_mobilization();
    double calculate_flow_mobilization_HYPE(double runoff);

    double calc_critical_shear_stress_nodim_VANRIJN(double diam_nodim);
    double calc_rill_flowdepth_from_manning(double flow_rate);
    double calc_rill_flowvel_from_flowdepth(double flow_rate, double h);
    double calc_bed_shear_stress(double stream_depth);
    double calc_nodim_diam( double diam );
    double calc_nodim_shear_stress( double tau_b );
    double calc_dim_bed_flux( double bed_flux_nodim );
    double VANRIJN( double tau_b_nodim , double tau_crit_nodim, double diam_nodim );
    void   initialize_VANRIJN();
    double calculate_flow_mobilization_VANRIJN(double runoff);


    double *conc_soil_rechr{ NULL };
    double **conc_soil_rechr_lay{ NULL };
    double *conc_soil_lower{ NULL };   // concentration of sediment (always zero)
    double **conc_soil_lower_lay{ NULL };

    const double *runoff{ NULL };
    const double *scf{ NULL };

// Vars for the vanRijn formulation
    double *diam_nodim{ NULL };
    double *tau_crit_nodim{ NULL };
    double *bed_flux{ NULL };      // debugging
    double *tau_b_nodim{ NULL };   // debugging
    double *tau_b{ NULL };   // debugging
    double *stream_depth{ NULL };   // debugging
// ******

    const double *soil_runoff{ NULL };   // mm (*km^2)/int
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

/* Parameters for van Rijn formulation */
    const double *channel_pct{ NULL }; // ()
    const double *sedslope{ NULL }; // ()
    const double *mannings_n{ NULL }; // ()
    const double *d50{ NULL }; // (m)
    const double *hru_area{ NULL }; // (m)

};

#endif
