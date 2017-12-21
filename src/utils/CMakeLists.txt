set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.62 COMPONENTS program_options system thread)

if (EDISON_BUILD)
  set(Boost_LIBRARIES
    /opt/poky-edison/1.7.3/sysroots/core2-32-poky-linux/usr/lib/libboost_program_options.so
    /opt/poky-edison/1.7.3/sysroots/core2-32-poky-linux/usr/lib/libboost_system.so
    /opt/poky-edison/1.7.3/sysroots/core2-32-poky-linux/usr/lib/libboost_thread.so
    )
endif()

include_directories(
  ${3RD_PARTY_PATH}
  include
  ${GTEST_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
)
set(BOOST_INCLUDE ${Boost_INCLUDE_DIR} PARENT_SCOPE)
set(BOOST_LIBS ${Boost_LIBRARIES} PARENT_SCOPE)

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

