set(TEST_TARGET AxelerometerAdapterImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/axelerometer_adapter/include
	)
	file(GLOB SOURCES *.cc)



	set(LIBRARIES
		AxelerometerAdapter
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
