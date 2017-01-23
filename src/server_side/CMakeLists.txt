
add_subdirectory(components)

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
	add_subdirectory(unit_tests)
endif()
