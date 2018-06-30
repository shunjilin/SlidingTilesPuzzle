add_subdirectory(tiles)

# search
add_library(search STATIC search.cpp)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(search
  PRIVATE tiles
  PRIVATE heuristics
  )

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  PRIVATE search
  PRIVATE tiles
  PRIVATE heuristics
  )

# action

add_library(action STATIC action.cpp)

target_include_directories(action
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(action PUBLIC cxx_std_14)

# node

add_library(node STATIC node.cpp)

target_include_directories(node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# tile node

add_library(tile_node STATIC tile_node.cpp)

target_include_directories(tile_node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(tile_node
  PRIVATE tiles
  PRIVATE node
  )

target_compile_features(tile_node PUBLIC cxx_std_14)
