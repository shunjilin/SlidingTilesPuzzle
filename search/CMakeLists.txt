add_subdirectory(tiles)
add_subdirectory(open)

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  PRIVATE open
  )

target_compile_features(astar PUBLIC cxx_std_11)
