# TODO: use helper functions so that DRY

# tiles

add_library(tiles STATIC tiles.cpp)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(tiles PUBLIC cxx_std_17)

# manhattan distance heuristic
add_library(manhattan_distance_heuristic STATIC manhattan_distance_heuristic.cpp)

target_include_directories(manhattan_distance_heuristic
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(manhattan_distance_heuristic
  PRIVATE tiles
)

# tile node

add_library(tile_node STATIC tile_node.hpp)

target_include_directories(tile_node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(tile_node
  PRIVATE tiles
  )
