add_library(newmodules OBJECT
    NewModules.cpp
)

target_include_directories(newmodules PUBLIC
    ../
    ../../libs/boost_1_75_0
)
