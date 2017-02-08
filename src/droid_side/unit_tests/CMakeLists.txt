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

add_subdirectory(server_message_handler)
add_subdirectory(scanner)
add_subdirectory(mover)
add_subdirectory(sensor_adapter)
add_subdirectory(servo_adapter)
add_subdirectory(engine_adapter)
add_subdirectory(axelerometer_adapter)
