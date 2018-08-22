add_subdirectory(utils)
add_subdirectory(hash)
add_subdirectory(tiles)
add_subdirectory(closed)
add_subdirectory(open)
add_subdirectory(search)

# executables
add_executable(Solver solver.cpp)
add_executable(ExperimentalSolver experimental_solver.cpp)

target_compile_features(Solver PUBLIC cxx_std_17)
target_compile_features(ExperimentalSolver PUBLIC cxx_std_17)

target_link_libraries(Solver
  PRIVATE cxxopts
  PRIVATE search
  PRIVATE astar
  PRIVATE astar_pool
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE tile_node
  )

target_link_libraries(ExperimentalSolver
  PRIVATE cxxopts
  PRIVATE search
  PRIVATE astar
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE tile_node
  PRIVATE closed_chaining
  PRIVATE double_closed
  )

# warning flags
if (MSVC)
  target_compile_options(Solver PRIVATE /W4)
  target_compile_options(ExperimentalSolver PRIVATE /W4)
else()
  target_compile_options(Solver PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(ExperimentalSolver PRIVATE -Wall -Wextra -Wpedantic)
endif()
