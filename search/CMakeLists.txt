add_subdirectory(tiles)
add_subdirectory(open)
add_subdirectory(closed)
add_subdirectory(memory_pool)

# search interface

add_library(search INTERFACE)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# astar

add_library(astar INTERFACE)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  INTERFACE open_array
  INTERFACE closed_open_address
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
