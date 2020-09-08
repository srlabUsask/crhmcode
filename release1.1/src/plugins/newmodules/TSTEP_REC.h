//created by Manishankar Mondal

#include "ClassModule.h"

class TSTEP_REC{ // time step information
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

  TSTEP_REC() : level(0), time_step(24*3600/Global::Freq), intervals(1), threshold(0.0) {};

};