#####################################
# Define Target Information
#####################################

set(TARGET_NAME kotiki-engine)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES
    ${TARGET_SOURCE_DIR}/main.cpp
)

#####################################
# Define Target
#####################################

add_executable(${TARGET_NAME} ${SRC_FILES})

target_include_directories(
    ${TARGET_NAME}
    SYSTEM
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)