cmake_minimum_required(VERSION 3.10)

set(ACTIVE_LOG_LEVEL "2")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(config.h.in config.h)

project(crhm)

include(ExternalProject)

SET(BOOST_ROOT '${PROJECT_SOURCE_DIR}/libs/boost')
ExternalProject_Add(boost
    PREFIX boost
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/boost
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
)





add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(core)
add_subdirectory(modules)

target_link_libraries(${PROJECT_NAME}
    core
    modules
)

add_dependencies(core boost)

target_include_directories(${PROJECT_NAME} PUBLIC
    config.h
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/core"
    "${PROJECT_SOURCE_DIR}/modules"
    "${PROJECT_SOURCE_DIR}/modules/newmodules"
    "${PROJECT_SOURCE_DIR}/modules/waterquality"
    "${PROJECT_SOURCE_DIR}/modules/hype"
)
