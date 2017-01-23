INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("SensorAdapter" ${SOURCES})
target_link_libraries("SensorAdapter" ${LIBRARIES})
