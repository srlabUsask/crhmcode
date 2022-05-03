add_library(hype OBJECT
    Hype_CRHM.cpp
    Hype_lake.cpp
    Hype_river.cpp
    Hype_routines.cpp
)

target_include_directories(hype PUBLIC
    ../
    ../../libs/boost_1_75_0
    "${PROJECT_SOURCE_DIR}/core"
    "${PROJECT_SOURCE_DIR}/libs/spdlog/include"
)
