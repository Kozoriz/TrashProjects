INCLUDE_DIRECTORIES(
    include
    ${COMPONENTS_DIR}/snapshot_processor/include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("MapDetalizationAnalyzer" ${SOURCES})
target_link_libraries("MapDetalizationAnalyzer" ${LIBRARIES})
