cmake_minimum_required(VERSION 3.10)
project(crhm VERSION 1.2)

#Project uses C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Logging level used by spdlog
# 0 - Trace
# 1 - Debug
# 2 - Info
# 3 - Warning
# 4 - Error
# 5 - Critical
# 6 - Off
set(ACTIVE_LOG_LEVEL "2")

#Local Boost Location must be set to the path to a boost download
# relative to the src folder.
set(LOCAL_BOOST_LOCATION "/libs/boost_1_75_0")

# Set the staging directory for finding spdlog library
#set(STAGING_DIR ".")

#If no Build Type is specified default to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

if(CMAKE_BUILD_TYPE EQUAL Release)
    set(ACTIVE_LOG_LEVEL "2")
endif()

if(CMAKE_BUILD_TYPE EQUAL DEBUG)
    set(DEBUG ON)
    set(ACTIVE_LOG_LEVEL "0")
endif()

#Debug symbols on in Debug mode
set(CMAKE_CXX_FLAGS_DEBUG "-g")
#Optimization on for Release mode
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Configuration stored in crhmConfig.h
configure_file(crhmConfig.h.in crhmConfig.h)

#Build the crhm executable from the object files
add_executable(${PROJECT_NAME} main.cpp
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:modules>
    $<TARGET_OBJECTS:waterquality>
    $<TARGET_OBJECTS:newmodules>
    $<TARGET_OBJECTS:def>
    $<TARGET_OBJECTS:exec>
    $<TARGET_OBJECTS:filter>
)

#Evaluate the core subdirectory to build the core objects
add_subdirectory(core)

#Evaluate the modules subdirectory to build the modules objects
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
    "${PROJECT_SOURCE_DIR}/libs/spdlog/include"
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)

install(TARGETS crhm DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/crhmConfig.h"
  DESTINATION include
 )

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${crhm_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${crhm_VERSION_MINOR}")
include(CPack)
