# Project settings
# Reference: https://github.com/albertchan/cmake-boost-demo

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
set(MC_UNIT_TESTS ${PROJECT_NAME_STR}_unit_tests)

set(MC_LIB_TEST_SRC 
    test_main.cpp
    Black76FormulaTest.cpp
    )

add_executable(${MC_UNIT_TESTS} ${MC_LIB_TEST_SRC})

# Dependencies
add_definitions(-DBOOST_TEST_DYN_LINK)
find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)
if (Boost_FOUND)
  # ALREADY INCLUDED: include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(${MC_UNIT_TESTS} ${Boost_LIBRARIES})
else()
   MESSAGE("***BOOST not found")
endif()

target_link_libraries(${MC_UNIT_TESTS} ${PROJECT_NAME_STR}_lib)

enable_testing()
add_test(DemoTest ${MC_UNIT_TESTS})