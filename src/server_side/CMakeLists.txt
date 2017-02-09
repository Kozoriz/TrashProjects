
add_subdirectory(components)

include_directories(
    components/include
    ${UTILS_INCLUDE_PATH}
    )

set(ClientExecutable ${PROJECT}_Server)

set(SOURCES
	main.cc
)

set(LIBRARIES
    DroneMessageHandler
    DroneMover
    Guide
    MapAssembler
    MapDetalizationAnalyzer
    SnapshotProcessor
)

add_executable(${ClientExecutable} ${SOURCES})
target_link_libraries (${ClientExecutable} ${LIBRARIES})

if(BUILD_TESTS)
        set(UNIT_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests)
        add_subdirectory(${UNIT_TESTS_DIR})
endif()
