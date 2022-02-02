#create def object libary
add_library(def OBJECT
    DefCRHM.cpp
    Defdecldiag.cpp
    Defdeclgetvar.cpp
    Defdecllocal.cpp
    Defdeclobsfunc.cpp
    Defdeclparam.cpp
    Defdeclputvar.cpp
    Defdeclreadobs.cpp
    Defdeclstatvar.cpp
    Defdeclvar.cpp
    Defdeclputparam.cpp
    Defdeclobs.cpp
)

target_include_directories(def PUBLIC
    #boost headers required
    "${PROJECT_SOURCE_DIR}/${LOCAL_BOOST_LOCATION}"
)
