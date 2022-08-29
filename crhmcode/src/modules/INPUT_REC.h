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
#ifndef INPUT_RECH
#define INPUT_RECH

class  INPUT_REC { // climate-data input records
public:

    double S_n;	// net solar radiation (W/m^2)
    double I_lw;	// incoming longwave (thermal) rad (W/m^2)
    double T_a;	// air temp (C)
    double e_a;	// vapor pressure (Pa)
    double u;	// wind speed (m/sec)
    double T_g;	// soil temp at depth z_g (C)
    double F_g;	// soil flux at depth z_g (W/m^2)
};

#endif