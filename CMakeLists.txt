cmake_minimum_required(VERSION 3.16)

# Definitions
set(PROJECT_NAME_STR monte_carlo_derivatives)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
# "I want C++11 for all targets, I dont't want to use any GNU or MS extensions." As of c++17, this still is IMHO the best way
# set(CMAKE_CXX_STANDARD 11)

# Project title and define versioning
project(${PROJECT_NAME_STR} 
        VERSION 0.1.0
        DESCRIPTION "Monte Carlo simulation of derivatives"
        LANGUAGES CXX)

set(DEMO_INCLUDES ${DEMO_INCLUDES} ${PROJECT_SOURCE_DIR}/src)
set(DEMO_INCLUDES ${DEMO_INCLUDES} ${PROJECT_SOURCE_DIR}/shared)

# Gather the header and source files
#file(GLOB_RECURSE INC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
#file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Gather all sources except the main entry point
file(GLOB_RECURSE INC_FILES src/*/*.hpp)
file(GLOB_RECURSE SRC_FILES src/*/*.cpp)

# Build object files for reuse (e.g. in test)
# ADD_LIBRARY(demo_objects OBJECT ${INC_FILES} ${SRC_FILES})

# Dependencies
find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

# Unit tests
add_subdirectory(test)

# Assign the include directories
include_directories(${Boost_INCLUDE_DIRS})

# Build
#set(SOURCE_FILES src/main.cpp $<TARGET_OBJECTS:demo_objects>)
set(SOURCE_FILES src/main.cpp ${INC_FILES} ${SRC_FILES})
add_executable(monte_carlo_demo ${SOURCE_FILES})
target_link_libraries(monte_carlo_demo ${Boost_LIBRARIES})



#include(CTest)
#enable_testing()

#add_library(MonteCarlo MonteCarlo.cpp)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
