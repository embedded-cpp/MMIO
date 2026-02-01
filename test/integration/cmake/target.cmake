function(mcu_add_executable)
  add_executable(${ARGV})
  target_link_libraries(${ARGV0} PRIVATE stm32f401_flags)
endfunction()

function(mcu_add_library)
  add_library(${ARGV})
  target_link_libraries(${ARGV0} PRIVATE stm32f401_flags)
endfunction()
