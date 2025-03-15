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
//---------------------------------------------------------------------------

#ifndef SnobalDefinesH
#define SnobalDefinesH
//---------------------------------------------------------------------------
/*
*  molecular weight of air (kg / kmole)
*/
#define MOL_AIR         28.9644

/*
*  molecular weight of water vapor (kg / kmole)
*/
#define MOL_H2O         18.0153

/*
*  gas constant (J / kmole / deg)
*/
#define RGAS            8.31432e3

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
#define DIFFUS(pa,ts)   ( (0.65*(SEA_LEVEL/(pa)) * \
                        pow(((ts)/FREEZE),14.0)) * (0.01*0.01) )
/*
*  latent heat of vaporization
*
*	t = temperature (K)
*/
#define LH_VAP(t)               (2.5e6 - 2.95573e3 *((t) - FREEZE))

/*
*  latent heat of fusion
*
*	t = temperature (K)
*/
#define LH_FUS(t)               (3.336e5 + 1.6667e2 * (FREEZE - (t)))

/*
*  specific heat of water at 0C (J / (kg K))
*/
#define CP_W0   	4217.7

/*
*  specific heat of water (J/(kg K))
*    (from CRC table D-158; most accurate from 0 to +10 C)
*    (incorrect at temperatures above 25 C)
*
*	t = temperature (K)
*/
#define CP_WATER(t)     ( CP_W0 - 2.55*((t)-FREEZE) )

/*
*  specific heat of ice (J/(kg K))
*    (from CRC table D-159; most accurate from 0 to -10 C)
*
*	t = temperature (K)
*/
#define CP_ICE(t)       ( CAL_TO_J(0.024928 + (0.00176*(t))) / G_TO_KG(1) )

/*
*  standard sea level pressure (Pa)
*/
#define SEA_LEVEL       1.013246e5

/*  thermal conductivity of wet sand (J/(m sec K))
*    (from Oke, 1978, pg. 38)
*/
#define KT_WETSAND      2.2
#define KT_MOISTSAND    1.65

/*
*  density of water at 0C (kg/m^3)
*    (from CRC handbook pg F-11)
*/
#define RHO_W0  	999.87

/*  density of ice - no air (kg/m^3)
*    (from CRC handbook pg F-1)
*/
#define RHO_ICE 	917.0

/*
*  triple point of water at standard pressure (deg K)
*/
#define FREEZE          2.7316e2
#define BOIL            3.7315e2

/*
*  Stefan-Boltzmann constant (W / m^2 / deg^4)
*/
#define STEF_BOLTZ      5.67032e-8

/*
*  Convert calories to Joules
*/
#define CAL_TO_J(c)		((c) * 4.186798188)

/*
*  Convert grams to kilograms.
*/
#define G_TO_KG(g)		((g) * 0.001)

/*
*  thermal emissivity of snow
*/
#define SNOW_EMISSIVITY		0.99 // changed from 0.98 03/27/15 as in JULES
#define CAN_EMISSIVITY      0.98 // as in JULES

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
#define KTS(rho)        CAL_TO_J(0.0077*((rho)/1000.0)*((rho)/1000.0))

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
#define CP_AIR          1.005e3

/*
*  gravitational acceleration at reference latitude 45d 32m 33s (m/s^2)
*/
#define GRAVITY		9.80665

/*
*  Von Karman constant
*/
#define VON_KARMAN      3.5e-1

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

inline double satw(double tk) {   // air temperature (K)
    double x;
    double l10;

    if (tk <= 0.) {
        CRHMException TExcept("satw temperature <= 0.0", TExcept::TERMINATE);
        LogError(TExcept);
    }

    errno = 0;
    l10 = log(1.e1);

    x = -7.90298 * (BOIL / tk - 1.0) + 5.02808 * log(BOIL / tk) / l10 -
        1.3816e-7 * (pow(1.0e1, 1.1344e1 * (1.0 - tk / BOIL)) - 1.0) +
        8.1328e-3 * (pow(1.0e1, -3.49149 * (BOIL / tk - 1.0)) - 1.0) +
        log(SEA_LEVEL) / l10;

    x = pow(1.0e1, x);

    if (errno) {
        CRHMException TExcept("satw: bad return from log or pow", TExcept::TERMINATE);
        LogError(TExcept);
    }

    return x;
}

// psi-functions
//	code =	SM	momentum
//		SH	sensible heat flux
//		SV	latent heat flux

inline double
psi(double zeta,		// z/lo
    int	code)		// which psi function? (see above)
{
    double	x;		// height function variable
    double	result{};

    if (zeta > 0) // stable
    {
        if (zeta > 1)
        {
            zeta = 1;
        }
        result = -BETA_S * zeta;
    }
    else if (zeta < 0) // unstable
    {
        x = sqrt(sqrt(1.0 - BETA_U * zeta));

        switch (code)
        {
            case SM:
                result = 2.0 * log((1.0 + x) / 2.0) + log((1.0 + x * x) / 2.0) -
                    2.0 * atan(x) + M_PI_2;
                break;

            case SH:
            case SV:
                result = 2.0 * log((1.0 + x * x) / 2.0);
                break;

            default: // shouldn't reach
                CRHMException TExcept("psi-function code not of these: SM, SH, SV", TExcept::TERMINATE);
                LogError(TExcept);
        }
    }
    else //Zeta == 1, neutral
    {
        result = 0.0;
    }

    return (result);
}



inline double sati(double  tk) { //* air temperature (K)

    double  l10;
    double  x;

    if (tk <= 0.0) {
        CRHMException TExcept("sati temperature <= 0.0", TExcept::TERMINATE);
        LogError(TExcept);
        //            tk = FREEZE + 0.01;
    }

    if (tk > FREEZE) {
        x = satw(tk);
        return(x);
    }

    errno = 0;
    l10 = log(1.e1);

    x = pow(1.e1, -9.09718 * ((FREEZE / tk) - 1.0) - 3.56654 * log(FREEZE / tk) / l10 +
        8.76793e-1 * (1.0 - (tk / FREEZE)) + log(6.1071) / l10);

    if (errno) {
        CRHMException TExcept("sati: bad return from log or pow", TExcept::TERMINATE);
        LogError(TExcept);
    }

    return(x * 1.e2);
}
/* ----------------------------------------------------------------------- */

inline double ssxfr(
    double	k1,	/* layer 1's thermal conductivity (J / (m K sec))  */
    double	k2,	/* layer 2's    "         "                        */
    double	t1,	/* layer 1's average layer temperature (K)	   */
    double	t2,	/* layer 2's    "      "        "         	   */
    double	d1,     /* layer 1's thickness (m)			   */
    double	d2)     /* layer 2's    "       "			   */
{
    double	xfr;

    xfr = 2.0 * (k1 * k2 * (t2 - t1)) / ((k2 * d1) + (k1 * d2));

    return (xfr);
}
/* ----------------------------------------------------------------------- */

inline double heat_stor(
    double	cp,	/* specific heat of layer (J/kg K) */
    double	spm,	/* layer specific mass (kg/m^2)    */
    double	tdif)	/* temperature change (K)          */
{
    double	stor;

    stor = cp * spm * tdif;

    return (stor);
}

/* ----------------------------------------------------------------------- */

inline double lambda(double t) // Latent heat of vaporization (mJ/(kg DEGREE_CELSIUS))
{
   return( 2.501 - 0.002361 * t );
}

inline double delta(double t) // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
{
  if (t > 0.0)
    return (2504.0 * exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
  else
    return (3549.0 * exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

inline double gamma(double Pa, double t) // Psychrometric constant (kPa/DEGREE_CELSIUS)
{
  return (0.00163 * Pa / lambda(t)); // lambda (mJ/(kg DEGREE_CELSIUS))
}

inline double adst_wind_cpy_top(
    double veg_ht, /* Height of vegetation (m) */
    double uz,     /* Wind speed at height z (m/s) */
    double z, /* Height of wind speed measurement (m) */

    // output
    double& u_veg_ht /* Wind speed at canopy top (m/s)*/
    )  
{
    if(z >= veg_ht){
        u_veg_ht = uz;
    } else if (veg_ht - 2.0 / 3.0 * z > 0.0) {
        u_veg_ht = uz * log((veg_ht - 2.0 / 3.0 * z) / 0.123 * z) / log((z - 2.0 / 3.0 * z) / 0.123 * z);
    } else {
        u_veg_ht = 0.0;
    }
    return(u_veg_ht);
}

inline double cionco_canopy_wind_spd(
    double veg_ht,    /* Height of vegetation (m) */
    double u_veg_ht,  /* Wind speed at height veg ht (m/s) */
    double target_ht, /* target height of output wind speed (m) */

    // output
    double &u_target_ht /* Wind speed at target height (m/s)*/
) 
{
    double A = 2.4338 + 3.45753 * exp(-u_veg_ht);                 /* Modified Cionco wind model */
    u_target_ht = u_veg_ht * exp(A * (target_ht / veg_ht - 1.0)); /* calculates canopy windspd  */

    return (u_target_ht);
}

