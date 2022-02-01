include(ExternalProject)

#Require spdlog
ExternalProject_Add(spdlog
    PREFIX spdlog
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/spdlog
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
    -DSPDLOG_BUILD_SHARED=OFF
)

add_subdirectory(exec)
add_subdirectory(def)
add_subdirectory(filter)

add_library(core OBJECT
    Administer.cpp
    ClassClark.cpp
    ClassCRHM.cpp
    ClassData.cpp
    Classfilter.cpp
    ClassMacro.cpp
    ClassModel.cpp
    ClassModule.cpp
    ClassMuskingum.cpp
    ClassPar.cpp
    ClassVar.cpp
    Common.cpp
    Convert.cpp
    CRHM_parse.cpp
    CRHMArguments.cpp
    CRHMLogger.cpp
    CRHMMain.cpp
    GlobalDll.cpp
    MacroClass.cpp
    MacroUnit.cpp
    Myparser.cpp
    ReportStream.cpp
    snowcover.cpp
    StandardConverterUtility.cpp
    Tresult.cpp
    VarCHRM.cpp
)

add_dependencies(core spdlog exec def filter)

target_include_directories(core PUBLIC
    "${STAGING_DIR}/include/" #Includes the spdlog libs
    "${PROJECT_SOURCE_DIR}/config.h"
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)
