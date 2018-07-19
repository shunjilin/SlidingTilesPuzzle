add_subdirectory(open)
add_subdirectory(closed)
add_subdirectory(tiles)

# astar test
add_executable(astar_test astar_test.cpp)

target_link_libraries(astar_test
  PRIVATE tile_node
  PRIVATE astar
  PRIVATE open
  PRIVATE closed
  PRIVATE manhattan_distance_heuristic
  PRIVATE gtest
  PRIVATE gmock
  )

add_test(astar_test astar_test)
