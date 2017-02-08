set(TEST_MAIN_CC ${UNIT_TESTS_DIR}/test_main.cc)

macro(create_test NAME SOURCES LIBS)
    add_executable("${NAME}" ${TEST_MAIN_CC} ${SOURCES})
    target_link_libraries("${NAME}" ${LIBS})
    target_link_libraries("${NAME}" GoogleTest)

    add_test(NAME ${NAME} COMMAND ${NAME} --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/)
endmacro(create_test)

include_directories(
    include
    ${UTILS_MOCK_INCLUDE_PATH}
    )

add_subdirectory(drone_message_handler)
add_subdirectory(drone_mover)
add_subdirectory(guide)
add_subdirectory(map_assembler)
add_subdirectory(map_detalization_analyzer)
add_subdirectory(snapshot_processor)
