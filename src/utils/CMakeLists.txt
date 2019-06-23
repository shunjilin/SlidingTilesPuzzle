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

# spinlock

add_library(spinlock INTERFACE)

target_include_directories(spinlock
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# util

add_library(util INTERFACE)

target_include_directories(util
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
