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
#ifndef PRECIP_RECH
#define PRECIP_RECH

class  PRECIP_REC { // precip-data input records
public:

    double	  m_pp;		// total precipitation mass (kg/m^2)
    double	  m_rain;	// mass of rain in precip   (kg/m^2)
    double	  m_snow;	// mass of snow in precip   (kg/m^2)
    double	  m_drift;	// mass of snow drift       (kg/m^2)
    double	  m_subl;	// mass of snow drift       (kg/m^2)
    double	  z_snow;	// depth of snow in precip  (m)
};

#endif