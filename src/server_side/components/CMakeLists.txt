set(COMPONENTS_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

include_directories(
    include
    ${UTILS_INCLUDE_PATH}
    )

add_subdirectory(drone_message_handler)
add_subdirectory(drone_mover)
add_subdirectory(guide)
add_subdirectory(map_assembler)
add_subdirectory(map_detalization_analyzer)
add_subdirectory(snapshot_processor)
