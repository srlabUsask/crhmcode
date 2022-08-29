/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include "../core/ClassModule.h"

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
