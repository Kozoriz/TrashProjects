set(TEST_TARGET MapDetalizationAnalyzerImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/map_detalization_analyzer/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		MapDetalizationAnalyzer
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
