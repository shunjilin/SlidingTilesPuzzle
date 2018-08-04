# compare incremental vs regular manhattan distance heuristic
add_executable(manhattan_distance_heuristic_bench manhattan_distance_heuristic_bench.cpp)

target_link_libraries(manhattan_distance_heuristic_bench
  PRIVATE benchmark
  PRIVATE tile_node
  PRIVATE manhattan_distance_heuristic
  )
