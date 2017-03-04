include_directories(
    ${GTEST_INCLUDE_DIR}
)

if (BUILD_TESTS)
  add_library("GoogleTest" googletest/gmock-gtest-all.cc)
  target_link_libraries("GoogleTest" ${CMAKE_THREAD_LIBS_INIT})
endif(BUILD_TESTS)
