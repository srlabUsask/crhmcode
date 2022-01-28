add_library(exec OBJECT
    execbase.cpp
)

target_include_directories(exec PUBLIC
    ../../libs/boost_1_75_0
)
