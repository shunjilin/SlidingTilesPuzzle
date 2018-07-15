add_subdirectory(open)

# astar test
add_executable(astar_test astar_test.cpp)

target_link_libraries(astar_test
  PRIVATE gtest
  PRIVATE gmock
  )

add_test(astar_test astar_test)
