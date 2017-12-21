set(TEST_TARGET MoverImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/mover/include
	)
	file(GLOB SOURCES *.cc)


	set(LIBRARIES
		Mover
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
