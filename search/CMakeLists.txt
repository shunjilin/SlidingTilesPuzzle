add_subdirectory(tiles)

# search
add_library(search STATIC search.cpp)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(search
  PRIVATE tiles
  PRIVATE heuristics
  )

target_compile_features(search PUBLIC cxx_std_11)

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  PRIVATE search
  PRIVATE tiles
  PRIVATE heuristics
  )
