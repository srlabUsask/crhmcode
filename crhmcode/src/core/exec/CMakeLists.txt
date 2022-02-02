#create exec object libary
add_library(exec OBJECT
    execbase.cpp
)


target_include_directories(exec PUBLIC
    #boost headers required
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)
