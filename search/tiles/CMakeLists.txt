# TODO: use helper functions so that DRY

# tile node

add_library(tiles STATIC tiles.cpp)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(tiles PUBLIC cxx_std_14)

# manhattan distance heuristic
add_library(manhattan_distance_heuristic STATIC manhattan_distance_heuristic.cpp)

target_include_directories(manhattan_distance_heuristic
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(manhattan_distance_heuristic
  PRIVATE tiles
) 
