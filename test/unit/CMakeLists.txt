cmake_minimum_required(VERSION 3.28)
project(mmioTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../../cmake/tools.cmake)

# ---- Dependencies ----

include(../../cmake/CPM.cmake)

CPMAddPackage("gh:doctest/doctest@2.4.12")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")
CPMAddPackage(NAME mmio SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest mmio)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        target_compile_options(mmio INTERFACE -Wall -Wpedantic -Wextra -Werror)
    elseif(MSVC)
        target_compile_options(mmio INTERFACE /W4 /WX)
        target_compile_definitions(${PROJECT_NAME} PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
    endif()
endif()

# ---- Add mmioTests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests. For other testing frameworks add
# the tests targets instead: add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
    find_program(GCOV_EXECUTABLE gcov REQUIRED)

    configure_file(gcovr.cfg.in gcovr.cfg @ONLY)

    add_custom_target(
        coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running gcovr to process coverage results"
        COMMAND gcovr --config ${CMAKE_CURRENT_BINARY_DIR}/gcovr.cfg .
    )

    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE -O0
                -g
                --coverage
                -fno-inline
                -fno-inline-small-functions
                -fno-default-inline
                -fkeep-inline-functions
    )
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE
        --coverage
        -fno-inline
        -fno-inline-small-functions
        -fno-default-inline
        -fkeep-inline-functions
    )
endif()

# ---- Analyse statique CodeChecker ----
# Usage : cmake --build <build_dir> --target codechecker Prérequis : - CodeChecker installé : pip install codechecker -
# cmake configuré avec -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

find_program(CODECHECKER_EXECUTABLE CodeChecker QUIET)

if(CODECHECKER_EXECUTABLE)
    # Racine du dépôt = 2 niveaux au-dessus de test/unit/
    get_filename_component(REPO_ROOT "${CMAKE_SOURCE_DIR}/../.." ABSOLUTE)

    add_custom_target(
        codechecker
        # Create output directory for CodeChecker reports
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/codechecker/reports
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/codechecker/reports/html
        # Analyze everything (Without --ignore to have all TUs analyzed, including headers in include/mmio/)
        COMMAND ${CODECHECKER_EXECUTABLE} analyze ${CMAKE_BINARY_DIR}/compile_commands.json --output
                ${CMAKE_BINARY_DIR}/codechecker/reports --enable-all --jobs 16 --clean
        # SARIF : Filtered results (only issues in include/mmio/**) --- IGNORE ---
        COMMAND ${CODECHECKER_EXECUTABLE} parse ${CMAKE_BINARY_DIR}/codechecker/reports --export sarif --output
                ${CMAKE_BINARY_DIR}/codechecker/results.sarif --ignore ${REPO_ROOT}/.codechecker/skip.list
        # HTML : Readable report for manual review (unfiltered to cover all TUs) --- IGNORE ---
        COMMAND ${CODECHECKER_EXECUTABLE} parse ${CMAKE_BINARY_DIR}/codechecker/reports --export html --output
                ${CMAKE_BINARY_DIR}/codechecker/html --ignore ${REPO_ROOT}/.codechecker/skip.list
        COMMAND ${CMAKE_COMMAND} -E echo "Rapport HTML : ${CMAKE_BINARY_DIR}/codechecker/html/index.html"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "CodeChecker analysis..."
        VERBATIM
    )

    message(STATUS "CodeChecker trouvé : ${CODECHECKER_EXECUTABLE}")
    message(STATUS "  Cible disponible : cmake --build <build_dir> --target codechecker")
    message(STATUS "  Rappel           : configurer avec -DCMAKE_EXPORT_COMPILE_COMMANDS=ON")
else()
    message(STATUS "CodeChecker non trouvé - cible 'codechecker' indisponible")
    message(STATUS "  Installer avec : pip install codechecker")
endif()
