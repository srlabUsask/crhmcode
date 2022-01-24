#pragma once

#ifndef CHAD_CONSTANTS
#define CHAD_CONSTANTS

namespace CHAD_constants {
	// Constants:
	const double emm = 0.985; 		// emissivity [ ]
	const double sbc = 5.67e-8; 		//Stephan-Boltzmann constant [W m-2 K-4]
	const double solarconst = 1367; 	// solar constant [W m-2]
	const double ca = 1013;  		//specific heat of air [J kg-1 K-1]
	const double cf = 2470;  		//specific heat of forest biomass [J kg-1 K-1]
	const double pa = 1.22;  		//typical air density [kg m-3]
	const double pf = 686;   		//typical forest biomass density [kg m-3]
	const double kf = 0.17;		//typical thermal conductivity of wood biomass [J m-1 K-1]
	const double dv = 1.983e-5;  		//dynamic viscosity of air (typical value for 300K) [kg m-1 s-1]
	const double kv = 1.88e-5;  		//kinematic viscosity of air (typical value for Sask.) [m2 s-1]
	const double dh = 2.216e-5; 		//thermal diffusivity of air (1 atm; 300 K) [m2 s-1]
	const double tca = 0.024;              //typical thermal conductivity of air (at 25�C) [J m-1 K-1]
	const double DTOR = 3.1416 / 180.0;
}

#endif // !CHAD_CONSTANTS
