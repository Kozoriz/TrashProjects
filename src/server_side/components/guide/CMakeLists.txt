INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("Guide" ${SOURCES})
target_link_libraries("Guide" ${LIBRARIES})
