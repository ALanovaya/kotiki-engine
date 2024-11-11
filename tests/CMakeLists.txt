enable_testing()

#####################################
# Define Target Information
#####################################
set(TARGET_NAME unit-tests)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/include)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/src)

set(PROJECT_SRC_FILES
    
)

set(TESTS_SRC_FILES
    main.cpp
    test-test.cpp
)

#####################################
# Test executable
#####################################

add_executable(unit-tests
    ${PROJECT_SRC_FILES}
    ${TESTS_SRC_FILES}
)


target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(
        ${TARGET_NAME}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
)

target_link_libraries(unit-tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit-tests)