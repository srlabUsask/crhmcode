// 11/20/19
//---------------------------------------------------------------------------
#ifndef Sed_Transport
#define Sed_Transport
//---------------------------------------------------------------------------

#include "../../core/ClassModule.h"
#include "WQ_CRHM.h"

using namespace std;



class ClassSed_Transport__vr : public ClassModule {
    public:



// ********* Extra constants:

double visc = 1.004e-6;  // kinematic viscosity coefficient of water (20C)
double g = 9.81;  // gravity (m/s2)
double rho_sed = 2650;  // kg/m3 for quartz
double rho_w = 1000;  // kg/m3 for water
double s = rho_sed / rho_w; 

// bed material sd could be calculated from 0.5 (D84/D50 + D16/D50) if the particle distribution profile was reliable enough
double bed_material_sd = 2.5;   // (sigma_s) From Van Rijn Suspended transport (84), p. 1630-1631
double von_Karman = 0.4;  // von Karman constant for clear flow
//double mannings_n = 0.104;  // check loch et al. 89 for values

// Constants for Van Rijn (suspended transport)
double MAX_BEDCONC = 0.65;

// *******************



    long dayno{0};

    ClassSed_Transport__vr(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

    ClassSed_Transport__vr* klone(string name) const;

    void decl(void);
    void init(void);
    void run(void);
    void finish(bool good);




/*****************************************************************
 * Particle Size Distribution Routines
******************************************************************/

    double calc_vcsi_diam_percentile(double percentile, double pct_sand, double pct_silt);


/*****************************************************************
 * van Rijn Support Routines
******************************************************************/

    double calc_critical_shear_stress_nodim_VANRIJN(double diam_nodim);

/*****************************************************************
 * van Rijn Bedload Transport Routines
******************************************************************/

    double calc_vanrijn_flowdepth_from_manning(double flow_rate);
    double calc_vanrijn_flowvel_from_flowdepth(double flow_rate, double h);
    double calc_bed_shear_stress(double stream_depth);
    double calc_nodim_diam( double diam );
    double calc_nodim_shear_stress( double tau_b );
    double calc_dim_bed_flux( double bed_flux_nodim );
    double VANRIJN( double tau_b_nodim , double tau_crit_nodim, double diam_nodim );

    double calc_bedload_transport_cap(double runoff);

/*****************************************************************
 * van Rijn Suspended Transport Routines
******************************************************************/

    double calc_vr_transport_stage(double streamwidth);
    double calc_vr_ref_level(double streamdepth);
    double calc_vr_ref_conc(double ref_level, double transport_stage);
    double calc_vr_diam_susp(double transport_stage);
    double calc_vr_fallvel(double transport_stage);
    double calc_vr_shearvel(double streamdepth);
    double calc_vr_beta_factor(double shearvel, double fallvel);
    double calc_vr_phi_factor(double fallvel, double shearvel, double ref_conc);
    double calc_vr_susp_param(double transport_stage, double shearvel, double ref_conc);
    double calc_vr_f_factor(double ref_level, double ref_conc, double streamdepth, double transport_stage);
    double calc_vr_susp_load_transport(double streamvel, double streamwidth, double streamdepth);


/*****************************************************************
 * van Rijn Miscellaneous Routines
******************************************************************/

    void   initialize_VANRIJN();
    double calc_vr_load_transport_rect(double streamflow );
//    double calculate_flow_mobilization_VANRIJN(double runoff);


/*****************************************************************
 * VARIABLES
******************************************************************/

    const double *outflow{ NULL };       // [nhru]
    double *outflow_mWQ{ NULL };       // [ndefn]
    double **outflow_mWQ_lay{ NULL };       // [ndefn]

// Vars for the vanRijn formulation
    double *pct_sand{ NULL }; // ()

    double *diam50{ NULL };   // mm
    double *diam90{ NULL };   // mm
    double *diam_nodim{ NULL };
    double *tau_crit_nodim{ NULL };

// Vars for debugging    
    double *bed_flux{ NULL };      // debugging
    double *tau_b_nodim{ NULL };   // debugging
    double *tau_b{ NULL };   // debugging
    double *stream_depth{ NULL };   // debugging
    double *mass_suspended{ NULL };      // debugging
    double *mass_bedload{ NULL };      // debugging
// ******

    const double *pct_clay{ NULL }; // ()
    const double *pct_silt{ NULL }; // ()

/*******************
 * PARAMETERS
 *******************/

/* Parameters for van Rijn formulation */
    const double *channel_width{ NULL };
    const double *channel_slope{ NULL }; // ()
    const double *channel_pct{ NULL }; // ()
    const double *vr_mannings_n{ NULL }; // ()
    const double *vr_roughness_height{ NULL }; // ()
    const double *hru_area{ NULL }; // (m)

};




#endif
