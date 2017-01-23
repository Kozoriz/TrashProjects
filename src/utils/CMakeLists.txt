

include_directories(
${3RD_PARTY_PATH}
include
)
file(GLOB SOURCES src/*.cc src/threads/*.cc src/synchronization/*.cc)

set(LIBRARIES

)

add_library("Utils" ${SOURCES})
target_link_libraries("Utils" ${LIBRARIES})
