//created by Manishankar Mondal

#include "ClassModule.h"

class ClassNeedle : public ClassModule {

    public:

    ClassNeedle(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

    double Qli_;

    double Qsi_;

// declared observations

    double *Ts;

    double *Qnsn;

    double *Qsisn;

    double *Qlisn;

    double *Qlosn;

// declared observation variables

    const double *Qsi;

    const double *Qli;

    const double *QsiA_Var;

    const double *QsiS_Var;

    const double *QliVt_Var;

// declared variables

   double *Pa;

   double *k;

   double *Tauc;

   double *ra;

   double *Qnsn_Var;

// declared parameters

   const double *LAI;

   const double *Ht;

   const double *Zwind;

   const double *Zref;

   const double *hru_elev;

   const double *Z0snow; // snow roughness length (m)


// variable inputs

    const double *beta;

    const double *SWE;

    const double *Albedo;

    const double *hru_t;

    const double *hru_u;

    const double *hru_ea;

    const double *hru_rh;


    void decl(void);

    void init(void);

    void run(void);

ClassNeedle* klone(string name) const;
};