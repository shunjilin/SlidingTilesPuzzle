add_subdirectory(tiles)

# search
add_library(search STATIC search.cpp)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(search
  PRIVATE heuristics
  )

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  PRIVATE search
  PRIVATE heuristics
  )

target_compile_features(astar PUBLIC cxx_std_11)

# heuristics

add_library(heuristics STATIC heuristics.cpp)

target_link_libraries(heuristics
  PRIVATE node
  )

target_include_directories(heuristics
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# node

add_library(node STATIC node.cpp)

target_include_directories(node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
