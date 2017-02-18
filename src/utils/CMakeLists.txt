set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.62 COMPONENTS system)

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
    ${Boost_LIBRARIES}
)

if(ENABLE_LOG)
  list(APPEND LIBRARIES log4cplus -L${LOG4CPLUS_LIB_DIR})
endif()

add_library("Utils" ${SOURCES})
target_link_libraries("Utils" ${LIBRARIES})

