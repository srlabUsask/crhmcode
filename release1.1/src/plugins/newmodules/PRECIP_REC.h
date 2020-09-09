class  PRECIP_REC { // precip-data input records
public:

    float	  m_pp;		// total precipitation mass (kg/m^2)
    float	  m_rain;	// mass of rain in precip   (kg/m^2)
    float	  m_snow;	// mass of snow in precip   (kg/m^2)
    float	  m_drift;	// mass of snow drift       (kg/m^2)
    float	  m_subl;	// mass of snow drift       (kg/m^2)
    float	  z_snow;	// depth of snow in precip  (m)
};