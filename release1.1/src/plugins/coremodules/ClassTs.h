//created by Manishankar Mondal

#include "ClassModule.h"

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