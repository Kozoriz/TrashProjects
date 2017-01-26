set(TEST_TARGET SensorAdapterImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/sensor_adapter/include
	)
	file(GLOB SOURCES *.cc)


	set(LIBRARIES
		SensorAdapter
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
