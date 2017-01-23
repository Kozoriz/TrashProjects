INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("DroneMover" ${SOURCES})
target_link_libraries("DroneMover" ${LIBRARIES})
