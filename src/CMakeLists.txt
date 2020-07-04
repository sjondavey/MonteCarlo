set(MC_LIBRARY ${PROJECT_NAME_STR}_lib)


set(MC_LIB_HDR 
        formula/Black76Formula.h
        )


set(MC_LIB_SRC 
        formula/Black76Formula.cpp
        )

add_library(${MC_LIBRARY} STATIC ${MC_LIB_SRC})

target_compile_features(${MC_LIBRARY} PRIVATE cxx_std_11)