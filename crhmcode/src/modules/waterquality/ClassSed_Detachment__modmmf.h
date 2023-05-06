// 11/20/19
//---------------------------------------------------------------------------
#ifndef Sed_Detachment
#define Sed_Detachment
//---------------------------------------------------------------------------

#include "../../core/ClassModule.h"
#include "WQ_CRHM.h"

using namespace std;



struct sed_triple {
    double c;
    double z;
    double s;
};



class ClassSed_Detachment : public ClassModule {
    public:

    long dayno{0};

    ClassSed_Detachment(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

    ClassSed_Detachment* klone(string name) const;

    void decl(void);
    void init(void);
    void run(void);
    void finish(bool good);


/*****************************************************************
 * HYPE Routines
******************************************************************/

    void runoff_sed_by_erosion();


/*****************************************************************
 * Modified [or Daily] Morgan-Morgan-Finney Routines
******************************************************************/

    double calc_flowvel_manning(double depth, double n);
    double calc_flowvel_veg();
    double calc_tillage_n();

    constexpr double calc_rainsplash_energy(double intensity);
    void calc_rainsplash_mobilization( sed_triple &rslt);
    void calc_flow_mobilization(double runoff, sed_triple &rslt);
    void calc_flow_deposition( bool mixed_sed, sed_triple &rslt);
    void calc_delivered_to_transport(sed_triple &rslt);
    void calc_transport_capacity(sed_triple &rslt);
    void calc_sed_balance(sed_triple &rslt);
    double calc_erosion();
    void initialize_modMMF();


/*****************************************************************
 * van Rijn Routines
******************************************************************/

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


/*****************************************************************
 * VARIABLES
******************************************************************/

    double *conc_soil_rechr{ NULL };
    double **conc_soil_rechr_lay{ NULL };
    double *conc_soil_lower{ NULL };   // concentration of sediment (always zero)
    double **conc_soil_lower_lay{ NULL };

    const double *runoff{ NULL };
    const double *scf{ NULL };

// Vars for the modified MMF formulation
    double *pct_sand{ NULL }; // ()

    double *DEP_immed_c{ NULL }; // (%)
    double *DEP_immed_z{ NULL }; // (%)
    double *DEP_immed_s{ NULL }; // (%)
    double *DEP_channel_c{ NULL }; // (%)
    double *DEP_channel_z{ NULL }; // (%)
    double *DEP_channel_s{ NULL }; // (%)

    double *v_std_bare{ NULL };  // m/s
    double *v_actual{ NULL };  // m/s
    double *v_veg{ NULL };  // m/s
    double *v_tillage{ NULL };  // m/s

// Just for debugging, remove once working well
    double *mob_rainsplash{ NULL };  // m/s
    double *mob_flow{ NULL };  // m/s
    double *sed_delivered_z{ NULL };  // m/s
    double *sed_transported_z{ NULL };  // m/s



// Vars for the vanRijn formulation
    double *diam_nodim{ NULL };
    double *tau_crit_nodim{ NULL };
    double *bed_flux{ NULL };      // debugging
    double *tau_b_nodim{ NULL };   // debugging
    double *tau_b{ NULL };   // debugging
    double *stream_depth{ NULL };   // debugging
// ******

    const double *soil_runoff{ NULL };   // mm (*km^2)/int
    double *soil_runoff_mWQ{ NULL };   // (g/int)
    double **soil_runoff_mWQ_lay{ NULL };   // (g/int)

    const double *snowmelt_int{ NULL };
    const double *snowmeltD{ NULL };
    const double *net_rain{ NULL };

// Vars for the HYPE delay pool
    double *sedrelpool{ NULL }; // (Particulate P release from soil due to erosion (kg/km2=mg/m2) (kg/km2/mm=mg/L)

/*******************
 * PARAMETERS
 *******************/

// Parameters for the HYPE delay pool
    const double *sedrelmax{ NULL }; // (mm)
    const double *sedrelexp{ NULL }; // ()
    const double *sreroexp{ NULL }; // ()


//    const double *erodibility{ NULL }; // (g/J)
//    const double *cohesion{ NULL }; // (kPa)

/* Parameters for modified MMF formulation */
    const double *mmf_mannings_n{ NULL }; // ()
    const double *mmf_repr_depth{ NULL }; // ()
    const double *sfcslope{ NULL }; // (degrees)
    const double *slopelen{ NULL }; // (m)

    const double *canopy_cvg{ NULL }; // ()
    const double *plant_height{ NULL }; // ()
    const double *ground_cover{ NULL }; // ()

    const double *mmf_d_bare{ NULL }; // ()
    const double *mmf_d_actual{ NULL }; // ()
    const double *mmf_d_tillage{ NULL }; // ()
    const double *mmf_n_bare{ NULL }; // ()
    const double *mmf_n_actual{ NULL }; // ()

    const double *erodibility_clay{ NULL }; // ()
    const double *erodibility_silt{ NULL }; // ()
    const double *erodibility_sand{ NULL }; // ()
    const double *detachibility_clay{ NULL }; // ()
    const double *detachibility_silt{ NULL }; // ()
    const double *detachibility_sand{ NULL }; // ()

    const double *pct_clay{ NULL }; // ()
    const double *pct_silt{ NULL }; // ()


/* Parameters for van Rijn formulation */
    const double *channel_slope{ NULL }; // ()
    const double *channel_pct{ NULL }; // ()
    const double *vr_mannings_n{ NULL }; // ()
    const double *d50{ NULL }; // (m)
    const double *hru_area{ NULL }; // (m)

};

#endif
