add_subdirectory(tiles)

# search
add_library(search STATIC search.cpp)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(astar
  PRIVATE search
  )

target_compile_features(astar PUBLIC cxx_std_11)

# node

add_library(node STATIC node.cpp)

target_include_directories(node
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
