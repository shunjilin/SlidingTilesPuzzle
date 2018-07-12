add_subdirectory(tiles)

# astar2
#add_library(astar2 STATIC astar2.cpp)

#target_include_directories(astar2
 # INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
 # )

# astar

add_library(astar STATIC astar.cpp)

target_include_directories(astar
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(astar PUBLIC cxx_std_11)
