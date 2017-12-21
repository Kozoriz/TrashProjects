include_directories(
    include
    )

file(GLOB SOURCES src/*.cc)

set(LIBRARIES
    Utils
    )

add_library("AxelerometerAdapter" ${SOURCES})
target_link_libraries("AxelerometerAdapter" ${LIBRARIES})
