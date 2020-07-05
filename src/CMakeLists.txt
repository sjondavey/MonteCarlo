#include(GenerateExportHeader)
set(MC_LIBRARY ${PROJECT_NAME_STR}_lib)

set(MC_LIB_HDR 
        formula/Black76Formula.h
        )


set(MC_LIB_SRC 
        formula/Black76Formula.cpp
        )

if(MSVC)
        add_library(${MC_LIBRARY} STATIC ${MC_LIB_SRC})
else()
        add_library(${MC_LIBRARY} SHARED ${MC_LIB_SRC})
endif()
#GENERATE_EXPORT_HEADER(${MC_LIBRARY})

