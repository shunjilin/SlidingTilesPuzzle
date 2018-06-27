add_library(search STATIC search.cpp)

target_include_directories(search
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(search
  PRIVATE tiles
  PRIVATE heuristics)

#target_compile_features(search PUBLIC cxx_std_11)
