include_directories(
    ${GTEST_INCLUDE_DIR}
)

add_library("GoogleTest" googletest/gmock-gtest-all.cc)
target_link_libraries("GoogleTest" ${CMAKE_THREAD_LIBS_INIT})

