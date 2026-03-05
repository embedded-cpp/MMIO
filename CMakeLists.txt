cmake_minimum_required(VERSION 3.28)

# ---- Project ----
project(
    mmio
    VERSION 1.0
    LANGUAGES CXX ASM
)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our targets installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")
# ---- Add source files ----

# ---- Create library ----
add_library(${PROJECT_NAME} INTERFACE)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# being a cross-platform targets, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} INTERFACE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Expose internal headers only for in-tree builds (not exported on install)
target_include_directories(
    ${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>
)

# ---- Create an installable targets ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
    NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
    VERSION_HEADER "${VERSION_HEADER_LOCATION}"
    COMPATIBILITY SameMajorVersion
)
