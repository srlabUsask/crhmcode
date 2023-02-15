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

#ifndef PBSM_CONSTANT
#define PBSM_CONSTANT

namespace PBSM_constants {

	const double rho = 1.23;     // (kg/m3) density of dry air
	const double Qstar = 120;    //{Solar Radiation Input}
	const double M = 18.01;      //{molecular weight of water (kg/kmole)}
	const double R = 8313;       //{universal gas constant (J/(kmole K))}
	const double LATH = 2.838E6; //{latent heat of sublimation (J/kg) List 1949}
	const double DICE = 900;     //{density of ice, assumed equal to blowing snow part (kg/m3)}
	const double ZD = 0.3;       //{height of boundary-layer at xd (m) Takeuchi (1980)}
	const double XD = 300;       //{Fetch to develop b-l to ZD (m)}
	const double g = 9.80;       //{m/s2}
	const double Beta = 170;     // Beta ratio of element to surface drag for vegetation Cr/Cs
	const double C1 = 2.8;       //{2.3}
	const double C2 = 1.6;
	const double C3 = 4.2;       //{3.25} {e = 1/(C3*Ustar)}
	const double KARMAN = 0.4;
	const double KARMAN2 = 0.16;
}

#endif // !PBSM_CONSTANT
