#pragma once
// 01/23/18
//---------------------------------------------------------------------------
//#include <vcl.h>
#pragma hdrstop
#include "stdafx.h"
#include "Hype_river.h"
#include "Hype_routines.h"
//#include "Hype_routines.cpp"
#include "GlobalDll.h"
#include <math.h>

//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma init_seg

//---------------------------------------------------------------------------
using namespace std;
using namespace CRHM;

ClassWQ_River* ClassWQ_River::klone(string name) const {
	return new ClassWQ_River(name);
}

void ClassWQ_River::decl(void) {

	Description = "'WQ River module.'";


	declvar("TPmean_r", NHRU, "365-day mean Total Phosphorus concentration of lake (laketype,subbasin)", "(mg/m)", &TPmean_r);

	declvar("temp_r", NHRU, "lake temperature (laketype,subbasin)", "(°C)", &temp_r);

	declvar("temp10_r", NHRU, "10-day mean lake temperature (laketype,subbasin)", "(°C)", &temp10_r);

	declvar("temp20_r", NHRU, "20-day mean lake temperature (laketype,subbasin)", "(°C)", &temp20_r);

	declvar("Psed", NHRU, "phosphorus sediment in river (rivertype, subbasin)", "(kg)", &Psed);


	declparam("catchment_area", NHRU, "[1]", "1e-6", "1e+09", "catchment_area", "(km^2)", &catchment_area);

	declparam("depth_river", NHRU, "[5]", "1", "50", "river depth", "(m)", &depth);

	declparam("transq", NHRU, "[50]", "1", "1000", "flow out of translation box chain", "(m^3/s)", &transq);

	declparam("qbank", NHRU, "[100]", "1", "1000", "bank full river flow", "(m^3/s)", &qbank);

	declparam("riverq", NHRU, "[100]", "1", "1000", "river discharge", "(m^3/s)", &riverq);

	declparam("denpar", NHRU, "[1]", "0", "100", "denitrification rate", "(kg/m^2)", &denpar);

	declparam("denparl", NHRU, "[1]", "0", "100", "denitrification rate, local river", "(kg/m^2)", &denparl);

	declparam("limpppar", NHRU, "[100]", "0", "1000", "limitation of sedimentation parameter", "(mg/l)", &limpppar);

	declparam("prodNpar", NHRU, "[0]", "0", "1", "flag for prodNpar model parameter production ON", "()", &prodNpar);

	declparam("prodPpar", NHRU, "[100]", "0", "1000", "production PP", "()", &prodPpar);

	declparam("sedexppar", NHRU, "[0.1]", "0.1", "100", "sedimentation/resuspension parameter", "(mg/l)", &sedexppar);

	declparam("prodpar", NHRU, "[0.1]", "0.1", "100", "production rate OC in water", "(mg/l)", &prodpar);

	declparam("limppar", NHRU, "[0.1]", "0.1", "100", "limitation of sedimentation parameter", "(mg/l)", &limppar);

	declparam("watertemp", NHRU, "[25]", "0", "100", "water TP mean", "(°C)", &watertemp);

	declparam("waterTPmean", NHRU, "[25]", "0", "100", "water temperature", "(°C)", &waterTPmean);

	declparam("i_in", NHRU, "[0]", "0", "5", " inorganic nitrogen", "(mm)", &i_in);

	declparam("i_on", NHRU, "[0]", "0", "5", " organic nitrogen", "(mm)", &i_on);

	declparam("i_sp", NHRU, "[0]", "0", "5", " soluble (reactive) phosphorus, i.e. phosphate", "(mm)", &i_sp);

	declparam("i_pp", NHRU, "[0]", "0", "5", " particulate phosphorus", "(mm)", &i_pp);

	declparam("i_oc", NHRU, "[0]", "0", "5", " (dissolved) organic carbon", "(mm)", &i_oc);

	declparam("conductP", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductP);

	declparam("conductN", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductN);

	declparam("rivertype", NHRU, "[1]", "1", "2", "river type (local -1 or main - 2)", "()", &rivertype);

	declparam("Psed_init", NHRU, "[100]", "1", "1000", "phosphorus sediment in river (rivertype, subbasin)", "(kg)", &Psed_init);


	declvar("water_r", NDEFN, "soil moisture", "(mm)", &water_r, &water_r_lay, numsubstances);

	declputvar("*", "conc", "(mg/l)", &conc, &conc_lay);

	declgetvar("*", "hru_t", "(°C)", &hru_t);

	declgetvar("*", "SRP_conc", "(mg/l)", &SRP_conc, &SRP_conc_lay);

	declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);
}

void ClassWQ_River::init(void) {

	for (hh = 0; chkStruct(); ++hh)
		Psed[hh] = Psed_init[hh];
}

void ClassWQ_River::run(void) {

	if (nstep == 1 || Global::Freq == 1) { // begining of day

		for (hh = 0; chkStruct(); ++hh) {
			sedimentation_resuspension(rivertype[hh], catchment_area[hh], sedexppar[hh], riverq[hh], qbank[hh], depth[hh]);

			np_processes_in_river(rivertype[hh], catchment_area[hh], depth[hh], transq[hh], qbank[hh], denpar[hh],
				denparl[hh], prodNpar[hh], prodPpar[hh], sedexppar[hh], limpppar[hh]);

			oc_processes_in_river(rivertype[hh], catchment_area[hh], depth[hh], prodpar[hh], limpppar[hh]);
		}
	} // begining of day
}

void ClassWQ_River::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessage(hh, string("'" + Name + " (WQ_Hype)'").c_str(), BLANK);
	}
	LogDebug(" ");
}

// Calculate nutrient processes in river
// This include denitrification, mineralisation, primary production,
// sedimentation, resuspension, exchange with sediment
// ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Common things in lakes and river,
// Denitrification, Primary production and mineralization, and Sedimentation/Resuspension)
//   ---------------------------------------------------------------------------
void ClassWQ_River::np_processes_in_river(const long rivertype, const float area, const float depth, const float transq, const float Qbank, const float denpar,
	const float denparl, const float prodNpar, const float prodPpar, const float sedexppar, const float limpppar) {
	/*
	USE MODVAR, ONLY : i_in,i_sp,conductP

	Argument declarations
	long, INTENT(IN) :: i         !<index of current subbasin
	long, INTENT(IN) :: itype     !<river type (local or main)
	float, INTENT(IN)    :: area      !<river area (m2)
	float, INTENT(IN)    :: depth     !<river depth (m)
	float, INTENT(IN)    :: transq    !<flow out of translation box chain (m3/s)
	float, INTENT(IN)    :: qbank     !<bank full river flow
	float, INTENT(IN)    :: denpar    !<model parameter denitrification rate (kg/m2/day)
	float, INTENT(IN)    :: denparl   !<model parameter denitrification rate, local river (kg/m2/day)
	float, INTENT(IN)    :: prodNpar  !<model parameter production ON
	float, INTENT(IN)    :: prodPpar  !<model parameter production PP
	float, INTENT(IN)    :: sedexppar !<sedimentation/resuspension parameter (mg/L)
	float, INTENT(IN)    :: limpppar  !<limitation of sedimentation parameter (mg/L)
	TYPE(riverstatetype),INTENT(INOUT) :: riverstate  !<River states
	*/

	// Calculate the nutrient processes
	if (area > 0.0) {
		if (i_sp[hh] > 0)
			calculate_river_tpmean(rivertype);
		if (i_in[hh] > 0) {
			if (rivertype == 1)
				denitrification_water(rivertype, area, denpar); // denitrification in local rivers
			else
				denitrification_water(rivertype, area, denpar);  // denitrification in rivers
		}

		production_mineralisation(rivertype, area, prodNpar, prodPpar, limpppar, depth); // mineraliation and primary production in rivers
		if (conductP[hh])
			sedimentation_resuspension(rivertype, area, sedexppar, transq, Qbank, depth); // sedimentation and resuspension of part P in rivers
	}
	// No sediment SRP exchange. The concentration smoothed with deadvolume
} //  np_processes_in_river


  // Calculates straight 365-day running average mean of TP
  // concentration in river
  // Reference ModelDescription Chapter  Nitrogen and phosphorus processes in rivers and lakes (Primary production
  //  and mineralization) and Organic carbon (River and Lakes - Primary production and mineralization)
  // -------------------------------------------------------------------
void ClassWQ_River::calculate_river_tpmean(const long rivertype) {
	/*
	USE MODVAR, ONLY : i_sp,i_pp

	!Argument declarations
	long, INTENT(IN) :: i         !<index of current subbasin
	long, INTENT(IN) :: watertype !<River type (1=local, 2=main)
	TYPE(riverstatetype),INTENT(INOUT) :: riverstate  !<River states
	*/
	TPmean_r[hh] = TPmean_r[hh] + (conc_lay[(int)i_sp[hh] - 1][hh]
		+ conc_lay[(int)i_pp[hh] - 1][hh] - TPmean_r[hh]) / 365.0;

} //  calculate_river_tpmean

  // Calculate sedimentation and resuspension of PP in rivers.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Sedimentation/Resuspension)
  // -----------------------------------------------------------------
void ClassWQ_River::sedimentation_resuspension(const long rivertype, const float area, const float sedexppar, const float riverq, const float qbank, const float depth) {
	/*
	USE MODVAR, ONLY : i_pp

	!Argument declaration
	long, INTENT(IN) :: i          !<index of current subbasin
	long, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
	float, INTENT(IN)    :: area       !<lake/river surface area (m2)
	float, INTENT(IN)    :: sedexppar  !<sedimentation/resuspension parameter
	float, INTENT(IN)    :: riverq     !<river discharge
	float, INTENT(IN)    :: qbank      !<Q bank full
	float, INTENT(IN)    :: depth      !<river depth (m)
	TYPE(riverstatetype),INTENT(INOUT) :: riverstate  !<River states
	*/
	// Local variables
	float PPpool[1];             // pools in water (kg)
	float sedPP[1], resuspPP[1]; // changes (kg/d)
	float tempsed[1];               // temparary variable for PP in river sediment (kg)
	float sedresp, help, qbankcorr;

	// Initial check
	if (sedexppar == 0 || i_pp[hh] == 0) return;
	if (catchment_area[hh] > 0.0) {
		tempsed[0] = Psed[hh];      // help variable, kg

									// Calculate nutrient pool of water
		PPpool[0] = water_r[hh] * conc_lay[(int)i_pp[hh] - 1][hh] * 1.0E-3; // kg (no ON sed/resusp in rivers)

																			// Calculate sedimentation and resuspension
		resuspPP[0] = 0.0;
		sedPP[0] = 0.0;
		if (qbank > 0.0) {
			qbankcorr = 0.7*qbank;
			help = 0.0;
			if (qbankcorr - riverq > 0.0)
				help = help + (qbankcorr - riverq) / pow(qbankcorr, sedexppar);  // sedimentation at low flow
			if (riverq > 0.0)
				help = help - pow(riverq / qbankcorr, sedexppar);  // rsuspension at all flows
			sedresp = max<float>(-1.0, min<float>(1.0, help));
			if (sedresp > 0.0) { // sedimentation (kg)
				sedPP[0] = sedresp * conc_lay[(int)i_pp[hh] - 1][hh] * min <float>(water_r[hh], catchment_area[hh] * depth) / 1.0E3;
				retention_pool(1, PPpool, sedPP);              // sedpp may change
				production_pool(1, tempsed, sedPP);
			}
			else {                 // resuspension (kg)
				resuspPP[0] = -sedresp * tempsed[0];
				retention_pool(1, tempsed, resuspPP);          // resusppp may change
				production_pool(1, PPpool, resuspPP);
			}
		}
	}
	// Update state variables
	Psed[hh] = tempsed[0];
	new_concentration(PPpool[0], water_r[hh] * 1.0E-3, &conc_lay[(int)i_pp[hh] - 1][hh]);

} //  sedimentation_resuspension

  // Lake processes in slow turnover lake part.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Denitrification)
  // -----------------------------------------------------------------------
void ClassWQ_River::denitrification_water(const long watertype, const float area, const float denpar) {
	/*
	USE MODVAR, ONLY : i_in
	USE HYPEVARIABLES, ONLY : halfsatINwater,   &
	maxdenitriwater

	!Argument declarations
	long, INTENT(IN) :: i          !<index of current subbasin
	long, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
	long, INTENT(IN) :: systemtype !<aquatic system type (1=lake, 2=river)
	float, INTENT(IN)    :: area       !<lake surface area/river bottom area (m2)
	float, INTENT(IN)    :: denpar     !<model parameter denitrification rate (kg/m2/day)
	TYPE(riverstatetype),INTENT(INOUT),OPTIONAL :: riverstate  !<River states
	TYPE(lakestatetype),INTENT(INOUT),OPTIONAL  :: lakestate   !<Lake states
	*/
	// Local variables
	float denitri_water[1], inorganicNpool[1];
	float tmpfcn, concfcn, watertemp, waterconc, vol;

	// Local parameters
	const long pooldim = 1;

	// Initial pools and values
	{                     // rivers
		vol = water_r[hh] * 1.0E-3;
		waterconc = conc_lay[(int)i_in[hh] - 1][hh]; // fix [nn]
		inorganicNpool[0] = vol * waterconc;     // kg
		watertemp = temp_r[hh];
	}

	// Temperature and concentration dependence factor
	tmpfcn = tempfactor(watertemp);
	concfcn = halfsatconcfactor(waterconc, halfsatINwater);

	// Denitrification
	denitri_water[0] = denpar * area * concfcn * tmpfcn;   // kg
	denitri_water[0] = min <float>(maxdenitriwater*inorganicNpool[0], denitri_water[0]);    // max 50% kan be denitrified
	retention_pool(pooldim, inorganicNpool, denitri_water);
	if (water_r[hh] > 0.0);
	new_concentration(inorganicNpool[0], vol, &conc_lay[(int)i_in[hh] - 1][hh]); // rivers  !!!FIX

} // denitrification_water

  // Calculates transformation between IN/ON and SRP/PP in water.
  // Simulating the combined processes of primary production and
  //   mineralisation. Lake processes in slow turnover lake part.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Primary production and mineralization)
  // -----------------------------------------------------------------------
void ClassWQ_River::production_mineralisation(const long watertype, const float area, const float prodNpar, const float prodPpar, const float limpppar,
	const float depth) {
	/*
	USE MODVAR, ONLY : conductN,conductP, &
	i_in,i_on,i_sp,i_pp
	USE HYPEVARIABLES, ONLY : maxprodwater,   &
	maxdegradwater, &
	NPratio,        &
	halfsatTPwater

	!Argument declarations
	long, INTENT(IN) :: i          !<index of current subbasin
	long, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
	long, INTENT(IN) :: systemtype !<aquatic system type (1=lake, 2=river)
	float, INTENT(IN)    :: area       !<lake surface area/ river bottom area (m2)
	float, INTENT(IN)    :: prodNpar   !<model parameter production rate ON in water
	float, INTENT(IN)    :: prodPpar   !<model parameter production rate PP in water
	float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
	TYPE(riverstatetype),INTENT(INOUT),OPTIONAL :: riverstate !<River states
	TYPE(lakestatetype),INTENT(INOUT),OPTIONAL  :: lakestate  !<Lake states
	float, INTENT(IN), OPTIONAL :: depth      !<river depth (m)
	*/
	// Local variables
	float ONpool[1], INpool[1], SRPpool[1], PPpool[1], minprodN[1], minprodP[1];
	float watertemp, waterTPmean, temp10, temp20;
	float tmpfcn, tmpfcn1, tmpfcn2, TPfcn;
	float vol;
	float waterdepth;     // m

						  // Local parameters
	long pooldim = 1;

	if (!conductN[hh] && !conductP[hh]) return;

	// Pools of nutrients in the water, water temperature and fraction of depth of water volume that is active
	// in rivers
	vol = water_r[hh] / 1.0E3;
	if (conductN[hh]) {
		INpool[0] = vol * conc_lay[(int)i_in[hh] - 1][hh]; // kg
		ONpool[0] = vol * conc_lay[(int)i_on[hh] - 1][hh]; // kg
	}
	if (conductP[hh]) {
		SRPpool[0] = vol * conc_lay[(int)i_sp[hh] - 1][hh];    // kg
		PPpool[0] = vol * conc_lay[(int)i_pp[hh] - 1][hh];    // kg
	}

	// Set help variable
	// in rivers
	watertemp = temp_r[hh];
	waterdepth = depth;
	waterTPmean = TPmean_r[hh];

	if (watertemp > 0.0) { // Total phosphorus concentration dependent factor
		TPfcn = halfsatconcfactor(max <float>(waterTPmean - limpppar, 0.0), halfsatTPwater);

		// Temperature dependent factor
		tmpfcn1 = watertemp / 20.0;
		tmpfcn2 = (temp10_r - temp20_r) / 5.0;
		tmpfcn = tmpfcn1 * tmpfcn2;

		// Production/mineralisation of organic nitrogen and particulate phosphorus
		if (conductN[hh]) {
			minprodN[0] = prodNpar * TPfcn * tmpfcn * waterdepth * area;  // kg
			if (minprodN[hh] > 0.0)   // production
				minprodN[0] = min <float>(maxprodwater * INpool[0], minprodN[0]);
			else                       // mineralisation
				minprodN[0] = max <float>(-maxdegradwater * ONpool[0], minprodN[0]);

			retention_pool(pooldim, INpool, minprodN);   // minprodN may be negative
			production_pool(pooldim, ONpool, minprodN);
		}
		if (conductP[hh]) {
			minprodP[0] = prodPpar * NPratio * TPfcn * tmpfcn * waterdepth * area;  // kg
			if (minprodP[0] > 0.0)   // production
				minprodP[0] = min <float>(maxprodwater * SRPpool[0], minprodP[0]);
			else                       // mineralisation
				minprodP[0] = max <float>(-maxdegradwater * PPpool[0], minprodP[0]);

			retention_pool(pooldim, SRPpool, minprodP);    // minprodP may be negative
			production_pool(pooldim, PPpool, minprodP);
		}

		// New concentration due to changes in pools
		// in rivers
		if (water_r[hh] > 0.0) {
			if (conductN[hh])  new_concentration(INpool[0], vol, &conc_lay[(int)i_in[hh] - 1][hh]);
			if (conductN[hh])  new_concentration(ONpool[0], vol, &conc_lay[(int)i_on[hh] - 1][hh]);
			if (conductP[hh])  new_concentration(SRPpool[0], vol, &conc_lay[(int)i_sp[hh] - 1][hh]);
			if (conductP[hh])  (PPpool[0], vol, conc_lay[(int)&i_pp[hh] - 1][hh]);
		}
	}

} // production_mineralisation

  // Calculate organic carbon processes in river; mineralisation,
  // primary production
  // Reference ModelDescription Chapter Organic carbon (River and Lakes - Primary production and mineralization)
  //----------------------------------------------------------------
void ClassWQ_River::oc_processes_in_river(const long watertype, const float area, const float depth, const float prodpar, const float limpppar) {
	/*
	USE MODVAR, ONLY : i_oc

	!Argument declarations
	INTEGER, INTENT(IN) :: i          !<index of current subbasin
	INTEGER, INTENT(IN) :: watertype  !<river type (local or main)
	REAL, INTENT(IN)    :: area       !<river area (m2)
	REAL, INTENT(IN)    :: depth      !<river depth (m)
	REAL, INTENT(IN)    :: prodpar    !<model parameter production OC
	REAL, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
	TYPE(riverstatetype),INTENT(INOUT) :: riverstate  !<River states
	*/
	// Local parameters
	const long systemtype = 2;    // river system

	if (i_oc[hh] == 0)
		return;

	// Calculate the organic carbon processes

	if (area > 0.0)
		oc_production_mineralisation(area, prodpar, limpppar, water_r[hh], conc_lay[(int)i_oc[hh] - 1][hh],
			temp_r[hh], TPmean_r[hh], temp10_r[hh], temp20_r[hh], depth);

} // ocesses_in_river

  // Calculates transformation between OC/DIC in water
  // Simulating the combined processes of primary production and mineralisation.
  // ModelDescription Organic carbon (River and lakes - Primary production
  //  and mineralization)
  // ----------------------------------------------------------------
void ClassWQ_River::oc_production_mineralisation(const float area, float prodpar, float limpppar, float water, float conc, float watertemp,
	float waterTPmean, float temp10, float temp20, float depth) {
	/*
	USE HYPEVARIABLES, ONLY : halfsatTPwater, &
	maxdegradwater, &
	NCratio

	!Argument declarations
	long, INTENT(IN)        :: systemtype  !<aquatic system type (1=lake, 2=river)
	float, INTENT(IN)           :: area        !<lake surface area/ river bottom area (m2)
	float, INTENT(IN)           :: prodpar     !<model parameter production rate OC in water
	float, INTENT(IN)           :: limpppar    !<limitation of sedimentation parameter (mg/L)
	float, INTENT(IN)           :: water       !<river or lake water (mm or m3)
	float, INTENT(INOUT)        :: conc        !<OC concentration of river or lake
	float, INTENT(IN)           :: watertemp   !<water temperature
	float, INTENT(IN)           :: waterTPmean !<water TP mean
	float, INTENT(IN)           :: temp10      !<10-day water temperature
	float, INTENT(IN)           :: temp20      !<20-day water temperature
	float, INTENT(IN), OPTIONAL :: depth       !<river depth (m)
	*/
	// Local variables
	float OCpool[1], minprodN[1], minprodC[1], minC[1], prodC[1];
	float tmpfcn, tmpfcn1, tmpfcn2, TPfcn;
	float vol;
	float waterdepth; // (m)

					  // Local parameter
	const long pooldim = 1;

	// Calculate pools of organic carbon in the water, water temperature
	// and fraction of depth of water volume that is active

	OCpool[0] = (water * conc) / 1.0E3; // kg  ***rivers
	waterdepth = depth;

	// Calculate dependency factors (Tot-P and temperature)

	TPfcn = halfsatconcfactor(waterTPmean - limpppar, halfsatTPwater);
	if (watertemp >= 0.0)
		tmpfcn1 = watertemp / 20.0;
	else
		tmpfcn1 = 0.0;

	tmpfcn2 = (temp10 - temp20) / 5.0;
	tmpfcn = tmpfcn1 * tmpfcn2;

	// Calculate production/mineralisation of organic carbon

	minprodN[0] = 0.0;
	if (watertemp > 0.0) {
		minprodN[0] = prodpar * TPfcn * tmpfcn * waterdepth * area;  // kg
		if (minprodN[0] > 0.0)  // production
			minprodC[0] = minprodN[0] * NCratio;
		else                       // mineralisation
			minprodC[0] = max <float>(-maxdegradwater * OCpool[0], minprodN[0] * NCratio);
	}

	minC[0] = -minprodC[0];
	prodC[0] = minprodC[0];
	if (minprodC[0] > 0.0)
		production_pool(pooldim, OCpool, prodC);
	if (minprodC[0] < 0.0)
		retention_pool(pooldim, OCpool, minC);

	// Set new concentration due to changes in pools

	if (water > 0.0) { // ***river
		vol = water / 1.0E3;
		new_concentration(OCpool[0], vol, &conc);
	}
} //  oc_production_mineralisation// Calculates the denitrification in river and lakes

ClassWQ_REWroute* ClassWQ_REWroute::klone(string name) const {
	return new ClassWQ_REWroute(name);
}

void ClassWQ_REWroute::decl(void) {

	Description = "'Handles the routing of surface and subsurface runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.'";

	variation_set = VARIATION_ORG;


	inflowCnt = declgrpvar("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", &rew, &inflow_All);

	declvar("WS_inflow", NHRU, "inflow from each RB", "(m^3/int)", &inflow);

	declstatdiag("cum_WSinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cuminflow);

	declvar("WS_outflow", NHRU, "outflow of each RB", "(m^3/int)", &outflow);

	declstatdiag("cum_WSoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumoutflow);

	declvar("WS_flow", BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", &flow);

	declvar("WS_flow_s", BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", &flow_s);

	declstatdiag("cum_WSflow", BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", &cumflow);


	gwCnt = declgrpvar("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", &gwrew, &gw_All);

	declvar("WS_gwinflow", NHRU, "inflow from each RB", "(m^3/int)", &gwinflow);

	declstatdiag("cum_WSgwinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cumgwinflow);

	declvar("WS_gwoutflow", NHRU, "outflow of each RB", "(m^3/int)", &gwoutflow);

	declstatdiag("cum_WSgwoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumgwoutflow);

	declvar("WS_gwflow", BASIN, "watershed ground water outflow", "(m^3/int)", &gwflow);

	declvar("WS_gwflow_s", BASIN, "watershed ground water outflow", "(m^3/s)", &gwflow_s);

	declstatdiag("cum_WSgwflow", BASIN, "cumulative watershed ground water outflow", "(m^3)", &cumgwflow);


	declparam("watershed_area", BASIN, "3", "1e-6", "1e09", "Total watershed area", "(km^2)", &watershed_area);

	declparam("RB_area", NHRU, "[1]", "1e-6", "1e09", "RB area", "(km^2)", &RB_area);

	declparam("WS_Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_Lag);

	declparam("WS_gwLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_gwLag);

	declparam("WS_whereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_whereto);

	declparam("WS_order", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_order);

	declparam("WS_gwwhereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_gwwhereto);

	declparam("WS_gworder", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_gworder);


	variation_set = VARIATION_0;

	decldiag("WS_Ktravel_var", NHRU, "inflow storage constant", "(d)", &WS_Ktravel_var);

	decldiag("WS_gwKtravel_var", NHRU, "gw storage constant", "(d)", &WS_gwKtravel_var);


	declparam("WS_route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &WS_route_n);

	declparam("WS_route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "()", &WS_route_R);

	declparam("WS_route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &WS_route_S0);

	declparam("WS_route_L", NHRU, "[3.69]", "0.01", "1.0E10", "routing length", "(m)", &WS_route_L);

	declparam("WS_Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &WS_Channel_shp);

	declparam("WS_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_route_X_M);

	declparam("WS_gwX_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_gwroute_X_M);


	variation_set = VARIATION_1;

	declparam("WS_Kstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_Kstorage);

	declparam("WS_gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_gwKstorage);


	variation_set = VARIATION_ORG;
}

void ClassWQ_REWroute::init(void) {

	if (nhru < inflowCnt) {
		CRHMException Except("Module REW route # of HRUs must be >= # of groups.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	float totarea = 0;
	for (hh = 0; hh < nhru; ++hh)
		totarea += RB_area[hh];

	if (fabs((totarea - watershed_area[0]) / watershed_area[0]) > 1e-3) {
		const_cast<float *>  (watershed_area)[0] = totarea;
		CRHMException TExcept(string(string("Sum of RB's area <> Watershed area, Watershed area made = ") + std::to_string(totarea)).c_str(), WARNING);
		LogError(TExcept);
	}

	if (WS_whereto[WS_order[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'whereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (WS_gwwhereto[WS_gworder[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'gwwhereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (variation == VARIATION_ORG) {
		const float Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

		for (hh = 0; hh < nhru; ++hh) {
			float Vavg = (1.0 / WS_route_n[hh])*pow(WS_route_R[hh], 2.0f / 3.0f)*pow(WS_route_S0[hh], 0.5f);

			WS_gwKtravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
			WS_Ktravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
		}

		inflowDelay = new ClassMuskingum(inflow, outflow, WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
		gwDelay = new ClassMuskingum(gwinflow, gwoutflow, WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);

		for (hh = 0; hh < nhru; ++hh) {
			if (WS_gwKtravel_var[hh] >= (Global::Interval / (2.0*WS_gwroute_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) GW Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (gwDelay->c0[hh] < 0.0) {
				gwDelay->c0[hh] = 0.0;
				gwDelay->c1[hh] = 1.0;
				gwDelay->c2[hh] = 0.0;
			}

			if (WS_Ktravel_var[hh] >= (Global::Interval / (2.0*WS_route_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) inflow Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (WS_Ktravel_var[hh] < (Global::Interval / (2.0*(1.0 - WS_route_X_M[hh])))) { //inflowDelay->c0[hh] < 0.0
				inflowDelay->c0[hh] = 0.0;
				inflowDelay->c1[hh] = 1.0;
				inflowDelay->c2[hh] = 0.0;
			}
		}
	}
	else if (variation == VARIATION_1) {
		Clark_inflowDelay = new ClassClark(inflow, outflow, WS_Kstorage, WS_Lag, nhru);
		Clark_gwDelay = new ClassClark(inflow, outflow, WS_gwKstorage, WS_gwLag, nhru);
	}

	flow[0] = 0.0;
	flow_s[0] = 0.0;
	cumflow[0] = 0.0;

	gwflow[0] = 0.0;
	gwflow_s[0] = 0.0;
	cumgwflow[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		gwinflow[hh] = 0.0;
		cumgwinflow[hh] = 0.0;
		gwoutflow[hh] = 0.0;
		cumgwoutflow[hh] = 0.0;
	}
}

void ClassWQ_REWroute::run(void) {

	flow[0] = 0.0;
	gwflow[0] = 0.0;

	for (long jj = 0; jj < inflowCnt; ++jj) { // HRUs not in sequence

		int hh = WS_order[jj] - 1;

		if (rew[hh])
			inflow[hh] = inflow_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			inflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {
				if (outflow[hhh] > 0.0)
					inflow[hh] += outflow[hhh];
			}
		}

		cuminflow[hh] += inflow[hh];

		if (variation == VARIATION_ORG)
			inflowDelay->DoMuskingum(hh); // need to update for later HRUs
		else
			Clark_inflowDelay->DoClark(hh); // need to update for later HRUs

		cumoutflow[hh] += outflow[hh];

		if (WS_whereto[hh] == 0) {
			flow[0] += outflow[hh]; // (already m^3)
			flow_s[0] = flow[0] * Global::Freq / 86400.0;
		}
	} //end for

	for (long jj = 0; jj < gwCnt; ++jj) { // HRUs not in sequence

		int hh = WS_gworder[jj] - 1;

		if (gwrew[hh])
			gwinflow[hh] = gw_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			gwinflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_gwwhereto[hhh] - 1 == hh && gwoutflow[hhh] > 0.0) {
				if (gwoutflow[hhh] > 0.0)
					gwinflow[hh] += gwoutflow[hhh];
			}
		}

		cumgwinflow[hh] += gwinflow[hh];

		if (variation == VARIATION_ORG)
			gwDelay->DoMuskingum(hh); // need to update for later HRUs
		else
			Clark_gwDelay->DoClark(hh); // need to update for later HRUs

		cumgwoutflow[hh] += gwoutflow[hh];

		if (WS_gwwhereto[hh] == 0) {
			gwflow[0] += gwoutflow[hh]; // (already m^3)
			gwflow_s[0] = gwflow[0] * Global::Freq / 86400.0;
		}
	} //end for

	cumflow[0] += flow[0];
	cumgwflow[0] += gwflow[0];
}

void ClassWQ_REWroute::finish(bool good) {
	for (hh = 0; hh < inflowCnt; ++hh) {
		LogMessageA(hh, string("'" + Name + " (REW_route)' cuminflow          (m^3) (m^3): ").c_str(), cuminflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route)' cumoutflow         (m^3) (m^3): ").c_str(), cumoutflow[hh], 1.0);
		if (variation == VARIATION_ORG)
			LogMessageA(hh, string("'" + Name + " (REW_route)' inflowDelay_in_storage (m^3) (m^3): ").c_str(), inflowDelay->Left(hh), 1.0);
		else
			LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str(), Clark_inflowDelay->Left(hh), 1.0);

		LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwinflow  (m^3) (m^3): ").c_str(), cumgwinflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwoutflow (m^3) (m^3): ").c_str(), cumgwoutflow[hh], 1.0);
		if (variation == VARIATION_ORG)
			LogMessageA(hh, string("'" + Name + " (REW_route)' gwDelay_in_storage (m^3) (m^3): ").c_str(), gwDelay->Left(hh), 1.0);
		else
			LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str(), Clark_gwDelay->Left(hh), 1.0);

		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (REW_route)' cumflow (m^3): ").c_str(), cumflow[0]);
	LogMessage(string("'" + Name + " (REW_route)' cumgwflow (m^3): ").c_str(), cumgwflow[0]);
	LogDebug(" ");

	if (variation == VARIATION_ORG) {
		delete inflowDelay;
		delete gwDelay;
	}
	else {
		delete Clark_inflowDelay;
		delete Clark_gwDelay;
	}
}


