cmake_minimum_required(VERSION 3.16)

include (${CMAKE_CURRENT_LIST_DIR}/project-meta-info.in)

#================================#
#  Global Configuration          #
#================================#
set(PROJECT_NAME_STR monte_carlo_derivatives)
project(${PROJECT_NAME_STR} 
        VERSION ${project_version}    # from project-meta-info.in
        DESCRIPTION ${project_description}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#https://www.youtube.com/watch?v=y9kSr5enrSk


# Boost: Get all the stuff you need once, don't load different packages in the sub-projects individual CMakeLists.txt
set(BOOST_VERSION 1.73.0) #
# From: https://cmake.org/cmake/help/git-master/module/FindBoost.html
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
# For some reason I cannot get find_package(...) to work in CONFIG mode with vcpkg. I am able to get the default modelue mode
# to work so I'm sticking with that
find_package(Boost ${BOOST_VERSION} REQUIRED) # I'm using the header only math package so am not providing COMPONENTS here

if (Boost_FOUND)
  # if target is found, make it global scope
  # set_target_property(Boost::boost # Boost::boost for the header only libraries
  #                     PROPERTIES GLOBAL TRUE)   
  include_directories(${Boost_INCLUDE_DIRS})
else()
   MESSAGE("BOOST not found")
endif()

#quantlib library --------------------------------------------------------------------------------------------
add_library(quantlib STATIC IMPORTED)
add_library(quantlibDebug STATIC IMPORTED)

if(MSVC)
  set(QUANTLIB_DIR "E:/SD/Programming/C++/vcpkg/installed/x64-windows" CACHE PATH "The path to the quantlib directory")
  set(QL_OPTIMISED_LIB ${QUANTLIB_DIR}/lib/QuantLib-vc141-x64-mt.lib)
  SET(QL_DEBUG_LIB ${QUANTLIB_DIR}/debug/lib/QuantLib-vc141-x64-mt-gd.lib)
else()
  set(QUANTLIB_DIR "/usr/vcpkg/installed/x64-linux" CACHE PATH "The path to the quantlib directory")
  set(QL_OPTIMISED_LIB ${QUANTLIB_DIR}/lib/??.lib)
  SET(QL_DEBUG_LIB ${QUANTLIB_DIR}/debug/lib/??.lib)
endif()
include_directories(${QUANTLIB_DIR})
set_target_properties(quantlib PROPERTIES IMPORTED_LOCATION ${QL_OPTIMISED_LIB})
set_target_properties(quantlibDebug PROPERTIES IMPORTED_LOCATION ${QL_DEBUG_LIB})


# Find other CMakeList.txt 
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(python)

# Testing : see https://cliutils.gitlab.io/modern-cmake/chapters/testing.html
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

enable_testing()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()


# Notes:
# Good Overall refernces for CMake projects:
# https://stackoverflow.com/questions/40227333/cmake-setup-multiple-projects-and-dependiencies-between-them/40242257#40242257

# include_directories vs. target_include_directories (https://stackoverflow.com/questions/31969547/what-is-the-difference-between-include-directories-and-target-include-directorie)
# include_directories(x/y): accessible for all the files in the source-tree
# target_include_directories(t x/y): accessible for a specific target when compile