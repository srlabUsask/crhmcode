#Create newmodules object library
add_library(newmodules OBJECT
    NewModules.cpp
)

target_include_directories(newmodules PUBLIC
    #ClassModule.h is required
    "${PROJECT_SOURCE_DIR}/modules"
    "${PROJECT_SOURCE_DIR}/core"
    "${PROJECT_SOURCE_DIR}/libs/spdlog/include"
)
