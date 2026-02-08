get_filename_component(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
list(APPEND CMAKE_MESSAGE_INDENT " | ")
message("${DIR_NAME}")

add_subdirectory(peripherals)

# Flags MCU GCC - target INTERFACE
add_library(stm32f401_flags INTERFACE)

target_compile_options(
    stm32f401_flags
    INTERFACE -mcpu=cortex-m4
              -mfpu=fpv4-sp-d16
              -mfloat-abi=hard
              -Wall
              -Wextra
              -Wshadow
              -Wcast-align
              -Wpedantic
              -Wunused
              -Wconversion
              -Wsign-conversion
              -Wmisleading-indentation
              -Wduplicated-cond
              -Wduplicated-branches
              -Wlogical-op
              -Wnull-dereference
              -Wdouble-promotion
              -Wformat=2
              -fdata-sections
              -ffunction-sections
)

target_compile_options(
    stm32f401_flags
    INTERFACE $<$<COMPILE_LANGUAGE:CXX>:
              -fno-rtti
              -fno-exceptions
              -fno-threadsafe-statics
              -fno-use-cxa-atexit
              -Wnon-virtual-dtor
              -Wold-style-cast
              -Woverloaded-virtual
              -Wuseless-cast>
)

target_compile_options(stm32f401_flags INTERFACE $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>)

target_link_options(
    stm32f401_flags
    INTERFACE
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    -T
    "${CMAKE_CURRENT_SOURCE_DIR}/linker_script.ld"
    --specs=nano.specs
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--cref
    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
    -Wl,--print-memory-usage
    -flto
)
