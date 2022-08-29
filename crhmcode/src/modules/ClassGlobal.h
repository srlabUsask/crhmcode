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



class Classglobal : public ClassModule {
public:

Classglobal(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

// declared variables
double *QdroD{ NULL };
double *QdroDext{ NULL };
double *QdfoD{ NULL };
double *Qdro{ NULL };
double *Qdfo{ NULL };
double *Qdflat{ NULL };
double *QdflatD{ NULL };
double *QdflatE{ NULL };
double *SolAng{ NULL };
double *SunMax{ NULL };
double *cosxs{ NULL };
double *cosxsflat{ NULL };
double *pQdro{ NULL };
double **pQdro_FREQ{ NULL };
double *pQdfo{ NULL };
double **pQdfo_FREQ{ NULL };
double *pQdflat{ NULL };
double **pQdflat_FREQ{ NULL };
double *pQdflatE{ NULL };
double **pQdflatE_FREQ{ NULL };
double *pSol{ NULL };
double **pSol_FREQ{ NULL };
double *pCosxs{ NULL };
double **pCosxs_FREQ{ NULL };
double *pCosxs0{ NULL };
double **pCosxs0_FREQ{ NULL };

// declared parameters
const double *hru_lat{ NULL };
const double *hru_elev{ NULL };
const double *hru_GSL{ NULL };
const double *hru_ASL{ NULL };
const double *Time_Offset{ NULL };

//const long  *Extra;

// variable inputs

void air_mass (const double czen, double &oam);

void decl(void);
void init(void);
void run(void);

Classglobal* klone(string name) const;
};
