# TODO: use custom functions so that DRY

# tiles test
add_executable(tiles_test tiles_test.cpp)

target_link_libraries(tiles_test
  PRIVATE tiles
  PRIVATE gtest
  PRIVATE gmock)

add_test(tiles_test tiles_test)

# manhattan distance test
add_executable(manhattan_distance_test manhattan_distance_test.cpp)

target_link_libraries(manhattan_distance_test
  PRIVATE manhattan_distance
  PRIVATE gtest
  PRIVATE gmock)

add_test(manhattan_distance_test manhattan_distance_test)

