//created by Manishankar Mondal

#include "ClassModule/ClassModule.h"

class ClassTs : public ClassModule {

    public:

    ClassTs(string Name, string Version = "Radiation", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, "QliVt_Var, ") {};

// declared observations
    double *Ts{ NULL };

// declared observation variables

    const double *hru_u{ NULL };

    const double *hru_t{ NULL };

    const double *hru_rh{ NULL };

    const double *Qli{ NULL };

    const double *QliVt_Var{ NULL };

// declared variables

   double *hru_Ts{ NULL };

   double *Pa{ NULL };

   double *q{ NULL };

   double *ra{ NULL };

   double *Qli_{ NULL };

// declared parameters

   const double *Ht{ NULL };

   const double *Zref{ NULL };

   const double *Zwind{ NULL };

   const double *hru_elev{ NULL };

   const double *Z0snow{ NULL }; // snow roughness length (m)

// variable inputs


    void decl(void);
    void init(void);
    void run(void);

ClassTs* klone(string name) const;
};