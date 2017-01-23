INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("Scanner" ${SOURCES})
target_link_libraries("Scanner" ${LIBRARIES})
