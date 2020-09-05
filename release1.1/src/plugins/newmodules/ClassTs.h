//created by Manishankar Mondal

#include "ClassModule.h"

class ClassTs : public ClassModule {

    public:

    ClassTs(string Name, string Version = "Radiation", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, "QliVt_Var, ") {};

// declared observations
    float *Ts;

// declared observation variables

    const float *hru_u;

    const float *hru_t;

    const float *hru_rh;

    const float *Qli;

    const float *QliVt_Var;

// declared variables

   float *hru_Ts;

   float *Pa;

   float *q;

   float *ra;

   float *Qli_;

// declared parameters

   const float *Ht;

   const float *Zref;

   const float *Zwind;

   const float *hru_elev;

   const float *Z0snow; // snow roughness length (m)

// variable inputs


    void decl(void);
    void init(void);
    void run(void);

ClassTs* klone(string name) const;
};