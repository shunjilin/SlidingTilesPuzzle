add_subdirectory(utils)
add_subdirectory(hash)
add_subdirectory(tiles)
add_subdirectory(closed)
add_subdirectory(open)
add_subdirectory(search)


# executables
add_executable(Solver solver.cpp)
add_executable(ConcurrentSolver concurrent_solver.cpp)

target_compile_features(Solver PUBLIC cxx_std_17)
target_compile_features(ConcurrentSolver PUBLIC cxx_std_17)

target_link_libraries(Solver
  PRIVATE cxxopts
  PRIVATE search
  PRIVATE astar
  PRIVATE idastar
  PRIVATE open_array
  PRIVATE closed_open_address_pool
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE tile_node
  PRIVATE boost_system
  )

target_link_libraries(ConcurrentSolver
  PRIVATE cxxopts
  PRIVATE search
  PRIVATE concurrent_search
  PRIVATE concurrent_astar
  PRIVATE manhattan_distance_heuristic
  PRIVATE tabulation
  PRIVATE tile_node
  )

# warning flags
target_compile_options(Solver PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(ConcurrentSolver PRIVATE -Wall -Wextra -Wpedantic)
