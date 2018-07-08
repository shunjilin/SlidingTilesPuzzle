# TODO: use helper functions so that DRY

# tile node

add_library(tiles STATIC tiles.cpp)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(tiles
  #PRIVATE tiles
  PRIVATE node
  )

target_compile_features(tiles PUBLIC cxx_std_14)

# heuristics
add_library(manhattan_distance_heuristics STATIC manhattan_distance_heuristics.cpp)

target_include_directories(manhattan_distance_heuristics
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(manhattan_distance_heuristics
  PRIVATE heuristics
  PRIVATE tiles
  PRIVATE manhattan_distance
  )

target_compile_features(manhattan_distance_heuristics PUBLIC cxx_std_11)

# manhattan distance
add_library(manhattan_distance STATIC manhattan_distance.cpp)

target_include_directories(manhattan_distance
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
