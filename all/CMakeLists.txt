# this script adds all subprojects to a single build to allow IDEs understand the full project structure.

cmake_minimum_required(VERSION 3.9...3.31)

project(BuildAll LANGUAGES CXX)

include(../cmake/tools.cmake)

# needed to generate test targets
enable_testing()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../test/unit ${CMAKE_BINARY_DIR}/test/unit)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../documentation ${CMAKE_BINARY_DIR}/documentation)
