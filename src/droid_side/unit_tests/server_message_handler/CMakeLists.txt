set(TEST_TARGET ServerMessageHandlerImplTest)

include_directories(
        ${GTEST_INCLUDE_DIR}
        include
        ${COMPONENTS_DIR}/server_message_handler/include
)
file(GLOB SOURCES *.cc)
set(LIBRARIES
        ServerMessageHandler
)

create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
