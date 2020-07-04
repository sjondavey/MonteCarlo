set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# https://pybind11.readthedocs.io/en/stable/compiling.html#pybind11-add-module
find_package(pybind11 CONFIG REQUIRED)

set(MC_PYTHON_SRC 
    mcPythonInterface.cpp
    )

#need my own libraries so don't use the pybind11_add_module(montecarlo ${MC_PYTHON_SRC}) approach, 
#do it manually: https://pybind11.readthedocs.io/en/stable/compiling.html#advanced-interface-library-target
add_library(montecarlo MODULE ${MC_PYTHON_SRC})
target_link_libraries(montecarlo PRIVATE pybind11::module ${PROJECT_NAME_STR}_lib)
set_target_properties(montecarlo PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                            SUFFIX "${PYTHON_MODULE_EXTENSION}")





