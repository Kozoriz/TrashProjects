INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("Mover" ${SOURCES})
target_link_libraries("Mover" ${LIBRARIES})
