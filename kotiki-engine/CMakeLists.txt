#####################################
# Define Target Information
#####################################

set(TARGET_NAME kotiki-engine)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES
    ${TARGET_SOURCE_DIR}/kotiki-engine/main.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/trajectory/trajectory.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/naive.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/metrics/euclidean.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/random_mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/trajectory_mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/utils/random.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/entities/entities_collection.cpp

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

target_link_libraries(${TARGET_NAME} PRIVATE matheval::x3)