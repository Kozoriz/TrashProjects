set(TEST_TARGET SnapshotProcessorImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/snapshot_processor/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		SnapshotProcessor
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
