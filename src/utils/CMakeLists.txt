# cxxopts

add_library(cxxopts INTERFACE)

target_include_directories(cxxopts
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# steady clock timer

add_library(steady_clock_timer INTERFACE)

target_include_directories(steady_clock_timer
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

