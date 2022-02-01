cmake_minimum_required(VERSION 3.10)
project(crhm VERSION 1.2)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

if(CMAKE_BUILD_TYPE EQUAL DEBUG)
    set(DEBUG TRUE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(ACTIVE_LOG_LEVEL "2")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LOCAL_BOOST_LOCATION "/libs/boost_1_75_0")
configure_file(config.h.in config.h)

add_executable(${PROJECT_NAME} main.cpp
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:modules>
    $<TARGET_OBJECTS:waterquality>
    $<TARGET_OBJECTS:newmodules>
    $<TARGET_OBJECTS:def>
    $<TARGET_OBJECTS:exec>
    $<TARGET_OBJECTS:filter>
)

add_subdirectory(core)
add_subdirectory(modules)

add_dependencies(${PROJECT_NAME} core modules)

target_include_directories(${PROJECT_NAME} PUBLIC
    config.h
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/core"
    "${PROJECT_SOURCE_DIR}/core/def"
    "${PROJECT_SOURCE_DIR}/core/exec"
    "${PROJECT_SOURCE_DIR}/core/filter"
    "${PROJECT_SOURCE_DIR}/modules"
    "${PROJECT_SOURCE_DIR}/modules/newmodules"
    "${PROJECT_SOURCE_DIR}/modules/waterquality"
    "${PROJECT_SOURCE_DIR}/modules/hype"
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)

install(TARGETS crhm DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/Config.h"
  DESTINATION include
 )

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${crhm_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${crhm_VERSION_MINOR}")
include(CPack)
