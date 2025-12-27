cmake_minimum_required(VERSION 3.9...3.31)

# ---- Project ----
project(
  mmio
  VERSION 1.0
  LANGUAGES CXX
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

# ---- Add source files ----

# ---- Create library ----
add_library(mmio INTERFACE)
set_target_properties(mmio PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(mmio INTERFACE "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Expose internal headers only for in-tree builds (not exported on install)
target_include_directories(mmio INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
