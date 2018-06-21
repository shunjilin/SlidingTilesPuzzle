add_library(tiles STATIC tiles.cpp)
target_include_directories(tiles
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(tiles PUBLIC cxx_std_11)
