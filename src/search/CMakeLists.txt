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

# concurrent astar
find_package(Boost)

add_library(concurrent_astar INTERFACE)

target_include_directories(concurrent_astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  INTERFACE ${Boost_INCLUDE_DIRS}
  )

target_link_libraries(concurrent_astar
  INTERFACE concurrent_open_array
  INTERFACE concurrent_closed_open_address_pool
  INTERFACE pthread
  )

target_compile_features(concurrent_astar INTERFACE cxx_std_11)
