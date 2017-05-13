cmake_minimum_required(VERSION 2.8)

set (PROJECT EnvironmentScanner)

### FLAGS/PACKAGES
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

### OPTIONS
option(BUILD_TESTS "Build Unit Tests" ON)
option(AXELEROMETER_INCLUDED "If axelerometer connected to drone" OFF)
option(ENABLE_LOG "If logging needed" ON)
option(DEBUG_OPTION "Debug/Release" ON)
option(EDISON_BUILD "Build Client for i568 platform" OFF)

if (EDISON_BUILD)
  #This is where all the settings to compile for the Edison are stored.
  INCLUDE(${CMAKE_SOURCE_DIR}/Edison.cmake)
  set(BUILD_TESTS false)
endif()


if (DEBUG_OPTION)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
  add_definitions(-DDEBUG)
else()
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif(DEBUG_OPTION)


### LOGGER
if (ENABLE_LOG)
  if (EXISTS "$ENV{LOG4CPLUS_DIRECTORY}/lib/liblog4cplus.a")
    set(LOGGER_HOME $ENV{LOG4CPLUS_DIRECTORY})
    if (EDISON_BUILD)
      set(LOGGER_HOME "$ENV{LOG4CPLUS_DIRECTORY}i586/")
    endif()
    add_definitions(-DENABLE_LOG)
    set(LOG4CPLUS_INCLUDE_DIR "${LOGGER_HOME}include")
    set(LOG4CPLUS_LIB_DIR "${LOGGER_HOME}lib")
    include_directories ( ${LOG4CPLUS_INCLUDE_DIR} )
  else()
    message(FATAL_ERROR " LOG4CPLUS is not present. Please install log4cplus logger ver. >= 2.0.0!")
  endif()
endif(ENABLE_LOG)


### VARIABLES
set(3RD_PARTY_PATH ${CMAKE_SOURCE_DIR}/src/3rd_party)
set(UTILS_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src/utils/include)
set(UTILS_MOCK_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src/utils/unit_tests/include)
set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR})


### TESTS
if(BUILD_TESTS)
    add_definitions(-DBUILD_TESTS)
    set(GTEST_INCLUDE_DIR ${3RD_PARTY_PATH}/googletest)
    include_directories(
        ${GTEST_INCLUDE_DIR}
    )
    enable_testing()
endif()


### MESSAGES
set(MESSAGES_INCLUDE_DIR src/messages/include)
include_directories(
${MESSAGES_INCLUDE_DIR}
) 


### SUBRIDECTORIES
add_subdirectory(src/3rd_party)
add_subdirectory(src/utils)
add_subdirectory(src/droid_side)
if(NOT EDISON_BUILD)
  add_subdirectory(src/server_side)
endif()
