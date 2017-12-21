set(TEST_TARGET MapAssemblerImplTest)
	include_directories(
		${GTEST_INCLUDE_DIR}
		include
		${COMPONENTS_DIR}/map_assembler/include
	)
	file(GLOB SOURCES *.cc)
	set(LIBRARIES
		MapAssembler
	)

        create_test(${TEST_TARGET} ${SOURCES} ${LIBRARIES})

	
