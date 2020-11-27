#ifndef INPUT_RECH
#define INPUT_RECH

class  INPUT_REC { // climate-data input records
public:

    double S_n;	// net solar radiation (W/m^2)
    double I_lw;	// incoming longwave (thermal) rad (W/m^2)
    double T_a;	// air temp (C)
    double e_a;	// vapor pressure (Pa)
    double u;	// wind speed (m/sec)
    double T_g;	// soil temp at depth z_g (C)
    double F_g;	// soil flux at depth z_g (W/m^2)
};

#endif