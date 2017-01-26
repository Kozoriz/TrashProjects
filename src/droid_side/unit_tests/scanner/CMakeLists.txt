set(TEST_TARGET ScannerImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/scanner/include
	)
	file(GLOB SOURCES *.cc)


	set(LIBRARIES
		Scanner
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
