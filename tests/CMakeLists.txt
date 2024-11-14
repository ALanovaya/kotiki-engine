enable_testing()

#####################################
# Define Target Information
#####################################
set(TARGET_NAME unit-tests)

set(KOTIKI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/include)
set(KOTIKI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/src)

set(PROJECT_SRC_FILES
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/algorithms/naive.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/metrics/euclidean.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/movers/random_mover.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/utils/random.cpp
)

set(TESTS_SRC_FILES
    main.cpp
    test-test.cpp
    test_algorithm.cpp
)

#####################################
# Test executable
#####################################

add_executable(unit-tests
    ${PROJECT_SRC_FILES}
    ${TESTS_SRC_FILES}
)


target_include_directories(
        ${TARGET_NAME}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${KOTIKI_INCLUDE_DIR}>
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(unit-tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit-tests)