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

class ClassXGAyers : public ClassModule {
public:

ClassXGAyers(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl),
                                    infiltype(NULL) {};

// declared observation variables

// declared variables
double *infil{ NULL };         // unfrozen infiltration
double *cuminfil{ NULL };      // cumulative unfrozen infiltration
double *snowinfil{ NULL };     // frozen infiltration
double *cumsnowinfil{ NULL };  // cumulative frozen infiltration
double *meltrunoff{ NULL };      // [nhru]
double *cummeltrunoff{ NULL }; // cumulative frozen melt runoff
double *runoff{ NULL };        // cumulative runoff
double *cumrunoff{ NULL };     // cumulative melt runoff

// variable put

// local variables
long *infiltype{ NULL };

// declared parameters
const double *basin_area{ NULL };  // [BASIN]
const double *hru_area{ NULL };
const long  *texture{ NULL };
const long  *groundcover{ NULL };

// variable inputs
const double *snowmeltD{ NULL };   // (mm/day)
const double *net_rain{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassXGAyers* klone(string name) const;
};
