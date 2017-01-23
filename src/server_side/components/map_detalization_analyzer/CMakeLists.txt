INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("MapDetalizationAnalyzer" ${SOURCES})
target_link_libraries("MapDetalizationAnalyzer" ${LIBRARIES})
