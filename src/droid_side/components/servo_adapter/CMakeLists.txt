INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("ServoAdapter" ${SOURCES})
target_link_libraries("ServoAdapter" ${LIBRARIES})
