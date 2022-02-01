add_library(exec OBJECT
    execbase.cpp
)

target_include_directories(exec PUBLIC
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)
