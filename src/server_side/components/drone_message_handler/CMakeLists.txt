INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("DroneMessageHandler" ${SOURCES})
target_link_libraries("DroneMessageHandler" ${LIBRARIES})
