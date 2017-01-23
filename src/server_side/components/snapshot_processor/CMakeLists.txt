INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("SnapshotProcessor" ${SOURCES})
target_link_libraries("SnapshotProcessor" ${LIBRARIES})
