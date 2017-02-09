

include_directories(
${3RD_PARTY_PATH}
include
${GTEST_INCLUDE_DIR}
)
file(GLOB SOURCES 
	src/*.cc 
	src/*/*.cc 
	src/*/*/*.cc)

set(LIBRARIES

)

add_library("Utils" ${SOURCES})
target_link_libraries("Utils" ${LIBRARIES})
