# TODO: use helper functions so that DRY

# tile node

add_library(tiles STATIC tiles.cpp)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(tiles
  PRIVATE node
  PRIVATE tile_heuristic
  )

target_compile_features(tiles PUBLIC cxx_std_14)

# heuristics
add_library(tile_heuristic STATIC tile_heuristic.cpp)

target_include_directories(tile_heuristic
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(tile_heuristic
  PRIVATE tiles
  PRIVATE manhattan_distance
  )

target_compile_features(tile_heuristic PUBLIC cxx_std_11)

# manhattan distance
add_library(manhattan_distance STATIC manhattan_distance.cpp)

target_include_directories(manhattan_distance
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
