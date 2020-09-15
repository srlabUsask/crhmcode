//created by Manishankar Mondal

#include "ClassModule.h"

class ClassShutWall : public ClassModule {
public:

ClassShutWall(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;
double z0;
double d;
double n;


// declared variables
double *hru_actet;
double *hru_cum_actet;
double *evap;
double *evapD;
double *cum_evap;
double *Cc;
double *Cs;
double *Ra;
double *Rc;
double *Rs;
double *ETc;
double *ETs;
double *raa;
double *rca;
double *rcs;
double *rsa;
double *rss;

// declared parameters
const double *basin_area;   // [BASIN]
const double *hru_area;
const double *rs;
const double *hru_elev;
const double *Cr;
const double *LAI;
const double *Ht;
const double *Zwind;
const double *w;
const double *rst;
const double *z0g;
const double *gammab;

const long *inhibit_evap;

// declared observations
const double *hru_u;
const double *hru_t;
const double *hru_ea;
const double *Qn;
const double *Qg;

// variable inputs

// local allocated arrays
double *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWall* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
};