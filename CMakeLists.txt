cmake_minimum_required(VERSION 3.10)

project("Search")

# ctest
enable_testing()

add_subdirectory(utils)
add_subdirectory(dependencies)
add_subdirectory(search)
add_subdirectory(test)

# executables
add_executable(Solver solver.cpp)

target_compile_features(Solver PUBLIC cxx_std_17)

# TODO: make factory library to handle search configuration
target_link_libraries(Solver
  PRIVATE cxxopts
  PRIVATE astar
  PRIVATE open_array
  PRIVATE closed_open_address
  PRIVATE manhattan_distance_heuristic
  PRIVATE tile_node
  )

# Memory Pool solver
add_executable(Solver2 solver2.cpp)

target_compile_features(Solver2 PUBLIC cxx_std_17)

# TODO: make factory library to handle search configuration
target_link_libraries(Solver2
  PRIVATE cxxopts
  PRIVATE astar_pool
  PRIVATE open_array_ptr
  PRIVATE closed_open_address_ptr
  PRIVATE manhattan_distance_heuristic
  PRIVATE tile_node
  )


# warning flags
if (MSVC)
  target_compile_options(Solver PRIVATE /W4)
  target_compile_options(Solver2 PRIVATE /W4)
else()
  target_compile_options(Solver PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(Solver2 PRIVATE -Wall -Wextra -Wpedantic)
endif()

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE DEBUG)


## run ctest on build : this does not work if executables have not been compiled
# add_custom_command(TARGET 24Puzzle
#                  POST_BUILD
#                 COMMAND ctest --output-on-failure)
