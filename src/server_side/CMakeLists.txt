
set(APP_MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app_main)

add_subdirectory(components)

set(ServerExecutable ${PROJECT}_Server)

include_directories(
  ${APP_MAIN_DIR}/include
  ${UTILS_INCLUDE_PATH}
  ${COMPONENTS_DIR}/include
  ${COMPONENTS_DIR}/drone_message_handler/include
  ${COMPONENTS_DIR}/drone_mover/include
  ${COMPONENTS_DIR}/guide/include
  ${COMPONENTS_DIR}/map_assembler/include
  ${COMPONENTS_DIR}/map_detalization_analyzer/include
  ${COMPONENTS_DIR}/snapshot_processor/include
)

file(GLOB SOURCES ${APP_MAIN_DIR}/src/*)

set(LIBRARIES
    Utils
    DroneMessageHandler
    DroneMover
    Guide
    MapAssembler
    MapDetalizationAnalyzer
    SnapshotProcessor
)

add_executable(${ServerExecutable} ${SOURCES})
target_link_libraries (${ServerExecutable} ${LIBRARIES})

if(BUILD_TESTS)
    set(UNIT_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests)
    add_subdirectory(${UNIT_TESTS_DIR})
endif()


set(INSTAL_FILES
log4cplus.properties
enviroment_scanner_server.ini
)

file(COPY ${INSTAL_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${ServerExecutable} DESTINATION ${INSTALL_DIR}/bin/server_side)
install(FILES ${INSTAL_FILES} DESTINATION ${INSTALL_DIR}/bin/server_side)
