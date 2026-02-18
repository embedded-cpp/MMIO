cmake_minimum_required(VERSION 3.9...3.31)
project(mmioTestsMcu LANGUAGES CXX ASM)

# ---- Options ----

option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)
set(MCU_NAME ${MCU_NAME})
string(TOLOWER ${MCU_NAME} MCU_NAME)

# --- Import tools ----
include(cmake/target.cmake)
include(../../cmake/tools.cmake)

# ---- Dependencies ----

include(../../cmake/CPM.cmake)

CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")
CPMAddPackage(NAME mmio SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

message(${PROJECT_NAME})

# ---- Board ----
add_subdirectory(source/mcu/${MCU_NAME})

# ---- Create binary ----

mcu_add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/mcu/${MCU_NAME}/startup.s)
target_link_libraries(${PROJECT_NAME} PRIVATE peripherals)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
    target_compile_options(mmio INTERFACE -Wall -Wpedantic -Wextra -Werror)
endif()
