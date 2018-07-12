# TODO: use custom functions so that DRY

# tiles test
add_executable(tiles_test tiles_test.cpp)

target_link_libraries(tiles_test
  PRIVATE tiles
  PRIVATE gtest
  PRIVATE gmock)

add_test(tiles_test tiles_test)

# manhattan heuristic test
add_executable(manhattan_distance_heuristic_test manhattan_distance_heuristic_test.cpp)

target_link_libraries(manhattan_distance_heuristic_test
  PRIVATE tiles
  PRIVATE manhattan_distance_heuristic
  PRIVATE gtest
  PRIVATE gmock)

add_test(manhattan_distance_heuristic_test manhattan_distance_heuristic_test)

# astar2 test
#add_executable(astar2_test astar2_test.cpp)

#target_link_libraries(astar2_test
 # PRIVATE astar2
  #PRIVATE tiles
  #PRIVATE manhattan_distance_heuristic
  #PRIVATE gtest
  #PRIVATE gmock)

#add_test(astar2_test astar2_test)
