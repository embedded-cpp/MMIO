cmake_minimum_required(VERSION 3.9...3.31)

project(mmioDocs)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:jothepro/doxygen-awesome-css#v2.4.1")
CPMAddPackage(NAME mmio SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Doxygen variables ----
set(AWESOME_CSS_DIR "${doxygen-awesome-css_SOURCE_DIR}")

# set Doxyfile variables
set(DOXYGEN_PROJECT_NAME mmio)
set(DOXYGEN_PROJECT_VERSION ${mmio_VERSION})
set(DOXYGEN_PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
set(DOXYGEN_HTML_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/header.html")

configure_file(${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

find_package(Doxygen REQUIRED)
add_custom_target(
    GenerateDocs
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMAND echo "Docs written to: ${DOXYGEN_OUTPUT_DIRECTORY}/html/index.html"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)