cmake_minimum_required(VERSION 2.8)

set (PROJECT EnvironmentScanner)

find_package (Threads)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(BUILD_TESTS "Build Unit Tests" ON)
option(AXELEROMETER_INCLUDED "If axelerometer connected to drone" OFF)

set(3RD_PARTY_PATH ${CMAKE_SOURCE_DIR}/src/3rd_party)
set(UTILS_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src/utils/include)

if(BUILD_TESTS)
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
