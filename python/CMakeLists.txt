cmake_minimum_required(VERSION 3.16) # Helps to have this repeated in case you want this to be the root of seperate project

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# https://pybind11.readthedocs.io/en/stable/compiling.html#pybind11-add-module
find_package(pybind11 CONFIG REQUIRED)

set(MC_PYTHON_SRC 
    mcPythonInterface.cpp
    )

pybind11_add_module(montecarlo ${MC_PYTHON_SRC})
# The key is to keep the 'PRIVATE' setting in target_link_libraries(...). 'PRIVATE' indicates that we are setting the build 
# requirements between this <target> (montecarlo) and the dependency (our library file). For reference, usage requirements  
# use the keyword 'INTERFACE'. Both build and usage requirements are implied with the keyword 'PUBLIC'. You should not ommit
# one of these keywords, even though the macro allows you to do so - it may behave erratically
target_link_libraries(montecarlo PRIVATE ${PROJECT_NAME_STR}_lib)






