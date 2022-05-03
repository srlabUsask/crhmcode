#Create filter object library
add_library(filter OBJECT
    Classabs.cpp
    Classadd.cpp
    ClassaddV.cpp
    Classconst.cpp
    Classcos.cpp
    ClassCtoK.cpp
    Classdiv.cpp
    ClassdivV.cpp
    Classea.cpp
    Classexp.cpp
    Classexpv.cpp
    ClassForce.cpp
    ClassFtoC.cpp
    Classjulian.cpp
    ClassKtoC.cpp
    Classlog.cpp
    Classlogv.cpp
    ClassMissing.cpp
    ClassMissing0.cpp
    ClassMissingC.cpp
    ClassMissingFlag.cpp
    ClassMissingFlagAfter.cpp
    ClassMissingInter.cpp
    ClassMissingrepl.cpp
    Classmul.cpp
    ClassmulV.cpp
    Classpoly.cpp
    Classpolyv.cpp
    Classpow.cpp
    Classpowv.cpp
    Classpulse.cpp
    Classramp.cpp
    Classrandom.cpp
    Classrefwind.cpp
    ClassReplace.cpp
    ClassRH_WtoI.cpp
    Classrh.cpp
    ClassSim.cpp
    ClassSmear.cpp
    Classsquare.cpp
    Classsub.cpp
    ClasssubV.cpp
    Classtime.cpp
    ClassTimeshift.cpp
    Classsin.cpp
)

target_include_directories(filter PUBLIC
    #boost headers required
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
    "${PROJECT_SOURCE_DIR}/core"
    "${PROJECT_SOURCE_DIR}/libs/spdlog/include"
)
