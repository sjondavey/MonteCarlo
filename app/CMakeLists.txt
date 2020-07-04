# Definitions
set(MC_DEMO ${PROJECT_NAME_STR}_demo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(MC_DEMO_SRC 
    main.cpp
    )
    
add_executable(${MC_DEMO} ${MC_DEMO_SRC})

target_link_libraries(${MC_DEMO} ${PROJECT_NAME_STR}_lib)

