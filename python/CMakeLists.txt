set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# https://pybind11.readthedocs.io/en/stable/compiling.html#pybind11-add-module
find_package(pybind11 CONFIG REQUIRED)

set(MC_PYTHON_SRC 
    mcPythonInterface.cpp
    )

#the key here is to keep the 'PRIVATE' command in target_ling_libraries
pybind11_add_module(montecarlo ${MC_PYTHON_SRC})
target_link_libraries(montecarlo PRIVATE ${PROJECT_NAME_STR}_lib)






