//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNeedle : public ClassModule {

    public:

    ClassNeedle(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

    float Qli_;

    float Qsi_;

// declared observations

    float *Ts;

    float *Qnsn;

    float *Qsisn;

    float *Qlisn;

    float *Qlosn;

// declared observation variables

    const float *Qsi;

    const float *Qli;

    const float *QsiA_Var;

    const float *QsiS_Var;

    const float *QliVt_Var;

// declared variables

   float *Pa;

   float *k;

   float *Tauc;

   float *ra;

   float *Qnsn_Var;

// declared parameters

   const float *LAI;

   const float *Ht;

   const float *Zwind;

   const float *Zref;

   const float *hru_elev;

   const float *Z0snow; // snow roughness length (m)


// variable inputs

    const float *beta;

    const float *SWE;

    const float *Albedo;

    const float *hru_t;

    const float *hru_u;

    const float *hru_ea;

    const float *hru_rh;


    void decl(void);

    void init(void);

    void run(void);

ClassNeedle* klone(string name) const;
};