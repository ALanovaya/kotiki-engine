enable_testing()

#####################################
# Define Target Information
#####################################
set(TARGET_NAME unit-tests)

set(KOTIKI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/include)
set(KOTIKI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/kotiki-engine/src)

set(PROJECT_SRC_FILES
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/trajectory/trajectory.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/algorithms/algorithm.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/algorithms/grid_lookup.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/algorithms/naive.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/metrics/minkowski.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/metrics/chebyshev.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/movers/mover.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/core/movers/random_mover.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/utils/random.cpp
    ${KOTIKI_SOURCE_DIR}/kotiki-engine/entities/scene_manager.cpp
)

set(TESTS_SRC_FILES
    main.cpp
    test-test.cpp
    test-trajectory.cpp
    test_algorithm.cpp
    test_entities.cpp
    test_metrics.cpp
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
target_link_libraries(unit-tests PRIVATE matheval::x3)

#####################################
# Run unit tests
#####################################

add_custom_target(run-unit-tests
    COMMAND unit-tests
    DEPENDS unit-tests
)

include(GoogleTest)
gtest_discover_tests(unit-tests)
