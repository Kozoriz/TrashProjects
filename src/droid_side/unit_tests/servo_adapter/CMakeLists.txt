set(TEST_TARGET ServoAdapterImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/servo_adapter/include
	)
	file(GLOB SOURCES *.cc)


	set(LIBRARIES
		ServoAdapter
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
