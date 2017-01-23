set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

include_directories(
    include
    ${UTILS_INCLUDE_PATH}
    )

add_subdirectory(server_message_handler)
add_subdirectory(scanner)
add_subdirectory(mover)
add_subdirectory(sensor_adapter)
add_subdirectory(servo_adapter)
add_subdirectory(engine_adapter)
add_subdirectory(axelerometer_adapter)
