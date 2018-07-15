add_library(open INTERFACE)

target_include_directories(open
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_features(open INTERFACE cxx_std_14)
