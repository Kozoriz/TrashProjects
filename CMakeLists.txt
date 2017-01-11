cmake_minimum_required(VERSION 2.8)

set (PROJECT EnvironmentScanner)

option(BUILD_TESTS "Build Unit Tests" ON)

add_subdirectory(src/droid_side)
add_subdirectory(src/server_side)