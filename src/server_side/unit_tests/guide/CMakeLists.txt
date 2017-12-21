set(TEST_TARGET GuideImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/guide/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		Guide
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
