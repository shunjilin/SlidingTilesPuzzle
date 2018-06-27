# TODO: use helper functions so that DRY
add_library(tiles STATIC tiles.cpp)
add_library(heuristics STATIC heuristics.cpp)

target_include_directories(tiles
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )
target_include_directories(heuristics
  INTERFACE ${CMAKE_CUrrent_SOURCE_DIR}
  )

target_link_libraries(heuristics
  PRIVATE tiles)

target_compile_features(tiles PUBLIC cxx_std_11)
