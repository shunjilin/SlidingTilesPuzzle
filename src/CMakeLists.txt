add_subdirectory(utils)
add_subdirectory(hash)
add_subdirectory(tiles)
add_subdirectory(closed)
add_subdirectory(open)
add_subdirectory(search)

find_package(Boost)
if (Boost_FOUND)
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
  if (MSVC)
    target_compile_options(Solver PRIVATE /W4)
    target_compile_options(ConcurrentSolver PRIVATE /W4)
  else()
    target_compile_options(Solver PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ConcurrentSolver PRIVATE -Wall -Wextra -Wpedantic)
  endif()


else()
  message("Requires Boost")
endif()
