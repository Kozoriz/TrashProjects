
add_subdirectory(components)

set(ClientExecutable ${PROJECT}_Client)


include_directories(
${UTILS_INCLUDE_PATH}
${COMPONENTS_DIR}/include
${COMPONENTS_DIR}/axelerometer_adapter/include
${COMPONENTS_DIR}/sensor_adapter/include
${COMPONENTS_DIR}/servo_adapter/include
${COMPONENTS_DIR}/scanner/include
${COMPONENTS_DIR}/mover/include
${COMPONENTS_DIR}/engine_adapter/include
${COMPONENTS_DIR}/server_message_handler/include
)

set(SOURCES
	main.cc
        life_cycle.cc
)

set(LIBRARIES
    Utils
    EngineAdapter
    Mover
    Scanner
    SensorAdapter
    ServerMessageHandler
    ServoAdapter
    AxelerometerAdapter
)

add_executable(${ClientExecutable} ${SOURCES})
target_link_libraries (${ClientExecutable} ${LIBRARIES})

if(BUILD_TESTS)
    set(UNIT_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests)
    add_subdirectory(${UNIT_TESTS_DIR})
endif()


set(INSTAL_FILES
log4cplus.properties
enviroment_scanner_client.ini
)

file(COPY ${INSTAL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${ClientExecutable} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
install(FILES ${INSTAL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
