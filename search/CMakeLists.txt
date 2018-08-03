add_subdirectory(tiles)
add_subdirectory(open)
add_subdirectory(closed)

# astar

add_library(astar INTERFACE)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(astar INTERFACE cxx_std_11)
