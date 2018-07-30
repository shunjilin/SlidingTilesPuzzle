# TODO: use helper functions so that DRY

# tiles

add_library(tiles INTERFACE)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(tiles INTERFACE cxx_std_17)

# manhattan distance heuristic
add_library(manhattan_distance_heuristic INTERFACE)

target_include_directories(manhattan_distance_heuristic
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(manhattan_distance_heuristic
  INTERFACE tiles
)

# tile node

add_library(tile_node INTERFACE)

target_include_directories(tile_node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(tile_node INTERFACE cxx_std_17)
