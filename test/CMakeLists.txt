set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(MC_UNIT_TESTS ${PROJECT_NAME_STR}_tests)

set(MC_LIB_TEST_SRC 
    test_main.cpp
    Black76FormulaTest.cpp
    )

add_executable(${MC_UNIT_TESTS} ${MC_LIB_TEST_SRC})

target_link_libraries(${MC_UNIT_TESTS} ${PROJECT_NAME_STR}_lib)

enable_testing()
add_test(DemoTest ${MC_UNIT_TESTS})