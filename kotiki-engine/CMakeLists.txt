#####################################
# Define Target Information
#####################################

set(TARGET_NAME kotiki-engine)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES
    ${TARGET_SOURCE_DIR}/kotiki-engine/main.cpp
)

#####################################
# Define Target
#####################################

add_executable(${TARGET_NAME} ${SRC_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE Qt::Core Qt::Widgets Qt::Gui )

target_include_directories(
        ${TARGET_NAME}
        SYSTEM
        PUBLIC
        $<BUILD_INTERFACE:${TARGET_INCLUDE_DIR}>
)