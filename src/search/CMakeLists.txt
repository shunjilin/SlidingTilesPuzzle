add_subdirectory(memory_pool)

# search interface

add_library(search INTERFACE)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# concurrent search interface

add_library(concurrent_search INTERFACE)

target_include_directories(concurrent_search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# astar

add_library(astar INTERFACE)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  INTERFACE open_array
  INTERFACE closed_chaining
  )

target_compile_features(astar INTERFACE cxx_std_11)

# astar (memory pool)

add_library(astar_pool INTERFACE)

target_include_directories(astar_pool
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar_pool
  INTERFACE MemoryPool
  INTERFACE open_array_ptr
  INTERFACE closed_open_address_ptr
  )

target_compile_features(astar_pool INTERFACE cxx_std_11)

# astar multicore

add_library(astar_multicore INTERFACE)

target_include_directories(astar_multicore
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar_multicore
  INTERFACE concurrent_search
  INTERFACE concurrent_open_array
  INTERFACE concurrent_closed_chaining
  INTERFACE pthread
  )

target_compile_features(astar_multicore INTERFACE cxx_std_11)

# astar multicore pool

add_library(astar_multicore_pool INTERFACE)

target_include_directories(astar_multicore_pool
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar_multicore_pool
  INTERFACE concurrent_search
  INTERFACE MemoryPool
  INTERFACE open_array_ptr
  INTERFACE closed_open_address_ptr
  INTERFACE pthread
  )

target_compile_features(astar_multicore_pool INTERFACE cxx_std_11)
