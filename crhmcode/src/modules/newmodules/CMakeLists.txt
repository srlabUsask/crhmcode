add_library(newmodules OBJECT
    NewModules.cpp
)

target_include_directories(newmodules PUBLIC
    "${PROJECT_SOURCE_DIR}/modules"
)
