enable_testing()

#####################################
# Test executable
#####################################

add_executable(unit-tests
    main.cpp
    test-test.cpp
)

target_include_directories(unit-tests SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(unit-tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit-tests)