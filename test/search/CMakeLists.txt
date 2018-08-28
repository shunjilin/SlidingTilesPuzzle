# astar test
add_executable(astar_test astar_test.cpp)

target_link_libraries(astar_test
  PRIVATE tile_node
  PRIVATE astar
  PRIVATE open_array
  PRIVATE closed_chaining
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE gtest
  PRIVATE gmock
  )

add_test(astar_test astar_test)
