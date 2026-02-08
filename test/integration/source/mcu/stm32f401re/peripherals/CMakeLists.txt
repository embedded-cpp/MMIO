get_filename_component(DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
list(APPEND CMAKE_MESSAGE_INDENT " | ")
message("${DIR_NAME}")

add_library(peripherals INTERFACE)

target_include_directories(peripherals INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(peripherals INTERFACE mmio)
