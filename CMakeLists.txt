cmake_minimum_required(VERSION 3.10.0)
project(kotiki-engine VERSION 0.1.0 LANGUAGES CXX C DESCRIPTION "Kotiki real-time simulation")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No CMAKE_BUILD_TYPE specified, default to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(BUILD_TESTS "Build C++ unit-tests" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(kotiki-engine)
add_subdirectory(external)

if (${BUILD_TESTS}) 
    add_subdirectory(tests)
endif()