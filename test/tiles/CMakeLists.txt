# TODO: use custom functions so that DRY

# tilesUnitTest
add_executable(tilesUnitTest tilesUnitTest.cpp)

target_link_libraries(tilesUnitTest
  PRIVATE tiles
  PRIVATE gtest
  PRIVATE gmock)

add_test(tilesUnitTest tilesUnitTest)

# manhattanDistanceUnitTest
add_executable(manhattanDistanceUnitTest manhattanDistanceUnitTest.cpp)

target_link_libraries(manhattanDistanceUnitTest
  PRIVATE manhattan_distance
  PRIVATE gtest
  PRIVATE gmock)

add_test(manhattanDistanceUnitTest manhattanDistanceUnitTest)

