cmake_minimum_required(VERSION 3.16) # Helps to have this repeated in case you want this to be the root of seperate project

set(MC_LIBRARY ${PROJECT_NAME_STR}_lib)

#include(${CMAKE_CURRENT_LIST_DIR}/cmake/quantlib.cmake)


set(MC_LIB_HDR 
    tools/errortracking.h
    formula/Black76Formula.h
    ratesource/ratesource.h
    ratesource/discount/discountratesource.h
    ratesource/discount/discountcurve.h
    ratesource/discount/flatrate.h
    )

set(MC_LIB_SRC 
    tools/errortracking.cpp
    formula/Black76Formula.cpp
    ratesource/ratesource.cpp
    ratesource/discount/discountcurve.cpp
    ratesource/discount/flatrate.cpp
    )

# Making use of the target_sources(...) to add sources and headers rather than listing them in the add_library(...) macro. 
# target_sources allows sources to be declared as PRIVATE (necessary to build), INTERFACE (not required for build, 
# only use NOTE that headers are not needed for the build) and  PUBLIC (necessary of build and use). This control is 
# not possible in the add_library(...) macro
if(MSVC)
        add_library(${MC_LIBRARY} STATIC)
else()
        add_library(${MC_LIBRARY} SHARED)
endif()
target_sources(${MC_LIBRARY}
                PRIVATE ${MC_LIB_SRC}
                INTERFACE ${MC_LIB_HDR}) # Header not required for build, therefore 

target_link_libraries(${MC_LIBRARY} 
                      debug ${QUANTLIB_DIR}/debug/lib/QuantLib-vc141-x64-mt-gd.lib
                      optimized ${QUANTLIB_DIR}/lib/QuantLib-vc141-x64-mt.lib)
