#pragma once
//---------------------------------------------------------------------------

#ifndef SnobalDefinesH
#define SnobalDefinesH
//---------------------------------------------------------------------------
/*
*  molecular weight of air (kg / kmole)
*/
#define MOL_AIR         28.9644f

/*
*  molecular weight of water vapor (kg / kmole)
*/
#define MOL_H2O         18.0153f

/*
*  gas constant (J / kmole / deg)
*/
#define RGAS            8.31432e3f

/*
*  specific humidity
*
*	e = vapor pressure
*	P = pressure (same units as e)
*/
#define SPEC_HUM(e,P)     ((e)*MOL_H2O/(MOL_AIR*(P)+(e)*(MOL_H2O-MOL_AIR)))

/*
*  water vapor flux (kg/(m^2 sec)) between two layers
*
*	air_d = air density (kg/m^3)
*	k     = diffusion coef. (m^2/sec)
*	q_dif = specific hum. diff between layers (kg/kg)
*	z_dif = absolute distance between layers (m)
*
*	note:   q_dif controls the sign of the computed flux
*/
#define EVAP(air_d,k,q_dif,z_dif)       ( air_d * k * (q_dif/z_dif) )

/*
*  effectuve diffusion coefficient (m^2/sec) for saturated porous layer
*  (like snow...).  See Anderson, 1976, pg. 32, eq. 3.13.
*
*	pa = air pressure (Pa)
*	ts = layer temperature (K)
*/
#define DIFFUS(pa,ts)   ( (0.65f*(SEA_LEVEL/(pa)) * \
                        pow(((ts)/FREEZE),14.0f)) * (0.01f*0.01f) )
/*
*  latent heat of vaporization
*
*	t = temperature (K)
*/
#define LH_VAP(t)               (2.5e6f - 2.95573e3f *((t) - FREEZE))

/*
*  latent heat of fusion
*
*	t = temperature (K)
*/
#define LH_FUS(t)               (3.336e5f + 1.6667e2f * (FREEZE - (t)))

/*
*  specific heat of water at 0C (J / (kg K))
*/
#define CP_W0   	4217.7f

/*
*  specific heat of water (J/(kg K))
*    (from CRC table D-158; most accurate from 0 to +10 C)
*    (incorrect at temperatures above 25 C)
*
*	t = temperature (K)
*/
#define CP_WATER(t)     ( CP_W0 - 2.55f*((t)-FREEZE) )

/*
*  specific heat of ice (J/(kg K))
*    (from CRC table D-159; most accurate from 0 to -10 C)
*
*	t = temperature (K)
*/
#define CP_ICE(t)       ( CAL_TO_J(0.024928f + (0.00176f*(t))) / G_TO_KG(1) )

/*
*  standard sea level pressure (Pa)
*/
#define SEA_LEVEL       1.013246e5f

/*  thermal conductivity of wet sand (J/(m sec K))
*    (from Oke, 1978, pg. 38)
*/
#define KT_WETSAND      2.2f
#define KT_MOISTSAND    1.65f

/*
*  density of water at 0C (kg/m^3)
*    (from CRC handbook pg F-11)
*/
#define RHO_W0  	999.87f

/*  density of ice - no air (kg/m^3)
*    (from CRC handbook pg F-1)
*/
#define RHO_ICE 	917.0f

/*
*  triple point of water at standard pressure (deg K)
*/
#define FREEZE          2.7316e2f
#define BOIL            3.7315e2f

/*
*  Stefan-Boltzmann constant (W / m^2 / deg^4)
*/
#define STEF_BOLTZ      5.67032e-8f

/*
*  Convert calories to Joules
*/
#define CAL_TO_J(c)		((c) * 4.186798188f)

/*
*  Convert grams to kilograms.
*/
#define G_TO_KG(g)		((g) * 0.001f)

/*
*  thermal emissivity of snow
*/
#define SNOW_EMISSIVITY		0.99f // changed from 0.98 03/27/15

/*
*  Macros
*/

/*
*  equation of state, to give density of a gas (kg/m^3)
*
*	p = pressure (Pa)
*	m = molecular weight (kg/kmole)
*	t = temperature (K)
*
*  or, inversely, to give pressure (Pa)
*
*      rho = density (kg/m^3)
*	m   = molecular weight (kg/kmole)
*	t   = temperature (K)
*/
#define GAS_DEN(p,m,t)          ((p)*(m)/(RGAS*(t)))
#define EQ_STATE(rho,m,t)       ((rho)*(RGAS)*(t)/(m))

/*
*  thermal conductivity of snow (J/(m sec K))
*    (after Yen, 1965, see Anderson, 1976, pg. 31)
*
*	rho = snow density (kg/m^3)
*/
#define KTS(rho)        CAL_TO_J(0.0077f*((rho)/1000.0f)*((rho)/1000.0f))

/*
*  melt (kg/m^2)
*
*	Q = available energy (J/m^2)
*/
#define MELT(Q)         ( (Q) / LH_FUS(FREEZE) )

/*
*  snow - liquid water mass fraction.
*    from:   Davis, et. al. (1985)
*
*	mw = mass of liquid water (kg)
*	ms = total mass of snow (kg)
*/
#define SNOH2O_MF(mw,ms)        ( mw / ms )

/*
* snow porosity
*    from:   Davis, et. al. (1985)
*
*	mw   = mass of liquid water (kg)
*	ms   = total mass of snow (kg)
*	rhos = density of snow (kg/m^3)
*/
#define SNO_PORO(mw,ms,rhos)    \
        ( (RHO_ICE - (rhos * (1.0 - SNOH2O_MF(mw,ms)))) / RHO_ICE )

/*
*  snow water saturation
*    from:   Davis, et. al. (1985)
*
*	mw   = mass of liquid water (kg)
*	ms   = total mass of snow (kg)
*	rhos = density of snow (kg/m^3)
*/
#define SNO_SAT(mw,ms,rhos)     \
	( (RHO_ICE * rhos * SNOH2O_MF(mw,ms)) / ((RHO_ICE - rhos) * RHO_W0) )

/*
*  water retained by snow at given saturation (see SNO_SAT)
*
*	d    = total depth of snow (m)
*	rhos = density of snow (kg/m^3)
*	sat  = snow saturation (see SNO_SAT)
*/
#define H2O_LEFT(d,rhos,sat)    \
        ( (sat * d * RHO_W0 * (RHO_ICE - rhos)) / RHO_ICE )

/*
*  'dry' snow density (without H2O) at a given total snow density
*  (with H2O) and snow saturation
*
*	rhos = total density of snow (kg/m^3)
*	sat  = snow saturation (see SNO_SAT)
*/
#define DRY_SNO_RHO(rhos,sat)    \
	( ((rhos) - (sat) * RHO_W0) / (1 - (sat) * RHO_W0 / RHO_ICE) )

/*
*  Minimum valid snow temperature (C).  This is also what temperatures
*  are set to when there's no snow (instead of 0 K).  This yields a
*  smaller quantization range in the output image: -75 C to 0 C
*  (instead of -273.16 C to 0 C).
*/

/*
*  latent heat of sublimination (J/kg)
*    from the sum of latent heats of vaporization and fusion,
*
*	t = temperature (K)
*/
#define LH_SUB(t)       	( LH_VAP(t) + LH_FUS(t) )

/*
*  mixing ratio
*
*	e = vapor pressure
*	P = pressure (same units as e)
*/
#define MIX_RATIO(e,P)          ((MOL_H2O/MOL_AIR)*(e)/((P)-(e)))

/*
*  specific heat of air at constant pressure (J / kg / deg)
*/
#define CP_AIR          1.005e3f

/*
*  gravitational acceleration at reference latitude 45d 32m 33s (m/s^2)
*/
#define GRAVITY		9.80665f

/*
*  Von Karman constant
*/
#define VON_KARMAN      3.5e-1f

/*
*  virtual temperature, i.e. the fictitious temperature that air must
*  have at the given pressure to have the same density as a water vapor
*  and air mixture at the same pressure with the given temperature and
*  vapor pressure.
*
*      t = temperature (K)
*      e = vapor pressure
*	P = pressure (e and P in same units),
*/
#define VIR_TEMP(t,e,P)		((t)/(1.-(1.-MOL_H2O/MOL_AIR)*((e)/(P))))

/*
*  dry adiabatic lapse rate (deg / m)
*/
#define DALR		( GRAVITY / CP_AIR )


#define MIN_SNOW_TEMP	-75

#endif
