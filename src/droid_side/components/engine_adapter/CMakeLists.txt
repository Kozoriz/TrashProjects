INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("EngineAdapter" ${SOURCES})
target_link_libraries("EngineAdapter" ${LIBRARIES})
