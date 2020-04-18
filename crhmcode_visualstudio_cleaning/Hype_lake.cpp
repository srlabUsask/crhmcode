#pragma once
// 01/23/18
//---------------------------------------------------------------------------
//#include <vcl.h>
#pragma hdrstop
#include "stdafx.h"
#include "Hype_lake.h"
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

ClassWQ_Lake* ClassWQ_Lake::klone(string name) const {
	return new ClassWQ_Lake(name);
}

void ClassWQ_Lake::decl(void) {

	Description = "'WQ Lake module.'";

	declstatvar("concslow", NHRU, "concentration of soil moisture per land-soil", "(mg/m^2)", &concslow, &concslow_lay, numsubstances);


	declvar("temp_l", NHRU, " (laketype,subbasin)", "(°C)", &temp_l);

	declvar("temp10_l", NHRU, "lake temperature10-day mean lake temperature (laketype,subbasin)", "(°C)", &temp10_l);

	declvar("temp20_l", NHRU, "20-day mean lake temperature (laketype,subbasin)", "(°C)", &temp20_l);

	declvar("TPmean_l", NHRU, "365-day mean Total Phosphorus concentration of lake (laketype,subbasin)", "(mg/m)", &TPmean_l);

	declstatvar("slowwater", NHRU, "volume or level of long turnover lake part (laketype,subbasin)", "(mm)", &slowwater);


	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("wp", NDEFN, "[1]", "1", "66", "water content at wilting point", "(mm)", &wp, &wp_lay, maxsoillayers);


	declparam("thickness", NDEFN, "[1]", "0", "100", "thickness of soil layers", "(mm)", &thickness, &thickness_lay, maxsoillayers);

	declparam("denpar", NHRU, "[1]", "0", "100", "parameter denitrification in soil", "(mm)", &denpar);

	declparam("calcN", NHRU, "[0]", "0", "1", "flag for nitrogen simulation", "()", &calcN);

	declparam("calcP", NHRU, "[0]", "0", "1", "flag for phosphorus simulation", "()", &calcP);

	//  declparam("i_sp", NHRU, "[0]", "0", "5", " soluble (reactive) phosphorus, i.e. phosphate", "(mm)", &i_sp);

	//  declparam("i_pp", NHRU, "[0]", "0", "5", " particulate phosphorus", "(mm)", &i_pp);

	//  declparam("i_oc", NHRU, "[0]", "0", "5", " (dissolved) organic carbon", "(mm)", &i_oc);

	declparam("conductP", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductP);

	declparam("conductN", NHRU, "[0]", "0", "1", "flag for conduct P", "()", &conductN);

	declparam("cohesion", NHRU, "[100]", "0", "1000", "cohesion", "(kPa)", &cohesion);

	declparam("erodibility", NHRU, "[0]", "0", "1", "erodibility", "(g/J)", &erodibility);

	declparam("closewater", NHRU, "[0]", "0", "1", "part of area (possibly agricultural area) close to water courses", "()", &closewater);

	declparam("buffer", NHRU, "[0]", "0", "1", "part of river length with buffer zones (of river in the area above (e.g. agricultural area))", "()", &buffer);

	declparam("sedonpar", NHRU, "[0]", "0", "1", "flag for sedonpar ON sedimentation rate  (lakes)", "()", &sedonpar);

	declparam("sedpppar", NHRU, "[100]", "0", "1000", "PP sedimentation rate  (lakes)", "()", &sedpppar);

	declparam("limonpar", NHRU, "[100]", "0", "1000", "limitation of sedimentation parameter", "(mg/l)", &limonpar);

	declparam("limpppar", NHRU, "[100]", "0", "1000", "limitation of sedimentation parameter", "(mg/l)", &limpppar);

	declparam("prodNpar", NHRU, "[0]", "0", "1", "production rate ON in water", "()", &prodNpar);

	declparam("prodPpar", NHRU, "[100]", "0", "1000", "production rate PP in water", "()", &prodPpar);

	declparam("sedocpar", NHRU, "[100]", "0", "1000", "OC sedimentation rate  (lakes)", "(m/d)", &sedocpar);

	declparam("laketype", NHRU, "[1]", "1", "2", "Lake or river type (1=local, 2=main/outlet))", "()", &laketype); // only used by "internal_lake_load"

	declparam("lake_depth", NHRU, "[1]", "1", "10", "depth of lake", "(m)", &lake_depth);

	declparam("pppar", NHRU, "[1]", "1", "10", "internal load of particulate phosphorus", "()", &pppar);

	declparam("sppar", NHRU, "[1]", "1", "10", "internal load of soluble (reactive) phosphorus", "()", &sppar);


	declputvar("*", "conc_top", "(mg/m^2)", &conc_top, &conc_top_lay);

	declputvar("*", "conc_bottom", "(mg/m^2)", &conc_bottom, &conc_bottom_lay);

	declputvar("*", "conc_below", "(mg/m^2)", &conc_below, &conc_below_lay);

	declgetvar("*", "soil_moisture", "(mm)", &water);

	declgetvar("*", "hru_t", "(°C)", &hru_t);

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_rain", "(mm)", &net_rain);

	declgetvar("*", "runoff", "(mm)", &runoff);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declgetvar("*", "SRP_conc", "(mg/l)", &SRP_conc);

	declgetvar("*", "poolPP", "(kg/km^2)", &poolPP);

	declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max);
}

void ClassWQ_Lake::init(void) {

}

void ClassWQ_Lake::run(void) {

	if (nstep == 1 || Global::Freq == 1) { // begining of day

		for (hh = 0; chkStruct(); ++hh) {
			np_processes_in_lake(laketype[hh], hru_area[hh], denpar[hh], prodNpar[hh], prodPpar[hh], sedonpar[hh], sedpppar[hh], limonpar[hh], limpppar[hh]);

			oc_processes_in_lake(laketype[hh], hru_area[hh], prodPpar[hh], limpppar[hh], sedocpar[hh]);
		}
	}
}

void ClassWQ_Lake::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessage(hh, string("'" + Name + " (WQ_Hype)'").c_str(), BLANK);
	}
	LogDebug(" ");
}

// Calculate nutrient processes in lake:
// denitrification, mineralisation, primary production,
// Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Common things in lakes and river,
// Denitrification, Primary production and mineralization, Sedimentation/Resuspension and Internal load)
// ------------------------------------------------------------------
void ClassWQ_Lake::np_processes_in_lake(const long laketype, const float area, const float denpar, const long prodNpar, const float prodPpar, const long sedonpar, const float sedpppar,
	const float limonpar, const float limpppar) {
	/*
	USE MODVAR, ONLY : conductN,conductP

	!Argument declarations
	long INTENT(IN) :: i          !<index of subbasin
	long, INTENT(IN) :: itype      !<lake type (ilake or olake)
	float, INTENT(IN)    :: area       !<lake area (m2)
	float, INTENT(IN)    :: denpar     !<model parameter denitrification rate (kg/m2/day)
	float, INTENT(IN)    :: prodNpar   !<model parameter production ON
	float, INTENT(IN)    :: prodPpar   !<model parameter production PP
	float, INTENT(IN)    :: sedonpar   !<ON sedimentation rate  (lakes)
	float, INTENT(IN)    :: sedpppar   !<PP sedimentation rate  (lakes)
	float, INTENT(IN)    :: limonpar   !<limitation of sedimentation parameter (mg/L)
	float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/

	// Calculate the nutrient processes
	if (conductP[hh])
		calculate_lake_tpmean(laketype);
	if (conductN[hh])
		denitrification_water(laketype, area, denpar); // denitrification in lakes    ??? LAKESTATE = lakestate

	production_mineralisation(laketype, area, prodNpar, prodPpar, limpppar);  // primary production and mineralisation in lakes
	sedimentation_lake(laketype, area, sedonpar, sedpppar, limonpar, limpppar);  // sedimentation of PP and ON in lakes
	if (conductP[hh])
		internal_lake_load(laketype, area);  // internal load of phosphorus

} // np_processes_in_lake

  // Calculates straight 365-day running average mean of TP
  // concentration in lake and mineralization) and Organic carbon (River and Lakes - Primary production and mineralization)
  // -----------------------------------------------------------------------
void ClassWQ_Lake::calculate_lake_tpmean(const long laketype) {
	/*
	USE MODVAR, ONLY : i_sp,i_pp

	!Argument declarations
	long, INTENT(IN) :: i         !<index of current subbasin
	long, INTENT(IN) :: watertype !<Lake type (1=local, 2=outlet)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/
	// Local variables
	float meanconc;

	meanconc = (water[hh] * (conc_top_lay[i_sp][hh] + conc_top_lay[i_pp][hh]) +
		slowwater[hh] * (concslow_lay[i_pp][hh] + concslow_lay[i_pp][hh])) /
		(water[hh] + slowwater[hh]);
	TPmean_l[hh] = TPmean_l[hh] + (meanconc - TPmean_l[hh]) / 365.0;

} // calculate_lake_tpmean

  // Calculates the denitrification in river and lakes
  // Lake processes in slow turnover lake part.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Denitrification)
  // -----------------------------------------------------------------------
void ClassWQ_Lake::denitrification_water(const long laketype, const float area, const float denpar) {
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
	// lakes
	vol = slowwater[hh] * hru_area[hh] * 1.0E-6;    // 0.001 m3
	waterconc = concslow_lay[i_in][hh];          // mg/L
	inorganicNpool[0] = vol * waterconc;                          // kg
	watertemp = temp_l[hh];

	// Temperature and concentration dependence factor
	tmpfcn = tempfactor(watertemp);
	concfcn = halfsatconcfactor(waterconc, halfsatINwater);

	// Denitrification
	denitri_water[0] = denpar * area * concfcn * tmpfcn;   // kg
	denitri_water[0] = min <float>(maxdenitriwater*inorganicNpool[0], denitri_water[0]);    // max 50% kan be denitrified
	retention_pool(pooldim, inorganicNpool, denitri_water);
	new_concentration(inorganicNpool[0], vol, concslow_lay[i_in][hh]);
} // denitrification_water

  // Calculates transformation between IN/ON and SRP/PP in water.
  // Simulating the combined processes of primary production and
  //   mineralisation. Lake processes in slow turnover lake part.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Primary production and mineralization)
  // -----------------------------------------------------------------------
void ClassWQ_Lake::production_mineralisation(const long laketype, const float area, const float prodNpar, const float prodPpar, const float limpppar,
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
	// lakes
	vol = slowwater[hh] * area / 1.0E6;
	if (conductN[hh]) {
		INpool[0] = vol * concslow_lay[i_in][hh];   // kg
		ONpool[0] = vol * concslow_lay[i_on][hh];   // kg
	}
	if (conductP[hh]) {
		SRPpool[0] = vol * concslow_lay[i_sp][hh];  // kg
		PPpool[0] = vol * concslow_lay[i_pp][hh];  // kg
	}

	// Set help variables
	// lakes
	watertemp = temp_l[hh];
	waterdepth = slowwater[hh] / 1000.;
	waterTPmean = TPmean_l[hh];

	if (watertemp > 0.0) { // Total phosphorus concentration dependent factor
		TPfcn = halfsatconcfactor(max <float>(waterTPmean - limpppar, 0.), halfsatTPwater);

		// Temperature dependent factor
		tmpfcn1 = watertemp / 20.0;
		tmpfcn2 = (temp10_l - temp20_l) / 5.0;
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
		// lakes
		if (conductN[hh])
			new_concentration(INpool[0], vol, concslow_lay[i_in][hh]);
		if (conductN[hh])
			new_concentration(ONpool[0], vol, concslow_lay[i_on][hh]);
		if (conductP[hh])
			new_concentration(SRPpool[0], vol, concslow_lay[i_sp][hh]);
		if (conductP[hh])
			new_concentration(PPpool[0], vol, concslow_lay[i_pp][hh]);
	}
} // production_mineralisation

  // Calculate sedimentation of PP and ON in lakes.
  // Lake processes in slow turnover lake part.
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Sedimentation/Resuspension)
  // -----------------------------------------------------------------
void ClassWQ_Lake::sedimentation_lake(const long laketype, const float area, const float sedonpar, const float sedpppar, const float limonpar, const float limpppar) {
	/*
	USE MODVAR, ONLY : conductN,conductP, &
	i_on,i_pp

	!Argument declarations
	long, INTENT(IN) :: i          !<index of current subbasin
	long, INTENT(IN) :: watertype  !<Lake type (1=local, 2=outlet)
	float, INTENT(IN)    :: area       !<lake surface area (m2)
	float, INTENT(IN)    :: sedonpar   !<ON sedimentation rate  (lakes) (m/d)
	float, INTENT(IN)    :: sedpppar   !<PP sedimentation rate  (lakes) (m/d)
	float, INTENT(IN)    :: limonpar   !<limitation of sedimentation parameter (mg/L)
	float, INTENT(IN)    :: limpppar   !<limitation of sedimentation parameter (mg/L)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/
	// Local variables
	float waterconcON, waterconcPP;
	float ONpool[1], PPpool[1]; // pools in water (kg)
	float sedON[1], sedPP[1];   // changes (kg/d)
	float vol;

	// Initial check
	if (!conductN[hh] && !conductP[hh]) return;

	// Calculate nutrient pool and concentration of water
	vol = slowwater[hh] * area * 1.0E-6;
	if (conductN[hh]) {
		ONpool[0] = vol * concslow_lay[i_on][hh];  // kg
		waterconcON = concslow_lay[i_on][hh]; // mg/l
	}
	if (conductP[hh]) {
		PPpool[0] = vol * concslow_lay[i_pp][hh];  // kg
		waterconcPP = concslow_lay[i_pp][hh]; // mg/l
	}

	// Calculate sedimentation
	if (conductN[hh]) sedON[0] = sedonpar * max <float>(waterconcON - limonpar, 0.0) * 1.0E-3 * area;    // kg
	if (conductP[hh]) sedPP[0] = sedpppar * max <float>(waterconcPP - limpppar, 0.0) * 1.0E-3 * area;    // kg

																										 // Remove sedimentation from the water
	if (conductN[hh])  retention_pool(1, ONpool, sedON);
	if (conductP[hh])  retention_pool(1, PPpool, sedPP);

	// Calculate the new concentration in the water due to the change in the pool
	if (conductN[hh])  new_concentration(ONpool[0], vol, concslow_lay[i_on][hh]);
	if (conductP[hh])  new_concentration(PPpool[0], vol, concslow_lay[i_pp][hh]);

} // sedimentation_lake

  // Calculates and add internal load of phosphorus for lakes
  // Lake processes in slow turnover lake part
  // Reference ModelDescription Chapter Nitrogen and phosphorus processes in rivers and lakes (Internal load)
  // -------------------------------------------------------------
void ClassWQ_Lake::internal_lake_load(const long laketype, const float area) {
	/*
	USE MODVAR, ONLY : lakeindex,   &
	lakedatapar, &
	lakedataparindex,  &
	i_sp,i_pp,   &
	numsubstances
	USE HYPEVARIABLES, ONLY : m_ldprodpp,  &
	m_ldprodsp

	!Argument declarations
	long, INTENT(IN) :: i           !<index of current subbasin
	long, INTENT(IN) :: watertype   !<Lake or river type (1=local, 2=main/outlet)
	long, INTENT(IN) :: systemtype  !<aquatic system type (1=lake, 2=river)
	float, INTENT(IN)    :: area        !<lake surface area/ river bottom area (m2)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/
	// Local variables
	float prodPP, prodSP;
	float tmpfcn, TPfcn;
	float vol;
	//    float pppar, sppar; // now a parameter
	float sourceP[numsubstances];

	// Local parameters
	//    const long pooldim = 0;

	// Check if internal phosphorus load is to be calculated
	if (laketype == 1)
		return;    // local
				   //    if(!=ALLOCATED(lakeindex)) return;  // no special lakes
				   //    pppar = lakedatapar(lakedataparindex(watertype), m_ldprodpp);
				   //    sppar = lakedatapar(lakedataparindex(watertype), m_ldprodsp);
	if (pppar == 0 && sppar == 0) return;
	sourceP[0] = 0.0;

	// Calculate pool of P, and concentration and temperature dependent factors
	TPfcn = 0.1;
	tmpfcn = pow(0.86, (abs(temp_l[hh]) - 15.));   // laketemp=T20 for olake

												   // Calculate internal load of phosphorus
	prodPP = pppar[hh] * TPfcn * tmpfcn * area / 1000.0;  // kg/d
	prodSP = sppar[hh] * TPfcn * tmpfcn * area / 1000.0;  // kg/d
	sourceP[i_pp] = prodPP;
	sourceP[i_sp] = prodSP;

	// Add internal load of phosphorus to lake water
	vol = slowwater[hh] * area / 1.0E6;
	add_source_to_water(vol, numsubstances, concslow_lay[i_in][hh], sourceP[hh]);

} // internal_lake_load

  // Calculate organic carbon processes in lake
  //  Mineralisation, primary production, sedimentation
  // Reference ModelDescription Chapter Organic carbon (River and Lakes)
  // ------------------------------------------------------------------
void ClassWQ_Lake::oc_processes_in_lake(const long watertype, const long area, const long prodpar, const long limpppar, const long sedocpar) {

	//    USE MODVAR, ONLY : i_oc
	/*
	!Argument declarations
	INTEGER, INTENT(IN) :: i                        !<current index of subbasin
	INTEGER, INTENT(IN) :: watertype                !<lake type (ilake or olake)
	REAL, INTENT(IN)    :: area                     !<lake area (m2)
	REAL, INTENT(IN)    :: prodpar                  !<model parameter production OC
	REAL, INTENT(IN)    :: limpppar                 !<limitation of sedimentation parameter (mg/L)
	REAL, INTENT(IN)    :: sedocpar                 !<OC sedimentation rate  (lakes)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/
	// Local parameters

	// Calculate the nutrient processes

	oc_production_mineralisation(area, prodpar, limpppar,
		slowwater[hh], concslow_lay[i_oc][hh],
		temp[hh], TPmean_l[hh], temp10_l[hh], temp20_l[hh], lake_depth[hh]);

	oc_sedimentation(area, sedocpar); // sedimentation in lakes

} // SUBROUTINE oc_processes_in_lake

void ClassWQ_Lake::oc_production_mineralisation(const float area, float prodpar, float limpppar, float water, float conc, float watertemp,
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

	OCpool[0] = (water * area * conc) / 1.0E6; // kg  *** lake
	waterdepth = depth / 1000.0;

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

	if (water > 0.0) { // lake
		vol = water * area / 1.0E6;
		new_concentration(OCpool[0], vol, conc);
	}
} //  oc_production_mineralisation// Calculates the denitrification in river and lakes

  // Calculate sedimentation of OC in lakes
  // Reference ModelDescription Chapter Organic carbon (River and lakes - Sedimentation)
  // --------------------------------------------------------------------------
void ClassWQ_Lake::oc_sedimentation(const float area, const float sedocpar) {
	/*
	USE MODVAR, ONLY : i_oc

	!Argument declarations
	INTEGER, INTENT(IN) :: i          !<current index of subbasin
	INTEGER, INTENT(IN) :: watertype  !<Lake or river type (1=local, 2=main/outlet)
	REAL, INTENT(IN)    :: area       !<lake surface area (m2)
	REAL, INTENT(IN)    :: sedocpar   !<OC sedimentation rate  (lakes) (m/d)
	TYPE(lakestatetype),INTENT(INOUT) :: lakestate  !<Lake state
	*/
	// Local variables
	float OCpool;          // pools in water (kg)
	float sedOC;          // changes (kg/d)
	float vol;

	// Calculate pool and sedimantation
	OCpool = (slowwater[hh] * concslow_lay[i_oc][hh] * area) / 1.0E6; // kg
	sedOC = (sedocpar * (concslow_lay[i_oc][hh]) / 1000.0) * area;    // kg

																	  // Remove sedimentation from water pool
	retention_pool(1, &OCpool, &sedOC);

	// Calculate the new concentration in the water due to the change in the pool
	vol = slowwater[hh] * area / 1.0E6;
	new_concentration(OCpool, vol, concslow_lay[i_oc][hh]);

} // SUBROUTINE oc_sedimentation


