//created by Manishankar Mondal

#include "ClassModule.h"

class ClassShutWallD : public ClassModule {
public:

ClassShutWallD(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt;
long Qg_Cnt;

// declared variables
double *hru_actet;
double *hru_cum_actet;
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
const double *hru_umean;
const double *hru_tmean;
const double *hru_eamean;
const double *Qn;
const double *Qg;

// declared observation functions
double *Qnmean;
double *Qgmean;

// variable inputs

// local allocated arrays
double *Pa;

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWallD* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/°C
};