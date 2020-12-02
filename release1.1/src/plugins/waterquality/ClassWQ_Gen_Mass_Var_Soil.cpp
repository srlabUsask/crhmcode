#include "ClassWQ_Gen_Mass_Var_Soil.h"


ClassWQ_Gen_Mass_Var_Soil* ClassWQ_Gen_Mass_Var_Soil::klone(string name) const {
    return new ClassWQ_Gen_Mass_Var_Soil(name);
}

void ClassWQ_Gen_Mass_Var_Soil::decl(void) {

    Description = "'Generates variable mWQ balances.'";

    declstatvar("soil_top_change_mWQ", TDim::NDEFN, "mass of solute soil_rechr change.", "(mg/l * mm*km^2/int)", &soil_top_change_mWQ, &soil_top_change_mWQ_lay, numsubstances);

    declstatvar("soil_moist_change_mWQ", TDim::NDEFN, "mass of solute soil_moist change.", "(mg/l * mm*km^2/int)", &soil_moist_change_mWQ, &soil_moist_change_mWQ_lay, numsubstances);

    declstatvar("soil_bottom_change_mWQ", TDim::NDEFN, "mass of solute soil_bottom change.", "(mg/l * mm*km^2/int)", &soil_bottom_change_mWQ, &soil_bottom_change_mWQ_lay, numsubstances);

    declstatvar("soil_ssr_change_mWQ", TDim::NDEFN, "mass of solute soil_bottom change.", "(mg/l * mm*km^2/int)", &soil_ssr_change_mWQ, &soil_ssr_change_mWQ_lay, numsubstances);

    declstatvar("Sd_change_mWQ", TDim::NDEFN, "mass of solute Sd change.", "(mg/l * mm*km^2/int)", &Sd_change_mWQ, &Sd_change_mWQ_lay, numsubstances);

    declstatvar("gw_change_mWQ", TDim::NDEFN, "mass of solute gw change.", "(mg/l * mm*km^2/int)", &gw_change_mWQ, &gw_change_mWQ_lay, numsubstances);

    declstatvar("soil_gw_change_mWQ", TDim::NDEFN, "mass of solute soil_gw change.", "(mg/l * mm*km^2/int)", &soil_gw_change_mWQ, &soil_gw_change_mWQ_lay, numsubstances);

    declstatvar("gw_flow_change_mWQ", TDim::NDEFN, "mass of solute gw_flow change.", "(mg/l * mm*km^2/int)", &gw_flow_change_mWQ, &gw_flow_change_mWQ_lay, numsubstances);

    declstatvar("infil_act_change_mWQ", TDim::NDEFN, "mass of solute infil_act change.", "(mg/l * mm*km^2/int)", &infil_act_change_mWQ, &infil_act_change_mWQ_lay, numsubstances);

    declstatvar("redirected_residual_change_mWQ", TDim::NDEFN, "mass of solute redirected_residual change.", "(mg/l * mm*km^2/int)", &redirected_residual_change_mWQ, &redirected_residual_change_mWQ_lay, numsubstances);

    declstatvar("soil_runoff_change_mWQ", TDim::NDEFN, "mass of solute soil_runoff change.", "(mg/l * mm*km^2/int)", &soil_runoff_change_mWQ, &soil_runoff_change_mWQ_lay, numsubstances);

    declstatvar("soil_top_mWQ_last", TDim::NDEFN, "mass of solute soil_rechr.", "(mg/l * mm*km^2/int)", &soil_top_mWQ_last, &soil_top_mWQ_lay_last, numsubstances);

    declstatvar("soil_bottom_mWQ_last", TDim::NDEFN, "mass of solute soil_bottom.", "(mmg/l * mm*km^2/intg)", &soil_bottom_mWQ_last, &soil_bottom_mWQ_lay_last, numsubstances);

    declstatvar("soil_ssr_mWQ_last", TDim::NDEFN, "mass of solute soil_ssr.", "(mg/l * mm*km^2/int)", &soil_ssr_mWQ_last, &soil_ssr_mWQ_lay_last, numsubstances);

    declstatvar("Sd_mWQ_last", TDim::NDEFN, "mass of solute Sd.", "(mg/l * mm*km^2/int)", &Sd_mWQ_last, &Sd_mWQ_lay_last, numsubstances);

    declstatvar("gw_mWQ_last", TDim::NDEFN, "mass of solute gw.", "(mg/l * mm*km^2/int)", &gw_mWQ_last, &gw_mWQ_lay_last, numsubstances);

    declstatvar("soil_gw_mWQ_last", TDim::NDEFN, "mass of solute soil_gw.", "(mg/l * mm*km^2/int)", &soil_gw_mWQ_last, &soil_gw_mWQ_lay_last, numsubstances);

    declstatvar("gw_flow_mWQ_last", TDim::NDEFN, "mass of solute gw_flow.", "(mg/l * mm*km^2/int)", &gw_flow_mWQ_last, &gw_flow_mWQ_lay_last, numsubstances);

    declstatvar("infil_act_mWQ_last", TDim::NDEFN, "mass of solute infil_act.", "(mg/l * mm*km^2/int)", &infil_act_mWQ_last, &infil_act_mWQ_lay_last, numsubstances);

    declstatvar("redirected_residual_mWQ_last", TDim::NDEFN, "mass of solute redirected_residual.", "(mg/l * mm*km^2/int)", &redirected_residual_mWQ_last, &redirected_residual_mWQ_lay_last, numsubstances);

    declstatvar("soil_runoff_mWQ_last", TDim::NDEFN, "mass of solute soil_runoff.", "(mg/l * mm*km^2/int)", &soil_runoff_mWQ_last, &soil_runoff_mWQ_lay_last, numsubstances);

    declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);

    declgetvar("*", "soil_lower", "(mm)", &soil_lower);

    declgetvar("*", "soil_moist", "(mm)", &soil_moist);

    declgetvar("*", "soil_ssr", "(mm)", &soil_ssr);

    declgetvar("*", "Sd", "(mm)", &Sd);

    declgetvar("*", "gw", "(mm)", &gw);

    declgetvar("*", "soil_gw", "(mm)", &soil_gw);

    declgetvar("*", "gw_flow", "(mm)", &gw_flow);

    declgetvar("*", "infil_act", "(mm)", &infil_act);

    declgetvar("*", "redirected_residual", "(mm)", &redirected_residual);

    declgetvar("*", "soil_runoff", "(mm)", &soil_runoff);

    declgetvar("*", "conc_soil_rechr", "(mg/l)", &conc_soil_rechr, &conc_soil_rechr_lay);

    declgetvar("*", "conc_soil_lower", "(mg/l)", &conc_soil_lower, &conc_soil_lower_lay);

    declgetvar("*", "soil_ssr_conc", "(mg/l)", &soil_ssr_conc, &soil_ssr_conc_lay);

    declgetvar("*", "Sd_conc", "(mg/l)", &Sd_conc, &Sd_conc_lay);

    declgetvar("*", "gw_conc", "(mg/l)", &gw_conc, &gw_conc_lay);

    declgetvar("*", "soil_gw_conc", "(mg/l)", &soil_gw_conc, &soil_gw_conc_lay);

    declgetvar("*", "gw_flow_conc", "(mg/l)", &gw_flow_conc, &gw_flow_conc_lay);

    declgetvar("*", "infil_act_conc", "(mg/l)", &infil_act_conc, &infil_act_conc_lay);

    declgetvar("*", "redirected_residual_conc", "(mg/l)", &redirected_residual_conc, &redirected_residual_conc_lay);

    declgetvar("*", "soil_runoff_cWQ", "(mg/l)", &soil_runoff_cWQ, &soil_runoff_cWQ_lay);

}

void ClassWQ_Gen_Mass_Var_Soil::init(void) {

    nhru = getdim(TDim::NHRU);

    for (hh = 0; chkStruct(); ++hh) {
        for (long Sub = 0; Sub < numsubstances; ++Sub) {
            soil_top_change_mWQ_lay[Sub][hh] = 0.0;
            soil_moist_change_mWQ_lay[Sub][hh] = 0.0;
            soil_bottom_change_mWQ_lay[Sub][hh] = 0.0;
            soil_ssr_change_mWQ_lay[Sub][hh] = 0.0;
            Sd_change_mWQ_lay[Sub][hh] = 0.0;
            gw_change_mWQ_lay[Sub][hh] = 0.0;
            soil_gw_change_mWQ_lay[Sub][hh] = 0.0;
            gw_flow_change_mWQ_lay[Sub][hh] = 0.0;
            infil_act_change_mWQ_lay[Sub][hh] = 0.0;
            redirected_residual_change_mWQ_lay[Sub][hh] = 0.0;
            soil_runoff_change_mWQ_lay[Sub][hh] = 0.0;

            soil_top_mWQ_lay_last[Sub][hh] = soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh];
            soil_bottom_mWQ_lay_last[Sub][hh] = soil_lower[hh] * conc_soil_lower_lay[Sub][hh];
            soil_ssr_mWQ_lay_last[Sub][hh] = soil_ssr[hh] * soil_ssr_conc_lay[Sub][hh];
            Sd_mWQ_lay_last[Sub][hh] = Sd[hh] * Sd_conc_lay[Sub][hh];
            gw_mWQ_lay_last[Sub][hh] = gw[hh] * gw_conc_lay[Sub][hh];
            soil_gw_mWQ_lay_last[Sub][hh] = soil_gw[hh] * soil_gw_conc_lay[Sub][hh];
            gw_flow_mWQ_lay_last[Sub][hh] = gw_flow[hh] * gw_flow_conc_lay[Sub][hh];
            infil_act_mWQ_lay_last[Sub][hh] = infil_act[hh] * infil_act_conc_lay[Sub][hh];
            redirected_residual_mWQ_lay_last[Sub][hh] = redirected_residual[hh] * redirected_residual_conc_lay[Sub][hh];
            soil_runoff_mWQ_lay_last[Sub][hh] = soil_runoff[hh] * soil_runoff_cWQ_lay[Sub][hh];
        }
    }
}

void ClassWQ_Gen_Mass_Var_Soil::run(void) {

    for (long Sub = 0; Sub < numsubstances; ++Sub) {
        double temp;
        for (hh = 0; chkStruct(); ++hh) {
            temp = soil_rechr[hh] * conc_soil_rechr_lay[Sub][hh]; // using "conc"
            soil_top_change_mWQ_lay[Sub][hh] = temp - soil_top_mWQ_lay_last[Sub][hh];
            soil_top_mWQ_lay_last[Sub][hh] = temp;

            temp = soil_lower[hh] * conc_soil_lower_lay[Sub][hh];
            soil_bottom_change_mWQ_lay[Sub][hh] = temp - soil_bottom_mWQ_lay_last[Sub][hh];
            soil_bottom_mWQ_lay_last[Sub][hh] = temp;

            soil_moist_change_mWQ_lay[Sub][hh] = soil_top_change_mWQ_lay[Sub][hh] + soil_bottom_change_mWQ_lay[Sub][hh];

            temp = soil_ssr[hh] * soil_ssr_conc_lay[Sub][hh];
            soil_ssr_change_mWQ_lay[Sub][hh] = temp - soil_ssr_mWQ_lay_last[Sub][hh];
            soil_ssr_mWQ_lay_last[Sub][hh] = temp;

            temp = Sd[hh] * Sd_conc_lay[Sub][hh];
            Sd_change_mWQ_lay[Sub][hh] = temp - Sd_mWQ_lay_last[Sub][hh];
            Sd_mWQ_lay_last[Sub][hh] = temp;

            temp = gw[hh] * gw_conc_lay[Sub][hh];
            gw_change_mWQ_lay[Sub][hh] = temp - gw_mWQ_lay_last[Sub][hh];
            gw_mWQ_lay_last[Sub][hh] = temp;

            temp = soil_gw[hh] * soil_gw_conc_lay[Sub][hh];
            soil_gw_change_mWQ_lay[Sub][hh] = temp - soil_gw_mWQ_lay_last[Sub][hh];
            soil_gw_mWQ_lay_last[Sub][hh] = temp;

            temp = gw_flow[hh] * gw_flow_conc_lay[Sub][hh];
            gw_flow_change_mWQ_lay[Sub][hh] = temp - gw_flow_mWQ_lay_last[Sub][hh];
            gw_flow_mWQ_lay_last[Sub][hh] = temp;

            temp = infil_act[hh] * infil_act_conc_lay[Sub][hh];
            infil_act_change_mWQ_lay[Sub][hh] = temp - infil_act_mWQ_lay_last[Sub][hh];
            infil_act_mWQ_lay_last[Sub][hh] = temp;

            temp = redirected_residual[hh] * redirected_residual_conc_lay[Sub][hh];
            redirected_residual_change_mWQ_lay[Sub][hh] = temp - redirected_residual_mWQ_lay_last[Sub][hh];
            redirected_residual_mWQ_lay_last[Sub][hh] = temp;

            temp = soil_runoff[hh] * soil_runoff_cWQ_lay[Sub][hh];
            soil_runoff_change_mWQ_lay[Sub][hh] = temp - soil_runoff_mWQ_lay_last[Sub][hh];
            soil_runoff_mWQ_lay_last[Sub][hh] = temp;
        }
    }
}

void ClassWQ_Gen_Mass_Var_Soil::finish(bool good) {

    LogDebug("**WQ_Gen_Mass_Var_Soil**");
    LogDebug(" ");

}