#ifndef INPUT_RECH
#define INPUT_RECH

class  INPUT_REC { // climate-data input records
public:

    float S_n;	// net solar radiation (W/m^2)
    float I_lw;	// incoming longwave (thermal) rad (W/m^2)
    float T_a;	// air temp (C)
    float e_a;	// vapor pressure (Pa)
    float u;	// wind speed (m/sec)
    float T_g;	// soil temp at depth z_g (C)
    float F_g;	// soil flux at depth z_g (W/m^2)
};

#endif