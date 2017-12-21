set(TEST_TARGET DroneMessageHandlerImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/drone_message_handler/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		DroneMessageHandler
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
