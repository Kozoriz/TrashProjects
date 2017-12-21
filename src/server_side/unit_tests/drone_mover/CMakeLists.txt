set(TEST_TARGET DroneMoverImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/drone_mover/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		DroneMover
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
