cmake_minimum_required(VERSION 3.28)
project(mmioDocs LANGUAGES NONE)

get_filename_component(MMIO_DOCS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/docs" ABSOLUTE)
get_filename_component(MMIO_SITE_DIR "${CMAKE_CURRENT_BINARY_DIR}/site" ABSOLUTE)
get_filename_component(MMIO_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include" ABSOLUTE)
get_filename_component(MMIO_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
get_filename_component(MMIO_DOCS_TEMPLATES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/templates" ABSOLUTE)
get_filename_component(MMIO_HOOKS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/hooks" ABSOLUTE)

find_package(Doxygen REQUIRED)
find_program(UV_EXECUTABLE NAMES uv REQUIRED)

configure_file(${CMAKE_CURRENT_LIST_DIR}/mkdocs.yml.in ${CMAKE_CURRENT_BINARY_DIR}/mkdocs.yml @ONLY)

if(DOXYGEN_FOUND)
    add_custom_target(
        generate_docs
        COMMAND "${UV_EXECUTABLE}" run --project "${CMAKE_CURRENT_SOURCE_DIR}" mkdocs build -f
                "${CMAKE_CURRENT_BINARY_DIR}/mkdocs.yml"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with MkDocs..."
        VERBATIM
    )
endif()
