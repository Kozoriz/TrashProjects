INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("MapAssembler" ${SOURCES})
target_link_libraries("MapAssembler" ${LIBRARIES})
