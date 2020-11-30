#pragma once

#ifndef CRHM_CONSTANTS
#define CRHM_CONSTANTS

namespace CRHM_constants {

	const double Cs = 1.28E+06; // (J/m3/K) volumetric heat capacity of soil
	const double Cp = 1005;     // (J/kg/K) volumetric heat capacity of dry air
	const double Rgas = 287.0;  // Gas constant for dry air (J/kg/K)
	const double Tm = 273.15;   // Melting point (K)

	const double Ls = 2.845e6;  // Latent heat of sublimation (J/kg)
	const double Lv = 2.50e6;  // Latent heat of vaporization (J/kg)
	const double Lf = 0.334e6;  // Latent heat of fusion (J/kg)
	const double kappa = 0.4;

	const double sbc = 5.67E-8; // Stephan-Boltzmann constant W/m^2/k4
	const double SB = 4.899e-09; // Stephan-Boltzmann constant MJ/m^2-d

	const double emiss = 0.985; // emissivity of the atmosphere and snowpack
	const double emiss_c = 0.96; // emissivity of the canopy
	const double em = 0.622;     //
}

#endif // !CRHM_CONSTANTS
