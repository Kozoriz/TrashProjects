INCLUDE_DIRECTORIES(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    GoogleTest
    )

add_library("ServerMessageHandler" ${SOURCES})
target_link_libraries("ServerMessageHandler" ${LIBRARIES})
