cmake_minimum_required(VERSION 3.16)

#================================#
#  Global Configuration          #
#================================#
set(PROJECT_NAME_STR monte_carlo_derivatives)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project title and define versioning
project(${PROJECT_NAME_STR} 
        VERSION 0.1.0
        DESCRIPTION "Monte Carlo simulation of derivatives"
        LANGUAGES CXX)

# From: https://cmake.org/cmake/help/git-master/module/FindBoost.html
# set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
find_package(Boost)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  # DO I NEED BOOST LIBRARIES? target_link_libraries(${MC_LIBRARY} ${Boost_LIBRARIES})
else()
   MESSAGE("BOOST not found")
endif()


# Find other CMakeList.txt 
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(app)
add_subdirectory(python)


# Notes:
# Good Overall refernces for CMake projects:
# https://stackoverflow.com/questions/40227333/cmake-setup-multiple-projects-and-dependiencies-between-them/40242257#40242257

# include_directories vs. target_include_directories (https://stackoverflow.com/questions/31969547/what-is-the-difference-between-include-directories-and-target-include-directorie)
# include_directories(x/y): accessible for all the files in the source-tree
# target_include_directories(t x/y): accessible for a specific target when compile