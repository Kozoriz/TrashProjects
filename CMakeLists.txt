cmake_minimum_required(VERSION 2.8)

set (PROJECT EnvironmentScanner)

find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_TESTS "Build Unit Tests" ON)
option(AXELEROMETER_INCLUDED "If axelerometer connected to drone" OFF)
option(ENABLE_LOG "If logging needed" ON)

if (ENABLE_LOG)
  if (EXISTS "$ENV{LOG4CPLUS_DIRECTORY}/lib/liblog4cplus.a")
    add_definitions(-DENABLE_LOG)
    set(LOG4CPLUS_INCLUDE_DIR "$ENV{LOG4CPLUS_DIRECTORY}include")
    set(LOG4CPLUS_LIB_DIR "$ENV{LOG4CPLUS_DIRECTORY}lib")
    include_directories ( ${LOG4CPLUS_INCLUDE_DIR} )
  else()
    message(FATAL_ERROR " LOG4CPLUS is not present. Please install log4cplus logger ver. >= 2.0.0!")
  endif()
endif(ENABLE_LOG)

set(3RD_PARTY_PATH ${CMAKE_SOURCE_DIR}/src/3rd_party)
set(UTILS_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src/utils/include)
set(UTILS_MOCK_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src/utils/unit_tests/include)

if(BUILD_TESTS)
    add_definitions(-DBUILD_TESTS)
    set(GTEST_INCLUDE_DIR ${3RD_PARTY_PATH}/googletest)
    include_directories(
        ${GTEST_INCLUDE_DIR}
    )
    enable_testing()
endif()

add_subdirectory(src/3rd_party)
add_subdirectory(src/utils)
add_subdirectory(src/droid_side)
add_subdirectory(src/server_side)
