set(TEST_TARGET EngineAdapterImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/engine_adapter/include
	)
	file(GLOB SOURCES *.cc)


	set(LIBRARIES
		EngineAdapter
	)

    create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
