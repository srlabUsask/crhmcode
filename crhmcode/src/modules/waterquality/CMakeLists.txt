add_library(waterquality OBJECT
    Class_lapse_rate_Monthly.cpp
    ClassGlacier_debris_cover.cpp
    ClassGlacier_melt_debris_cover_estimate_Mod.cpp
    ClassGrow_crops_annually.cpp
    Classlapse_rate_Monthly_Mod.cpp
    ClassSoilPrairie.cpp
    ClassWQ_Gen_Mass_Var_Netroute.cpp
    ClassWQ_Gen_Mass_Var_Soil.cpp
    ClassWQ_mass_conc.cpp
    ClassWQ_Netroute_M_D.cpp
    ClassWQ_Netroute.cpp
    ClassWQ_pbsm.cpp
    ClassWQ_pbsmSnobal.cpp
    ClassWQ_Soil.cpp
    ClassWQ_Substitute_Hype.cpp
    ClassWQ_Test_Hype.cpp
    WQ_CRHM.cpp
    WQ_Soil_NPCcycling.cpp
)

target_include_directories(waterquality PUBLIC
    ../../libs/boost_1_75_0
)
