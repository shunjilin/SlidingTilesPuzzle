# TODO: use custom functions so that DRY

# manhattan heuristic test
add_executable(manhattan_distance_heuristic_test manhattan_distance_heuristic_test.cpp)

target_link_libraries(manhattan_distance_heuristic_test
  PRIVATE tile_node
  PRIVATE manhattan_distance_heuristic
  PRIVATE gtest
  PRIVATE gmock)

add_test(manhattan_distance_heuristic_test manhattan_distance_heuristic_test)

# tile_node test
add_executable(tile_node_test tile_node_test.cpp)

target_link_libraries(tile_node_test
  PRIVATE tile_node
  PRIVATE gtest
  PRIVATE gmock)

add_test(tile_node_test tile_node_test)
