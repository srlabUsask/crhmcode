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
#ifndef TSTEP_RECH
#define TSTEP_RECH

class TSTEP_REC { // time step information
public:

#define	DATA_TSTEP	   0
#define	NORMAL_TSTEP	   1
#define	MEDIUM_TSTEP	   2
#define	SMALL_TSTEP	   3

    // default for normal run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_NORMAL_THRESHOLD  60.0

// default for medium run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_MEDIUM_THRESHOLD  10.0

// default for small run timestep's threshold for a layer's mass (kg/m^2)

#define	DEFAULT_SMALL_THRESHOLD  1.0


    int level;	    // timestep's level

    long time_step;   // length of timestep (seconds)

    int intervals;    // # of these timestep that are in the previous-level's timestep (not used for level 0: data tstep)

    float threshold;  // mass threshold for a layer to use this timestep (not used for level 0: data tstep)

    TSTEP_REC() : level(0), time_step(24 * 3600 / Global::Freq), intervals(1), threshold(0.0) {};

};

#endif
