cmake_minimum_required(VERSION 3.10.2)

#####################################
# Define Target Information
#####################################

set(TARGET_NAME kotiki-engine)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES
    ${TARGET_SOURCE_DIR}/kotiki-engine/main.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/graphics/fps_counter.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/graphics/view.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/trajectory/trajectory.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/naive.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/grid_lookup.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/metrics/minkowski.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/metrics/chebyshev.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/algorithms/grid_lookup.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/random_mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/core/movers/trajectory_mover.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/utils/random.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/entities/scene_manager.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/graphics/palette.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/graphics/settings.cpp
    ${TARGET_SOURCE_DIR}/kotiki-engine/graphics/main_window.cpp
)

set(INCLUDE_FILES
    ${TARGET_INCLUDE_DIR}/kotiki-engine/graphics/fps_counter.hpp
    ${TARGET_INCLUDE_DIR}/kotiki-engine/graphics/view.hpp
    ${TARGET_INCLUDE_DIR}/kotiki-engine/graphics/palette.hpp
    ${TARGET_INCLUDE_DIR}/kotiki-engine/graphics/settings.hpp
    ${TARGET_INCLUDE_DIR}/kotiki-engine/graphics/main_window.hpp
)

#####################################
# Define Target
#####################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

add_executable(${TARGET_NAME} ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui )

target_include_directories(
        ${TARGET_NAME}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${TARGET_INCLUDE_DIR}>
)

target_link_libraries(${TARGET_NAME} PRIVATE matheval::x3)