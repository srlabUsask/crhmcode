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
#pragma once

#ifndef CRHM_CONSTANTS
#define CRHM_CONSTANTS

namespace CRHM_constants {

	const double Cs = 1.28E+06; // (J/m3/K) volumetric heat capacity of soil
	const double Cp = 1005;     // (J/kg/K) volumetric heat capacity of dry air
	const double Rgas = 287.0;  // Gas constant for dry air (J/kg/K)
	const double Tm = 273.15;   // Melting point (K)
	const double Tf = 273.16; // Freezing point of water (K) as in CLASS and SNOBAL

	const double Ls = 2.845e6;  // Latent heat of sublimation (J/kg)
	const double Lv = 2.50e6;  // Latent heat of vaporization (J/kg)
	const double Lf = 0.334e6;  // Latent heat of fusion (J/kg)
	const double kappa = 0.4;

	const double sbc = 5.67E-8; // Stephan-Boltzmann constant W/m^2/k4
	const double SB = 4.899e-09; // Stephan-Boltzmann constant MJ/m^2-d

	const double emiss = 0.99; // emissivity the snowpack changed from 0.985 on 2025-02-06
	const double emiss_c = 0.96; // emissivity of the canopy
	const double em = 0.622;     //
    const double ci = 2.102e3; // specific heat capacity of ice (J/kg/K)
	const double cw = 4.186e3; // specific heat capacity of h2o (J/kg/K) from CLASS
	const double cv = 2.70e3; // specific heat capacity of vegetation (J/kg/K) from CLASS


}

#endif // !CRHM_CONSTANTS
