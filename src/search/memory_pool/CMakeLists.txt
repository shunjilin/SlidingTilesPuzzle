# memory pool

add_library(MemoryPool INTERFACE)

target_include_directories(MemoryPool
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(MemoryPool INTERFACE cxx_std_17)
