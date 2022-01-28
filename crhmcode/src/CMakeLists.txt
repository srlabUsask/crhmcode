cmake_minimum_required(VERSION 3.10)

configure_file(config.h.in config.h)

set(ACTIVE_LOG_LEVEL "2")
set(CXX_STANDARD 14)

# set( BOOST_ROOT "libs/boost_1_75_0")
# #set( BOOST_LIBRARYDIR "libs/boost_1_75_0/libs")
# set( BOOST_INCLUDEDIR "libs/boost_1_75_0/boost")
# #set( Boost_NO_SYSTEM_PATHS ON)
# message(STATUS "BOOST_ROOT: ${BOOST_ROOT}")
# configure a header file to pass some of the CMake settings
# to the source code


project(crhm)

# find_package(Boost REQUIRED COMPONENTS spirit)
#
# if(NOT TARGET Boost::spirit)
#     add_library(Boost::spirit IMPORTED INTERFACE)
#     set_property(TARGET Boost::spirit PROPERTY
#         INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
#     set_property(TARGET Boost::spirit PROPERTY
#         INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
# endif()
add_compile_options( -std=c++14 -static -static-libgcc -static-libstdc++ -lstdc++)


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

# target_link_libraries(${PROJECT_NAME} PUBLIC
#     modules
#     core
#     # Boost::spirit
# )

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
    "${PROJECT_SOURCE_DIR}/libs/boost_1_75_0"
)
