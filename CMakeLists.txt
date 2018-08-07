cmake_minimum_required(VERSION 3.10)

project("Search")

# ctest
enable_testing()

add_subdirectory(utils)
add_subdirectory(dependencies)
add_subdirectory(search)
add_subdirectory(test)
add_subdirectory(benchmark)

# executables
add_executable(Solver solver.cpp)

target_compile_features(Solver PUBLIC cxx_std_17)

target_link_libraries(Solver
  PRIVATE cxxopts
  PRIVATE search
  PRIVATE astar
  PRIVATE astar_pool
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE tile_node
  )

# warning flags
if (MSVC)
  target_compile_options(Solver PRIVATE /W4)
else()
  target_compile_options(Solver PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE DEBUG)


## run ctest on build : this does not work if executables have not been compiled
# add_custom_command(TARGET 24Puzzle
#                  POST_BUILD
#                 COMMAND ctest --output-on-failure)
