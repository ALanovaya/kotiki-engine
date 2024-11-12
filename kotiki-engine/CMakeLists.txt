#####################################
# Define Target Information
#####################################

set(TARGET_NAME kotiki-engine)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES
    ${TARGET_SOURCE_DIR}/kotiki-engine/main.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/naive.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/grid_lookup.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/metrics/euclidean.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/random_mover.cpp
)

#####################################
# Define Target
#####################################

add_executable(${TARGET_NAME} ${SRC_FILES})

target_include_directories(
        ${TARGET_NAME}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${TARGET_INCLUDE_DIR}>
)