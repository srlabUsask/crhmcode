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